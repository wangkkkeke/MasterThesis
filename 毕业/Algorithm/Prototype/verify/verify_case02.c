/*
 * Case02 — Multi-Coupling Pair Verification
 *
 * Unique goal: prove force / mapping superposition for multiple
 * Proxy–Free coupling pairs. No Cell List, no auto packing, no FEM CD.
 *
 * Topology:
 *
 *           P1(0)
 *          /    \
 *        B1      B2
 *        /        \
 *     F1(1)------F2(2)   (layout only; no Free-Free bond)
 *        \        /
 *        B3      B4
 *          \    /
 *           P2(3)
 *
 * Output: output/verify_case02.csv
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "proto_api.h"

#define VERIFY_ABS_TOL 1.0e-12
#define VERIFY_REL_TOL 1.0e-12

#define ID_P1 0
#define ID_F1 1
#define ID_F2 2
#define ID_P2 3

#define B1 0
#define B2 1
#define B3 2
#define B4 3

static FILE *g_csv = 0;
static int g_fail_count = 0;
static int g_pass_count = 0;

/* Per-bond force contribution on endpoints (theory) */
static double g_bfx[4][2]; /* [bond][0=A,1=B] */
static double g_bfy[4][2];
static double g_bfz[4][2];
static double g_bfn[4];

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

static void clear_node_force(void)
{
    int i;
    for (i = 0; i < node_num; ++i) {
        node_fx[i] = node_fy[i] = node_fz[i] = 0.0;
    }
}

/*
 * Theoretical single-bond force (same formula as bond_force.c).
 * A = bond_sphereA, B = bond_sphereB.
 */
static void theory_bond_force(int a, int c, double kn, double L0,
                              double *fn,
                              double *fax, double *fay, double *faz,
                              double *fbx, double *fby, double *fbz)
{
    double dx, dy, dz, L, stretch, nx, ny, nz;
    double fx, fy, fz;
    const double eps = 1.0e-30;

    dx = sphere_x[a] - sphere_x[c];
    dy = sphere_y[a] - sphere_y[c];
    dz = sphere_z[a] - sphere_z[c];
    L = sqrt(dx * dx + dy * dy + dz * dz);
    if (L < eps) {
        *fn = 0.0;
        *fax = *fay = *faz = 0.0;
        *fbx = *fby = *fbz = 0.0;
        return;
    }
    nx = dx / L;
    ny = dy / L;
    nz = dz / L;
    stretch = L - L0;
    *fn = kn * stretch;
    fx = -(*fn) * nx;
    fy = -(*fn) * ny;
    fz = -(*fn) * nz;
    *fax = fx; *fay = fy; *faz = fz;
    *fbx = -fx; *fby = -fy; *fbz = -fz;
}

static void compute_all_theory_bonds(void)
{
    int b;
    for (b = 0; b < bond_num; ++b) {
        theory_bond_force(bond_sphereA[b], bond_sphereB[b],
                          bond_kn[b], bond_L0[b],
                          &g_bfn[b],
                          &g_bfx[b][0], &g_bfy[b][0], &g_bfz[b][0],
                          &g_bfx[b][1], &g_bfy[b][1], &g_bfz[b][1]);
    }
}

static void sum_theory_sphere_force(int s,
                                    double *fx, double *fy, double *fz)
{
    int b;
    double sx = 0.0, sy = 0.0, sz = 0.0;

    for (b = 0; b < bond_num; ++b) {
        if (bond_active[b] != BOND_ACTIVE) {
            continue;
        }
        if (bond_sphereA[b] == s) {
            sx += g_bfx[b][0];
            sy += g_bfy[b][0];
            sz += g_bfz[b][0];
        } else if (bond_sphereB[b] == s) {
            sx += g_bfx[b][1];
            sy += g_bfy[b][1];
            sz += g_bfz[b][1];
        }
    }
    *fx = sx; *fy = sy; *fz = sz;
}

static int build_case02_model(void)
{
    /* Large tet so both proxies fit inside */
    node_num = 4;
    node_x[0] = 0.0; node_y[0] = 0.0; node_z[0] = 0.0;
    node_x[1] = 2.0; node_y[1] = 0.0; node_z[1] = 0.0;
    node_x[2] = 0.0; node_y[2] = 2.0; node_z[2] = 0.0;
    node_x[3] = 0.0; node_y[3] = 0.0; node_z[3] = 2.0;
    {
        int i;
        for (i = 0; i < 4; ++i) {
            node_vx[i] = node_vy[i] = node_vz[i] = 0.0;
            node_mass[i] = 1.0;
        }
    }

    tet_num = 1;
    tet_node1[0] = 0;
    tet_node2[0] = 1;
    tet_node3[0] = 2;
    tet_node4[0] = 3;
    tet_region[0] = REGION_FEM;

    sphere_num = 4;

    /* P1 */
    sphere_x[ID_P1] = 0.40; sphere_y[ID_P1] = 0.40; sphere_z[ID_P1] = 0.40;
    sphere_vx[ID_P1] = sphere_vy[ID_P1] = sphere_vz[ID_P1] = 0.0;
    sphere_radius[ID_P1] = 0.05;
    sphere_mass[ID_P1] = 1.0;
    sphere_region[ID_P1] = REGION_FEM;
    sphere_motion_mode[ID_P1] = MOTION_PROXY;

    /* F1 */
    sphere_x[ID_F1] = 1.20; sphere_y[ID_F1] = 0.40; sphere_z[ID_F1] = 0.40;
    sphere_vx[ID_F1] = sphere_vy[ID_F1] = sphere_vz[ID_F1] = 0.0;
    sphere_radius[ID_F1] = 0.05;
    sphere_mass[ID_F1] = 1.0;
    sphere_region[ID_F1] = REGION_DEM;
    sphere_motion_mode[ID_F1] = MOTION_FREE;

    /* F2 */
    sphere_x[ID_F2] = 1.20; sphere_y[ID_F2] = 0.90; sphere_z[ID_F2] = 0.40;
    sphere_vx[ID_F2] = sphere_vy[ID_F2] = sphere_vz[ID_F2] = 0.0;
    sphere_radius[ID_F2] = 0.05;
    sphere_mass[ID_F2] = 1.0;
    sphere_region[ID_F2] = REGION_DEM;
    sphere_motion_mode[ID_F2] = MOTION_FREE;

    /* P2 */
    sphere_x[ID_P2] = 0.50; sphere_y[ID_P2] = 0.30; sphere_z[ID_P2] = 0.50;
    sphere_vx[ID_P2] = sphere_vy[ID_P2] = sphere_vz[ID_P2] = 0.0;
    sphere_radius[ID_P2] = 0.05;
    sphere_mass[ID_P2] = 1.0;
    sphere_region[ID_P2] = REGION_FEM;
    sphere_motion_mode[ID_P2] = MOTION_PROXY;

    /* 4 ACTIVE Proxy–Free bonds */
    bond_num = 4;
    bond_sphereA[B1] = ID_P1; bond_sphereB[B1] = ID_F1; bond_kn[B1] = 1000.0;
    bond_sphereA[B2] = ID_P1; bond_sphereB[B2] = ID_F2; bond_kn[B2] = 1000.0;
    bond_sphereA[B3] = ID_F1; bond_sphereB[B3] = ID_P2; bond_kn[B3] = 1000.0;
    bond_sphereA[B4] = ID_F2; bond_sphereB[B4] = ID_P2; bond_kn[B4] = 1000.0;
    {
        int b;
        for (b = 0; b < 4; ++b) {
            bond_ks[b] = 0.0;
        }
    }

    printf("[Driver] Case02 model: 1 tet, P1/P2 + F1/F2, bonds B1..B4\n");
    return 0;
}

/* Stretch geometry so all bonds have non-zero force */
static void apply_controlled_stretch(void)
{
    /* Move frees outward to stretch all PF bonds */
    sphere_x[ID_F1] = 1.50;
    sphere_y[ID_F1] = 0.40;
    sphere_z[ID_F1] = 0.40;

    sphere_x[ID_F2] = 1.50;
    sphere_y[ID_F2] = 1.00;
    sphere_z[ID_F2] = 0.40;
}

/* ---- V1 Shape Function (regression) ---- */
static void verify_v1_shape_function(void)
{
    double n1 = 0.1, n2 = 0.2, n3 = 0.3, n4 = 0.4;
    double u1 = 1.0, u2 = 2.0, u3 = 3.0, u4 = 4.0;
    double theory = n1 * u1 + n2 * u2 + n3 * u3 + n4 * u4;
    double program = 0.0;

    shape_function_tet(n1, n2, n3, n4, u1, u2, u3, u4, &program);
    check_item("V1_ShapeFunction_u", theory, program);
}

/* ---- V2 Sphere Force = sum bond forces ---- */
static void verify_v2_sphere_force(void)
{
    int s;
    double thx, thy, thz;
    char name[64];

    compute_all_theory_bonds();
    sphere_clear_force();
    bond_compute_force();

    for (s = 0; s < sphere_num; ++s) {
        sum_theory_sphere_force(s, &thx, &thy, &thz);
        sprintf(name, "V2_Sphere%d_Fx", s);
        check_item(name, thx, sphere_fx[s]);
        sprintf(name, "V2_Sphere%d_Fy", s);
        check_item(name, thy, sphere_fy[s]);
        sprintf(name, "V2_Sphere%d_Fz", s);
        check_item(name, thz, sphere_fz[s]);
    }
}

/* ---- V3 Proxy Reaction = sum of bond forces on that proxy ---- */
static void verify_v3_proxy_reaction(void)
{
    double thx, thy, thz;

    /* After V2, forces already computed; recompute theory */
    compute_all_theory_bonds();
    sum_theory_sphere_force(ID_P1, &thx, &thy, &thz);
    check_item("V3_P1_Rx", thx, sphere_fx[ID_P1]);
    check_item("V3_P1_Ry", thy, sphere_fy[ID_P1]);
    check_item("V3_P1_Rz", thz, sphere_fz[ID_P1]);

    sum_theory_sphere_force(ID_P2, &thx, &thy, &thz);
    check_item("V3_P2_Rx", thx, sphere_fx[ID_P2]);
    check_item("V3_P2_Ry", thy, sphere_fy[ID_P2]);
    check_item("V3_P2_Rz", thz, sphere_fz[ID_P2]);
}

/* ---- V4 Node Force = Ni * R (single proxy contribution check) ---- */
static void verify_v4_mapping_single(void)
{
    double n1, n2, n3, n4;
    double rx, ry, rz;

    /* Isolate P1 reaction only for analytic check of one proxy */
    sphere_clear_force();
    bond_active[B1] = BOND_ACTIVE;
    bond_active[B2] = BOND_ACTIVE;
    bond_active[B3] = BOND_INACTIVE;
    bond_active[B4] = BOND_INACTIVE;
    bond_compute_force();

    n1 = sphere_N1[ID_P1];
    n2 = sphere_N2[ID_P1];
    n3 = sphere_N3[ID_P1];
    n4 = sphere_N4[ID_P1];
    rx = sphere_fx[ID_P1];
    ry = sphere_fy[ID_P1];
    rz = sphere_fz[ID_P1];

    clear_node_force();
    /* Temporarily mark only P1 as proxy for mapping? Mapping loops all PROXY.
     * Zero P2 force so it contributes 0. */
    sphere_fx[ID_P2] = sphere_fy[ID_P2] = sphere_fz[ID_P2] = 0.0;
    force_mapping_proxy_to_tet();

    check_item("V4_node0_fx", n1 * rx, node_fx[0]);
    check_item("V4_node1_fx", n2 * rx, node_fx[1]);
    check_item("V4_node2_fx", n3 * rx, node_fx[2]);
    check_item("V4_node3_fx", n4 * rx, node_fx[3]);
    check_item("V4_node0_fy", n1 * ry, node_fy[0]);
    check_item("V4_sum_fx", rx, node_fx[0] + node_fx[1] + node_fx[2] + node_fx[3]);

    /* restore all active */
    bond_active[B1] = bond_active[B2] = bond_active[B3] = bond_active[B4] = BOND_ACTIVE;
}

/* ---- V5 Multi-Proxy Mapping superposition ---- */
static void verify_v5_multi_proxy_mapping(void)
{
    double th_fx[4], th_fy[4], th_fz[4];
    int i;
    char name[64];

    sphere_clear_force();
    bond_compute_force();

    for (i = 0; i < 4; ++i) {
        th_fx[i] = th_fy[i] = th_fz[i] = 0.0;
    }

    /* Fi = N_i^{P1} * R^{P1} + N_i^{P2} * R^{P2} */
    th_fx[0] = sphere_N1[ID_P1] * sphere_fx[ID_P1] + sphere_N1[ID_P2] * sphere_fx[ID_P2];
    th_fy[0] = sphere_N1[ID_P1] * sphere_fy[ID_P1] + sphere_N1[ID_P2] * sphere_fy[ID_P2];
    th_fz[0] = sphere_N1[ID_P1] * sphere_fz[ID_P1] + sphere_N1[ID_P2] * sphere_fz[ID_P2];

    th_fx[1] = sphere_N2[ID_P1] * sphere_fx[ID_P1] + sphere_N2[ID_P2] * sphere_fx[ID_P2];
    th_fy[1] = sphere_N2[ID_P1] * sphere_fy[ID_P1] + sphere_N2[ID_P2] * sphere_fy[ID_P2];
    th_fz[1] = sphere_N2[ID_P1] * sphere_fz[ID_P1] + sphere_N2[ID_P2] * sphere_fz[ID_P2];

    th_fx[2] = sphere_N3[ID_P1] * sphere_fx[ID_P1] + sphere_N3[ID_P2] * sphere_fx[ID_P2];
    th_fy[2] = sphere_N3[ID_P1] * sphere_fy[ID_P1] + sphere_N3[ID_P2] * sphere_fy[ID_P2];
    th_fz[2] = sphere_N3[ID_P1] * sphere_fz[ID_P1] + sphere_N3[ID_P2] * sphere_fz[ID_P2];

    th_fx[3] = sphere_N4[ID_P1] * sphere_fx[ID_P1] + sphere_N4[ID_P2] * sphere_fx[ID_P2];
    th_fy[3] = sphere_N4[ID_P1] * sphere_fy[ID_P1] + sphere_N4[ID_P2] * sphere_fy[ID_P2];
    th_fz[3] = sphere_N4[ID_P1] * sphere_fz[ID_P1] + sphere_N4[ID_P2] * sphere_fz[ID_P2];

    clear_node_force();
    force_mapping_proxy_to_tet();

    for (i = 0; i < 4; ++i) {
        sprintf(name, "V5_node%d_fx_multi", i);
        check_item(name, th_fx[i], node_fx[i]);
        sprintf(name, "V5_node%d_fy_multi", i);
        check_item(name, th_fy[i], node_fy[i]);
        sprintf(name, "V5_node%d_fz_multi", i);
        check_item(name, th_fz[i], node_fz[i]);
    }
}

/* ---- V6 Action-Reaction per bond ---- */
static void verify_v6_action_reaction(void)
{
    int b;
    char name[64];

    compute_all_theory_bonds();
    for (b = 0; b < bond_num; ++b) {
        sprintf(name, "V6_B%d_Fx_sum", b);
        check_item(name, 0.0, g_bfx[b][0] + g_bfx[b][1]);
        sprintf(name, "V6_B%d_Fy_sum", b);
        check_item(name, 0.0, g_bfy[b][0] + g_bfy[b][1]);
        sprintf(name, "V6_B%d_Fz_sum", b);
        check_item(name, 0.0, g_bfz[b][0] + g_bfz[b][1]);
    }

    /* Also check program forces after full compute */
    sphere_clear_force();
    bond_compute_force();
    check_item("V6_allSphere_Fx_sum", 0.0,
               sphere_fx[0] + sphere_fx[1] + sphere_fx[2] + sphere_fx[3]);
    check_item("V6_allSphere_Fy_sum", 0.0,
               sphere_fy[0] + sphere_fy[1] + sphere_fy[2] + sphere_fy[3]);
    check_item("V6_allSphere_Fz_sum", 0.0,
               sphere_fz[0] + sphere_fz[1] + sphere_fz[2] + sphere_fz[3]);
}

/* ---- V7 Global force conservation ---- */
static void verify_v7_global_force(void)
{
    double sum_node;

    sphere_clear_force();
    bond_compute_force();
    check_item("V7_sumSphereFx", 0.0,
               sphere_fx[0] + sphere_fx[1] + sphere_fx[2] + sphere_fx[3]);

    clear_node_force();
    force_mapping_proxy_to_tet();
    sum_node = node_fx[0] + node_fx[1] + node_fx[2] + node_fx[3];
    check_item("V7_sumNodeFx_eq_sumProxyRx",
               sphere_fx[ID_P1] + sphere_fx[ID_P2], sum_node);
}

/* ---- V8 Bond Independence ---- */
static void verify_v8_bond_independence(void)
{
    double fn_full[4];
    double fn_wo[4];
    int remove_b, b;
    char name[64];
    char saved_active[4];

    /* Full system bond_fn */
    for (b = 0; b < 4; ++b) {
        bond_active[b] = BOND_ACTIVE;
    }
    sphere_clear_force();
    bond_compute_force();
    for (b = 0; b < 4; ++b) {
        fn_full[b] = bond_fn[b];
    }

    for (remove_b = 0; remove_b < 4; ++remove_b) {
        for (b = 0; b < 4; ++b) {
            saved_active[b] = bond_active[b];
            bond_active[b] = (b == remove_b) ? BOND_INACTIVE : BOND_ACTIVE;
        }
        sphere_clear_force();
        bond_compute_force();
        for (b = 0; b < 4; ++b) {
            fn_wo[b] = bond_fn[b];
        }

        for (b = 0; b < 4; ++b) {
            if (b == remove_b) {
                sprintf(name, "V8_removeB%d_B%d_fn_zero", remove_b, b);
                check_item(name, 0.0, fn_wo[b]);
            } else {
                sprintf(name, "V8_removeB%d_B%d_fn_unchanged", remove_b, b);
                check_item(name, fn_full[b], fn_wo[b]);
            }
        }

        for (b = 0; b < 4; ++b) {
            bond_active[b] = saved_active[b];
        }
    }

    /* restore */
    for (b = 0; b < 4; ++b) {
        bond_active[b] = BOND_ACTIVE;
    }
}

int main(void)
{
    printf("[Verify] Case02 Multi-Coupling Pair Verification start\n");

#ifdef _WIN32
    system("if not exist output mkdir output");
#else
    system("mkdir -p output");
#endif

    remove("output/verify_case02.csv");
    g_csv = fopen("output/verify_case02.csv", "w");
    if (!g_csv) {
        fprintf(stderr, "[Verify] cannot open output/verify_case02.csv\n");
        return 1;
    }
    fprintf(g_csv, "Item,Theory,Numerical,AbsError,RelError,PASS\n");

    if (prototype_initialize(8, 2, 8, 8) != 0) {
        fclose(g_csv);
        return 1;
    }

    build_case02_model();
    if (sphere_find_host_tet() != 0) {
        fprintf(stderr, "[Verify] host tet failed (proxy outside tet?)\n");
        prototype_finalize();
        fclose(g_csv);
        return 1;
    }
    if (bond_create() != 0) {
        prototype_finalize();
        fclose(g_csv);
        return 1;
    }

    /* Stretch AFTER L0 recorded at create, so bonds carry force */
    apply_controlled_stretch();

    printf("[Sphere] P1 N=%.4f %.4f %.4f %.4f host=%d\n",
           sphere_N1[ID_P1], sphere_N2[ID_P1], sphere_N3[ID_P1], sphere_N4[ID_P1],
           sphere_hostTet[ID_P1]);
    printf("[Sphere] P2 N=%.4f %.4f %.4f %.4f host=%d\n",
           sphere_N1[ID_P2], sphere_N2[ID_P2], sphere_N3[ID_P2], sphere_N4[ID_P2],
           sphere_hostTet[ID_P2]);

    verify_v1_shape_function();
    verify_v2_sphere_force();
    verify_v3_proxy_reaction();
    verify_v4_mapping_single();
    verify_v5_multi_proxy_mapping();
    verify_v6_action_reaction();
    verify_v7_global_force();
    verify_v8_bond_independence();

    prototype_finalize();
    fclose(g_csv);
    g_csv = 0;

    printf("[Verify] PASS=%d FAIL=%d\n", g_pass_count, g_fail_count);
    if (g_fail_count == 0) {
        printf("[Verify] Case02 ALL PASSED — Multi-Coupling Pair verified.\n");
        return 0;
    }
    printf("[Verify] Case02 FAILED — do NOT enter Case03.\n");
    return 1;
}
