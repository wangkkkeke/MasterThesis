#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "proto_api.h"

static void *proto_calloc(size_t n, size_t size)
{
    void *p;

    if (n == 0) {
        return 0;
    }
    p = calloc(n, size);
    return p;
}

static int alloc_doubles(double **p, int n)
{
    *p = (double *)proto_calloc((size_t)n, sizeof(double));
    return (*p != 0 || n == 0) ? 0 : -1;
}

static int alloc_ints(int **p, int n)
{
    *p = (int *)proto_calloc((size_t)n, sizeof(int));
    return (*p != 0 || n == 0) ? 0 : -1;
}

static int alloc_chars(char **p, int n)
{
    *p = (char *)proto_calloc((size_t)n, sizeof(char));
    return (*p != 0 || n == 0) ? 0 : -1;
}

int proto_alloc_arrays(int max_node, int max_tet, int max_sphere, int max_bond)
{
    int ok = 0;

    if (max_node < 0 || max_tet < 0 || max_sphere < 0 || max_bond < 0) {
        fprintf(stderr, "[Driver] proto_alloc_arrays: invalid size\n");
        return -1;
    }

    ok |= alloc_doubles(&node_x, max_node);
    ok |= alloc_doubles(&node_y, max_node);
    ok |= alloc_doubles(&node_z, max_node);
    ok |= alloc_doubles(&node_vx, max_node);
    ok |= alloc_doubles(&node_vy, max_node);
    ok |= alloc_doubles(&node_vz, max_node);
    ok |= alloc_doubles(&node_ax, max_node);
    ok |= alloc_doubles(&node_ay, max_node);
    ok |= alloc_doubles(&node_az, max_node);
    ok |= alloc_doubles(&node_fx, max_node);
    ok |= alloc_doubles(&node_fy, max_node);
    ok |= alloc_doubles(&node_fz, max_node);
    ok |= alloc_doubles(&node_mass, max_node);

    ok |= alloc_ints(&tet_node1, max_tet);
    ok |= alloc_ints(&tet_node2, max_tet);
    ok |= alloc_ints(&tet_node3, max_tet);
    ok |= alloc_ints(&tet_node4, max_tet);
    ok |= alloc_ints(&tet_region, max_tet);

    ok |= alloc_doubles(&sphere_x, max_sphere);
    ok |= alloc_doubles(&sphere_y, max_sphere);
    ok |= alloc_doubles(&sphere_z, max_sphere);
    ok |= alloc_doubles(&sphere_vx, max_sphere);
    ok |= alloc_doubles(&sphere_vy, max_sphere);
    ok |= alloc_doubles(&sphere_vz, max_sphere);
    ok |= alloc_doubles(&sphere_ax, max_sphere);
    ok |= alloc_doubles(&sphere_ay, max_sphere);
    ok |= alloc_doubles(&sphere_az, max_sphere);
    ok |= alloc_doubles(&sphere_fx, max_sphere);
    ok |= alloc_doubles(&sphere_fy, max_sphere);
    ok |= alloc_doubles(&sphere_fz, max_sphere);
    ok |= alloc_doubles(&sphere_radius, max_sphere);
    ok |= alloc_doubles(&sphere_mass, max_sphere);
    ok |= alloc_ints(&sphere_motion_mode, max_sphere);
    ok |= alloc_ints(&sphere_region, max_sphere);
    ok |= alloc_ints(&sphere_hostTet, max_sphere);
    ok |= alloc_doubles(&sphere_N1, max_sphere);
    ok |= alloc_doubles(&sphere_N2, max_sphere);
    ok |= alloc_doubles(&sphere_N3, max_sphere);
    ok |= alloc_doubles(&sphere_N4, max_sphere);

    ok |= alloc_ints(&bond_sphereA, max_bond);
    ok |= alloc_ints(&bond_sphereB, max_bond);
    ok |= alloc_chars(&bond_active, max_bond);
    ok |= alloc_doubles(&bond_kn, max_bond);
    ok |= alloc_doubles(&bond_ks, max_bond);
    ok |= alloc_doubles(&bond_L0, max_bond);
    ok |= alloc_doubles(&bond_fn, max_bond);
    ok |= alloc_doubles(&bond_fs, max_bond);

    /* neighbor arrays sized with sphere for Stage 6 cell list */
    ok |= alloc_ints(&cell_next, max_sphere);
    cell_num = 0;
    cell_head = 0;

    if (ok != 0) {
        fprintf(stderr, "[Driver] proto_alloc_arrays: allocation failed\n");
        proto_free_arrays();
        return -1;
    }

    printf("[Driver] proto_alloc_arrays: node=%d tet=%d sphere=%d bond=%d\n",
           max_node, max_tet, max_sphere, max_bond);

    proto_cap_node = max_node;
    proto_cap_tet = max_tet;
    proto_cap_sphere = max_sphere;
    proto_cap_bond = max_bond;
    return 0;
}

void proto_free_arrays(void)
{
    free(node_x); node_x = 0;
    free(node_y); node_y = 0;
    free(node_z); node_z = 0;
    free(node_vx); node_vx = 0;
    free(node_vy); node_vy = 0;
    free(node_vz); node_vz = 0;
    free(node_ax); node_ax = 0;
    free(node_ay); node_ay = 0;
    free(node_az); node_az = 0;
    free(node_fx); node_fx = 0;
    free(node_fy); node_fy = 0;
    free(node_fz); node_fz = 0;
    free(node_mass); node_mass = 0;

    free(tet_node1); tet_node1 = 0;
    free(tet_node2); tet_node2 = 0;
    free(tet_node3); tet_node3 = 0;
    free(tet_node4); tet_node4 = 0;
    free(tet_region); tet_region = 0;

    free(sphere_x); sphere_x = 0;
    free(sphere_y); sphere_y = 0;
    free(sphere_z); sphere_z = 0;
    free(sphere_vx); sphere_vx = 0;
    free(sphere_vy); sphere_vy = 0;
    free(sphere_vz); sphere_vz = 0;
    free(sphere_ax); sphere_ax = 0;
    free(sphere_ay); sphere_ay = 0;
    free(sphere_az); sphere_az = 0;
    free(sphere_fx); sphere_fx = 0;
    free(sphere_fy); sphere_fy = 0;
    free(sphere_fz); sphere_fz = 0;
    free(sphere_radius); sphere_radius = 0;
    free(sphere_mass); sphere_mass = 0;
    free(sphere_motion_mode); sphere_motion_mode = 0;
    free(sphere_region); sphere_region = 0;
    free(sphere_hostTet); sphere_hostTet = 0;
    free(sphere_N1); sphere_N1 = 0;
    free(sphere_N2); sphere_N2 = 0;
    free(sphere_N3); sphere_N3 = 0;
    free(sphere_N4); sphere_N4 = 0;

    free(bond_sphereA); bond_sphereA = 0;
    free(bond_sphereB); bond_sphereB = 0;
    free(bond_active); bond_active = 0;
    free(bond_kn); bond_kn = 0;
    free(bond_ks); bond_ks = 0;
    free(bond_L0); bond_L0 = 0;
    free(bond_fn); bond_fn = 0;
    free(bond_fs); bond_fs = 0;

    free(cell_head); cell_head = 0;
    free(cell_next); cell_next = 0;
    cell_num = 0;

    node_num = 0;
    tet_num = 0;
    sphere_num = 0;
    bond_num = 0;
}
