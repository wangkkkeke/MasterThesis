#include <stdio.h>

#include "proto_api.h"

/*
 * Case03+: search Host Tet for EVERY sphere (before classification).
 * If inside a tet: store hostTetID and N1..N4.
 * If not: hostTet = -1 (candidate FREE / DEM).
 *
 * Does NOT set motion_mode (that is sphere_classify via inheritance).
 */
int sphere_find_host_tet(void)
{
    int s, t;
    int found;
    int n1i, n2i, n3i, n4i;
    double n1, n2, n3, n4;
    int n_found = 0;

    for (s = 0; s < sphere_num; ++s) {
        found = 0;
        sphere_hostTet[s] = -1;
        sphere_N1[s] = sphere_N2[s] = sphere_N3[s] = sphere_N4[s] = 0.0;

        for (t = 0; t < tet_num; ++t) {
            n1i = tet_node1[t];
            n2i = tet_node2[t];
            n3i = tet_node3[t];
            n4i = tet_node4[t];

            if (point_in_tet(sphere_x[s], sphere_y[s], sphere_z[s],
                             node_x[n1i], node_y[n1i], node_z[n1i],
                             node_x[n2i], node_y[n2i], node_z[n2i],
                             node_x[n3i], node_y[n3i], node_z[n3i],
                             node_x[n4i], node_y[n4i], node_z[n4i])) {
                barycentric(sphere_x[s], sphere_y[s], sphere_z[s],
                            node_x[n1i], node_y[n1i], node_z[n1i],
                            node_x[n2i], node_y[n2i], node_z[n2i],
                            node_x[n3i], node_y[n3i], node_z[n3i],
                            node_x[n4i], node_y[n4i], node_z[n4i],
                            &n1, &n2, &n3, &n4);
                sphere_hostTet[s] = t;
                sphere_N1[s] = n1;
                sphere_N2[s] = n2;
                sphere_N3[s] = n3;
                sphere_N4[s] = n4;
                found = 1;
                n_found++;
                break;
            }
        }

        if (found) {
            printf("[Sphere] id=%d hostTet=%d N=%.4f %.4f %.4f %.4f\n",
                   s, sphere_hostTet[s],
                   sphere_N1[s], sphere_N2[s], sphere_N3[s], sphere_N4[s]);
        }
    }

    printf("[Sphere] find_host_tet: found=%d / %d\n", n_found, sphere_num);
    return 0;
}
