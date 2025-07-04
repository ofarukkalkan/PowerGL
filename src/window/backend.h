#ifndef POWERGL_WINDOW_BACKEND_H
#define POWERGL_WINDOW_BACKEND_H

#include "../event.h"

struct powergl_window_t;

typedef struct powergl_window_backend {
    int (*create)(struct powergl_window_t *wnd, int width, int height);
    int (*run)(struct powergl_window_t *wnd);
    int (*poll_event)(struct powergl_window_t *wnd, powergl_event *ev);
    void (*swap_buffers)(struct powergl_window_t *wnd);
    void (*destroy)(struct powergl_window_t *wnd);
    void *(*get_native_window)(struct powergl_window_t *wnd);
} powergl_window_backend;

#endif /* POWERGL_WINDOW_BACKEND_H */
