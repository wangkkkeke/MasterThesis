#include <stdio.h>

#include "proto_api.h"

/*
 * Regular lattice packing over node bounding box.
 * Uses proto_sphere_radius and proto_pack_spacing (default 2*R).
 * Does not set motion_mode (UNSET until classify).
 */
int sphere_generate_regular(void)
{
    double xmin, ymin, zmin, xmax, ymax, zmax;
    double sp, r, m;
    double x, y, z;
    int i;
    int count;

    if (node_num <= 0) {
        fprintf(stderr, "[Sphere] generate_regular: no nodes\n");
        return -1;
    }

    r = proto_sphere_radius;
    m = proto_sphere_mass;
    sp = proto_pack_spacing;
    if (sp <= 0.0) {
        sp = 2.0 * r;
        proto_pack_spacing = sp;
    }
    if (r <= 0.0) {
        fprintf(stderr, "[Sphere] generate_regular: invalid radius\n");
        return -1;
    }

    xmin = xmax = node_x[0];
    ymin = ymax = node_y[0];
    zmin = zmax = node_z[0];
    for (i = 1; i < node_num; ++i) {
        if (node_x[i] < xmin) xmin = node_x[i];
        if (node_x[i] > xmax) xmax = node_x[i];
        if (node_y[i] < ymin) ymin = node_y[i];
        if (node_y[i] > ymax) ymax = node_y[i];
        if (node_z[i] < zmin) zmin = node_z[i];
        if (node_z[i] > zmax) zmax = node_z[i];
    }

    xmin += r; ymin += r; zmin += r;
    xmax -= r; ymax -= r; zmax -= r;
    if (xmax < xmin || ymax < ymin || zmax < zmin) {
        fprintf(stderr, "[Sphere] generate_regular: bbox too small for radius\n");
        return -1;
    }

    count = 0;
    for (x = xmin; x <= xmax + 1.0e-12; x += sp) {
        for (y = ymin; y <= ymax + 1.0e-12; y += sp) {
            for (z = zmin; z <= zmax + 1.0e-12; z += sp) {
                if (count >= proto_cap_sphere) {
                    fprintf(stderr, "[Sphere] generate_regular: overflow cap=%d\n",
                            proto_cap_sphere);
                    sphere_num = count;
                    return -1;
                }
                sphere_x[count] = x;
                sphere_y[count] = y;
                sphere_z[count] = z;
                sphere_vx[count] = sphere_vy[count] = sphere_vz[count] = 0.0;
                sphere_ax[count] = sphere_ay[count] = sphere_az[count] = 0.0;
                sphere_fx[count] = sphere_fy[count] = sphere_fz[count] = 0.0;
                sphere_radius[count] = r;
                sphere_mass[count] = m;
                sphere_motion_mode[count] = MOTION_UNSET;
                sphere_region[count] = REGION_UNSET;
                sphere_hostTet[count] = -1;
                sphere_N1[count] = sphere_N2[count] = 0.0;
                sphere_N3[count] = sphere_N4[count] = 0.0;
                count++;
            }
        }
    }

    sphere_num = count;
    printf("[Sphere] generate_regular: n=%d R=%.4f spacing=%.4f\n",
           sphere_num, r, sp);
    return 0;
}
