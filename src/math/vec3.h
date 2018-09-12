#ifndef _powergl_vec3_h
#define _powergl_vec3_h

#include <math.h>

typedef struct {
  float x;
  float y;
  float z;
} powergl_vec3;

void powergl_printvec3(powergl_vec3*v);
void powergl_normvec3(const powergl_vec3*m,powergl_vec3*r);
void powergl_subvec3(const powergl_vec3*m,const powergl_vec3*n,powergl_vec3*r);
void powergl_mulvec3(const powergl_vec3*m,const powergl_vec3*n,powergl_vec3*r);
void powergl_crossvec3(const powergl_vec3*m,const powergl_vec3*n,powergl_vec3*r);
float powergl_lenvec3(const powergl_vec3*m);
float powergl_dotvec3(const powergl_vec3*m,const powergl_vec3*n);

#endif
