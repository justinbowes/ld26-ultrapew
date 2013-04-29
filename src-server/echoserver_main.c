/*
 * udpserver.c - A simple UDP echo server
 * usage: udpserver <port>
 */

#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "uthash.h"

#include "xpl.h"
#include "xpl_log.h"
#include "xpl_hash.h"

#include "game/game.h"
#include "game/packet.h"

#include "udpnet.h"

#define BUFSIZE 1024

#define TIMEOUT 5.0

typedef struct client_info {
	int					id;
	
	UDPNET_ADDRESS		remote_addr;
	
	uint32_t			seq;
	double				last_packet_time;
	
	player_id_t			player_id;
	
	bool				drop;
		
	UT_hash_handle		hh;
} client_info_t;

static client_info_t *clients = NULL;
static uint16_t client_uid_counter = 1;
static SOCKET sock;

/*
 * error - wrapper for perror
 */
static void error(char *msg) {
	LOG_ERROR("%s", msg);
	exit(1);
}

static void pointcast_buffer(uint8_t *buf, int size, client_info_t *client) {
	int ret = udp_send(sock, buf, size, client->remote_addr.address, client->remote_addr.port);
	if (ret) {
		LOG_DEBUG("Failed to send to %u, dropping", client->player_id.client_id);
		client->drop = true;
	}
}

static void pointcast_packet(uint16_t subject, packet_t *packet, client_info_t *client) {
	uint8_t buf[1024];
	size_t size = packet_encode(packet, subject, buf);
	pointcast_buffer(buf, (int)size, client);
}

static void broadcast_buffer(uint8_t *buf, int size) {
	client_info_t *dest, *tmp;
	HASH_ITER(hh, clients, dest, tmp) {
		pointcast_buffer(buf, size, dest);
	}
}


static void broadcast_packet(uint16_t subject, packet_t *packet) {
	uint8_t buf[1024];
	size_t size = packet_encode(packet, subject, buf);
	broadcast_buffer(buf, (int)size);
}


static client_info_t *get_client(UDPNET_ADDRESS *remote_addr) {
	client_info_t *client;
	int hash = xpl_hashs(remote_addr->address, XPL_HASH_INIT);
	hash = xpl_hashi(remote_addr->port, hash);
	HASH_FIND_INT(clients, &hash, client);
	
	if (! client) {
		LOG_INFO("New client");
		client = xpl_calloc_type(client_info_t);
		client->id = hash;
		client->remote_addr = *remote_addr;
		client->player_id.client_id = client_uid_counter++;
		LOG_INFO("Client %u at %s:%d", client->player_id.client_id, client->remote_addr.address, client->remote_addr.port);
		HASH_ADD_INT(clients, id, client);
	}
	
	return client;
}

static void delete_client(client_info_t *client) {
	HASH_DEL(clients, client);

	LOG_DEBUG("Sending goodbye packet");
	packet_t bye;
	memset(&bye, 0, sizeof(bye));
	bye.type = pt_goodbye;
	bye.goodbye = client->player_id;
	broadcast_packet(client->player_id.client_id, &bye);
	
	xpl_free(client);
}

static void purge_clients() {
	double time = xpl_get_time();
	client_info_t *dest, *tmp;
	HASH_ITER(hh, clients, dest, tmp) {
		
		if (dest->drop) {
			LOG_DEBUG("Dropping client %u", dest->player_id.client_id);
			delete_client(dest);
		}
		
		if (time - dest->last_packet_time > TIMEOUT) {
			LOG_DEBUG("Timeout client %u", dest->player_id.client_id);
			delete_client(dest);
		}
	}
}

int main(int argc, char **argv) {
	uint8_t buf[BUFSIZE];				/* message buf */
	int n;							/* message byte size */
	
	xpl_init_timer();
	
	/*
	 * check command line arguments
	 */
	if (argc != 2) {
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		exit(1);
	}
	int portno = atoi(argv[1]);
	
	/* setsockopt: Handy debugging trick that lets
	 * us rerun the server immediately after we kill it;
	 * otherwise we have to wait about 20 secs.
	 * Eliminates "ERROR on binding: Address already in use" error.
	 */
	//	struct sockaddr_in serveraddr;	/* server's addr */
	//	int optval;						/* flag value for setsockopt */
	//	optval = 1;
	//	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,
	//			   (const void *)&optval , sizeof(int));

	udp_socket_init();
	sock = udp_create_endpoint(portno);
	if (sock < 0) {
		error("Couldn't bind endpoint");
	}
	
	LOG_INFO("Socket bound on port %d", portno);
	
	while (1) {
		memset(buf, 0, 1024);
		purge_clients();
		
		UDPNET_ADDRESS src;
		n = udp_receive(sock, buf, BUFSIZE, &src);
		
		if (n < 0) {
			int e = udp_error();
			if (e == EWOULDBLOCK ||
				e == EAGAIN) {
				xpl_sleep_seconds(0.01);
				continue;
			}
			error("Error code from socket on receive");
		}
		
		LOG_DEBUG("Received packet");
		
		client_info_t *client_info = get_client(&src);

		uint16_t client_source;
		packet_t packet;
		packet_decode(&packet, &client_source, buf);
		
		if (packet.seq <= client_info->seq) {
			LOG_DEBUG("Dropping old packet %d", packet.seq);
			continue;
		}
		client_info->seq = packet.seq;
		
		if (packet.type == pt_hello) {
			if (packet.hello.nonce && client_source == 0) {
				client_source = client_info->player_id.client_id;
				LOG_DEBUG("Sending client id %u to client", client_info->player_id.client_id);
				packet.hello.client_id = client_info->player_id.client_id;
				pointcast_packet(client_source, &packet, client_info);
				
				assert(client_source != 0);
			}
			strncpy(client_info->player_id.name, packet.hello.name, NAME_SIZE);
			// Overwrite the nonce so it's not shared
			packet.hello.nonce = 0;
		}
		
		if (client_source != client_info->player_id.client_id) {
			LOG_WARN("Packet client_id mismatch (claim %u, have %u); dropping packet",
					 client_source, client_info->player_id.client_id);
			continue;
		}
		
		double time = xpl_get_time();
		client_info->last_packet_time = time;
		
		broadcast_packet(client_source, &packet);
		
	}
}