#include "Real.h"  
USERDLL void FGM_ela(int ie, Real x, Real y, Real z, Real* ela);
USERDLL void FGM_vp(int ie, Real x, Real y, Real z, Real* vp);
USERDLL void FGM_ro(int ie, Real x, Real y, Real z, Real* ro);
USERDLL void FGM_kt(int ie, Real x, Real y, Real z, Real* k11, Real* k22, Real* k33, Real* k12, Real* k23, Real* k31);
USERDLL void FGM_tec(int ie, Real x, Real y, Real z, Real* tec);
USERDLL void FGM_cp(int ie, Real x, Real y, Real z, Real* cp);
USERDLL void FGM_km(int ie, Real x, Real y, Real z, Real* km11, Real* km22, Real* km33, Real* km12, Real* km21, Real* km31);
USERDLL void FGM_alfa(int ie, Real x, Real y, Real z, Real* alfa);
USERDLL void FGM_kf(int ie, Real x, Real y, Real z, Real* kf11, Real* kf22, Real* kf33, Real* kf12, Real* kf21, Real* kf31);
USERDLL void FGM_np(int ie, Real x, Real y, Real z, Real* np);
USERDLL void FGM_joint(int nje, int je, Real x, Real y, Real z,
	Real* pn, Real* pt, Real* ft, Real* co, Real* fric, Real* gi, Real* gii, int* ijebk, Real* am0,
	Real* a0, Real* amin, Real* amax,
	Real len);
