#include <stdio.h>

#include "proto_api.h"

/*
 * Append one time-row for numerical check.
 * Header written if file is new / empty.
 */
int csv_write(const char *path)
{
    FILE *fp;
    int proxy = -1;
    int free_s = -1;
    int i;
    long pos;

    if (path == 0) {
        fprintf(stderr, "[CSV] null path\n");
        return -1;
    }

    for (i = 0; i < sphere_num; ++i) {
        if (sphere_motion_mode[i] == MOTION_PROXY && proxy < 0) {
            proxy = i;
        }
        if (sphere_motion_mode[i] == MOTION_FREE && free_s < 0) {
            free_s = i;
        }
    }

    fp = fopen(path, "a");
    if (fp == 0) {
        fprintf(stderr, "[CSV] cannot open %s\n", path);
        return -1;
    }

    fseek(fp, 0, SEEK_END);
    pos = ftell(fp);
    if (pos == 0) {
        fprintf(fp,
                "time,"
                "proxy_x,proxy_y,proxy_z,"
                "free_x,free_y,free_z,"
                "bond_fn,bond_fs,"
                "proxy_fx,proxy_fy,proxy_fz,"
                "node0_fx,node0_fy,node0_fz,"
                "node1_fx,node1_fy,node1_fz,"
                "node2_fx,node2_fy,node2_fz,"
                "node3_fx,node3_fy,node3_fz\n");
    }

    fprintf(fp, "%.8e,", proto_time);
    if (proxy >= 0) {
        fprintf(fp, "%.8e,%.8e,%.8e,",
                sphere_x[proxy], sphere_y[proxy], sphere_z[proxy]);
    } else {
        fprintf(fp, "0,0,0,");
    }
    if (free_s >= 0) {
        fprintf(fp, "%.8e,%.8e,%.8e,",
                sphere_x[free_s], sphere_y[free_s], sphere_z[free_s]);
    } else {
        fprintf(fp, "0,0,0,");
    }
    if (bond_num > 0) {
        fprintf(fp, "%.8e,%.8e,", bond_fn[0], bond_fs[0]);
    } else {
        fprintf(fp, "0,0,");
    }
    if (proxy >= 0) {
        fprintf(fp, "%.8e,%.8e,%.8e,",
                sphere_fx[proxy], sphere_fy[proxy], sphere_fz[proxy]);
    } else {
        fprintf(fp, "0,0,0,");
    }
    for (i = 0; i < 4; ++i) {
        if (i < node_num) {
            fprintf(fp, "%.8e,%.8e,%.8e",
                    node_fx[i], node_fy[i], node_fz[i]);
        } else {
            fprintf(fp, "0,0,0");
        }
        if (i < 3) {
            fprintf(fp, ",");
        }
    }
    fprintf(fp, "\n");

    fclose(fp);
    printf("[CSV] append %s t=%.6e\n", path, proto_time);
    return 0;
}
