#include "Real.h"  
USERDLL void Cjoint3D_intact(
	Real rs[][3], Real vnor[3], Real area,
	Real h,
	Real pn, Real ps,
	Real co, Real fric, Real ft, Real gi, Real gii,
	int imat, int* ijesf, int* ijebk, Real* damge, Real* d1jefs,
	Real p1, Real p2, Real p3,
	Real fnt[][3]
);

USERDLL void Cjoint3D_broken(
	Real rs[][3], Real vnor[3], Real area,
	Real h,
	Real pn, Real ps,
	Real co, Real fric, Real ft, Real gi, Real gii,
	int imat, int* ijesf, int* ijebk, Real* damge, 
	Real p1, Real p2, Real p3,
	Real fnt[][3]
);
