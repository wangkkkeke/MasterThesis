#include <math.h>
#include <stdio.h>

#include "proto_api.h"

/*
 * Finalize bonds: set bond_active from motion modes ONCE at create time.
 * Runtime bond_compute_force must NOT branch on Proxy/Free (Freeze ①).
 *
 * ACTIVE: not (both PROXY)
 * INACTIVE: both PROXY (topology kept)
 *
 * Rest length L0 = initial center distance.
 */
int bond_create(void)
{
    int b;
    int a, c;
    int mode_a, mode_b;
    double dx, dy, dz, dist;

    for (b = 0; b < bond_num; ++b) {
        a = bond_sphereA[b];
        c = bond_sphereB[b];
        if (a < 0 || c < 0 || a >= sphere_num || c >= sphere_num) {
            fprintf(stderr, "[Bond] bond_create: invalid sphere id at %d\n", b);
            return -1;
        }

        mode_a = sphere_motion_mode[a];
        mode_b = sphere_motion_mode[c];

        if (mode_a == MOTION_PROXY && mode_b == MOTION_PROXY) {
            bond_active[b] = BOND_INACTIVE;
        } else {
            bond_active[b] = BOND_ACTIVE;
        }

        dx = sphere_x[a] - sphere_x[c];
        dy = sphere_y[a] - sphere_y[c];
        dz = sphere_z[a] - sphere_z[c];
        dist = sqrt(dx * dx + dy * dy + dz * dz);
        bond_L0[b] = dist;
        bond_fn[b] = 0.0;
        bond_fs[b] = 0.0;

        printf("[Bond] create id=%d A=%d B=%d active=%d L0=%.6f\n",
               b, a, c, (int)bond_active[b], bond_L0[b]);
    }
    return 0;
}
