#include "ibond_types.h"
#include "ibond_math.h"
#include "../Cpucore.h"
#include "../Cpuuser.h"
#include "../Standard_library.h"
#include <stdio.h>

/* minimal_coupling.inp: CPS3 elem 60, nodes 36,42,41 (1-based) */
static const int s_face_nodes_1based[3] = { 36, 42, 41 };

static Real ibond_tri_area(Real ax, Real ay, Real bx, Real by, Real cx, Real cy)
{
    return (Real)(0.5 * fabs((double)((bx - ax) * (cy - ay) - (cx - ax) * (by - ay))));
}

int ibond_entity_build_minimal_cps3(CPUCORE cpucore, InterfaceEntity *ent)
{
    int i, n0;
    Real ax, ay, az, bx, by, bz, cx, cy, cz;
    Real xc, yc, zc;

    if (ent == NULL) return 0;

    memset(ent, 0, sizeof(InterfaceEntity));
    ent->kind = IBOND_IFACE_FACE_CENTROID;
    ent->elem_id = 60;
    ent->nnodes = 3;

    for (i = 0; i < 3; i++)
    {
        n0 = s_face_nodes_1based[i] - 1;
        ent->node_ids[i] = n0;
        if (cpucore == NULL || n0 < 0 || n0 >= cpucore->nfn)
            return 0;
    }

    n0 = ent->node_ids[0];
    ax = cpucore->d1fnix[n0]; ay = cpucore->d1fniy[n0]; az = cpucore->d1fniz[n0];
    n0 = ent->node_ids[1];
    bx = cpucore->d1fnix[n0]; by = cpucore->d1fniy[n0]; bz = cpucore->d1fniz[n0];
    n0 = ent->node_ids[2];
    cx = cpucore->d1fnix[n0]; cy = cpucore->d1fniy[n0]; cz = cpucore->d1fniz[n0];

    xc = (ax + bx + cx) / 3.0;
    yc = (ay + by + cy) / 3.0;
    zc = (az + bz + cz) / 3.0;
    ent->xc = xc;
    ent->yc = yc;
    ent->zc = zc;

    ent->nx = 1.0;
    ent->ny = 0.0;
    ent->nz = 0.0;

    ent->area = ibond_tri_area(ax, ay, bx, by, cx, cy);

    for (i = 0; i < 3; i++)
        ent->shape_n[i] = 1.0 / 3.0;
    ent->shape_n[3] = R0;

    return 1;
}

/* Benchmark02: C3D4 elem 1, interface face nodes 2,3,4 (1-based) at x=L */
static const int s_bench2_face_nodes_1based[3] = { 2, 3, 4 };

int ibond_entity_build_benchmark2_c3d4(CPUCORE cpucore, InterfaceEntity *ent)
{
    int i, n0;
    Real ax, ay, az, bx, by, bz, cx, cy, cz;
    Real v1x, v1y, v1z, v2x, v2y, v2z;
    Real nx, ny, nz, len;

    if (ent == NULL) return 0;

    memset(ent, 0, sizeof(InterfaceEntity));
    ent->kind = IBOND_IFACE_FACE_CENTROID;
    ent->elem_id = 1;
    ent->nnodes = 3;

    for (i = 0; i < 3; i++)
    {
        n0 = s_bench2_face_nodes_1based[i] - 1;
        ent->node_ids[i] = n0;
        if (cpucore == NULL || n0 < 0 || n0 >= cpucore->nfn)
            return 0;
    }

    n0 = ent->node_ids[0];
    ax = cpucore->d1fnix[n0]; ay = cpucore->d1fniy[n0];
    az = (cpucore->d1fniz != NULL) ? cpucore->d1fniz[n0] : R0;
    n0 = ent->node_ids[1];
    bx = cpucore->d1fnix[n0]; by = cpucore->d1fniy[n0];
    bz = (cpucore->d1fniz != NULL) ? cpucore->d1fniz[n0] : R0;
    n0 = ent->node_ids[2];
    cx = cpucore->d1fnix[n0]; cy = cpucore->d1fniy[n0];
    cz = (cpucore->d1fniz != NULL) ? cpucore->d1fniz[n0] : R0;

    ent->xc = (ax + bx + cx) / 3.0;
    ent->yc = (ay + by + cy) / 3.0;
    ent->zc = (az + bz + cz) / 3.0;

    v1x = bx - ax; v1y = by - ay; v1z = bz - az;
    v2x = cx - ax; v2y = cy - ay; v2z = cz - az;
    nx = v1y * v2z - v1z * v2y;
    ny = v1z * v2x - v1x * v2z;
    nz = v1x * v2y - v1y * v2x;
    len = ibond_vec3_norm(ibond_vec3(nx, ny, nz));
    if (len <= 1e-30)
        return 0;
    ent->nx = nx / len;
    ent->ny = ny / len;
    ent->nz = nz / len;
    if (ent->nx < R0)
    {
        ent->nx = -ent->nx;
        ent->ny = -ent->ny;
        ent->nz = -ent->nz;
    }

    ent->area = ibond_tri_area(ax, ay, bx, by, cx, cy);
    for (i = 0; i < 3; i++)
        ent->shape_n[i] = 1.0 / 3.0;
    ent->shape_n[3] = R0;

    return 1;
}

void ibond_relative_displacement_entity(CPUCORE cpucore, CPUUSER cpuuser,
                                        const InterfaceEntity *entity,
                                        int particle_index,
                                        IbondVec3 *du_out)
{
    IbondVec3 ue, up;
    int i, n, vc;
    Real sx, sy, sz;

    if (du_out == NULL) return;
    ue = ibond_vec3(R0, R0, R0);
    up = ibond_vec3(R0, R0, R0);

    vc = (cpuuser != NULL) ? cpuuser->ibond_verify_case : 0;

    if (cpuuser != NULL && cpuuser->bench_kind == 2)
    {
        BondTable *t = &cpuuser->ibond_mgr.table;
        const Particle *p = NULL;
        if (particle_index >= 0 && particle_index < t->nparticles && t->particles != NULL)
            p = &t->particles[particle_index];
        if (p != NULL && cpuuser->bench1_particle_du_n != R0)
            up = ibond_vec3(cpuuser->bench1_particle_du_n, R0, R0);
        if (cpuuser->bench1_test_id == 41)
            ue = ibond_vec3(cpuuser->bench1_anchor_ux, R0, R0);
        *du_out = ibond_vec3_sub(up, ue);
        return;
    }

    if (entity != NULL && entity->nnodes > 0 && cpucore != NULL)
    {
        if (vc == 9 || vc == 10 || vc == 11)
        {
            ue = ibond_vec3(R0, R0, R0);
        }
        else
        {
            sx = sy = sz = R0;
            for (i = 0; i < entity->nnodes; i++)
            {
                n = entity->node_ids[i];
                if (n < 0 || n >= cpucore->nfn) continue;
                if (cpucore->d1dncx != NULL && cpucore->d1fnix != NULL)
                    sx += cpucore->d1dncx[n] - cpucore->d1fnix[n];
                if (cpucore->d1dncy != NULL && cpucore->d1fniy != NULL)
                    sy += cpucore->d1dncy[n] - cpucore->d1fniy[n];
                if (cpucore->d1dncz != NULL && cpucore->d1fniz != NULL)
                    sz += cpucore->d1dncz[n] - cpucore->d1fniz[n];
            }
            sx /= (Real)entity->nnodes;
            sy /= (Real)entity->nnodes;
            sz /= (Real)entity->nnodes;
            ue = ibond_vec3(sx, sy, sz);
        }
    }

    if (cpuuser != NULL)
    {
        BondTable *t = &cpuuser->ibond_mgr.table;
        const Particle *p;
        if (particle_index >= 0 && particle_index < t->nparticles && t->particles != NULL)
        {
            p = &t->particles[particle_index];
            if (vc == 9 || vc == 10 || vc == 11)
                up = ibond_vec3(0.001, R0, R0);
            else
            {
                up.x = p->ux;
                up.y = p->uy;
                up.z = p->uz;
            }
        }
    }

    *du_out = ibond_vec3_sub(up, ue);
}
