#include "ibond_types.h"
#include "ibond_provider.h"
#include "../Cpucore.h"
#include "../Cpuuser.h"
#include "../Standard_library.h"
#include <stdio.h>

#define IBOND_MAX_ACC_NODES 512

static void ibond_apply_dem_forces(CPUCORE cpucore, CPUUSER cpuuser, BondTable *t)
{
    int i;
    int pi;
    int dn;
    Particle *p;
    BondForce *bf;

    if (cpucore == NULL || cpuuser == NULL || t == NULL) return;
    if (cpucore->d1dnfx == NULL || cpucore->d1dnfy == NULL) return;

    for (i = 0; i < t->nbond; i++)
    {
        pi = t->bonds[i].sphere_index;
        if (pi < 0 || pi >= t->nparticles || t->particles == NULL)
            continue;
        p = &t->particles[pi];
        if (p->is_mock)
            continue;

        bf = &t->forces[i];
        dn = p->dem_node_id;
        if (dn < 0 || dn >= cpucore->ndn)
            continue;

        cpucore->d1dnfx[dn] += bf->dem_fx;
        cpucore->d1dnfy[dn] += bf->dem_fy;
        if (cpucore->d1dnfz != NULL)
            cpucore->d1dnfz[dn] += bf->dem_fz;

        if (cpuuser->ibond_verify_case == 23 && i == 0)
            printf("[ibond_apply] Case O dem_node=%d demF=(%.3e,%.3e,%.3e)\n",
                   dn + 1,
                   (double)bf->dem_fx, (double)bf->dem_fy, (double)bf->dem_fz);
    }
}

void ibond_apply_forces(CPUCORE cpucore, CPUUSER cpuuser)
{
    int i, j, n, vc;
    BondTable *t;
    Real acc_fx[IBOND_MAX_ACC_NODES];
    Real acc_fy[IBOND_MAX_ACC_NODES];
    Real acc_fz[IBOND_MAX_ACC_NODES];
    Real sum_fx, sum_fy, sum_fz;
    static int s_log_count = 0;
    FILE *fp;

    if (cpucore == NULL || cpuuser == NULL) return;
    t = &cpuuser->ibond_mgr.table;
    if (t->nbond <= 0 || t->forces == NULL || t->bonds == NULL)
        return;

    vc = cpuuser->ibond_verify_case;

    /* M4-B Case J: distribute FaceForce to nodes */
    if (cpuuser->ibond_level >= 2 && vc == 10)
    {
        InterfaceEntity *entity;
        BondForce *bf;

        if (cpucore->d1dnfx == NULL || cpucore->d1dnfy == NULL) return;
        if (cpucore->nfn > IBOND_MAX_ACC_NODES) return;

        for (n = 0; n < cpucore->nfn; n++)
            acc_fx[n] = acc_fy[n] = acc_fz[n] = R0;

        fp = fopen("face_force_log.txt", "w");
        if (fp != NULL)
            fprintf(fp, "verify_case=10 (Case J: distribute)\n");

        for (i = 0; i < t->nbond; i++)
        {
            if (t->bonds[i].entity_index < 0 || t->entities == NULL) continue;
            entity = &t->entities[t->bonds[i].entity_index];
            bf = &t->forces[i];

            sum_fx = sum_fy = sum_fz = R0;
            ibond_distribute_face_force(entity, bf, cpucore,
                                        acc_fx, acc_fy, acc_fz,
                                        &sum_fx, &sum_fy, &sum_fz);

            if (fp != NULL)
            {
                fprintf(fp, "bond[%d] FaceForce=(%.6e,%.6e,%.6e)\n",
                        i, (double)bf->fem_fx, (double)bf->fem_fy, (double)bf->fem_fz);
                fprintf(fp, "bond[%d] sum_NodeForce=(%.6e,%.6e,%.6e)\n",
                        i, (double)sum_fx, (double)sum_fy, (double)sum_fz);
            }

            if (s_log_count < 2)
            {
                printf("[ibond_apply] Case J bond[%d] FaceForce=(%.3e,%.3e,%.3e)\n",
                       i, (double)bf->fem_fx, (double)bf->fem_fy, (double)bf->fem_fz);
                printf("[ibond_apply] Case J bond[%d] sum_NodeForce=(%.3e,%.3e,%.3e)\n",
                       i, (double)sum_fx, (double)sum_fy, (double)sum_fz);
                for (j = 0; j < entity->nnodes; j++)
                {
                    n = entity->node_ids[j];
                    printf("[ibond_apply] Case J node=%d N=%.3f F=(%.3e,%.3e,%.3e)\n",
                           n + 1, (double)entity->shape_n[j],
                           (double)(entity->shape_n[j] * bf->fem_fx),
                           (double)(entity->shape_n[j] * bf->fem_fy),
                           (double)(entity->shape_n[j] * bf->fem_fz));
                }
            }
        }

        if (fp != NULL) fclose(fp);

        for (n = 0; n < cpucore->nfn; n++)
        {
            if (acc_fx[n] == R0 && acc_fy[n] == R0 && acc_fz[n] == R0)
                continue;
            cpucore->d1dnfx[n] += acc_fx[n];
            cpucore->d1dnfy[n] += acc_fy[n];
            if (cpucore->d1dnfz != NULL)
                cpucore->d1dnfz[n] += acc_fz[n];
        }

        s_log_count++;
        return;
    }

    /* M4-A: record FaceForce only, do not write nodes */
    if (cpuuser->ibond_level >= 2)
    {
        fp = fopen("face_force_log.txt", "w");
        if (fp != NULL)
        {
            fprintf(fp, "verify_case=%d\n", vc);
            fprintf(fp, "nbond=%d\n", t->nbond);
            for (i = 0; i < t->nbond; i++)
            {
                BondForce *bf = &t->forces[i];
                fprintf(fp, "bond[%d] FaceForce=(%.6e,%.6e,%.6e)\n",
                        i, (double)bf->fem_fx, (double)bf->fem_fy, (double)bf->fem_fz);
            }
            fclose(fp);
        }
        if (s_log_count < 3)
        {
            for (i = 0; i < t->nbond; i++)
            {
                BondForce *bf = &t->forces[i];
                printf("[ibond_apply] M4-A bond[%d] FaceForce=(%.3e,%.3e,%.3e) (not to nodes)\n",
                       i, (double)bf->fem_fx, (double)bf->fem_fy, (double)bf->fem_fz);
            }
            s_log_count++;
        }
        return;
    }

    if (cpucore->d1dnfx == NULL || cpucore->d1dnfy == NULL) return;
    if (cpucore->nfn > IBOND_MAX_ACC_NODES) return;

    for (n = 0; n < cpucore->nfn; n++)
        acc_fx[n] = acc_fy[n] = acc_fz[n] = R0;

    for (i = 0; i < t->nbond; i++)
    {
        BondAnchor *anchor;
        BondForce *bf;

        if (t->bonds[i].anchor_index < 0 || t->anchors == NULL) continue;
        anchor = &t->anchors[t->bonds[i].anchor_index];
        bf = &t->forces[i];
        n = anchor->node_id;

        if (n < 0 || n >= cpucore->nfn) continue;

        acc_fx[n] += bf->fem_fx;
        acc_fy[n] += bf->fem_fy;
        acc_fz[n] += bf->fem_fz;

        if (s_log_count < 5)
        {
            printf("[ibond_apply] bond[%d] node=%d femF=(%.3e,%.3e,%.3e)\n",
                   i, n + 1,
                   (double)bf->fem_fx, (double)bf->fem_fy, (double)bf->fem_fz);
            s_log_count++;
        }
    }

    for (n = 0; n < cpucore->nfn; n++)
    {
        if (acc_fx[n] == R0 && acc_fy[n] == R0 && acc_fz[n] == R0)
            continue;
        cpucore->d1dnfx[n] += acc_fx[n];
        cpucore->d1dnfy[n] += acc_fy[n];
        if (cpucore->d1dnfz != NULL)
            cpucore->d1dnfz[n] += acc_fz[n];
    }

    if (vc == 23)
    {
        ibond_apply_dem_forces(cpucore, cpuuser, t);
        if (s_log_count < 2)
        {
            ibond_provider_log_apply(cpucore, cpuuser);
            s_log_count++;
        }
    }

    if (vc == 5 && s_log_count <= 5)
    {
        for (n = 0; n < cpucore->nfn; n++)
        {
            if (acc_fx[n] != R0 || acc_fy[n] != R0 || acc_fz[n] != R0)
            {
                printf("[ibond_apply] Case E accumulated node=%d F=(%.3e,%.3e,%.3e)\n",
                       n + 1, (double)acc_fx[n], (double)acc_fy[n], (double)acc_fz[n]);
                break;
            }
        }
    }
}
