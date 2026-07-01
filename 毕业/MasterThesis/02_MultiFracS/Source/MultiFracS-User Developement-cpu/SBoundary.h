#include "Real.h"  
USERDLL void User_surface_force_boundary(
	int itype, int nstep, Real dtm,
	Real Ela, Real vp, Real ro,
	Real x, Real y, Real z,
	Real vn, Real vs,
	Real* pre, Real* tao);

USERDLL void Mech_crack_force_boundary(Real x, Real y, Real z, int nstep, Real dtm, Real* pre);
