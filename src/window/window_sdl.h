#ifndef POWERGL_WINDOW_SDL_H
#define POWERGL_WINDOW_SDL_H

#include "../event.h"

typedef union SDL_Event SDL_Event;

void powergl_sdl_translate_event(const SDL_Event *src, powergl_event *dst);
int powergl_sdl_poll_event(powergl_event *ev);

#endif
