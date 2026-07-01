#include "Real.h"  
#include "Plug.h"
#include <math.h>
#include <stdio.h>
void Plug(int itype, Real x, Real y, Real z, Real pc, int* iflag, Real* ft, Real* co, Real* fr)
{
	//itype就是.inp文件中*plug关键词后的数字
	//*iflag=1表示暂堵  *iflag=0表示不暂堵
	//if (itype == 1)
	//{
	//	if (y > 60 && y< 62)
	//	{
	//		*iflag = 1;
	//	}
	//}

	//if (itype == 1)
	//{
	//	if (x > -0.01 && x < 0.01)
	//	{
	//		if (y > 0.21 && y < 0.3)
	//		{
	//			*iflag = 1;
	//		}
	//	}
	//}

	//if (itype == 2)
	//{
	//	if (x > -0.01 && x < 0.01)
	//	{
	//		if (y > 0.21 && y < 0.3)
	//		{
	//			*iflag = 0;
	//		}
	//	}
	//}

	//if (itype == 1)  //zandu-3.3
	//{
	//	if (x > -0.05 && x < 0.05)
	//	{
	//		if (y > 1.0 - 1e-4 && y < 1.0 + 1e-4)
	//		{
	//			*iflag = 1;
	//		}

	//		if (y > -1.0 - 1e-4 && y < -1.0 + 1e-4)
	//		{
	//			*iflag = 1;
	//		}
	//	}
	//}

}