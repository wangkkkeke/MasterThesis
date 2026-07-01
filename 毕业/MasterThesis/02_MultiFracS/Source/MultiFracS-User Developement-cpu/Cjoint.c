#include "Real.h"  
#include "Cjoint.h"
#include <math.h>
#include <stdio.h>

#define JEISOFT1 1
#define JEISOFT2 2
#define JEISOFT3 3
#define JEBKT1 11
#define JEBKT2 12
#define JEBKT3 13
#define ABS(x) (((x)<0)?-(x):(x))
#define MAX(x,y) (((x)<(y))?(y):(x))
#define MIN(x,y) (((x)>(y))?(y):(x))

void op_ot_sp_st(Real ft, Real fs, Real co,
	Real pn, Real ps,
	Real gi, Real gii, Real h,
	Real* op, Real* ot, Real* sp, Real* st)
{
	*op = R2 * h * ft / pn;
	*sp = R2 * h * co / ps;

	*ot = R3 * gi / ft;
	*st = R3 * gii / co;
}

//------断裂节理单元受压时
void Cjoint_broken(
	int ijebk,  //jflag==10表示初始裂缝 >10表示生成的裂缝
	Real o, Real s,
	Real op, Real sp,
	Real ot, Real st,
	Real h,
	Real ft, Real fric,
	Real pn, Real ps,
	Real* sig, Real* tao
)
{
	Real sigma = pn * o / h;
	*sig = sigma;
	*tao = -sigma * fric;
}

static void Cjoint1(Real o, Real s, Real op, Real sp, Real ot, Real st,
	Real co, Real fric, Real ft, Real fs,
	int* nfail, int mfail,
	int* ijesf, int* ijebk,
	Real* sig, Real* tao, Real* damge
)
{
	Real sabs, D, sigma, tau;
	sabs = fabs(s);

	if (o <= op && sabs <= sp)
	{
		D = R0;
	}
	else if (o > op && sabs <= sp)
	{
		D = (o - op) / ot;
		*ijesf = JEISOFT1;
	}
	else if (sabs > sp && o <= op)
	{
		D = (sabs - sp) / st;
		*ijesf = JEISOFT2;
	}
	else
	{
		D = sqrt(((o - op) / ot) * ((o - op) / ot) + ((sabs - sp) / st) * ((sabs - sp) / st));
		*ijesf = JEISOFT3;
	}

	if (D >= R1)
	{
		*nfail = *nfail + 1;
		if ((*nfail > mfail) /*&& (*ijebk <= 0)*/)
		{
			if (o >= (op + ot))
			{
				*ijebk = JEBKT1;
			}
			else if (sabs >= (sp + st))
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
	if (o < R0)           //法向应力
	{
		sigma = R2 * o * ft / op;
	}
	else if (o <= op)
	{
		sigma = (R2 * o / op - (o / op) * (o / op)) * fD * ft;
	}
	else
	{
		sigma = ft * fD;
	}

	if (sabs > sp)  //剪应力
	{
		if (sigma > R0)
		{
			tau = co * fD;
		}
		else
		{
			tau = co * fD - sigma * fric;
		}
	}
	else
	{
		//tau = (R2 * (sabs / sp) - (sabs / sp) * (sabs / sp)) * fD * fs;
		if (sigma > R0)
		{
			tau = (R2 * (sabs / sp) - (sabs / sp) * (sabs / sp)) * co * fD;
		}
		else
		{
			tau = (R2 * (sabs / sp) - (sabs / sp) * (sabs / sp)) * (co * fD - sigma * fric);
		}
	}

	*sig = sigma;
	*tao = tau;
}

static void Cjoint2(Real o, Real s, Real op, Real sp, Real ot, Real st,
	Real co, Real fric, Real ft, Real fs,
	int* nfail, int mfail,
	int* ijesf, int* ijebk,
	Real* sig, Real* tao, Real* damge
)
{
	Real sabs, D, sigma, tau;
	sabs = fabs(s);

	D = R0;
	if ((o > op) || (sabs > sp))
	{
		if (sabs <= sp)
		{
			D = (o - op) / ot;
			*ijesf = JEISOFT1;
		}
		else if (o <= op)
		{
			D = (sabs - sp) / st;
			*ijesf = JEISOFT2;
		}
		else
		{
			D = sqrt(((o - op) / ot) * ((o - op) / ot) + ((sabs - sp) / st) * ((sabs - sp) / st));
			*ijesf = JEISOFT3;
		}
	}

	if (D >= R1)
	{
		*nfail = *nfail + 1;
		if ((*nfail > mfail) && (*ijebk <= 0))
		{
			if (o >= (op + ot))
			{
				*ijebk = JEBKT1;
			}
			else if (sabs >= (sp + st))
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
	fD = 1 - D;
	if (o < R0)
	{
		sigma = R2 * o * ft / op;
	}
	else if (o <= op)
	{
		sigma = (R2 * o / op - (o / op) * (o / op)) * fD * ft;
	}
	else
	{
		sigma = ft * fD;
	}

	if (sigma > R0)
	{
		fs = co;
	}
	else
	{
		fs = co - sigma * fric; //采用莫尔库伦计算抗剪强度 2013-4-16
	}

	if (sabs > sp)
	{
		if (sigma > R0)
		{
			tau = co * fD;
		}
		else
		{
			tau = co * fD - sigma * fric;
		}
	}
	else //if (sabs <= sp)
	{
		tau = (R2 * (sabs / sp) - (sabs / sp) * (sabs / sp)) * fD * fs;
	}

	*sig = sigma;
	*tao = tau;
}

static void Cjoint3(Real o, Real s, Real op, Real sp, Real ot, Real st,
	Real co, Real fric, Real ft, Real fs,
	int* nfail, int mfail,
	int* ijesf, int* ijebk,
	Real* sig, Real* tao, Real* damge
)
{
	Real sabs, D, sigma, tau;
	sabs = fabs(s);

	D = R0;
	if ((o > op) || (sabs > sp))
	{
		if (sabs <= sp)
		{
			D = (o - op) / ot;
			*ijesf = JEISOFT1;
		}
		else if (o <= op)
		{
			D = (sabs - sp) / st;
			*ijesf = JEISOFT2;
		}
		else
		{
			D = sqrt(((o - op) / ot) * ((o - op) / ot) + ((sabs - sp) / st) * ((sabs - sp) / st));
			*ijesf = JEISOFT3;
		}
	}

	if (D >= R1)
	{
		*nfail = *nfail + 1;
		if ((*nfail > mfail) && (*ijebk <= 0))
		{
			if (o >= (op + ot))
			{
				*ijebk = JEBKT1;
			}
			else if (sabs >= (sp + st))
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
	fD = 1 - D;
	if (o < R0)
	{
		sigma = R2 * o * ft / op;
	}
	else if (o <= op)
	{
		sigma = (o / op) * fD * ft;
	}
	else
	{
		sigma = ft * fD;
	}

	if (sigma > R0)
	{
		fs = co;
	}
	else
	{
		fs = co - sigma * fric; //采用莫尔库伦计算抗剪强度 2013-4-16
	}

	if (sabs > sp)
	{
		if (sigma > R0)
		{
			tau = co * fD;
		}
		else
		{
			tau = co * fD - sigma * fric;
		}
	}
	else //if (sabs <= sp)
	{
		tau = (sabs / sp) * fD * fs;
	}

	*sig = sigma;
	*tao = tau;
}

static void Cjoint4(Real o, Real s, Real op, Real sp, Real ot, Real st,
	Real co, Real fric, Real ft, Real fs,
	int* nfail, int mfail,
	int* ijesf, int* ijebk,
	Real* sig, Real* tao, Real* damge
)
{
	Real sabs, D, sigma, tau;
	sabs = fabs(s);

	if (o <= op && sabs <= sp)
	{
		D = R0;
	}
	else if (o > op && sabs <= sp)
	{
		D = (o - op) / ot;
		*ijesf = JEISOFT1;
	}
	else if (sabs > sp && o <= op)
	{
		D = (sabs - sp) / st;
		*ijesf = JEISOFT2;
	}
	else
	{
		D = sqrt(((o - op) / ot) * ((o - op) / ot) + ((sabs - sp) / st) * ((sabs - sp) / st));
		*ijesf = JEISOFT3;
	}

	if (D >= R1)
	{
		*nfail = *nfail + 1;
		if ((*nfail > mfail) && (*ijebk <= 0))
		{
			if (o >= (op + ot))
			{
				*ijebk = JEBKT1;
			}
			else if (sabs >= (sp + st))
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
	fD = 1 - D;
	if (o < R0)           //法向应力
	{
		sigma = R2 * o * ft / op;
	}
	else if (o <= op)
	{
		sigma = (o / op) * fD * ft;
	}
	else
	{
		sigma = ft * fD;
	}

	if (sabs > sp)  //剪应力
	{
		tau = fs * fD;
	}
	else
	{
		tau = (sabs / sp) * fD * fs;
	}

	*sig = sigma;
	*tao = tau;
}

//static void Cjoint5(Real o, Real s, Real op, Real sp, Real ot, Real st,
//	Real co, Real fric, Real ft, Real fs,
//	int* nfail, int mfail,
//	int* ijesf, int* ijebk,
//	Real* sig, Real* tao, Real* damge,
//	Real* omax, Real* smax
//)
//{
//	Real sabs, D, sigma, tau;
//	sabs = fabs(s);
//
//	D = R0;
//	if ((o > op) || (sabs > sp))
//	{
//		if (sabs <= sp)
//		{
//			D = (o - op) / ot;
//			*ijesf = JEISOFT1;
//		}
//		else if (o <= op)
//		{
//			D = (sabs - sp) / st;
//			*ijesf = JEISOFT2;
//		}
//		else
//		{
//			D = sqrt(((o - op) / ot) * ((o - op) / ot) + ((sabs - sp) / st) * ((sabs - sp) / st));
//			*ijesf = JEISOFT3;
//		}
//	}
//
//	if (D >= R1)
//	{
//		*nfail = *nfail + 1;
//		if ((*nfail > mfail) && (*ijebk <= 0))
//		{
//			if (o >= (op + ot))
//			{
//				*ijebk = JEBKT1;
//			}
//			else if (sabs >= (sp + st))
//			{
//				*ijebk = JEBKT2;
//			}
//			else
//			{
//				*ijebk = JEBKT3;
//			}
//		}
//		D = R1;
//	}
//	*damge = MAX(D, *damge);
//	D = *damge;
//
//	Real fD;
//	fD = 1 - D;
//	if (o < R0)
//	{
//		sigma = R2 * o * ft / op;
//	}
//	else if (o <= op)
//	{
//		sigma = (o / op) * fD * ft;
//	}
//	else
//	{
//		sigma = ft * fD;
//	}
//
//	if (sabs > sp)
//	{
//		if (sigma > R0)
//		{
//			tau = co * fD;
//		}
//		else
//		{
//			tau = co * fD - sigma * fric;
//		}
//	}
//	else //if (sabs <= sp)
//	{
//		tau = (sabs / sp) * fD * fs;
//	}
//
//	if (o > 0 && o<(*omax) && (*omax)>op)
//	{
//		sigma = fD * ft * o / (*omax);
//	}
//
//	if (sabs<(*smax) && (*smax)>sp)
//	{
//		tau = (fD * co - sigma * fric) * sabs / (*smax);
//	}
//
//	*sig = sigma;
//	*tao = tau;
//}

//------未断裂节理单元
void  Cjoint(Real o, Real s, Real op, Real sp, Real ot, Real st,
	Real co, Real fric, Real ft, Real fs,
	int* nfail, int mfail,
	int* ijesf, int* ijebk,
	Real* sig, Real* tao, Real* damge, int icjointdll,
	Real* omax, Real* smax, Real* aperture)
{
	switch (icjointdll)
	{
	case 1: Cjoint1(o, s, op, sp, ot, st,
		co, fric, ft, fs, nfail, mfail,
		ijesf, ijebk,
		sig, tao, damge); //fD=复杂,曲线
		break;
	case 2: Cjoint2(o, s, op, sp, ot, st,
		co, fric, ft, fs, nfail, mfail,
		ijesf, ijebk,
		sig, tao, damge); //fD=1-D,曲线
		break;
	case 3: Cjoint3(o, s, op, sp, ot, st,
		co, fric, ft, fs, nfail, mfail,
		ijesf, ijebk,
		sig, tao, damge); //fD=1-D,直线
		break;
	case 4: Cjoint4(o, s, op, sp, ot, st,
		co, fric, ft, fs, nfail, mfail,
		ijesf, ijebk,
		sig, tao, damge); //固定剪应力
		break;
	//case 5: Cjoint5(o, s, op, sp, ot, st,
	//	co, fric, ft, fs, nfail, mfail,
	//	ijesf, ijebk,
	//	sig, tao, damge,
	//	omax, smax
	//); //考虑损伤不可逆
		break;
	}
}
