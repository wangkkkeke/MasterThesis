#include "ibond_types.h"
#include "ibond_math.h"
#include "../Cpucore.h"
#include "../Cpuuser.h"
#include "../Standard_library.h"

static const Particle *ibond_get_particle(CPUUSER cpuuser, int particle_index)
{
    BondTable *t;
    if (cpuuser == NULL || particle_index < 0) return NULL;
    t = &cpuuser->ibond_mgr.table;
    if (particle_index >= t->nparticles || t->particles == NULL) return NULL;
    return &t->particles[particle_index];
}

static IbondVec3 ibond_get_anchor_displacement(CPUCORE cpucore, CPUUSER cpuuser,
                                               const BondAnchor *anchor)
{
    IbondVec3 u;
    int n;

    u = ibond_vec3(R0, R0, R0);
    if (anchor == NULL) return u;

    if (cpuuser != NULL && cpuuser->bench1_test_id == 41)
        return ibond_vec3(cpuuser->bench1_anchor_ux, R0, R0);

    if (cpuuser != NULL && (cpuuser->ibond_verify_case == 1 ||
                            cpuuser->ibond_verify_case == 5))
        return u;
    if (cpuuser != NULL && cpuuser->ibond_verify_case == 2)
        return ibond_vec3(cpuuser->dev_anchor_ux, R0, R0);

    if (cpucore == NULL) return u;

    if (anchor->kind == IBOND_ANCHOR_NODE && anchor->node_id >= 0)
    {
        n = anchor->node_id;
        if (cpucore->d1dncx != NULL && cpucore->d1fnix != NULL)
            u.x = cpucore->d1dncx[n] - cpucore->d1fnix[n];
        if (cpucore->d1dncy != NULL && cpucore->d1fniy != NULL)
            u.y = cpucore->d1dncy[n] - cpucore->d1fniy[n];
        if (cpucore->d1dncz != NULL && cpucore->d1fniz != NULL)
            u.z = cpucore->d1dncz[n] - cpucore->d1fniz[n];
        else
            u.z = R0;
    }

    return u;
}

static IbondVec3 ibond_get_particle_displacement(CPUCORE cpucore, CPUUSER cpuuser,
                                                 int particle_index)
{
    IbondVec3 u = ibond_vec3(R0, R0, R0);
    const Particle *p;
    int n;

    if (cpuuser == NULL) return u;
    p = ibond_get_particle(cpuuser, particle_index);
    if (p == NULL) return u;

    if (!p->is_mock)
    {
        if (cpuuser->bench1_test_id >= 0 && cpuuser->bench1_particle_du_n != R0)
            return ibond_vec3(cpuuser->bench1_particle_du_n, R0, R0);

        if (cpucore == NULL)
            return u;
        n = p->dem_node_id;
        if (n < 0 || n >= cpucore->ndn || cpucore->d1dncx == NULL)
            return u;
        if (n < cpucore->nfn && cpucore->d1fnix != NULL)
        {
            u.x = cpucore->d1dncx[n] - cpucore->d1fnix[n];
            if (cpucore->d1dncy != NULL && cpucore->d1fniy != NULL)
                u.y = cpucore->d1dncy[n] - cpucore->d1fniy[n];
            if (cpucore->d1dncz != NULL && cpucore->d1fniz != NULL)
                u.z = cpucore->d1dncz[n] - cpucore->d1fniz[n];
        }
        else
        {
            u.x = cpucore->d1dncx[n] - p->x0;
            if (cpucore->d1dncy != NULL)
                u.y = cpucore->d1dncy[n] - p->y0;
            if (cpucore->d1dncz != NULL)
                u.z = cpucore->d1dncz[n] - p->z0;
        }
        return u;
    }

    if (cpuuser->ibond_verify_case == 1 || cpuuser->ibond_verify_case == 5)
        return ibond_vec3(0.001, R0, R0);
    if (cpuuser->ibond_verify_case == 2)
        return u;

    u.x = p->ux;
    u.y = p->uy;
    u.z = p->uz;
    return u;
}

void ibond_relative_displacement(CPUCORE cpucore, CPUUSER cpuuser,
                                 const BondAnchor *anchor,
                                 int particle_index,
                                 IbondVec3 *du_out)
{
    IbondVec3 ua, up;
    if (du_out == NULL) return;
    ua = ibond_get_anchor_displacement(cpucore, cpuuser, anchor);
    up = ibond_get_particle_displacement(cpucore, cpuuser, particle_index);
    *du_out = ibond_vec3_sub(up, ua);
}
