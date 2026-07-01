#include "Real.h"  
#include "Ce3D.h"
#include <math.h>
#include <stdio.h>
#include "Macro_math.h"

void Tet_constitutive_equation_increment(
	Real G, Real lamda, int imat,
	Real de11, Real de22, Real de33,
	Real de12, Real de23, Real de31,
	Real* s11, Real* s22, Real* s33,
	Real* s12, Real* s23, Real* s31
)
{
	Real ds11, ds22, ds33, ds12, ds23, ds31;
	ds11 = (R2 * G * de11 + lamda * (de11 + de22 + de33));
	ds22 = (R2 * G * de22 + lamda * (de11 + de22 + de33));
	ds33 = (R2 * G * de33 + lamda * (de11 + de22 + de33));
	ds12 = (R2 * G * de12);
	ds23 = (R2 * G * de23);
	ds31 = (R2 * G * de31);

	*s11 += ds11; //应变增量引起的应力增量
	*s22 += ds22;
	*s33 += ds33;
	*s12 += ds12;
	*s23 += ds23;
	*s31 += ds31;
}