#ifndef _powergl_scene_hierarchy_h
#define _powergl_scene_hierarchy_h

#include "../rendering/visualscene.h"
#include "../../third_party/nuklear/nuklear.h"

void powergl_ui_draw_object_tree(struct nk_context *ctx, powergl_object *obj);
void powergl_ui_draw_scene_hierarchy(struct nk_context *ctx,
                                     powergl_visualscene *scene,
                                     struct nk_rect bounds);

#endif
