#ifndef _powergl_rendering_visualscene_h
#define _powergl_rendering_visualscene_h

#include <stddef.h>
#include "object.h"
#include "pipeline.h"

typedef struct powergl_rendering_visualscene_t powergl_rendering_visualscene;

typedef void powergl_create_visualscene_func(powergl_rendering_visualscene *);
typedef void powergl_run_visualscene_func(powergl_rendering_visualscene *);

struct powergl_rendering_visualscene_t {

  // objects
  powergl_rendering_object **objects;
  size_t n_object;

  // default camera object
  powergl_rendering_object *main_camera;

  // default light object 
  powergl_rendering_object *main_light;

  // pipeline
  powergl_rendering_pipeline pipeline;

  powergl_run_visualscene_func *run;
  powergl_create_visualscene_func *create;

};

void powergl_rendering_visualscene_build_from_dae( powergl_rendering_visualscene *, const char * );


#endif
