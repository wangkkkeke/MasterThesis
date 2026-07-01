#include "Real.h"  
#include "SRM.h"
#include <math.h>
#include <stdio.h>

void Reduction_contact_fric(
	int ematid, 
	Real x, Real y, Real z, 
	Real* ctfric)  //折减接触摩擦系数
{
	//ematid 实体单元的材料编号，从0开始, 跟在.inp文件中出现次序一致
	//*ctfric=factor*(*ctfric);   factor为折减系数

}

void Reduction_joint_fric_co(
	int jematid, 
	Real x, Real y, Real z, 
	Real* jfric, Real* jco
)  //折减节理摩擦系数,
{
	//jematid 节理单的材料编号，从0开始, 跟在.inp文件中出现次序一致
	//*jfric=factor*(*jfric); factor为折减系数
	//*jco=factor*(*jco);

}

void Centrifugal_load(int nstep, Real dtm, Real* dfscl)
{
	//*dfscl为离心加载系数

}



void Set_contact_fric_as_function_of_vs(int nstep, Real dtm, Real vs, Real* fric, int ieflag, int jeflag)
{
	//*fric=f(vs);
	//if (ieflag == eflag || jeflag == eflag) { //修改摩擦系数   }  //仅仅修改真实节理处的摩擦系数
}
