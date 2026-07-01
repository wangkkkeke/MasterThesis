#include "Real.h"  
USERDLL void op_ot_sp_st(Real ft, Real fs, Real co,
	Real pn, Real ps,
	Real gi, Real gii, Real h,
	Real* op, Real* ot, Real* sp, Real* st);

USERDLL void  Cjoint(Real o, Real s, Real op, Real sp, Real ot, Real st,
	Real co, Real fric, Real ft, Real fs,
	int* nfail, int mfail,
	int* ijesf, int* ijebk, 
	Real* sig, Real* tao, Real* damge, int icjointdll,
	Real* omax, Real* smax, Real* aperture);

USERDLL void Cjoint_broken(int ijebk, Real o, Real s,
	Real op, Real sp,
	Real ot, Real st,
	Real h,
	Real ft, Real fric,
	Real pn, Real ps,
	Real* sig, Real* tao);