#ifndef _powergl_rendering_objectlibrary_h
#define _powergl_rendering_objectlibrary_h

#include "object.h"

typedef struct
{
    powergl_rendering_object **objects;
    size_t n_object;
    char *dae_file;
} powergl_objectlibrary;

void powergl_build_lib_from_dae(powergl_objectlibrary *lib, const char *dae);
powergl_rendering_object * powergl_new_object_from_lib(powergl_objectlibrary *lib,const char *id);
powergl_rendering_geometry * powergl_get_geometry_from_lib(powergl_objectlibrary *lib, const char *id, size_t geo_index);

#endif
