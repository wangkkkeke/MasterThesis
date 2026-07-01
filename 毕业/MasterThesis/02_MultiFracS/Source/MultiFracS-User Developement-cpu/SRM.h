#include "Real.h"  
USERDLL void Reduction_contact_fric(int ematid, Real x, Real y, Real z,	Real* ctfric);
USERDLL void Reduction_joint_fric_co(int jematid, Real x, Real y, Real z, Real* jfric, Real* jco);
USERDLL void Centrifugal_load(int nstep, Real dtm, Real* dfscl);

USERDLL void Set_contact_fric_as_function_of_vs(int nstep, Real dtm, Real vs, Real* fric, int ieflag, int jeflag);
