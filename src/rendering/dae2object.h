#ifndef _powergl_rendering_dae2object_h
#define _powergl_dae2object_h

#include "../powergl.h"
#include "../collada/collada.h"
#include "../math/mat4x4.h"
#include "object.h"

#include <stdio.h>
#include <string.h>
#include <math.h>

void powergl_build_collider(powergl_object *obj);
void powergl_build_animation(powergl_collada_core_library_animations *anim_lib, powergl_object *obj);
void powergl_build_geometry(powergl_collada_core_node *node, powergl_object *obj);
void powergl_build_camera(powergl_collada_core_node *node, powergl_object *obj);
void powergl_build_light(powergl_collada_core_node *node, powergl_object *obj);
void powergl_build_transform(powergl_collada_core_node *node, powergl_object *obj);
void powergl_build_object(powergl_collada_core_node  *node, powergl_collada_core_COLLADA *root, powergl_object *obj);


#endif
