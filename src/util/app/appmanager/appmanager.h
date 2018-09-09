#ifndef _powergl_util_app_appmanager_h
#define _powergl_util_app_appmanager_h

#include "../app.h"

typedef struct powergl_util_app_appmanager_t powergl_util_app_appmanager;

struct powergl_util_app_appmanager_t {
  powergl_util_app _base;
  powergl_util_app apps;
  size_t n_app;
};

int powergl_util_app_appmanager_check_init(void);
int powergl_util_app_appmanager_init(void);
int powergl_util_app_appmanager_finish(void);
powergl_util_app_appmanager* powergl_util_app_appmanager_new(void);
int powergl_util_app_appmanager_delete(void);
int powergl_util_app_appmanager_delete_all(void);
int powergl_util_app_appmanager_set_index(size_t);
size_t powergl_util_app_appmanager_get_index();
powergl_util_app_appmanager* powergl_util_app_appmanager_get_ptr();

#endif
