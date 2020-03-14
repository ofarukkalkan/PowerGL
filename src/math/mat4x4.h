#ifndef _powergl_mat4_h
#define _powergl_mat4_h
#define GL_GLEXT_PROTOTYPES
#include "vec3.h"

/*
  mat4 should be 16 byte = 4 byte * 4, if there is a problem in listing matrix, check every c[i] vec4's starting address
*/
typedef union {
  struct {
    powergl_vec4 c[4];
  };
  struct {
    GLfloat data[16];
  };
} powergl_mat4;
void powergl_mat4_print(const char *msg, powergl_mat4 m);
powergl_mat4 powergl_mat4_zero();
powergl_mat4 powergl_mat4_ident();
void powergl_mat4_copy(powergl_mat4 *m, const double * const arr, size_t size, int type);
powergl_mat4 powergl_mat4_muls(powergl_mat4 m1, GLfloat s);
powergl_mat4 powergl_mat4_mul(powergl_mat4 m1, powergl_mat4 m2);
powergl_mat4 powergl_mat4_transpose(powergl_mat4 m);
powergl_mat4 powergl_mat4_inv(powergl_mat4 m);
powergl_mat4 powergl_mat4_translate(powergl_mat4 m, powergl_vec3 v);
powergl_mat4 powergl_mat4_rot(powergl_mat4 m, float angle, powergl_vec3 v);
powergl_mat4 powergl_mat4_lookatRH(powergl_vec3 eye, powergl_vec3 center, powergl_vec3 up);
powergl_mat4 powergl_mat4_perspectiveRH(float fovy, float aspect, float zNear, float zFar);
powergl_vec4 powergl_vec4_trans(powergl_vec4 v, powergl_mat4  m);
#endif
