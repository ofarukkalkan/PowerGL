#include "powergl.h"

void *powergl_resize( void *ptr, size_t count, size_t size )
{
  assert(count);
  assert(size);
  
  if ( ptr == NULL )
    {
      ptr = calloc(count, size );
      assert( ptr );
    }
  else
    {
      void *tmp_ptr = realloc( ptr, count * size );
      assert( tmp_ptr );
      ptr = tmp_ptr;
    }
  return ptr;
}
