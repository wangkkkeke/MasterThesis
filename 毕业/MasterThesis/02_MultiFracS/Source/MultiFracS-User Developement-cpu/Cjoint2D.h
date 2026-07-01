#include "Real.h"  
USERDLL void joint_model_intact_2d_user(
	Real o1, Real o2,
	Real s1, Real s2,
	Real h, Real e1x, Real e1y,
	Real pn, Real ps,
	Real co, Real fric, Real ft, Real gi, Real gii, Real o0,
	int imat, int* ijesf, int* ijebk, Real* djedamge,
	Real damge[3], Real djefs[3], Real ol[3], Real sl[3], Real omax[3], Real smax[3],
	Real p1, Real p2,
	Real fx[2], Real fy[2]
);

USERDLL void joint_model_broken_2D_user(
	Real o1, Real o2,
	Real s1, Real s2,
	Real vs1, Real vs2, Real dtm,
	Real h, Real e1x, Real e1y,
	Real pn, Real ps,
	Real co, Real fric, Real ft, Real gi, Real gii, Real o0,
	int imat, int* ijesf, int* ijebk, Real* djedamge,
	Real damge[3], Real djefs[3], Real ol[3], Real sl[3],
	Real sign[3], Real ShearAmount[3], Real dsl[3],
	Real p1, Real p2,
	Real fx[2], Real fy[2]
);
