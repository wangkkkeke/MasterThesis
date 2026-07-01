/*
 * ibond_init.c -- InterfaceBond pair identification (Issue003)
 *
 * For each SPH element (FEM-side proxy), compute centroid from FEM nodes.
 * For each DEM discrete node, check distance to centroid.
 * If distance <= ibond_rcut, record (sph_id, dn_id) as a Bond pair.
 *
 * Called from user_solver() on first invocation (static flag guard).
 *
 * NOTE: preprocess_cpuuser() has no CPUCORE access, so geometric
 *       identification cannot happen there.
 */

#include "Cpucore.h"
#include "Cpuuser_abstract.h"
#include "Cpuuser.h"
#include "Standard_library.h"

/* Forward declaration -- defined in User_preprocess.c */
void allocate_ibond_arrays(CPUUSER cpuuser);

static void ibond_sph_centroid(CPUCORE core, int s,
                               Real *cx, Real *cy, Real *cz)
{
    int nnode = core->ndim + 1;
    int k;
    *cx = R0;  *cy = R0;  *cz = R0;

    for (k = 0; k < nnode; k++)
    {
        int fn = core->i1sphfnid[s * nnode + k];
        *cx += core->d1fnix[fn];
        *cy += core->d1fniy[fn];
        *cz += core->d1fniz[fn];
    }

    *cx /= (Real)nnode;
    *cy /= (Real)nnode;
    *cz /= (Real)nnode;
}

void ibond_identify(CPUCORE cpucore, CPUUSER cpuuser)
{
    int s, d, idx;
    int count = 0;
    Real rcut  = cpuuser->ibond_rcut;
    Real rcut2 = rcut * rcut;

    if (cpucore->nsph <= 0)
    {
        printf("[ibond_identify] nsph=0, no SPH elements. Check inp.\n");
        return;
    }
    if (rcut <= R0)
    {
        printf("[ibond_identify] ibond_rcut=%.3e, add *InterfaceBond to inp.\n",
               rcut);
        return;
    }

    printf("[ibond_identify] scanning %d SPH x %d DEM, rcut=%.3e ...\n",
           cpucore->nsph, cpucore->ndn, rcut);

    /* Pass 1: count */
    for (s = 0; s < cpucore->nsph; s++)
    {
        Real cx, cy, cz;
        ibond_sph_centroid(cpucore, s, &cx, &cy, &cz);

        for (d = 0; d < cpucore->ndn; d++)
        {
            Real dx = cx - cpucore->d1dncx[d];
            Real dy = cy - cpucore->d1dncy[d];
            Real dz = cz - cpucore->d1dncz[d];
            if (dx*dx + dy*dy + dz*dz <= rcut2) count++;
        }
    }

    cpuuser->nibond = count;
    printf("[ibond_identify] found %d InterfaceBond pairs.\n", count);
    if (count == 0) return;

    /* Allocate */
    allocate_ibond_arrays(cpuuser);

    /* Pass 2: fill */
    idx = 0;
    for (s = 0; s < cpucore->nsph; s++)
    {
        Real cx, cy, cz;
        ibond_sph_centroid(cpucore, s, &cx, &cy, &cz);

        for (d = 0; d < cpucore->ndn; d++)
        {
            Real dx = cx - cpucore->d1dncx[d];
            Real dy = cy - cpucore->d1dncy[d];
            Real dz = cz - cpucore->d1dncz[d];
            if (dx*dx + dy*dy + dz*dz <= rcut2)
            {
                cpuuser->i1ibsphid[idx] = s;
                cpuuser->i1ibdnid[idx]  = d;
                idx++;
            }
        }
    }

    if (idx != count)
        printf("[ibond_identify] ERROR: idx=%d != count=%d\n", idx, count);
    else
        printf("[ibond_identify] OK. Bond[0]: sph=%d dn=%d\n",
               cpuuser->i1ibsphid[0], cpuuser->i1ibdnid[0]);
}
