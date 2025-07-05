#include "gizmo.h"
#include "pipeline.h"
#include "../math/mat4x4.h"
#include <string.h>

static powergl_object gizmo_obj;
static powergl_object *gizmo_objs[1] = {&gizmo_obj};
static powergl_pipeline3 gizmo_pipeline;
static int gizmo_initialized = 0;

void powergl_gizmo_create(powergl_object *obj, float size)
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

void powergl_gizmo_draw(powergl_object *cam, int width, int height)
{
    if(!gizmo_initialized){
        powergl_gizmo_create(&gizmo_obj, 1.0f);
        powergl_pipeline3_create(&gizmo_pipeline, gizmo_objs, 1);
        gizmo_initialized = 1;
    }

    if(!cam)
        return;

    powergl_mat4 rot = powergl_mat4_ident();
    rot = powergl_mat4_rot(rot, cam->transform.rotation_z.w, cam->transform.rotation_z.xyz);
    rot = powergl_mat4_rot(rot, cam->transform.rotation_y.w, cam->transform.rotation_y.xyz);
    rot = powergl_mat4_rot(rot, cam->transform.rotation_x.w, cam->transform.rotation_x.xyz);
    rot = powergl_mat4_transpose(rot);

    powergl_mat4 proj = powergl_mat4_perspectiveRH(powergl_float_to_radians(30.0f), 1.0f, 0.1f, 10.0f);
    gizmo_obj.transform.mvp = powergl_mat4_mul(proj, rot);
    gizmo_obj.transform.mvp_flag = 1;

    GLint vp[4];
    glGetIntegerv(GL_VIEWPORT, vp);
    int size = 80;
    glViewport(width - size - 10, height - size - 10, size, size);
    powergl_pipeline3_render(&gizmo_pipeline, gizmo_objs, 1);
    glViewport(vp[0], vp[1], vp[2], vp[3]);
}
