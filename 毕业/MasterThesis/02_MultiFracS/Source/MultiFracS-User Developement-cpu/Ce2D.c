#include "Real.h"  
#include "Ce2D.h"
#include <math.h>
#include <stdio.h>
#include "Macro_math.h"
#include "Macro_user.h"

void Tri_constitutive_equation_increment(
	Real Ela, Real vp, int istressOrstrain, int imat,
	Real de11, Real de22, Real de12,
	Real* s11, Real* s22, Real* s12
	)
{
	//Ela弹性模量, vp就是泊松比, istressOrstrain=1平面应力单元，!=1平面应变单元
	//imat材料编号 根据*Mat出现的顺序从0开始编号
	//de11 x方向的正应变增量，de22 y方向的正应变增量 de12剪应变增量
	//*s11是上一步的总正应力sigmaxx, *s22是上一步的总正应力sigmayy,
	//*s12是上一步的总剪应力sigmaxy
	//本构模型的本质是由应变增量求应力增量，最后得到当前步的总应力

	Real ds11, ds22, ds12;
	if (istressOrstrain == EType_S2D3) //平面应力单元
	{
		ds11 = Ela / (1 - vp * vp) * (de11 + vp * de22);
		ds22 = Ela / (1 - vp * vp) * (vp * de11 + de22);
		ds12 = Ela / (1 + vp) * de12;
	}
	else //平面应变
	{
		ds11 = Ela / ((1 + vp) * (-1 + R2 * vp)) * ((-1 + vp) * de11 - vp * de22);
		ds22 = Ela / ((1 + vp) * (-1 + R2 * vp)) * ((-1 + vp) * de22 - vp * de11);
		ds12 = Ela / (1 + vp) * de12;
	}

	*s11 += ds11; //应变增量引起的应力增量
	*s22 += ds22;
	*s12 += ds12;
}