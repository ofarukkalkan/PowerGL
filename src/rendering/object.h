#ifndef _powergl_object_h
#define _powergl_object_h

#define GL_GLEXT_PROTOTYPES

#include <GL/glcorearb.h>
#include <stddef.h>
#include "../powergl.h"
#include "../math/vec3.h"

typedef struct powergl_object_t powergl_object;
typedef struct powergl_geometry_t powergl_geometry;
typedef struct powergl_camera_t powergl_camera;
typedef struct powergl_light_t powergl_light;

typedef void powergl_run_object_func(powergl_object*);
typedef void powergl_create_object_func(powergl_object*);

struct powergl_light_t
{

    char type;

    GLfloat color[3];
    char color_flag;

    GLfloat dir[3];
    char dir_flag;

};

struct powergl_camera_t
{

    char type;

    GLfloat view[4][4];
    char view_flag;

    GLfloat projection[4][4];
    char projection_flag;

    GLfloat vp[4][4];

    GLfloat xfov;
    GLfloat yfov;
    GLfloat xmag;
    GLfloat ymag;
    GLfloat aspect_ratio;
    GLfloat znear;
    GLfloat zfar;

};

struct powergl_geometry_t
{

    GLuint vao;
    GLuint vbo;
    GLuint nbo;
    GLuint cbo;

    powergl_vec3 *vertex;
    char vertex_flag;
    size_t n_vertex;

    powergl_vec3 *normal;
    char normal_flag;
    size_t n_normal;

    powergl_vec3 *color;
    char color_flag;
    size_t n_color;

    GLuint *index;
    char index_flag;
    size_t n_index;

};

struct powergl_object_t
{

    // parent
    powergl_object *parent;

    // geometry
    powergl_geometry **geometry;
    size_t n_geometry;

    // camera
    powergl_camera *camera;

    // light
    powergl_light *light;

    // transform
    GLfloat matrix[4][4];
    char matrix_flag;

    GLfloat mvp[4][4];

    GLfloat lookat[3][3];
    GLfloat translate[3];
    GLfloat rotation[4];
    char rotation_flag;
    GLfloat scale[3];



    // info
    char *id;
    char *name;

    // virtual functions
    powergl_run_object_func *run;
    powergl_create_object_func *create;

};


#endif
