#ifndef _powergl_util_window_h
#define _powergl_util_window_h

#include "../../powergl.h"

typedef struct powergl_util_window_t powergl_util_window;
typedef int powergl_util_window_create_func_t (void);
typedef int powergl_util_window_run_func_t (void);

struct powergl_util_window_t {
  
  powergl_util_window_create_func_t* create;
  powergl_util_window_run_func_t* run;
};

// global functions
const powergl_util_window* powergl_util_window_new(void);


#endif
