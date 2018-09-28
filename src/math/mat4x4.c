#include "mat4x4.h"

#include <float.h>
#include <stdio.h>
#include <assert.h>

void powergl_print4x4( float m[4][4] ) {
  unsigned i, j;
  printf( "\n" );
  for ( i = 0; i < 4; ++i ) {
    printf( "[ " );
    for ( j = 0; j < 4; j++ ) {
      printf( "%f ", m[i][j] );
    }
    printf( " ]\n" );
  }
}

void powergl_zero4x4( GLfloat m[4][4] ) {
  m[0][0] = 0.0f;
  m[0][1] = 0.0f;
  m[0][2] = 0.0f;
  m[0][3] = 0.0f;
  m[1][0] = 0.0f;
  m[1][1] = 0.0f;
  m[1][2] = 0.0f;
  m[1][3] = 0.0f;
  m[2][0] = 0.0f;
  m[2][1] = 0.0f;
  m[2][2] = 0.0f;
  m[2][3] = 0.0f;
  m[3][0] = 0.0f;
  m[3][1] = 0.0f;
  m[3][2] = 0.0f;
  m[3][3] = 0.0f;
}

void powergl_ident4x4( GLfloat m[4][4] ) {
  m[0][0] = 1.0f;
  m[0][1] = 0.0f;
  m[0][2] = 0.0f;
  m[0][3] = 0.0f;
  m[1][0] = 0.0f;
  m[1][1] = 1.0f;
  m[1][2] = 0.0f;
  m[1][3] = 0.0f;
  m[2][0] = 0.0f;
  m[2][1] = 0.0f;
  m[2][2] = 1.0f;
  m[2][3] = 0.0f;
  m[3][0] = 0.0f;
  m[3][1] = 0.0f;
  m[3][2] = 0.0f;
  m[3][3] = 1.0f;
}

//this func. transforms vector v using m transformation matrix and does normalization on result vector to get H = 1
void powergl_transformvec4( const GLfloat v[4], const GLfloat m[4][4], GLfloat result[4] ) {

  result[0] = v[0] * m[0][0] + v[1] * m[1][0] + v[2] * m[2][0] + v[3] * m[3][0];
  result[1] = v[0] * m[0][1] + v[1] * m[1][1] + v[2] * m[2][1] + v[3] * m[3][1];
  result[2] = v[0] * m[0][2] + v[1] * m[1][2] + v[2] * m[2][2] + v[3] * m[3][2];
  result[3] = v[0] * m[0][3] + v[1] * m[1][3] + v[2] * m[2][3] + v[3] * m[3][3];
}

void powergl_mult4x4( GLfloat m[4][4], GLfloat n[4][4], GLfloat r[4][4] ) {
  r[0][0] = m[0][0] * n[0][0] + m[0][1] * n[1][0] + m[0][2] * n[2][0] + m[0][3] * n[3][0];
  r[0][1] = m[0][0] * n[0][1] + m[0][1] * n[1][1] + m[0][2] * n[2][1] + m[0][3] * n[3][1];
  r[0][2] = m[0][0] * n[0][2] + m[0][1] * n[1][2] + m[0][2] * n[2][2] + m[0][3] * n[3][2];
  r[0][3] = m[0][0] * n[0][3] + m[0][1] * n[1][3] + m[0][2] * n[2][3] + m[0][3] * n[3][3];

  r[1][0] = m[1][0] * n[0][0] + m[1][1] * n[1][0] + m[1][2] * n[2][0] + m[1][3] * n[3][0];
  r[1][1] = m[1][0] * n[0][1] + m[1][1] * n[1][1] + m[1][2] * n[2][1] + m[1][3] * n[3][1];
  r[1][2] = m[1][0] * n[0][2] + m[1][1] * n[1][2] + m[1][2] * n[2][2] + m[1][3] * n[3][2];
  r[1][3] = m[1][0] * n[0][3] + m[1][1] * n[1][3] + m[1][2] * n[2][3] + m[1][3] * n[3][3];

  r[2][0] = m[2][0] * n[0][0] + m[2][1] * n[1][0] + m[2][2] * n[2][0] + m[2][3] * n[3][0];
  r[2][1] = m[2][0] * n[0][1] + m[2][1] * n[1][1] + m[2][2] * n[2][1] + m[2][3] * n[3][1];
  r[2][2] = m[2][0] * n[0][2] + m[2][1] * n[1][2] + m[2][2] * n[2][2] + m[2][3] * n[3][2];
  r[2][3] = m[2][0] * n[0][3] + m[2][1] * n[1][3] + m[2][2] * n[2][3] + m[2][3] * n[3][3];

  r[3][0] = m[3][0] * n[0][0] + m[3][1] * n[1][0] + m[3][2] * n[2][0] + m[3][3] * n[3][0];
  r[3][1] = m[3][0] * n[0][1] + m[3][1] * n[1][1] + m[3][2] * n[2][1] + m[3][3] * n[3][1];
  r[3][2] = m[3][0] * n[0][2] + m[3][1] * n[1][2] + m[3][2] * n[2][2] + m[3][3] * n[3][2];
  r[3][3] = m[3][0] * n[0][3] + m[3][1] * n[1][3] + m[3][2] * n[2][3] + m[3][3] * n[3][3];

  m[0][0] = r[0][0];
  m[0][1] = r[0][1];
  m[0][2] = r[0][2];
  m[0][3] = r[0][3];

  m[1][0] = r[1][0];
  m[1][1] = r[1][1];
  m[1][2] = r[1][2];
  m[1][3] = r[1][3];

  m[2][0] = r[2][0];
  m[2][1] = r[2][1];
  m[2][2] = r[2][2];
  m[2][3] = r[2][3];

  m[3][0] = r[3][0];
  m[3][1] = r[3][1];
  m[3][2] = r[3][2];
  m[3][3] = r[3][3];

}

void powergl_trans4x4( GLfloat m[4][4] ) {
  GLfloat n[4][4];

  for ( size_t i = 0; i < 4; ++i ) {
    for ( size_t j = 0; j < 4; ++j ) {
      n[j][i] = m[i][j];
    }
  }

  for ( size_t i = 0; i < 4; ++i ) {
    for ( size_t j = 0; j < 4; ++j ) {
      m[i][j] = n[i][j];
    }
  }
}

int powergl_inv4x4( GLfloat m[16], GLfloat invOut[16] ) {
  GLfloat inv[16];
  GLfloat det = 0.0f;

  inv[ 0] =  m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
  inv[ 4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
  inv[ 8] =  m[4] * m[ 9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[ 9];
  inv[12] = -m[4] * m[ 9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[ 9];
  inv[ 1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] - m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];
  inv[ 5] =  m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] + m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
  inv[ 9] = -m[0] * m[ 9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] - m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[ 9];
  inv[13] =  m[0] * m[ 9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] + m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[ 9];
  inv[ 2] =  m[1] * m[ 6] * m[15] - m[1] * m[ 7] * m[14] - m[5] * m[2] * m[15] + m[5] * m[3] * m[14] + m[13] * m[2] * m[ 7] - m[13] * m[3] * m[ 6];
  inv[ 6] = -m[0] * m[ 6] * m[15] + m[0] * m[ 7] * m[14] + m[4] * m[2] * m[15] - m[4] * m[3] * m[14] - m[12] * m[2] * m[ 7] + m[12] * m[3] * m[ 6];
  inv[10] =  m[0] * m[ 5] * m[15] - m[0] * m[ 7] * m[13] - m[4] * m[1] * m[15] + m[4] * m[3] * m[13] + m[12] * m[1] * m[ 7] - m[12] * m[3] * m[ 5];
  inv[14] = -m[0] * m[ 5] * m[14] + m[0] * m[ 6] * m[13] + m[4] * m[1] * m[14] - m[4] * m[2] * m[13] - m[12] * m[1] * m[ 6] + m[12] * m[2] * m[ 5];
  inv[ 3] = -m[1] * m[ 6] * m[11] + m[1] * m[ 7] * m[10] + m[5] * m[2] * m[11] - m[5] * m[3] * m[10] - m[ 9] * m[2] * m[ 7] + m[ 9] * m[3] * m[ 6];
  inv[ 7] =  m[0] * m[ 6] * m[11] - m[0] * m[ 7] * m[10] - m[4] * m[2] * m[11] + m[4] * m[3] * m[10] + m[ 8] * m[2] * m[ 7] - m[ 8] * m[3] * m[ 6];
  inv[11] = -m[0] * m[ 5] * m[11] + m[0] * m[ 7] * m[ 9] + m[4] * m[1] * m[11] - m[4] * m[3] * m[ 9] - m[ 8] * m[1] * m[ 7] + m[ 8] * m[3] * m[ 5];
  inv[15] =  m[0] * m[ 5] * m[10] - m[0] * m[ 6] * m[ 9] - m[4] * m[1] * m[10] + m[4] * m[2] * m[ 9] + m[ 8] * m[1] * m[ 6] - m[ 8] * m[2] * m[ 5];

  det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

  if ( det == 0.0f ) {
    return 0;
  }

  det = 1.0f / det;

  for ( size_t i = 0; i < 16; i++ ) {
    invOut[i] = inv[i] * det;
  }

  return 1;
}

void powergl_rot4x4( GLfloat m[4][4], GLfloat n[4][4], float angle, powergl_vec3 *axis ) {
  float a, c, s, tmp, rot[9];
  powergl_vec3 temp;

  a = angle;
  c = cosf( a );
  s = sinf( a );

  powergl_normvec3( axis, axis );
  tmp = 1.0f - c;
  temp.x = axis->x * tmp;
  temp.y = axis->y * tmp;
  temp.z = axis->z * tmp;

  rot[0] = ( c + temp.x * axis->x );
  rot[1] = ( temp.x * axis->y + s * axis->z );
  rot[2] = ( temp.x * axis->z - s * axis->y );
  rot[3] = ( temp.y * axis->x - s * axis->z );
  rot[4] = ( c + temp.y * axis->y );
  rot[5] = ( temp.y * axis->z + s * axis->x );
  rot[6] = ( temp.z * axis->x + s * axis->y );
  rot[7] = ( temp.z * axis->y - s * axis->x );
  rot[8] = ( c + temp.z * axis->z );

  n[0][0] = m[0][0] * rot[0] + m[1][0] * rot[1] + m[2][0] * rot[2];
  n[0][1] = m[0][1] * rot[0] + m[1][1] * rot[1] + m[2][1] * rot[2];
  n[0][2] = m[0][2] * rot[0] + m[1][2] * rot[1] + m[2][2] * rot[2];

  n[1][0] = m[0][0] * rot[3] + m[1][0] * rot[4] + m[2][0] * rot[5];
  n[1][1] = m[0][1] * rot[3] + m[1][1] * rot[4] + m[2][1] * rot[5];
  n[1][2] = m[0][2] * rot[3] + m[1][2] * rot[4] + m[2][2] * rot[5];

  n[2][0] = m[0][0] * rot[6] + m[1][0] * rot[7] + m[2][0] * rot[8];
  n[2][1] = m[0][1] * rot[6] + m[1][1] * rot[7] + m[2][1] * rot[8];
  n[2][2] = m[0][2] * rot[6] + m[1][2] * rot[7] + m[2][2] * rot[8];

  m[0][0] = n[0][0];
  m[0][1] = n[0][1];
  m[0][2] = n[0][2];

  m[1][0] = n[1][0];
  m[1][1] = n[1][1];
  m[1][2] = n[1][2];

  m[2][0] = n[2][0];
  m[2][1] = n[2][1];
  m[2][2] = n[2][2];
}


/* creating rigth handed and 0 to 1 depth ranged perspective projection transformation */
void powergl_perspectiveRH( GLfloat projection[4][4], float fovy, float aspect, float zNear, float zFar ) {
  assert( fabs( aspect - FLT_EPSILON ) > 0.0f );
  const float tanHalfFovy = tanf( fovy / 2.0f );
  powergl_zero4x4( projection );
  projection[0][0] = 1.0f / ( aspect * tanHalfFovy );
  projection[1][1] = 1.0f / ( tanHalfFovy );
  projection[2][3] = -1.0f;
  /* depth range 0 to 1
     projection[2][2] = zFar / (zFar - zNear);
     projection[3][2] = -(zFar * zNear) / (zFar - zNear);
  */
  /* depth range -1 to 1*/
  projection[2][2] = - ( zFar + zNear ) / ( zFar - zNear );
  projection[3][2] = - ( 2.0f * zFar * zNear ) / ( zFar - zNear );

}

/* creating view transformation */
void powergl_lookat( GLfloat view[4][4], powergl_vec3 *eye, powergl_vec3 *target, powergl_vec3 *up ) {
  powergl_vec3 f;
  powergl_vec3 s;
  powergl_vec3 u;

  powergl_subvec3( target, eye, &f );
  powergl_normvec3( &f, &f );

  powergl_crossvec3( &f, up, &s );
  powergl_normvec3( &s, &s );

  powergl_crossvec3( &s, &f, &u );

  powergl_ident4x4( view );

  view[0][0] = s.x;
  view[1][0] = s.y;
  view[2][0] = s.z;
  view[0][1] = u.x;
  view[1][1] = u.y;
  view[2][1] = u.z;
  view[0][2] = -f.x;
  view[1][2] = -f.y;
  view[2][2] = -f.z;
  view[3][0] = -powergl_dotvec3( &s, eye );
  view[3][1] = -powergl_dotvec3( &u, eye );
  view[3][2] = powergl_dotvec3( &f, eye );
}
