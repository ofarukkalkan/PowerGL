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
    obj->geometry.vertex = powergl_resize(NULL, 6, sizeof(powergl_vec3));
    obj->geometry.n_vertex = 6;
    obj->geometry.vertex_flag = 1;
    obj->geometry.triangles.color = powergl_resize(NULL, 6, sizeof(powergl_vec3));
    obj->geometry.triangles.n_color = 6;
    obj->geometry.triangles.color_flag = 1;

    /* X axis (red) */
    obj->geometry.vertex[0] = (powergl_vec3){0.0f, 0.0f, 0.0f};
    obj->geometry.vertex[1] = (powergl_vec3){size, 0.0f, 0.0f};
    obj->geometry.triangles.color[0] = (powergl_vec3){1.0f, 0.0f, 0.0f};
    obj->geometry.triangles.color[1] = (powergl_vec3){1.0f, 0.0f, 0.0f};

    /* Y axis (green) */
    obj->geometry.vertex[2] = (powergl_vec3){0.0f, 0.0f, 0.0f};
    obj->geometry.vertex[3] = (powergl_vec3){0.0f, size, 0.0f};
    obj->geometry.triangles.color[2] = (powergl_vec3){0.0f, 1.0f, 0.0f};
    obj->geometry.triangles.color[3] = (powergl_vec3){0.0f, 1.0f, 0.0f};

    /* Z axis (blue - forward is -Z in OpenGL default) */
    obj->geometry.vertex[4] = (powergl_vec3){0.0f, 0.0f, 0.0f};
    obj->geometry.vertex[5] = (powergl_vec3){0.0f, 0.0f, -size};
    obj->geometry.triangles.color[4] = (powergl_vec3){0.0f, 0.0f, 1.0f};
    obj->geometry.triangles.color[5] = (powergl_vec3){0.0f, 0.0f, 1.0f};
}

void powergl_orientation_gizmo_update(powergl_object *obj, powergl_object *cam)
{
    if(!obj || !cam)
        return;
    powergl_mat4 view = cam->camera.view;
    view.c[3].r[0] = 0.0f;
    view.c[3].r[1] = 0.0f;
    view.c[3].r[2] = 0.0f;
    powergl_mat4 proj = powergl_mat4_perspectiveRH(powergl_float_to_radians(45.0f),
                                                   1.0f, cam->camera.znear, cam->camera.zfar);
    obj->transform.mvp = powergl_mat4_mul(proj, powergl_mat4_mul(view, obj->transform.world));
    obj->transform.mvp_flag = 1;
}

