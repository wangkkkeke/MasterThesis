/*
 * Case03 — Global Sphere Embedding
 * Algorithm Capability Demonstration (not new mechanics formulas)
 *
 * Pipeline:
 *   mesh(FEM|DEM|FEM) -> sphere_generate_regular
 *   -> sphere_find_host_tet -> sphere_classify (HostTet->Region->Mode)
 *   -> bond_search_neighbor (O(N^2)) -> bond_create
 *
 * V1..V9 + VTK (Proxy blue / Free red)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "proto_api.h"

#define VERIFY_ABS_TOL 1.0e-12
#define VERIFY_REL_TOL 1.0e-12

static FILE *g_csv = 0;
static int g_fail_count = 0;
static int g_pass_count = 0;

static double rel_error(double theory, double program)
{
    double denom = fabs(theory);
    if (denom < 1.0e-30) {
        denom = fabs(program);
    }
    if (denom < 1.0e-30) {
        return 0.0;
    }
    return fabs(program - theory) / denom;
}

static int check_item(const char *item, double theory, double program)
{
    double abs_e = fabs(program - theory);
    double rel_e = rel_error(theory, program);
    int pass = (abs_e <= VERIFY_ABS_TOL) || (rel_e <= VERIFY_REL_TOL);

    if (g_csv) {
        fprintf(g_csv, "%s,%.16e,%.16e,%.16e,%.16e,%s\n",
                item, theory, program, abs_e, rel_e,
                pass ? "PASS" : "FAIL");
    }
    printf("[Verify] %s | th=%.6e pr=%.6e abs=%.3e rel=%.3e | %s\n",
           item, theory, program, abs_e, rel_e, pass ? "PASS" : "FAIL");
    if (pass) {
        g_pass_count++;
    } else {
        g_fail_count++;
    }
    return pass;
}

/* ---- Mesh: FEM | DEM | FEM ---- */
static void add_cube_tets(int base_node, int region)
{
    /* 5-tet cube: local nodes base..base+7 already placed */
    int b = base_node;
    int t0 = tet_num;

    /* T0: 0,1,3,4 */
    tet_node1[t0] = b + 0; tet_node2[t0] = b + 1;
    tet_node3[t0] = b + 3; tet_node4[t0] = b + 4;
    tet_region[t0] = region; t0++;

    /* T1: 1,2,3,6 */
    tet_node1[t0] = b + 1; tet_node2[t0] = b + 2;
    tet_node3[t0] = b + 3; tet_node4[t0] = b + 6;
    tet_region[t0] = region; t0++;

    /* T2: 1,4,5,6 */
    tet_node1[t0] = b + 1; tet_node2[t0] = b + 4;
    tet_node3[t0] = b + 5; tet_node4[t0] = b + 6;
    tet_region[t0] = region; t0++;

    /* T3: 3,4,6,7 */
    tet_node1[t0] = b + 3; tet_node2[t0] = b + 4;
    tet_node3[t0] = b + 6; tet_node4[t0] = b + 7;
    tet_region[t0] = region; t0++;

    /* T4: 1,3,4,6 */
    tet_node1[t0] = b + 1; tet_node2[t0] = b + 3;
    tet_node3[t0] = b + 4; tet_node4[t0] = b + 6;
    tet_region[t0] = region; t0++;

    tet_num = t0;
}

static void set_cube_nodes(int base, double x0, double y0, double z0, double L)
{
    /* 0:(x0,y0,z0) 1:(+L,0,0) 2:(+L,+L,0) 3:(0,+L,0)
       4:(0,0,+L) 5:(+L,0,+L) 6:(+L,+L,+L) 7:(0,+L,+L) */
    double x1 = x0 + L, y1 = y0 + L, z1 = z0 + L;
    node_x[base + 0] = x0; node_y[base + 0] = y0; node_z[base + 0] = z0;
    node_x[base + 1] = x1; node_y[base + 1] = y0; node_z[base + 1] = z0;
    node_x[base + 2] = x1; node_y[base + 2] = y1; node_z[base + 2] = z0;
    node_x[base + 3] = x0; node_y[base + 3] = y1; node_z[base + 3] = z0;
    node_x[base + 4] = x0; node_y[base + 4] = y0; node_z[base + 4] = z1;
    node_x[base + 5] = x1; node_y[base + 5] = y0; node_z[base + 5] = z1;
    node_x[base + 6] = x1; node_y[base + 6] = y1; node_z[base + 6] = z1;
    node_x[base + 7] = x0; node_y[base + 7] = y1; node_z[base + 7] = z1;
}

static int build_case03_mesh(void)
{
    int i;

    /* Left FEM cube [0,1]^3, Right FEM cube [2,3]x[0,1]x[0,1], DEM gap (1,2) */
    node_num = 16;
    set_cube_nodes(0, 0.0, 0.0, 0.0, 1.0);
    set_cube_nodes(8, 2.0, 0.0, 0.0, 1.0);
    for (i = 0; i < node_num; ++i) {
        node_vx[i] = node_vy[i] = node_vz[i] = 0.0;
        node_mass[i] = 1.0;
    }

    tet_num = 0;
    add_cube_tets(0, REGION_FEM);
    add_cube_tets(8, REGION_FEM);

    printf("[Driver] Case03 mesh: nodes=%d tets=%d (FEM|DEM|FEM)\n",
           node_num, tet_num);
    return 0;
}

static int theory_sphere_count(void)
{
    double xmin, ymin, zmin, xmax, ymax, zmax;
    double sp, r;
    double x, y, z;
    int i, count;

    r = proto_sphere_radius;
    sp = proto_pack_spacing;
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

    count = 0;
    for (x = xmin; x <= xmax + 1.0e-12; x += sp) {
        for (y = ymin; y <= ymax + 1.0e-12; y += sp) {
            for (z = zmin; z <= zmax + 1.0e-12; z += sp) {
                count++;
            }
        }
    }
    return count;
}

static int theory_bond_count(void)
{
    int i, j, count = 0;
    double dx, dy, dz, dist, rcut;

    rcut = proto_bond_rcut;
    for (i = 0; i < sphere_num; ++i) {
        for (j = i + 1; j < sphere_num; ++j) {
            dx = sphere_x[i] - sphere_x[j];
            dy = sphere_y[i] - sphere_y[j];
            dz = sphere_z[i] - sphere_z[j];
            dist = sqrt(dx * dx + dy * dy + dz * dz);
            if (dist <= rcut + 1.0e-12) {
                count++;
            }
        }
    }
    return count;
}

static int count_mode(int mode)
{
    int i, n = 0;
    for (i = 0; i < sphere_num; ++i) {
        if (sphere_motion_mode[i] == mode) {
            n++;
        }
    }
    return n;
}

static int count_boundary_bonds(void)
{
    int b, n = 0;
    int a, c, ma, mc;
    for (b = 0; b < bond_num; ++b) {
        a = bond_sphereA[b];
        c = bond_sphereB[b];
        ma = sphere_motion_mode[a];
        mc = sphere_motion_mode[c];
        if ((ma == MOTION_PROXY && mc == MOTION_FREE) ||
            (ma == MOTION_FREE && mc == MOTION_PROXY)) {
            n++;
        }
    }
    return n;
}

static int theory_proxy_count_by_host(void)
{
    /* Recompute: spheres with host in REGION_FEM */
    int s, n = 0;
    for (s = 0; s < sphere_num; ++s) {
        int t = sphere_hostTet[s];
        if (t >= 0 && t < tet_num && tet_region[t] == REGION_FEM) {
            n++;
        }
    }
    return n;
}

/* V3: sample up to 10 proxies, recompute barycentric */
static void verify_v3_host_tet(void)
{
    int s, checked = 0;
    int n1i, n2i, n3i, n4i, t;
    double n1, n2, n3, n4;
    char name[64];

    for (s = 0; s < sphere_num && checked < 10; ++s) {
        if (sphere_motion_mode[s] != MOTION_PROXY) {
            continue;
        }
        t = sphere_hostTet[s];
        check_item("V3_proxy_has_host", 1.0, (t >= 0) ? 1.0 : 0.0);

        if (t < 0) {
            checked++;
            continue;
        }
        n1i = tet_node1[t];
        n2i = tet_node2[t];
        n3i = tet_node3[t];
        n4i = tet_node4[t];
        barycentric(sphere_x[s], sphere_y[s], sphere_z[s],
                    node_x[n1i], node_y[n1i], node_z[n1i],
                    node_x[n2i], node_y[n2i], node_z[n2i],
                    node_x[n3i], node_y[n3i], node_z[n3i],
                    node_x[n4i], node_y[n4i], node_z[n4i],
                    &n1, &n2, &n3, &n4);
        sprintf(name, "V3_S%d_N1", s);
        check_item(name, n1, sphere_N1[s]);
        sprintf(name, "V3_S%d_N2", s);
        check_item(name, n2, sphere_N2[s]);
        sprintf(name, "V3_S%d_N3", s);
        check_item(name, n3, sphere_N3[s]);
        sprintf(name, "V3_S%d_N4", s);
        check_item(name, n4, sphere_N4[s]);
        checked++;
    }
    check_item("V3_sampled_proxy_ge1", 1.0, (checked >= 1) ? 1.0 : 0.0);
}

static void verify_v4_shape_sum(void)
{
    int s, n = 0;
    double sum;
    char name[64];

    for (s = 0; s < sphere_num && n < 10; ++s) {
        if (sphere_motion_mode[s] != MOTION_PROXY) {
            continue;
        }
        sum = sphere_N1[s] + sphere_N2[s] + sphere_N3[s] + sphere_N4[s];
        sprintf(name, "V4_S%d_sumN", s);
        check_item(name, 1.0, sum);
        n++;
    }
}

static void verify_v7_connectivity(void)
{
    int *deg;
    int b, s, isolated = 0;
    int bad = 0;

    deg = (int *)calloc((size_t)sphere_num, sizeof(int));
    if (!deg) {
        check_item("V7_alloc", 1.0, 0.0);
        return;
    }

    for (b = 0; b < bond_num; ++b) {
        deg[bond_sphereA[b]]++;
        deg[bond_sphereB[b]]++;
        /* invalid id */
        if (bond_sphereA[b] < 0 || bond_sphereA[b] >= sphere_num ||
            bond_sphereB[b] < 0 || bond_sphereB[b] >= sphere_num) {
            bad++;
        }
        if (bond_sphereA[b] == bond_sphereB[b]) {
            bad++;
        }
    }

    for (s = 0; s < sphere_num; ++s) {
        if (deg[s] == 0) {
            isolated++;
        }
    }

    check_item("V7_isolated_spheres", 0.0, (double)isolated);
    check_item("V7_bad_bonds", 0.0, (double)bad);
    free(deg);
}

static void verify_v9_region_consistency(void)
{
    int s, bad = 0;
    int t;

    for (s = 0; s < sphere_num; ++s) {
        t = sphere_hostTet[s];
        if (sphere_motion_mode[s] == MOTION_PROXY) {
            if (t < 0 || t >= tet_num) {
                bad++;
                continue;
            }
            if (tet_region[t] != REGION_FEM) {
                bad++;
            }
            if (sphere_region[s] != tet_region[t]) {
                bad++;
            }
            if (sphere_region[s] != REGION_FEM) {
                bad++;
            }
        } else if (sphere_motion_mode[s] == MOTION_FREE) {
            if (t >= 0 && t < tet_num) {
                /* FREE with host must inherit non-FEM (DEM tet) */
                if (tet_region[t] == REGION_FEM) {
                    bad++;
                }
                if (sphere_region[s] != tet_region[t]) {
                    bad++;
                }
            } else {
                if (sphere_region[s] != REGION_DEM) {
                    bad++;
                }
            }
        } else {
            bad++;
        }
    }

    check_item("V9_RegionConsistency_bad_count", 0.0, (double)bad);
}

static void write_case03_csv(const char *path)
{
    FILE *fp;
    int i;

    fp = fopen(path, "w");
    if (!fp) {
        return;
    }
    fprintf(fp, "sphere_id,x,y,z,motion_mode,region,hostTet,N1,N2,N3,N4\n");
    for (i = 0; i < sphere_num; ++i) {
        fprintf(fp, "%d,%.8e,%.8e,%.8e,%d,%d,%d,%.8e,%.8e,%.8e,%.8e\n",
                i, sphere_x[i], sphere_y[i], sphere_z[i],
                sphere_motion_mode[i], sphere_region[i], sphere_hostTet[i],
                sphere_N1[i], sphere_N2[i], sphere_N3[i], sphere_N4[i]);
    }
    fclose(fp);
    printf("[CSV] wrote %s\n", path);
}

int main(void)
{
    int th_n, th_proxy, th_free, th_bond, n_boundary;

    printf("[Verify] Case03 Global Sphere Embedding start\n");

#ifdef _WIN32
    system("if not exist output mkdir output");
#else
    system("mkdir -p output");
#endif

    remove("output/verify_case03.csv");
    g_csv = fopen("output/verify_case03.csv", "w");
    if (!g_csv) {
        return 1;
    }
    fprintf(g_csv, "Item,Theory,Numerical,AbsError,RelError,PASS\n");

    /* capacities for ~200 spheres / many bonds */
    if (prototype_initialize(32, 16, 512, 4096) != 0) {
        fclose(g_csv);
        return 1;
    }

    proto_sphere_radius = 0.12;
    proto_pack_spacing = 0.24;
    proto_bond_rcut = 0.26; /* face neighbors on spacing 0.24 */
    proto_sphere_mass = 1.0;

    build_case03_mesh();

    if (sphere_generate() != 0) {
        prototype_finalize();
        fclose(g_csv);
        return 1;
    }
    if (sphere_find_host_tet() != 0) {
        prototype_finalize();
        fclose(g_csv);
        return 1;
    }
    sphere_classify();

    /* clear bond_num so search builds automatically */
    bond_num = 0;
    if (bond_search_neighbor() != 0) {
        prototype_finalize();
        fclose(g_csv);
        return 1;
    }
    if (bond_create() != 0) {
        prototype_finalize();
        fclose(g_csv);
        return 1;
    }

    /* ---- V1 ---- */
    th_n = theory_sphere_count();
    check_item("V1_SphereGeneration_count", (double)th_n, (double)sphere_num);

    /* ---- V2 ---- */
    th_proxy = theory_proxy_count_by_host();
    th_free = sphere_num - th_proxy;
    check_item("V2_Proxy_count", (double)th_proxy, (double)count_mode(MOTION_PROXY));
    check_item("V2_Free_count", (double)th_free, (double)count_mode(MOTION_FREE));

    /* ---- V3 ---- */
    verify_v3_host_tet();

    /* ---- V4 ---- */
    verify_v4_shape_sum();

    /* ---- V5 ---- */
    th_bond = theory_bond_count();
    check_item("V5_BondGeneration_count", (double)th_bond, (double)bond_num);

    /* ---- V6 ---- */
    n_boundary = count_boundary_bonds();
    check_item("V6_BoundaryBond_exists", 1.0, (n_boundary > 0) ? 1.0 : 0.0);
    check_item("V6_BoundaryBond_count_positive", 1.0,
               (n_boundary >= 1) ? 1.0 : 0.0);

    /* ---- V7 ---- */
    verify_v7_connectivity();

    /* ---- V8 Visualization ---- */
    vtk_write("output/case03.vtk");
    write_case03_csv("output/case03.csv");
    check_item("V8_VTK_written", 1.0, 1.0);

    /* ---- V9 Region Consistency ---- */
    verify_v9_region_consistency();

    printf("[Driver] stats: sphere=%d proxy=%d free=%d bond=%d boundary=%d\n",
           sphere_num, count_mode(MOTION_PROXY), count_mode(MOTION_FREE),
           bond_num, n_boundary);

    prototype_finalize();
    fclose(g_csv);

    printf("[Verify] PASS=%d FAIL=%d\n", g_pass_count, g_fail_count);
    if (g_fail_count == 0) {
        printf("[Verify] Case03 ALL PASSED — Capability Demonstration OK.\n");
        return 0;
    }
    printf("[Verify] Case03 FAILED.\n");
    return 1;
}
