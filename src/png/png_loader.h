#include <png.h>

typedef struct {

  png_byte * data;
  png_uint_32 width, height;
  int depth;
  int color_type;

} powergl_png;

powergl_png powergl_png_load(const char * file);
