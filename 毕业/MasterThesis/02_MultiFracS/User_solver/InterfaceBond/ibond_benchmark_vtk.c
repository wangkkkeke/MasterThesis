#include "ibond_benchmark.h"
#include "ibond_math.h"
#include "../Cpucore.h"
#include "../Cpuuser.h"
#include "../Standard_library.h"
#include <stdio.h>
#include <string.h>

FILE *ibond_benchmark_fopen_output(int bench_kind, const char *fname,
                                   char *path_out, int path_len);

#ifdef _WIN32
#include <direct.h>
#define IBOND_MKDIR(p) _mkdir(p)
#else
#include <sys/stat.h>
#define IBOND_MKDIR(p) mkdir(p, 0755)
#endif

static int ibond_benchmark_get_geometry(CPUCORE cpucore, CPUUSER cpuuser,
                                        Real *ax, Real *ay, Real *az,
                                        Real *sx, Real *sy, Real *sz,
                                        int *anchor_pt, Real *dist_out,
                                        InterfaceEntity *ent_out)
{
    BondTable *t;
    BondAnchor *anchor;
    Particle *particle;
    int i;

    *ax = *ay = *az = R0;
    *sx = cpuuser->bench1_sphere_x;
    *sy = cpuuser->bench1_sphere_y;
    *sz = cpuuser->bench1_sphere_z;
    *anchor_pt = 1;
    *dist_out = R0;
    if (ent_out != NULL)
        memset(ent_out, 0, sizeof(InterfaceEntity));

    if (cpuuser->nibond <= 0)
        return 0;

    t = &cpuuser->ibond_mgr.table;
    if (t->nbond <= 0 || t->particles == NULL)
        return 0;

    particle = &t->particles[t->bonds[0].sphere_index];
    *sx = particle->x0;
    *sy = particle->y0;
    *sz = particle->z0;

    if (t->bonds[0].entity_index >= 0 && t->entities != NULL)
    {
        InterfaceEntity *ent = &t->entities[t->bonds[0].entity_index];
        *ax = ent->xc;
        *ay = ent->yc;
        *az = ent->zc;
        *anchor_pt = ent->node_ids[0];
        if (ent_out != NULL)
            memcpy(ent_out, ent, sizeof(InterfaceEntity));
    }
    else if (t->anchors != NULL)
    {
        anchor = &t->anchors[t->bonds[0].anchor_index];
        i = anchor->node_id;
        *anchor_pt = i;
        *ax = cpucore->d1fnix[i];
        *ay = cpucore->d1fniy[i];
        *az = (cpucore->d1fniz != NULL) ? cpucore->d1fniz[i] : R0;
    }
    else
        return 0;

    *dist_out = ibond_vec3_norm(ibond_vec3(*sx - *ax, *sy - *ay, *sz - *az));
    return 1;
}

static void ibond_benchmark_get_force(BondTable *t, int has_bond,
                                      Real *fem_fx, Real *fem_fy, Real *fem_fz,
                                      Real *dem_fx, Real *dem_fy, Real *dem_fz)
{
    *fem_fx = *fem_fy = *fem_fz = R0;
    *dem_fx = *dem_fy = *dem_fz = R0;
    if (!has_bond || t == NULL || t->forces == NULL)
        return;

    *fem_fx = t->forces[0].fem_fx;
    *fem_fy = t->forces[0].fem_fy;
    *fem_fz = t->forces[0].fem_fz;
    *dem_fx = t->forces[0].dem_fx;
    *dem_fy = t->forces[0].dem_fy;
    *dem_fz = t->forces[0].dem_fz;
}

static void ibond_benchmark_emit_vtk_cps3(FILE *fp, CPUCORE cpucore, CPUUSER cpuuser,
                                          Real sx, Real sy, Real sz,
                                          int anchor_pt, int has_bond, Real r)
{
    int i, nfn, sphere_pt;
    int ncell, cell_size;
    Real fem_fx, fem_fy, fem_fz, dem_fx, dem_fy, dem_fz;
    BondTable *t = &cpuuser->ibond_mgr.table;

    nfn = cpucore->nfn;
    sphere_pt = nfn;
    ncell = has_bond ? 3 : 2;
    cell_size = has_bond ? 10 : 7;
    ibond_benchmark_get_force(t, has_bond, &fem_fx, &fem_fy, &fem_fz,
                              &dem_fx, &dem_fy, &dem_fz);

    fprintf(fp, "# vtk DataFile Version 3.0\n");
    fprintf(fp, "Benchmark-1 test_id=%d\n", cpuuser->bench1_test_id);
    fprintf(fp, "ASCII\n");
    fprintf(fp, "DATASET UNSTRUCTURED_GRID\n");
    fprintf(fp, "POINTS %d float\n", nfn + 1);
    for (i = 0; i < nfn; i++)
    {
        Real z = (cpucore->d1fniz != NULL) ? cpucore->d1fniz[i] : R0;
        fprintf(fp, "%.8e %.8e %.8e\n",
                (double)cpucore->d1fnix[i],
                (double)cpucore->d1fniy[i], (double)z);
    }
    fprintf(fp, "%.8e %.8e %.8e\n", (double)sx, (double)sy, (double)sz);

    fprintf(fp, "CELLS %d %d\n", ncell, cell_size);
    fprintf(fp, "3 0 1 2\n");
    if (has_bond)
        fprintf(fp, "2 %d %d\n", anchor_pt, sphere_pt);
    fprintf(fp, "1 %d\n", sphere_pt);

    fprintf(fp, "CELL_TYPES %d\n", ncell);
    fprintf(fp, "5\n");
    if (has_bond)
        fprintf(fp, "3\n");
    fprintf(fp, "1\n");

    fprintf(fp, "POINT_DATA %d\n", nfn + 1);
    fprintf(fp, "SCALARS radius float 1\nLOOKUP_TABLE default\n");
    for (i = 0; i < nfn; i++)
        fprintf(fp, "0.0\n");
    fprintf(fp, "%.8e\n", (double)r);

    fprintf(fp, "SCALARS sphere_marker float 1\nLOOKUP_TABLE default\n");
    for (i = 0; i < nfn; i++)
        fprintf(fp, "0.0\n");
    fprintf(fp, "1.0\n");

    fprintf(fp, "SCALARS sphere_radius_vis float 1\nLOOKUP_TABLE default\n");
    for (i = 0; i < nfn; i++)
        fprintf(fp, "0.0\n");
    fprintf(fp, "%.8e\n", (double)((r > 0.015) ? r : 0.015));

    fprintf(fp, "VECTORS node_force float\n");
    for (i = 0; i < nfn; i++)
    {
        if (i == anchor_pt && has_bond)
            fprintf(fp, "%.8e %.8e %.8e\n", (double)fem_fx, (double)fem_fy, (double)fem_fz);
        else
            fprintf(fp, "0.0 0.0 0.0\n");
    }
    fprintf(fp, "0.0 0.0 0.0\n");

    fprintf(fp, "VECTORS sphere_force float\n");
    for (i = 0; i < nfn; i++)
        fprintf(fp, "0.0 0.0 0.0\n");
    if (has_bond)
        fprintf(fp, "%.8e %.8e %.8e\n", (double)dem_fx, (double)dem_fy, (double)dem_fz);
    else
        fprintf(fp, "0.0 0.0 0.0\n");

    fprintf(fp, "SCALARS point_role int 1\nLOOKUP_TABLE default\n");
    for (i = 0; i < nfn; i++)
        fprintf(fp, "%d\n", (i == anchor_pt) ? 1 : 0);
    fprintf(fp, "2\n");
}

static void ibond_benchmark_emit_vtk_c3d4(FILE *fp, CPUCORE cpucore, CPUUSER cpuuser,
                                          Real sx, Real sy, Real sz,
                                          const InterfaceEntity *ent,
                                          int has_bond, Real r)
{
    int i, j, nfn, n_pts, centroid_pt, sphere_pt;
    int ncell, cell_size;
    int n0, n1, n2, n3;
    Real fem_fx, fem_fy, fem_fz, dem_fx, dem_fy, dem_fz;
    Real nfx, nfy, nfz, ni;
    BondTable *t = &cpuuser->ibond_mgr.table;

    nfn = cpucore->nfn;
    if (has_bond)
    {
        n_pts = nfn + 2;
        centroid_pt = nfn;
        sphere_pt = nfn + 1;
        ncell = 4;
        cell_size = 14;
    }
    else
    {
        n_pts = nfn + 1;
        centroid_pt = -1;
        sphere_pt = nfn;
        ncell = 3;
        cell_size = 11;
    }

    ibond_benchmark_get_force(t, has_bond, &fem_fx, &fem_fy, &fem_fz,
                              &dem_fx, &dem_fy, &dem_fz);

    n0 = 0; n1 = 1; n2 = 2; n3 = 3;
    if (cpucore->ndsolidelem == 1 && cpucore->i1enid != NULL)
    {
        int r0 = cpucore->i1enid[0];
        int r1 = cpucore->i1enid[1];
        int r2 = cpucore->i1enid[2];
        int r3 = cpucore->i1enid[3];
        /* inp 为 1-based 节点号；部分版本 i1enid 已是 0-based */
        if (r0 >= 1 && r1 >= 1 && r2 >= 1 && r3 >= 1)
        {
            n0 = r0 - 1;
            n1 = r1 - 1;
            n2 = r2 - 1;
            n3 = r3 - 1;
        }
        else
        {
            n0 = r0;
            n1 = r1;
            n2 = r2;
            n3 = r3;
        }
    }

    fprintf(fp, "# vtk DataFile Version 3.0\n");
    fprintf(fp, "Benchmark-2 test_id=%d\n", cpuuser->bench1_test_id);
    fprintf(fp, "ASCII\n");
    fprintf(fp, "DATASET UNSTRUCTURED_GRID\n");
    fprintf(fp, "POINTS %d float\n", n_pts);
    for (i = 0; i < nfn; i++)
    {
        Real z = (cpucore->d1fniz != NULL) ? cpucore->d1fniz[i] : R0;
        fprintf(fp, "%.8e %.8e %.8e\n",
                (double)cpucore->d1fnix[i],
                (double)cpucore->d1fniy[i], (double)z);
    }
    if (has_bond && ent != NULL)
        fprintf(fp, "%.8e %.8e %.8e\n", (double)ent->xc, (double)ent->yc, (double)ent->zc);
    fprintf(fp, "%.8e %.8e %.8e\n", (double)sx, (double)sy, (double)sz);

    fprintf(fp, "CELLS %d %d\n", ncell, cell_size);
    fprintf(fp, "4 %d %d %d %d\n", n0, n1, n2, n3);
    if (ent != NULL && ent->nnodes == 3)
        fprintf(fp, "3 %d %d %d\n",
                ent->node_ids[0], ent->node_ids[1], ent->node_ids[2]);
    else
        fprintf(fp, "3 1 2 3\n");
    fprintf(fp, "1 %d\n", sphere_pt);
    if (has_bond)
        fprintf(fp, "2 %d %d\n", centroid_pt, sphere_pt);

    fprintf(fp, "CELL_TYPES %d\n", ncell);
    fprintf(fp, "10\n");
    fprintf(fp, "5\n");
    fprintf(fp, "1\n");
    if (has_bond)
        fprintf(fp, "3\n");

    fprintf(fp, "POINT_DATA %d\n", n_pts);
    fprintf(fp, "SCALARS radius float 1\nLOOKUP_TABLE default\n");
    for (i = 0; i < nfn; i++)
        fprintf(fp, "0.0\n");
    if (has_bond)
        fprintf(fp, "0.0\n");
    fprintf(fp, "%.8e\n", (double)r);

    fprintf(fp, "SCALARS sphere_marker float 1\nLOOKUP_TABLE default\n");
    for (i = 0; i < nfn; i++)
        fprintf(fp, "0.0\n");
    if (has_bond)
        fprintf(fp, "0.0\n");
    fprintf(fp, "1.0\n");

    fprintf(fp, "SCALARS sphere_radius_vis float 1\nLOOKUP_TABLE default\n");
    for (i = 0; i < nfn; i++)
        fprintf(fp, "0.0\n");
    if (has_bond)
        fprintf(fp, "0.0\n");
    fprintf(fp, "%.8e\n", (double)((r > 0.015) ? r : 0.015));

    fprintf(fp, "VECTORS node_force float\n");
    for (i = 0; i < nfn; i++)
    {
        nfx = nfy = nfz = R0;
        if (has_bond && ent != NULL)
        {
            for (j = 0; j < ent->nnodes; j++)
            {
                if (ent->node_ids[j] == i)
                {
                    ni = ent->shape_n[j];
                    nfx = ni * fem_fx;
                    nfy = ni * fem_fy;
                    nfz = ni * fem_fz;
                    break;
                }
            }
        }
        fprintf(fp, "%.8e %.8e %.8e\n", (double)nfx, (double)nfy, (double)nfz);
    }
    if (has_bond)
        fprintf(fp, "%.8e %.8e %.8e\n", (double)fem_fx, (double)fem_fy, (double)fem_fz);
    fprintf(fp, "0.0 0.0 0.0\n");

    fprintf(fp, "VECTORS sphere_force float\n");
    for (i = 0; i < nfn; i++)
        fprintf(fp, "0.0 0.0 0.0\n");
    if (has_bond)
        fprintf(fp, "0.0 0.0 0.0\n");
    if (has_bond)
        fprintf(fp, "%.8e %.8e %.8e\n", (double)dem_fx, (double)dem_fy, (double)dem_fz);
    else
        fprintf(fp, "0.0 0.0 0.0\n");

    fprintf(fp, "SCALARS point_role int 1\nLOOKUP_TABLE default\n");
    for (i = 0; i < nfn; i++)
    {
        int role = 0;
        if (ent != NULL)
        {
            for (j = 0; j < ent->nnodes; j++)
                if (ent->node_ids[j] == i) { role = 1; break; }
        }
        fprintf(fp, "%d\n", role);
    }
    if (has_bond)
        fprintf(fp, "3\n");
    fprintf(fp, "2\n");
}

void ibond_benchmark_write_setup_log(CPUCORE cpucore, CPUUSER cpuuser)
{
    FILE *fp;
    char path[512];
    char fname[64];
    Real ax, ay, az, sx, sy, sz, d0;
    int anchor_pt, has_bond;
    InterfaceEntity ent;
    const char *prefix;
    const char *bname;
    const char *status;

    if (!ibond_benchmark_is_active(cpuuser))
        return;

    prefix = (cpuuser->bench_kind == 2) ? "benchmark2" : "benchmark1";
    bname = (cpuuser->bench_kind == 2) ? "Benchmark-2" : "Benchmark-1";

    sprintf(fname, "%s_test%d_setup.txt", prefix, cpuuser->bench1_test_id);
    fp = ibond_benchmark_fopen_output(cpuuser->bench_kind, fname, path, (int)sizeof(path));
    if (fp == NULL)
    {
        printf("[ibond_benchmark] cannot open setup log\n");
        return;
    }

    anchor_pt = 1;
    memset(&ent, 0, sizeof(ent));
    has_bond = ibond_benchmark_get_geometry(cpucore, cpuuser, &ax, &ay, &az,
                                            &sx, &sy, &sz, &anchor_pt, &d0, &ent);
    if (!has_bond)
    {
        sx = cpuuser->bench1_sphere_x;
        sy = cpuuser->bench1_sphere_y;
        sz = cpuuser->bench1_sphere_z;
        if (cpuuser->bench_kind == 2 &&
            ibond_entity_build_benchmark2_c3d4(cpucore, &ent))
        {
            ax = ent.xc;
            ay = ent.yc;
            az = ent.zc;
        }
        d0 = ibond_vec3_norm(ibond_vec3(sx - ax, sy - ay, sz - az));
    }

    if (cpuuser->bench1_test_id == 0)
        status = (cpuuser->nibond == 1) ? "OK_identify" : "FAIL_nibond";
    else if (cpuuser->bench1_test_id == 2)
        status = (cpuuser->nibond == 0) ? "OK_beyond_rcut" : "FAIL_nibond";
    else
        status = (cpuuser->nibond == 1) ? "OK_identify" : "FAIL_nibond";

    fprintf(fp, "benchmark=%s\n", bname);
    fprintf(fp, "stage=identify_only\n");
    fprintf(fp, "test_id=%d\n", cpuuser->bench1_test_id);
    fprintf(fp, "ibond_level=%d\n", cpuuser->ibond_level);
    fprintf(fp, "nibond=%d\n", cpuuser->nibond);
    fprintf(fp, "rcut=%.6e\n", (double)cpuuser->ibond_rcut);
    fprintf(fp, "anchor=(%.6e,%.6e,%.6e)\n", (double)ax, (double)ay, (double)az);
    fprintf(fp, "sphere=(%.6e,%.6e,%.6e)\n", (double)sx, (double)sy, (double)sz);
    fprintf(fp, "d0=%.6e\n", (double)d0);
    if (cpuuser->bench_kind == 2)
    {
        if (ent.nnodes == 0)
            ibond_entity_build_benchmark2_c3d4(cpucore, &ent);
        if (ent.nnodes > 0)
            fprintf(fp, "representation=R2_FaceCentroid iface_nodes=%d,%d,%d\n",
                    ent.node_ids[0] + 1, ent.node_ids[1] + 1, ent.node_ids[2] + 1);
    }
    fprintf(fp, "Bond Active=%s\n", (cpuuser->nibond == 1) ? "Yes" : "No");
    fprintf(fp, "status=%s\n", status);

    fclose(fp);
    printf("[ibond_benchmark] wrote %s nibond=%d d0=%.6e rcut=%.6e\n",
           path, cpuuser->nibond, (double)d0, (double)cpuuser->ibond_rcut);
}

void ibond_benchmark_write_vtk(CPUCORE cpucore, CPUUSER cpuuser)
{
    FILE *fp;
    char path[512];
    char fname[64];
    Real ax, ay, az, sx, sy, sz, d0, r;
    int anchor_pt, has_bond;
    InterfaceEntity ent;
    const char *prefix;

    if (cpucore == NULL || cpuuser == NULL || !ibond_benchmark_is_active(cpuuser))
        return;

    prefix = (cpuuser->bench_kind == 2) ? "benchmark2" : "benchmark1";
    anchor_pt = 1;
    memset(&ent, 0, sizeof(ent));
    has_bond = ibond_benchmark_get_geometry(cpucore, cpuuser, &ax, &ay, &az,
                                            &sx, &sy, &sz, &anchor_pt, &d0, &ent);
    r = 0.005;
    if (has_bond)
    {
        BondTable *t = &cpuuser->ibond_mgr.table;
        Particle *p = &t->particles[t->bonds[0].sphere_index];
        if (p->radius > R0)
            r = p->radius;
    }

    sprintf(fname, "%s_test%d.vtk", prefix, cpuuser->bench1_test_id);
    fp = ibond_benchmark_fopen_output(cpuuser->bench_kind, fname, path, (int)sizeof(path));
    if (fp == NULL)
    {
        printf("[ibond_benchmark_vtk] cannot open %s\n", fname);
        return;
    }
    if (cpuuser->bench_kind == 2)
        ibond_benchmark_emit_vtk_c3d4(fp, cpucore, cpuuser, sx, sy, sz, &ent, has_bond, r);
    else
        ibond_benchmark_emit_vtk_cps3(fp, cpucore, cpuuser, sx, sy, sz, anchor_pt, has_bond, r);
    fclose(fp);
    printf("[ibond_benchmark_vtk] wrote %s\n", path);

    sprintf(fname, "%s.vtk", prefix);
    fp = ibond_benchmark_fopen_output(cpuuser->bench_kind, fname, path, (int)sizeof(path));
    if (fp != NULL)
    {
        if (cpuuser->bench_kind == 2)
            ibond_benchmark_emit_vtk_c3d4(fp, cpucore, cpuuser, sx, sy, sz, &ent, has_bond, r);
        else
            ibond_benchmark_emit_vtk_cps3(fp, cpucore, cpuuser, sx, sy, sz, anchor_pt, has_bond, r);
        fclose(fp);
        printf("[ibond_benchmark_vtk] wrote %s\n", path);
    }
}
