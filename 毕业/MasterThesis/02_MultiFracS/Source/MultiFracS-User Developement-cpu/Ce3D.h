#include "Real.h"  
USERDLL void Tet_constitutive_equation_increment(
	Real G, Real lamda, int imat,
	Real de11, Real de22, Real de33,
	Real de12, Real de23, Real de31,
	Real* s11, Real* s22, Real* s33,
	Real* s12, Real* s23, Real* s31
);
