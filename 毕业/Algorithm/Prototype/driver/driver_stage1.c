/*
 * Stage 1 smoke test: SoA + Memory + Initialize / Finalize
 * Compile: make stage1
 */
#include <stdio.h>
#include <stdlib.h>

#include "proto_api.h"

int main(void)
{
    int i;

    printf("[Driver] Stage1 start\n");

    if (prototype_initialize(8, 2, 4, 4) != 0) {
        return 1;
    }

    /* Write through SoA to verify contiguous arrays are usable */
    node_num = 4;
    for (i = 0; i < node_num; ++i) {
        node_x[i] = (double)i;
        node_y[i] = 0.0;
        node_z[i] = 0.0;
        node_mass[i] = 1.0;
    }

    sphere_num = 2;
    sphere_x[0] = 0.1;
    sphere_y[0] = 0.1;
    sphere_z[0] = 0.1;
    sphere_motion_mode[0] = MOTION_PROXY;
    sphere_x[1] = 0.5;
    sphere_y[1] = 0.1;
    sphere_z[1] = 0.1;
    sphere_motion_mode[1] = MOTION_FREE;

    bond_num = 1;
    bond_sphereA[0] = 0;
    bond_sphereB[0] = 1;
    bond_active[0] = BOND_ACTIVE;

    printf("[Sphere] id=0 mode=%d x=%.3f\n",
           sphere_motion_mode[0], sphere_x[0]);
    printf("[Sphere] id=1 mode=%d x=%.3f\n",
           sphere_motion_mode[1], sphere_x[1]);
    printf("[Bond] id=0 A=%d B=%d active=%d\n",
           bond_sphereA[0], bond_sphereB[0], (int)bond_active[0]);
    printf("[FEM] node0 x=%.3f mass=%.3f\n", node_x[0], node_mass[0]);

    prototype_finalize();

    printf("[Driver] Stage1 ok\n");
    return 0;
}
