#ifndef _powergl_window_h
#define _powergl_window_h

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include "../powergl.h"
#include "../rendering/visualscene.h"

typedef struct window_backend_t window_backend;


typedef struct powergl_window_t powergl_window;


struct window_backend_t {
    int (*backend_create)(powergl_window *, int, int);
    void (*backend_destroy)(powergl_window *);
    int (*backend_poll_event)(powergl_window *, SDL_Event *);
    void (*backend_swap)(powergl_window *);
};

struct powergl_window_t {
    powergl_visualscene *root_scene;
    const window_backend *backend;
    void *backend_handle;
    int width;
    int height;
};

#ifdef POWERGL_BACKEND_SDL
extern const window_backend powergl_sdl_backend;
#endif
#ifdef POWERGL_BACKEND_GLFW
extern const window_backend powergl_glfw_backend;
#endif

SDL_Window *powergl_window_get_sdl_window(powergl_window *);

powergl_window *powergl_window_new(powergl_visualscene *scene);
int powergl_window_create(powergl_window *, int, int);
void powergl_window_destroy(powergl_window *);
int powergl_window_run(powergl_window *);


#endif
