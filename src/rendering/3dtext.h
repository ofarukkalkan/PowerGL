#ifndef _powergl_3dtext_h
#define _powergl_3dtext_h

#include "objectlibrary.h"

typedef struct powergl_3dtext_node_t powergl_3dtext_node;

struct powergl_3dtext_node_t {
  powergl_3dtext_node *prev;
  powergl_3dtext_node *next;

  powergl_geometry *geo;

  char letter;
};

typedef struct {
  float hspace, vspace, hlimit, vlimit;
} powergl_3dtext_config;

typedef struct {
  powergl_object *root;
  powergl_3dtext_node *root_node;
  
  char *str;
  size_t n_char;
  
  powergl_3dtext_config cfg;

} powergl_3dtext;


void powergl_3dtext_build(powergl_3dtext *text, powergl_3dtext_config cfg, powergl_object_library *lib, const char *str);

#endif
