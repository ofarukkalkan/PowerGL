
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include "window_sdl.h"
#include "window.h"
#include <stdio.h>
#include <string.h>

typedef struct {
    SDL_Window *window;
    SDL_GLContext context;
} sdl_backend_data;

static powergl_key translate_key(SDL_Keycode k){
    switch(k){
        case SDLK_a: return POWERGL_KEY_A;
        case SDLK_d: return POWERGL_KEY_D;
        case SDLK_w: return POWERGL_KEY_W;
        case SDLK_s: return POWERGL_KEY_S;
        case SDLK_SPACE: return POWERGL_KEY_SPACE;
        case SDLK_LCTRL: return POWERGL_KEY_LCTRL;
        case SDLK_LEFT: return POWERGL_KEY_ARROW_LEFT;
        case SDLK_RIGHT: return POWERGL_KEY_ARROW_RIGHT;
        case SDLK_UP: return POWERGL_KEY_ARROW_UP;
        case SDLK_DOWN: return POWERGL_KEY_ARROW_DOWN;
        default: return POWERGL_KEY_UNKNOWN;
    }
}

static powergl_mouse_button translate_button(Uint8 b){
    switch(b){
        case SDL_BUTTON_LEFT: return POWERGL_MOUSE_BUTTON_LEFT;
        case SDL_BUTTON_RIGHT: return POWERGL_MOUSE_BUTTON_RIGHT;
        case SDL_BUTTON_MIDDLE: return POWERGL_MOUSE_BUTTON_MIDDLE;
        default: return POWERGL_MOUSE_BUTTON_NONE;
    }
}

void powergl_sdl_translate_event(const SDL_Event *src, powergl_event *dst){
    dst->x = 0;
    dst->y = 0;
    dst->key = POWERGL_KEY_UNKNOWN;
    dst->button = POWERGL_MOUSE_BUTTON_NONE;
    switch(src->type){
        case SDL_QUIT:
            dst->type = POWERGL_EVENT_WINDOW_CLOSE;
            break;
        case SDL_KEYDOWN:
            dst->type = POWERGL_EVENT_KEY_DOWN;
            dst->key = translate_key(src->key.keysym.sym);
            break;
        case SDL_KEYUP:
            dst->type = POWERGL_EVENT_KEY_UP;
            dst->key = translate_key(src->key.keysym.sym);
            break;
        case SDL_MOUSEMOTION:
            dst->type = POWERGL_EVENT_MOUSE_MOVE;
            dst->x = src->motion.x;
            dst->y = src->motion.y;
            break;
        case SDL_MOUSEBUTTONDOWN:
            dst->type = POWERGL_EVENT_MOUSE_BUTTON_DOWN;
            dst->button = translate_button(src->button.button);
            dst->x = src->button.x;
            dst->y = src->button.y;
            break;
        case SDL_MOUSEBUTTONUP:
            dst->type = POWERGL_EVENT_MOUSE_BUTTON_UP;
            dst->button = translate_button(src->button.button);
            dst->x = src->button.x;
            dst->y = src->button.y;
            break;
        case SDL_MOUSEWHEEL:
            dst->type = POWERGL_EVENT_MOUSE_WHEEL;
            dst->x = src->wheel.x;
            dst->y = src->wheel.y;
            break;
        default:
            dst->type = POWERGL_EVENT_NONE;
            break;
    }
}

int powergl_sdl_poll_event(powergl_event *ev){
    SDL_Event e;
    if(!SDL_PollEvent(&e))
        return 0;
    powergl_sdl_translate_event(&e, ev);
    return 1;
}

/* Backend implementation */

static void errorCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
                          GLsizei length, const GLchar *message,
                          const GLvoid *userParam)
{
    fprintf(stderr, "\nSource = [ %d ] \n", (int) source);
    fprintf(stderr, "Type = [ %d ]\n", (int) type);
    fprintf(stderr, "Severity = [ %d ]\n", (int) severity);
    fprintf(stderr, "ID = [ %d ]\n", (int) id);
    fprintf(stderr, "Msg = [ %u %s ]\n", length, (const char *)message);
    (void)userParam;
}

static int gl_debug_enabled(void)
{
    const char *env = getenv("POWERGL_GL_DEBUG");
    return env && strcmp(env, "1") == 0;
}

static int sdl_create(powergl_window *wnd, int width, int height)
{
    int success = 1;
    sdl_backend_data *data = calloc(1, sizeof(*data));
    wnd->backend_data = data;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL could not initialize! SDL Error: %s\n",
                SDL_GetError());
        success = 0;
    } else {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        data->window = SDL_CreateWindow("PowerGL Engine",
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        width, height,
                                        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        if(!data->window) {
            fprintf(stderr, "Window could not be created! SDL Error: %s\n",
                    SDL_GetError());
            success = 0;
        } else {
            data->context = SDL_GL_CreateContext(data->window);
            if(!data->context) {
                fprintf(stderr, "OpenGL context could not be created! SDL Error: %s\n",
                        SDL_GetError());
                success = 0;
            } else {
                glewExperimental = GL_TRUE;
                GLenum glewError = glewInit();
                if(glewError != GLEW_OK)
                    fprintf(stderr, "Error initializing GLEW! %s\n",
                            glewGetErrorString(glewError));

                if(SDL_GL_SetSwapInterval(1) < 0)
                    fprintf(stderr, "Warning: Unable to set VSync! SDL Error: %s\n",
                            SDL_GetError());
            }
        }
    }

    return success;
}

static int sdl_poll_event(powergl_window *wnd, powergl_event *ev)
{
    (void)wnd; /* unused */
    return powergl_sdl_poll_event(ev);
}

static void sdl_swap(powergl_window *wnd)
{
    sdl_backend_data *data = (sdl_backend_data *)wnd->backend_data;
    SDL_GL_SwapWindow(data->window);
}

static int sdl_run(powergl_window *wnd)
{
    if(gl_debug_enabled()) {
        glDebugMessageCallback(errorCallback, NULL);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
        glEnable(GL_DEBUG_OUTPUT);
    }
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.3f, 0.6f, 0.9f, 1.0f);
    wnd->root_scene->create(wnd->root_scene);

    float delta_time = 0.0f;
    int quit = 0;
    powergl_event ev;
    Uint64 last_counter = SDL_GetPerformanceCounter();
    Uint64 frequency = SDL_GetPerformanceFrequency();

    while(!quit) {
        Uint64 current_counter = SDL_GetPerformanceCounter();
        delta_time = (float)(current_counter - last_counter) / (float)frequency;

        while(sdl_poll_event(wnd, &ev)) {
            wnd->root_scene->handle_events(wnd->root_scene, &ev, delta_time);
            if(ev.type == POWERGL_EVENT_WINDOW_CLOSE)
                quit = 1;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        wnd->root_scene->run(wnd->root_scene, delta_time);
        sdl_swap(wnd);
        last_counter = current_counter;
    }
    return 0;
}

static void sdl_destroy(powergl_window *wnd)
{
    sdl_backend_data *data = (sdl_backend_data *)wnd->backend_data;
    if(data) {
        if(data->context)
            SDL_GL_DeleteContext(data->context);
        if(data->window)
            SDL_DestroyWindow(data->window);
        free(data);
    }
    SDL_Quit();
}

static void *sdl_get_native_window(powergl_window *wnd)
{
    sdl_backend_data *data = (sdl_backend_data *)wnd->backend_data;
    return data ? (void*)data->window : NULL;
}

const powergl_window_backend powergl_window_backend_sdl = {
    .create = sdl_create,
    .run = sdl_run,
    .poll_event = sdl_poll_event,
    .swap_buffers = sdl_swap,
    .destroy = sdl_destroy,
    .get_native_window = sdl_get_native_window
};
