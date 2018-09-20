#ifndef _powergl_rendering_visualscene_h
#define _powergl_rendering_visualscene_h

#include <stddef.h>
#include "object.h"
#include "pipeline.h"

typedef struct powergl_rendering_visualscene_t powergl_rendering_visualscene;

struct powergl_rendering_visualscene_t {

  // objects
  powergl_rendering_object **objects;
  size_t n_object;

  // default camera object index
  int i_camera;

  // pipeline
  powergl_rendering_pipeline pipeline;

};

int powergl_rendering_visualscene_create( powergl_rendering_visualscene *, const char * );
int powergl_rendering_visualscene_run( powergl_rendering_visualscene * );
void powergl_rendering_visualscene_build_from_dae( powergl_rendering_visualscene *, const char * );


#endif
