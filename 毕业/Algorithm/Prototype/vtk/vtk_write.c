#include <stdio.h>
#include <string.h>

#include "proto_api.h"

/*
 * VTK: nodes + tets + spheres + bond lines.
 * Sphere color: PROXY blue (0,0,1), FREE red (1,0,0).
 */
int vtk_write(const char *path)
{
    FILE *fp;
    int i;

    if (path == 0) {
        fprintf(stderr, "[VTK] null path\n");
        return -1;
    }

    fp = fopen(path, "w");
    if (fp == 0) {
        fprintf(stderr, "[VTK] cannot open %s\n", path);
        return -1;
    }

    fprintf(fp, "# vtk DataFile Version 3.0\n");
    fprintf(fp, "Prototype symbiotic topology\n");
    fprintf(fp, "ASCII\n");
    fprintf(fp, "DATASET UNSTRUCTURED_GRID\n");

    fprintf(fp, "POINTS %d double\n", node_num + sphere_num);
    for (i = 0; i < node_num; ++i) {
        fprintf(fp, "%.8e %.8e %.8e\n", node_x[i], node_y[i], node_z[i]);
    }
    for (i = 0; i < sphere_num; ++i) {
        fprintf(fp, "%.8e %.8e %.8e\n", sphere_x[i], sphere_y[i], sphere_z[i]);
    }

    {
        int ncells = tet_num + bond_num;
        int size = tet_num * 5 + bond_num * 3;
        fprintf(fp, "CELLS %d %d\n", ncells, size);
        for (i = 0; i < tet_num; ++i) {
            fprintf(fp, "4 %d %d %d %d\n",
                    tet_node1[i], tet_node2[i], tet_node3[i], tet_node4[i]);
        }
        for (i = 0; i < bond_num; ++i) {
            fprintf(fp, "2 %d %d\n",
                    node_num + bond_sphereA[i],
                    node_num + bond_sphereB[i]);
        }
        fprintf(fp, "CELL_TYPES %d\n", ncells);
        for (i = 0; i < tet_num; ++i) {
            fprintf(fp, "10\n");
        }
        for (i = 0; i < bond_num; ++i) {
            fprintf(fp, "3\n");
        }
    }

    fprintf(fp, "POINT_DATA %d\n", node_num + sphere_num);

    fprintf(fp, "SCALARS motion_mode int 1\n");
    fprintf(fp, "LOOKUP_TABLE default\n");
    for (i = 0; i < node_num; ++i) {
        fprintf(fp, "-1\n");
    }
    for (i = 0; i < sphere_num; ++i) {
        fprintf(fp, "%d\n", sphere_motion_mode[i]);
    }

    /* RGB: Proxy=blue, Free=red, node=gray */
    fprintf(fp, "COLOR_SCALARS rgb 3\n");
    for (i = 0; i < node_num; ++i) {
        fprintf(fp, "0.6 0.6 0.6\n");
    }
    for (i = 0; i < sphere_num; ++i) {
        if (sphere_motion_mode[i] == MOTION_PROXY) {
            fprintf(fp, "0.0 0.0 1.0\n"); /* blue */
        } else if (sphere_motion_mode[i] == MOTION_FREE) {
            fprintf(fp, "1.0 0.0 0.0\n"); /* red */
        } else {
            fprintf(fp, "0.5 0.5 0.5\n");
        }
    }

    fprintf(fp, "SCALARS region int 1\n");
    fprintf(fp, "LOOKUP_TABLE default\n");
    for (i = 0; i < node_num; ++i) {
        fprintf(fp, "-1\n");
    }
    for (i = 0; i < sphere_num; ++i) {
        fprintf(fp, "%d\n", sphere_region[i]);
    }

    fclose(fp);
    printf("[VTK] wrote %s\n", path);
    return 0;
}
