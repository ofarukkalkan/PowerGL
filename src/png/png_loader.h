#ifndef POWERGL_PNG_LOADER_H
#define POWERGL_PNG_LOADER_H

#include <png.h>

typedef struct {

  png_byte * data;
  png_uint_32 width, height;
  int depth;
  int color_type;

} powergl_png;

powergl_png powergl_png_load(const char * file);

/*
 * Save the current OpenGL framebuffer to a PNG image. The image dimensions
 * are taken from the current viewport. Returns 0 on failure, non-zero on
 * success.
 */
int powergl_png_save(const char *filename);

/*
 * Compare two PNG images pixel by pixel. Returns 1 if the images have the
 * same dimensions and differ by less than a threshold, otherwise returns 0.
 */
int powergl_png_compare(const char *a, const char *b);

#endif /* POWERGL_PNG_LOADER_H */
