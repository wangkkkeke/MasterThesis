#include "ibond_provider.h"
#include "ibond_table.h"
#include "../Cpucore.h"
#include "../Cpuuser.h"
#include "../Standard_library.h"
#include <stdio.h>

IbondProviderKind ibond_provider_kind(CPUUSER cpuuser)
{
    if (cpuuser != NULL && cpuuser->bench_kind >= 1)
        return IBOND_PROVIDER_CPUCORE;
    if (cpuuser != NULL && cpuuser->ibond_verify_case >= 20)
        return IBOND_PROVIDER_CPUCORE;
    return IBOND_PROVIDER_MOCK;
}

int ibond_provider_count(CPUCORE cpucore, CPUUSER cpuuser)
{
    if (cpucore == NULL)
        return 0;
    if (ibond_provider_kind(cpuuser) != IBOND_PROVIDER_CPUCORE)
        return 0;
    if (cpucore->nsph > 0)
        return cpucore->nsph;
    if (cpuuser != NULL && cpuuser->bench_kind >= 1)
        return 1;
    return 0;
}

static int ibond_provider_stride(CPUCORE cpucore)
{
    int ndim;

    if (cpucore == NULL)
        return 4;
    ndim = cpucore->ndim;
    if (ndim <= 0)
        ndim = 3;
    return ndim + 1;
}

int ibond_provider_fill_particle(CPUCORE cpucore, CPUUSER cpuuser,
                                 int index, Particle *out)
{
    int stride;
    int i;
    int cnt;
    int fnid;
    Real x, y, z;

    if (cpucore == NULL || out == NULL || index < 0)
        return -1;
    if (ibond_provider_kind(cpuuser) != IBOND_PROVIDER_CPUCORE)
        return -1;

    if (cpucore->nsph <= 0 && cpuuser != NULL && cpuuser->bench_kind >= 1)
    {
        if (index != 0)
            return -1;
        memset(out, 0, sizeof(Particle));
        out->is_mock = 0;
        out->dem_node_id = -1;
        out->x0 = cpuuser->bench1_sphere_x;
        out->y0 = cpuuser->bench1_sphere_y;
        out->z0 = cpuuser->bench1_sphere_z;
        out->radius = 0.005;
        return 0;
    }

    if (index >= cpucore->nsph)
        return -1;

    memset(out, 0, sizeof(Particle));
    out->is_mock = 0;
    out->dem_node_id = index;

    stride = ibond_provider_stride(cpucore);
    x = y = z = 0.0;
    cnt = 0;

    if (cpucore->i1sphfnid != NULL &&
        cpucore->d1dncx != NULL &&
        cpucore->d1dncy != NULL &&
        cpucore->d1dncz != NULL)
    {
        for (i = 0; i < stride; i++)
        {
            fnid = cpucore->i1sphfnid[index * stride + i];
            if (fnid < 0 || fnid >= cpucore->ndn)
                continue;
            x += cpucore->d1dncx[fnid];
            y += cpucore->d1dncy[fnid];
            z += cpucore->d1dncz[fnid];
            cnt++;
        }
        if (cnt > 0)
        {
            out->x0 = x / (Real)cnt;
            out->y0 = y / (Real)cnt;
            out->z0 = z / (Real)cnt;
        }
        out->dem_node_id = cpucore->i1sphfnid[index * stride + 0];
    }

    if (cpucore->d1sphr != NULL)
        out->radius = cpucore->d1sphr[index];
    else if (cpucore->d1sphdx != NULL)
        out->radius = cpucore->d1sphdx[index] * 0.5;

    return 0;
}

void ibond_provider_probe(CPUCORE cpucore, CPUUSER cpuuser)
{
    FILE *fp;
    int nparticle;
    int i;
    int ndem_hint;
    Particle p;

    fp = fopen("particle_probe_log.txt", "w");
    if (fp == NULL)
    {
        printf("[ibond_provider] Case L: cannot open particle_probe_log.txt\n");
        return;
    }

    ndem_hint = 0;
    if (cpucore != NULL && cpucore->ndn > cpucore->nfn)
        ndem_hint = cpucore->ndn - cpucore->nfn;

    fprintf(fp, "provider=CpuCore\n");
    fprintf(fp, "verify_case=20 (Case L: read only)\n");
    if (cpucore != NULL)
    {
        fprintf(fp, "nfn=%d ndn=%d nsph=%d ndim=%d ndem_hint=%d\n",
                cpucore->nfn, cpucore->ndn, cpucore->nsph,
                cpucore->ndim, ndem_hint);
    }
    else
    {
        fprintf(fp, "nfn=0 ndn=0 nsph=0 ndim=0 ndem_hint=0\n");
    }

    nparticle = ibond_provider_count(cpucore, cpuuser);
    fprintf(fp, "nparticle=%d\n", nparticle);

    if (nparticle == 0)
        fprintf(fp, "status=BLOCKED_need_FEM_DEM_inp\n");
    else
        fprintf(fp, "status=OK\n");

    for (i = 0; i < nparticle; i++)
    {
        if (ibond_provider_fill_particle(cpucore, cpuuser, i, &p) != 0)
            continue;
        fprintf(fp, "[%d] id=%d dem_node_id=%d x=%.6e y=%.6e z=%.6e r=%.6e\n",
                i, i, p.dem_node_id,
                (double)p.x0, (double)p.y0, (double)p.z0, (double)p.radius);
    }

    fclose(fp);
    printf("[ibond_provider] Case L: wrote particle_probe_log.txt nparticle=%d\n",
           nparticle);
}

int ibond_provider_particle_active(const Particle *p, IbondProviderKind kind)
{
    if (p == NULL)
        return 0;
    if (kind == IBOND_PROVIDER_MOCK)
        return p->is_mock;
    return !p->is_mock;
}

int ibond_provider_sync_to_table(CPUCORE cpucore, CPUUSER cpuuser, BondTable *table)
{
    int n;
    int i;

    if (table == NULL)
        return 0;
    if (ibond_provider_kind(cpuuser) != IBOND_PROVIDER_CPUCORE)
        return 0;

    n = ibond_provider_count(cpucore, cpuuser);
    if (n <= 0)
    {
        table->nparticles = 0;
        return 1;
    }

    if (n > IBOND_MAX_PARTICLES)
    {
        printf("[ibond_provider] warning: cap particles %d -> %d\n",
               n, IBOND_MAX_PARTICLES);
        n = IBOND_MAX_PARTICLES;
    }

    if (!ibond_table_reserve_particles(table, n))
        return 0;

    for (i = 0; i < n; i++)
    {
        if (ibond_provider_fill_particle(cpucore, cpuuser, i, &table->particles[i]) != 0)
            return 0;
    }

    printf("[ibond_provider] synced %d particles from CPUCORE\n", n);
    return 1;
}

void ibond_provider_log_identify(CPUCORE cpucore, CPUUSER cpuuser, int nibond)
{
    FILE *fp;
    int nparticle;

    fp = fopen("ibond_identify_status.txt", "w");
    if (fp == NULL)
        return;

    nparticle = ibond_provider_count(cpucore, cpuuser);
    fprintf(fp, "provider=CpuCore\n");
    fprintf(fp, "verify_case=%d (Case M: identify only)\n",
            cpuuser != NULL ? cpuuser->ibond_verify_case : 0);
    if (cpucore != NULL)
        fprintf(fp, "nfn=%d ndn=%d nsph=%d\n",
                cpucore->nfn, cpucore->ndn, cpucore->nsph);
    fprintf(fp, "nparticles=%d\n", nparticle);
    fprintf(fp, "nibond=%d\n", nibond);
    if (nparticle == 0)
        fprintf(fp, "status=BLOCKED_need_FEM_DEM_inp\n");
    else
        fprintf(fp, "status=OK\n");

    if (nibond > 0 && cpuuser != NULL)
    {
        BondTable *t = &cpuuser->ibond_mgr.table;
        int i;

        fprintf(fp, "nbond=%d\n", t->nbond);
        for (i = 0; i < t->nbond; i++)
        {
            BondAnchor *a = &t->anchors[t->bonds[i].anchor_index];
            fprintf(fp, "bond[%d] anchor=%d particle=%d node=%d dem_node_id=%d\n",
                    i, t->bonds[i].anchor_index, t->bonds[i].sphere_index,
                    a->node_id + 1,
                    t->particles[t->bonds[i].sphere_index].dem_node_id);
        }
    }

    fclose(fp);
}

void ibond_provider_log_bond_force(CPUCORE cpucore, CPUUSER cpuuser)
{
    FILE *fp;
    BondTable *t;
    int i;
    int nibond;

    fp = fopen("bond_force_log.txt", "w");
    if (fp == NULL)
    {
        printf("[ibond_provider] Case N: cannot open bond_force_log.txt\n");
        return;
    }

    fprintf(fp, "provider=CpuCore\n");
    fprintf(fp, "verify_case=22 (Case N: compute only)\n");
    if (cpucore != NULL)
        fprintf(fp, "nfn=%d ndn=%d nsph=%d\n",
                cpucore->nfn, cpucore->ndn, cpucore->nsph);

    nibond = (cpuuser != NULL) ? cpuuser->nibond : 0;
    fprintf(fp, "nibond=%d\n", nibond);

    if (nibond <= 0 || cpuuser == NULL)
    {
        fprintf(fp, "status=BLOCKED_need_FEM_DEM_inp\n");
        fclose(fp);
        printf("[ibond_provider] Case N: wrote bond_force_log.txt nibond=0\n");
        return;
    }

    t = &cpuuser->ibond_mgr.table;
    fprintf(fp, "status=OK\n");
    fprintf(fp, "nbond=%d\n", t->nbond);

    for (i = 0; i < t->nbond; i++)
    {
        BondForce *bf = &t->forces[i];
        Particle *p = NULL;
        BondAnchor *a = NULL;
        int pi = t->bonds[i].sphere_index;

        if (pi >= 0 && pi < t->nparticles && t->particles != NULL)
            p = &t->particles[pi];
        if (t->bonds[i].anchor_index >= 0 && t->anchors != NULL)
            a = &t->anchors[t->bonds[i].anchor_index];

        fprintf(fp, "bond[%d] particle=%d", i, pi);
        if (p != NULL)
            fprintf(fp, " dem_node_id=%d x=%.6e y=%.6e z=%.6e r=%.6e",
                    p->dem_node_id,
                    (double)p->x0, (double)p->y0, (double)p->z0, (double)p->radius);
        if (a != NULL)
            fprintf(fp, " anchor_node=%d", a->node_id + 1);
        fprintf(fp, "\n");
        fprintf(fp, "bond[%d] femF=(%.6e,%.6e,%.6e) demF=(%.6e,%.6e,%.6e)\n",
                i,
                (double)bf->fem_fx, (double)bf->fem_fy, (double)bf->fem_fz,
                (double)bf->dem_fx, (double)bf->dem_fy, (double)bf->dem_fz);
    }

    fclose(fp);
    printf("[ibond_provider] Case N: wrote bond_force_log.txt nbond=%d\n", t->nbond);
}

void ibond_provider_log_apply(CPUCORE cpucore, CPUUSER cpuuser)
{
    FILE *fp;
    BondTable *t;
    int i;
    int nibond;

    fp = fopen("apply_force_log.txt", "w");
    if (fp == NULL)
    {
        printf("[ibond_provider] Case O: cannot open apply_force_log.txt\n");
        return;
    }

    fprintf(fp, "provider=CpuCore\n");
    fprintf(fp, "verify_case=23 (Case O: full apply)\n");
    if (cpucore != NULL)
        fprintf(fp, "nfn=%d ndn=%d nsph=%d\n",
                cpucore->nfn, cpucore->ndn, cpucore->nsph);

    nibond = (cpuuser != NULL) ? cpuuser->nibond : 0;
    fprintf(fp, "nibond=%d\n", nibond);

    if (nibond <= 0 || cpuuser == NULL)
    {
        fprintf(fp, "status=BLOCKED_need_FEM_DEM_inp\n");
        fclose(fp);
        printf("[ibond_provider] Case O: wrote apply_force_log.txt nibond=0\n");
        return;
    }

    t = &cpuuser->ibond_mgr.table;
    fprintf(fp, "status=OK\n");
    fprintf(fp, "nbond=%d\n", t->nbond);

    for (i = 0; i < t->nbond; i++)
    {
        BondForce *bf = &t->forces[i];
        BondAnchor *a = NULL;
        Particle *p = NULL;
        int pi = t->bonds[i].sphere_index;

        if (t->bonds[i].anchor_index >= 0 && t->anchors != NULL)
            a = &t->anchors[t->bonds[i].anchor_index];
        if (pi >= 0 && pi < t->nparticles && t->particles != NULL)
            p = &t->particles[pi];

        if (a != NULL)
            fprintf(fp, "bond[%d] fem_node=%d femF=(%.6e,%.6e,%.6e)\n",
                    i, a->node_id + 1,
                    (double)bf->fem_fx, (double)bf->fem_fy, (double)bf->fem_fz);
        if (p != NULL && !p->is_mock)
            fprintf(fp, "bond[%d] dem_node=%d demF=(%.6e,%.6e,%.6e)\n",
                    i, p->dem_node_id + 1,
                    (double)bf->dem_fx, (double)bf->dem_fy, (double)bf->dem_fz);
    }

    fclose(fp);
    printf("[ibond_provider] Case O: wrote apply_force_log.txt nbond=%d\n", t->nbond);
}
