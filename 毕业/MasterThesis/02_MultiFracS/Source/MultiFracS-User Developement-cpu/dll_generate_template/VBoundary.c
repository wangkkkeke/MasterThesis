#define _CRT_SECURE_NO_WARNINGS
#include "Real.h"
#include "VBoundary.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//设置宏FileName，表示地震数据的文件名，用户可改成自己的地震数据文件名
//该文件和MultiFracS在同一个文件夹下
//数据文件格式为n行*2列，一行的两个数据空格分隔，整个文件不要有空行
/*
x0 y0
x1 y1
.  .
.  .
.  .
xn yn
*/
#define FileName "data.txt"

//定义全局变量，本.c文件的函数均可直接使用
Real* time;
Real* yt;
int num=0; //真实数据的行数

static void Read_x_y_data_from_file(char* filename, int* nrow, Real** x, Real** y)
{
	FILE* file = fopen(filename, "r");
	if (file == NULL)
	{
		//printf("无法打开文件,来自Read_x_y_data_from_file\n");
		return;
	}
	else
	{
		printf("Read_x_y_data_from_file 读入数据文件 %s 成功!!!\n", filename);
	}

	char line[256];
	char xstr[30], ystr[30];
	int i = 0;
	while (fgets(line, sizeof(line), file))
	{
		i++;
	}
	*nrow = i;

	Real* xp = malloc(i * sizeof(Real));
	Real* yp = malloc(i * sizeof(Real));
	//fclose(file);

	//file = fopen(filename, "r");
	rewind(file);//将文件指针从新指向文件的开头
	i = 0;
	while (fgets(line, sizeof(line), file))
	{
		sscanf(line, "%s %s", xstr, ystr);
		xp[i] = atof(xstr);
		yp[i] = atof(ystr);
		i++;
	}
	fclose(file);

	*x = xp;
	*y = yp;
}

//该函数的作用为通过线性插值确定yc的值
static Real linear_interpolation(Real* x, Real* y, int nrow, Real xc)
{
	int i0 = 0, i1 = 0;
	int i = 0;
	for (i = 0; i < nrow - 1; i++)
	{
		//printf("x=%e, y=%e\n", x[i], y[i]);

		if (xc < x[0])
		{
			i0 = 0;
			i1 = 0;
			break;
		}

		if (xc > x[nrow - 1])
		{
			i0 = nrow - 1;
			i1 = nrow - 1;
			break;
		}

		if (xc >= x[i] && xc < x[i + 1])
		{
			i0 = i;
			i1 = i + 1;
			break;
		}
	}

	Real yc;
	if (x[i1] - x[i0] != 0)
	{
		yc = y[i0] + (xc - x[i0]) * (y[i1] - y[i0]) / (x[i1] - x[i0]);
	}
	else
	{
		yc = y[i0];
	}

	return yc;
}


void Read_seismic_data()
{
	//Read_x_y_data_from_file(FileName, &num, &time, &yt);
	//for (int i = 0; i < num; i++)
	//{
	//	printf("%d %f %f\n", i, time[i], yt[i]);
	//}
}


void User_node_velocity_boundary(
	int itype, int nstep, Real dtm,
	Real fx, Real fy, Real fz,
	Real* x, Real* y, Real* z,
	Real* vx, Real* vy, Real* vz,
	int* ifix, int* ifiy, int* ifiz)
{
	//itype就是.inp文件中第*FixBoundary中第一个数据的值，可取1-4之外的整数值，
	//当存在多个自定义边界时，可用该数值加以区分
	//fx,fy,fz为该边界集合受到的总的力在x,y,z三个方向的分量
	//如果完全固定x方向则将设置*fix=1; 否则不设置，如果只是施加一个增量也不设置该值
	//Real pi = 3.1415926535;
	//Real f = 3;
	//Real amax = 1.0;
	//Real velx = 0.05;
	//if (itype == 1024)
	//{
	//	*ifix = 1;
	//	*vx = *vx + amax * sin(2 * pi * f);
	//	*x = *x + (*vx) * nstep * dtm;
	//	*ifiy = 1;
	//	*vy = 0;
	//	*y = *y + (*vy) * nstep * dtm;
	//}

	//Real pi = 3.1415926535;
	//Real t = nstep * dtm;
	//Real a = 9.8;
	//Real sta_time = 200000 * dtm;
	//Real env_time = 30200000 * dtm;

	//Real t_1 = (nstep - 200000) * dtm;
	//Real wave;

	//if (t < sta_time || t > env_time)
	//{
	//	wave = 0.0;
	//}
	//else
	//{
	//	wave = -0.3 * a * cos(2 * pi * 15 * t_1) / (2 * pi * 15);
	//}
	//if (itype == 1024)
	//{
	//	*ifix = 1;
	//	*vx = wave;
	//	*x = *x + (*vx) * dtm;
	//	*ifiy = 1;
	//	*vy = 0;
	//	*y = *y + (*vy) * dtm;
	//}

	////示例代码，如何根据当前时间确定当前的振动速度
	//Real tc = nstep * dtm;
	//Real yc;
	//yc = linear_interpolation(time, yt, num, tc);
	//printf("time=%e yc=%e\n", tc, yc);


}

void User_node_velocity_boundary_GPU(
	const int itype, const Real value,
	const Real* x, const Real* y, const Real* z,
	Real* vx, Real* vy, Real* vz,
	int* ifix, int* ifiy, int* ifiz)
{
	//仅对GPU并行计算有效，计算类型为11及以上，目前只能设置速度不随时间变化的边界
	//value就是.inp文件中第*FixBoundary中第2个数据的值
	//if (itype == 10)
	//{
	//	double v = value;
	//	double r = sqrt((*x) * (*x) + (*y) * (*y) + (*z) * (*z));

	//	//printf("r=%f\n", r);
	//	*ifix = 1;
	//	*vx = ((*x) / r) * v;
	//	*ifiy = 1;
	//	*vy = ((*y) / r) * v;
	//	*ifiz = 1;
	//	*vz = ((*z)) / r * v;
	//	//printf("%f,%f,%f\n", *vx, *vy, *vz);
	//}
}