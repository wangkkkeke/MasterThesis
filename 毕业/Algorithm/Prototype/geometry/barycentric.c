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
 * Barycentric coordinates of point P in tet (1,2,3,4).
 * N1 volume opposite node1, etc.
 */
void barycentric(double px, double py, double pz,
                 double x1, double y1, double z1,
                 double x2, double y2, double z2,
                 double x3, double y3, double z3,
                 double x4, double y4, double z4,
                 double *n1, double *n2, double *n3, double *n4)
{
    double v;
    double v1, v2, v3, v4;
    const double eps = 1.0e-30;

    v = tet_volume6(x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4);
    if (v > -eps && v < eps) {
        fprintf(stderr, "[Sphere] barycentric: degenerate tet\n");
        *n1 = *n2 = *n3 = *n4 = 0.0;
        return;
    }

    /* Ni = V(P, opposite face) / V */
    v1 = tet_volume6(px, py, pz, x2, y2, z2, x3, y3, z3, x4, y4, z4);
    v2 = tet_volume6(x1, y1, z1, px, py, pz, x3, y3, z3, x4, y4, z4);
    v3 = tet_volume6(x1, y1, z1, x2, y2, z2, px, py, pz, x4, y4, z4);
    v4 = tet_volume6(x1, y1, z1, x2, y2, z2, x3, y3, z3, px, py, pz);

    *n1 = v1 / v;
    *n2 = v2 / v;
    *n3 = v3 / v;
    *n4 = v4 / v;
}
