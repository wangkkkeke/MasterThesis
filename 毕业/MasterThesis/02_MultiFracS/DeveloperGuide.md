# MultiFracS v5.8 二次开发指南

> 面向读者：需要在 MultiFracS 上添加 InterfaceBond 或其他自定义模块的开发者
> 来源：`User_solver/` 源码 + `MultiFracS-User Developement-cpu/` + inp格式文档

---

## 一、二次开发体系总览

MultiFracS 提供两套二次开发接口，职责不同：

| 接口类型 | 位置 | 适用场景 |
|---------|------|---------|
| **用户函数DLL**（User Plugin DLL） | `MultiFracS-User Developement-cpu/` | 修改本构、边界条件、材料参数函数 |
| **用户求解器DLL**（User Solver DLL） | `User_solver/` | 添加全新物理场（SPH、自定义耦合等） |

**关键原则**：两套接口通过函数签名约定与主程序交互，**函数签名不能修改**，函数体是用户的自由空间。

---

## 二、用户函数DLL 体系（User Plugin DLL）

### 2.1 文件组织

```
MultiFracS-User Developement-cpu/
├── Real.h              ← 类型定义 + 常量 + 不可修改
├── Ce2D.c/h            ← 2D三角单元本构
├── Ce3D.c/h            ← 3D四面体单元本构
├── Cjoint.c/h          ← 通用节理本构（2D）
├── Cjoint2D.c/h        ← 2D节理（带流体压力）
├── Cjoint3D.c/h        ← 3D节理（带流体压力）← InterfaceBond 最近邻
├── Ccjoint.c/h         ← 连续体损伤节理
├── Mech.c/h            ← 力学-多场耦合参数
├── Seepage.c/h         ← 渗流参数
├── Thermal.c/h         ← 热力耦合参数
├── Moisture.c/h        ← 湿度参数
├── Boundary.c/h        ← 多物理场边界条件
├── SBoundary.c/h       ← 面力边界
├── VBoundary.c/h       ← 速度/位移边界（含地震波输入）
├── InSitu.c/h          ← 初始条件
├── Exca.c/h            ← 开挖逻辑
├── FGM.c/h             ← 空间变化材料参数
├── SRM.c/h             ← 强度折减
├── SKE.c/h             ← 单元节点坐标调整
├── Plug.c/h            ← 节理堵塞
├── Bhm.c/h             ← Bingham流体
├── Viscosity.c/h       ← 流体黏度
└── dll_generate_template/   ← VS项目模板
```

### 2.2 各DLL被调用时机

| DLL | 调用时机 | 调用频率 |
|-----|---------|---------|
| `InSitu.dll` | 主程序 preprocess 阶段 | 每节点/单元一次（初始化） |
| `SKE.dll` | preprocess 阶段，单元坐标调整 | 每单元一次 |
| `FGM.dll` | preprocess 阶段，材料参数初始化 | 每单元/节理一次 |
| `Ce3D.dll` | 每步力计算，每个实体单元 | nstep × nelem 次 |
| `Cjoint3D.dll` | 每步力计算，每个节理单元 | nstep × njoint 次 |
| `Mech.dll` | 每步，材料参数更新 | nstep × nmat 次 |
| `Seepage/Thermal/Moisture.dll` | 每步（仅对应物理场开启时） | 同上 |
| `SBoundary.dll` | 每步，面力边界 | nstep × nboundary 次 |
| `VBoundary.dll` | 每步，速度边界 | nstep × nnode_bc 次 |
| `Exca.dll` | 每步（仅 `*vexcavate` 激活时） | nstep × nexca_elem |
| `Plug.dll` | 每步（仅 `*plug` 激活时） | nstep × njoint |

### 2.3 入口函数一览（不可修改签名）

#### Ce3D.dll — 四面体本构
```c
// 每步每单元调用，计算应力增量并累加
USERDLL void Tet_constitutive_equation_increment(
    Real G, Real lamda, int imat,        // 输入：剪切模量、拉梅常数、材料编号
    Real de11, Real de22, Real de33,     // 输入：正应变增量
    Real de12, Real de23, Real de31,     // 输入：剪应变增量
    Real* s11, Real* s22, Real* s33,    // 输入输出：应力（累加）
    Real* s12, Real* s23, Real* s31
);
```

#### Cjoint3D.dll — 3D节理本构
```c
// 完整节理：计算损伤 + 键力
USERDLL void Cjoint3D_intact(
    Real rs[][3],          // 输入：3个积分点的相对位移向量[3][3]
    Real vnor[3],          // 输入：节理面单位法向量
    Real area,             // 输入：节理面面积
    Real h,                // 输入：特征长度
    Real pn, Real ps,      // 输入：法向/切向罚参数
    Real co, Real fric, Real ft, Real gi, Real gii,
    int imat, int* ijesf, int* ijebk, Real* damge, Real* d1jefs,
    Real p1, Real p2, Real p3,          // 输入：3积分点处流体压力
    Real fnt[][3]          // 输出：3积分点处的节点力[3][3]
);

// 断裂节理：仅计算摩擦接触力
USERDLL void Cjoint3D_broken(
    Real rs[][3], Real vnor[3], Real area, Real h,
    Real pn, Real ps, Real co, Real fric, Real ft, Real gi, Real gii,
    int imat, int* ijesf, int* ijebk, Real* damge,
    Real p1, Real p2, Real p3,
    Real fnt[][3]
);
```

#### VBoundary.dll — 速度边界
```c
// CPU版：每步每边界节点调用
USERDLL void User_node_velocity_boundary(
    int itype, int nstep, Real dtm,
    Real fx, Real fy, Real fz,           // 该边界集合受到的总力（只读）
    Real* x, Real* y, Real* z,          // 节点当前坐标（可修改以约束位置）
    Real* vx, Real* vy, Real* vz,       // 节点速度（可设置）
    int* ifix, int* ifiy, int* ifiz     // 1=固定该方向
);

// GPU版（仅GPU计算有效）
USERDLL void User_node_velocity_boundary_GPU(
    const int itype, const Real value,
    const Real* x, const Real* y, const Real* z,
    Real* vx, Real* vy, Real* vz,
    int* ifix, int* ifiy, int* ifiz
);
```

#### SBoundary.dll — 面力边界
```c
// itype>=6 时触发用户代码
USERDLL void User_surface_force_boundary(
    int itype, int nstep, Real dtm,
    Real Ela, Real vp, Real ro,          // 当前单元弹模、泊松比、密度
    Real x, Real y, Real z,             // 面元中心坐标
    Real vn, Real vs,                    // 法向速度、切向速度（带符号）
    Real* pre,                           // 输出：法向面力（压为正）
    Real* tao                            // 输出：切向面力
);
// 典型用途：吸收边界（Lysmer）、爆炸荷载
// pre = -(ρ·Cp)·vn;  tao = -(ρ·Cs)·vs;
```

#### InSitu.dll — 初始条件
```c
// 以下函数 itype 对应 inp 中第一个参数（>=2 触发用户代码）
USERDLL void InitVel(int itype, Real x, Real y, Real z, Real v[3]);
USERDLL void InitSituStress(int itype, int nstep, Real dtm, Real x, Real y, Real z, Real T[3][3]);
USERDLL void InitCrackPressure(int itype, Real x, Real y, Real z, Real* p);
USERDLL void InitPorePre(int itype, Real x, Real y, Real z, Real* p);
USERDLL void InitSolidTemperature(int itype, Real x, Real y, Real z, Real* T);
// 可读取外部文件（CSV）进行最近邻插值赋初值
```

#### FGM.dll — 空间变化材料
```c
// ie=单元编号(0起), x/y/z=单元中心坐标
USERDLL void FGM_ela(int ie, Real x, Real y, Real z, Real* ela);
USERDLL void FGM_vp(int ie, Real x, Real y, Real z, Real* vp);
USERDLL void FGM_ro(int ie, Real x, Real y, Real z, Real* ro);
// 节理单元（传入*ijebk可强制设置初始断裂）
USERDLL void FGM_joint(int nje, int je, Real x, Real y, Real z,
    Real* pn, Real* pt, Real* ft, Real* co, Real* fric, Real* gi, Real* gii,
    int* ijebk, Real* am0, Real* a0, Real* amin, Real* amax, Real len);
```

---

## 三、用户求解器DLL 体系（User Solver DLL）

### 3.1 文件组织

```
User_solver/
├── Cpucore.h           ← 主程序传给用户的数据结构（只读接口，不可修改）
├── Cpuuser.h           ← 用户自定义数据结构（可扩展）
├── Cpuuser_abstract.h  ← DLL导出函数声明（不可修改签名）
├── User_create.c       ← Create_cpuuser()：分配CPUUSER内存
├── User_preprocess.c   ← preprocess_cpuuser()：读用户inp、初始化
├── User_solve.c        ← user_solver() + user_to_MultiFracS()：核心逻辑
└── User_postprocess.c  ← Output_vtk_user() + Output_mointor_history_user()：输出
```

### 3.2 调用关系图

```
MultiFracS 主程序
│
├─ 启动阶段：
│   ├─ Create_cpuuser()                  ← User_create.c
│   └─ preprocess_cpuuser(cpucore, file) ← User_preprocess.c
│
├─ 每个时间步（主循环内）：
│   ├─ ① [主程序] Ce3D / Cjoint3D / Cd3D / Cf3D / Boundary 计算
│   ├─ ② solve_user(cpucore, cpuuser)    ← solve_for_user.c（框架，不修改）
│   │     └─ for i in range(nuser):
│   │          user_solver(cpucore, cpuuser)  ← User_solve.c（用户写）
│   │          nuserstep++; time += dt
│   ├─ ③ user_to_MultiFracS(cpucore, cpuuser) ← User_solve.c（用户写）
│   │     → 将用户场力注入 cpucore->d1dnfx/y/z
│   └─ ④ [主程序] 显式时间积分 a=F/m → v → x
│
└─ 输出阶段：
    ├─ Output_mointor_history_user(cpuuser, nhstep)  ← User_postprocess.c
    └─ Output_vtk_user(cpuuser, nhstep)              ← User_postprocess.c
```

### 3.3 关键函数详解

#### `Create_cpuuser()` — 初始化分配
```c
USERDLL CPUUSER Create_cpuuser() {
    CPUUSER cpuuser = malloc(sizeof(CPUUSER_struct));
    return cpuuser;
}
// 职责：仅分配 CPUUSER 结构体内存
// 用户：如果添加了指针字段到 CPUUSER_struct，在此处 malloc 子内存
// 调用时机：主程序启动，preprocess 之前，调用一次
```

#### `preprocess_cpuuser()` — 预处理
```c
void preprocess_cpuuser(CPUUSER cpuuser, char* userfilename) {
    Cpuuser_default_value(cpuuser);      // 设默认值
    Cpuuser_allocate_memory(cpuuser);    // 分配动态数组
    Cpuuser_read_input_data_file(cpuuser, userfilename); // 读用户inp
}
// 职责：
//   1. 初始化 CPUUSER 所有字段默认值
//   2. 分配动态内存（如 snum 个三角面的坐标数组）
//   3. 读取用户自定义 inp 文件（可选）
// 调用时机：主程序 preprocess 阶段，读完主inp后调用一次
// 注意：此时 cpucore 已填充，可访问 nfn/ndn/njelem 等
```

#### `user_solver()` — 核心求解
```c
void user_solver(CPUCORE cpucore, CPUUSER cpuuser) {
    // 用户在此处编写自定义场的求解逻辑
    // 可访问的数据：
    //   cpucore->ndn, d1dncx/y/z    ← 节点坐标
    //   cpucore->d1dnvx/y/z         ← 节点速度
    //   cpucore->i1jenid, i1jebk    ← 节理状态
    //   cpucore->nsph, i1sphfnid    ← 颗粒所属FEM节点
    //   cpucore->dtm                ← 时间步长
    //   cpuuser->nuserstep          ← 当前用户计算步数
}
// 注意：这里修改 cpucore->d1dnfx/y/z 无效！
// 要修改力，必须在 user_to_MultiFracS 中进行
```

#### `user_to_MultiFracS()` — 力注入
```c
void user_to_MultiFracS(CPUCORE cpucore, CPUUSER cpuuser) {
    // 将用户场的力施加到节点上
    // 这是写入 d1dnfx/y/z 的正确位置
    // 示例：
    //   cpucore->d1dnfx[nodeID] += myForceX;
}
// 调用时机：user_solver 完成后，显式积分之前
// 职责：将 user_solver 中计算的力注入主程序节点力数组
```

#### `Output_vtk_user()` — VTK 输出扩展
```c
void Output_vtk_user(CPUUSER cpuuser, long long nhstep) {
    // 写用户自定义 VTK 文件
    // 文件名建议：fname + "-user-" + nhstep + ".vtk"
    // 格式：VTK Legacy ASCII（UNSTRUCTURED_GRID）
    // 可输出：SPH 颗粒位置、InterfaceBond 键力、自定义场变量
}
// 调用时机：与主程序 VTK 同步，每 outvtk 步调用一次
```

### 3.4 CPUUSER 结构体扩展方法

```c
// 当前默认 CPUUSER（Cpuuser.h）：
struct CPUUSER_struct {
    char userInputFileName[100];
    int nuser;       // 每整体步循环几次user_solver
    int nuserstep;   // 当前用户步数（由框架自动增加）
    Real dusertime;  // 用户场当前时间
    Real duserdt;    // 用户时间步长

    // ↓ 用户添加自己的数据 ↓
    int snum;        // 示例：三角面数量
};

// 添加 InterfaceBond 相关数据的方法：
struct CPUUSER_struct {
    // ... 原有字段 ...

    // InterfaceBond 数据
    int nbond;               // 界面键数量
    int* bondFemElemID;      // [nbond] 每个键对应的FEM单元ID
    int* bondDemParticleID;  // [nbond] 对应的DEM颗粒ID（在d1dn*中的编号）
    Real* bondShapeN;        // [nbond*4] 形函数系数
    Real* bondKn;            // [nbond] 法向刚度
    Real* bondKt;            // [nbond] 切向刚度
    Real* bondForce;         // [nbond*3] 当前键力向量（dx,dy,dz）
    int* bondState;          // [nbond] 0=完整，1=断裂
};
```

---

## 四、不能修改的接口（禁止区）

### 4.1 不可修改的文件

| 文件 | 原因 |
|------|------|
| `Real.h` | 主程序依赖其中所有 `#define` 和类型定义，修改会导致ABI不兼容 |
| `Cpucore.h` | 主程序传递给DLL的内存布局，修改会导致内存访问错误 |
| `Cpuuser_abstract.h` | DLL导出函数签名，修改会导致主程序无法加载DLL |
| `solve_for_user.c` | 框架调度逻辑（虽然是用户DLL的一部分，建议不改） |

### 4.2 不可修改的函数签名

以下函数的**参数列表**不可修改，只能修改函数体：

```
Ce2D / Ce3D:
  Tri_constitutive_equation_increment(...)
  Tet_constitutive_equation_increment(...)

Cjoint / Cjoint2D / Cjoint3D:
  op_ot_sp_st(...)
  Cjoint(...)           Cjoint3D_intact(...)
  Cjoint_broken(...)    Cjoint3D_broken(...)

SBoundary:
  User_surface_force_boundary(...)
  Mech_crack_force_boundary(...)

VBoundary:
  User_node_velocity_boundary(...)
  User_node_velocity_boundary_GPU(...)

InSitu:
  InitVel(...)  InitSituStress(...)  InitCrackPressure(...)
  InitPorePre(...)  InitSolidTemperature(...)  等所有 Init* 函数

User_solver（Cpuuser_abstract.h中声明的所有）:
  Create_cpuuser()
  preprocess_cpuuser(CPUUSER, char*)
  solve_user(CPUCORE, CPUUSER)
  user_solver(CPUCORE, CPUUSER)
  user_to_MultiFracS(CPUCORE, CPUUSER)
  Output_mointor_history_user(CPUUSER, int)
  Output_vtk_user(CPUUSER, long long)
```

### 4.3 不可修改的 `cpucore->` 字段含义

以下字段由主程序写入，用户只能读取，**不能从用户DLL修改其内存布局**：

```
cpucore->nfn, ndn, ndim, ndsolidelem, njelem, nsph
cpucore->d1fnix/y/z    (初始坐标，只读)
cpucore->i1enid        (单元拓扑，只读)
cpucore->i1jenid       (节理拓扑，只读)
cpucore->i1jebk        (节理状态，可读，注意并发)
```

**可写的字段**（仅在 `user_to_MultiFracS` 中）：
```
cpucore->d1dnfx/y/z    ← 这是用户DLL向主程序注入力的唯一合法通道
```

---

## 五、InterfaceBond 二次开发路线（论文方案）

### 5.1 选择开发位置

**方案A（推荐）：扩展 User_solver.dll**

优点：不修改已有DLL，风险低；可访问完整 CPUCORE 数据；灵活。
```
User_solve.c 中实现 user_solver():
  1. 识别界面键（preprocess阶段完成，存于cpuuser）
  2. 形函数插值 FEM 侧代理速度
  3. 计算 InterfaceBond 力
  4. 存入 cpuuser->bondForce

user_to_MultiFracS() 中:
  1. 将 bondForce 分配给 FEM 节点（按形函数权重）
  2. 将 bondForce 反向施加给 DEM 颗粒
```

**方案B：扩展 Cjoint3D.dll**

仅适合主程序将 InterfaceBond 类型节理路由到该 DLL 时。
需要导师确认主程序的节理类型派发逻辑。

### 5.2 User_solver 实现步骤

**Step 1：preprocess_cpuuser — 界面识别**
```c
void Cpuuser_generate_input_data_file(CPUUSER cpuuser) {
    // 1. 遍历 cpucore 节理单元（njelem，i1jenid，i1jebk）
    //    识别 ijebk == JEInterfaceBond（新定义的标志值，如 50）的节理
    // 2. 对每个界面键：
    //    - 查找对应 FEM 单元（通过几何位置搜索）
    //    - 计算颗粒在四面体内的重心坐标 → shapeFuncN[4]
    // 3. 填充 cpuuser->bondFemElemID/demParticleID/bondShapeN
}
```

**Step 2：user_solver — 每步键力计算**
```c
void user_solver(CPUCORE cpucore, CPUUSER cpuuser) {
    for (int ib = 0; ib < cpuuser->nbond; ib++) {
        if (cpuuser->bondState[ib] != 0) continue;  // 已断裂跳过

        int* fnid = &cpucore->i1sphfnid[ib*4];
        Real* N   = &cpuuser->bondShapeN[ib*4];

        // FEM 侧代理颗粒速度（形函数插值）
        Real vx_proxy = N[0]*cpucore->d1dnvx[fnid[0]] + N[1]*cpucore->d1dnvx[fnid[1]]
                      + N[2]*cpucore->d1dnvx[fnid[2]] + N[3]*cpucore->d1dnvx[fnid[3]];
        // ... vy, vz 同理

        // DEM 颗粒速度
        int demID = cpuuser->bondDemParticleID[ib];
        Real vx_dem = cpucore->d1dnvx[demID];

        // 相对速度 → 位移增量 → 键力
        Real dvx = vx_proxy - vx_dem;
        // ... 分解法向/切向分量，乘以 Kn/Kt，累积 bondForce
    }
}
```

**Step 3：user_to_MultiFracS — 力注入**
```c
void user_to_MultiFracS(CPUCORE cpucore, CPUUSER cpuuser) {
    for (int ib = 0; ib < cpuuser->nbond; ib++) {
        if (cpuuser->bondState[ib] != 0) continue;

        Real* F   = &cpuuser->bondForce[ib*3];
        int* fnid = &cpucore->i1sphfnid[ib*4];
        Real* N   = &cpuuser->bondShapeN[ib*4];
        int demID = cpuuser->bondDemParticleID[ib];

        // 力施加到 DEM 颗粒（反向）
        cpucore->d1dnfx[demID] -= F[0];
        cpucore->d1dnfy[demID] -= F[1];
        cpucore->d1dnfz[demID] -= F[2];

        // 力按形函数权重分配到4个 FEM 节点（正向）
        for (int i = 0; i < 4; i++) {
            cpucore->d1dnfx[fnid[i]] += N[i] * F[0];
            cpucore->d1dnfy[fnid[i]] += N[i] * F[1];
            cpucore->d1dnfz[fnid[i]] += N[i] * F[2];
        }
    }
}
```

### 5.3 编译与部署

```
1. 打开 dll_generate_template/generate_modules.sln（Visual Studio）
2. 复制 User_solver/ 文件到项目中，或新建 vcxproj 引用这些文件
3. 配置编译选项：
   - 输出类型：动态链接库（DLL）
   - 平台：x64
   - 配置：Release（调试用 Debug）
   - 附加包含目录：添加 User_solver/ 路径
4. 编译生成 User_solver.dll
5. 将生成的 DLL 替换到 MultiFracS.exe 同目录
6. 运行 MultiFracS.exe 测试
```

---

## 六、调试建议

### 6.1 验证 DLL 加载
```
主程序启动时控制台会打印：
  "Read_seismic_data" 或 "Read_inital_data" 等日志
  → 确认 DLL 正确加载
```

### 6.2 添加调试输出
```c
// 在 user_solver 中临时添加（生产版本需删除）
if (cpuuser->nuserstep % 100 == 0) {
    printf("InterfaceBond step=%d nbond=%d F[0]=%e\n",
           cpuuser->nuserstep, cpuuser->nbond,
           cpuuser->bondForce[0]);
}
// 输出重定向到 zConsolePrint-.dat 文件，闪退后可查看
```

### 6.3 能量守恒检验
InterfaceBond 实现正确的必要条件：
- FEM 侧接受的力 + DEM 侧接受的力 = 0（作用反作用）
- 界面总功率 = 0（无虚功）
- Ghost Force 指标：静止状态下节点力残差应趋近 0

---

## 七、快速参考：应该修改哪个文件？

| 开发目标 | 修改文件 | 关键函数 |
|---------|---------|---------|
| 修改 FEM 单元本构（如增加塑性） | `Ce3D.c` | `Tet_constitutive_equation_increment` |
| 修改节理断裂准则 | `Cjoint3D.c` | `Cjoint3D_intact` |
| 添加吸收边界条件 | `SBoundary.c` | `User_surface_force_boundary` |
| 施加地震波荷载 | `VBoundary.c` | `User_node_velocity_boundary` |
| 设置非均匀初始地应力 | `InSitu.c` | `InitSituStress` + 从CSV读取 |
| 设置空间变化材料参数 | `FGM.c` | `FGM_ela` / `FGM_joint` |
| **添加 InterfaceBond（论文）** | `User_solver/User_solve.c` | `user_solver` + `user_to_MultiFracS` |
| 添加 SPH 流体 | `User_solver/User_solve.c` | 同上 |
| 扩展自定义 VTK 输出 | `User_solver/User_postprocess.c` | `Output_vtk_user` |
| 设置强度折减 | `SRM.c` | `Reduction_contact_fric` |
| 非牛顿流体 | `Bhm.c` | `Bingham_fluid` |

---

*本文件为 MultiFracS 二次开发内部指南，基于源码分析生成，持续更新。*
