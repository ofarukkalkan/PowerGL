#ifndef _powergl_util_app_appmanager_h
#define _powergl_util_app_appmanager_h

#include "../app.h"

typedef struct powergl_util_app_appmanager_t powergl_util_app_appmanager;

struct powergl_util_app_appmanager_t {
  powergl_util_app _base;
  powergl_util_app apps;
  size_t n_app;
};

powergl_util_app_appmanager* powergl_util_app_appmanager_new(void);

#endif
