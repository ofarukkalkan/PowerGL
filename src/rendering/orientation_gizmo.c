#include "orientation_gizmo.h"
#include <string.h>
#include "../math/mat4x4.h"

void powergl_orientation_gizmo_create(powergl_object *obj)
{
    if(!obj)
        return;
    memset(obj, 0, sizeof(*obj));
    powergl_transform_reset(&obj->transform);

    obj->geometry.visible_flag = 1;
    obj->geometry.primitive_type = GL_LINES;
    obj->geometry.n_vertex = 6;
    obj->geometry.vertex = powergl_resize(NULL, 6, sizeof(powergl_vec3));
    obj->geometry.vertex_flag = 1;
    obj->geometry.triangles.color = powergl_resize(NULL, 6, sizeof(powergl_vec3));
    obj->geometry.triangles.n_color = 6;
    obj->geometry.triangles.color_flag = 1;

    obj->geometry.vertex[0] = (powergl_vec3){0.f, 0.f, 0.f};
    obj->geometry.vertex[1] = (powergl_vec3){1.f, 0.f, 0.f};
    obj->geometry.triangles.color[0] = (powergl_vec3){1.f, 0.f, 0.f};
    obj->geometry.triangles.color[1] = (powergl_vec3){1.f, 0.f, 0.f};

    obj->geometry.vertex[2] = (powergl_vec3){0.f, 0.f, 0.f};
    obj->geometry.vertex[3] = (powergl_vec3){0.f, 1.f, 0.f};
    obj->geometry.triangles.color[2] = (powergl_vec3){0.f, 1.f, 0.f};
    obj->geometry.triangles.color[3] = (powergl_vec3){0.f, 1.f, 0.f};

    obj->geometry.vertex[4] = (powergl_vec3){0.f, 0.f, 0.f};
    obj->geometry.vertex[5] = (powergl_vec3){0.f, 0.f, 1.f};
    obj->geometry.triangles.color[4] = (powergl_vec3){0.f, 0.f, 1.f};
    obj->geometry.triangles.color[5] = (powergl_vec3){0.f, 0.f, 1.f};
}

void powergl_orientation_gizmo_update(powergl_object *obj, powergl_object *cam)
{
    if(!obj || !cam)
        return;

    powergl_mat4 rot = powergl_mat4_ident();
    rot = powergl_mat4_rot(rot, cam->transform.rotation_z.w, cam->transform.rotation_z.xyz);
    rot = powergl_mat4_rot(rot, cam->transform.rotation_y.w, cam->transform.rotation_y.xyz);
    rot = powergl_mat4_rot(rot, cam->transform.rotation_x.w, cam->transform.rotation_x.xyz);
    rot = powergl_mat4_transpose(rot); /* inverse rotation */

    powergl_mat4 m = powergl_mat4_ident();
    m.c[0].x = 0.2f;
    m.c[1].y = 0.2f;
    m.c[2].z = 0.2f;
    m = powergl_mat4_mul(rot, m);
    powergl_mat4 trans = powergl_mat4_ident();
    trans.c[3].x = 0.8f;
    trans.c[3].y = 0.8f;
    m = powergl_mat4_mul(trans, m);

    obj->transform.mvp = m;
    obj->transform.mvp_flag = 1;
}
