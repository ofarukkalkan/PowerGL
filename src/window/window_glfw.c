#include "window_glfw.h"
#ifdef POWERGL_USE_GLFW
#include <GLFW/glfw3.h>
#endif

#ifdef POWERGL_USE_GLFW
static powergl_key translate_key(int key){
    switch(key){
        case GLFW_KEY_A: return POWERGL_KEY_A;
        case GLFW_KEY_D: return POWERGL_KEY_D;
        case GLFW_KEY_W: return POWERGL_KEY_W;
        case GLFW_KEY_S: return POWERGL_KEY_S;
        case GLFW_KEY_SPACE: return POWERGL_KEY_SPACE;
        case GLFW_KEY_LEFT_CONTROL: return POWERGL_KEY_LCTRL;
        default: return POWERGL_KEY_UNKNOWN;
    }
}

static powergl_mouse_button translate_button(int button){
    switch(button){
        case GLFW_MOUSE_BUTTON_LEFT: return POWERGL_MOUSE_BUTTON_LEFT;
        case GLFW_MOUSE_BUTTON_RIGHT: return POWERGL_MOUSE_BUTTON_RIGHT;
        case GLFW_MOUSE_BUTTON_MIDDLE: return POWERGL_MOUSE_BUTTON_MIDDLE;
        default: return POWERGL_MOUSE_BUTTON_NONE;
    }
}

void powergl_glfw_translate_key(powergl_event *dst, int key, int action){
    dst->key = translate_key(key);
    if(action == GLFW_PRESS)
        dst->type = POWERGL_EVENT_KEY_DOWN;
    else if(action == GLFW_RELEASE)
        dst->type = POWERGL_EVENT_KEY_UP;
    else
        dst->type = POWERGL_EVENT_NONE;
}

void powergl_glfw_translate_button(powergl_event *dst, int button, int action, int x, int y){
    dst->button = translate_button(button);
    dst->x = x;
    dst->y = y;
    if(action == GLFW_PRESS)
        dst->type = POWERGL_EVENT_MOUSE_BUTTON_DOWN;
    else if(action == GLFW_RELEASE)
        dst->type = POWERGL_EVENT_MOUSE_BUTTON_UP;
    else
        dst->type = POWERGL_EVENT_NONE;
}

void powergl_glfw_translate_cursor(powergl_event *dst, int x, int y){
    dst->type = POWERGL_EVENT_MOUSE_MOVE;
    dst->x = x;
    dst->y = y;
}

#endif /* POWERGL_USE_GLFW */
