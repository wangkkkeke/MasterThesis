#ifndef IBOND_MATH_H
#define IBOND_MATH_H

#include "../Real.h"

typedef struct {
    Real x, y, z;
} IbondVec3;

static IbondVec3 ibond_vec3(Real x, Real y, Real z)
{
    IbondVec3 v;
    v.x = x; v.y = y; v.z = z;
    return v;
}

static IbondVec3 ibond_vec3_sub(IbondVec3 a, IbondVec3 b)
{
    return ibond_vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

static IbondVec3 ibond_vec3_add(IbondVec3 a, IbondVec3 b)
{
    return ibond_vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

static Real ibond_vec3_dot(IbondVec3 a, IbondVec3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

static IbondVec3 ibond_vec3_scale(IbondVec3 a, Real s)
{
    return ibond_vec3(a.x * s, a.y * s, a.z * s);
}

static Real ibond_vec3_norm(IbondVec3 a)
{
    return (Real)sqrt((double)(a.x * a.x + a.y * a.y + a.z * a.z));
}

#endif
