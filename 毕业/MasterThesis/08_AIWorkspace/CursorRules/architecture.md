# architecture.md — 软件架构规范

> 来源：`02_MultiFracS/Architecture.md` + `DeveloperGuide.md` + `CallGraph.md` + `DataStructure.md`

---

## 0. 工作区目录原则（D004，已定稿，不再修改）

**不确定文件放哪里时，只回答一个问题：**

| 这个文件是什么来源？ | 放哪里 |
|---------------------|--------|
| 别人告诉我们的（文献/教材/开题/导师资料） | `01_KnowledgeBase` |
| 软件本身已有的（MultiFracS 源码/文档）| `02_MultiFracS` |
| 我们开发过程中产生的（Issue/Debug/Review/History）| `03_Development` |
| 我们研究出来的（公式推导/设计/FormulaIndex）| `05_Research` |
| 验证算例跑出来的结果 | `04_VerificationCases` / `06_Results` |
| 最终写进论文的 | `07_Thesis` |

**绝对不按文件格式或名称决定目录位置。**

---

## 1. 整体架构（三层）

```
MultiFracS.exe（主程序，闭源）
    │
    ├── Core Engine DLLs（闭源，不可修改）
    │   ├── Cd3D.dll          ← DEM颗粒接触计算（CPU）
    │   ├── Cf3D.dll          ← FEM单元计算（CPU）
    │   ├── gpu_Cd3D.dll      ← GPU加速版DEM
    │   ├── gpu_Cf3D.dll      ← GPU加速版FEM
    │   └── ...其他核心模块
    │
    ├── User Function DLLs（开源，可修改）
    │   ├── Ce3D.dll          ← 三维四面体本构（源码在Source/）
    │   ├── Cjoint3D.dll      ← 三维节理本构（源码在Source/）
    │   ├── SBoundary.dll     ← 静力边界条件（源码在Source/）
    │   ├── VBoundary.dll     ← 速度边界条件（源码在Source/）
    │   ├── InSitu.dll        ← 初始地应力（源码在Source/）
    │   ├── FGM.dll           ← 非均质材料（源码在Source/）
    │   ├── SKE.dll           ← 自定义动能（源码在Source/）
    │   ├── SRM.dll           ← 随机强度（源码在Source/）
    │   └── ...其他功能模块
    │
    └── User Solver DLL（开源，主要二次开发入口）
        └── User_solver.dll   ← CPUUSER接口（源码在User_solver/）
```

---

## 2. 两类二次开发接口

**来源：** `DeveloperGuide.md` §2

### 接口类型A：User Function DLL

- 路径：`02_MultiFracS/Source/MultiFracS-User Developement-cpu/`
- 编译：Visual Studio → 生成 `.dll` → 放到 MultiFracS.exe 同目录
- 特点：针对单一物理模型（本构、边界），参数由 inp 文件传入
- **函数签名不可更改（Core Engine 硬编码调用约定）**

### 接口类型B：User Solver DLL

- 路径：`02_MultiFracS/User_solver/`
- 关键文件：`Cpuuser.h`, `Cpuuser_abstract.h`, `solve_for_user.c`
- 特点：可访问全部 CPUCORE 数据，实现全局耦合逻辑
- InterfaceBond 全局耦合逻辑**必须在此实现**
- **CPUCORE 结构体字段不可修改**（闭源引擎维护）

---

## 3. SOA 数据布局（强制）

**来源：** `DataStructure.md` + `Cpucore.h` 字段命名规律

```c
// SOA（Structure of Arrays）— MultiFracS 全局采用
d1fnix[nfn]   // 所有节点的x坐标（连续内存）
d1fniy[nfn]   // 所有节点的y坐标（连续内存）
d1fniz[nfn]   // 所有节点的z坐标（连续内存）
// 不是 Node.x, Node.y, Node.z（AOS，缓存不友好）
```

**规则：**
- 新增用户数据结构必须遵循 SOA 布局
- 在 CPUUSER 中添加数组，不要添加单个结构体指针数组
- GPU 版本尤其依赖 SOA 的内存连续性

---

## 4. CPUCORE 与 CPUUSER

**来源：** `Cpucore.h`, `Cpuuser.h`, `Cpuuser_abstract.h`

### 4.1 CPUCORE（只读，不可修改）

```c
// 来自Cpucore.h（关键字段）
int nfn;            // FEM节点数
int ndn;            // DEM颗粒数
int nfelem;         // FEM单元数
int njelem;         // 节理单元数
Real dtm;           // 当前时间步（秒）
Real tm;            // 当前时刻（秒）
int nstep;          // 当前步数
Real* d1fnvx/vy/vz; // FEM节点速度（可读取，谨慎写入）
Real* d1fnfx/fy/fz; // FEM节点力（可写入，InterfaceBond反力在此）
Real* d1dnvx/vy/vz; // DEM颗粒速度（界面颗粒可写入）
int*  i1sphfnid;    // DEM颗粒→FEM节点映射（InterfaceBond关键）
```

### 4.2 CPUUSER（用户自定义，自由扩展）

```c
// Cpuuser.h 中定义用户自己的数据
typedef struct {
    // 新增字段示例（InterfaceBond）
    int    n_ibond;          // 界面Bond数量
    int*   i1ibond_fid;      // Bond的FEM侧颗粒ID
    int*   i1ibond_did;      // Bond的DEM侧颗粒ID
    Real*  d1ibond_Kn;       // 各Bond法向刚度
    Real*  d1ibond_Kt;       // 各Bond切向刚度
    Real*  d1ibond_dn;       // 各Bond法向位移（历史）
    Real*  d1ibond_dt;       // 各Bond切向位移（历史）
} CPUUSER_struct;
```

---

## 5. 工作流程（Gmsh → MultiFracS → ParaView）

**来源：** `CallGraph.md`

```
1. Gmsh 建模
   └── 模型要求：CCW（逆时针）建立几何面（否则法向量反向）
   └── Physical Group 必须命名（对应 inp 中的 *Elset/*Nset）
   └── 导出：.inp 格式（Abaqus兼容）

2. 编辑 inp 文件（手动添加计算设定）
   └── 关键顺序：*Material → *Joint → *Boundary → *CalulationType → *TimeStepSize → *Begin

3. MultiFracS.exe 计算
   └── 拖入 inp 文件即可启动
   └── 需要 virbox 加密锁（踩坑：USB锁必须插上才能运行）
   └── 输出：.vtk（位移/速度/应力）+ .csv（Monitor Point数据）

4. ParaView 后处理
   └── 加载 vtk 序列（不是单个文件）
   └── Calculator → Stress 分量
```

---

## 6. DLL 加载规则

**来源：** `Architecture.md` + 实际运行经验

```
MultiFracS.exe 同目录必须包含：
- Ce3D.dll（或gpu_Ce3D.dll）
- Cjoint3D.dll
- SBoundary.dll
- VBoundary.dll
- User_solver.dll（若使用User_solver功能）
- 其他 inp 中引用的模块 DLL
```

**规则：**
- DLL 文件名必须与 inp 中 `type=` 字段完全一致（区分大小写）
- 修改后的 DLL 必须替换到 exe 同目录，否则仍使用旧版本
- 编译后检查：DLL 依赖（Dependency Walker）确认无缺失

---

## 7. 不可修改的约束（来自闭源引擎）

**来源：** `DeveloperGuide.md` §4

| 约束项 | 原因 |
|--------|------|
| CPUCORE 结构体字段顺序 | 引擎按固定偏移量访问 |
| User Function 函数签名 | 引擎 dlopen 后按固定参数调用 |
| DLL 导出函数名 | 引擎通过 GetProcAddress 查找 |
| USERDLL 宏前缀 | Windows/Linux 双平台兼容 |
