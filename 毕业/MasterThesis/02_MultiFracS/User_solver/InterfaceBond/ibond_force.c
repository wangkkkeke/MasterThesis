#include "ibond_types.h"
#include "ibond_math.h"
#include "../Cpucore.h"
#include "../Cpuuser.h"
#include "../Standard_library.h"
#include <stdio.h>

static void ibond_check_action_reaction(BondForce *f, Real tol)
{
    Real sx, sy, sz;
    if (f == NULL) return;
    sx = f->fem_fx + f->dem_fx;
    sy = f->fem_fy + f->dem_fy;
    sz = f->fem_fz + f->dem_fz;
    if (ibond_vec3_norm(ibond_vec3(sx, sy, sz)) > tol)
        printf("[ibond_force] warning: action-reaction residual=%.3e\n",
               (double)ibond_vec3_norm(ibond_vec3(sx, sy, sz)));
}

void ibond_compute_forces(CPUCORE cpucore, CPUUSER cpuuser)
{
    int i;
    BondTable *t;
    IbondVec3 du, n;
    Real dun, fn;

    if (cpucore == NULL || cpuuser == NULL) return;
    t = &cpuuser->ibond_mgr.table;
    if (t->nbond <= 0 || t->bonds == NULL || t->forces == NULL)
        return;

    for (i = 0; i < t->nbond; i++)
    {
        BondForce *bf = &t->forces[i];

        if (t->bonds[i].entity_index >= 0 && t->entities != NULL)
        {
            InterfaceEntity *entity = &t->entities[t->bonds[i].entity_index];
            ibond_relative_displacement_entity(cpucore, cpuuser, entity,
                                                 t->bonds[i].sphere_index, &du);
            n = ibond_vec3(entity->nx, entity->ny, entity->nz);
        }
        else if (t->bonds[i].anchor_index >= 0 && t->anchors != NULL)
        {
            BondAnchor *anchor = &t->anchors[t->bonds[i].anchor_index];
            ibond_relative_displacement(cpucore, cpuuser, anchor,
                                        t->bonds[i].sphere_index, &du);
            n = ibond_vec3(anchor->nx, anchor->ny, anchor->nz);
        }
        else
            continue;

        dun = ibond_vec3_dot(du, n);
        fn = t->bonds[i].kn * dun;

        bf->fem_fx = -fn * n.x;
        bf->fem_fy = -fn * n.y;
        bf->fem_fz = -fn * n.z;
        bf->dem_fx = -bf->fem_fx;
        bf->dem_fy = -bf->fem_fy;
        bf->dem_fz = -bf->fem_fz;

        ibond_check_action_reaction(bf, 1e-12);

        if (cpuuser->ibond_level >= 2)
            printf("[ibond_force] R2 bond[%d] FaceForce=(%.3e,%.3e,%.3e) dun=%.6e\n",
                   i, (double)bf->fem_fx, (double)bf->fem_fy, (double)bf->fem_fz,
                   (double)dun);
    }
}
