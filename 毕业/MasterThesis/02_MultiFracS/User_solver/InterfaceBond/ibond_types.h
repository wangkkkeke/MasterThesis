#ifndef IBOND_TYPES_H
#define IBOND_TYPES_H

#include "../Real.h"
#include "ibond_math.h"

#define IBOND_MAX_PARTICLES 8

typedef enum {
    IBOND_ANCHOR_NODE = 0,
    IBOND_ANCHOR_FACE_CENTER = 1,
    IBOND_ANCHOR_SPH = 2
} IbondAnchorKind;

typedef enum {
    IBOND_IFACE_NODE = 0,
    IBOND_IFACE_FACE_CENTROID = 1,
    IBOND_IFACE_SPH = 2
} IbondIfaceKind;

typedef struct {
    IbondAnchorKind kind;
    int   node_id;
    Real  x, y, z;
    Real  nx, ny, nz;
    int   face_elem_id;
    Real  shape_n[4];
} BondAnchor;

typedef struct {
    IbondIfaceKind kind;
    int   elem_id;
    int   node_ids[4];
    int   nnodes;
    Real  xc, yc, zc;
    Real  nx, ny, nz;
    Real  area;
    Real  shape_n[4];
} InterfaceEntity;

typedef struct {
    int   is_mock;
    Real  x0, y0, z0;
    Real  radius;
    Real  ux, uy, uz;
    int   prescribed;
    int   dem_node_id;
} Particle;

typedef Particle MockSphere;

typedef struct {
    int   anchor_index;
    int   entity_index;
    int   sphere_index;
    Real  kn, kt;
    Real  rcut_at_build;
    int   broken;
} BondPair;

typedef struct {
    Real  fem_fx, fem_fy, fem_fz;
    Real  dem_fx, dem_fy, dem_fz;
} BondForce;

typedef struct {
    int              nbond;
    int              capacity;
    int              nanchors;
    int              acapacity;
    int              nentities;
    int              ecapacity;
    int              nparticles;
    BondAnchor      *anchors;
    InterfaceEntity *entities;
    Particle        *particles;
    BondPair        *bonds;
    BondForce       *forces;
} BondTable;

typedef struct {
    BondTable table;
} BondManager;

struct CPUCORE_struct;
struct CPUUSER_struct;
typedef struct CPUCORE_struct *CPUCORE;
typedef struct CPUUSER_struct *CPUUSER;

void ibond_config_mock(CPUUSER cpuuser);
void ibond_identify(CPUCORE cpucore, CPUUSER cpuuser);
void ibond_compute_forces(CPUCORE cpucore, CPUUSER cpuuser);
void ibond_apply_forces(CPUCORE cpucore, CPUUSER cpuuser);
void ibond_free_tables(CPUUSER cpuuser);

void ibond_relative_displacement(CPUCORE cpucore, CPUUSER cpuuser,
                                 const BondAnchor *anchor,
                                 int particle_index,
                                 IbondVec3 *du_out);

void ibond_relative_displacement_entity(CPUCORE cpucore, CPUUSER cpuuser,
                                        const InterfaceEntity *entity,
                                        int particle_index,
                                        IbondVec3 *du_out);

void ibond_mgr_init(BondManager *mgr);
void ibond_mgr_free(BondManager *mgr);
void ibond_mgr_clear(BondManager *mgr);
void ibond_sync_nibond(CPUUSER cpuuser);
int  ibond_mgr_remove_bond(BondManager *mgr, int bond_index);
void ibond_mgr_identify(CPUCORE cpucore, CPUUSER cpuuser, BondManager *mgr);

int  ibond_entity_build_minimal_cps3(CPUCORE cpucore, InterfaceEntity *ent);
int  ibond_entity_build_benchmark2_c3d4(CPUCORE cpucore, InterfaceEntity *ent);

void ibond_distribute_face_force(const InterfaceEntity *entity, const BondForce *bf,
                                 CPUCORE cpucore,
                                 Real *acc_fx, Real *acc_fy, Real *acc_fz,
                                 Real *sum_fx, Real *sum_fy, Real *sum_fz);

void ibond_provider_probe(CPUCORE cpucore, CPUUSER cpuuser);

void ibond_provider_log_bond_force(CPUCORE cpucore, CPUUSER cpuuser);

void ibond_provider_log_apply(CPUCORE cpucore, CPUUSER cpuuser);

#endif
