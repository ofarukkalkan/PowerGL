#ifndef _powergl_geometry_h
#define _powergl_geometry_h

#include "vec3.h"

int powergl_test_ray_tri_mesh(powergl_vec3 *mesh, int n_vertex, float mvp[4][4], float event_pos[2], float vp[4], powergl_vec3 *P, int cull );


#endif
