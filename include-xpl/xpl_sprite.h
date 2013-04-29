/*
 * xpl_sprite_batch.h
 *
 *  Created on: 2012-12-21
 *      Author: Justin
 */

#ifndef XPL_SPRITE_BATCH_H
#define XPL_SPRITE_BATCH_H

#include <wchar.h>

#include "uthash.h"

#include "xpl_gl.h"
#include "xpl_vec.h"

static const int BLEND_FUNCS_PREMULT[] = {
    GL_ONE, GL_ONE_MINUS_SRC_ALPHA,
    GL_ONE, GL_ZERO
};
static const int BLEND_FUNCS_NO_PREMULT[] = {
    GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA,
    GL_ONE, GL_ZERO
};
static const int BLEND_FUNCS_MULTIPLY[] = {
    GL_DST_COLOR, GL_ZERO,
    GL_DST_ALPHA, GL_ZERO
};
static const int BLEND_FUNCS_ADD[] = {
    GL_ONE, GL_ONE,
    GL_ONE, GL_ONE
};
static const int BLEND_FUNCS_REPLACE[] = {
    GL_SRC_ALPHA, GL_ZERO,
    GL_ONE, GL_ZERO,
};

typedef struct xpl_sprite xpl_sprite_t;
typedef struct xpl_sprite_batch xpl_sprite_batch_t;

#define XPL_SPRITE_SHEET_END    -1

typedef struct xpl_sprite_sheet_sprite {
    int                         sprite_id;
    xirect                      rect;
} xpl_sprite_sheet_sprite_t;

typedef struct xpl_sprite_sheet_def {
    const char *resource;
    xivec2 image_dimension;
    xivec2 slices;
    int invert_ids_y;
} xpl_sprite_sheet_def_t;

typedef struct xpl_sprite_sheet_entry xpl_sprite_sheet_entry_t;
typedef struct xpl_sprite_sheet xpl_sprite_sheet_t;

xpl_sprite_batch_t * xpl_sprite_batch_new(void);
void xpl_sprite_batch_destroy(struct xpl_sprite_batch **ppbatch);

void xpl_sprite_batch_begin(struct xpl_sprite_batch *self);
void xpl_sprite_batch_end(struct xpl_sprite_batch *self);

xmat4 *xpl_sprite_batch_matrix_push(struct xpl_sprite_batch *self);
void xpl_sprite_batch_matrix_pop(struct xpl_sprite_batch *self);

struct xpl_sprite *xpl_sprite_new(struct xpl_sprite_batch *batch, const char *resource, const xirect *region);
void xpl_sprite_destroy(struct xpl_sprite **ppsprite);
void xpl_sprite_set_blend_funcs(struct xpl_sprite *sprite, const int *blend_funcs);
void xpl_sprite_draw(struct xpl_sprite *sprite, float x, float y, float width, float height);
void xpl_sprite_draw_colored(struct xpl_sprite *sprite, float x, float y, float width, float height, xvec4 color);
void xpl_sprite_draw_transformed(struct xpl_sprite *sprite, float x, float y, float origin_x, float origin_y, float width, float height, float scale_x, float scale_y, float rotation_rads, xvec4 *color);

xpl_sprite_sheet_t *xpl_sprite_sheet_new(struct xpl_sprite_batch *batch, const char *resource, const xpl_sprite_sheet_sprite_t *sprite_defs);
xpl_sprite_sheet_t *xpl_sprite_sheet_new_def(struct xpl_sprite_batch *batch, xpl_sprite_sheet_def_t *def);
struct xpl_sprite *xpl_sprite_get(struct xpl_sprite_sheet *sheet, int sprite_id);
void xpl_sprite_sheet_destroy(xpl_sprite_sheet_t **ppsheet);

#endif /* XPL_SPRITE_BATCH_H */
