#include "Real.h"  
#include "Bhm.h"
#include <math.h>
#include <stdio.h>
void Bingham_fluid(Real deltp, Real a, Real len, Real ft0, Real kj, Real* qi)
{
	//kj=1/(12*Á÷ÌåÕ³ÐÔ£©
	if (fabs(deltp / len) > (2.0 * ft0) / a)
	{
		*qi = -kj * a * a * a * deltp / len * (1 - 3.0 * ft0 * len / (fabs(deltp) * a) + 4.0 * pow(((ft0 * len) / (fabs(deltp) * a)), 3.0));
	}
	else
	{
		*qi = 0;
	}
}

Real Unsatfs(Real sat)
{
	return sat * sat * (3.0 - 2.0 * sat);
}