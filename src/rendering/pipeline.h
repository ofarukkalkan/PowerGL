#ifndef _powergl_pipeline_h
#define _powergl_pipeline_h

#define GL_GLEXT_PROTOTYPES

#include <GL/glcorearb.h>
#include <stddef.h>

#include "object.h"

typedef struct powergl_pipeline_t powergl_pipeline;

typedef struct
{
    GLuint index;
    GLint size;
    GLenum type;
    GLboolean normalized;
    GLsizei stride;
    GLvoid *offset;

} powergl_vsis; // vertex shader input specs

struct powergl_pipeline_t
{

    powergl_vsis vis;
    powergl_vsis nis;
    powergl_vsis cis;
    GLuint vs;
    GLuint fs;
    GLuint gp;
    GLuint uni_matrix;
    GLuint uni_light_color;
    GLuint uni_light_dir;
};

int powergl_pipeline_create( powergl_pipeline * );
int powergl_pipeline_render( powergl_pipeline *, powergl_object **, size_t, powergl_object*, powergl_object* );
void powergl_pipeline_init(powergl_pipeline *, powergl_object *);
#endif
