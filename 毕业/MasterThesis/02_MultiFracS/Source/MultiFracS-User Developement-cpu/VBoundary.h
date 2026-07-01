#include "Real.h"  
USERDLL void Read_seismic_data();
USERDLL void User_node_velocity_boundary(
	int itype, int nstep, Real dtm,
	Real fx, Real fy, Real fz,
	Real* x, Real* y, Real* z,
	Real* vx, Real* vy, Real* vz,
	int* ifix, int* ifiy, int* ifiz);
USERDLL void User_node_velocity_boundary_GPU(
	const int itype, const Real value,
	const Real* x, const Real* y, const Real* z,
	Real* vx, Real* vy, Real* vz,
	int* ifix, int* ifiy, int* ifiz);


