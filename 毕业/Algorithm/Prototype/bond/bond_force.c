#include <math.h>
#include <stdio.h>

#include "proto_api.h"

/*
 * Stage 6 — Architecture Freeze ①:
 * Bond does not know Proxy / Free.
 * Only bond_active gates computation.
 * Writes action-reaction forces into both spheres' force arrays.
 *
 * First version: normal linear spring only.
 * Fn = Kn * (L - L0); direction along A<-B.
 * Tangential: Fs=0 (no history in Case01).
 */
void bond_compute_force(void)
{
    int b;
    int a, c;
    double dx, dy, dz, L, stretch;
    double nx, ny, nz;
    double fn;
    double fx, fy, fz;
    const double eps = 1.0e-30;

    for (b = 0; b < bond_num; ++b) {
        if (bond_active[b] != BOND_ACTIVE) {
            bond_fn[b] = 0.0;
            bond_fs[b] = 0.0;
            continue;
        }

        a = bond_sphereA[b];
        c = bond_sphereB[b];

        dx = sphere_x[a] - sphere_x[c];
        dy = sphere_y[a] - sphere_y[c];
        dz = sphere_z[a] - sphere_z[c];
        L = sqrt(dx * dx + dy * dy + dz * dz);
        if (L < eps) {
            bond_fn[b] = 0.0;
            bond_fs[b] = 0.0;
            continue;
        }

        nx = dx / L;
        ny = dy / L;
        nz = dz / L;

        stretch = L - bond_L0[b];
        fn = bond_kn[b] * stretch;
        bond_fn[b] = fn;
        bond_fs[b] = 0.0;

        /* Force on A along +n when stretch>0 (tension pulls A toward B => -n) */
        fx = -fn * nx;
        fy = -fn * ny;
        fz = -fn * nz;

        sphere_fx[a] += fx;
        sphere_fy[a] += fy;
        sphere_fz[a] += fz;

        sphere_fx[c] -= fx;
        sphere_fy[c] -= fy;
        sphere_fz[c] -= fz;
    }
}
