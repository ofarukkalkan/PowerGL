#ifndef _powergl_rendering_pipeline_h
#define _powergl_rendering_pipeline_h

#define GL_GLEXT_PROTOTYPES

#include <GL/glcorearb.h>
#include <stddef.h>
#include "object.h"


typedef struct powergl_rendering_pipeline_t powergl_rendering_pipeline;
typedef int powergl_rendering_pipeline_create_func_t (void);
typedef int powergl_rendering_pipeline_run_func_t (void);


typedef struct {
  GLuint index;
  GLint size;
  GLenum type;
  GLboolean normalized;
  GLsizei stride;
  GLvoid * offset;
    
} powergl_vsis; // vertex shader input specs

struct powergl_rendering_pipeline_t {

  powergl_rendering_pipeline_create_func_t* create;
  powergl_rendering_pipeline_run_func_t* run;

  // objects
  powergl_rendering_object *objects;
  size_t n_object;

  powergl_vsis vsis;
  GLuint vs;
  GLuint fs;
  GLuint gp;
  GLuint mvp;
};


#endif
