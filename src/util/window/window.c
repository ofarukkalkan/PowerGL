#include "window.h"
#include "xorg/xorg.h"


powergl_util_window *powergl_util_window_new( powergl_util_app *app ) {

  powergl_util_window *wnd =  powergl_resize( NULL, sizeof( powergl_util_window_xorg ) );
  wnd->root_app = app;
  return wnd;
}

int powergl_util_window_create( powergl_util_window *wnd ) {
  powergl_util_window_xorg *xorg_wnd = ( powergl_util_window_xorg * ) wnd;
  return powergl_util_window_xorg_create( xorg_wnd );
}

int powergl_util_window_run( powergl_util_window *wnd ) {
  powergl_util_window_xorg *xorg_wnd = ( powergl_util_window_xorg * ) wnd;
  return powergl_util_window_xorg_run( xorg_wnd );
}
