#ifndef CPUUSER_H
#define CPUUSER_H
#include "Real.h"

struct CPUUSER_struct
{
    /* framework fields (do not remove) */
    char userInputFileName[100];
    int  nuser;
    int  nuserstep;
    Real dusertime;
    Real duserdt;

    /* -------------------------------------------------------
     * InterfaceBond fields (Issue002)
     * Naming matches CPUCORE convention: i1xxx=int[], d1xxx=Real[]
     * Proxy = SPH element centroid (see ADR001, ibond_init.c)
     * ------------------------------------------------------- */

    /* Bond count and pair arrays */
    int   nibond;        /* number of InterfaceBond pairs */
    int  *i1ibsphid;     /* [nibond] FEM-side SPH element index */
    int  *i1ibdnid;      /* [nibond] DEM discrete node index */

    /* Per-bond stiffness (supports heterogeneous calibration) */
    Real *d1ibkn;        /* [nibond] normal stiffness Kn (Pa/m) */
    Real *d1ibkt;        /* [nibond] shear stiffness  Kt (Pa/m) */

    /* Accumulated bond forces (updated each step) */
    Real *d1ibfnx;       /* [nibond] normal force x (N) */
    Real *d1ibfny;       /* [nibond] normal force y (N) */
    Real *d1ibfnz;       /* [nibond] normal force z (N) */
    Real *d1ibfsx;       /* [nibond] shear force x (N) */
    Real *d1ibfsy;       /* [nibond] shear force y (N) */
    Real *d1ibfsz;       /* [nibond] shear force z (N) */
    int  *i1ibbk;        /* [nibond] broken flag: 0=intact 1=tensile 2=shear */

    /* Global calibration parameters (read from inp *InterfaceBond) */
    Real ibond_kn;       /* default normal stiffness (Pa/m) */
    Real ibond_kt;       /* default shear  stiffness (Pa/m) */
    Real ibond_ft;       /* tensile strength (Pa) */
    Real ibond_fs;       /* shear  strength base value (Pa) */
    Real ibond_phi;      /* friction angle (rad) */
    Real ibond_rcut;     /* identification cutoff distance (m) */
};

#endif
