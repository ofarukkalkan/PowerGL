#ifndef POWERGL_WINDOW_GLFW_H
#define POWERGL_WINDOW_GLFW_H

#include "../event.h"

#ifdef POWERGL_USE_GLFW
void powergl_glfw_translate_key(powergl_event *dst, int key, int action);
void powergl_glfw_translate_button(powergl_event *dst, int button, int action, int x, int y);
void powergl_glfw_translate_cursor(powergl_event *dst, int x, int y);
#endif

#endif
