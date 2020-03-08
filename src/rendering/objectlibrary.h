#ifndef _powergl_objectlibrary_h
#define _powergl_objectlibrary_h

#include "object.h"

typedef struct
{
    powergl_object **objects;
    size_t n_object;
    char *dae_file;
} powergl_objectlibrary;

void powergl_build_lib_from_dae(powergl_objectlibrary *lib, const char *dae);

#endif
