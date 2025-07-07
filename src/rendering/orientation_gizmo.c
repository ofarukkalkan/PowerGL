#include "orientation_gizmo.h"
#include "../math/mat4x4.h"
#include <string.h>

void powergl_orientation_gizmo_create(powergl_object *obj, float size)
{
    if(!obj)
        return;
    memset(obj, 0, sizeof(*obj));
    powergl_transform_reset(&obj->transform);

    obj->geometry.visible_flag = 1;
    obj->geometry.primitive_type = GL_LINES;
    obj->geometry.vertex = powergl_resize(NULL, 6, sizeof(powergl_vec3));
    obj->geometry.n_vertex = 6;
    obj->geometry.vertex_flag = 1;
    obj->geometry.triangles.color = powergl_resize(NULL, 6, sizeof(powergl_vec3));
    obj->geometry.triangles.n_color = 6;
    obj->geometry.triangles.color_flag = 1;

    obj->geometry.vertex[0] = (powergl_vec3){0.0f, 0.0f, 0.0f};
    obj->geometry.vertex[1] = (powergl_vec3){size, 0.0f, 0.0f};
    obj->geometry.vertex[2] = (powergl_vec3){0.0f, 0.0f, 0.0f};
    obj->geometry.vertex[3] = (powergl_vec3){0.0f, size, 0.0f};
    obj->geometry.vertex[4] = (powergl_vec3){0.0f, 0.0f, 0.0f};
    obj->geometry.vertex[5] = (powergl_vec3){0.0f, 0.0f, size};

    obj->geometry.triangles.color[0] = (powergl_vec3){1.0f, 0.0f, 0.0f};
    obj->geometry.triangles.color[1] = (powergl_vec3){1.0f, 0.0f, 0.0f};
    obj->geometry.triangles.color[2] = (powergl_vec3){0.0f, 1.0f, 0.0f};
    obj->geometry.triangles.color[3] = (powergl_vec3){0.0f, 1.0f, 0.0f};
    obj->geometry.triangles.color[4] = (powergl_vec3){0.0f, 0.0f, 1.0f};
    obj->geometry.triangles.color[5] = (powergl_vec3){0.0f, 0.0f, 1.0f};
}

void powergl_orientation_gizmo_update(powergl_object *obj, powergl_object *cam)
{
    if(!obj || !cam)
        return;

    powergl_vec3 right = {cam->transform.world.c[0].x,
                          cam->transform.world.c[0].y,
                          cam->transform.world.c[0].z};
    powergl_vec3 up = {cam->transform.world.c[1].x,
                       cam->transform.world.c[1].y,
                       cam->transform.world.c[1].z};
    powergl_vec3 forward = {cam->transform.world.c[2].x,
                            cam->transform.world.c[2].y,
                            cam->transform.world.c[2].z};

    powergl_vec3 pos = cam->transform.location;
    pos = powergl_vec3_add(pos, powergl_vec3_muls(right, 2.0f));
    pos = powergl_vec3_add(pos, powergl_vec3_muls(up, 2.0f));
    pos = powergl_vec3_add(pos, powergl_vec3_muls(forward, -5.0f));

    obj->transform.local = powergl_mat4_ident();
    obj->transform.local = powergl_mat4_translate(obj->transform.local, pos);
    obj->transform.matrix_flag = 1;
    obj->transform.world = obj->transform.local;

    powergl_mat4 view = cam->camera.view;
    view.c[3].x = 0.0f;
    view.c[3].y = 0.0f;
    view.c[3].z = 0.0f;
    powergl_mat4 vp = powergl_mat4_mul(cam->camera.projection, view);
    obj->transform.mvp = powergl_mat4_mul(vp, obj->transform.world);
    obj->transform.mvp_flag = 1;
}

void powergl_orientation_gizmo_draw(powergl_pipeline3 *ppl, powergl_object *obj)
{
    if(!ppl || !obj)
        return;

    GLint vp[4];
    glGetIntegerv(GL_VIEWPORT, vp);
    glViewport(vp[2] - 120, vp[3] - 120, 120, 120);
    glDisable(GL_DEPTH_TEST);
    powergl_pipeline3_render(ppl, &obj, 1);
    glEnable(GL_DEPTH_TEST);
    glViewport(vp[0], vp[1], vp[2], vp[3]);
}
