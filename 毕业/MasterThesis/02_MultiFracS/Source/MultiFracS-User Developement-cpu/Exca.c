#include "Real.h"  
#include "Exca.h"
#include <math.h>
#include <stdio.h>

void Mech_Exca_v(int iemat, Real x, Real y, Real z, int nstepbeginexca, int nstep, Real dtm, int* iflag)
{
	//imat从0开始，按照*Material关键词在inp文件中出现的顺序, 实体单元的材料编号
	//x,y,z实体单元的坐标, nstep当前步数， dtm时间步长
	//设置*iflag=1表示开挖该单元，*iflag=0表示不开挖
	//该二次开发接口需要和命令*vexcavate一块使用，
	//只有在*Begin和*End之间使用了*vexcavate之后，本接口才会被调用
	
	//本接口可以灵活使用，有多种功能，可以控制MultiFracS在计算过程中按照用户
	//的特定要求，删除指定的单元，实现超出范围自动删除，连续开挖等功能

	//举例1 将超出右侧界线xmax的单元自动删除
	//Real xmax = 1.0;
	//if (x >= xmax)
	//{
	//	*iflag = 1;
	//}

	//举例2 将落入指定圆形区域的单元自动删除
	//Real xc, yc, r;
	//xc = 0; yc = 0; r = 0.5;
	//Real dist2 = (x - xc) * (x - xc) + (y - yc) * (y - yc);
	//if (dist2 < r * r)
	//{
	//	*iflag = 1;
	//}

	////举例3 连续开挖 将掌子面初始位置和当前位置之间的单元删除，实现连续开挖
	//Real xmin, xmax, ymin, ymax; //待开挖区域的范围
	//xmin = 200; xmax = 1450;
	//ymin = 100; ymax = 150;

	//Real x0, xc;//掌子面的初始位置和当前位置
	//x0 = xmin; //从左侧开始开挖

	//Real len;
	//len = 0.006;
	//xc = x0 + (nstep - nstepbeginexca) * len;//每步前进len米

	//if ((x >= xmin && x <= xmax)
	//	&& (y >= ymin && y <= ymax))  //限定待开挖的范围
	//{
	//	if (x < xc)
	//	{
	//		*iflag = 1;
	//	}
	//}

	//	//举例3 连续开挖 将掌子面初始位置和当前位置之间的单元删除，实现连续开挖
	//Real xmin, xmax, ymin, ymax; //待开挖区域的范围
	//xmin = 5; xmax = 145;
	//ymin = 5; ymax = 13;

	//Real x0, xc;//掌子面的初始位置和当前位置
	//x0 = xmin; //从左侧开始开挖

	//Real len;
	//len = 0.00003;
	//xc = x0 + (nstep - nstepbeginexca) * len;//每步前进len米

	//if ((x >= xmin && x <= xmax)
	//	&& (y >= ymin && y < ymax))  //限定待开挖的范围
	//{
	//	if (x < xc)
	//	{
	//		*iflag = 1;
	//	}
	//}

	//举例3 连续开挖 将掌子面初始位置和当前位置之间的单元删除，实现连续开挖
	Real xmin, xmax, ymin, ymax; //待开挖区域的范围
	xmin = 150; xmax = 1450;
	ymin = 100; ymax = 150;

	Real x0, xc;//掌子面的初始位置和当前位置
	x0 = xmin; //从左侧开始开挖

	Real len;
	len = 0.1;
	xc = x0 + (nstep - nstepbeginexca) * len;//每步前进len米

	if ((x > xmin && x <= xmax)
		&& (y >= ymin && y < ymax))  //限定待开挖的范围
	{
		if (x < xc)
		{
			*iflag = 1;
		}
	}
}
