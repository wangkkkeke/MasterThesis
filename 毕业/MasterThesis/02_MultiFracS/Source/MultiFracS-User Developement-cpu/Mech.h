#include "Real.h"  
USERDLL void Mech_hjt(int imat, Real damagej, int nstep, Real dt, Real* hjt);
USERDLL void Mech_hjf(int imat, Real damagej, int nstep, Real dt, Real* hjf);
USERDLL void Mech_hjw(int imat, Real damagej, int nstep, Real dt, Real* hjw);
USERDLL void Mech_kf(int imat, Real sigma[3][3], Real strain[3][3], Real pc, Real biot, int nstep, Real dt, Real* kf11, Real* kf22, Real* kf33);
USERDLL void Mech_Ela(int imat, Real sigma[3][3], Real strain[3][3], int nstep, Real dt, Real Ela0, Real* Ela, Real* vp);
USERDLL void Mech_grout(int nstep, Real x, Real y, Real z, Real pc, int* ijebk);
