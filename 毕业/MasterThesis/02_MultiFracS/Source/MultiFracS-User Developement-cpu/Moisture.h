
#ifndef MOISTURE_FUNCTION_H
#define MOISTURE_FUNCTION_H
#include "Real.h"  
USERDLL void Moisture_Ela(int imat, Real w, int nstep, Real dtw, Real* Ela, Real* vp);
USERDLL void Moisture_km(int imat, Real w, Real T, int nstep, Real dtw, Real* km11, Real* km22, Real* km33);
USERDLL void Moisture_alfa(int imat, Real w, int nstep, Real dtw, Real* alfa);
USERDLL void Moisture_contact_fric(int imat, Real w, int nstep, Real dtw, Real* fric);

USERDLL void Moisture_ft(int imat, Real w, int nstep, Real dtw, Real* ft);
USERDLL void Moisture_co(int imat, Real w, int nstep, Real dtw, int* userstep, Real* co);
USERDLL void Moisture_fric(int imat, Real w, int nstep, Real dtw, Real* fric);
USERDLL void Moisture_gi(int imat, Real w, int nstep, Real dtw, Real* gi);
USERDLL void Moisture_gii(int imat, Real w, int nstep, Real dtw, Real* gii);
#endif