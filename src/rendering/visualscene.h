#ifndef _powergl_visualscene_h
#define _powergl_visualscene_h

#include <stddef.h>
#include <SDL2/SDL.h>
#include "object.h"
#include "pipeline.h"

typedef struct powergl_visualscene_t powergl_visualscene;

typedef void (*fpcreate_visualscene)(powergl_visualscene *);
typedef void (*fprun_visualscene)(powergl_visualscene *, float);
typedef void (*fphandle_events_visualscene)(powergl_visualscene *, SDL_Event *e, float);

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

    fprun_visualscene run;
    fpcreate_visualscene create;
    fphandle_events_visualscene handle_events;

};

void powergl_scene_build(powergl_visualscene *, const char *);
powergl_object *powergl_scene_find(powergl_visualscene *, const char *);

#endif
