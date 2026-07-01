# MultiFracS v5.8 架构分析

> 分析对象：`02_MultiFracS/Source/2026-05-08/` DLL列表 + `MultiFracS-User Developement-cpu/` 源码
> 分析日期：2026-06-30
> 分析目的：理解软件模块组成，为FEM-DEM共生耦合(InterfaceBond)开发定位入口

---

## 一、总体架构

MultiFracS 采用**插件化DLL架构**：主程序 `MultiFracS.exe` 在运行时动态加载各功能DLL，通过 `USERDLL`（即 `__declspec(dllexport)`）导出标准化函数接口。

全部DLL按可定制性分为两类：

| 类别 | 说明 |
|------|------|
| **用户可定制DLL（CPU）** | 提供C源码，用户可修改后重新编译替换 |
| **核心引擎DLL（不开放源码）** | 仅有编译好的DLL，无C源码 |
| **GPU加速DLL** | 对应CPU版本的CUDA并行实现 |

---

## 二、DLL完整列表与分类

### 2.1 用户可定制模块（CPU，含C源码）

#### 【力学求解类】

| DLL | 对应源文件 | 功能描述 |
|-----|-----------|---------|
| `Ce2D.dll` | Ce2D.c/h | 2D三角形单元本构方程（平面应力/应变，增量格式） |
| `Ce3D.dll` | Ce3D.c/h | 3D四面体单元本构方程（C3D4，六分量应力增量） |
| `Cjoint.dll` | Cjoint.c/h | 节理单元核心本构模型（4种损伤演化模式，处理完整/断裂状态，Mohr-Coulomb准则） |
| `Cjoint2D.dll` | Cjoint2D.c/h | 2D节理单元本构（完整/断裂双函数，含流体压力 p1/p2） |
| `Cjoint3D.dll` | Cjoint3D.c/h | 3D节理单元本构（三角面，含法向力和切向力，含流体压力 p1/p2/p3） |
| `Ccjoint.dll` | Ccjoint.c/h | 连续体损伤节理模型（Ccjoint：区别于离散裂纹的等效连续体处理） |
| `Mech.dll` | Mech.c/h | 力学-多物理场耦合参数控制（弹模/渗透率/换热系数随应力/时间的函数、注浆触发） |
| `SKE.dll` | SKE.c/h | 单元节点坐标调整（按内切球半径向外扩展W，2D三角形/3D四面体，消除零厚度节理单元干涉） |

#### 【多物理场参数类】

| DLL | 对应源文件 | 功能描述 |
|-----|-----------|---------|
| `Seepage.dll` | Seepage.c/h | 孔隙渗流材料参数随压力/饱和度变化（Ela、kf、fric、ft、co、Gi、Gii） |
| `Thermal.dll` | Thermal.c/h | 温度相关材料参数（密度、弹模、热膨胀、导热系数、比热容、渗透率、裂纹参数） |
| `Moisture.dll` | Moisture.c/h | 含湿量相关材料参数（弹模、湿传系数、热膨胀、摩擦、强度参数） |
| `Viscosity.dll` | Viscosity.c/h | 流体黏度随位置/时间/压力/饱和度变化 |
| `Bhm.dll` | Bhm.c/h | Bingham流体模型（裂缝内非牛顿流体流量计算）+ 非饱和修正函数 |

#### 【边界条件类】

| DLL | 对应源文件 | 功能描述 |
|-----|-----------|---------|
| `Boundary.dll` | Boundary.c/h | 全物理场边界条件（热、温度、湿、裂隙渗流、孔隙渗流、支撑剂浓度边界，含体积热源） |
| `SBoundary.dll` | SBoundary.c/h | 面力边界条件（用户自定义法向/切向面力，裂缝水压边界） |
| `VBoundary.dll` | VBoundary.c/h | 速度/位移边界条件（节点速度函数、地震波输入、GPU版本接口） |

#### 【初始条件类】

| DLL | 对应源文件 | 功能描述 |
|-----|-----------|---------|
| `InSitu.dll` | InSitu.c/h | 初始状态设置（初始地应力、速度、孔压、温度、含湿量、冰比例、裂隙饱和度/压力、支撑剂浓度） |

#### 【特殊功能类】

| DLL | 对应源文件 | 功能描述 |
|-----|-----------|---------|
| `Exca.dll` | Exca.c/h | 开挖模拟（按时间步激活/停用单元，模拟施工开挖过程） |
| `FGM.dll` | FGM.c/h | 功能梯度材料（Functionally Graded Material，材料参数随空间坐标连续变化） |
| `SRM.dll` | SRM.c/h | 强度折减法（Strength Reduction Method，摩擦/黏聚力按比例折减 + 离心加速荷载） |
| `Plug.dll` | Plug.c/h | 节理堵塞（根据位置/压力判断节理是否堵塞，控制 ijebk 标志位） |
| `User_solver.dll` | — | 用户自定义求解器扩展接口（DLL存在但CPU源码未开放） |

---

### 2.2 核心引擎模块（无C源码，主程序内部或专用DLL）

| DLL | 推断功能 | 依据 |
|-----|---------|------|
| `Cd2D.dll` | DEM二维离散元接触力计算（颗粒-颗粒、颗粒-结构Hertz-Mindlin体系） | 命名规律 C=Contact/Core，d=DEM，2D |
| `Cd3D.dll` | DEM三维离散元接触力计算 | 同上，3D |
| `Cf2D.dll` | 裂缝流体渗流（二维裂隙网络水力耦合计算） | C=Crack/Core，f=Fluid，未见用户源码 |
| `Cf3D.dll` | 裂缝流体渗流（三维） | 同上，3D |
| `cseepage.dll` | 连续体孔隙渗流核心计算（区别于裂缝渗流） | 命名含seepage，无用户源码 |
| `cudart64_12.dll` | CUDA 12运行时库（第三方，NVIDIA） | 标准CUDA运行时 |

---

### 2.3 GPU加速模块（CUDA，与CPU版对应）

| GPU DLL | 对应CPU DLL | 说明 |
|---------|------------|------|
| `gpu_Cd2D.dll` | Cd2D.dll | GPU版DEM二维接触 |
| `gpu_Cd3D.dll` | Cd3D.dll | GPU版DEM三维接触 |
| `gpu_Ce2D.dll` | Ce2D.dll | GPU版2D单元本构 |
| `gpu_Ce3D.dll` | Ce3D.dll | GPU版3D单元本构 |
| `gpu_Cf2D.dll` | Cf2D.dll | GPU版裂缝流体二维 |
| `gpu_Cf3D.dll` | Cf3D.dll | GPU版裂缝流体三维 |
| `gpu_Cjoint2D.dll` | Cjoint2D.dll | GPU版2D节理本构 |
| `gpu_Cjoint3D.dll` | Cjoint3D.dll | GPU版3D节理本构 |
| `gpu_Mech.dll` | Mech.dll | GPU版力学耦合参数 |
| `gpu_Moisture.dll` | Moisture.dll | GPU版含湿量参数 |
| `gpu_Seepage.dll` | Seepage.dll | GPU版渗流参数 |
| `gpu_Thermal.dll` | Thermal.dll | GPU版温度参数 |
| `gpu_Boundary_T.dll` | Boundary.dll（热） | GPU版温度边界 |
| `gpu_Boundary_w.dll` | Boundary.dll（湿） | GPU版湿边界 |
| `gpu_Boundary_pf.dll` | Boundary.dll（裂隙渗流） | GPU版裂隙渗流边界 |
| `gpu_Boundary_cf.dll` | Boundary.dll（连续体渗流） | GPU版孔隙渗流边界 |
| `gpu_Boundary_crack_Tw.dll` | Boundary.dll（裂缝热湿） | GPU版裂缝热湿耦合边界 |
| `gpu_SBoundary.dll` | SBoundary.dll | GPU版面力边界 |
| `gpu_VBoundary.dll` | VBoundary.dll | GPU版速度边界 |
| `gpu_Exca.dll` | Exca.dll | GPU版开挖 |
| `gpu_User_solver.dll` | User_solver.dll | GPU版用户求解器 |

---

## 三、模块依赖关系

```
MultiFracS.exe（主程序/求解引擎）
│
├── 核心动力学（不开放）
│   ├── Cd2D/Cd3D      ← DEM接触力主循环
│   ├── Ce2D/Ce3D      ← FEM单元内力
│   ├── Cf2D/Cf3D      ← 裂缝流体
│   └── cseepage       ← 孔隙渗流
│
├── 节理本构（可定制）
│   ├── Cjoint         ← 通用节理（损伤 + 断裂判断）
│   ├── Cjoint2D       ← 2D节理（含流体压力）
│   ├── Cjoint3D       ← 3D节理（含流体压力）
│   └── Ccjoint        ← 连续体损伤节理
│
├── 材料本构（可定制）
│   ├── Ce2D/Ce3D      ← 弹性/弹塑性增量本构
│   └── Mech           ← 应力相关参数（Ela、kf随σ变化）
│
├── 多物理场耦合参数（可定制）
│   ├── Seepage/Thermal/Moisture  ← 渗流/热/湿相关参数
│   ├── Viscosity                  ← 流体黏度
│   └── Bhm                        ← Bingham流体
│
├── 边界与初始条件（可定制）
│   ├── Boundary       ← 所有物理场边界函数
│   ├── SBoundary      ← 面力边界
│   ├── VBoundary      ← 速度/位移边界（含地震波）
│   └── InSitu         ← 初始地应力/温度/孔压
│
└── 特殊功能（可定制）
    ├── Exca           ← 开挖
    ├── FGM            ← 梯度材料
    ├── SRM            ← 强度折减
    ├── SKE            ← 节点坐标调整
    ├── Plug           ← 节理堵塞
    └── User_solver    ← 用户扩展
```

---

## 四、关键数据类型（Real.h）

```c
// 精度控制（默认双精度）
#define Real double   // 或 float（#define SinglePrecision 时）

// 单元类型
#define EType_C3D4  11  // 3D四面体变形单元（论文核心FEM单元）
#define EType_R3D4  12  // 3D四面体刚体单元

// 节理单元状态标志
#define JEInterfaceIntact  1   // 完整节理
#define JEInterfaceBroken  2   // 断裂节理
#define JEBKT1            11   // 拉裂缝
#define JEBKT2            12   // 剪裂缝
#define JEGrout           -10  // 注浆节理
```

---

## 五、与论文的关联分析

### InterfaceBond开发位置推断

论文需要实现的 **FEM-DEM共生耦合 InterfaceBond**，根据架构分析：

| 开发内容 | 可能的DLL位置 | 说明 |
|---------|-------------|------|
| FEM-DEM界面识别 | 主程序或新建DLL | 需要同时访问FEM节点和DEM颗粒数据 |
| FEM侧代理颗粒速度插值（形函数） | 主程序或新建DLL | 需访问FEM单元节点速度 |
| InterfaceBond力计算（Kn/Kt） | 类似Cjoint3D的新DLL | 接口格式参考Cjoint3D.h |
| 力反馈到FEM节点 | 主程序 | 需修改主程序力汇集 |
| 节理单元本构（界面键） | 新 `Cjoint_InterfaceBond.dll`（待定） | 或扩展Cjoint3D |

### 需要重点阅读的模块

1. `Cjoint3D.c/h`：最接近InterfaceBond的接口形式（三维界面力计算）
2. `Ce3D.c/h`：C3D4四面体本构，FEM侧积分逻辑
3. `VBoundary.c/h`：节点速度设置，理解速度插值如何馈入系统
4. `InSitu.c/h`：初始状态设置接口，理解数据流格式

### 源码搜索关键词（待阅读主程序时使用）

```
InterfaceBond  Particle  BoundaryParticle  VirtualParticle
ShapeFunction  Interpolation  CouplingPoint
```

---

*本文件由架构阅读自动生成，后续随源码深入阅读持续更新。*
