#ifndef CPUCORE_H
#define CPUCORE_H
#include "Real.h" 

typedef struct CPUCORE_struct* CPUCORE;
struct CPUCORE_struct
{
	//--输出频率
	int outvtk; //输出vtk的间隔
	int outconsole;//控制台输出间隔

	Real dtsph; //sph时间步长

	//整体信息
	Real dtm; //力学时间步长
	Real dampCn; //法向接触阻尼
	Real dampCt; //切向接触阻尼

	//---有限元节点
	int nfn;
	Real* d1fnix;
	Real* d1fniy;
	Real* d1fniz;
	
	//---sph单元信息
	int nsph; //sph单元个数
	int* i1sphfnid;//[nsph*(ndim+1)+i] sph实体单元的有限元节点编号
	int* i1sphmatid; //[nsph] SPH单元材料编号
	Real* d1sphrho; //[nsph]流体的初始密度
	Real* d1sphnu; //[nsph]流体粘性
	Real* d1sphcs; //[nsph]流体声速
	Real* d1sphp0; //[nsph]参考压力 大气压 p0=1.013e5 Pa
	Real* d1sphdx; //[nsph]粒子的初始间距 
	Real* d1sphh; //[nsph]粒子光滑长度 h=1.2-1.5dx
	Real* d1sphr; //[nsph]粒子半径

	//---离散节点信息
	int ndn; //节点的数目 从0开始编号
	int ndim; //节点的维数 1-1D 2-2D 3-3D
	Real* d1dncx;  //节点当前坐标
	Real* d1dncy;
	Real* d1dncz;

	Real* d1dnvx;
	Real* d1dnvy;
	Real* d1dnvz;

	Real* d1dnmass;

	Real* d1dnfx;  //节点力
	Real* d1dnfy;
	Real* d1dnfz;
	int* i1dnbnflag; //节点是否为边界节点的标志 [ndn] >0 是边界节点

	//----实体单元信息
	int ndsolidelem; //离散实体单元数
	int* i1enid;     //[ndsolidelem*(ndim+1)] 单元节点编号映射
	int* i1ebeflag; //[ndsolidelem] 边界单元标志
	Real* d1epn;
	Real* d1ept;
	Real* d1efr;

	//----节理单元的信息
	int njelem;   //节理单元的数量
	int* i1jenid;     //节理单元的节点编号
	int* i1jebk; //[jelem] <=0表示节理单元未断裂 >0表示节理单元断裂
};
#endif