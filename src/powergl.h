#ifndef _powergl_h
#define _powergl_h

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

typedef void powergl_run_func(void);
typedef void powergl_create_func(void);

void *powergl_resize(void *ptr, size_t count, size_t newsize);

typedef struct {
    void **arr;
    size_t size;
    size_t index;
} powergl_stack;

void powergl_stack_new(powergl_stack *, size_t);
void powergl_stack_delete(powergl_stack *);
void powergl_stack_push(powergl_stack *, void *);
void *powergl_stack_pop(powergl_stack *);
size_t powergl_stack_size(powergl_stack *);
#endif
