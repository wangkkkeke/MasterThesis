#ifndef IBOND_PROVIDER_H
#define IBOND_PROVIDER_H

#include "ibond_types.h"

typedef enum {
    IBOND_PROVIDER_MOCK = 0,
    IBOND_PROVIDER_CPUCORE = 1
} IbondProviderKind;

IbondProviderKind ibond_provider_kind(CPUUSER cpuuser);

int ibond_provider_count(CPUCORE cpucore, CPUUSER cpuuser);

int ibond_provider_fill_particle(CPUCORE cpucore, CPUUSER cpuuser,
                                 int index, Particle *out);

void ibond_provider_probe(CPUCORE cpucore, CPUUSER cpuuser);

int ibond_provider_sync_to_table(CPUCORE cpucore, CPUUSER cpuuser, BondTable *table);

int ibond_provider_particle_active(const Particle *p, IbondProviderKind kind);

void ibond_provider_log_identify(CPUCORE cpucore, CPUUSER cpuuser, int nibond);

void ibond_provider_log_bond_force(CPUCORE cpucore, CPUUSER cpuuser);

void ibond_provider_log_apply(CPUCORE cpucore, CPUUSER cpuuser);

#endif
