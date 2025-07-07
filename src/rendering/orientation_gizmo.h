#ifndef POWERGL_ORIENTATION_GIZMO_H
#define POWERGL_ORIENTATION_GIZMO_H
#include "object.h"
#include "pipeline.h"

void powergl_orientation_gizmo_create(powergl_object *obj, float size);
void powergl_orientation_gizmo_update(powergl_object *obj, powergl_object *cam);
void powergl_orientation_gizmo_draw(powergl_pipeline3 *ppl, powergl_object *obj);

#endif
