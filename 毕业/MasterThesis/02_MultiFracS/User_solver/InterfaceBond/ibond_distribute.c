#include "ibond_types.h"
#include "../Cpucore.h"
#include "../Standard_library.h"
#include <stdio.h>

void ibond_distribute_face_force(const InterfaceEntity *entity, const BondForce *bf,
                                 CPUCORE cpucore,
                                 Real *acc_fx, Real *acc_fy, Real *acc_fz,
                                 Real *sum_fx, Real *sum_fy, Real *sum_fz)
{
    int i, n;
    Real ni, fx, fy, fz;

    if (entity == NULL || bf == NULL || cpucore == NULL) return;
    if (acc_fx == NULL || acc_fy == NULL || acc_fz == NULL) return;

    fx = bf->fem_fx;
    fy = bf->fem_fy;
    fz = bf->fem_fz;

    if (sum_fx) *sum_fx = R0;
    if (sum_fy) *sum_fy = R0;
    if (sum_fz) *sum_fz = R0;

    for (i = 0; i < entity->nnodes; i++)
    {
        ni = entity->shape_n[i];
        n = entity->node_ids[i];
        if (n < 0 || n >= cpucore->nfn) continue;

        acc_fx[n] += ni * fx;
        acc_fy[n] += ni * fy;
        if (acc_fz != NULL && cpucore->d1dnfz != NULL)
            acc_fz[n] += ni * fz;

        if (sum_fx) *sum_fx += ni * fx;
        if (sum_fy) *sum_fy += ni * fy;
        if (sum_fz) *sum_fz += ni * fz;
    }
}
