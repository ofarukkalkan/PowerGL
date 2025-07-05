#include "grid.h"
#include <string.h>

void powergl_grid_create(powergl_object *obj, int half_size)
{
    if(!obj)
        return;
    memset(obj, 0, sizeof(*obj));
    powergl_transform_reset(&obj->transform);

    int lines = half_size * 2 + 1;
    int n_vertices = lines * 4;

    obj->geometry.visible_flag = 1;
    obj->geometry.primitive_type = GL_LINES;
    obj->geometry.vertex = powergl_resize(NULL, n_vertices, sizeof(powergl_vec3));
    obj->geometry.n_vertex = n_vertices;
    obj->geometry.vertex_flag = 1;
    obj->geometry.triangles.color = powergl_resize(NULL, n_vertices, sizeof(powergl_vec3));
    obj->geometry.triangles.n_color = n_vertices;
    obj->geometry.triangles.color_flag = 1;

    powergl_vec3 col = {0.5f, 0.5f, 0.5f};
    int idx = 0;
    for(int i = -half_size; i <= half_size; ++i){
        obj->geometry.vertex[idx]   = (powergl_vec3){(float)i, 0.0f, (float)-half_size};
        obj->geometry.vertex[idx+1] = (powergl_vec3){(float)i, 0.0f, (float)half_size};
        obj->geometry.vertex[idx+2] = (powergl_vec3){(float)-half_size, 0.0f, (float)i};
        obj->geometry.vertex[idx+3] = (powergl_vec3){(float)half_size, 0.0f, (float)i};
        obj->geometry.triangles.color[idx] = col;
        obj->geometry.triangles.color[idx+1] = col;
        obj->geometry.triangles.color[idx+2] = col;
        obj->geometry.triangles.color[idx+3] = col;
        idx += 4;
    }
}
