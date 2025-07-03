#ifndef POWERGL_EVENT_H
#define POWERGL_EVENT_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    POWERGL_EVENT_NONE = 0,
    POWERGL_EVENT_QUIT,
    POWERGL_EVENT_KEY_DOWN,
    POWERGL_EVENT_KEY_UP
} powergl_event_type;

typedef enum {
    POWERGL_KEY_UNKNOWN = 0,
    POWERGL_KEY_A,
    POWERGL_KEY_D,
    POWERGL_KEY_W,
    POWERGL_KEY_S,
    POWERGL_KEY_SPACE,
    POWERGL_KEY_LEFT_CTRL
} powergl_keycode;

typedef struct powergl_event_t {
    powergl_event_type type;
    powergl_keycode key;
    int x;
    int y;
} powergl_event;

#ifdef __cplusplus
}
#endif

#endif /* POWERGL_EVENT_H */
