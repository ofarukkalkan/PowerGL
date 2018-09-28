#ifndef _powergl_rendering_object_h
#define _powergl_rendering_object_h

#define GL_GLEXT_PROTOTYPES

#include <GL/glcorearb.h>
#include <stddef.h>
#include "../powergl.h"
#include "../math/vec3.h"

typedef struct powergl_rendering_object_t powergl_rendering_object;
typedef struct powergl_rendering_geometry_t powergl_rendering_geometry;
typedef struct powergl_rendering_camera_t powergl_rendering_camera;
typedef struct powergl_rendering_light_t powergl_rendering_light;

struct powergl_rendering_light_t {

  char type;

  GLfloat color[3];
  char color_flag;
	
  GLfloat dir[3];
  char dir_flag;
	
};

struct powergl_rendering_camera_t {

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

struct powergl_rendering_geometry_t {

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

struct powergl_rendering_object_t {

  // geometry
  powergl_rendering_geometry *geometry;

  // camera
  powergl_rendering_camera *camera;

  // light
  powergl_rendering_light *light;

  // transform
  GLfloat matrix[4][4];
  char matrix_flag;

  GLfloat mvp[4][4];

  GLfloat lookat[3][3];
  GLfloat translate[3];
  GLfloat rotation[4];
  char rotation_flag;
  GLfloat scale[3];
  GLfloat skew[3];


  // info
  const char *id;
  const char *name;
};

int powergl_rendering_geometry_create( powergl_rendering_geometry * );
int powergl_rendering_camera_create( powergl_rendering_camera * );
int powergl_rendering_light_create( powergl_rendering_light * );
int powergl_rendering_object_create( powergl_rendering_object * );
int powergl_rendering_object_run( powergl_rendering_object * );
int powergl_rendering_object_rotate ( powergl_rendering_object *obj, float axisx,float axisy,float axisz, float radians );
int powergl_rendering_geometry_transform_normals(powergl_rendering_geometry *geo, GLfloat m[4][4]);

#endif
