#include <math.h>
#include <stdio.h>

#include "proto_api.h"

/*
 * Case01 Driver FEM — Freeze / Spec:
 * Prescribe node displacement/velocity. No FEM integration.
 * Node0: x = x0 + 0.001 * sin(t); others fixed.
 */
void driver_fem_step(void)
{
    double amp = 0.001;
    double x0;
    int i;

    /* Preserve reference x of node 0 in node_mass? No.
     * Use: initial position stored once in node_ax as unused for Case01 —
     * cleaner: store rest x in a static.
     */
    static int init = 0;
    static double node0_x0 = 0.0;

    if (!init) {
        node0_x0 = node_x[0];
        init = 1;
    }

    x0 = node0_x0 + amp * sin(proto_time);

    node_x[0] = x0;
    node_vx[0] = amp * cos(proto_time);
    node_vy[0] = 0.0;
    node_vz[0] = 0.0;
    node_y[0] = node_y[0]; /* unchanged */
    node_z[0] = node_z[0];

    for (i = 1; i < node_num; ++i) {
        node_vx[i] = 0.0;
        node_vy[i] = 0.0;
        node_vz[i] = 0.0;
    }

    printf("[FEM] driver_fem_step t=%.6f node0_x=%.6f vx=%.6f\n",
           proto_time, node_x[0], node_vx[0]);
}

/* Case02+: real central difference — not implemented in Case01 */
void fem_step(void)
{
    fprintf(stderr, "[FEM] fem_step: not used in Case01 (use driver_fem_step)\n");
}
