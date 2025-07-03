#include "window.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    GLFWwindow *window;
} glfw_backend_data;

static int glfw_create(powergl_window *wnd, int width, int height)
{
    if(!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return 0;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *win = glfwCreateWindow(width, height, "PowerGL Engine", NULL, NULL);
    if(!win) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return 0;
    }

    glfwMakeContextCurrent(win);
    if(glewInit() != GLEW_OK)
        fprintf(stderr, "Failed to init GLEW\n");

    glfwSwapInterval(1);

    glfw_backend_data *data = calloc(1, sizeof(*data));
    data->window = win;
    wnd->backend_handle = data;
    return 1;
}

static void glfw_destroy(powergl_window *wnd)
{
    glfw_backend_data *data = wnd->backend_handle;
    if(!data)
        return;
    glfwDestroyWindow(data->window);
    glfwTerminate();
    free(data);
    wnd->backend_handle = NULL;
}

static int glfw_poll_event(powergl_window *wnd, SDL_Event *e)
{
    glfw_backend_data *data = wnd->backend_handle;
    (void)data;
    glfwPollEvents();
    if(glfwWindowShouldClose(data->window)) {
        e->type = SDL_QUIT;
        glfwSetWindowShouldClose(data->window, GLFW_FALSE);
        return 1;
    }
    return 0;
}

static void glfw_swap(powergl_window *wnd)
{
    glfw_backend_data *data = wnd->backend_handle;
    glfwSwapBuffers(data->window);
}

const window_backend powergl_glfw_backend = {
    glfw_create,
    glfw_destroy,
    glfw_poll_event,
    glfw_swap
};
