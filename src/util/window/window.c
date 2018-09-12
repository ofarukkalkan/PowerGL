#include "window.h"
#include "xorg/xorg.h"

int powergl_util_window_check_init(void){
  return powergl_util_window_xorg_check_init();
}

int powergl_util_window_init(void){
  return powergl_util_window_xorg_init();
}

int powergl_util_window_finish(void){
  return powergl_util_window_xorg_finish();
}

const powergl_util_window* powergl_util_window_new(powergl_util_app *root_app){
  powergl_util_window* wnd = (powergl_util_window*)(powergl_util_window_xorg_new(root_app));
  return wnd;
}

int powergl_util_window_delete(void){
  return powergl_util_window_xorg_delete();
}

int powergl_util_window_delete_all(void){
  return powergl_util_window_xorg_delete_all();
}

int powergl_util_window_set_index(size_t i){
  return powergl_util_window_xorg_set_index(i);
}

size_t powergl_util_window_get_index(){
  return powergl_util_window_xorg_get_index();
}

const powergl_util_window* powergl_util_window_get_ptr(){
  return (const powergl_util_window*) powergl_util_window_xorg_get_ptr();
}
