#include "vec3.h"
#include <stdio.h>
#include <assert.h>
#ifndef DEBUG_OUTPUT
#define DEBUG_OUTPUT 0
#endif


void powergl_float_print(const char *msg, GLfloat m) {
    printf("%s ->\n", msg);
    printf("[ %f ]\n", m);
}


void powergl_vec3_print(const char *msg, powergl_vec3  m) {
    printf("%s ->\n",  msg);
    printf("[ %f , %f , %f ]\n", m.x, m.y, m.z);
}

void powergl_vec4_print(const char *msg, powergl_vec4  m) {
    printf("%s ->\n", msg);
    printf("[ %f , %f , %f %f ]\n", m.x, m.y, m.z, m.w);
}

inline void powergl_vec3_copy(powergl_vec3 *v, const double * const arr, size_t size){
  if(size != 3){
    assert(0);
  }
  for(size_t i=0; i < size; i++){
    v->r[i] = (GLfloat)arr[i];
  }
}
inline void powergl_vec4_copy(powergl_vec4 *v, const double * const arr, size_t size){
  if(size != 4){
    assert(0);
  }
  for(size_t i=0; i < size; i++){
    v->r[i] = (GLfloat)arr[i];
  }
}


inline float powergl_vec3_dot(powergl_vec3 m, powergl_vec3 n) {
#if DEBUG_OUTPUT
    printf("%s\n", __func__);
    powergl_vec3_print("m", m);
    powergl_vec3_print("n", n);
#endif
    return (m.x * n.x) + (m.y * n.y) + (m.z * n.z);
}
inline float powergl_vec3_len(powergl_vec3 m) {
#if DEBUG_OUTPUT
    printf("%s\n", __func__);
    powergl_vec3_print("m", m);
#endif
    return sqrtf(powergl_vec3_dot(m, m));
}
inline powergl_vec3 powergl_vec3_cross(powergl_vec3 m, powergl_vec3 n) {
#if DEBUG_OUTPUT
    printf("%s\n", __func__);
    powergl_vec3_print("m", m);
    powergl_vec3_print("n", n);
#endif
    powergl_vec3 res;
    res.x = m.y * n.z - n.y * m.z;
    res.y = m.z * n.x - n.z * m.x;
    res.z = m.x * n.y - n.x * m.y;
    return res;
}
inline powergl_vec3 powergl_vec3_mulv(powergl_vec3 m,  powergl_vec3 n) {
#if DEBUG_OUTPUT
    printf("%s\n", __func__);
    powergl_vec3_print("m", m);
    powergl_vec3_print("n", n);
#endif
    powergl_vec3 r;
    r.x = m.x * n.x;
    r.y = m.y * n.y;
    r.z = m.z * n.z;
    return r;
}

inline powergl_vec3 powergl_vec3_muls(powergl_vec3 m, GLfloat n) {
#if DEBUG_OUTPUT
    printf("%s\n", __func__);
    powergl_vec3_print("m", m);
    powergl_float_print("n", n);
#endif
    powergl_vec3 r;
    r.x = m.x * n;
    r.y = m.y * n;
    r.z = m.z * n;
    return r;
}

inline powergl_vec4  powergl_vec4_mulv(powergl_vec4 m,  powergl_vec4 n) {
#if DEBUG_OUTPUT
    printf("%s\n", __func__);
    powergl_vec4_print("m", m);
    powergl_vec4_print("n", n);
#endif
    powergl_vec4 r;
    r.x = m.x * n.x;
    r.y = m.y * n.y;
    r.z = m.z * n.z;
    r.w = m.w * n.w;
    return r;
}
inline powergl_vec4 powergl_vec4_muls(powergl_vec4 m, GLfloat n) {
#if DEBUG_OUTPUT
    printf("%s\n", __func__);
    powergl_vec4_print("m", m);
    powergl_float_print("n", n);
#endif
    powergl_vec4 r;
    r.x = m.x * n;
    r.y = m.y * n;
    r.z = m.z * n;
    r.w = m.w * n;
    return r;
}

inline powergl_vec3 powergl_vec3_add(powergl_vec3 m,  powergl_vec3 n) {
#if DEBUG_OUTPUT
    printf("%s\n", __func__);
    powergl_vec3_print("m", m);
    powergl_vec3_print("n", n);
#endif
    powergl_vec3 r;
    r.x = m.x + n.x;
    r.y = m.y + n.y;
    r.z = m.z + n.z;
    return r;
}
inline powergl_vec4 powergl_vec4_add(powergl_vec4 m,  powergl_vec4 n) {
#if DEBUG_OUTPUT
    printf("%s\n", __func__);
    powergl_vec4_print("m", m);
    powergl_vec4_print("n", n);
#endif
    powergl_vec4 r;
    r.x = m.x + n.x;
    r.y = m.y + n.y;
    r.z = m.z + n.z;
    r.w = m.w + n.w;
    return r;
}

inline powergl_vec3 powergl_vec3_sub(powergl_vec3 m,  powergl_vec3 n) {
#if DEBUG_OUTPUT
    printf("%s\n", __func__);
    powergl_vec3_print("m", m);
    powergl_vec3_print("n", n);
#endif
    powergl_vec3 r;
    r.x = m.x - n.x;
    r.y = m.y - n.y;
    r.z = m.z - n.z;
    return r;
}
inline powergl_vec4 powergl_vec4_sub(powergl_vec4 m,  powergl_vec4 n) {
#if DEBUG_OUTPUT
    printf("%s\n", __func__);
    powergl_vec4_print("m", m);
    powergl_vec4_print("n", n);
#endif
    powergl_vec4 r;
    r.x = m.x - n.x;
    r.y = m.y - n.y;
    r.z = m.z - n.z;
    r.w = m.w - n.w;
    return r;
}
inline powergl_vec3 powergl_vec3_div(powergl_vec3 m,  powergl_vec3 n) {
#if DEBUG_OUTPUT
    printf("%s\n", __func__);
    powergl_vec3_print("m", m);
    powergl_vec3_print("n", n);
#endif
    powergl_vec3 r;
    r.x = m.x / n.x;
    r.y = m.y / n.y;
    r.z = m.z / n.z;
    return r;
}
inline powergl_vec4 powergl_vec4_div(powergl_vec4 m,  powergl_vec4 n) {
#if DEBUG_OUTPUT
    printf("%s\n", __func__);
    powergl_vec4_print("m", m);
    powergl_vec4_print("n", n);
#endif
    powergl_vec4 r;
    r.x = m.x / n.x;
    r.y = m.y / n.y;
    r.z = m.z / n.z;
    r.w = m.w / n.w;
    return r;
}
inline powergl_vec3 powergl_vec3_norm(powergl_vec3 m) {
#if DEBUG_OUTPUT
    printf("%s\n", __func__);
    powergl_vec3_print("m", m);
#endif
    powergl_vec3 res;
    float length = powergl_vec3_len(m);
    res.x = m.x / length;
    res.y = m.y / length;
    res.z = m.z / length;
    return res;
}
