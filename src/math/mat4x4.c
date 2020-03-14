#include "mat4x4.h"

#include <float.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#ifndef DEBUG_OUTPUT
#define DEBUG_OUTPUT 0
#endif


void powergl_mat4_print(const char *msg, powergl_mat4 m) {
    printf("%s ->\n", msg);

    size_t i, j;

    for(i = 0; i < 4; ++i) {
        printf("[ ");

        for(j = 0; j < 4; j++) {
            printf("%f ", m.c[j].r[i]);
        }

        printf(" ]\n");
    }
}

inline powergl_mat4 powergl_mat4_zero() {
    powergl_mat4 m;
    m.c[0].r[0] = 0.0f;
    m.c[0].r[1] = 0.0f;
    m.c[0].r[2] = 0.0f;
    m.c[0].r[3] = 0.0f;
    m.c[1].r[0] = 0.0f;
    m.c[1].r[1] = 0.0f;
    m.c[1].r[2] = 0.0f;
    m.c[1].r[3] = 0.0f;
    m.c[2].r[0] = 0.0f;
    m.c[2].r[1] = 0.0f;
    m.c[2].r[2] = 0.0f;
    m.c[2].r[3] = 0.0f;
    m.c[3].r[0] = 0.0f;
    m.c[3].r[1] = 0.0f;
    m.c[3].r[2] = 0.0f;
    m.c[3].r[3] = 0.0f;
    return m;
}

inline powergl_mat4 powergl_mat4_ident() {
    powergl_mat4 m;
    m.c[0].r[0] = 1.0f;
    m.c[0].r[1] = 0.0f;
    m.c[0].r[2] = 0.0f;
    m.c[0].r[3] = 0.0f;
    m.c[1].r[0] = 0.0f;
    m.c[1].r[1] = 1.0f;
    m.c[1].r[2] = 0.0f;
    m.c[1].r[3] = 0.0f;
    m.c[2].r[0] = 0.0f;
    m.c[2].r[1] = 0.0f;
    m.c[2].r[2] = 1.0f;
    m.c[2].r[3] = 0.0f;
    m.c[3].r[0] = 0.0f;
    m.c[3].r[1] = 0.0f;
    m.c[3].r[2] = 0.0f;
    m.c[3].r[3] = 1.0f;
    return m;
}

inline void powergl_mat4_copy(powergl_mat4 *m, const double * const arr, size_t size, int type){
  if(size!=16){
    assert(0);
  }
  for(size_t i=0; i < 4; i++){
    for(size_t j=0; j < 4; j++){
      if(type==1){//row-major
	m->c[j].r[i] = (GLfloat)arr[i*4 + j];
      } else {
	m->c[i].r[j] = (GLfloat)arr[i*4 + j];
      }
    }
  }
}

inline powergl_mat4 powergl_mat4_muls(powergl_mat4 m1, GLfloat s) {
#if DEBUG_OUTPUT
    printf("%s\n", __func__);
    powergl_mat4_print("m1", m1);
    powergl_float_print("s", s);
#endif
    powergl_mat4 r;
    r.c[0] = powergl_vec4_muls(m1.c[0], s);
    r.c[1] = powergl_vec4_muls(m1.c[1], s);
    r.c[2] = powergl_vec4_muls(m1.c[2], s);
    r.c[3] = powergl_vec4_muls(m1.c[3], s);
    return r;
}

inline powergl_mat4 powergl_mat4_mul(powergl_mat4 m1, powergl_mat4 m2) {
#if DEBUG_OUTPUT
    printf("%s\n", __func__);
    powergl_mat4_print("in m1", m1);
    powergl_mat4_print("in m2", m2);
#endif
    powergl_vec4 SrcA0 = m1.c[0];
    powergl_vec4 SrcA1 = m1.c[1];
    powergl_vec4 SrcA2 = m1.c[2];
    powergl_vec4 SrcA3 = m1.c[3];
    powergl_vec4 SrcB0 = m2.c[0];
    powergl_vec4 SrcB1 = m2.c[1];
    powergl_vec4 SrcB2 = m2.c[2];
    powergl_vec4 SrcB3 = m2.c[3];
    powergl_mat4 Result;
    Result.c[0] = powergl_vec4_add(powergl_vec4_add(powergl_vec4_muls(SrcA0, SrcB0.r[0]),
						    powergl_vec4_muls(SrcA1, SrcB0.r[1])),
                                   powergl_vec4_add(powergl_vec4_muls(SrcA2, SrcB0.r[2]),
						    powergl_vec4_muls(SrcA1, SrcB0.r[3])));
    Result.c[1] = powergl_vec4_add(powergl_vec4_add(powergl_vec4_muls(SrcA0, SrcB1.r[0]),
						    powergl_vec4_muls(SrcA1, SrcB1.r[1])),
                                   powergl_vec4_add(powergl_vec4_muls(SrcA2, SrcB1.r[2]),
						    powergl_vec4_muls(SrcA3, SrcB1.r[3])));
    Result.c[2] = powergl_vec4_add(powergl_vec4_add(powergl_vec4_muls(SrcA0, SrcB2.r[0]),
						    powergl_vec4_muls(SrcA1, SrcB2.r[1])),
                                   powergl_vec4_add(powergl_vec4_muls(SrcA2, SrcB2.r[2]),
						    powergl_vec4_muls(SrcA3, SrcB2.r[3])));
    Result.c[3] = powergl_vec4_add(powergl_vec4_add(powergl_vec4_muls(SrcA0, SrcB3.r[0]),
						    powergl_vec4_muls(SrcA1, SrcB3.r[1])),
                                   powergl_vec4_add(powergl_vec4_muls(SrcA2, SrcB3.r[2]),
						    powergl_vec4_muls(SrcA3, SrcB3.r[3])));
    return Result;
}

inline powergl_mat4 powergl_mat4_transpose(powergl_mat4 m) {
#if DEBUG_OUTPUT
    printf("%s\n", __func__);
    powergl_mat4_print("in m", m);
#endif
    powergl_mat4 Result;
    Result.c[0].r[0] = m.c[0].r[0];
    Result.c[0].r[1] = m.c[1].r[0];
    Result.c[0].r[2] = m.c[2].r[0];
    Result.c[0].r[3] = m.c[3].r[0];
    Result.c[1].r[0] = m.c[0].r[1];
    Result.c[1].r[1] = m.c[1].r[1];
    Result.c[1].r[2] = m.c[2].r[1];
    Result.c[1].r[3] = m.c[3].r[1];
    Result.c[2].r[0] = m.c[0].r[2];
    Result.c[2].r[1] = m.c[1].r[2];
    Result.c[2].r[2] = m.c[2].r[2];
    Result.c[2].r[3] = m.c[3].r[2];
    Result.c[3].r[0] = m.c[0].r[3];
    Result.c[3].r[1] = m.c[1].r[3];
    Result.c[3].r[2] = m.c[2].r[3];
    Result.c[3].r[3] = m.c[3].r[3];
    return Result;
}

inline powergl_mat4 powergl_mat4_inv(powergl_mat4 m) {
#if DEBUG_OUTPUT
    printf("%s\n", __func__);
    powergl_mat4_print("in m", m);
#endif
    GLfloat Coef00 = m.c[2].r[2] * m.c[3].r[3] - m.c[3].r[2] * m.c[2].r[3];
    GLfloat Coef02 = m.c[1].r[2] * m.c[3].r[3] - m.c[3].r[2] * m.c[1].r[3];
    GLfloat Coef03 = m.c[1].r[2] * m.c[2].r[3] - m.c[2].r[2] * m.c[1].r[3];
    GLfloat Coef04 = m.c[2].r[1] * m.c[3].r[3] - m.c[3].r[1] * m.c[2].r[3];
    GLfloat Coef06 = m.c[1].r[1] * m.c[3].r[3] - m.c[3].r[1] * m.c[1].r[3];
    GLfloat Coef07 = m.c[1].r[1] * m.c[2].r[3] - m.c[2].r[1] * m.c[1].r[3];
    GLfloat Coef08 = m.c[2].r[1] * m.c[3].r[2] - m.c[3].r[1] * m.c[2].r[2];
    GLfloat Coef10 = m.c[1].r[1] * m.c[3].r[2] - m.c[3].r[1] * m.c[1].r[2];
    GLfloat Coef11 = m.c[1].r[1] * m.c[2].r[2] - m.c[2].r[1] * m.c[1].r[2];
    GLfloat Coef12 = m.c[2].r[0] * m.c[3].r[3] - m.c[3].r[0] * m.c[2].r[3];
    GLfloat Coef14 = m.c[1].r[0] * m.c[3].r[3] - m.c[3].r[0] * m.c[1].r[3];
    GLfloat Coef15 = m.c[1].r[0] * m.c[2].r[3] - m.c[2].r[0] * m.c[1].r[3];
    GLfloat Coef16 = m.c[2].r[0] * m.c[3].r[2] - m.c[3].r[0] * m.c[2].r[2];
    GLfloat Coef18 = m.c[1].r[0] * m.c[3].r[2] - m.c[3].r[0] * m.c[1].r[2];
    GLfloat Coef19 = m.c[1].r[0] * m.c[2].r[2] - m.c[2].r[0] * m.c[1].r[2];
    GLfloat Coef20 = m.c[2].r[0] * m.c[3].r[1] - m.c[3].r[0] * m.c[2].r[1];
    GLfloat Coef22 = m.c[1].r[0] * m.c[3].r[1] - m.c[3].r[0] * m.c[1].r[1];
    GLfloat Coef23 = m.c[1].r[0] * m.c[2].r[1] - m.c[2].r[0] * m.c[1].r[1];
    powergl_vec4 Fac0 = {{Coef00, Coef00, Coef02, Coef03}};
    powergl_vec4 Fac1 = {{Coef04, Coef04, Coef06, Coef07}};
    powergl_vec4 Fac2 = {{Coef08, Coef08, Coef10, Coef11}};
    powergl_vec4 Fac3 = {{Coef12, Coef12, Coef14, Coef15}};
    powergl_vec4 Fac4 = {{Coef16, Coef16, Coef18, Coef19}};
    powergl_vec4 Fac5 = {{Coef20, Coef20, Coef22, Coef23}};
    powergl_vec4 Vec0 = {{m.c[1].r[0], m.c[0].r[0], m.c[0].r[0], m.c[0].r[0]}};
    powergl_vec4 Vec1 = {{m.c[1].r[1], m.c[0].r[1], m.c[0].r[1], m.c[0].r[1]}};
    powergl_vec4 Vec2 = {{m.c[1].r[2], m.c[0].r[2], m.c[0].r[2], m.c[0].r[2]}};
    powergl_vec4 Vec3 = {{m.c[1].r[3], m.c[0].r[3], m.c[0].r[3], m.c[0].r[3]}};
    
    powergl_vec4 Inv0 =	powergl_vec4_add(powergl_vec4_mulv(Vec3, Fac2),
                                         powergl_vec4_sub(powergl_vec4_mulv(Vec1, Fac0),
							  powergl_vec4_mulv(Vec2, Fac1)));
    
    powergl_vec4 Inv1 = powergl_vec4_add(powergl_vec4_mulv(Vec3, Fac4),
                                         powergl_vec4_sub(powergl_vec4_mulv(Vec0, Fac0),
							  powergl_vec4_mulv(Vec2, Fac3)));
    
    powergl_vec4 Inv2 = powergl_vec4_add(powergl_vec4_mulv(Vec3, Fac5),
                                         powergl_vec4_sub(powergl_vec4_mulv(Vec0, Fac1),
							  powergl_vec4_mulv(Vec1, Fac3)));
    
    powergl_vec4 Inv3 = powergl_vec4_add(powergl_vec4_mulv(Vec2, Fac5),
                                         powergl_vec4_sub(powergl_vec4_mulv(Vec0, Fac2),
							  powergl_vec4_mulv(Vec1, Fac4)));
    powergl_vec4 SignA = {{+1, -1, +1, -1}};
    powergl_vec4 SignB = {{-1, +1, -1, +1}};
    powergl_mat4 Inverse;
    Inverse.c[0] = powergl_vec4_mulv(Inv0, SignA);
    Inverse.c[1] = powergl_vec4_mulv(Inv1, SignB);
    Inverse.c[2] = powergl_vec4_mulv(Inv2, SignA);
    Inverse.c[3] = powergl_vec4_mulv(Inv3, SignB);
    powergl_vec4 Row0 = {{Inverse.c[0].r[0], Inverse.c[1].r[0], Inverse.c[2].r[0], Inverse.c[3].r[0]}};
    powergl_vec4 Dot0 = powergl_vec4_mulv(m.c[0], Row0);
    GLfloat Dot1 = (Dot0.x + Dot0.y) + (Dot0.z + Dot0.w);
    GLfloat det = 1.0f / Dot1;
    powergl_mat4_muls(Inverse, det);
    return Inverse;
}

inline powergl_mat4 powergl_mat4_translate(powergl_mat4 m, powergl_vec3 v) {
#if DEBUG_OUTPUT
    printf("%s\n", __func__);
    powergl_mat4_print("in m", m);
    powergl_vec3_print("translate v", v);
#endif
    powergl_mat4 r = m;
    r.c[3].r[0] = m.c[3].r[0] + v.x;
    r.c[3].r[1] = m.c[3].r[1] + v.y;
    r.c[3].r[2] = m.c[3].r[2] + v.z;
    return r;
}

inline powergl_mat4 powergl_mat4_rot(powergl_mat4 m, float angle, powergl_vec3 v) {
#if DEBUG_OUTPUT
    printf("%s\n", __func__);
    powergl_mat4_print("in m", m);
    powergl_float_print("angle", angle);
    powergl_vec3_print("axis", v);
#endif
    GLfloat a = angle;
    GLfloat c = cosf(a);
    GLfloat s = sinf(a);
    powergl_vec3 axis = powergl_vec3_norm(v);
    powergl_vec3 temp = powergl_vec3_muls(axis, (1.0f - c));
    powergl_mat4 Rotate;
    Rotate.c[0].r[0] = c + temp.r[0] * axis.r[0];
    Rotate.c[0].r[1] = temp.r[0] * axis.r[1] + s * axis.r[2];
    Rotate.c[0].r[2] = temp.r[0] * axis.r[2] - s * axis.r[1];
    Rotate.c[1].r[0] = temp.r[1] * axis.r[0] - s * axis.r[2];
    Rotate.c[1].r[1] = c + temp.r[1] * axis.r[1];
    Rotate.c[1].r[2] = temp.r[1] * axis.r[2] + s * axis.r[0];
    Rotate.c[2].r[0] = temp.r[2] * axis.r[0] + s * axis.r[1];
    Rotate.c[2].r[1] = temp.r[2] * axis.r[1] - s * axis.r[0];
    Rotate.c[2].r[2] = c + temp.r[2] * axis.r[2];
    powergl_mat4 Result;
    Result.c[0] = powergl_vec4_add(powergl_vec4_muls(m.c[0], Rotate.c[0].r[0]),
                                   powergl_vec4_add(powergl_vec4_muls(m.c[1], Rotate.c[0].r[1]),
                                           powergl_vec4_muls(m.c[2], Rotate.c[0].r[2])));
    Result.c[1] = powergl_vec4_add(powergl_vec4_muls(m.c[0], Rotate.c[1].r[0]),
                                   powergl_vec4_add(powergl_vec4_muls(m.c[1], Rotate.c[1].r[1]),
                                           powergl_vec4_muls(m.c[2], Rotate.c[1].r[2])));
    Result.c[2] = powergl_vec4_add(powergl_vec4_muls(m.c[0], Rotate.c[2].r[0]),
                                   powergl_vec4_add(powergl_vec4_muls(m.c[1], Rotate.c[2].r[1]),
                                           powergl_vec4_muls(m.c[2], Rotate.c[2].r[2])));
    Result.c[3] = m.c[3];
    return Result;
}

/* creating view transformation */
powergl_mat4 powergl_mat4_lookatRH(powergl_vec3 eye, powergl_vec3 center, powergl_vec3 up) {
#if DEBUG_OUTPUT
    printf("%s\n", __func__);
    powergl_vec3_print("eye", eye);
    powergl_vec3_print("target", center);
    powergl_vec3_print("up", up);
#endif
    powergl_vec3 f = powergl_vec3_norm(powergl_vec3_sub(center, eye));
    powergl_vec3 s = powergl_vec3_norm(powergl_vec3_cross(f, up));
    powergl_vec3 u = powergl_vec3_cross(s, f);
    powergl_mat4 Result = powergl_mat4_ident();
    Result.c[0].r[0] = s.x;
    Result.c[1].r[0] = s.y;
    Result.c[2].r[0] = s.z;
    Result.c[0].r[1] = u.x;
    Result.c[1].r[1] = u.y;
    Result.c[2].r[1] = u.z;
    Result.c[0].r[2] = -f.x;
    Result.c[1].r[2] = -f.y;
    Result.c[2].r[2] = -f.z;
    Result.c[3].r[0] = -powergl_vec3_dot(s, eye);
    Result.c[3].r[1] = -powergl_vec3_dot(u, eye);
    Result.c[3].r[2] = powergl_vec3_dot(f, eye);
    return Result;
}

/* creating right handed and 0 to 1 depth ranged perspective projection transformation */
inline powergl_mat4 powergl_mat4_perspectiveRH(float fovy, float aspect, float zNear, float zFar) {
#if DEBUG_OUTPUT
    printf("%s\n", __func__);
    powergl_float_print("fovy", fovy);
    powergl_float_print("aspect", aspect);
    powergl_float_print("zNear", zNear);
    powergl_float_print("zFar", zFar);
#endif
    assert(fabs(aspect - FLT_EPSILON) > 0.0f);
    GLfloat tanHalfFovy = tanf(fovy / 2.0f);
    powergl_mat4 Result = powergl_mat4_zero();
    Result.c[0].r[0] = 1.0f / (aspect * tanHalfFovy);
    Result.c[1].r[1] = 1.0f / (tanHalfFovy);
    Result.c[2].r[2] = - (zFar + zNear) / (zFar - zNear);
    Result.c[2].r[3] = -1.0f;
    Result.c[3].r[2] = -(2.0f * zFar * zNear) / (zFar - zNear);
    return Result;
}

// v  = m * v, result is column vec4 not row !
inline powergl_vec4 powergl_vec4_trans(powergl_vec4 v, powergl_mat4  m) {
#if DEBUG_OUTPUT
    printf("%s\n", __func__);
    powergl_vec4_print("v", v);
    powergl_mat4_print("transform m", m);
#endif
    powergl_vec4 result;
    result.r[0] = m.c[0].r[0] * v.r[0] + m.c[1].r[0] * v.r[1] + m.c[2].r[0] * v.r[2] + m.c[3].r[0] * v.r[3];   
    result.r[1] = m.c[0].r[1] * v.r[0] + m.c[1].r[1] * v.r[1] + m.c[2].r[1] * v.r[2] + m.c[3].r[1] * v.r[3];
    result.r[2] = m.c[0].r[2] * v.r[0] + m.c[1].r[2] * v.r[1] + m.c[2].r[2] * v.r[2] + m.c[3].r[2] * v.r[3];
    result.r[3] = m.c[0].r[3] * v.r[0] + m.c[1].r[3] * v.r[1] + m.c[2].r[3] * v.r[2] + m.c[3].r[3] * v.r[3];
    return result;
}
