#include <math.h>
#include <stdio.h>

#include "proto_api.h"

/*
 * O(N^2) neighbor search. No Cell Linked List in Case03.
 * If bond_num already set with valid pairs (Case01/02 manual), keep them.
 * Otherwise fill bonds for all pairs with distance < proto_bond_rcut.
 */
int bond_search_neighbor(void)
{
    int i, j;
    int count = 0;
    double dx, dy, dz, dist, rcut;

    if (bond_num > 0 && bond_sphereA != 0 && bond_sphereB != 0 &&
        bond_sphereA[0] >= 0 && bond_sphereB[0] >= 0) {
        printf("[Bond] bond_search_neighbor: keep existing %d bonds\n", bond_num);
        return 0;
    }

    rcut = proto_bond_rcut;
    if (rcut <= 0.0) {
        rcut = 2.2 * proto_sphere_radius;
        if (rcut <= 0.0) {
            rcut = 0.25;
        }
        proto_bond_rcut = rcut;
    }

    bond_num = 0;
    for (i = 0; i < sphere_num; ++i) {
        for (j = i + 1; j < sphere_num; ++j) {
            dx = sphere_x[i] - sphere_x[j];
            dy = sphere_y[i] - sphere_y[j];
            dz = sphere_z[i] - sphere_z[j];
            dist = sqrt(dx * dx + dy * dy + dz * dz);
            if (dist < rcut - 1.0e-12 || fabs(dist - rcut) <= 1.0e-12) {
                if (count >= proto_cap_bond) {
                    fprintf(stderr, "[Bond] search overflow cap=%d\n", proto_cap_bond);
                    bond_num = count;
                    return -1;
                }
                bond_sphereA[count] = i;
                bond_sphereB[count] = j;
                bond_kn[count] = 1.0e3;
                bond_ks[count] = 0.0;
                bond_active[count] = BOND_ACTIVE; /* finalized in bond_create */
                count++;
            }
        }
    }

    bond_num = count;
    printf("[Bond] bond_search_neighbor: O(N^2) n_bond=%d rcut=%.4f\n",
           bond_num, rcut);
    return 0;
}
