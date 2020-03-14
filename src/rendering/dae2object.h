#ifndef _powergl_rendering_dae2object_h
#define _powergl_dae2object_h

#include "../powergl.h"
#include "../collada/collada.h"
#include "../math/mat4x4.h"
#include "object.h"

#include <stdio.h>
#include <string.h>
#include <math.h>


void powergl_build_geometry_triangle_index(powergl_geometry *geo, powergl_collada_core_triangles *triangles, powergl_collada_core_input_local_offset  *vertex_input, powergl_collada_core_input_local_offset  *color_input, powergl_collada_core_input_local_offset  *normal_input);
void powergl_build_geometry_triangle_color(powergl_geometry *geo, powergl_collada_core_triangles *triangles, powergl_collada_core_input_local_offset  *color_input);
void powergl_build_geometry_triangle_normal(powergl_geometry *geo, powergl_collada_core_triangles *triangles, powergl_collada_core_input_local_offset  *normal_input);
void powergl_build_geometry_triangle_vertex(powergl_geometry *geo, powergl_collada_core_triangles *triangles, powergl_collada_core_input_local_offset  *vertex_input);
void powergl_build_geometry_triangle(powergl_geometry *geo, powergl_collada_core_triangles *triangles);
void powergl_build_geometry(powergl_collada_core_node *node, powergl_object *obj);
void powergl_build_camera(powergl_collada_core_node *node, powergl_object *obj);
void powergl_build_light(powergl_collada_core_node *node, powergl_object *obj);
void powergl_build_transform(powergl_collada_core_node *node, powergl_object *obj);
void powergl_build_object(powergl_collada_core_node  *node, powergl_object *obj);

#endif
