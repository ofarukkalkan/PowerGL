#ifndef _powergl_rendering_object_h
#define _powergl_rendering_object_h

#define GL_GLEXT_PROTOTYPES

#include <GL/glcorearb.h>
#include <stddef.h>
#include "../powergl.h"
#include "../math/vec3.h"
#include "../asset/collada.h"

typedef struct powergl_rendering_object_t powergl_rendering_object;
typedef int powergl_rendering_object_create_func_t (void);
typedef int powergl_rendering_object_run_func_t (void);


struct powergl_rendering_object_t {

  powergl_rendering_object_create_func_t* create;
  powergl_rendering_object_run_func_t* run;

  // transform
  GLfloat matrix[4][4];
  GLfloat lookat[3][3];
  GLfloat translate[3];
  GLfloat rotation[4];
  GLfloat scale[3];
  GLfloat skew[3];
  char matrix_flag;

  // geometry
  GLuint vao;
  GLuint vbo;
  powergl_vec3 * vertex;
  size_t n_vertex;

  // info
  const char *id;
  const char *name;
};

void powergl_rendering_object_build_from_dae(powergl_rendering_object *, powergl_asset_collada_node *);

#endif
