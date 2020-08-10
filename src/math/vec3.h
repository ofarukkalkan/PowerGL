#ifndef _powergl_vec3_h
#define _powergl_vec3_h
#include <GL/glcorearb.h>
#include <math.h>
#include <stddef.h>
typedef union vec4_t powergl_vec4;
typedef union vec3_t powergl_vec3;
typedef union vec2_t powergl_vec2;

union vec2_t {
  struct {
    GLfloat x, y;
  };
  union {
    GLfloat r[2], data[2];
  };
};

union vec3_t {
  struct {
    GLfloat x, y, z;
  };
  union {
    GLfloat r[3], data[3];
  };
};

union vec4_t {
  struct {
    GLfloat x, y, z, w;
  };
  union {
    GLfloat r[4], data[4];
  };
  struct {
    powergl_vec3 xyz;
    GLfloat w1;
  };
};

void powergl_float_print(const char *msg, GLfloat m);
float powergl_float_to_radians(float degrees);
void powergl_vec3_print(const char *msg, powergl_vec3  m);
void powergl_vec4_print(const char *msg, powergl_vec4  m);
void powergl_vec3_copy(powergl_vec3 *v, const double * const arr, size_t size);
void powergl_vec4_copy(powergl_vec4 *v, const double * const arr, size_t size);
float powergl_vec3_dot(powergl_vec3 m, powergl_vec3 n);
float powergl_vec3_len(powergl_vec3 m);
powergl_vec3 powergl_vec3_cross(powergl_vec3 m, powergl_vec3 n);
powergl_vec3 powergl_vec3_mulv(powergl_vec3 m,  powergl_vec3 n);
powergl_vec3 powergl_vec3_muls(powergl_vec3 m, GLfloat n);
powergl_vec4  powergl_vec4_mulv(powergl_vec4 m,  powergl_vec4 n);
powergl_vec4 powergl_vec4_muls(powergl_vec4 m, GLfloat n);
powergl_vec3 powergl_vec3_add(powergl_vec3 m,  powergl_vec3 n);
powergl_vec4 powergl_vec4_add(powergl_vec4 m,  powergl_vec4 n);
powergl_vec3 powergl_vec3_sub(powergl_vec3 m,  powergl_vec3 n);
powergl_vec4 powergl_vec4_sub(powergl_vec4 m,  powergl_vec4 n);
powergl_vec3 powergl_vec3_div(powergl_vec3 m,  powergl_vec3 n);
powergl_vec4 powergl_vec4_div(powergl_vec4 m,  powergl_vec4 n);
powergl_vec3 powergl_vec3_norm(powergl_vec3 m);

#endif
