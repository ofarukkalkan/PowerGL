#ifndef _powergl_util_app_h
#define _powergl_util_app_h

typedef struct powergl_util_app_t powergl_util_app;
typedef int powergl_util_app_create_func_t (void);
typedef int powergl_util_app_run_func_t (void);

struct powergl_util_app_t {

  powergl_util_app_create_func_t* create;
  powergl_util_app_run_func_t* run;
};

#endif
