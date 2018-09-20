#include "vec3.h"
#include <stdio.h>

void powergl_printvec3( powergl_vec3 *m ) {
  printf( "\n[ %f , %f , %f ]\n", m->x, m->y, m->z );
}
float powergl_dotvec3( const powergl_vec3 *m, const powergl_vec3 *n ) {
  return ( m->x * n->x ) + ( m->y * n->y ) + ( m->z * n->z );
}
float powergl_lenvec3( const powergl_vec3 *m ) {
  return sqrtf( powergl_dotvec3( m, m ) );
}
void powergl_crossvec3( const powergl_vec3 *m, const powergl_vec3 *n, powergl_vec3 *r ) {
  r->x = m->y * n->z - n->y * m->z;
  r->y = m->z * n->x - n->z * m->x;
  r->z = m->x * n->y - n->x * m->y;
}
void powergl_mulvec3( const powergl_vec3 *m, const powergl_vec3 *n, powergl_vec3 *r ) {
  r->x = m->x * n->x;
  r->y = m->y * n->y;
  r->z = m->z * n->z;
}
void powergl_subvec3( const powergl_vec3 *m, const powergl_vec3 *n, powergl_vec3 *r ) {
  r->x = m->x - n->x;
  r->y = m->y - n->y;
  r->z = m->z - n->z;
}
void powergl_normvec3( const powergl_vec3 *m, powergl_vec3 *r ) {
  float length;
  length = powergl_lenvec3( m );
  r->x = m->x / length;
  r->y = m->y / length;
  r->z = m->z / length;
}
