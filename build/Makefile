SRCDIR = ../src-xpl ../src/game ../src-server
INCDIR = -I../include-xpl -I../include -I../include-lib/common
CFLAGS = -g -Wall $(INCDIR) -O3 -std=gnu99
LFLAGS = -lpthread -lm -lrt
CC = gcc

SOURCES = ../src-server/echoserver_main.c ../src-xpl/xpl_platform.c ../src/game/packet.c ../src/net/udpnet.c
OBJECTS = $(patsubst %.c,%.o,$(wildcard *.c))
TARGET = echoserver

.PHONY : all

all: clean import depend build

build: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LFLAGS) -o $(TARGET)

import:
	@echo "import"
	@rm -f *.c *~
	@for file in $(SOURCES); do ln -s $$file ; done

depend:
	@echo "depend"
	@makedepend $(INCDIR) -Y -m $(SOURCES)

clean:
	@echo "clean"
	@rm -f *.o *.bak *.c *~ *%

##### End of makefile
# DO NOT DELETE

../src-server/echoserver_main.o: ../include-lib/common/uthash.h
../src-server/echoserver_main.o: ../include-xpl/xpl.h
../src-server/echoserver_main.o: ../include/app_settings.h
../src-server/echoserver_main.o: ../include-xpl/xpl_platform.h
../src-server/echoserver_main.o: ../include-xpl/xpl_memory.h
../src-server/echoserver_main.o: ../include-xpl/xpl_rc.h
../src-server/echoserver_main.o: ../include-xpl/xpl_log.h
../src-server/echoserver_main.o: ../include-xpl/xpl_file.h
../src-server/echoserver_main.o: ../include-xpl/xpl_dynamic_buffer.h
../src-server/echoserver_main.o: ../include-xpl/xpl_l10n.h
../src-server/echoserver_main.o: ../include-xpl/xpl_hash.h
../src-server/echoserver_main.o: ../include/game/game.h
../src-server/echoserver_main.o: ../include-xpl/xpl_vec2.h
../src-server/echoserver_main.o: ../include-xpl/xpl_vec4.h
../src-server/echoserver_main.o: ../include-xpl/xpl_vec3.h
../src-server/echoserver_main.o: ../include-xpl/xpl_ivec2.h
../src-server/echoserver_main.o: ../include-xpl/xpl_irect.h
../src-server/echoserver_main.o: ../include-xpl/xpl_vec.h
../src-server/echoserver_main.o: ../include-xpl/xpl_math.h
../src-server/echoserver_main.o: ../include-xpl/xpl_ivec3.h
../src-server/echoserver_main.o: ../include-xpl/xpl_ivec4.h
../src-server/echoserver_main.o: ../include-xpl/xpl_rect.h
../src-server/echoserver_main.o: ../include-xpl/xpl_plane.h
../src-server/echoserver_main.o: ../include-xpl/xpl_sphere.h
../src-server/echoserver_main.o: ../include-xpl/xpl_quaternion.h
../src-server/echoserver_main.o: ../include-xpl/xpl_mat2.h
../src-server/echoserver_main.o: ../include-xpl/xpl_mat3.h
../src-server/echoserver_main.o: ../include-xpl/xpl_mat4.h
../src-server/echoserver_main.o: ../include/audio/audio.h
../src-server/echoserver_main.o: ../include/game/packet.h
../src-server/echoserver_main.o: ../include/net/udpnet.h
../src-xpl/xpl_platform.o: ../include-xpl/xpl.h ../include/app_settings.h
../src-xpl/xpl_platform.o: ../include-xpl/xpl_platform.h
../src-xpl/xpl_platform.o: ../include-xpl/xpl_memory.h
../src-xpl/xpl_platform.o: ../include-xpl/xpl_rc.h ../include-xpl/xpl_log.h
../src-xpl/xpl_platform.o: ../include-xpl/xpl_file.h
../src-xpl/xpl_platform.o: ../include-xpl/xpl_dynamic_buffer.h
../src-xpl/xpl_platform.o: ../include-xpl/xpl_l10n.h
../src/game/packet.o: ../include/game/packet.h ../include/game/game.h
../src/game/packet.o: ../include-xpl/xpl_vec2.h ../include-xpl/xpl_platform.h
../src/game/packet.o: ../include-xpl/xpl.h ../include/app_settings.h
../src/game/packet.o: ../include-xpl/xpl_memory.h ../include-xpl/xpl_rc.h
../src/game/packet.o: ../include-xpl/xpl_log.h ../include-xpl/xpl_file.h
../src/game/packet.o: ../include-xpl/xpl_dynamic_buffer.h
../src/game/packet.o: ../include-xpl/xpl_l10n.h ../include-xpl/xpl_vec4.h
../src/game/packet.o: ../include-xpl/xpl_vec3.h ../include-xpl/xpl_ivec2.h
../src/game/packet.o: ../include-xpl/xpl_irect.h ../include-xpl/xpl_vec.h
../src/game/packet.o: ../include-xpl/xpl_math.h ../include-xpl/xpl_ivec3.h
../src/game/packet.o: ../include-xpl/xpl_ivec4.h ../include-xpl/xpl_rect.h
../src/game/packet.o: ../include-xpl/xpl_plane.h ../include-xpl/xpl_sphere.h
../src/game/packet.o: ../include-xpl/xpl_quaternion.h
../src/game/packet.o: ../include-xpl/xpl_mat2.h ../include-xpl/xpl_mat3.h
../src/game/packet.o: ../include-xpl/xpl_mat4.h ../include/audio/audio.h
../src/game/packet.o: ../include-lib/common/uthash.h
../src/net/udpnet.o: ../include/net/udpnet.h ../include-xpl/xpl.h
../src/net/udpnet.o: ../include/app_settings.h ../include-xpl/xpl_platform.h
../src/net/udpnet.o: ../include-xpl/xpl_memory.h ../include-xpl/xpl_rc.h
../src/net/udpnet.o: ../include-xpl/xpl_log.h ../include-xpl/xpl_file.h
../src/net/udpnet.o: ../include-xpl/xpl_dynamic_buffer.h
../src/net/udpnet.o: ../include-xpl/xpl_l10n.h
