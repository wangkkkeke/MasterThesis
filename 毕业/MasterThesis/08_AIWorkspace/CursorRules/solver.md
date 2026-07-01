# solver.md — 求解器开发规范

> 来源：`02_MultiFracS/inp数据格式文件5.8.md` + `User_solver/` 源码 + `DevelopmentHistory.md` 踩坑记录 + `TheoryGuide.md`

---

## 1. 时间步

### 1.1 Rayleigh 时间步（强制上限）

**来源：** `inp数据格式文件5.8.md` §TimeStepSize + `TheoryGuide.md`

```
*TimeStepSize
0.1
```

**规则：**
- inp中填写的是 Rayleigh 时间步的**倍率**（0~1.0），不是秒
- 实际 dt = 倍率 × dt_critical（由程序自动计算）
- dt_critical 公式：dt = α × (L_min / c_wave)，其中 c_wave = sqrt(E/ρ)
- **InterfaceBond 接口刚度 Kn 会降低临界时间步，必须重新验证稳定性**
- 推荐初始值：0.1 → 验证稳定后可调高，不建议超过0.5

### 1.2 单位一致性（血泪教训）

**来源：** `DevelopmentHistory.md` Bug002，应力误差1000倍

```
必须统一使用：
长度：m（米）
质量：kg
时间：s
应力：Pa = N/m²

禁止混用：
mm + MPa（会导致应力差1000倍）
m  + MPa（量纲不一致）
```

**验证方法：** 静力学算例（悬臂梁）先验证应力数量级是否与理论解匹配。

---

## 2. 边界条件

### 2.1 速度边界（优先于位移边界）

**来源：** `DevelopmentHistory.md` 成功方案1 + 失败方案1 + `VBoundary.h`

```c
// VBoundary 接口（不可改变签名）
USERDLL void VBoundary_velocity(
    int nstep, Real dtm, Real tm, int imat,
    Real d1fnix, Real d1fniy, Real d1fniz,
    Real* vx, Real* vy, Real* vz
);
```

**规则：**
- MultiFracS 显式动力学**禁止直接施加位移边界**（程序无此接口）
- 固定边界通过 `*FixBoundary` 关键字实现（等价 v=0）
- 动态加载通过 `*VForceBoundary` + `VBoundary.dll` 实现
- 静力学加载通过 `*SForceBoundary` + `SBoundary.dll` 施加，是**力**，不是位移
- **踩坑：** 尝试用 SBoundary 施加位移历史失败，原因是SBoundary接口传入的是坐标，返回的是力

### 2.2 SForceBoundary 正确用法

**来源：** `DevelopmentHistory.md` 成功方案2 + `SBoundary.c`

```c
USERDLL void SBoundary_force(
    int nstep, Real dtm, Real tm, int imat,
    Real x, Real y, Real z,            // 节点当前坐标（输入）
    Real* fx, Real* fy, Real* fz       // 返回节点力（输出，单位N）
);
```

正确用法：
```c
*fx = pressure * area_per_node;  // 力 = 压力 × 该节点负责面积
```

**踩坑：** area_per_node 必须按实际离散面积计算，不能平均分，否则边节点受力偏小。

### 2.3 初始地应力

**来源：** `InSitu.c` + `inp数据格式文件5.8.md`

```
*InitSituStress
σxx σyy σzz σxy σyz σxz（Pa，压为负）
```

规则：
- 地应力张量的符号约定：压应力为**负**
- 初始地应力必须与后续荷载方向保持约定一致

---

## 3. 材料参数

### 3.1 Ce3D（四面体有限元单元）参数顺序

**来源：** `inp数据格式文件5.8.md` §Ce3D材料 + `Ce3D.h`

```
*Material, name=rock, type=Ce3D
E  nu  rho  damp_n  damp_s
```

| 参数 | 含义 | 典型值（砂岩）|
|------|------|-------------|
| E    | 弹性模量（Pa）| 2e10 |
| nu   | 泊松比 | 0.25 |
| rho  | 密度（kg/m³）| 2500 |
| damp_n | 法向阻尼 | 0.1~0.7 |
| damp_s | 切向阻尼 | 0.1~0.7 |

**注意：** Ce3D 应力符号规定压为负（`DevelopmentHistory.md` Bug001）

### 3.2 Cjoint3D（节理单元）参数

**来源：** `Cjoint3D.h` + `inp数据格式文件5.8.md` §Joint

```
*Joint, name=joint1, type=Cjoint3D
pn  ps  co  fric  ft  gi  gii
```

| 参数 | 含义 |
|------|------|
| pn   | 法向刚度（Pa/m）|
| ps   | 切向刚度（Pa/m）|
| co   | 粘聚力（Pa）|
| fric | 内摩擦角（rad）|
| ft   | 抗拉强度（Pa）|
| gi   | I型断裂能（J/m²）|
| gii  | II型断裂能（J/m²）|

### 3.3 IbkFlag 的正确语义

**来源：** `DevelopmentHistory.md` 失败方案4 + `inp数据格式文件5.8.md`

```
IbkFlag = 0  → 节理完整（intact）
IbkFlag = 1  → 拉伸断裂（tensile failure）
IbkFlag ≥ 2  → 剪切断裂（shear failure）
```

**错误用法（已记录）：** 把 IbkFlag 当成激活/禁用 InterfaceBond 的开关 —— 错误，该参数是断裂状态输出，由程序内部更新，不要在 User_solver 中手动设置。

---

## 4. 显式动力学时间步循环

### 4.1 User_solver 调用时序

**来源：** `DeveloperGuide.md` + `User_solve.c`

```
每个时间步调用顺序（不可改变）：
1. User_preprocess()       ← 前处理（初始化一次）
2. [主循环 nstep=1..N]
   2.1 Core Engine 更新节点加速度/速度/位移
   2.2 User_solve()         ← 用户自定义力、本构
   2.3 Core Engine 接触检测
   2.4 User_postprocess()  ← 后处理（输出、统计）
3. User_postprocess()      ← 最终输出
```

**规则：** User_solve 内不得修改时间步 dtm，不得改变节点编号数组 i1enid。

### 4.2 Monitor Point 位置

**来源：** `DevelopmentHistory.md` 踩坑2 + `inp数据格式文件5.8.md`

```
*MonitorPoint
x y z   ← 必须落在网格节点上，否则输出为零
```

**踩坑：** Monitor Point 如果放在几何中心而非节点，输出恒为零，模型看似无响应。

---

## 5. 输出控制

**来源：** `inp数据格式文件5.8.md` §OutResultFileFrequency

```
*OutResultFileFrequency
每N步输出一次
```

建议值：调试期间10~50步，正式计算1000步。
频率过低会导致大量VTK文件，影响磁盘和ParaView性能。

---

## 6. InterfaceBond 耦合开发规范（关键）

**来源：** `DeveloperGuide.md` + `DataStructure.md` + `TheoryGuide.md`

### 6.1 FEM-DEM 界面识别

```c
// 通过 i1sphfnid 识别：某颗粒绑定到哪个FEM节点
// 来源：Cpucore.h
int* i1sphfnid;  // [ndn] 每个DEM颗粒对应的FEM节点ID（-1表示纯DEM）
```

### 6.2 代理颗粒速度更新（必须在 User_solve 开头执行）

```c
// 每步开始时，将FEM节点速度映射到界面DEM颗粒
for (int id = 0; id < ndn; id++) {
    if (i1sphfnid[id] >= 0) {
        int fnid = i1sphfnid[id];
        d1dnvx[id] = d1fnvx[fnid];  // 形函数插值（若已绑定节点则直接赋值）
        d1dnvy[id] = d1fnvy[fnid];
        d1dnvz[id] = d1fnvz[fnid];
    }
}
```

**注意：** 此处是否为形函数插值还是直接赋值，取决于源码是否建立了真实Particle对象（待导师确认，见 KnowledgeSummary.md 待确认项）。

### 6.3 InterfaceBond 力反馈必须作用于两侧

```c
// 力平衡：FEM节点 + DEM颗粒 等量反向
d1fnfx[fnid] += fx_bond;   // FEM节点受力
d1dnfx[did]  -= fx_bond;   // DEM颗粒受反力
```
