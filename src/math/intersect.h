#ifndef _powergl_intersect_h
#define _powergl_intersect_h

#include "vec3.h"
#include "mat4x4.h"

int powergl_intersect_ray_tri_mesh(powergl_vec3 *mesh, int n_vertex, powergl_mat4 mvp, powergl_vec2 event_pos, powergl_vec4 vp, powergl_vec3 *P, int cull );

#endif
