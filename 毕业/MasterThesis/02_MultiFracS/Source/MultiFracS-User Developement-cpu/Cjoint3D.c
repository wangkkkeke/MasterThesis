#include "Real.h"  
#include "Cjoint3D.h"
#include <math.h>
#include <stdio.h>

#define JEISOFT1 1
#define JEISOFT2 2
#define JEISOFT3 3
#define JEBKT1 11
#define JEBKT2 12
#define JEBKT3 13

#define V3DDot(s,x1,y1,z1,x2,y2,z2) {(s)=((x1)*(x2))+((y1)*(y2))+((z1)*(z2));}
#define V3DNor(s,x1,y1,z1) \
              {(s)=sqrt((x1)*(x1)+(y1)*(y1)+(z1)*(z1));   \
              if((s)>SmallPositiveNumber)(x1)=(x1)/(s);  \
              if((s)>SmallPositiveNumber)(y1)=(y1)/(s);  \
              if((s)>SmallPositiveNumber)(z1)=(z1)/(s);  }

void Cjoint3D_intact(
	Real rs[][3], Real vnor[3], Real area,
	Real h, 
	Real pn, Real ps,
	Real co, Real fric, Real ft, Real gi, Real gii,
	int imat, int* ijesf, int* ijebk, Real* damge, Real* d1jefs,
	Real p1, Real p2, Real p3,
	Real fnt[][3]
)
{
	double op, sp, ot, st;
	op = 2.0 * h * ft / pn;
	sp = 2.0 * h * co / ps;
	ot = 3.0 * gi / ft;
	st = 3.0 * gii / co;

	int nfail = 0;
	for (int ip = 0; ip < 3; ip++)
	{
		Real o;
		V3DDot(o, rs[ip][0], rs[ip][1], rs[ip][2], vnor[0], vnor[1], vnor[2]);

		Real se[3];
		for (int j = 0; j < 3; j++)
		{
			se[j] = rs[ip][j] - o * vnor[j];
		}
		Real sabs;
		V3DNor(sabs, se[0], se[1], se[2]);

		Real sigma = 0; Real tau = 0; 
		Real D;

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
			nfail = nfail + 1;
			if (nfail > 2)
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
		*damge += D;

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
			if (o > R0)
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
			if (o > R0)
			{
				tau = (R2 * (sabs / sp) - (sabs / sp) * (sabs / sp)) * co * fD;
			}
			else
			{
				tau = (R2 * (sabs / sp) - (sabs / sp) * (sabs / sp)) * (co * fD - sigma * fric);
			}
		}

		for (int j = 0; j < 3; j++)
		{
			Real trac = sigma * vnor[j] + tau * se[j];
			fnt[ip][j] = trac * area / R3;
		}
	}

	*damge /= 3.0;
}

void Cjoint3D_broken(
	Real rs[][3], Real vnor[3], Real area,
	Real h,
	Real pn, Real ps,
	Real co, Real fric, Real ft, Real gi, Real gii,
	int imat, int* ijesf, int* ijebk, Real* damge, 
	Real p1, Real p2, Real p3,
	Real fnt[][3]
)
{
	double op, sp, ot, st;
	op = 2.0 * h * ft / pn;
	sp = 2.0 * h * co / ps;
	ot = 3.0 * gi / ft;
	st = 3.0 * gii / co;

	int nfail = 0;
	for (int ip = 0; ip < 3; ip++)
	{
		Real o;
		V3DDot(o, rs[ip][0], rs[ip][1], rs[ip][2], vnor[0], vnor[1], vnor[2]);

		if (o >= 0) continue;  //拉伸

		Real se[3];
		for (int j = 0; j < 3; j++)
		{
			se[j] = rs[ip][j] - o * vnor[j];
		}
		Real sabs;
		V3DNor(sabs, se[0], se[1], se[2]);

		Real sigma = 0; Real tau = 0; 

		sigma = pn * o / h;
		tau = -sigma * fric;

		for (int j = 0; j < 3; j++)
		{
			Real trac = sigma * vnor[j] + tau * se[j];
			fnt[ip][j] = trac * area / R3;
		}
	}

	*damge = 1.0;
}