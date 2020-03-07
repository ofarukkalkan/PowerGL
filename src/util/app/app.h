#ifndef _powergl_util_app_h
#define _powergl_util_app_h

#include <stddef.h>
#include <SDL2/SDL.h>
#include "../../powergl.h"
#include "../../rendering/visualscene.h"

typedef struct powergl_util_app_t powergl_util_app;

typedef void powergl_create_app_func(powergl_util_app *);
typedef void powergl_run_app_func(powergl_util_app *,float);
typedef void powergl_handle_events_app_func(powergl_util_app *, SDL_Event *e);

struct powergl_util_app_t
{

    // visual scene
    powergl_rendering_visualscene *scene;

    // virtual functions
    powergl_run_app_func *run;
    powergl_create_app_func *create;
    powergl_handle_events_app_func *handle_events;
};

int powergl_util_app_create( powergl_util_app * );
int powergl_util_app_run( powergl_util_app *, float);
void powergl_util_app_handle_events( powergl_util_app *, SDL_Event *);
const char *powergl_util_app_get_name( powergl_util_app * );


#endif
