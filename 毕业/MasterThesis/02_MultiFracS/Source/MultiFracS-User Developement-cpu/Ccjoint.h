#include "Real.h"  
USERDLL void op_ot_sp_st_continuum(Real ft, Real fs, Real c,
	Real pn, Real ps,
	Real gi, Real gii, Real h,
	Real* ot, Real* st);

USERDLL void Cjoint_broken_continuum(Real o, Real s, Real h,
	Real pn, Real fric, Real ps,
	Real* sig, Real* tao);

USERDLL void  Cjoint_continuum(Real o, Real s, Real ot, Real st, Real h,
	Real pn, Real co, Real fric, Real ft, Real fs,
	int* nfail, int mfail,
	int* ijesf, int* ijebk, Real* djefs,
	Real* sig, Real* tao, Real* damge,
	Real* ol, Real* sl);
