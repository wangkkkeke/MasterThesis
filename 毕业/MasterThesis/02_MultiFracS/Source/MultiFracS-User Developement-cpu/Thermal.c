#include "Real.h"  
#include "Thermal.h"
#include <math.h>
#include <stdio.h>
void Thermal_ro(int imat, Real T, Real Tmin, Real Tmax, int nstep, Real dtt, Real* ro)
{
	//imat从0开始，按照*Material关键词在inp文件中出现的顺序
	//T温度，Tmin经历的最低温，Tmax经历的最高温度，nstep时间步数， dtt热学时间步长， Ela 弹性模量，vp泊松比
	//将密度ro写成T或nstep的函数 *ro=f1(T,nstep)
}

void Thermal_Ela(int imat, Real T, Real Tmin, Real Tmax, int nstep, Real dtt, Real Ela0, Real* Ela, Real* vp)
{
	//imat从0开始，按照*Material关键词在inp文件中出现的顺序
	//T温度， nstep时间步数， dtt热学时间步长， Ela 弹性模量，vp泊松比
	//将Ela,vp写成T或nstep的函数 *Ela=f1(T,nstep)  *vp=f2(T,nstep)
	//Ela0初始弹模
}

void Thermal_kt(int imat, Real T, Real Tmin, Real Tmax, int nstep, Real dtt, Real damage, Real* kt11, Real* kt22, Real* kt33)
{
	//将热传导系数kt写成T或nstep的函数 *kt11=f(T,nstep,dt)  dt为时间步长   damage为实体单元损伤变量
}

void Thermal_cp(int imat, Real T, Real Tmin, Real Tmax, int nstep, Real dtt, Real damage, Real* cp)
{
	//将比热cp写成T或nstep的函数 *cp=f(T,nstep,dt)  dt为时间步长 damage为实体单元损伤变量
}

void Thermal_alfa(int imat, Real T, Real Tmin, Real Tmax, int nstep, Real dtt, Real damage, Real* alfa)
{
	//将收缩系数，改成T或者nstep的函数  *alfa=f(T,nstep)
}

void Thermal_kf(int imat, Real T, Real Tmin, Real Tmax, int nstep, Real dtt, Real damage, Real* kf11, Real* kf22, Real* kf33)
{
	//将渗透率kf写成T或nstep的函数 *kf11=f(T,nstep,dt)  dt为时间步长   damage为实体单元损伤变量
}

void Thermal_contact_fric(int imat, Real T, Real Tmin, Real Tmax, int nstep, Real dtt, Real damage, Real* fric)
{
	//接触摩擦系数
}



void Thermal_ft(int imat, Real T, Real Tmin, Real Tmax, int nstep, Real dtt, Real* ft)
{
	//将ft写成T或nstep的函数 *ft=f(T,nstep)
}

void Thermal_co(int imat, Real T, Real Tmin, Real Tmax, int nstep, Real dtt, Real* co)
{
	//将co写成T或nstep的函数 *ft=f(T,nstep)
}

void Thermal_fric(int imat, Real T, Real Tmin, Real Tmax, int nstep, Real dtt, Real* fric)
{
	//将内摩擦系数fric写成T或nstep的函数 *ft=f(T,nstep)
}

void Thermal_gi(int imat, Real T, Real Tmin, Real Tmax, int nstep, Real dtt, Real* gi) //I型断裂能
{
	//将I型断裂gi写成T或nstep的函数 *ft=f(T,nstep)
}

void Thermal_gii(int imat, Real T, Real Tmin, Real Tmax, int nstep, Real dtt, Real* gii)  //II型断裂能
{
	//将II型断裂能gii写成T或nstep的函数 *ft=f(T,nstep)
}



void Thermal_w(Real T, Real* w)
{
	//将含水率*w写成温度T的函数
}


void Thermal_roi(Real T, Real* roi)  //冰的密度
{
	
}
void Thermal_beta(Real T, Real* ki) //冰水相变的体积膨胀系数
{

}
void Thermal_crfluid_vis(Real T, Real* vis) //裂隙流体粘性
{

}

