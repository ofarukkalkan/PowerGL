#include "window.h"
#include "xorg/xorg.h"

const powergl_util_window* powergl_util_window_new(void){
  const powergl_util_window* w;
  powergl_util_window_xorg_init();
  w = (const powergl_util_window*)(powergl_util_window_xorg_new());
  return w;
}
