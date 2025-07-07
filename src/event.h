#ifndef POWERGL_EVENT_H
#define POWERGL_EVENT_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    POWERGL_EVENT_NONE = 0,
    POWERGL_EVENT_KEY_DOWN,
    POWERGL_EVENT_KEY_UP,
    POWERGL_EVENT_MOUSE_MOVE,
    POWERGL_EVENT_MOUSE_BUTTON_DOWN,
    POWERGL_EVENT_MOUSE_BUTTON_UP,
    POWERGL_EVENT_WINDOW_CLOSE
} powergl_event_type;

typedef enum {
    POWERGL_KEY_UNKNOWN = 0,
    POWERGL_KEY_A,
    POWERGL_KEY_D,
    POWERGL_KEY_W,
    POWERGL_KEY_S,
    POWERGL_KEY_SPACE,
    POWERGL_KEY_LCTRL,
    POWERGL_KEY_ARROW_UP,
    POWERGL_KEY_ARROW_DOWN,
    POWERGL_KEY_ARROW_LEFT,
    POWERGL_KEY_ARROW_RIGHT
} powergl_key;

typedef enum {
    POWERGL_MOUSE_BUTTON_NONE = 0,
    POWERGL_MOUSE_BUTTON_LEFT,
    POWERGL_MOUSE_BUTTON_RIGHT,
    POWERGL_MOUSE_BUTTON_MIDDLE
} powergl_mouse_button;

typedef struct {
    powergl_event_type type;
    powergl_key key;
    powergl_mouse_button button;
    int x;
    int y;
} powergl_event;

#ifdef __cplusplus
}
#endif

#endif /* POWERGL_EVENT_H */
