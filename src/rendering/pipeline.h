#ifndef _powergl_pipeline_h
#define _powergl_pipeline_h

#define GL_GLEXT_PROTOTYPES

#include <GL/glcorearb.h>
#include <stddef.h>

#include "object.h"

typedef struct powergl_pipeline_t powergl_pipeline;
typedef struct powergl_pipeline2_t powergl_pipeline2;

typedef struct {
  GLuint index;
  GLint size;
  GLenum type;
  GLboolean normalized;
  GLsizei stride;
  GLvoid *offset;

} powergl_vsis; // vertex shader input specs

struct powergl_pipeline_t {
  powergl_vsis vis;
  powergl_vsis nis;
  powergl_vsis cis;
  powergl_vsis tcis;
  GLuint vs;
  GLuint fs;
  GLuint gp;
  GLint uni_matrix;
  GLint uni_light_color;
  GLint uni_light_dir;
  GLint uni_sampler;
};

struct powergl_pipeline2_t {
  powergl_vsis vis;
  powergl_vsis nis;
  GLuint vs;
  GLuint fs;
  GLuint gp;
  GLint uni_matrix;
};


void powergl_pipeline_create(powergl_pipeline *, powergl_object **objs, size_t n_obj);
void powergl_pipeline_render(powergl_pipeline *, powergl_object **, size_t, powergl_object *);

void powergl_pipeline2_create(powergl_pipeline2 *, powergl_object **objs, size_t n_obj);
void powergl_pipeline2_render(powergl_pipeline2 *, powergl_object **, size_t);
#endif
