#ifndef PROTO_API_H
#define PROTO_API_H

#include "proto_soa.h"

/* ---- Lifecycle (Stage 1) ---- */
int prototype_initialize(int max_node, int max_tet, int max_sphere, int max_bond);
void prototype_finalize(void);

/* ---- Memory helpers (Stage 1) ---- */
int proto_alloc_arrays(int max_node, int max_tet, int max_sphere, int max_bond);
void proto_free_arrays(void);

/* ---- Geometry (Stage 2) ---- */
int point_in_tet(double px, double py, double pz,
                 double x1, double y1, double z1,
                 double x2, double y2, double z2,
                 double x3, double y3, double z3,
                 double x4, double y4, double z4);
void barycentric(double px, double py, double pz,
                 double x1, double y1, double z1,
                 double x2, double y2, double z2,
                 double x3, double y3, double z3,
                 double x4, double y4, double z4,
                 double *n1, double *n2, double *n3, double *n4);
void shape_function_tet(double n1, double n2, double n3, double n4,
                        double u1, double u2, double u3, double u4,
                        double *u);

/* ---- Sphere (Stage 3–5) ---- */
int sphere_generate(void);
int sphere_generate_regular(void);
void sphere_classify(void);
int sphere_find_host_tet(void);
void sphere_clear_force(void);
void proxy_update(void);

/* ---- Bond (Stage 6) ---- */
int bond_search_neighbor(void);
int bond_create(void);
void bond_compute_force(void);

/* ---- FEM / DEM / Coupling (Stage 7–8) ---- */
void driver_fem_step(void);
void fem_step(void);
void dem_step(void);
void force_mapping_proxy_to_tet(void);

/* ---- I/O (Stage 10) ---- */
int vtk_write(const char *path);
int csv_write(const char *path);

#endif /* PROTO_API_H */
