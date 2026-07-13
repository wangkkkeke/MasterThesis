#include <stdio.h>

#include "proto_api.h"

/*
 * Stage 5 — Architecture Freeze:
 * Only interpolate Position / Velocity from host Tet nodes.
 * No force, no mapping, no bond.
 */
void proxy_update(void)
{
    int s;
    int t;
    int n1i, n2i, n3i, n4i;
    double n1, n2, n3, n4;
    double px, py, pz;
    double vx, vy, vz;

    for (s = 0; s < sphere_num; ++s) {
        if (sphere_motion_mode[s] != MOTION_PROXY) {
            continue;
        }

        t = sphere_hostTet[s];
        if (t < 0 || t >= tet_num) {
            fprintf(stderr, "[Sphere] proxy_update: invalid hostTet for %d\n", s);
            continue;
        }

        n1i = tet_node1[t];
        n2i = tet_node2[t];
        n3i = tet_node3[t];
        n4i = tet_node4[t];

        n1 = sphere_N1[s];
        n2 = sphere_N2[s];
        n3 = sphere_N3[s];
        n4 = sphere_N4[s];

        shape_function_tet(n1, n2, n3, n4,
                           node_x[n1i], node_x[n2i], node_x[n3i], node_x[n4i], &px);
        shape_function_tet(n1, n2, n3, n4,
                           node_y[n1i], node_y[n2i], node_y[n3i], node_y[n4i], &py);
        shape_function_tet(n1, n2, n3, n4,
                           node_z[n1i], node_z[n2i], node_z[n3i], node_z[n4i], &pz);

        shape_function_tet(n1, n2, n3, n4,
                           node_vx[n1i], node_vx[n2i], node_vx[n3i], node_vx[n4i], &vx);
        shape_function_tet(n1, n2, n3, n4,
                           node_vy[n1i], node_vy[n2i], node_vy[n3i], node_vy[n4i], &vy);
        shape_function_tet(n1, n2, n3, n4,
                           node_vz[n1i], node_vz[n2i], node_vz[n3i], node_vz[n4i], &vz);

        sphere_x[s] = px;
        sphere_y[s] = py;
        sphere_z[s] = pz;
        sphere_vx[s] = vx;
        sphere_vy[s] = vy;
        sphere_vz[s] = vz;
    }
}
