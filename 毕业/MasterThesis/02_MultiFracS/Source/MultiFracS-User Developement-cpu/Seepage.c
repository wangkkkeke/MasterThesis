#include "Real.h"  
#include "Seepage.h"
#include <math.h>
#include <stdio.h>
void Pore_seepage_Ela(int imat, Real p, Real sat, int nstep, Real* Ela, Real* vp)
{
	//imat从0开始，按照*Material关键词在inp文件中出现的顺序
	//p压力，sat饱和度， nstep时间步数， Ela 弹性模量，vp泊松比
	//将Ela,vp写成p,sat或nstep的函数 *Ela=f1(p,nstep)  *vp=f2(p,nstep)
}

void Pore_seepage_kf(int imat, Real p, Real sat, int nstep, Real* kf11, Real* kf22, Real* kf33)
{
	//将kf写成p或nstep的函数 *km11=f(p,nstep)
}

void Pore_seepage_contact_fric(int imat, Real p, Real sat, int nstep, Real* fric)
{
	//接触摩擦系数
}


void Pore_seepage_ft(int imat, Real p, Real sat, int nstep, Real* ft)
{
	//将ft写成p或nstep的函数 *ft=f(p,nstep)
}

void Pore_seepage_co(int imat, Real p, Real sat, int nstep, Real* co)
{
	//将co写成p或nstep的函数 *co=f(p,nstep)
}

void Pore_seepage_fric(int imat, Real p, Real sat, int nstep, Real* fric)
{
	//将co写成p或nstep的函数 *fric=f(p,nstep)
}

void Pore_seepage_gi(int imat, Real p, Real sat, int nstep, Real* gi)
{
	//将gi写成p或nstep的函数 *gi=f(p,nstep)
}

void Pore_seepage_gii(int imat, Real p, Real sat, int nstep, Real* gii)
{
	//将gi写成p或nstep的函数 *gi=f(p,nstep)
}

