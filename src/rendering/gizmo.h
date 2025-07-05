#ifndef _powergl_gizmo_h
#define _powergl_gizmo_h

#include "object.h"

void powergl_gizmo_create(powergl_object *obj, float size);
void powergl_gizmo_draw(powergl_object *cam, int width, int height);

#endif
