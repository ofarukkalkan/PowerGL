#include "powergl.h"

void* powergl_resize(void *ptr,size_t newsize){
  if(ptr==NULL){
    ptr = malloc(newsize);
    assert(ptr);
  }else{
    void* tmp_ptr = realloc(ptr,newsize);
    assert(tmp_ptr);
    ptr = tmp_ptr;
  }
  return ptr;
}
