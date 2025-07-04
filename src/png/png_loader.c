#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <setjmp.h>

#include "png_loader.h"
#include <GL/glew.h>
#include <png.h>

powergl_png powergl_png_load(const char * file){

  powergl_png image;
  FILE *f;
  int is_png, bit_depth, color_type, row_bytes, i;
  png_infop info_ptr, end_info;
  png_uint_32 t_width, t_height;
  png_byte header[8], *image_data;
  png_bytepp row_pointers;
  png_structp png_ptr;
  int alpha;

  image.data = NULL;


  if ( !( f = fopen(file, "r" ) ) ) {
    fprintf(stderr, "\npng_loader : path is wrong\n");
    return image;
  }
  fread( header, 1, 8, f );
  is_png = !png_sig_cmp( header, 0, 8 );
  if ( !is_png ) {
    fclose( f );
    fprintf(stderr, "\npng_loader : no png header\n");
    return image;
  }
  png_ptr = png_create_read_struct( PNG_LIBPNG_VER_STRING, NULL,
				    NULL, NULL );
  if ( !png_ptr ) {
    fclose( f );
    fprintf(stderr, "\npng_loader : coulndt create read struct\n");
    return image;
  }
  info_ptr = png_create_info_struct( png_ptr );
  if ( !info_ptr ) {
    png_destroy_read_struct( &png_ptr, (png_infopp) NULL, 
			     (png_infopp) NULL );
    fprintf(stderr, "\npng_loader : coulndt create info struct\n");
    fclose( f );
    return image;
  }
  end_info = png_create_info_struct( png_ptr );
  if ( !end_info ) {
    png_destroy_read_struct( &png_ptr, (png_infopp) NULL,
			     (png_infopp) NULL );
    fclose( f );
    return image;
  }
  if ( setjmp( png_jmpbuf( png_ptr ) ) ) {
    png_destroy_read_struct( &png_ptr, &info_ptr, &end_info );
    fclose( f );
    return image;
  }
  png_init_io( png_ptr, f );
  png_set_sig_bytes( png_ptr, 8 );
  png_read_info( png_ptr, info_ptr );
  png_get_IHDR( png_ptr, info_ptr, &t_width, &t_height, &bit_depth, 
		&color_type, NULL, NULL, NULL );

  png_read_update_info( png_ptr, info_ptr );
  row_bytes = png_get_rowbytes( png_ptr, info_ptr );
  image_data = (png_bytep) malloc( row_bytes * t_height * sizeof(png_byte) );
  if ( !image_data ) {
    png_destroy_read_struct( &png_ptr, &info_ptr, &end_info );
    fclose( f );
    return image;
  }
  row_pointers = (png_bytepp) malloc( t_height * sizeof(png_bytep) );
  if ( !row_pointers ) {
    png_destroy_read_struct( &png_ptr, &info_ptr, &end_info );
    free( image_data );
    fclose( f );
    return image;
  }
  for ( i = 0; i < t_height; ++i ) {
    row_pointers[t_height - 1 - i] = image_data + i * row_bytes;
  }
  png_read_image( png_ptr, row_pointers );

  image.data = image_data;
  image.width = t_width;
  image.height = t_height;
  image.depth = bit_depth;
  image.color_type = color_type;

  return image;
}

int powergl_png_save(const char *filename){
  GLint vp[4];
  glGetIntegerv(GL_VIEWPORT, vp);
  int width = vp[2];
  int height = vp[3];
  size_t size = (size_t)width * height * 4;
  unsigned char *pixels = (unsigned char*)malloc(size);
  if(!pixels){
    fprintf(stderr, "failed to allocate %zu bytes for screenshot\n", size);
    return 0;
  }
  glPixelStorei(GL_PACK_ALIGNMENT, 1);
  glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

  FILE *fp = fopen(filename, "wb");
  if(!fp){
    fprintf(stderr, "cannot open %s for writing\n", filename);
    free(pixels);
    return 0;
  }

  png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if(!png_ptr){
    fprintf(stderr, "failed to create png write struct\n");
    fclose(fp);
    free(pixels);
    return 0;
  }
  png_infop info_ptr = png_create_info_struct(png_ptr);
  if(!info_ptr){
    fprintf(stderr, "failed to create png info struct\n");
    png_destroy_write_struct(&png_ptr, NULL);
    fclose(fp);
    free(pixels);
    return 0;
  }
  if(setjmp(png_jmpbuf(png_ptr))){
    fprintf(stderr, "png error writing to %s\n", filename);
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);
    free(pixels);
    return 0;
  }
  png_init_io(png_ptr, fp);
  png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGBA,
               PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
  png_write_info(png_ptr, info_ptr);
  png_bytep *row_pointers = malloc(sizeof(png_bytep) * height);
  if(!row_pointers){
    fprintf(stderr, "failed to allocate row pointers\n");
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);
    free(pixels);
    return 0;
  }
  for(int y = 0; y < height; ++y)
    row_pointers[height - 1 - y] = pixels + y * width * 4;
  png_write_image(png_ptr, row_pointers);
  png_write_end(png_ptr, NULL);
  png_destroy_write_struct(&png_ptr, &info_ptr);
  free(row_pointers);
  fclose(fp);
  free(pixels);
  return 1;
}

int powergl_png_compare(const char *a, const char *b){
  powergl_png pa = powergl_png_load(a);
  powergl_png pb = powergl_png_load(b);
  if(!pa.data){
    fprintf(stderr, "failed to load image %s\n", a);
    if(pb.data) free(pb.data);
    return 0;
  }
  if(!pb.data){
    fprintf(stderr, "failed to load image %s\n", b);
    free(pa.data);
    return 0;
  }
  if(pa.width != pb.width || pa.height != pb.height || pa.color_type != pb.color_type){
    fprintf(stderr, "image dimensions or color type differ\n");
    free(pa.data);
    free(pb.data);
    return 0;
  }
  int bpp = (pa.color_type == PNG_COLOR_TYPE_RGB) ? 3 : 4;
  size_t size = (size_t)pa.width * pa.height * bpp;
  int diff = 0;
  for(size_t i = 0; i < size; ++i){
    if(abs((int)pa.data[i] - (int)pb.data[i]) > 160){
      diff = 1;
      break;
    }
  }
  if(diff)
    fprintf(stderr, "image data differs between %s and %s\n", a, b);
  free(pa.data);
  free(pb.data);
  return diff ? 0 : 1;
}
