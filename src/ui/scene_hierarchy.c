#include "scene_hierarchy.h"

void powergl_ui_draw_object_tree(struct nk_context *ctx, powergl_object *obj){
    const char *label = obj->id ? obj->id : "object";
    if(nk_tree_push_id(ctx, NK_TREE_NODE, label, NK_MINIMIZED, (int)(intptr_t)obj)){
        nk_labelf(ctx, NK_TEXT_LEFT, "Name: %s", label);
        nk_labelf(ctx, NK_TEXT_LEFT, "Translate: %.2f %.2f %.2f",
                  obj->transform.location.x,
                  obj->transform.location.y,
                  obj->transform.location.z);
        nk_labelf(ctx, NK_TEXT_LEFT, "Rotation: %.2f %.2f %.2f",
                  obj->transform.rotation_x.w,
                  obj->transform.rotation_y.w,
                  obj->transform.rotation_z.w);
        nk_labelf(ctx, NK_TEXT_LEFT, "Scale: %.2f %.2f %.2f",
                  obj->transform.scale.x,
                  obj->transform.scale.y,
                  obj->transform.scale.z);
        for(size_t i = 0; i < obj->n_object; ++i)
            powergl_ui_draw_object_tree(ctx, obj->objects[i]);
        nk_tree_pop(ctx);
    }
}

void powergl_ui_draw_scene_hierarchy(struct nk_context *ctx,
                                     powergl_visualscene *scene,
                                     struct nk_rect bounds){
    if(nk_begin(ctx, "Scene Hierarchy", bounds,
                NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
                NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE)){
        if(nk_tree_push(ctx, NK_TREE_NODE, "visual_scene", NK_MINIMIZED)){
            for(size_t i = 0; i < scene->n_object; ++i)
                powergl_ui_draw_object_tree(ctx, scene->objects[i]);
            nk_tree_pop(ctx);
        }
    }
    nk_end(ctx);
}
