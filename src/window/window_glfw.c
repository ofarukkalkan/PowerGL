#include "window.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    GLFWwindow *window;
    int has_event;
    powergl_event event;
} glfw_backend_data;

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    powergl_window *wnd = glfwGetWindowUserPointer(window);
    if(!wnd) return;
    glfw_backend_data *data = wnd->backend_handle;
    if(!data) return;

    data->has_event = 1;
    data->event.key = POWERGL_KEY_UNKNOWN;
    switch(key) {
    case GLFW_KEY_A: data->event.key = POWERGL_KEY_A; break;
    case GLFW_KEY_D: data->event.key = POWERGL_KEY_D; break;
    case GLFW_KEY_W: data->event.key = POWERGL_KEY_W; break;
    case GLFW_KEY_S: data->event.key = POWERGL_KEY_S; break;
    case GLFW_KEY_SPACE: data->event.key = POWERGL_KEY_SPACE; break;
    case GLFW_KEY_LEFT_CONTROL: data->event.key = POWERGL_KEY_LEFT_CTRL; break;
    default: break;
    }
    if(action == GLFW_PRESS)
        data->event.type = POWERGL_EVENT_KEY_DOWN;
    else if(action == GLFW_RELEASE)
        data->event.type = POWERGL_EVENT_KEY_UP;
    else
        data->event.type = POWERGL_EVENT_NONE;
}


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

    glfwSetWindowUserPointer(win, wnd);
    glfwSetKeyCallback(win, key_callback);

    glfwMakeContextCurrent(win);
    if(glewInit() != GLEW_OK)
        fprintf(stderr, "Failed to init GLEW\n");

    glfwSwapInterval(1);

    glfw_backend_data *data = calloc(1, sizeof(*data));
    data->window = win;
    data->has_event = 0;
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

static int glfw_poll_event(powergl_window *wnd, powergl_event *e)
{
    glfw_backend_data *data = wnd->backend_handle;
    if(data->has_event) {
        *e = data->event;
        data->has_event = 0;
        return 1;
    }
    glfwPollEvents();
    if(glfwWindowShouldClose(data->window)) {
        e->type = POWERGL_EVENT_QUIT;
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
