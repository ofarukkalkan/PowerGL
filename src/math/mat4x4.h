#ifndef _powergl_mat4x4_h
#define _powergl_mat4x4_h
#define GL_GLEXT_PROTOTYPES
#include <GL/glcorearb.h>
#include "vec3.h"
void powergl_print4x4( float m[4][4] );
void powergl_zero4x4( GLfloat m[4][4] );
void powergl_ident4x4( GLfloat m[4][4] );
void powergl_mult4x4( GLfloat m[4][4], GLfloat n[4][4], GLfloat r[4][4] );
void powergl_trans4x4( GLfloat m[4][4] );
void powergl_transformvec4( const GLfloat v[4], const GLfloat m[4][4], GLfloat result[4] );
void powergl_rot4x4( GLfloat m[4][4], GLfloat n[4][4], float angle, powergl_vec3 *axis );
int powergl_inv4x4( GLfloat m[16], GLfloat n[16] );
void powergl_perspectiveRH( GLfloat m[4][4], GLfloat yfov, GLfloat aspect, GLfloat znear, GLfloat zfar );
void powergl_lookat( GLfloat view[4][4], powergl_vec3 *eye, powergl_vec3 *target, powergl_vec3 *up );
#endif
