#ifndef THERMAL_H
#define THERMAL_H
#include "Real.h"  
USERDLL void Thermal_ro(int imat, Real T, Real Tmin, Real Tmax, int step, Real dtt, Real* ro);
USERDLL void Thermal_Ela(int imat, Real T, Real Tmin, Real Tmax, int step, Real dtt, Real Ela0, Real* Ela, Real* vp);
USERDLL void Thermal_alfa(int imat, Real T, Real Tmin, Real Tmax, int step, Real dtt, Real damage, Real* alfa);
USERDLL void Thermal_kt(int imat, Real T, Real Tmin, Real Tmax, int step, Real dtt, Real damage, Real* kt11, Real* kt22, Real* kt33);
USERDLL void Thermal_cp(int imat, Real T, Real Tmin, Real Tmax, int step, Real dtt, Real damage, Real* cp);
USERDLL void Thermal_kf(int imat, Real T, Real Tmin, Real Tmax, int nstep, Real dtt, Real damage, Real* kf11, Real* kf22, Real* kf33);
USERDLL void Thermal_contact_fric(int imat, Real T, Real Tmin, Real Tmax, int nstep, Real dtt, Real damage, Real* fric);

USERDLL void Thermal_ft(int imat, Real T, Real Tmin, Real Tmax, int step, Real dtt, Real* ft);
USERDLL void Thermal_co(int imat, Real T, Real Tmin, Real Tmax, int step, Real dtt, Real* co);
USERDLL void Thermal_fric(int imat, Real T, Real Tmin, Real Tmax, int step, Real dtt, Real* fric);
USERDLL void Thermal_gi(int imat, Real T, Real Tmin, Real Tmax, int nstep, Real dtt, Real* gi);
USERDLL void Thermal_gii(int imat, Real T, Real Tmin, Real Tmax, int nstep, Real dtt, Real* gii);

USERDLL void Thermal_w(Real T, Real* w);

USERDLL void Thermal_roi(Real T, Real* roi);
USERDLL void Thermal_beta(Real T, Real* beta);
USERDLL void Thermal_crfluid_vis(Real T, Real* vis);

#endif


