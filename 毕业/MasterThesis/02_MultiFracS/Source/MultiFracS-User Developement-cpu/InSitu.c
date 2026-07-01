#include "Real.h"  
#include "InSitu.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//设置宏FileName，表示初始条件的文件名，用户可改成自己的初始条件数据文件名
//该文件和MultiFracS在同一个文件夹下
//数据文件格式为n行m列，一行的数据逗号分隔，整个文件不要有空行，文件的首行为数据项说，读入时会自动跳过
//用户可以自行修改Read_x_y_data_from_file的代码，来读如不同数据格式的文件
/*
编号,x坐标,y坐标,孔压值
id0,x0,y0,p0
id1,x1,y1,p1
.  .
.  .
.  .
idn,xn,yn,pn
*/

/*
编号,x坐标,y坐标,sxx,syy,sxy,
id0,x0,y0,sxx,syy,sxy
id1,x1,y1,sxx1,syy1,sxy1
.  .
.  .
.  .
idn,xn,yn,sxxn,syyn,sxyn
*/

#define FileName1 "15-jizhi-insitu-stress-pore-pressure-2000.csv"  //地应力数据文件
#define FileName2 "15-jizhi-insitu-stress-pore-pressure-2000.csv"  //孔隙压力数据文件

//定义全局变量，本.c文件的函数均可直接使用
int* idg = NULL;
Real* xg = NULL;
Real* yg = NULL;
Real* zg = NULL;
Real* sgxx = NULL;
Real* sgyy = NULL;
Real* sgzz = NULL;
Real* sgxy = NULL;
Real* sgyz = NULL;
Real* sgzx = NULL;
int numrow1 = 0; //地应力数据的行数


int* idp = NULL;
Real* xp = NULL;
Real* yp = NULL;
Real* zp = NULL;
Real* pp = NULL;
int numrow2 = 0; //孔隙压力数据的行数

static void Read_insitu_stress_data_from_file(char* filename, int* nrow, int** id, Real** x, Real** y, Real** sxx, Real** syy, Real** sxy)
{
	int i = 0;
	FILE* file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("无法打开文件,来自Read_insitu_stress_data_from_file\n");
		return;
	}
	else
	{
		printf("Read_insitu_stress_data_from_file 读入数据文件 %s 成功!!!\n", filename);
	}

	char line[256];
	char idstr[30], xstr[30], ystr[30], zstr[30], sxxstr[30], syystr[30], sxystr[30];

	fgets(line, sizeof(line), file);
	while (fgets(line, sizeof(line), file))
	{
		i++;
	}
	*nrow = i;

	int* idp = malloc(i * sizeof(int));
	Real* xp = malloc(i * sizeof(Real));
	Real* yp = malloc(i * sizeof(Real));
	Real* spxx = malloc(i * sizeof(Real));
	Real* spyy = malloc(i * sizeof(Real));
	Real* spxy = malloc(i * sizeof(Real));

	rewind(file);//将文件指针从新指向文件的开头
	i = 0;
	fgets(line, 256, file); //跳过首行
	fgets(line, 256, file);
	while (1)
	{
		if (feof(file) != 0)
		{
			fclose(file);
			break;
		}
		else
		{
			// 移除换行符
			line[strcspn(line, "\n")] = '\0';
			sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]", idstr, xstr, ystr, sxxstr, syystr, sxystr);
			idp[i] = atoi(idstr) - 1;
			xp[i] = atof(xstr);
			yp[i] = atof(ystr);
			spxx[i] = atof(sxxstr);
			spyy[i] = atof(syystr);
			spxy[i] = atof(sxystr);

			i++;

			fgets(line, 256, file);
		}
	}
	fclose(file);

	*id = idp;
	*x = xp;
	*y = yp;
	*sxx = spxx;
	*syy = spyy;
	*sxy = spxy;
}

static void Read_pore_pressure_data_from_file(char* filename, int* nrow, int** id, Real** x, Real** y, Real** p)
{
	int i = 0;
	FILE* file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("无法打开文件,来自Read_pore_pressure_data_from_file\n");
		return;
	}
	else
	{
		printf("Read_pore_pressure_data_from_file 读入数据文件 %s 成功!!!\n", filename);
	}

	char line[256];
	char idstr[30], xstr[30], ystr[30], zstr[30], pstr[30];

	fgets(line, sizeof(line), file);
	while (fgets(line, sizeof(line), file))
	{
		i++;
	}
	*nrow = i;

	int* idp = malloc(i * sizeof(int));
	Real* xp = malloc(i * sizeof(Real));
	Real* yp = malloc(i * sizeof(Real));
	Real* pp = malloc(i * sizeof(Real));

	rewind(file);//将文件指针从新指向文件的开头
	i = 0;
	fgets(line, 256, file); //跳过首行
	fgets(line, 256, file);
	while (1)
	{
		if (feof(file) != 0)
		{
			fclose(file);
			break;
		}
		else
		{
			line[strcspn(line, "\n")] = '\0';
			sscanf(line, "%[^,],%[^,],%[^,],%[^,]", idstr, xstr, ystr, pstr);
			idp[i] = atoi(idstr) - 1;
			xp[i] = atof(xstr);
			yp[i] = atof(ystr);
			pp[i] = atof(pstr);

			i++;

			fgets(line, 256, file);
		}
	}
	fclose(file);

	*id = idp;
	*x = xp;
	*y = yp;
	*p = pp;
}

// 最近邻插值函数
static double interpolate2D(double* x, double* y, double* T, int numPoints, double x0, double y0)
{
	double minDistance = 1e20;
	double T0 = 0;
	for (int i = 0; i < numPoints; i++)
	{
		double distance = (x[i] - x0) * (x[i] - x0) + (y[i] - y0) * (y[i] - y0);
		if (distance < minDistance)
		{
			minDistance = distance;
			T0 = T[i];
		}
	}
	return T0;
}

static double interpolate3D(double* x, double* y, double* z, double* T, int numPoints, double x0, double y0, double z0)
{
	double minDistance = 1e20;
	double T0 = 0;
	for (int i = 0; i < numPoints; i++)
	{
		double distance = (x[i] - x0) * (x[i] - x0) + (y[i] - y0) * (y[i] - y0) + (z[i] - z0) * (z[i] - z0);
		if (distance < minDistance)
		{
			minDistance = distance;
			T0 = T[i];
		}
	}
	return T0;
}

void Read_inital_data()
{
	//Read_insitu_stress_data_from_file(FileName1, &numrow1, &idg, &xg, &yg, &sgxx, &sgyy, &sgxy);
	//Read_pore_pressure_data_from_file(FileName2, &numrow2, &idp, &xp, &yp, &pp);
}

void Get_geostress_from_file_2D(int nelem, Real* d1dnix, Real* d1dniy, Real* d2egestress)
{
	for (int ielem = 0; ielem < nelem; ielem++)
	{
		int i0, i1, i2;
		i0 = ielem * 3 + 0;
		i1 = ielem * 3 + 1;
		i2 = ielem * 3 + 2;
		Real xc = (d1dnix[i0] + d1dnix[i1] + d1dnix[i2]) / 3.0;
		Real yc = (d1dniy[i0] + d1dniy[i1] + d1dniy[i2]) / 3.0;
		d2egestress[ielem*6+0] = interpolate2D(xg, yg, sgxx, numrow1, xc, yc);
		d2egestress[ielem*6+1] = interpolate2D(xg, yg, sgyy, numrow1, xc, yc);
		d2egestress[ielem*6+3] = interpolate2D(xg, yg, sgxy, numrow1, xc, yc);
	}
}

void Get_geostress_from_file_3D(int nelem, Real* d1dnix, Real* d1dniy, Real* d1dniz, Real* d2egestress)
{
	for (int ielem = 0; ielem < nelem; ielem++)
	{
		int i0, i1, i2, i3;
		i0 = ielem * 4 + 0;
		i1 = ielem * 4 + 1;
		i2 = ielem * 4 + 2;
		i3 = ielem * 4 + 3;
		Real xc = (d1dnix[i0] + d1dnix[i1] + d1dnix[i2] + d1dnix[i3]) / 4.0;
		Real yc = (d1dniy[i0] + d1dniy[i1] + d1dniy[i2] + d1dniy[i3]) / 4.0;
		Real zc = (d1dniz[i0] + d1dniz[i1] + d1dniz[i2] + d1dniz[i3]) / 4.0;
		d2egestress[ielem * 6 + 0] = interpolate3D(xg, yg, zg, sgxx, numrow1, xc, yc, zc);
		d2egestress[ielem * 6 + 1] = interpolate3D(xg, yg, zg, sgyy, numrow1, xc, yc, zc);
		d2egestress[ielem * 6 + 2] = interpolate3D(xg, yg, zg, sgzz, numrow1, xc, yc, zc);
		d2egestress[ielem * 6 + 3] = interpolate3D(xg, yg, zg, sgxy, numrow1, xc, yc, zc);
		d2egestress[ielem * 6 + 4] = interpolate3D(xg, yg, zg, sgyz, numrow1, xc, yc, zc);
		d2egestress[ielem * 6 + 5] = interpolate3D(xg, yg, zg, sgzx, numrow1, xc, yc, zc);
	}
}


void Get_pore_pressure_from_file_2D(int nfn, Real* d1fnix, Real* d1fniy, Real* d1fnpopre)
{
	for (int ifn = 0; ifn < nfn; ifn++)
	{
		Real xc = d1fnix[ifn];
		Real yc = d1fniy[ifn];
		d1fnpopre[ifn] = interpolate2D(xp, yp, pp, numrow2, xc, yc);
	}
}

void Get_pore_pressure_from_file_3D(int nfn, Real* d1fnix, Real* d1fniy, Real* d1fniz, Real* d1fnpopre)
{
	for (int ifn = 0; ifn < nfn; ifn++)
	{
		Real xc = d1fnix[ifn];
		Real yc = d1fniy[ifn];
		Real zc = d1fniz[ifn];
		d1fnpopre[ifn] = interpolate3D(xp, yp, zp, pp, numrow2, xc, yc, zc);
	}
}

void InitVel(int itype, Real x, Real y, Real z, Real v[3])
{
}

void InitSituStress(int itype, int nstep, Real dtm, Real x, Real y, Real z, Real T[3][3])
{
	//itype表示是*InitSituStres下一行的第一个数据值
	// nstep当前步数，dtm时间步长
	//T[0][0],T[1][1],T[2][2]分别对应sigxx,sigyy,sigzz
	//T[0][1],T[1][2],T[2][1]分别对应sigxy,sigyz,sigzx

}

void InitCrackSat(int itype, Real x, Real y, Real z, Real* sat)
{
}

void InitCrackPressure(int itype, Real x, Real y, Real z, Real* p)
{
}

void InitProppant(int itype, Real x, Real y, Real z, Real* c)
{
	//设置支撑剂浓度
}

void InitPoreSat(int itype, Real x, Real y, Real z, Real* sat)
{
}

void InitPorePre(int itype, Real x, Real y, Real z, Real* p)
{
	//*p=interpolate2D(xg,yg,pg,numrow,x,y);
}

void InitSolidTemperature(int itype, Real x, Real y, Real z, Real* T)
{
}

void InitFluidTemperature(int itype, Real x, Real y, Real z, Real* T)
{
}

void InitIceRatio(int itype, Real x, Real y, Real z, Real* si)
{
	//*si为冰的质量占冰水混合物质量的比值，取值范围[0,1]
}

void InitMoisture(int itype, Real x, Real y, Real z, Real* w)
{
}