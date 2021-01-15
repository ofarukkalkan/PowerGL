#ifndef _powergl_object_h
#define _powergl_object_h

#define GL_GLEXT_PROTOTYPES

#include <GL/glcorearb.h>
#include <stddef.h>
#include "../powergl.h"
#include "../math/vec3.h"
#include "../math/mat4x4.h"
#include "../png/png_loader.h"

#include <SDL2/SDL_events.h>

typedef struct powergl_object_t powergl_object;
typedef struct powergl_transform_t powergl_transform;
typedef struct powergl_geometry_t powergl_geometry;
typedef struct powergl_camera_t powergl_camera;
typedef struct powergl_light_t powergl_light;
typedef struct powergl_animation_t powergl_animation;
typedef struct powergl_animation_channel_t powergl_animation_channel;
typedef struct powergl_event_t powergl_event;
typedef struct powergl_collider_t powergl_collider;
typedef struct powergl_texture_t powergl_texture;

typedef void powergl_run_object_func(powergl_object *);
typedef void powergl_create_object_func(powergl_object *);


struct powergl_collider_t {
  
  powergl_geometry *shape;
  powergl_transform *transform;
  powergl_collider *nodes[8];
};

struct powergl_event_t {
  char key_w_pressed;
  char key_s_pressed;
  char key_a_pressed;
  char key_d_pressed;
  char key_space_pressed;
  char key_lctrl_pressed;
};

struct powergl_texture_t {
  
  powergl_png image;
  GLuint id;

};

struct powergl_animation_channel_t {
  size_t count;
  size_t current_key;
  float current_time;
  GLfloat *inputs;
  GLfloat *outputs;
  char** types;
  float* target;
};

struct powergl_animation_t {
  powergl_animation_channel channels[9];
  size_t n_channel;
};

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
  char vp_flag;

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
  GLuint tcbo;

  char visible_flag;
  
  float min_x, min_y, min_z, max_x, max_y, max_z;
  // bounding box vertices
  // min_x, min_y, min_z
  // min_x, min_y, max_z
  // min_x, max_y, min_z
  // min_x, max_y, max_z
  // max_x, min_y, min_z
  // max_x, min_y, max_z
  // max_x, max_y, min_z
  // max_x, max_y, max_z
  powergl_vec3 bounds[8];

  powergl_vec3 *vertex;
  char vertex_flag; // used for detection of vertex data changes
  size_t n_vertex;

  struct { // attributes below are optional
    size_t count;
  
    powergl_vec3 *normal;
    char normal_flag;  // used for detection of normal data changes
    size_t n_normal;

    powergl_vec3 *color;
    char color_flag; // used for detection of color data changes
    size_t n_color;

    powergl_vec2 *texcoord;
    char texcoord_flag; // used for detection of texcoord data changes
    size_t n_texcoord;


    GLuint *index;
    char index_flag; // used for detection of index data changes
    size_t n_index;

  } triangles;

};

struct powergl_transform_t {

  // mvp matrix
  powergl_mat4 mvp;

  // parent relative transform matrix
  powergl_mat4 local;

  // world transform matrix
  powergl_mat4 world;


  // basis transform components
  powergl_vec3 location;
  powergl_vec4 rotation_x;
  powergl_vec4 rotation_y;
  powergl_vec4 rotation_z;
  powergl_vec3 scale;

  //flags

  char mvp_flag;
  char matrix_flag;

};

struct powergl_object_t {

  // parent
  powergl_object *parent;

  // child objects
  powergl_object **objects;
  size_t n_object;

  // transform
  powergl_transform transform;

  // collider object
  powergl_collider *collider;

  // event
  powergl_event event;

  // geometry
  powergl_geometry geometry;

  // animation
  powergl_animation animation;

  // camera
  powergl_camera camera;

  // light
  powergl_light light;

  // texture
  powergl_texture texture;
  
  
  //flags
  char collider_flag;
  char event_flag;
  char animated_flag;
  char camera_flag;
  char light_flag;
  char textured_flag;

  // info
  char *id;
  char *name;

  // virtual functions
  powergl_run_object_func *run;
  powergl_create_object_func *create;

};

void powergl_animation_next(powergl_object *obj, float delta_time);
void powergl_light_update(powergl_object *obj);
void powergl_camera_update(powergl_object *obj);
void powergl_object_update_transform(powergl_object *obj, float delta_time);
void powergl_object_update_mvp(powergl_object *obj, powergl_object *cam);
void powergl_object_fps_controller(powergl_object *obj, float delta_time);
void powergl_event_handle(powergl_object *obj, SDL_Event *e, float delta_time);
void powergl_object_geometry_append(powergl_geometry *dest, powergl_geometry *src, powergl_vec3 offset);
void powergl_object_geometry_reset(powergl_geometry *geo);

void powergl_transform_reset(powergl_transform *trans);

 



#endif
