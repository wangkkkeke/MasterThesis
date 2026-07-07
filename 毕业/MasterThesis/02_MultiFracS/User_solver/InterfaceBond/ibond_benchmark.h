#ifndef IBOND_BENCHMARK_H
#define IBOND_BENCHMARK_H

#include "ibond_types.h"

void ibond_benchmark_clear(CPUUSER cpuuser);

int ibond_benchmark_load_from_file(CPUUSER cpuuser, const char *filename);

int ibond_benchmark_is_active(CPUUSER cpuuser);

int ibond_benchmark_get_kind(CPUUSER cpuuser);

void ibond_benchmark_write_log(CPUCORE cpucore, CPUUSER cpuuser);

void ibond_benchmark_write_setup_log(CPUCORE cpucore, CPUUSER cpuuser);

void ibond_benchmark_write_vtk(CPUCORE cpucore, CPUUSER cpuuser);

#endif
