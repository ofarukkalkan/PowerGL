#include "window.h"
#include <stdio.h>
#include <string.h>

typedef struct {
    SDL_Window *window;
    SDL_GLContext context;
} sdl_backend_data;

static int sdl_create(powergl_window *wnd, int width, int height)
{
    sdl_backend_data *data = calloc(1, sizeof(*data));
    wnd->backend_handle = data;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return 0;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    data->window = SDL_CreateWindow("PowerGL Engine", SDL_WINDOWPOS_UNDEFINED,
                                     SDL_WINDOWPOS_UNDEFINED, width, height,
                                     SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if(!data->window) {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return 0;
    }

    data->context = SDL_GL_CreateContext(data->window);
    if(!data->context) {
        printf("OpenGL context could not be created! SDL Error: %s\n",
               SDL_GetError());
        return 0;
    }

    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if(glewError != GLEW_OK)
        printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));

    if(SDL_GL_SetSwapInterval(1) < 0)
        printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());

    return 1;
}

static void sdl_destroy(powergl_window *wnd)
{
    sdl_backend_data *data = wnd->backend_handle;
    if(!data)
        return;
    SDL_GL_DeleteContext(data->context);
    SDL_DestroyWindow(data->window);
    SDL_Quit();
    free(data);
    wnd->backend_handle = NULL;
}

static int sdl_poll_event(powergl_window *wnd, SDL_Event *e)
{
    (void)wnd;
    return SDL_PollEvent(e);
}

static void sdl_swap(powergl_window *wnd)
{
    sdl_backend_data *data = wnd->backend_handle;
    SDL_GL_SwapWindow(data->window);
}

SDL_Window *powergl_window_get_sdl_window(powergl_window *wnd)
{
    sdl_backend_data *data = wnd->backend_handle;
    return data ? data->window : NULL;
}

const window_backend powergl_sdl_backend = {
    sdl_create,
    sdl_destroy,
    sdl_poll_event,
    sdl_swap
};
