#ifndef _powergl_objectlibrary_h
#define _powergl_objectlibrary_h

#include "object.h"

typedef struct {
  powergl_object **objects;
  size_t n_object;

} powergl_object_library;

powergl_object_library * powergl_object_library_build(const char *file);
powergl_object * powergl_object_library_copy_object(powergl_object_library *, const char *id);

powergl_object * powergl_object_library_find_object(powergl_object_library *lib, const char *id);

#endif
