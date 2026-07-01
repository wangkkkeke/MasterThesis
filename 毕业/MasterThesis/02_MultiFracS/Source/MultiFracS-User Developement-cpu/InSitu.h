#include "Real.h"  
USERDLL void Read_inital_data();
USERDLL void Get_geostress_from_file_2D(int nelem, Real* d1dnix, Real* d1dniy, Real* d2egestress);
USERDLL void Get_geostress_from_file_3D(int nelem, Real* d1dnix, Real* d1dniy, Real* d1dniz, Real* d2egestress);
USERDLL void Get_pore_pressure_from_file_2D(int nfn, Real* d1fnix, Real* d1fniy, Real* d1fnpopre);
USERDLL void Get_pore_pressure_from_file_3D(int nfn, Real* d1fnix, Real* d1fniy, Real* d1fniz, Real* d1fnpopre);
USERDLL void InitVel(int itype, Real x, Real y, Real z, Real v[3]);
USERDLL void InitSituStress(int itype, int nstep, Real dtm, Real x, Real y, Real z, Real T[3][3]);
USERDLL void InitCrackSat(int itype, Real x, Real y, Real z, Real* sat);
USERDLL void InitCrackPressure(int itype, Real x, Real y, Real z, Real* p);
USERDLL void InitProppant(int itype, Real x, Real y, Real z, Real* c);
USERDLL void InitPoreSat(int itype, Real x, Real y, Real z, Real* sat);
USERDLL void InitPorePre(int itype, Real x, Real y, Real z, Real* p);
USERDLL void InitSolidTemperature(int itype, Real x, Real y, Real z, Real* T);
USERDLL void InitFluidTemperature(int itype, Real x, Real y, Real z, Real* T);
USERDLL void InitIceRatio(int itype, Real x, Real y, Real z, Real* si);
USERDLL void InitMoisture(int itype, Real x, Real y, Real z, Real* w);


