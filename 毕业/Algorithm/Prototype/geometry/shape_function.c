#include <stdio.h>

#include "proto_api.h"

/*
 * Scalar shape-function interpolation on a tet:
 * u = N1*u1 + N2*u2 + N3*u3 + N4*u4
 */
void shape_function_tet(double n1, double n2, double n3, double n4,
                        double u1, double u2, double u3, double u4,
                        double *u)
{
    if (u == 0) {
        fprintf(stderr, "[Sphere] shape_function_tet: null output\n");
        return;
    }
    *u = n1 * u1 + n2 * u2 + n3 * u3 + n4 * u4;
}
