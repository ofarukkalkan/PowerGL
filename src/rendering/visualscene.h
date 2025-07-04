#ifndef _powergl_visualscene_h
#define _powergl_visualscene_h

#include <stddef.h>
#include "../event.h"
#include "object.h"
#include "pipeline.h"

typedef struct powergl_visualscene_t powergl_visualscene;

typedef void (*fpcreate_visualscene)(powergl_visualscene *);
typedef void (*fprun_visualscene)(powergl_visualscene *, float);
typedef void (*fphandle_events_visualscene)(powergl_visualscene *, powergl_event *e, float);

struct powergl_visualscene_t {

  // objects
  powergl_object **objects;
  size_t n_object;

  // default camera object
  powergl_object *main_camera;

  // default light object
  powergl_object *main_light;

  // pipeline
  powergl_pipeline pipeline;
  powergl_pipeline2 pipeline2;
  powergl_pipeline3 pipeline3;
  powergl_pipeline4 pipeline4;

  /* interaction state */
  powergl_object *hovered_object;
  powergl_object *selected_object;

  fprun_visualscene run;
  fpcreate_visualscene create;
  fphandle_events_visualscene handle_events;

};

void powergl_scene_build(powergl_visualscene *, const char *);
powergl_object *powergl_scene_find(powergl_visualscene *, const char *);
powergl_object *powergl_scene_pick(powergl_visualscene *, powergl_object *cam,
                                   powergl_vec2 mouse,
                                   powergl_vec4 viewport,
                                   float *out_dist);
void powergl_scene_handle_picking(powergl_visualscene *, powergl_event *e);

#endif
