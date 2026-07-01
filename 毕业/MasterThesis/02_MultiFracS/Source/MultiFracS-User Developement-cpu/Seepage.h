#ifndef SEEPAGE_H
#define SEEPAGE_H
USERDLL void Pore_seepage_Ela(int imat, Real p, Real sat, int nstep, Real* Ela, Real* vp);
USERDLL void Pore_seepage_kf(int imat, Real p, Real sat, int nstep, Real* kf11, Real* kf22, Real* kf33);
USERDLL void Pore_seepage_contact_fric(int imat, Real p, Real sat, int nstep, Real* fric);

USERDLL void Pore_seepage_ft(int imat, Real p, Real sat, int nstep, Real* ft);
USERDLL void Pore_seepage_co(int imat, Real p, Real sat, int nstep, Real* co);
USERDLL void Pore_seepage_fric(int imat, Real p, Real sat, int nstep, Real* fric);
USERDLL void Pore_seepage_gi(int imat, Real p, Real sat, int nstep, Real* gi);
USERDLL void Pore_seepage_gii(int imat, Real p, Real sat, int nstep, Real* gii);
#endif

