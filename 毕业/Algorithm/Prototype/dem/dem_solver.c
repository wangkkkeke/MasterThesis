#include <stdio.h>

#include "proto_api.h"

/*
 * Stage 7 — Freeze ④:
 * DEM does not know Proxy. Only integrates MOTION_FREE.
 * No rotation. a = F/m; v += a*dt; x += v*dt (semi-implicit Euler).
 */
void dem_step(void)
{
    int s;
    double ax, ay, az;
    double m;

    for (s = 0; s < sphere_num; ++s) {
        if (sphere_motion_mode[s] != MOTION_FREE) {
            continue;
        }

        m = sphere_mass[s];
        if (m <= 0.0) {
            fprintf(stderr, "[DEM] dem_step: non-positive mass at %d\n", s);
            continue;
        }

        ax = sphere_fx[s] / m;
        ay = sphere_fy[s] / m;
        az = sphere_fz[s] / m;

        sphere_ax[s] = ax;
        sphere_ay[s] = ay;
        sphere_az[s] = az;

        sphere_vx[s] += ax * proto_dt;
        sphere_vy[s] += ay * proto_dt;
        sphere_vz[s] += az * proto_dt;

        sphere_x[s] += sphere_vx[s] * proto_dt;
        sphere_y[s] += sphere_vy[s] * proto_dt;
        sphere_z[s] += sphere_vz[s] * proto_dt;
    }
}
