#include "orientation_gizmo.h"
#include <string.h>

void powergl_orientation_gizmo_create(powergl_object *obj, float size)
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

    powergl_mat4 mat = powergl_mat4_ident();
    mat.c[0].x = 0.1f;
    mat.c[1].y = 0.1f;
    mat.c[2].z = 0.1f;

    mat = powergl_mat4_rot(mat, cam->transform.rotation_z.w, cam->transform.rotation_z.xyz);
    mat = powergl_mat4_rot(mat, cam->transform.rotation_y.w, cam->transform.rotation_y.xyz);
    mat = powergl_mat4_rot(mat, cam->transform.rotation_x.w, cam->transform.rotation_x.xyz);

    mat.c[3].x = 0.8f;
    mat.c[3].y = 0.8f;
    mat.c[3].z = 0.0f;

    obj->transform.mvp = mat;
    obj->transform.mvp_flag = 1;
}

