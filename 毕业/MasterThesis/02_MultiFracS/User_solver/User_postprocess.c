#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <time.h>
#include <signal.h>
#include <omp.h>
#include "Cpuuser_abstract.h"
#include "Cpuuser.h"

void Output_mointor_history_user(CPUUSER cpuuser, int nhstep)  //输出监测数据
{
	//FILE static* fileUserMonitor = FileNULL;
	//static int itimes = 0;
	//if (itimes == 0)
	//{
	//	itimes = 1;

	//	char outfilename[200] = "";
	//	char path[200] = "";
	//	char fname[200] = "";
	//	path_and_file_name(cpuuser->userInputFileName, path, fname);
	//	strcpy(outfilename, path);

	//	strcat(outfilename, "User-Monitor-");
	//	strcat(outfilename, fname);
	//	strcat(outfilename, ".csv");
	//	fileUserMonitor = fopen(outfilename, "wb");
	//}

	//fprintf(fileUserMonitor, "step, Uy(m), Fy(N), sigma(Pa),");
	//fprintf(fileUserMonitor, " nbj, nbjt, nbjs, nbjts, nbj_space, nbjt_space, nbjs_space, njsoftI, njsoftII, njsotI_II,");
	//fprintf(fileUserMonitor, " dEkbj(J), dEkbjt(J), dEkbjs(J), dEkbj_space(J), dEkbjt_space(J), dEkbjs_space(J), Ek(J), Es(J), Eg(J), E(J)\n");
}

void Output_vtk_user(CPUUSER cpuuser, long long nhstep) //输出云图
{
	//char outfilename[200] = "";
	//char path[200] = "";
	//char fname[200] = "";
	//path_and_file_name(cpuuser->userInputFileName, path, fname);
	//strcpy(outfilename, path);
	//strcat(outfilename, fname);

	//strcat(outfilename, "-user-");
	//char ctmp[200];
	//sprintf(ctmp, "%lld", nhstep);
	//strcat(outfilename, ctmp);
	//strcat(outfilename, ".vtk");
	//FILE* pFile = fopen(outfilename, "wb");

	//fprintf(pFile, "# vtk DataFile Version 2.0\n");
	//fprintf(pFile, "Unstructured Grid Example\n");
	//fprintf(pFile, "ASCII\n");
	//fprintf(pFile, "\n");
	//fprintf(pFile, "DATASET UNSTRUCTURED_GRID\n");

	////输出节点坐标
	//fprintf(pFile, "POINTS %d %s\n", num, FloatType);
	//for (int in = 0; in < num; in++)
	//{
	//	fprintf(pFile, "%f %f %f\n", x[in], y[in], 0.0);
	//}
	//fprintf(pFile, "\n");

	////---输出单元数据
	//fprintf(pFile, "CELLS %d %d\n", num, 2*num);
	//for (int ie = 0; ie < num; ie++)
	//{
	//	fprintf(pFile, "1 %d\n", ie);
	//}
	//fprintf(pFile, "\n");

	//fprintf(pFile, "CELL_TYPES %d\n", num);
	//for (int ie = 0; ie < num; ie++)
	//{
	//	fprintf(pFile, "1\n");
	//}

	//fprintf(pFile, "POINT_DATA %d\n", num);
	//
	//fprintf(pFile, "VECTORS V %s\n", FloatType);
	//for (int in = 0; in < num; in++)
	//{
	//	fprintf(pFile, "%f %f %f\n", vx[in], vy[in], 0.0);
	//}

	//fprintf(pFile, "SCALARS p %s 1\n", FloatType);
	//fprintf(pFile, "LOOKUP_TABLE default\n");
	//for (int in = 0; in < num; in++)
	//{
	//	fprintf(pFile, "%f ", p[in]);
	//	if (in % 16 == 0 || in == num - 1)
	//	{
	//		fprintf(pFile, "\n");
	//	}
	//}
}