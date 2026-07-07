#ifndef IBOND_TABLE_H
#define IBOND_TABLE_H

#include "ibond_types.h"
#include "../Cpucore.h"

void ibond_table_init(BondTable *t);
void ibond_table_free(BondTable *t);
void ibond_table_clear(BondTable *t);
int  ibond_table_reserve_particles(BondTable *t, int n);
int  ibond_table_find_anchor(const BondTable *t, int node_id);
int  ibond_table_has_bond(const BondTable *t, int anchor_index, int particle_index);
int  ibond_table_has_bond_entity(const BondTable *t, int entity_index, int particle_index);
int  ibond_table_add_anchor(BondTable *t, CPUCORE cpucore, int node_id);
int  ibond_table_add_entity(BondTable *t, const InterfaceEntity *ent);
int  ibond_table_add_bond(BondTable *t, int anchor_index, int particle_index,
                          Real kn, Real kt, Real dist);
int  ibond_table_add_bond_entity(BondTable *t, int entity_index, int particle_index,
                                 Real kn, Real kt, Real dist);
int  ibond_table_remove_at(BondTable *t, int bond_index);

#endif
