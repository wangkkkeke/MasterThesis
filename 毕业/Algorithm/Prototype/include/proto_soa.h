#ifndef PROTO_SOA_H
#define PROTO_SOA_H

#include "proto_types.h"

/*
 * Structure of Arrays (SoA) — Architecture Freeze v1.0
 * Forbidden: Array of Structures (e.g. Sphere sphere[N])
 */

/* ---- Node ---- */
extern int node_num;
extern double *node_x;
extern double *node_y;
extern double *node_z;
extern double *node_vx;
extern double *node_vy;
extern double *node_vz;
extern double *node_ax;
extern double *node_ay;
extern double *node_az;
extern double *node_fx;
extern double *node_fy;
extern double *node_fz;
extern double *node_mass;

/* ---- Tet ---- */
extern int tet_num;
extern int *tet_node1;
extern int *tet_node2;
extern int *tet_node3;
extern int *tet_node4;
extern int *tet_region;

/* ---- Sphere ---- */
extern int sphere_num;
extern double *sphere_x;
extern double *sphere_y;
extern double *sphere_z;
extern double *sphere_vx;
extern double *sphere_vy;
extern double *sphere_vz;
extern double *sphere_ax;
extern double *sphere_ay;
extern double *sphere_az;
extern double *sphere_fx;
extern double *sphere_fy;
extern double *sphere_fz;
extern double *sphere_radius;
extern double *sphere_mass;
extern int *sphere_motion_mode;
extern int *sphere_region;
extern int *sphere_hostTet;
extern double *sphere_N1;
extern double *sphere_N2;
extern double *sphere_N3;
extern double *sphere_N4;

/* ---- Bond ---- */
extern int bond_num;
extern int *bond_sphereA;
extern int *bond_sphereB;
extern char *bond_active;
extern double *bond_kn;
extern double *bond_ks;
extern double *bond_L0;
extern double *bond_fn;
extern double *bond_fs;

/* ---- Neighbor (Cell Linked List; Stage 6+ may use) ---- */
extern int *cell_head;
extern int *cell_next;
extern int cell_num;

/* ---- Time / packing params ---- */
extern double proto_time;
extern double proto_dt;
extern double proto_t_end;

extern int proto_cap_node;
extern int proto_cap_tet;
extern int proto_cap_sphere;
extern int proto_cap_bond;

extern double proto_sphere_radius;
extern double proto_sphere_mass;
extern double proto_bond_rcut;
extern double proto_pack_spacing;

#endif /* PROTO_SOA_H */
