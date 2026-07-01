#include "Real.h"  
#include "FGM.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void FGM_ela(int ie, Real x, Real y, Real z, Real* ela)
{
	//*ela弹性模量
}
void FGM_vp(int ie, Real x, Real y, Real z, Real* vp)
{
	//*vp泊松比
}
void FGM_ro(int ie, Real x, Real y, Real z, Real* ro)
{
	//*ro密度
}


void FGM_kt(int ie,Real x, Real y, Real z, Real* k11, Real* k22, Real* k33, Real* k12, Real* k23, Real* k31)
{ 
	//ie实体单元编号从0开始
	//*k11,*k22,*k33为x,y,z轴三个方向的热传导系数
}
void FGM_tec(int ie, Real x, Real y, Real z, Real* tec)
{ 
	//*tec热膨胀系数
}
void FGM_cp(int ie, Real x, Real y, Real z, Real* cp)
{
	//*cp比热容
}


void FGM_km(int ie, Real x, Real y, Real z, Real* km11, Real* km22, Real* km33, Real* km12, Real* km21, Real* km31) 
{
	//km表示湿度传导系数张量
}
void FGM_alfa(int ie, Real x, Real y, Real z, Real* alfa) 
{
	//*alfa湿度膨系数
}


void FGM_kf(int ie, Real x, Real y, Real z, Real* kf11, Real* kf22, Real* kf33, Real* kf12, Real* kf21, Real* kf31)
{
	//*kf表示孔隙渗流渗透率
}
void FGM_np(int ie, Real x, Real y, Real z, Real* np)
{
	//*np表示孔隙率
}


void FGM_joint(int nje, int je, Real x, Real y, Real z,
	Real* pn, Real* pt, Real* ft, Real* co, Real* fric, Real* gi, Real* gii, int* ijebk, Real* am0,
	Real* a0, Real* amin, Real* amax,
	Real len)
{
	//nje总的节理单元数，je当前节理单元的编号，x,y,z节理单元中心的坐标
	//*pn节理单元法向罚参数 *pt节理单元切向罚参数
	//*ft抗拉强度，*co粘聚力，*fric内摩擦系数，*gi I型断裂能， *gii II型断裂能，
	//*jebk节理单元是否断裂及断裂类型 1-断裂 0未断裂  (传入的*ijebk可能取值为0未断裂，10表示初始裂缝 11-表示拉裂缝 12-表示剪切裂缝 13-表示拉剪裂缝）  
	//*am0节理单元虚拟力学张开度 设置该参数来考虑峰前压密
	//*a0,*amin,*amax分别表示节理单元初始张开度，最小张开度，最大张开度  裂隙渗流计算会用到
	//len 2D表示节理单元的长度 3D表示节理单元的面积

	//if (y >= 0 && y <= 0.1)
	//{
	//	double m, randNum;
	//	m = 10.0;  //均质度系数，取值越大，材料越均匀
	//	srand(1); //1作为种子
	//	for (int i = 0; i <= je; i++)
	//	{
	//		randNum = (double)(rand()+1) / (double)((RAND_MAX + 2.0)); //rand()返回0到RAND_MAX的伪随机数
	//		if (i == je)
	//		{
	//			*co = *co * pow((-log(1.0 - randNum)), (1.0 / m));
	//			if(*co<=0)
	//			{ 
	//			printf("%f\n", *co);
	//			}
	//		}
	//	}
	//}
}
