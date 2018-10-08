#include "app.h"

int powergl_util_app_create( powergl_util_app *app ) {

  app->create(app);

}

int powergl_util_app_run( powergl_util_app *app ) {

  app->run(app);

}
