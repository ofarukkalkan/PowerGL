#ifndef _powergl_util_window_xorg_h
#define _powergl_util_window_xorg_h

#define GL_GLEXT_PROTOTYPES
#define GLX_GLXEXT_PROTOTYPES

#include "../window.h"


#include <GL/glx.h>
#include <GL/glxext.h>

typedef struct powergl_util_window_xorg_t powergl_util_window_xorg;

struct powergl_util_window_xorg_t {
  powergl_util_window_create_func_t* create;
  Display * display;
  int screenid;
  GLXFBConfig fbconfig;
  Colormap colormap;
  Window window;
  GLXContext context;
};

powergl_util_window_xorg* powergl_util_window_xorg_create(void);

#endif
