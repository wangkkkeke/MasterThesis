#include <stdio.h>

#include "proto_api.h"

/*
 * Stage 8 — Freeze ③⑤:
 * Only modifies Node Force.
 * Does not modify Sphere position / velocity / force.
 * Reads MOTION_PROXY sphere force as Reaction.
 * Fi += Ni * Reaction
 *
 * FEM solver never sees Sphere; coupling only.
 */
void force_mapping_proxy_to_tet(void)
{
    int s;
    int t;
    int n1i, n2i, n3i, n4i;
    double n1, n2, n3, n4;
    double rx, ry, rz;

    for (s = 0; s < sphere_num; ++s) {
        if (sphere_motion_mode[s] != MOTION_PROXY) {
            continue;
        }

        t = sphere_hostTet[s];
        if (t < 0 || t >= tet_num) {
            fprintf(stderr, "[Mapping] invalid hostTet for sphere %d\n", s);
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

        rx = sphere_fx[s];
        ry = sphere_fy[s];
        rz = sphere_fz[s];

        node_fx[n1i] += n1 * rx;
        node_fy[n1i] += n1 * ry;
        node_fz[n1i] += n1 * rz;

        node_fx[n2i] += n2 * rx;
        node_fy[n2i] += n2 * ry;
        node_fz[n2i] += n2 * rz;

        node_fx[n3i] += n3 * rx;
        node_fy[n3i] += n3 * ry;
        node_fz[n3i] += n3 * rz;

        node_fx[n4i] += n4 * rx;
        node_fy[n4i] += n4 * ry;
        node_fz[n4i] += n4 * rz;

        printf("[Mapping] proxy %d R=(%.6e,%.6e,%.6e) -> nodes\n",
               s, rx, ry, rz);
    }
}
