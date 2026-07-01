#include "Real.h"
USERDLL void op_ot_sp_st_user(Real ft, Real fs, Real c,
	Real pn, Real ps,
	Real gi, Real gii, Real h,
	Real* op, Real* ot, Real* sp, Real* st,
	int iflag
);

USERDLL void  Cjoint_user(Real o, Real s, Real op, Real sp, Real ot, Real st,
	Real co, Real fric, Real ft, Real fs,
	int* nfail, int mfail,
	int* ijesf, int* ijebk, Real* djefs,
	Real* sig, Real* tao, Real* damge,
	Real* ol, Real* sl, Real* aperture,
	Real* omax, Real* smax,
	int iflag
);

USERDLL void Cjoint_broken_user(int jflag, Real o, Real s,
	Real op, Real sp,
	Real ot, Real st,
	Real h,
	Real ft, Real fric,
	Real pn, Real ps,
	Real* sig, Real* tao,
	
	Real vs, Real dtm,
	Real* ol, Real* sl,
	Real* sigl, Real* taol,
	Real* aperture,
	Real* sign, Real* ShearAmount, Real* dsl,
	int iflag
);
