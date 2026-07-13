/*
 * Case01 Verification — Architecture Freeze v1.0
 *
 * Prove algorithm correctness (theory vs program).
 * No new physics. Exit 0 only if ALL checks pass.
 *
 * Output: output/verify_case01.csv
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "proto_api.h"

#define VERIFY_ABS_TOL 1.0e-9
#define VERIFY_REL_TOL 1.0e-9

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

static int check_scalar(const char *item, const char *qty,
                        double theory, double program)
{
    double abs_e = fabs(program - theory);
    double rel_e = rel_error(theory, program);
    int pass = (abs_e <= VERIFY_ABS_TOL) || (rel_e <= VERIFY_REL_TOL);

    if (g_csv) {
        fprintf(g_csv,
                "%s,%s,%.16e,%.16e,%.16e,%.16e,%s\n",
                item, qty, theory, program, abs_e, rel_e,
                pass ? "PASS" : "FAIL");
    }

    printf("[Verify] %s | %s | th=%.6e pr=%.6e abs=%.3e rel=%.3e | %s\n",
           item, qty, theory, program, abs_e, rel_e,
           pass ? "PASS" : "FAIL");

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
        node_fx[i] = 0.0;
        node_fy[i] = 0.0;
        node_fz[i] = 0.0;
    }
}

static int build_base_model(void)
{
    node_num = 4;
    node_x[0] = 0.0; node_y[0] = 0.0; node_z[0] = 0.0;
    node_x[1] = 1.0; node_y[1] = 0.0; node_z[1] = 0.0;
    node_x[2] = 0.0; node_y[2] = 1.0; node_z[2] = 0.0;
    node_x[3] = 0.0; node_y[3] = 0.0; node_z[3] = 1.0;
    node_vx[0] = node_vy[0] = node_vz[0] = 0.0;
    node_vx[1] = node_vy[1] = node_vz[1] = 0.0;
    node_vx[2] = node_vy[2] = node_vz[2] = 0.0;
    node_vx[3] = node_vy[3] = node_vz[3] = 0.0;
    node_mass[0] = node_mass[1] = node_mass[2] = node_mass[3] = 1.0;

    tet_num = 1;
    tet_node1[0] = 0;
    tet_node2[0] = 1;
    tet_node3[0] = 2;
    tet_node4[0] = 3;
    tet_region[0] = REGION_FEM;

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

    return 0;
}

/* ---- 1. Shape Function ---- */
static void verify_shape_function(void)
{
    double n1 = 0.25, n2 = 0.25, n3 = 0.25, n4 = 0.25;
    double u1 = 0.0, u2 = 1.0, u3 = 2.0, u4 = 3.0;
    double theory = n1 * u1 + n2 * u2 + n3 * u3 + n4 * u4;
    double program = 0.0;

    shape_function_tet(n1, n2, n3, n4, u1, u2, u3, u4, &program);
    check_scalar("ShapeFunction", "u", theory, program);
}

/* ---- 2. Proxy interpolation ---- */
static void verify_proxy_interpolation(void)
{
    double th_x, th_y, th_z;
    double th_vx, th_vy, th_vz;
    double n1, n2, n3, n4;

    /* Move nodes with known displacements / velocities */
    node_x[0] = 0.10; node_y[0] = 0.00; node_z[0] = 0.00;
    node_x[1] = 1.10; node_y[1] = 0.00; node_z[1] = 0.00;
    node_x[2] = 0.10; node_y[2] = 1.00; node_z[2] = 0.00;
    node_x[3] = 0.10; node_y[3] = 0.00; node_z[3] = 1.00;

    node_vx[0] = 1.0; node_vy[0] = 0.0; node_vz[0] = 0.0;
    node_vx[1] = 2.0; node_vy[1] = 0.0; node_vz[1] = 0.0;
    node_vx[2] = 3.0; node_vy[2] = 0.0; node_vz[2] = 0.0;
    node_vx[3] = 4.0; node_vy[3] = 0.0; node_vz[3] = 0.0;

    /* Reset proxy seed position for host search on original tet geometry:
     * host Tet / N already found on undeformed mesh in main.
     * Use stored N from sphere_find_host_tet.
     */
    n1 = sphere_N1[0];
    n2 = sphere_N2[0];
    n3 = sphere_N3[0];
    n4 = sphere_N4[0];

    th_x = n1 * node_x[0] + n2 * node_x[1] + n3 * node_x[2] + n4 * node_x[3];
    th_y = n1 * node_y[0] + n2 * node_y[1] + n3 * node_y[2] + n4 * node_y[3];
    th_z = n1 * node_z[0] + n2 * node_z[1] + n3 * node_z[2] + n4 * node_z[3];
    th_vx = n1 * node_vx[0] + n2 * node_vx[1] + n3 * node_vx[2] + n4 * node_vx[3];
    th_vy = n1 * node_vy[0] + n2 * node_vy[1] + n3 * node_vy[2] + n4 * node_vy[3];
    th_vz = n1 * node_vz[0] + n2 * node_vz[1] + n3 * node_vz[2] + n4 * node_vz[3];

    proxy_update();

    check_scalar("ProxyInterp", "x", th_x, sphere_x[0]);
    check_scalar("ProxyInterp", "y", th_y, sphere_y[0]);
    check_scalar("ProxyInterp", "z", th_z, sphere_z[0]);
    check_scalar("ProxyInterp", "vx", th_vx, sphere_vx[0]);
    check_scalar("ProxyInterp", "vy", th_vy, sphere_vy[0]);
    check_scalar("ProxyInterp", "vz", th_vz, sphere_vz[0]);
}

/* ---- 3. Bond force ---- */
static void verify_bond_force(void)
{
    double dx, dy, dz, L, stretch, nx, fn;
    double th_fx_a, th_fy_a, th_fz_a;
    double th_fx_b, th_fy_b, th_fz_b;
    const double eps = 1.0e-30;

    /* Controlled positions: stretch along x */
    sphere_x[0] = 0.00; sphere_y[0] = 0.0; sphere_z[0] = 0.0;
    sphere_x[1] = 0.40; sphere_y[1] = 0.0; sphere_z[1] = 0.0;
    bond_L0[0] = 0.35;
    bond_kn[0] = 1000.0;
    bond_active[0] = BOND_ACTIVE;

    dx = sphere_x[0] - sphere_x[1];
    dy = sphere_y[0] - sphere_y[1];
    dz = sphere_z[0] - sphere_z[1];
    L = sqrt(dx * dx + dy * dy + dz * dz);
    nx = dx / (L < eps ? 1.0 : L);
    stretch = L - bond_L0[0];
    fn = bond_kn[0] * stretch;

    /* Same formula as bond_force.c */
    th_fx_a = -fn * nx;
    th_fy_a = 0.0;
    th_fz_a = 0.0;
    th_fx_b = -th_fx_a;
    th_fy_b = 0.0;
    th_fz_b = 0.0;

    sphere_clear_force();
    bond_compute_force();

    check_scalar("BondForce", "fn", fn, bond_fn[0]);
    check_scalar("BondForce", "fx_A", th_fx_a, sphere_fx[0]);
    check_scalar("BondForce", "fy_A", th_fy_a, sphere_fy[0]);
    check_scalar("BondForce", "fz_A", th_fz_a, sphere_fz[0]);
    check_scalar("BondForce", "fx_B", th_fx_b, sphere_fx[1]);
    check_scalar("BondForce", "fy_B", th_fy_b, sphere_fy[1]);
    check_scalar("BondForce", "fz_B", th_fz_b, sphere_fz[1]);
}

/* ---- 4. DEM explicit step ---- */
static void verify_dem_step(void)
{
    double m, fx, dt;
    double th_ax, th_vx, th_x;
    double v0, x0;

    /* Isolate FREE sphere; PROXY must not move under dem_step */
    sphere_motion_mode[0] = MOTION_PROXY;
    sphere_motion_mode[1] = MOTION_FREE;

    m = 2.0;
    fx = 4.0;
    dt = 1.0e-3;
    x0 = 1.0;
    v0 = 0.5;

    sphere_mass[1] = m;
    sphere_fx[1] = fx;
    sphere_fy[1] = 0.0;
    sphere_fz[1] = 0.0;
    sphere_x[1] = x0;
    sphere_y[1] = 0.0;
    sphere_z[1] = 0.0;
    sphere_vx[1] = v0;
    sphere_vy[1] = 0.0;
    sphere_vz[1] = 0.0;

    sphere_x[0] = 9.0;
    sphere_vx[0] = 9.0;

    proto_dt = dt;

    th_ax = fx / m;
    th_vx = v0 + th_ax * dt;
    th_x = x0 + th_vx * dt; /* semi-implicit, matches dem_solver.c */

    dem_step();

    check_scalar("DEM", "ax", th_ax, sphere_ax[1]);
    check_scalar("DEM", "vx", th_vx, sphere_vx[1]);
    check_scalar("DEM", "x", th_x, sphere_x[1]);
    /* PROXY unchanged */
    check_scalar("DEM", "proxy_x_unchanged", 9.0, sphere_x[0]);
    check_scalar("DEM", "proxy_vx_unchanged", 9.0, sphere_vx[0]);
}

/* ---- 5. Force Mapping ---- */
static void verify_force_mapping(void)
{
    double n1, n2, n3, n4;
    double rx, ry, rz;
    double th0x, th1x, th2x, th3x;

    /* Restore Case01 host / N */
    build_base_model();
    if (sphere_find_host_tet() != 0) {
        check_scalar("ForceMapping", "host_tet", 0.0, 1.0);
        return;
    }

    n1 = sphere_N1[0];
    n2 = sphere_N2[0];
    n3 = sphere_N3[0];
    n4 = sphere_N4[0];

    rx = 8.0;
    ry = 0.0;
    rz = 0.0;
    sphere_fx[0] = rx;
    sphere_fy[0] = ry;
    sphere_fz[0] = rz;
    sphere_fx[1] = sphere_fy[1] = sphere_fz[1] = 0.0;

    clear_node_force();
    force_mapping_proxy_to_tet();

    th0x = n1 * rx;
    th1x = n2 * rx;
    th2x = n3 * rx;
    th3x = n4 * rx;

    check_scalar("ForceMapping", "node0_fx", th0x, node_fx[0]);
    check_scalar("ForceMapping", "node1_fx", th1x, node_fx[1]);
    check_scalar("ForceMapping", "node2_fx", th2x, node_fx[2]);
    check_scalar("ForceMapping", "node3_fx", th3x, node_fx[3]);
    check_scalar("ForceMapping", "sum_Ni", 1.0, n1 + n2 + n3 + n4);
    check_scalar("ForceMapping", "sum_node_fx", rx,
                 node_fx[0] + node_fx[1] + node_fx[2] + node_fx[3]);
}

/* ---- 6. Action-reaction ---- */
static void verify_action_reaction(void)
{
    double sum_fx, sum_fy, sum_fz;

    build_base_model();
    sphere_x[0] = 0.00; sphere_y[0] = 0.0; sphere_z[0] = 0.0;
    sphere_x[1] = 0.40; sphere_y[1] = 0.0; sphere_z[1] = 0.0;
    bond_create();
    /* override L0 for controlled stretch */
    bond_L0[0] = 0.35;
    bond_active[0] = BOND_ACTIVE;

    sphere_clear_force();
    bond_compute_force();

    sum_fx = sphere_fx[0] + sphere_fx[1];
    sum_fy = sphere_fy[0] + sphere_fy[1];
    sum_fz = sphere_fz[0] + sphere_fz[1];

    check_scalar("ActionReaction", "Fx_A+Fx_B", 0.0, sum_fx);
    check_scalar("ActionReaction", "Fy_A+Fy_B", 0.0, sum_fy);
    check_scalar("ActionReaction", "Fz_A+Fz_B", 0.0, sum_fz);
    check_scalar("ActionReaction", "Fx_B+Fx_A_pair",
                 -sphere_fx[0], sphere_fx[1]);
}

/* ---- 7. Global force conservation ---- */
static void verify_global_force_conservation(void)
{
    double sum_sphere_fx, sum_sphere_fy, sum_sphere_fz;
    double sum_node_fx;
    double rx;

    build_base_model();
    if (sphere_find_host_tet() != 0) {
        check_scalar("GlobalForce", "host_tet", 0.0, 1.0);
        return;
    }

    /* Stretch bond */
    sphere_x[0] = 0.25; sphere_y[0] = 0.25; sphere_z[0] = 0.25;
    sphere_x[1] = 0.55; sphere_y[1] = 0.25; sphere_z[1] = 0.25;
    bond_create();
    bond_L0[0] = 0.20; /* force non-zero stretch from 0.30 length */
    bond_active[0] = BOND_ACTIVE;

    sphere_clear_force();
    bond_compute_force();

    sum_sphere_fx = sphere_fx[0] + sphere_fx[1];
    sum_sphere_fy = sphere_fy[0] + sphere_fy[1];
    sum_sphere_fz = sphere_fz[0] + sphere_fz[1];

    check_scalar("GlobalForce", "sum_sphere_Fx", 0.0, sum_sphere_fx);
    check_scalar("GlobalForce", "sum_sphere_Fy", 0.0, sum_sphere_fy);
    check_scalar("GlobalForce", "sum_sphere_Fz", 0.0, sum_sphere_fz);

    /* Mapping: sum of nodal mapped forces == proxy reaction */
    rx = sphere_fx[0];
    clear_node_force();
    force_mapping_proxy_to_tet();
    sum_node_fx = node_fx[0] + node_fx[1] + node_fx[2] + node_fx[3];
    check_scalar("GlobalForce", "sum_node_fx_eq_proxy_R", rx, sum_node_fx);
}

int main(void)
{
    printf("[Verify] Case01 verification start\n");

#ifdef _WIN32
    system("if not exist output mkdir output");
#else
    system("mkdir -p output");
#endif

    remove("output/verify_case01.csv");
    g_csv = fopen("output/verify_case01.csv", "w");
    if (!g_csv) {
        fprintf(stderr, "[Verify] cannot open output/verify_case01.csv\n");
        return 1;
    }
    fprintf(g_csv, "item,quantity,theory,program,abs_err,rel_err,pass\n");

    if (prototype_initialize(8, 2, 4, 4) != 0) {
        fclose(g_csv);
        return 1;
    }

    build_base_model();
    if (sphere_find_host_tet() != 0) {
        fprintf(stderr, "[Verify] host tet failed\n");
        prototype_finalize();
        fclose(g_csv);
        return 1;
    }
    bond_create();

    verify_shape_function();
    verify_proxy_interpolation();
    verify_bond_force();
    verify_dem_step();
    verify_force_mapping();
    verify_action_reaction();
    verify_global_force_conservation();

    prototype_finalize();
    fclose(g_csv);
    g_csv = 0;

    printf("[Verify] PASS=%d FAIL=%d\n", g_pass_count, g_fail_count);
    if (g_fail_count == 0) {
        printf("[Verify] ALL PASSED — Case01 verified. Case02 allowed.\n");
        return 0;
    }

    printf("[Verify] FAILED — do NOT enter Case02.\n");
    return 1;
}
