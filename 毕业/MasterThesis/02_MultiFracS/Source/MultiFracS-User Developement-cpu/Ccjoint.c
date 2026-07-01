#include "Real.h"  
#include "Ccjoint.h"
#include <math.h>
#include <stdio.h>

#define JEISOFT1 1
#define JEISOFT2 2
#define JEISOFT3 3
#define JEBKT1 11 //拉裂缝
#define JEBKT2 12 //剪裂缝
#define JEBKT3 13 //拉剪混合裂隙


void op_ot_sp_st_continuum(Real ft, Real fs, Real c,
	Real pn, Real ps,
	Real gi, Real gii, Real h,
	Real* ot, Real* st)
{
	*ot = R3 * gi / ft;
	*st = R3 * gii / c;

	//新的公式--2021-2-1 这个公式要写一篇论文
	//*ot=gi*(*op)*(pn/Ela);  //这样ot和st就是峰值法向位移和峰值剪切位移的多少倍
	//*st=gii*(*sp)*(pn/G);
}

//------断裂节理单元受压时
void Cjoint_broken_continuum(Real o, Real s, Real h,
	Real pn, Real fric, Real ps,
	Real* sig, Real* tao)
{
	Real sigma = pn * o / h;
	*sig = sigma;
	*tao = -sigma * fric;
}

//------未断裂节理单元
void  Cjoint_continuum(Real o, Real s, Real ot, Real st, Real h,
	Real pn, Real co, Real fric, Real ft, Real fs,
	int* nfail, int mfail,
	int* ijesf, int* ijebk, Real* djefs,
	Real* sig, Real* tao, Real* damge,
	Real* ol, Real* sl)
{
	Real sabs, D, sigma, tau;
	sabs = fabs(s);

	if ((o > 0) || (sabs > 0))
	{
		if (sabs <= 0)
		{
			D = o / ot;
		}
		else if (o <= 0)
		{
			D = sabs / st;
		}
		else
		{
			D = sqrt((o / ot) * (o / ot) + (sabs / st) * (sabs / st));
		}
	}
	else
	{
		D = R0;
	}

	if (D >= R1)
	{
		*nfail = *nfail + 1;
		if ((*nfail > mfail) && (*ijebk <= 0))
		{
			if (o >= ot)
			{
				*ijebk = JEBKT1;
			}
			else if (sabs >= st)
			{
				*ijebk = JEBKT2;
			}
			else
			{
				*ijebk = JEBKT3;
			}
		}
		D = R1;
	}
	*damge = D;

	Real fD;
	fD = (R1 - ((a_const + b_const - R1) / (a_const + b_const)) *
		exp(D * (a_const + c_const * b_const) / ((a_const + b_const) * (R1 - a_const - b_const))))
		* (a_const * (R1 - D) + b_const * pow((R1 - D), c_const));
	if (o < R0)           /* normal stress */
	{
		sigma = pn * o / h; //pn * o / (R2 * h);
	}
	else
	{
		sigma = ft * fD;
	}

	/* take into account Mohr-Coulomb   */
	if (co > R0)
	{
		if (sigma > R0)
		{
			fs = co;
		}
		else
		{
			fs = co - sigma * fric; //采用莫尔库伦计算抗剪强度 2013-4-16
		}
		*djefs = fs;    /* update fs to Mohr-Coulomb  除了第一个时间步外 后面用到的抗剪强度均是通过摩尔库伦计算得到的 这样考虑非常合理 2013-4-16  */
	}

	if (sigma > R0)
	{
		tau = co * fD;
	}
	else
	{
		tau = co * fD - sigma * fric;
	}

	*sig = sigma;
	*tao = tau;
}