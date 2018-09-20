#ifndef _powergl_rendering_pipeline_h
#define _powergl_rendering_pipeline_h

#define GL_GLEXT_PROTOTYPES

#include <GL/glcorearb.h>
#include <stddef.h>

#include "object.h"

typedef struct powergl_rendering_pipeline_t powergl_rendering_pipeline;

typedef struct {
  GLuint index;
  GLint size;
  GLenum type;
  GLboolean normalized;
  GLsizei stride;
  GLvoid *offset;

} powergl_vsis; // vertex shader input specs

struct powergl_rendering_pipeline_t {

  powergl_vsis vis;
  powergl_vsis cis;
  GLuint vs;
  GLuint fs;
  GLuint gp;
  GLuint uni_matrix;
};

int powergl_rendering_pipeline_create( powergl_rendering_pipeline *, powergl_rendering_object **, size_t );
int powergl_rendering_pipeline_render( powergl_rendering_pipeline *, powergl_rendering_object **, size_t, int );

#endif
