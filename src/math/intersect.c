#include "intersect.h"
#include "mat4x4.h"
#include <stdio.h>
#include <float.h>

int powergl_intersect_ray_tri_mesh(powergl_vec3 *mesh, int n_vertex, powergl_mat4 mvp, powergl_vec2 event_pos, powergl_vec4 vp, powergl_vec3 *P, int cull )
{
  powergl_vec3 edge1 = powergl_vec3_zeros();
  powergl_vec3 edge2 = powergl_vec3_zeros();
  powergl_vec3 tvec = powergl_vec3_zeros();
  powergl_vec3 pvec = powergl_vec3_zeros();
  powergl_vec3 qvec = powergl_vec3_zeros();
  powergl_vec3 O = powergl_vec3_zeros();
  powergl_vec3 D = powergl_vec3_zeros();
  powergl_vec3 far = powergl_vec3_zeros();
  powergl_vec3 near = powergl_vec3_zeros();
  powergl_vec3 NDC = powergl_vec3_zeros();
  powergl_vec3 tmp = powergl_vec3_zeros();
    
  float eps = FLT_EPSILON;
  float det = 0.0f;
  float inv_det = 0.0f;
  NDC.x = event_pos.x;
  NDC.y = vp.w - event_pos.y; // vp.w does not mean the w component of direction vector. it just used to get 3.index
  NDC.z = -1.0f; // near plane z
  near = powergl_unproject(NDC, mvp, vp);
  NDC.z = 1.0f; // far plane z
  far = powergl_unproject(NDC, mvp, vp);
  tmp = powergl_vec3_sub(far, near);
  D = powergl_vec3_norm(tmp); // D for direction of ray
  O = near; // O for origin of ray

  
  for(size_t i = 0; i < n_vertex / 3; i++)
    {
      powergl_vec3 vert0 = mesh[i * 3 + 0];
      powergl_vec3 vert1 = mesh[i * 3 + 1];
      powergl_vec3 vert2 = mesh[i * 3 + 2];
      edge1 = powergl_vec3_sub(vert1, vert0);
      edge2 = powergl_vec3_sub(vert2, vert0);
      pvec = powergl_vec3_cross(D, edge2);
      det = powergl_vec3_dot(edge1, pvec );
      if( cull )
	{
	  if( det < eps )
	    {
	      fprintf(stderr, "cull test failed det = %f eps = %f\n", det, eps);
	      continue;
	    }
	  tvec = powergl_vec3_sub(O, vert0);
	  P->x = powergl_vec3_dot(tvec, pvec );
	  if( P->x < 0.0f || P->x > det )
	    {
	      fprintf(stderr, "U test failed\n");
	      continue;
	    }
	  qvec = powergl_vec3_cross( tvec, edge1);
	  P->y = powergl_vec3_dot( D, qvec );
	  if( P->y < 0.0f || ( P->x + P->y ) > det )
	    {
	      fprintf(stderr, "V test failed\n");
	      continue;
	    }
	  P->z = powergl_vec3_dot( edge2, qvec );
	  inv_det = 1.0f / det;
	  P->x *= inv_det;
	  P->y *= inv_det;
	  P->z *= inv_det;
	}
      else
	{
	  if( det > - eps && det < eps )
	    {
	      continue;
	    }
	  inv_det = 1.0f / det;
	  tvec = powergl_vec3_sub(O, vert0);
	  P->x = powergl_vec3_dot(tvec, pvec ) * inv_det;
	  if( P->x < 0.0f || P->x > 1.0f )
	    {
	      continue;
	    }
	  qvec = powergl_vec3_cross(tvec, edge1);
	  P->y = powergl_vec3_dot(D, qvec ) * inv_det;
	  if( P->y < 0.0f || P->x + P->y > 1.0f )
	    {
	      continue;
	    }
	  P->z = powergl_vec3_dot( edge2, qvec ) * inv_det;
	}
      return 1;
    }
  return 0;
}
