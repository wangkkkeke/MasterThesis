#include "proto_soa.h"

/* SoA storage definitions */

int node_num = 0;
double *node_x = 0;
double *node_y = 0;
double *node_z = 0;
double *node_vx = 0;
double *node_vy = 0;
double *node_vz = 0;
double *node_ax = 0;
double *node_ay = 0;
double *node_az = 0;
double *node_fx = 0;
double *node_fy = 0;
double *node_fz = 0;
double *node_mass = 0;

int tet_num = 0;
int *tet_node1 = 0;
int *tet_node2 = 0;
int *tet_node3 = 0;
int *tet_node4 = 0;
int *tet_region = 0;

int sphere_num = 0;
double *sphere_x = 0;
double *sphere_y = 0;
double *sphere_z = 0;
double *sphere_vx = 0;
double *sphere_vy = 0;
double *sphere_vz = 0;
double *sphere_ax = 0;
double *sphere_ay = 0;
double *sphere_az = 0;
double *sphere_fx = 0;
double *sphere_fy = 0;
double *sphere_fz = 0;
double *sphere_radius = 0;
double *sphere_mass = 0;
int *sphere_motion_mode = 0;
int *sphere_region = 0;
int *sphere_hostTet = 0;
double *sphere_N1 = 0;
double *sphere_N2 = 0;
double *sphere_N3 = 0;
double *sphere_N4 = 0;

int bond_num = 0;
int *bond_sphereA = 0;
int *bond_sphereB = 0;
char *bond_active = 0;
double *bond_kn = 0;
double *bond_ks = 0;
double *bond_L0 = 0;
double *bond_fn = 0;
double *bond_fs = 0;

int *cell_head = 0;
int *cell_next = 0;
int cell_num = 0;

double proto_time = 0.0;
double proto_dt = 0.0;
double proto_t_end = 0.0;

int proto_cap_node = 0;
int proto_cap_tet = 0;
int proto_cap_sphere = 0;
int proto_cap_bond = 0;

double proto_sphere_radius = 0.1;
double proto_sphere_mass = 1.0;
double proto_bond_rcut = 0.0;
double proto_pack_spacing = 0.0;
