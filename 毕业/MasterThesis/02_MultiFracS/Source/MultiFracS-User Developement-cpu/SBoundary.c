#include "Real.h"  
#include "SBoundary.h"
#include <math.h>
#include <stdio.h>
void User_surface_force_boundary(
	int itype, int nstep, Real dtm,
	Real Ela, Real vp, Real ro, 
    Real x, Real y, Real z,
	Real vn, Real vs,
	Real* pre, Real* tao)
{
	//itype就是.inp文件中第*SForceBoundary中第一个数据的值，可取1-4之外的整数值，当存在多个自定义边界时，可用该整数加以区分
	//vn边界法向速度,vs边界切向速度，均为带符号的量，Ela弹性模量，vp泊松比
	
	//Real pi = 3.1415926535;
	//Real t = nstep * dtm;
	//Real wave;
	//if (t > 1.0 / 4.0)
	//	wave = 0.0;
	//else
	//	wave = 0.5 * (1 - cos(2 * pi * 4 * t));

	//if (itype == 10)
	//{
	//	*tao = -200000 * wave;
	//}

}

void Mech_crack_force_boundary(Real x, Real y, Real z, int nstep, Real dtm, Real* pre) //对裂缝(包括初始裂缝和新生成裂缝）施加用户自定义压力
{
	//nstep计算步数，dtm时间步长，nstep*dtm即为当前时间
	//*pre裂缝面上的法向压力 压为正，拉为负
	//Real t = nstep * dtm;
	//double P1 = 5e9;
	//double Lb = 0.2;
	//Real A = 0.27 * Lb;
	//Real B = 0.83 * Lb;
	//double C0 = 6900;
	//double alpha = 1.55;

	//if (t >= 0.000024)
	//{
	//	*pre = P1 * (A / (C0 * t - B)) / alpha;
	//}
}

