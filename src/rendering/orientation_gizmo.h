#ifndef _powergl_orientation_gizmo_h
#define _powergl_orientation_gizmo_h

#include "object.h"

/* Build an orientation gizmo with X (red), Y (green) and Z (blue) axes. */
void powergl_orientation_gizmo_create(powergl_object *obj);

/* Update gizmo's MVP so it stays in the upper-right corner and follows the
 * orientation of the given camera. */
void powergl_orientation_gizmo_update(powergl_object *obj, powergl_object *cam);

#endif
