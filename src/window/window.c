#include "window.h"

powergl_window *powergl_window_new_with_backend(powergl_visualscene *scene,
                                               const powergl_window_backend *backend)
{
    powergl_window *wnd = powergl_resize(NULL, 1, sizeof(*wnd));
    wnd->root_scene = scene;
    wnd->backend = backend;
    wnd->backend_data = NULL;
    wnd->width = wnd->height = 0;
    return wnd;
}

powergl_window *powergl_window_new(powergl_visualscene *scene)
{
    extern const powergl_window_backend powergl_window_backend_sdl; /* defined in window_sdl.c */
    return powergl_window_new_with_backend(scene, &powergl_window_backend_sdl);
}

int powergl_window_create(powergl_window *wnd, int width, int height)
{
    wnd->width = width;
    wnd->height = height;
    if(!wnd->backend || !wnd->backend->create)
        return 0;
    return wnd->backend->create(wnd, width, height);
}

int powergl_window_run(powergl_window *wnd)
{
    if(!wnd->backend || !wnd->backend->run)
        return 0;
    return wnd->backend->run(wnd);
}

int powergl_window_poll_event(powergl_window *wnd, powergl_event *ev)
{
    if(!wnd->backend || !wnd->backend->poll_event)
        return 0;
    return wnd->backend->poll_event(wnd, ev);
}

void powergl_window_swap_buffers(powergl_window *wnd)
{
    if(wnd->backend && wnd->backend->swap_buffers)
        wnd->backend->swap_buffers(wnd);
}

void *powergl_window_get_native_window(powergl_window *wnd)
{
    if(wnd->backend && wnd->backend->get_native_window)
        return wnd->backend->get_native_window(wnd);
    return NULL;
}
