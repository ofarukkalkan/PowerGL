#ifndef _powergl_objectlibrary_h
#define _powergl_objectlibrary_h

#include "object.h"

typedef struct {
  powergl_object **objects;
  size_t n_object;

} powergl_object_library;

void powergl_object_library_build(powergl_object_library *lib, const char *file);

#endif
