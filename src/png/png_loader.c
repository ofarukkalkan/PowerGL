#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <setjmp.h>

#include "png_loader.h"

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
