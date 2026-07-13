/*
 * Stage 2 smoke test: geometry (barycentric / point_in_tet / shape_function)
 */
#include <stdio.h>
#include <math.h>

#include "proto_api.h"

static int nearly_eq(double a, double b, double tol)
{
    return fabs(a - b) <= tol;
}

int main(void)
{
    double n1, n2, n3, n4;
    double u;
    int inside;

    /* Unit tet: (0,0,0)(1,0,0)(0,1,0)(0,0,1) */
    double x1 = 0, y1 = 0, z1 = 0;
    double x2 = 1, y2 = 0, z2 = 0;
    double x3 = 0, y3 = 1, z3 = 0;
    double x4 = 0, y4 = 0, z4 = 1;

    printf("[Driver] Stage2 start\n");

    barycentric(0.25, 0.25, 0.25,
                x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4,
                &n1, &n2, &n3, &n4);

    printf("[Sphere] barycentric N=%.4f %.4f %.4f %.4f sum=%.4f\n",
           n1, n2, n3, n4, n1 + n2 + n3 + n4);

    if (!nearly_eq(n1 + n2 + n3 + n4, 1.0, 1e-9)) {
        fprintf(stderr, "[Driver] Stage2 FAIL: sum N != 1\n");
        return 1;
    }
    if (!nearly_eq(n1, 0.25, 1e-9) || !nearly_eq(n2, 0.25, 1e-9) ||
        !nearly_eq(n3, 0.25, 1e-9) || !nearly_eq(n4, 0.25, 1e-9)) {
        fprintf(stderr, "[Driver] Stage2 FAIL: expected equal N=0.25\n");
        return 1;
    }

    inside = point_in_tet(0.25, 0.25, 0.25,
                          x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4);
    if (!inside) {
        fprintf(stderr, "[Driver] Stage2 FAIL: centroid not inside\n");
        return 1;
    }

    inside = point_in_tet(2.0, 0.0, 0.0,
                          x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4);
    if (inside) {
        fprintf(stderr, "[Driver] Stage2 FAIL: exterior point reported inside\n");
        return 1;
    }

    shape_function_tet(n1, n2, n3, n4, 0.0, 1.0, 2.0, 3.0, &u);
    printf("[Sphere] shape_function u=%.4f\n", u);
    if (!nearly_eq(u, 1.5, 1e-9)) {
        fprintf(stderr, "[Driver] Stage2 FAIL: interpolation\n");
        return 1;
    }

    printf("[Driver] Stage2 ok\n");
    return 0;
}
