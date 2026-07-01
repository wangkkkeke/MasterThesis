#include "Real.h"  
#include "Mech.h"
#include <math.h>
#include <stdio.h>
void Mech_hjt(int imat, Real damagej, int nstep, Real dt, Real* hjt)
{
	//imat从0开始，按照*Material关键词和*Joint在inp文件中出现的顺序进行整体编号
	//damagej节理单元的损伤系数， nstep时间步数， dt时间步长
	//将节理单元换热系数htj写成damagej或nstep的函数 *hjt=f1(damagej,nstep)
}

void Mech_hjf(int imat, Real damagej, int nstep, Real dt, Real* hjf)
{
	//imat从0开始，按照*Material关键词和*Joint在inp文件中出现的顺序进行整体编号
	//damagej节理单元的损伤系数， nstep时间步数， dt时间步长
	//将节理单元换流系数hjf写成damagej或nstep的函数 *hjf=f1(damagej,nstep)
}

void Mech_hjw(int imat, Real damagej, int nstep, Real dt, Real* hjw)
{
	//imat从0开始，按照*Material关键词和*Joint在inp文件中出现的顺序进行整体编号
	//damagej节理单元的损伤系数， nstep时间步数， dt时间步长
	//将节理单元换湿系数hjw写成damagej或nstep的函数 *hjw=f1(damagej,nstep)
}

void Mech_kf(int imat, Real sigma[3][3], Real strain[3][3], Real pc, Real biot, int nstep, Real dt, Real* kf11, Real* kf22, Real* kf33)
{
	//imat从0开始，按照*Material关键词在inp文件中出现的顺序进行整体编号
	//sigma[3][3]应力张量， strain[3][3]应变张量，pc孔隙压力，biot比奥系数
	//nstep时间步数， dt时间步长
	//将实体单元的渗透率kf写成应力的函数 *kf11=f1(sigma[0][0],nstep)
	
}

void Mech_Ela(int imat, Real sigma[3][3], Real strain[3][3], int nstep, Real dt, Real Ela0, Real* Ela, Real* vp)
{
	//imat从0开始，按照*Material关键词在inp文件中出现的顺序进行整体编号
	//nstep时间步数，dt时间步长，Ela0初始弹性模量， *vp泊松比
	//将弹性模量表示应力、时间步等的函数 *Ela=f1(sigma[0][0],nstep)
}

void Mech_grout(int nstep, Real x, Real y, Real z, Real pc, int* ijebk)
{
	//nstep时间步数， x,y,z节理单元的坐标，pc节理单元的裂隙压力
	//将*ijebk设置为-10，则这个节理单元被施加注浆加固
	if (x >= 0.4 && x <= 0.6 && y >= 0.3 && y <= 0.7)
	{
		if (nstep > 10000 && pc >= 3e6)
		{
			*ijebk = -10;  // 施加注浆加固
		}
	}
}