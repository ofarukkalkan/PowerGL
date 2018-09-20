#include "app.h"

int powergl_util_app_create( powergl_util_app * app ) {
	
	powergl_rendering_visualscene_create( &app->scene , "/home/omerfaruk/Desktop/importtest.dae" );
	
}

int powergl_util_app_run( powergl_util_app * app ) {

	powergl_rendering_visualscene_run( &app->scene );
	
}
