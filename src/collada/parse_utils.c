#include "parse_utils.h"
#include "../powergl.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <inttypes.h>
#include <assert.h>

char **powergl_collada_parse_names(const char *str, size_t *value_size_ptr){
  char **arr = NULL;
  size_t size = 10;
  size_t index = 0;
  const char s[2] = " ";
  char *token;
   
  arr = powergl_resize(NULL, size, sizeof(char*));
  char * copy = powergl_resize(NULL, strlen(str)+1, sizeof(char));
  strcpy(copy, str);

  token = strtok(copy, s);
   
  /* walk through other tokens */
  while( token != NULL ) {
    if(index == size){
      size = size * 2;
      arr = powergl_resize(arr, size, sizeof(char*));
    }
    arr[index++] = powergl_resize(NULL, strlen(token)+1, sizeof(char));
    strcpy(arr[index-1], token);
    
    token = strtok(NULL, s);

  }
  
  free(copy);
  copy = NULL;
  
  *value_size_ptr = index;
  return arr;
}

size_t *powergl_collada_parse_uints(const char *str, size_t *value_size_ptr) {
    size_t len = strlen(str);
    char *end = NULL;
    const char *old_ptr = str;
    size_t i = 0;

    for(size_t f = strtoumax(str, &end, 10); end <= (old_ptr + len * sizeof(char)); f = strtoul(str, &end, 10)) {
        if(end == str) {    //  If no conversion can be performed
            break;
        }

        str = end;

        if(errno == ERANGE) {
            fprintf(stderr, "%lu range error, got ", f);
            errno = 0;
        } else {
            i++;
        }
    }

    if(i == 0) {
        *value_size_ptr = 0;
        return NULL;
    }

    size_t *arr = NULL;
    arr = powergl_resize(NULL, i,  sizeof(size_t));
    i = 0;
    str = old_ptr;
    end = NULL;

    for(size_t f = strtoumax(str, &end, 10); end <= (old_ptr + len * sizeof(char)); f = strtoul(str, &end, 10)) {
        if(end == str) {    //  If no conversion can be performed
            break;
        }

        str = end;

        if(errno == ERANGE) {
            fprintf(stderr, "range error, got ");
            errno = 0;
        } else {
            arr[i] = f;
            i++;
        }
    }

    *value_size_ptr = i;
    return arr;
}

double *powergl_collada_parse_floats(const char *str, size_t *value_size_ptr) {
    size_t len = strlen(str);
    char *end = NULL;
    const char *old_ptr = str;
    size_t i = 0;

    for(double f = strtof(str, &end); end <= (old_ptr + len * sizeof(char)); f = strtof(str, &end)) {
        if(end == str) {    //  If no conversion can be performed
            break;
        }

        str = end;

        if(errno == ERANGE) {
            fprintf(stderr, "%f, range error, got ", f);
            errno = 0;
        } else {
            i++;
        }
    }

    if(i == 0) {
        *value_size_ptr = 0;
        return NULL;
    }

    double *arr = NULL;
    arr = powergl_resize(NULL, i, sizeof(double));
    i = 0;
    str = old_ptr;
    end = NULL;

    for(double f = strtof(str, &end); end <= (old_ptr + len * sizeof(char)); f = strtof(str, &end)) {
        if(end == str) {    //  If no conversion can be performed
            break;
        }

        str = end;

        if(errno == ERANGE) {
            fprintf(stderr, "range error, got ");
            errno = 0;
        } else {
            arr[i] = f;
            i++;
        }
    }

    *value_size_ptr = i;
    return arr;
}
