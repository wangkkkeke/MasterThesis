#include <stdio.h>

#include "proto_api.h"

/*
 * Classification by inheritance (Case03+):
 *
 *   Host Tet  ->  tet_region  ->  sphere_region / motion_mode
 *
 * Rules:
 *   hostTet >= 0 && tet_region == REGION_FEM  -> MOTION_PROXY
 *   hostTet >= 0 && tet_region == REGION_DEM  -> MOTION_FREE
 *   hostTet <  0                              -> REGION_DEM, MOTION_FREE
 *
 * Forbidden: classify by raw geometric coordinates alone.
 */
void sphere_classify(void)
{
    int i;
    int t;
    int n_proxy = 0;
    int n_free = 0;

    for (i = 0; i < sphere_num; ++i) {
        t = sphere_hostTet[i];
        if (t >= 0 && t < tet_num) {
            sphere_region[i] = tet_region[t];
            if (tet_region[t] == REGION_FEM) {
                sphere_motion_mode[i] = MOTION_PROXY;
                n_proxy++;
            } else {
                sphere_motion_mode[i] = MOTION_FREE;
                n_free++;
            }
        } else {
            sphere_region[i] = REGION_DEM;
            sphere_motion_mode[i] = MOTION_FREE;
            sphere_hostTet[i] = -1;
            sphere_N1[i] = sphere_N2[i] = sphere_N3[i] = sphere_N4[i] = 0.0;
            n_free++;
        }
    }

    printf("[Sphere] classify (HostTet->Region->Mode): proxy=%d free=%d\n",
           n_proxy, n_free);
}
