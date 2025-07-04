#ifndef _powergl_headless_h
#define _powergl_headless_h

#include <EGL/egl.h>
#include "../powergl.h"
#include "../rendering/visualscene.h"
#include "backend.h"

typedef struct powergl_headless_t powergl_headless;

struct powergl_headless_t {
    powergl_visualscene *root_scene;
    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;
    int width;
    int height;
};

powergl_headless *powergl_headless_new(powergl_visualscene *scene);
int powergl_headless_create(powergl_headless *h, int width, int height);
int powergl_headless_run(powergl_headless *h);

extern const powergl_window_backend powergl_window_backend_headless;

#endif
