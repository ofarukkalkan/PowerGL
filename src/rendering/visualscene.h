#ifndef _powergl_rendering_visualscene_h
#define _powergl_rendering_visualscene_h

#include <stddef.h>
#include "pipeline.h"


typedef struct powergl_rendering_visualscene_t powergl_rendering_visualscene;
typedef int powergl_rendering_visualscene_create_func_t (void);
typedef int powergl_rendering_visualscene_run_func_t (void);


struct powergl_rendering_visualscene_t {

  powergl_rendering_visualscene_create_func_t* create;
  powergl_rendering_visualscene_run_func_t* run;

  // pipelines
  powergl_rendering_pipeline *pipelines;
  size_t n_pipeline;
};

void powergl_rendering_visualscene_build_from_dae(powergl_asset_collada_visual_scene *);


#endif
