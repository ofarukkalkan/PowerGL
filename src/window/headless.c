#include "headless.h"
#include "window.h"
#include <string.h>
#include <stdio.h>
#include <SDL2/SDL_opengl.h>

static const EGLint configAttribs[] = {
    EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
    EGL_BLUE_SIZE, 8,
    EGL_GREEN_SIZE, 8,
    EGL_RED_SIZE, 8,
    EGL_ALPHA_SIZE, 8,
    EGL_DEPTH_SIZE, 8,
    EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
    EGL_NONE
};

typedef powergl_headless headless_backend_data;

powergl_headless *powergl_headless_new(powergl_visualscene *scene){
    powergl_headless *h = calloc(1, sizeof(*h));
    h->root_scene = scene;
    return h;
}

int powergl_headless_create(powergl_headless *h, int width, int height){
    h->width = width;
    h->height = height;

    h->display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if(h->display == EGL_NO_DISPLAY){
        fprintf(stderr, "Failed to get EGL display\n");
        return 0;
    }

    if(!eglInitialize(h->display, NULL, NULL)){
        fprintf(stderr, "Failed to initialize EGL\n");
        return 0;
    }

    EGLint numConfigs;
    EGLConfig eglCfg;
    if(!eglChooseConfig(h->display, configAttribs, &eglCfg, 1, &numConfigs)){
        fprintf(stderr, "Failed to choose EGL config\n");
        return 0;
    }

    const EGLint pbufferAttribs[] = {
        EGL_WIDTH, width,
        EGL_HEIGHT, height,
        EGL_NONE,
    };

    h->surface = eglCreatePbufferSurface(h->display, eglCfg, pbufferAttribs);
    if(h->surface == EGL_NO_SURFACE){
        fprintf(stderr, "Failed to create EGL surface\n");
        return 0;
    }

    if(!eglBindAPI(EGL_OPENGL_API)){
        fprintf(stderr, "Failed to bind OpenGL API\n");
        return 0;
    }

    const EGLint ctxAttribs[] = {
        EGL_CONTEXT_MAJOR_VERSION, 3,
        EGL_CONTEXT_MINOR_VERSION, 3,
        EGL_CONTEXT_OPENGL_PROFILE_MASK, EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT,
        EGL_NONE
    };
    h->context = eglCreateContext(h->display, eglCfg, EGL_NO_CONTEXT, ctxAttribs);
    if(h->context == EGL_NO_CONTEXT){
        fprintf(stderr, "Failed to create EGL context\n");
        return 0;
    }

    if(!eglMakeCurrent(h->display, h->surface, h->surface, h->context)){
        fprintf(stderr, "Failed to make EGL context current\n");
        return 0;
    }

    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
    glClearColor(76.0f/255.0f, 153.0f/255.0f, 229.0f/255.0f, 1.0f);

    return 1;
}

int powergl_headless_run(powergl_headless *h){
    if(h->root_scene){
        h->root_scene->create(h->root_scene);
        for(int i = 0; i < 10; ++i){
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            h->root_scene->run(h->root_scene, 1.0f/60.0f);
        }
    }
    eglSwapBuffers(h->display, h->surface);
    eglMakeCurrent(h->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglDestroySurface(h->display, h->surface);
    eglDestroyContext(h->display, h->context);
    eglTerminate(h->display);
    return 0;
}

/* Backend interface implementation */
static int headless_create(powergl_window *wnd, int width, int height)
{
    headless_backend_data *h = calloc(1, sizeof(*h));
    wnd->backend_data = h;
    h->root_scene = wnd->root_scene;
    return powergl_headless_create(h, width, height);
}

static int headless_run(powergl_window *wnd)
{
    headless_backend_data *h = (headless_backend_data *)wnd->backend_data;
    return powergl_headless_run(h);
}

static int headless_poll_event(powergl_window *wnd, powergl_event *ev)
{
    (void)wnd; (void)ev;
    return 0;
}

static void headless_swap(powergl_window *wnd)
{
    headless_backend_data *h = (headless_backend_data *)wnd->backend_data;
    eglSwapBuffers(h->display, h->surface);
}

static void headless_destroy(powergl_window *wnd)
{
    headless_backend_data *h = (headless_backend_data *)wnd->backend_data;
    if(!h)
        return;
    eglMakeCurrent(h->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglDestroySurface(h->display, h->surface);
    eglDestroyContext(h->display, h->context);
    eglTerminate(h->display);
    free(h);
}

static void *headless_get_native_window(powergl_window *wnd)
{
    (void)wnd;
    return NULL;
}

const powergl_window_backend powergl_window_backend_headless = {
    .create = headless_create,
    .run = headless_run,
    .poll_event = headless_poll_event,
    .swap_buffers = headless_swap,
    .destroy = headless_destroy,
    .get_native_window = headless_get_native_window
};

