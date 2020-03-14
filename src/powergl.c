#include "powergl.h"
#include <string.h>

void *powergl_resize(void *ptr, size_t count, size_t size) {
    assert(count);
    assert(size);

    if(ptr == NULL) {
        ptr = calloc(count, size);
        assert(ptr);
    } else {
        void *tmp_ptr = realloc(ptr, count * size);
        assert(tmp_ptr);
        ptr = tmp_ptr;
    }

    return ptr;
}

void powergl_stack_new(powergl_stack *st, size_t n) {
    st->arr = powergl_resize(NULL, n, sizeof(void *));
    st->size = n;
    st->index = 0;
}
void powergl_stack_delete(powergl_stack *st) {
    if(st->arr) {
        for(size_t i = 0; i < st->size; i++) {
            if(st->arr[i]) {
                free(st->arr[i]);
                st->arr[i] = NULL;
            }
        }

        free(st->arr);
        st->arr = NULL;
        st->size = 0;
        st->index = 0;
    } else {
        assert(st->arr);
    }
}

void powergl_stack_push(powergl_stack *st, void *data) {
    if(st->index == st->size) {
        st->arr = powergl_resize(st->arr, st->size * 2, sizeof(void *));
    }

    st->arr[st->index++] = data;
}
void *powergl_stack_pop(powergl_stack *st) {
    if(st->index > 0)  {
        void *ptr = st->arr[--st->index];
        st->arr[st->index] = NULL;
        return ptr;
    } else {
        void *ptr = st->arr[0];
        st->arr[0] = NULL;
        return ptr;
    }
}
