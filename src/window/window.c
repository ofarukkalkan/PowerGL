#include "window.h"
#include <stdio.h>
#include <time.h>
#include <string.h>

enum msgSource {
    SOURCE_API = 0x8246,
    SOURCE_SYSTEM = 0x8247,
    SOURCE_SHADER_COMPILER = 0x8248,
    SOURCE_THIRD_PARTY = 0x8249,
    SOURCE_APPLICATION = 0x824A,
    SOURCE_OTHER = 0x824B,
};

enum msgType {
    TYPE_ERROR = 0x824C,
    TYPE_DEPRECATED_BEHAVIOR = 0x824D,
    TYPE_UNDEFINED_BEHAVIOR = 0x824E,
    TYPE_PORTABILITY = 0x824F,
    TYPE_PERFORMANCE = 0x8250,
    TYPE_OTHER = 0x8251,
    TYPE_MARKER = 0x8268,
    TYPE_PUSH_GROUP = 0x8269,
    TYPE_POP_GROUP = 0x826A,
};

enum msgSeverity {
    SEVERITY_HIGH = 0x9146,
    SEVERITY_MEDIUM = 0x9147,
    SEVERITY_LOW = 0x9148,
    SEVERITY_NOTIFICATION = 0x826B,
};

static void errorCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
                          GLsizei length, const GLchar *message, const GLvoid *userParam)
{
    fprintf(stderr, "\nSource = [ %d ] \n", (int)source);
    fprintf(stderr, "Type = [ %d ]\n", (int)type);
    fprintf(stderr, "Severity = [ %d ]\n", (int)severity);
    fprintf(stderr, "ID = [ %d ]\n", (int)id);
    fprintf(stderr, "Msg = [ %u %s ]\n", length, (const char *)message);
    (void)userParam;
}

static int gl_debug_enabled(void)
{
    const char *env = getenv("POWERGL_GL_DEBUG");
    return env && strcmp(env, "1") == 0;
}

powergl_window *powergl_window_new(powergl_visualscene *scene)
{
    powergl_window *wnd = powergl_resize(NULL, 1, sizeof(*wnd));
    wnd->root_scene = scene;
#ifdef POWERGL_BACKEND_GLFW
    wnd->backend = &powergl_glfw_backend;
#else
    wnd->backend = &powergl_sdl_backend;
#endif
    wnd->backend_handle = NULL;
    wnd->width = 0;
    wnd->height = 0;
    return wnd;
}

int powergl_window_create(powergl_window *wnd, int width, int height)
{
    wnd->width = width;
    wnd->height = height;
    return wnd->backend->backend_create(wnd, width, height);
}

void powergl_window_destroy(powergl_window *wnd)
{
    if(wnd && wnd->backend && wnd->backend->backend_destroy)
        wnd->backend->backend_destroy(wnd);
}

int powergl_window_run(powergl_window *wnd)
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
    SDL_Event e;

    Uint64 last_counter = SDL_GetPerformanceCounter();
    Uint64 frequency = SDL_GetPerformanceFrequency();

    while(!quit) {
        Uint64 current_counter = SDL_GetPerformanceCounter();
        delta_time = (float)(current_counter - last_counter) / (float)frequency;

        while(wnd->backend->backend_poll_event(wnd, &e)) {
            wnd->root_scene->handle_events(wnd->root_scene, &e, delta_time);
            if(e.type == SDL_QUIT)
                quit = 1;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        wnd->root_scene->run(wnd->root_scene, delta_time);
        wnd->backend->backend_swap(wnd);
        last_counter = current_counter;
    }

    return 0;
}
