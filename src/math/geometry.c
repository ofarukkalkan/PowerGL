#include "geometry.h"
#include "mat4x4.h"
#include <stdio.h>
#include <float.h>

int powergl_test_ray_tri_mesh(powergl_vec3 *mesh, int n_vertex, float mvp[4][4], float event_pos[2], float vp[4], powergl_vec3 *P, int cull )
{
    powergl_vec3 edge1 = (powergl_vec3)
    {
        0.0f, 0.0f, 0.0f
    };
    powergl_vec3 edge2 = (powergl_vec3)
    {
        0.0f, 0.0f, 0.0f
    };
    powergl_vec3 tvec = (powergl_vec3)
    {
        0.0f, 0.0f, 0.0f
    };
    powergl_vec3 pvec = (powergl_vec3)
    {
        0.0f, 0.0f, 0.0f
    };
    powergl_vec3 qvec = (powergl_vec3)
    {
        0.0f, 0.0f, 0.0f
    };
    powergl_vec3 O = (powergl_vec3)
    {
        0.0f, 0.0f, 0.0f
    };
    powergl_vec3 D = (powergl_vec3)
    {
        0.0f, 0.0f, 0.0f
    };
    powergl_vec3 far = (powergl_vec3)
    {
        0.0f, 0.0f, 0.0f
    };
    powergl_vec3 near = (powergl_vec3)
    {
        0.0f, 0.0f, 0.0f
    };
    powergl_vec3 NDC = (powergl_vec3)
    {
        0.0f, 0.0f, 0.0f
    };
    powergl_vec3 tmp = (powergl_vec3)
    {
        0.0f, 0.0f, 0.0f
    };
    float eps = FLT_EPSILON;
    float det = 0.0f;
    float inv_det = 0.0f;
    NDC.x = event_pos[0];
    NDC.y = vp[3] - event_pos[1];
    NDC.z = -1.0f;
    powergl_unproject(&near, &NDC, mvp, vp);
    NDC.z = 1.0f;
    powergl_unproject(&far, &NDC, mvp, vp);
    powergl_subvec3(&far, &near, &tmp);
    powergl_normvec3(&tmp, &D);
    O = near;
    //powergl_printvec3(&D);
    //powergl_printvec3(&O);
    for(int i = 0; i < n_vertex / 3; i++)
        {
            powergl_vec3 *vert0 = &mesh[i * 3 + 0];
            powergl_vec3 *vert1 = &mesh[i * 3 + 1];
            powergl_vec3 *vert2 = &mesh[i * 3 + 2];
            powergl_subvec3(vert1, vert0, &edge1);
            powergl_subvec3(vert2, vert0, &edge2);
            powergl_crossvec3( &D, &edge2, &pvec );
            det = powergl_dotvec3( &edge1, &pvec );
            if( cull )
                {
                    if( det < eps )
                        {
                            printf("cull test failed det = %f eps = %f\n", det, eps);
                            continue;
                        }
                    powergl_subvec3(&O,vert0, &tvec);
                    P->x = powergl_dotvec3( &tvec, &pvec );
                    if( P->x < 0.0f || P->x > det )
                        {
                            printf("U test failed\n");
                            continue;
                        }
                    powergl_crossvec3( &tvec, &edge1, &qvec );
                    P->y = powergl_dotvec3( &D, &qvec );
                    if( P->y < 0.0f || ( P->x + P->y ) > det )
                        {
                            printf("V test failed\n");
                            continue;
                        }
                    P->z = powergl_dotvec3( &edge2, &qvec );
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
                    powergl_subvec3( &O, vert0, &tvec);
                    P->x = powergl_dotvec3( &tvec, &pvec ) * inv_det;
                    if( P->x < 0.0f || P->x > 1.0f )
                        {
                            continue;
                        }
                    powergl_crossvec3( &tvec, &edge1, &qvec );
                    P->y = powergl_dotvec3( &D, &qvec ) * inv_det;
                    if( P->y < 0.0f || P->x + P->y > 1.0f )
                        {
                            continue;
                        }
                    P->z = powergl_dotvec3( &edge2, &qvec ) * inv_det;
                }
            return 1;
        }
    return 0;
}
