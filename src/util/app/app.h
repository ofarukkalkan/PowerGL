#ifndef _powergl_util_app_h
#define _powergl_util_app_h

#include <stddef.h>
#include "../../powergl.h"

typedef struct powergl_util_app_t powergl_util_app;
typedef int powergl_util_app_create_func_t (void);
typedef int powergl_util_app_run_func_t (void);
typedef const char* powergl_util_app_get_name_func_t (void);

struct powergl_util_app_t {

  powergl_util_app_create_func_t* create;
  powergl_util_app_run_func_t* run;
  powergl_util_app_get_name_func_t* get_name;
};

int powergl_util_app_check_init(void);
int powergl_util_app_init(void);
int powergl_util_app_finish(void);
powergl_util_app* powergl_util_app_new(const char*);
int powergl_util_app_delete(void);
int powergl_util_app_delete_all(void);
int powergl_util_app_set_index(size_t);
size_t powergl_util_app_get_index();
powergl_util_app* powergl_util_app_get_ptr();
powergl_util_app* powergl_util_app_find(const char*);

#endif
