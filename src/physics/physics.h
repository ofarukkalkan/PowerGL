#ifndef _powergl_physics_h
#define _powergl_physics_h

#include "../math/vec3.h"
#include "../math/mat4x4.h"


typedef struct powergl_impulse_t
{
    powergl_vec3 force;
    float time;
} powergl_impulse;

typedef struct powergl_rigidbody_t
{
    float mass;
    powergl_vec3 vel;
    powergl_vec3 pos;
    powergl_impulse imps[3];
    int n_imp;
} powergl_rigidbody;

void powergl_apply_impulse(powergl_rigidbody *body, powergl_vec3 force, float time);
void powergl_simulate_physics(powergl_rigidbody *body, GLfloat m[4][4], float delta_time);

#endif
