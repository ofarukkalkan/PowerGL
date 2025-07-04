#ifndef _powergl_window_h
#define _powergl_window_h


#include "../powergl.h"
#include "../rendering/visualscene.h"
#include "backend.h"


typedef struct powergl_window_t powergl_window;

struct powergl_window_t {
    powergl_visualscene *root_scene;
    const powergl_window_backend *backend;
    void *backend_data;
    int width;
    int height;
};

powergl_window *powergl_window_new(powergl_visualscene *scene);
powergl_window *powergl_window_new_with_backend(powergl_visualscene *scene,
                                               const powergl_window_backend *backend);
int powergl_window_create(powergl_window *, int, int);
int powergl_window_run(powergl_window *);
int powergl_window_poll_event(powergl_window *, powergl_event *ev);
void powergl_window_swap_buffers(powergl_window *);
void *powergl_window_get_native_window(powergl_window *);


#endif
