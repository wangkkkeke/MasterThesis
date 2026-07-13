#include <math.h>
#include <stdio.h>

#include "proto_api.h"

/* Signed volume of tet (p1,p2,p3,p4); 6*V */
static double tet_volume6(
    double x1, double y1, double z1,
    double x2, double y2, double z2,
    double x3, double y3, double z3,
    double x4, double y4, double z4)
{
    double a11 = x2 - x1;
    double a12 = y2 - y1;
    double a13 = z2 - z1;
    double a21 = x3 - x1;
    double a22 = y3 - y1;
    double a23 = z3 - z1;
    double a31 = x4 - x1;
    double a32 = y4 - y1;
    double a33 = z4 - z1;

    return a11 * (a22 * a33 - a23 * a32)
         - a12 * (a21 * a33 - a23 * a31)
         + a13 * (a21 * a32 - a22 * a31);
}

/*
 * Return 1 if point is inside tet (barycentric all in [0,1], sum~1).
 * Uses relative tolerance on volume.
 */
int point_in_tet(double px, double py, double pz,
                 double x1, double y1, double z1,
                 double x2, double y2, double z2,
                 double x3, double y3, double z3,
                 double x4, double y4, double z4)
{
    double n1, n2, n3, n4;
    const double eps = 1.0e-12;

    barycentric(px, py, pz,
                x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4,
                &n1, &n2, &n3, &n4);

    if (n1 < -eps || n2 < -eps || n3 < -eps || n4 < -eps) {
        return 0;
    }
    if (n1 > 1.0 + eps || n2 > 1.0 + eps || n3 > 1.0 + eps || n4 > 1.0 + eps) {
        return 0;
    }
    return 1;
}
