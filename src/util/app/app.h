#ifndef _powergl_util_app_h
#define _powergl_util_app_h

#include <stddef.h>
#include "../../powergl.h"
#include "../../rendering/visualscene.h"

typedef struct powergl_util_app_t powergl_util_app;

struct powergl_util_app_t {

  // visual scene
  powergl_rendering_visualscene scene;
};

int powergl_util_app_create( powergl_util_app * );
int powergl_util_app_run( powergl_util_app * );
const char *powergl_util_app_get_name( powergl_util_app * );


#endif
