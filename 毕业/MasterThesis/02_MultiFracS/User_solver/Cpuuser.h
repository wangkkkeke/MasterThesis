#ifndef CPUUSER_H
#define CPUUSER_H
#include "Real.h"
#include "InterfaceBond/ibond_types.h"

struct CPUUSER_struct
{
    char userInputFileName[100];
    int  nuser;
    int  nuserstep;
    Real dusertime;
    Real duserdt;

    int   ibond_level;
    int   ibond_verify_case;
    int   nibond;

    BondManager ibond_mgr;

    Real  dev_anchor_ux;

    int  *i1ibsphid;
    int  *i1ibdnid;
    Real *d1ibkn;
    Real *d1ibkt;
    Real *d1ibfnx;
    Real *d1ibfny;
    Real *d1ibfnz;
    Real *d1ibfsx;
    Real *d1ibfsy;
    Real *d1ibfsz;
    int  *i1ibbk;

    Real ibond_kn;
    Real ibond_kt;
    Real ibond_ft;
    Real ibond_fs;
    Real ibond_phi;
    Real ibond_rcut;

    int  bench_kind;       /* 0=off 1=Benchmark01 2=Benchmark02 */
    int  bench1_test_id;
    Real bench1_sphere_x;
    Real bench1_sphere_y;
    Real bench1_sphere_z;
    Real bench1_particle_du_n;
    Real bench1_anchor_ux;
};

#endif
