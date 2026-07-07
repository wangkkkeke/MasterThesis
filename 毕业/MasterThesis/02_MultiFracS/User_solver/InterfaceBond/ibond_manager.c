#include "ibond_types.h"
#include "ibond_table.h"
#include "ibond_provider.h"
#include "../Cpucore.h"
#include "../Cpuuser.h"
#include "../Standard_library.h"
#include <stdio.h>

void ibond_mgr_init(BondManager *mgr)
{
    if (mgr == NULL) return;
    ibond_table_init(&mgr->table);
}

void ibond_mgr_free(BondManager *mgr)
{
    if (mgr == NULL) return;
    ibond_table_free(&mgr->table);
}

void ibond_mgr_clear(BondManager *mgr)
{
    if (mgr == NULL) return;
    ibond_table_clear(&mgr->table);
}

void ibond_sync_nibond(CPUUSER cpuuser)
{
    if (cpuuser == NULL) return;
    cpuuser->nibond = cpuuser->ibond_mgr.table.nbond;
}

int ibond_mgr_remove_bond(BondManager *mgr, int bond_index)
{
    if (mgr == NULL) return 0;
    return ibond_table_remove_at(&mgr->table, bond_index);
}

static Real ibond_dist3(Real ax, Real ay, Real az, Real bx, Real by, Real bz)
{
    Real dx = ax - bx, dy = ay - by, dz = az - bz;
    return (Real)sqrt((double)(dx * dx + dy * dy + dz * dz));
}

static Real ibond_interface_xmax(CPUCORE cpucore)
{
    int i;
    Real xmax;
    if (cpucore == NULL || cpucore->nfn <= 0 || cpucore->d1fnix == NULL)
        return R0;
    xmax = cpucore->d1fnix[0];
    for (i = 1; i < cpucore->nfn; i++)
        if (cpucore->d1fnix[i] > xmax)
            xmax = cpucore->d1fnix[i];
    return xmax;
}

static int ibond_nearest_interface_node(CPUCORE cpucore, Real cx, Real cy, Real cz,
                                        Real *dist_out)
{
    int i, best = -1;
    Real best_dist = REAL_MAX;
    Real xmax, tol, dist;

    if (dist_out != NULL) *dist_out = REAL_MAX;
    if (cpucore == NULL || cpucore->nfn <= 0) return -1;

    xmax = ibond_interface_xmax(cpucore);
    tol = 1e-9;

    for (i = 0; i < cpucore->nfn; i++)
    {
        if (cpucore->d1fnix[i] < xmax - tol) continue;
        dist = ibond_dist3(cpucore->d1fnix[i], cpucore->d1fniy[i], cpucore->d1fniz[i],
                           cx, cy, cz);
        if (dist < best_dist)
        {
            best_dist = dist;
            best = i;
        }
    }
    if (dist_out != NULL) *dist_out = best_dist;
    return best;
}

static void ibond_write_status(CPUUSER cpuuser, int nibond, int best_node, Real dist, Real rcut)
{
    FILE *fp = fopen("ibond_identify_status.txt", "w");
    if (fp == NULL) return;
    fprintf(fp, "nibond=%d\n", nibond);
    if (best_node >= 0)
        fprintf(fp, "best_node=%d\n", best_node + 1);
    fprintf(fp, "dist=%.6e\n", (double)dist);
    fprintf(fp, "rcut=%.6e\n", (double)rcut);
    if (nibond > 0 && cpuuser != NULL)
    {
        BondTable *t = &cpuuser->ibond_mgr.table;
        int i;
        fprintf(fp, "nbond=%d\n", t->nbond);
        for (i = 0; i < t->nbond; i++)
        {
            BondAnchor *a = &t->anchors[t->bonds[i].anchor_index];
            fprintf(fp, "bond[%d] anchor=%d particle=%d node=%d\n",
                    i, t->bonds[i].anchor_index, t->bonds[i].sphere_index,
                    a->node_id + 1);
        }
    }
    fclose(fp);
}

static void ibond_mgr_identify_r2(CPUCORE cpucore, CPUUSER cpuuser, BondManager *mgr)
{
    BondTable *t;
    InterfaceEntity ent;
    int ei, pi, created;
    Real cx, cy, cz, dist, rcut;
    FILE *fp;

    t = &mgr->table;
    rcut = cpuuser->ibond_rcut;
    ibond_table_clear(t);

    printf("[ibond_identify] R2 FaceCentroid verify_case=%d rcut=%.6f\n",
           cpuuser->ibond_verify_case, (double)rcut);

    if (cpuuser != NULL && cpuuser->bench_kind == 2)
    {
        if (!ibond_entity_build_benchmark2_c3d4(cpucore, &ent))
        {
            printf("[ibond_identify] R2 Benchmark-2: build C3D4 entity failed.\n");
            ibond_sync_nibond(cpuuser);
            return;
        }
    }
    else if (!ibond_entity_build_minimal_cps3(cpucore, &ent))
    {
        printf("[ibond_identify] R2: build InterfaceEntity failed.\n");
        ibond_sync_nibond(cpuuser);
        return;
    }

    printf("[ibond_identify] R2 elem=%d centroid=(%.6f, %.6f, %.6f) area=%.6e\n",
           ent.elem_id, (double)ent.xc, (double)ent.yc, (double)ent.zc, (double)ent.area);

    ei = ibond_table_add_entity(t, &ent);
    if (ei < 0)
    {
        ibond_sync_nibond(cpuuser);
        return;
    }

    created = 0;
    for (pi = 0; pi < t->nparticles; pi++)
    {
        IbondProviderKind pkind = ibond_provider_kind(cpuuser);

        if (!ibond_provider_particle_active(&t->particles[pi], pkind))
            continue;

        cx = t->particles[pi].x0 + t->particles[pi].ux;
        cy = t->particles[pi].y0 + t->particles[pi].uy;
        cz = t->particles[pi].z0 + t->particles[pi].uz;

        dist = ibond_dist3(cx, cy, cz, ent.xc, ent.yc, ent.zc);
        printf("[ibond_identify] R2 particle[%d] dist_to_centroid=%.6f\n", pi, (double)dist);

        if (dist > rcut)
        {
            printf("[ibond_identify] R2: dist > rcut, no bond.\n");
            continue;
        }

        if (ibond_table_add_bond_entity(t, ei, pi, cpuuser->ibond_kn, cpuuser->ibond_kt, dist))
        {
            created++;
            printf("[ibond_identify] R2 CreateBond bond[%d] entity=%d particle=%d\n",
                   t->nbond - 1, ei, pi);
        }
    }

    ibond_sync_nibond(cpuuser);
    printf("[ibond_identify] R2 nibond=%d (created=%d)\n", cpuuser->nibond, created);

    fp = fopen("ibond_identify_status.txt", "w");
    if (fp != NULL)
    {
        fprintf(fp, "representation=R2_FaceCentroid\n");
        fprintf(fp, "nibond=%d\n", cpuuser->nibond);
        fprintf(fp, "elem_id=%d\n", ent.elem_id);
        fprintf(fp, "centroid_x=%.6e\n", (double)ent.xc);
        fprintf(fp, "centroid_y=%.6e\n", (double)ent.yc);
        fprintf(fp, "dist=%.6e\n", (double)dist);
        fprintf(fp, "rcut=%.6e\n", (double)rcut);
        fclose(fp);
    }
}

void ibond_mgr_identify(CPUCORE cpucore, CPUUSER cpuuser, BondManager *mgr)
{
    BondTable *t;
    int pi, node, anchor_idx, created;
    Real cx, cy, cz, dist, rcut;

    if (cpucore == NULL || cpuuser == NULL || mgr == NULL) return;

    if (ibond_provider_kind(cpuuser) == IBOND_PROVIDER_CPUCORE)
        ibond_provider_sync_to_table(cpucore, cpuuser, &mgr->table);

    if (cpuuser->ibond_level >= 2 &&
        (ibond_provider_kind(cpuuser) != IBOND_PROVIDER_CPUCORE ||
         (cpuuser != NULL && cpuuser->bench_kind == 2)))
    {
        ibond_mgr_identify_r2(cpucore, cpuuser, mgr);
        return;
    }

    t = &mgr->table;
    rcut = cpuuser->ibond_rcut;

    ibond_table_clear(t);

    printf("[ibond_identify] Level-%d verify_case=%d rcut=%.6f nparticles=%d\n",
           cpuuser->ibond_level, cpuuser->ibond_verify_case, (double)rcut, t->nparticles);

    if (rcut <= R0 || t->nparticles <= 0 || t->particles == NULL)
    {
        printf("[ibond_identify] skip: rcut or particles invalid.\n");
        ibond_sync_nibond(cpuuser);
        if (ibond_provider_kind(cpuuser) == IBOND_PROVIDER_CPUCORE)
            ibond_provider_log_identify(cpucore, cpuuser, cpuuser->nibond);
        return;
    }

    if (cpucore->nfn <= 0 || cpucore->d1fnix == NULL)
    {
        printf("[ibond_identify] no FEM nodes.\n");
        ibond_sync_nibond(cpuuser);
        return;
    }

    created = 0;
    for (pi = 0; pi < t->nparticles; pi++)
    {
        IbondProviderKind pkind = ibond_provider_kind(cpuuser);

        if (!ibond_provider_particle_active(&t->particles[pi], pkind))
            continue;

        cx = t->particles[pi].x0 + t->particles[pi].ux;
        cy = t->particles[pi].y0 + t->particles[pi].uy;
        cz = t->particles[pi].z0 + t->particles[pi].uz;

        printf("[ibond_identify] particle[%d] center (%.6f, %.6f, %.6f)\n",
               pi, (double)cx, (double)cy, (double)cz);

        node = ibond_nearest_interface_node(cpucore, cx, cy, cz, &dist);
        if (node < 0)
        {
            printf("[ibond_identify] particle[%d]: no interface node.\n", pi);
            continue;
        }

        printf("[ibond_identify] particle[%d] nearest node=%d dist=%.6f\n",
               pi, node + 1, (double)dist);

        if (dist > rcut)
        {
            printf("[ibond_identify] particle[%d]: dist > rcut, skip bond.\n", pi);
            continue;
        }

        anchor_idx = ibond_table_add_anchor(t, cpucore, node);
        if (anchor_idx < 0)
            continue;

        if (ibond_table_add_bond(t, anchor_idx, pi, cpuuser->ibond_kn, cpuuser->ibond_kt, dist))
        {
            created++;
            printf("[ibond_identify] CreateBond bond[%d] node=%d particle=%d\n",
                   t->nbond - 1, node + 1, pi);
        }
        else
            printf("[ibond_identify] particle[%d]: duplicate bond skipped.\n", pi);
    }

    ibond_sync_nibond(cpuuser);
    printf("[ibond_identify] nibond=%d (created=%d)\n", cpuuser->nibond, created);

    if (ibond_provider_kind(cpuuser) == IBOND_PROVIDER_CPUCORE)
        ibond_provider_log_identify(cpucore, cpuuser, cpuuser->nibond);
    else if (cpuuser->nibond == 0 && t->nparticles == 1)
    {
        Real d;
        int bn = ibond_nearest_interface_node(cpucore,
            t->particles[0].x0, t->particles[0].y0, t->particles[0].z0, &d);
        ibond_write_status(cpuuser, 0, bn, d, rcut);
    }
    else
        ibond_write_status(cpuuser, cpuuser->nibond, -1, R0, rcut);
}
