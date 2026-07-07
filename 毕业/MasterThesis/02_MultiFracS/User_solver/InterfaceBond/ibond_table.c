#include "ibond_types.h"
#include "../Cpucore.h"
#include "../Standard_library.h"

void ibond_table_init(BondTable *t)
{
    if (t == NULL) return;
    memset(t, 0, sizeof(BondTable));
}

void ibond_table_free(BondTable *t)
{
    if (t == NULL) return;
    free(t->anchors);
    free(t->entities);
    free(t->particles);
    free(t->bonds);
    free(t->forces);
    memset(t, 0, sizeof(BondTable));
}

void ibond_table_clear(BondTable *t)
{
    if (t == NULL) return;
    t->nbond = 0;
    t->nanchors = 0;
    t->nentities = 0;
}

static int ibond_table_grow_bonds(BondTable *t)
{
    int newcap;
    BondPair *nb;
    BondForce *nf;

    if (t->nbond < t->capacity)
        return 1;

    newcap = (t->capacity > 0) ? t->capacity * 2 : 4;
    nb = (BondPair *)realloc(t->bonds, (size_t)newcap * sizeof(BondPair));
    nf = (BondForce *)realloc(t->forces, (size_t)newcap * sizeof(BondForce));
    if (nb == NULL || nf == NULL)
        return 0;

    t->bonds = nb;
    t->forces = nf;
    t->capacity = newcap;
    return 1;
}

static int ibond_table_grow_anchors(BondTable *t)
{
    int newcap;
    BondAnchor *na;

    if (t->nanchors < t->acapacity)
        return 1;

    newcap = (t->acapacity > 0) ? t->acapacity * 2 : 4;
    na = (BondAnchor *)realloc(t->anchors, (size_t)newcap * sizeof(BondAnchor));
    if (na == NULL)
        return 0;

    t->anchors = na;
    t->acapacity = newcap;
    return 1;
}

int ibond_table_reserve_particles(BondTable *t, int n)
{
    Particle *np;

    if (t == NULL || n <= 0 || n > IBOND_MAX_PARTICLES)
        return 0;

    np = (Particle *)realloc(t->particles, (size_t)n * sizeof(Particle));
    if (np == NULL)
        return 0;

    t->particles = np;
    t->nparticles = n;
    return 1;
}

static int ibond_table_grow_entities(BondTable *t)
{
    int newcap;
    InterfaceEntity *ne;

    if (t->nentities < t->ecapacity)
        return 1;

    newcap = (t->ecapacity > 0) ? t->ecapacity * 2 : 4;
    ne = (InterfaceEntity *)realloc(t->entities, (size_t)newcap * sizeof(InterfaceEntity));
    if (ne == NULL)
        return 0;

    t->entities = ne;
    t->ecapacity = newcap;
    return 1;
}

int ibond_table_has_bond_entity(const BondTable *t, int entity_index, int particle_index)
{
    int i;
    if (t == NULL) return 0;
    for (i = 0; i < t->nbond; i++)
    {
        if (t->bonds[i].entity_index == entity_index &&
            t->bonds[i].sphere_index == particle_index)
            return 1;
    }
    return 0;
}

int ibond_table_add_entity(BondTable *t, const InterfaceEntity *ent)
{
    int idx;

    if (t == NULL || ent == NULL) return -1;

    if (!ibond_table_grow_entities(t))
        return -1;

    idx = t->nentities;
    t->entities[idx] = *ent;
    t->nentities++;
    return idx;
}

int ibond_table_find_anchor(const BondTable *t, int node_id)
{
    int i;
    if (t == NULL) return -1;
    for (i = 0; i < t->nanchors; i++)
        if (t->anchors[i].node_id == node_id)
            return i;
    return -1;
}

int ibond_table_has_bond(const BondTable *t, int anchor_index, int particle_index)
{
    int i;
    if (t == NULL) return 0;
    for (i = 0; i < t->nbond; i++)
    {
        if (t->bonds[i].entity_index >= 0)
            continue;
        if (t->bonds[i].anchor_index == anchor_index &&
            t->bonds[i].sphere_index == particle_index)
            return 1;
    }
    return 0;
}

int ibond_table_add_anchor(BondTable *t, CPUCORE cpucore, int node_id)
{
    int idx;
    BondAnchor *a;

    idx = ibond_table_find_anchor(t, node_id);
    if (idx >= 0)
        return idx;

    if (!ibond_table_grow_anchors(t))
        return -1;

    idx = t->nanchors;
    a = &t->anchors[idx];
    memset(a, 0, sizeof(BondAnchor));
    a->kind = IBOND_ANCHOR_NODE;
    a->node_id = node_id;
    if (cpucore != NULL && node_id >= 0 && node_id < cpucore->nfn)
    {
        a->x = cpucore->d1fnix[node_id];
        a->y = cpucore->d1fniy[node_id];
        a->z = cpucore->d1fniz[node_id];
    }
    a->nx = 1.0;
    a->ny = 0.0;
    a->nz = 0.0;
    t->nanchors++;
    return idx;
}

int ibond_table_add_bond(BondTable *t, int anchor_index, int particle_index,
                         Real kn, Real kt, Real dist)
{
    BondPair *bp;

    if (t == NULL || anchor_index < 0 || particle_index < 0)
        return 0;
    if (ibond_table_has_bond(t, anchor_index, particle_index))
        return 0;
    if (!ibond_table_grow_bonds(t))
        return 0;

    bp = &t->bonds[t->nbond];
    bp->anchor_index = anchor_index;
    bp->entity_index = -1;
    bp->sphere_index = particle_index;
    bp->kn = kn;
    bp->kt = kt;
    bp->rcut_at_build = dist;
    bp->broken = 0;
    t->forces[t->nbond].fem_fx = R0;
    t->forces[t->nbond].fem_fy = R0;
    t->forces[t->nbond].fem_fz = R0;
    t->forces[t->nbond].dem_fx = R0;
    t->forces[t->nbond].dem_fy = R0;
    t->forces[t->nbond].dem_fz = R0;
    t->nbond++;
    return 1;
}

int ibond_table_add_bond_entity(BondTable *t, int entity_index, int particle_index,
                                Real kn, Real kt, Real dist)
{
    BondPair *bp;

    if (t == NULL || entity_index < 0 || particle_index < 0)
        return 0;
    if (ibond_table_has_bond_entity(t, entity_index, particle_index))
        return 0;
    if (!ibond_table_grow_bonds(t))
        return 0;

    bp = &t->bonds[t->nbond];
    bp->anchor_index = -1;
    bp->entity_index = entity_index;
    bp->sphere_index = particle_index;
    bp->kn = kn;
    bp->kt = kt;
    bp->rcut_at_build = dist;
    bp->broken = 0;
    t->forces[t->nbond].fem_fx = R0;
    t->forces[t->nbond].fem_fy = R0;
    t->forces[t->nbond].fem_fz = R0;
    t->forces[t->nbond].dem_fx = R0;
    t->forces[t->nbond].dem_fy = R0;
    t->forces[t->nbond].dem_fz = R0;
    t->nbond++;
    return 1;
}

int ibond_table_remove_at(BondTable *t, int bond_index)
{
    int i;

    if (t == NULL || bond_index < 0 || bond_index >= t->nbond)
        return 0;

    for (i = bond_index; i < t->nbond - 1; i++)
    {
        t->bonds[i] = t->bonds[i + 1];
        t->forces[i] = t->forces[i + 1];
    }
    t->nbond--;
    return 1;
}
