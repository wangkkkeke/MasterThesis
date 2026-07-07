#include "ibond_types.h"
#include "ibond_table.h"
#include "../Cpucore.h"
#include "../Cpuuser.h"
#include "../Standard_library.h"
#include <stdio.h>

static void ibond_particle_defaults(Particle *p)
{
    if (p == NULL) return;
    memset(p, 0, sizeof(Particle));
    p->is_mock = 1;
    p->radius = 0.01;
    p->dem_node_id = -1;
}

static void ibond_config_three_particles(CPUUSER cpuuser, Real x0, Real y0, Real z0)
{
    BondTable *t;
    int i;
    Real dx[3] = { 0.0, 0.001, 0.002 };

    if (cpuuser == NULL) return;
    t = &cpuuser->ibond_mgr.table;

    ibond_table_free(t);
    ibond_table_init(t);
    ibond_table_reserve_particles(t, 3);

    for (i = 0; i < 3; i++)
    {
        ibond_particle_defaults(&t->particles[i]);
        t->particles[i].x0 = x0 + dx[i];
        t->particles[i].y0 = y0;
        t->particles[i].z0 = z0;
    }
}

void ibond_config_mock(CPUUSER cpuuser)
{
    BondTable *t;
    Particle *p;

    if (cpuuser == NULL) return;

    if (cpuuser->ibond_verify_case >= 5 && cpuuser->ibond_verify_case <= 8)
        cpuuser->ibond_level = 1;

    if (cpuuser->ibond_verify_case >= 9 && cpuuser->ibond_verify_case <= 11)
    {
        BondTable *t2;
        Particle *p2;

        cpuuser->ibond_level = 2;
        t2 = &cpuuser->ibond_mgr.table;
        ibond_table_free(t2);
        ibond_table_init(t2);
        ibond_table_reserve_particles(t2, 1);
        p2 = &t2->particles[0];
        ibond_particle_defaults(p2);
        /* near centroid of CPS3 elem 60: ~(0.0467, 0.0567, 0.1), offset +x */
        p2->x0 = 0.06;
        p2->y0 = 0.056667;
        p2->z0 = 0.1;
        return;
    }

    /* Level-1 Case E/F/G/H: 3 particles near same interface node */
    if (cpuuser->ibond_verify_case >= 5 && cpuuser->ibond_verify_case <= 8)
    {
        ibond_config_three_particles(cpuuser, 0.06, 0.05, 0.1);
        return;
    }

    t = &cpuuser->ibond_mgr.table;
    ibond_table_free(t);
    ibond_table_init(t);
    ibond_table_reserve_particles(t, 1);

    p = &t->particles[0];
    ibond_particle_defaults(p);

    if (cpuuser->ibond_verify_case == 3)
    {
        p->x0 = 1.0;
        p->y0 = 0.05;
        p->z0 = 0.1;
        return;
    }

    p->x0 = 0.06;
    p->y0 = 0.05;
    p->z0 = 0.1;
}

void ibond_free_tables(CPUUSER cpuuser)
{
    if (cpuuser == NULL) return;
    ibond_mgr_clear(&cpuuser->ibond_mgr);
    cpuuser->nibond = 0;
}

void ibond_identify(CPUCORE cpucore, CPUUSER cpuuser)
{
    ibond_mgr_identify(cpucore, cpuuser, &cpuuser->ibond_mgr);
}
