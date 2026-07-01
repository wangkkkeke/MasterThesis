#include "Real.h"  
#include "Boundary.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//特别说明：本文件中的指针，仅让用户通过该指针向MultiFracS传递值，MultiFracS不会通过该指针向用户传值
//因此该指针只能出现在等号的左边

//设置宏FileName，表示热源数据的文件名，用户可改成自己的热源数据文件名
//该文件和MultiFracS在同一个文件夹下
//数据文件格式为n行m列，一行的数据逗号分隔，整个文件不要有空行，文件的首行为数据项说，读入时会自动跳过
//用户可以自行修改Read_x_y_data_from_file的代码，来读如不同数据格式的文件
/*
编号,x坐标,y坐标,热源值
id0,x0,y0,H0
id1,x1,y1,H1
.  .
.  .
.  .
idn,xn,yn,Hn
*/
#define FileName "2D-11-Heat-source.csv"

//定义全局变量，本.c文件的函数均可直接使用
int* id = NULL;
Real* x = NULL;
Real* y = NULL;
Real* z = NULL;
Real* H = NULL;
int numb = 0; //真实数据的行数

static void Read_x_y_data_from_file(char* filename, int* nrow, int** id, Real** x, Real** y, Real** z, Real** H)
{
	int i = 0;
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
	char idstr[30], xstr[30], ystr[30], zstr[30], Hstr[30];

	fgets(line, sizeof(line), file);
	while (fgets(line, sizeof(line), file))
	{
		i++;
	}
	*nrow = i;

	int* idp = malloc(i * sizeof(int));
	//Real* yp = malloc(i * sizeof(Real));
	//Real* zp = malloc(i * sizeof(Real));
	Real* Hp = malloc(i * sizeof(Real));


	rewind(file);//将文件指针从新指向文件的开头
	i = 0;
	fgets(line, 256, file);
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
			sscanf(line, "%[^,],%[^,],%[^,],%[^,]", idstr, xstr, ystr, Hstr);
			//printf("%d,%s,%s,%s,%s\n", i,idstr, xstr, ystr, Hstr);
			idp[i] = atoi(idstr) - 1;
			//yp[i] = atof(ystr);
			//zp[i] = atof(zstr);
			Hp[i] = atof(Hstr);

			i++;

			fgets(line, 256, file);
		}
	}
	fclose(file);

	*id = idp;
	//*y = yp;
	//*z = zp;
	*H = Hp;
}

void Read_boundary_data()
{
	Read_x_y_data_from_file(FileName, &numb, &id, &x, &y, &z, &H);
}

void Thermal_volume_heat_source_intensity(int* numid, int** i1nid, Real** d1nH)
{
	//体积热源密度，各个节点的体积热源密度
	*numid = numb;
	*i1nid = id;
	*d1nH = H;
}

void Thermal_solid_T_boundary(int itype, int nstep, Real dtt, Real dtm, Real x, Real y, Real z, Real* T)
{
	//温度边界
	//itype>=5 id=1则会采用本函数中定义的边界
	//*T=f(nstep,dtt)  将温度设置为某种形式的函数
}
void Thermal_solid_qTflow_boundary(int itype, int nstep, Real dtt, Real dtm, Real T, Real x, Real y, Real z, Real* qflow)
{
	//流量边界，非流量密度, *qflow是指施加在单个节点上的流量
	//itype>=5 id=2则会采用本函数中定义的边界
	//if (itype == 5)
	//{
	// *qflow=f(t);
	//}
}
void Thermal_solid_qTflow_per_area_boundary(int itype, int nstep, Real dtt, Real dtm, Real* qflow)
{
	//流量密度边界, *qflow是指施加在边界上单位长度(2D)或面积(3D)的流量
	//itype>=5 id=3 则会采用本函数中定义的流量边界
	//if (itype == 5)
	//{
	// *qflow=f(t);
	//}
}
void Thermal_crack_boundary(int nstep, Real dtt, Real dtm, int bkstep,
	Real x, Real y, Real z, int* itype, Real* hgas, Real* Tgas, Real* Ts1, Real* Ts2, Real* qarea1, Real* qarea2)
{
	//x,y,z表示裂缝的位置
	//*itype=1表示固定温度 *itype=3表示固定流量密度 *itype=4表示和空气的对流边界
	//*Tgas空气温度 *Ts1, *Ts2分别为裂缝两侧的温度，对于计算类型1 *Ts1==*Ts2 
	//*qarea1,*qarea2分别为裂缝两侧的热流量，对于计算类型1 *qarea1==*qarea2 
	//*hgas表示空气和裂缝热交换系数
	//示例代码,以下代码直接将所有裂缝的湿度*wc设置为0.5
	//*itype = 1;
	//*Ts = 0.5;
}

void Moisture_w_boundary(int itype, int nstep, Real dtw, Real dtm, Real x, Real y, Real z, Real* w)
{
	//湿度边界，第一类边界
	// itype>=5 id=1则会采用本函数中定义的边界
}
void Moisture_qflow_boundary(int itype, int nstep, Real dtw, Real dtm, Real* qflow)
{
	//流量边界，施加在单个节点上，第二类边界 
	// itype>=5 id=2则会采用本函数中定义的边界
}
void Moisture_qflow_per_area_boundary(int itype, int nstep, Real dtw, Real dtm, Real* qflow)
{
	//流量密度边界，第二类边界
	// itype>=5 id=3则会采用本函数中定义的边界
}
void Moisture_crack_boundary(int nstep, Real dtw, Real dtm, int bkstep,
	Real x, Real y, Real z, int* itype, Real* hgas, Real* wgas, Real* wc1, Real* wc2, Real* qarea1, Real* qarea2)
{
	//nstep当前步数，dtw湿度时间步长，dtm力学时间步长，bkstep裂纹生成时的步数
	//可以将bkstep作为起点，裂纹的相关边界条件施加持续的时间=(nstep-bkstep)*dtw
	//x,y,z表示裂缝的位置
	//*itype=1表示固定湿度 *itype=3表示固定流量密度 *itype=4表示和空气的对流边界
	//*wgas空气湿度 *wc1,*wc2分别为裂缝两侧湿度，对于计算类型1，*wc1==*wc2
	//*qarea1, *qarea2分别为裂缝两侧的流量，对于计算类型1 *qarea1==*qarea2 
	//示例代码,以下代码直接将所有裂缝的湿度*wc设置为0.5
	//*itype = 1;
	//*wc = 0.5;

}

void Crack_seepage_p_boundary(int itype, int nstep, Real dtf, Real dtm, Real x, Real y, Real z, Real* p)
{
	//压力边界
	// itype>=5 id=1则会采用本函数中定义的边界
	//*p=f(nstep,dtf)  将温度设置为某种形式的函数
}
void Crack_seepage_qflow_boundary(int itype, int nstep, Real dtf, Real dtm, Real* qflow)
{
	//流量边界，非流量密度，*qflow是指施加在单个节点上的流量
	//itype>=5 id=2则会采用本函数中定义的边界
	//if (itype == 5)
	//{
	// *qflow=f(t);
	//}
}
void Crack_seepage_qflow_per_area_boundary(int itype, int nstep, Real dtf, Real dtm, Real* qflow)
{
	//流量密度边界
	//itype>=5 id=3则会采用本函数中定义的边界
}

void Proppant_c_boundary(int itype, int nstep, Real dtf, Real dtm, Real x, Real y, Real z, Real* c)
{
	//itype>=5, id=1支撑剂浓度边界
	//if(itype==5)
	//{
	//	*c=f(nstep,dtf)  //将温度设置为某种形式的函数
	//}
}
void Proppant_qflow_boundary(int itype, int nstep, Real dtf, Real dtm, Real* qflow)
{
	//流量边界，非流量密度，*qflow是指施加在单个节点上的流量
	//itype>=5,id=2则会采用本函数中定义的流量边界
	//if (itype == 5)
	//{
	// *qflow=f(t);
	//}
}

void Pore_seepage_p_boundary(int itype, int nstep, Real dtf, Real dtm, Real x, Real y, Real z, Real* p)
{
	//itype>=5, id=1，则会采用本函数中的压力边界
	//*p=f(nstep,dtf)  将温度设置为某种形式的函数
}
void Pore_seepage_qflow_boundary(int itype, int nstep, Real dtf, Real dtm, Real* qflow)
{
	//流量边界，非流量密度，*qflow是指施加在单个节点上的流量
	//itype>=5, id=2，则会采用本函数中定义的流量边界
	//if (itype == 5)
	//{
	// *qflow=f(t);
	//}
}
void Pore_seepage_qflow_per_area_boundary(int itype, int nstep, Real dtf, Real dtm, Real* qflow)
{
	//流量密度边界 即单位面积上的流量
	//itype>=5，id=3,则会采用本函数中定义的流量边界
	//if (itype == 5)
	//{
	// *qflow=f(t);
	//}
}