#ifndef _powergl_util_app_h
#define _powergl_util_app_h

#include <stddef.h>
#include "../../powergl.h"
#include "../../rendering/visualscene.h"

typedef struct powergl_util_app_t powergl_util_app;
typedef int powergl_util_app_create_func_t (void);
typedef int powergl_util_app_run_func_t (void);
typedef const char* powergl_util_app_get_name_func_t (void);

struct powergl_util_app_t {

  powergl_util_app_create_func_t* create;
  powergl_util_app_run_func_t* run;
  powergl_util_app_get_name_func_t* get_name;

  // visual scenes
  powergl_rendering_visualscene **scenes;
  size_t n_scene;
};


#endif
