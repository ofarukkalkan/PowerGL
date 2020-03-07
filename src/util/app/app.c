#include "app.h"

int powergl_util_app_create( powergl_util_app *app )
{
    app->create(app);
}

int powergl_util_app_run( powergl_util_app *app, float delta_time)
{
    app->run(app, delta_time);
}


void powergl_util_app_handle_events( powergl_util_app *app, SDL_Event *e)
{
    app->handle_events(app, e);
}
