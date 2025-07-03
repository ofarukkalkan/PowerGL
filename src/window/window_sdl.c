#include "window_sdl.h"
#include <SDL2/SDL.h>

static powergl_key translate_key(SDL_Keycode k){
    switch(k){
        case SDLK_a: return POWERGL_KEY_A;
        case SDLK_d: return POWERGL_KEY_D;
        case SDLK_w: return POWERGL_KEY_W;
        case SDLK_s: return POWERGL_KEY_S;
        case SDLK_SPACE: return POWERGL_KEY_SPACE;
        case SDLK_LCTRL: return POWERGL_KEY_LCTRL;
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
