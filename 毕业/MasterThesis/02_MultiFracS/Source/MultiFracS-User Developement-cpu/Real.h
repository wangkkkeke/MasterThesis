#define _CRT_SECURE_NO_WARNINGS

#ifndef RealInclude
#define RealInclude

//#define SinglePrecision

#ifdef SinglePrecision

#define Real float
#define RealType "float"

#define LON long long //2019-4-22添加
#define a_const 0.63f
#define b_const 1.8f
#define c_const 6.0f

#define PI 3.1415926535897932384626f
#define SmallPositiveNumber 1.0e-10f
#define SmallNegativeNumber -1.0e-10f
#define LargePositiveNumber 1.0e+15f
#define R0 0.0f
#define R1 1.0f
#define R2 2.0f
#define R3 3.0f
#define R4 4.0f
#define R5 5.0f
#define R6 6.0f
#define R7 7.0f
#define R8 8.0f
#define R9 9.0f
#define R10 10.0f
#define R12 12.0f
#define R18 18.0f
#define R19 19.0f
#define R20 20.0f
#define R24 24.0f
#define R27 27.0f //2019-12-7重新添加
#define R36 36.0f
#define R21 21.0f
#define RP8 0.8f
#define RP2 0.2f
#define RP11 1.1f
#define RP12 1.2f
#define RP15 1.5f
#define RP25 0.25f
#define RP5  0.5f
#define RP31  3.1f
#define RP9  0.9f
#define RP1  0.1f
#define RP3  0.3f
#define RP7  0.7f
#define RP75  0.75f
#define RP37  0.37f
#define ROOT2 1.414213562373095f

#else

#define Real double
#define FloatType "float"

#define LON long long //2019-4-22添加
#define a_const 0.63
#define b_const 1.8
#define c_const 6.0
#define PI 3.1415926535897932384626
#define SmallPositiveNumber 1.0e-10
#define SmallNegativeNumber -1.0e-10
#define LargePositiveNumber 1.0e+15
#define R0 0.0
#define R1 1.0
#define R2 2.0
#define R3 3.0
#define R4 4.0
#define R5 5.0
#define R6 6.0
#define R7 7.0
#define R8 8.0
#define R9 9.0
#define R10 10.0
#define R12 12.0
#define R18 18.0
#define R19 19.0
#define R20 20.0
#define R24 24.0
#define R27 27.0 //2019-12-7重新添加
#define R36 36.0
#define R21 21.0
#define RP8 0.8
#define RP2 0.2
#define RP11 1.1
#define RP12 1.2
#define RP15 1.5
#define RP25 0.25
#define RP5  0.5
#define RP31  3.1
#define RP9  0.9
#define RP1  0.1
#define RP3  0.3
#define RP7  0.7
#define RP75  0.75
#define RP37  0.37
#define ROOT2 1.414213562373095

#endif

#ifdef __linux__
#define USERDLL extern
#else
#define USERDLL __declspec(dllexport)
#endif

#define ITHERMAL 1
#define IMOISTURE 2

#define MaxInt  10000000
#define MinInt -10000000

#define REAL_MAX 1e20
#define REAL_MIN -1e20

typedef unsigned int uint;

#define EType_S2D3 1  //平面应力单元
#define EType_E2D3 2  //平面应变单元 /*D-可变形，2D-维数，S-平面应力，3-节点数*/
#define EType_R2D3 3   //平面刚体 /*R-刚体*/

#define EType_C3D4 11
#define EType_R3D4 12
#define EType_C3D10 13
#define EType_R3D10 14

#define EType_J2D4 31
#define EType_J3D6 32

#define LinElem 1
#define TriElem 2
#define TetElem 3
#define TEEXCA 10 //开挖掉的实体单元

#define Ball2D 2
#define Ball3D 3
#define Bond 0

#define BoltExca -1
#define BoltSleep 0
#define BoltActive 1
#define BoltBroken 2

#define JEGrout -10  //具有粘结强度的界面
#define JEInterfaceIntact 1
#define JEInterfaceBroken 2
#define JEWELL 9 //断裂的节理单元，但不施加流体压力
#define JECRACK 10 //初始断裂的节理单元

#define JEBKT1 11 //拉裂缝
#define JEBKT2 12 //剪裂缝
#define JEBKT3 13 //拉剪混合裂隙

#define JEEXCA 14 //开挖掉的节理单元

#define JEPLUG 1024  //堵塞的节理单元

#define JEISOFT1 1
#define JEISOFT2 2
#define JEISOFT3 3
#define JSOFT    10  //初始断裂的节理单元当然软化
#define JESOFT1 11
#define JESOFT2 12
#define JESOFT3 13

#define NNODE 3

#define MaxInt  10000000
#define MinInt -10000000

#define N2DCELL 9  //需要检测的格子数量
#define NH2DCELL 5
#define N3DCELL 27
#define NH3DCELL 14

#define N2Time 2

#define Tecplot 1
#define ParaView 2

#endif
