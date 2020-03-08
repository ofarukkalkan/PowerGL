#ifndef _powergl_h
#define _powergl_h

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

typedef void powergl_run_func(void);
typedef void powergl_create_func(void);

void *powergl_resize( void *ptr, size_t count, size_t newsize );
#endif
