#include "window.h"
#include "xorg/xorg.h"

powergl_util_window* powergl_util_window_new(void){
  powergl_util_window* w;
  w = (powergl_util_window*) powergl_util_window_xorg_new();
  return w;
}
