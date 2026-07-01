#include "Real.h"  
#include "Moisture.h"
#include <math.h>
#include <stdio.h>
void Moisture_Ela(int imat, Real w, int nstep, Real dtw, Real* Ela, Real* vp)
{
	//imat从0开始，按照*Material关键词在inp文件中出现的顺序, w含水率， nstep时间步数， dtw湿度计算时间步长， Ela 弹性模量，vp泊松比
	//将Ela,vp写成w或nstep的函数 *Ela=f1(w,nstep,dtw)  *vp=f2(w,nstep,dtw)
}

void Moisture_km(int imat, Real w, Real T, int nstep, Real dtw, Real* km11,Real* km22, Real* km33)
{
	//将km写成w，T，nstep的函数 *km11=f(w,T,nstep,dtw)
}

void Moisture_alfa(int imat, Real w, int nstep, Real dtw, Real* alfa)
{
	//将收缩系数，改成w或者nstep的函数  *alfa=f(w,nstep,dtw)
} 

void Moisture_contact_fric(int imat, Real w, int nstep, Real dtw, Real* fric)
{
	//接触摩擦系数
}



void Moisture_ft(int imat, Real w, int nstep, Real dtw, Real* ft)
{
	//将ft写成w或nstep的函数 *ft=f(w,nstep,dtw)
}

void Moisture_co(int imat, Real w, int nstep, Real dtw, int* userstep, Real* co)
{
	//将co写成w或nstep的函数 *ft=f(w,nstep,dtw)
	//*userstep用于记录特定步数，以便后续改变粘聚力以*userstep作为起点
	//*co = 50e6 * pow((w * 100), -0.93);
}

void Moisture_fric(int imat, Real w, int nstep, Real dtw, Real* fric)
{
	//将节理单元摩擦系数fric写成w或nstep的函数 *ft=f(w,nstep,dtw)
}

void Moisture_gi(int imat, Real w, int nstep, Real dtw, Real* gi)
{
	//将I型断裂能gi写成w或nstep的函数 *ft=f(w,nstep,dtw)
}

void Moisture_gii(int imat, Real w, int nstep, Real dtw, Real* gii)
{
	//将II型断裂能gii写成w或nstep的函数 *ft=f(w,nstep,dtw)
}