/*
 * Case01 Driver — Architecture Freeze v1.0
 *
 * 1 Tet + 1 Proxy + 1 Bond + 1 Free
 * Driver FEM (prescribed displacement), no central difference.
 *
 * Time loop (Freeze ⑦ — scheduler only here):
 *   clear_force -> driver_fem -> proxy -> bond -> dem -> mapping -> vtk/csv
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "proto_api.h"

static void clear_node_force(void)
{
    int i;
    for (i = 0; i < node_num; ++i) {
        node_fx[i] = 0.0;
        node_fy[i] = 0.0;
        node_fz[i] = 0.0;
    }
}

static int build_case01_model(void)
{
    /* Tet: (0,0,0)(1,0,0)(0,1,0)(0,0,1) */
    node_num = 4;
    node_x[0] = 0.0; node_y[0] = 0.0; node_z[0] = 0.0;
    node_x[1] = 1.0; node_y[1] = 0.0; node_z[1] = 0.0;
    node_x[2] = 0.0; node_y[2] = 1.0; node_z[2] = 0.0;
    node_x[3] = 0.0; node_y[3] = 0.0; node_z[3] = 1.0;
    node_mass[0] = node_mass[1] = node_mass[2] = node_mass[3] = 1.0;

    tet_num = 1;
    tet_node1[0] = 0;
    tet_node2[0] = 1;
    tet_node3[0] = 2;
    tet_node4[0] = 3;
    tet_region[0] = REGION_FEM;

    /* Proxy at centroid; Free along +x outside */
    sphere_num = 2;
    sphere_x[0] = 0.25; sphere_y[0] = 0.25; sphere_z[0] = 0.25;
    sphere_vx[0] = sphere_vy[0] = sphere_vz[0] = 0.0;
    sphere_radius[0] = 0.05;
    sphere_mass[0] = 1.0;
    sphere_region[0] = REGION_FEM;
    sphere_motion_mode[0] = MOTION_PROXY;

    sphere_x[1] = 0.60; sphere_y[1] = 0.25; sphere_z[1] = 0.25;
    sphere_vx[1] = sphere_vy[1] = sphere_vz[1] = 0.0;
    sphere_radius[1] = 0.05;
    sphere_mass[1] = 1.0;
    sphere_region[1] = REGION_DEM;
    sphere_motion_mode[1] = MOTION_FREE;

    bond_num = 1;
    bond_sphereA[0] = 0;
    bond_sphereB[0] = 1;
    bond_kn[0] = 1.0e3;
    bond_ks[0] = 0.0;

    printf("[Driver] Case01 model: 1 tet, 2 spheres, 1 bond\n");
    return 0;
}

int main(void)
{
    int step;
    int nstep;
    char vtk_path[256];

    printf("[Driver] Case01 start\n");

    if (prototype_initialize(8, 2, 4, 4) != 0) {
        return 1;
    }

    if (build_case01_model() != 0) {
        prototype_finalize();
        return 1;
    }

    if (sphere_find_host_tet() != 0) {
        prototype_finalize();
        return 1;
    }

    if (bond_search_neighbor() != 0) {
        prototype_finalize();
        return 1;
    }
    if (bond_create() != 0) {
        prototype_finalize();
        return 1;
    }

    /* remove old csv */
    remove("output/case01.csv");

#ifdef _WIN32
    system("if not exist output mkdir output");
#else
    system("mkdir -p output");
#endif

    proto_dt = 1.0e-4;
    proto_t_end = 2.0e-2;
    proto_time = 0.0;
    nstep = (int)(proto_t_end / proto_dt + 0.5);

    for (step = 0; step <= nstep; ++step) {
        sphere_clear_force();
        clear_node_force();

        driver_fem_step();
        proxy_update();
        bond_compute_force();
        dem_step();
        force_mapping_proxy_to_tet();

        if (step % 10 == 0) {
            sprintf(vtk_path, "output/case01_%04d.vtk", step);
            vtk_write(vtk_path);
            csv_write("output/case01.csv");
        }

        proto_time += proto_dt;
    }

    printf("[Sphere] final proxy (%.6f,%.6f,%.6f)\n",
           sphere_x[0], sphere_y[0], sphere_z[0]);
    printf("[Sphere] final free  (%.6f,%.6f,%.6f)\n",
           sphere_x[1], sphere_y[1], sphere_z[1]);
    printf("[Bond] final fn=%.6e\n", bond_fn[0]);
    printf("[Driver] Case01 done\n");

    prototype_finalize();
    return 0;
}
