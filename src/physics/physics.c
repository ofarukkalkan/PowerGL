#include "physics.h"
#include <stdio.h>

void powergl_apply_impulse(powergl_rigidbody *body, powergl_vec3 force, float time)
{
    body->n_imp++;
    body->imps[body->n_imp - 1].force = force;
    body->imps[body->n_imp - 1].time = time;
}

void powergl_simulate_physics(powergl_rigidbody *body, GLfloat m[4][4], float delta_time)
{
    float delta_vel_x = 0.0f;
    float delta_vel_y = 0.0f;
    float delta_vel_z = 0.0f;
    // apply forces that affect just this object
    for(int j=0; j < body->n_imp; j++)
        {
            if( body->imps[j].time > 0.0f )
                {
                    if( body->imps[j].time < delta_time )
                        {
                            delta_vel_x += ( body->imps[j].force.x * body->imps[j].time ) / body->mass;
                            delta_vel_y += ( body->imps[j].force.y * body->imps[j].time ) / body->mass;
                            delta_vel_z += ( body->imps[j].force.z * body->imps[j].time ) / body->mass;
                            body->imps[j].time = 0.0f;
                        }
                    else
                        {
                            delta_vel_x += ( body->imps[j].force.x * delta_time ) / body->mass;
                            delta_vel_y += ( body->imps[j].force.y * delta_time ) / body->mass;
                            delta_vel_z += ( body->imps[j].force.z * delta_time ) / body->mass;
                            body->imps[j].time -= delta_time;
                        }
                }
        }
    // apply global forces like gravity i.e.
    delta_vel_z += (-9.8f * delta_time ) / body->mass;
    // check collisions before moving object
    // translate object after applying impulses
    powergl_vec3 delta_pos = {body->vel.x * delta_time,
                              body->vel.y * delta_time,
                              body->vel.z * delta_time
                             };
    powergl_translate4x4(m, &delta_pos);
    body->vel.x += delta_vel_x;
    body->vel.y += delta_vel_y;
    body->vel.z += delta_vel_z;
}
