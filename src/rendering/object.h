#ifndef _powergl_object_h
#define _powergl_object_h

#define GL_GLEXT_PROTOTYPES

#include <GL/glcorearb.h>
#include <stddef.h>
#include "../powergl.h"
#include "../math/vec3.h"
#include "../math/mat4x4.h"

typedef struct powergl_object_t powergl_object;
typedef struct powergl_geometry_t powergl_geometry;
typedef struct powergl_camera_t powergl_camera;
typedef struct powergl_light_t powergl_light;

typedef void powergl_run_object_func(powergl_object *);
typedef void powergl_create_object_func(powergl_object *);

struct powergl_light_t {

    char type;

    powergl_vec3 color;
    char color_flag;

    powergl_vec3 dir;
    char dir_flag;

};

struct powergl_camera_t {

    char type;

    powergl_mat4 view;
    char view_flag;

    powergl_mat4 projection;
    char projection_flag;

    powergl_mat4 vp;

    GLfloat xfov;
    GLfloat yfov;
    GLfloat aspect_ratio;
    GLfloat znear;
    GLfloat zfar;

};

struct powergl_geometry_t {

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

struct powergl_object_t {

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
    char rotation_flag;
    char matrix_flag;

    powergl_mat4 mvp;
    powergl_mat4 transform;


    // info
    char *id;
    char *name;

    // virtual functions
    powergl_run_object_func *run;
    powergl_create_object_func *create;

};


#endif
