#include "Real.h"  
#include "Cjoint2D.h"
#include <math.h>
#include <stdio.h>

#define JEISOFT1 1
#define JEISOFT2 2
#define JEISOFT3 3
#define JEBKT1 11
#define JEBKT2 12
#define JEBKT3 13

#define a_const 0.63
#define b_const 1.8
#define c_const 6.0

USERDLL void joint_model_intact_2d_user(
	Real o1, Real o2,
	Real s1, Real s2,
	Real h, Real e1x, Real e1y,
	Real pn, Real ps,
	Real co, Real fric, Real ft, Real gi, Real gii, Real o0,
	int imat, int* ijesf, int* ijebk, Real* djedamge,
	Real damge[3], Real djefs[3], Real ol[3], Real sl[3], Real omax[3], Real smax[3],
	Real p1, Real p2,
	Real fx[2], Real fy[2]
)
{
	//o1-节理单元A端的法向位移量  张开为正 压缩为负
	//o2-节理单元B端的法向位移量
	//s1-节理单元A端的切向滑移量
	//s2-节理单元B端的切向滑移量
	//h-节理单元的长度，e1x,e1y为节理单元切向方向的单位方向向量，该向量的大小为1
	//对应的节理单元的法向单位向量为-e1y,e1x
	//pn-节理单元法向罚参数,ps-节理单元的切向罚参数
	//co-节理单元的粘聚力，fric-节理单元的内摩擦系数，ft-节理单元的抗拉强度
	//gi-节理单元的I型断裂能 gii-节理单元的II型断裂能
	//o0-节理单元的虚拟初始张开量，节理单元需要克服该值才会有压应力，在FGM.c中可以设置该值，如未设置，则默认值为0
	//imat-节理单元的材料编号 按照*Mat和*Joint关键词，从0开始编号
	//*ijesf-节理单元的软化标志  *ijebk-节理单元断裂标志 *djedagme-节理单元的平均损伤值
	//damge[3]-节理单元积分点(最多允许3个积分点)的损伤值(0-1), djefs[3]-节理单元积分点的抗剪强度，
	//ol[3]-节理单元积分点上一步的法向张开量，sl[3]-节理单元积分点上一步的切向位移，
	//omax[3]-节理单元积分点的历史最大法向张开量，smax[3]-节理单元积分点的历史最大切向位移，
	//fx[2],fy[2]是节理单元变形引起的节点力
	double op, sp, ot, st;
	op = 2.0 * h * ft / pn;
	sp = 2.0 * h * co / ps;
	ot = 3.0 * gi / ft;
	st = 3.0 * gii / co;

	int nfail = 0;
	Real o, s;
	Real sumdamge = 0;
	for (int ip = 0; ip < 3; ip++)
	{
		if (ip == 0)
		{
			o = o1; s = s1;
		}
		else if (ip == 2)
		{
			o = o2; s = s2;
		}
		else
		{
			o = 0.5 * (o1 + o2); s = 0.5 * (s1 + s2);
		}

		Real sabs, D, sigma, tau;
		sabs = fabs(s);

		if (o <= op && sabs <= sp)
		{
			D = 0.0;
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

		if (D >= 1.0)
		{
			nfail = nfail + 1;
			if (nfail > 1)
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
			D = 1.0;
		}
		sumdamge += D;

		Real fD;
		fD = (1.0 - ((a_const + b_const - 1.0) / (a_const + b_const)) *
			exp(D * (a_const + c_const * b_const) / ((a_const + b_const) * (1.0 - a_const - b_const))))
			* (a_const * (1.0 - D) + b_const * pow((1.0 - D), c_const));
		if (o < 0.0)           //法向应力
		{
			sigma = 2.0 * o * ft / op;
		}
		else if (o <= op)
		{
			sigma = (2.0 * o / op - (o / op) * (o / op)) * fD * ft;
		}
		else
		{
			sigma = ft * fD;
		}

		if (sabs > sp)  //剪应力
		{
			if (o > 0.0)
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
			if (o > 0.0)
			{
				tau = (2.0 * (sabs / sp) - (sabs / sp) * (sabs / sp)) * co * fD;
			}
			else
			{
				tau = (2.0 * (sabs / sp) - (sabs / sp) * (sabs / sp)) * (co * fD - sigma * fric);
			}
		}

		if (s < 0.0) tau = -tau;

		Real tau_e1x = tau * e1x;
		Real tau_e1y = tau * e1y;
		Real sigma_e1x = sigma * e1x;
		Real sigma_e1y = sigma * e1y;
		Real area;
		if (ip == 0)
		{
			area = h / 6.0;
			fx[0] += -area * (tau_e1x - sigma_e1y);
			fy[0] += -area * (tau_e1y + sigma_e1x);
		}
		else if (ip == 1)
		{
			area = h / 3.0;
			fx[0] += -area * (tau_e1x - sigma_e1y);
			fy[0] += -area * (tau_e1y + sigma_e1x);
			fx[1] += -area * (tau_e1x - sigma_e1y);
			fy[1] += -area * (tau_e1y + sigma_e1x);
		}
		else
		{
			area = h / 6.0;
			fx[1] += -area * (tau_e1x - sigma_e1y);
			fy[1] += -area * (tau_e1y + sigma_e1x);
		}
	}

	*djedamge = sumdamge/3.0;
}

USERDLL void joint_model_broken_2D_user(
	Real o1, Real o2,
	Real s1, Real s2,
	Real vs1, Real vs2, Real dtm,
	Real h, Real e1x, Real e1y,
	Real pn, Real ps,
	Real co, Real fric, Real ft, Real gi, Real gii, Real o0,
	int imat, int* ijesf, int* ijebk, Real* djedamge,
	Real damge[3], Real djefs[3], Real ol[3], Real sl[3],
	Real sign[3], Real ShearAmount[3], Real dsl[3],
	Real p1, Real p2,
	Real fx[2], Real fy[2]
)
{
	//sign[3]-节理单元积分点的累计剪切位移的方向
	//ShearAmount[3]-节理单元积分点累计剪切位移的绝对值
	//dsl[3]-节理单元积分点上一个时间步的位移增量
	//vs1-节理单元A端的切向相对速度，vs2-节理单元B端的切向相对速度
	double op, sp, ot, st;
	op = 2.0 * h * ft / pn;
	sp = 2.0 * h * co / ps;
	ot = 3.0 * gi / ft;
	st = 3.0 * gii / co;

	int nfail = 0;
	Real o, s;
	for (int ip = 0; ip < 3; ip++)
	{
		if (ip == 0)
		{
			o = o1; s = s1;
		}
		else if (ip == 2)
		{
			o = o2; s = s2;
		}
		else
		{
			o = 0.5 * (o1 + o2); s = 0.5 * (s1 + s2);
		}

		if (o >= 0) continue;  //拉伸

		Real sigma, tau;

		sigma = pn * o / h;
		tau = -sigma * fric;

		if (s < 0.0) tau = -tau;

		Real tau_e1x = tau * e1x;
		Real tau_e1y = tau * e1y;
		Real sigma_e1x = sigma * e1x;
		Real sigma_e1y = sigma * e1y;
		Real area;
		if (ip == 0)
		{
			area = h / 6.0;
			fx[0] += -area * (tau_e1x - sigma_e1y);
			fy[0] += -area * (tau_e1y + sigma_e1x);
		}
		else if (ip == 1)
		{
			area = h / 3.0;
			fx[0] += -area * (tau_e1x - sigma_e1y);
			fy[0] += -area * (tau_e1y + sigma_e1x);
			fx[1] += -area * (tau_e1x - sigma_e1y);
			fy[1] += -area * (tau_e1y + sigma_e1x);
		}
		else
		{
			area = h / 6.0;
			fx[1] += -area * (tau_e1x - sigma_e1y);
			fy[1] += -area * (tau_e1y + sigma_e1x);
		}
	}

	*djedamge = 1.0;
}