#include "Real.h"  
USERDLL void Read_boundary_data();
USERDLL void Thermal_volume_heat_source_intensity(int* numid, int** i1nid, Real** d1nH);
USERDLL void Thermal_solid_T_boundary(int itype, int nstep, Real dtt, Real dtm, Real x, Real y, Real z, Real* T);
USERDLL void Thermal_solid_qTflow_boundary(int itype, int nstep, Real dtt, Real dtm, Real T, Real x, Real y, Real z, Real* qflow);
USERDLL void Thermal_solid_qTflow_per_area_boundary(int itype, int nstep, Real dtt, Real dtm, Real* qflow);
USERDLL void Thermal_crack_boundary(int nstep, Real dtt, Real dtm, int bkstep, Real x, Real y, Real z, int* itype, Real* hgas, Real* Tgas, Real* Ts1, Real* Ts2, Real* qarea1, Real* qarea2);
USERDLL void Moisture_w_boundary(int itype, int nstep, Real dtw, Real dtm, Real x, Real y, Real z, Real* w);
USERDLL void Moisture_qflow_boundary(int itype, int nstep, Real dtw, Real dtm, Real* qflow);
USERDLL void Moisture_qflow_per_area_boundary(int itype, int nstep, Real dtw, Real dtm, Real* qflow);
USERDLL void Moisture_crack_boundary(int nstep, Real dtw, Real dtm, int bkstep, Real x, Real y, Real z, int* itype, Real* hgas, Real* wgas, Real* wc1, Real* wc2, Real* qarea1, Real* qarea2);
USERDLL void Crack_seepage_p_boundary(int itype, int nstep, Real dtf, Real dtm, Real x, Real y, Real z, Real* p);
USERDLL void Crack_seepage_qflow_boundary(int itype, int nstep, Real dtf, Real dtm, Real* qflow);
USERDLL void Crack_seepage_qflow_per_area_boundary(int itype, int nstep, Real dtf, Real dtm, Real* qflow);
USERDLL void Proppant_c_boundary(int itype, int nstep, Real dtf, Real dtm, Real x, Real y, Real z, Real* c);
USERDLL void Proppant_qflow_boundary(int itype, int nstep, Real dtf, Real dtm, Real* qflow);
USERDLL void Pore_seepage_p_boundary(int itype, int nstep, Real dtf, Real dtm, Real x, Real y, Real z, Real* p);
USERDLL void Pore_seepage_qflow_boundary(int itype, int nstep, Real dtf, Real dtm, Real* qflow);
USERDLL void Pore_seepage_qflow_per_area_boundary(int itype, int nstep, Real dtf, Real dtm, Real* qflow);
