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
int powergl_util_window_check_init(void);
int powergl_util_window_init(void);
int powergl_util_window_finish(void);
const powergl_util_window* powergl_util_window_new(void);
int powergl_util_window_delete(void);
int powergl_util_window_delete_all(void);
int powergl_util_window_set_index(size_t);
size_t powergl_util_window_get_index();
const powergl_util_window* powergl_util_window_get_ptr();

#endif
