#ifndef _powergl_util_window_xorg_h
#define _powergl_util_window_xorg_h

#define GL_GLEXT_PROTOTYPES
#define GLX_GLXEXT_PROTOTYPES

#include "../window.h"

#include <GL/glx.h>
#include <GL/glxext.h>

typedef struct powergl_util_window_xorg_t powergl_util_window_xorg;

struct powergl_util_window_xorg_t {
  powergl_util_window _base;
  Display * display;
  int screenid;
  GLXFBConfig fbconfig;
  Colormap colormap;
  Window window;
  GLXContext context;
};

// global functions
int powergl_util_window_xorg_check_init(void);
int powergl_util_window_xorg_init(void);
int powergl_util_window_xorg_finish(void);
powergl_util_window_xorg* powergl_util_window_xorg_new(void);
int powergl_util_window_xorg_delete(void);
int powergl_util_window_xorg_delete_all(void);
int powergl_util_window_xorg_set_index(size_t);
size_t powergl_util_window_xorg_get_index();
powergl_util_window_xorg* powergl_util_window_xorg_get_ptr();

// global functions for per instance
int powergl_util_window_xorg_create(void);
int powergl_util_window_xorg_run(void);

#endif
