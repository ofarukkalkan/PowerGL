#ifndef _powergl_window_h
#define _powergl_window_h

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include "../powergl.h"
#include "../rendering/visualscene.h"


typedef struct powergl_window_t powergl_window;


struct powergl_window_t {
    powergl_visualscene *root_scene;
    SDL_Window *window;
    SDL_GLContext context;
    int width;
    int height;
};

powergl_window *powergl_window_new(powergl_visualscene *scene);
int powergl_window_create(powergl_window *, int, int);
int powergl_window_run(powergl_window *);


#endif
