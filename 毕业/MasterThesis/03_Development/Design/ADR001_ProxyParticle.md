# ADR001 — Proxy Particle 架构决策

**类型：** Architecture Decision Record（架构决策记录）
**状态：** Working Assumption — 源码阅读已提供间接证据，倾向方案A（2026-06-30）
**创建时间：** 2026-06-30
**预计确认时间：** ~2026-07-02（向导师确认最终方案）

---

## 背景

InterfaceBond 机制中，FEM 区域与 DEM 颗粒之间存在一个"中间对象"，其运动学状态由 FEM 节点通过形函数插值得到。该对象在不同文档中描述不一致：

- 技术建议书：称为"虚拟 DEM 颗粒"，暗示为真实 Particle 对象
- 开题报告：称为"FEM 侧颗粒"，速度由节点插值
- 导师答辩描述："本质还是颗粒之间连接"

目前有两种可能的实现方式：

| 方案 | 描述 |
|------|------|
| 方案A：Proxy Point | Proxy 不是真实 Particle；每步由 FEM 节点插值临时构造，仅用于力计算 |
| 方案B：Virtual Particle | Proxy 是真实 `Particle` 对象，有独立内存，速度来自插值而非积分 |

---

## 当前工作假设（Working Assumption）

**采用方案A：Proxy Point**

具体假设：
- Proxy **不属于** DEM Particle 数组，不占 `CPUCORE.sphxyz[]` 等粒子数组空间
- Proxy **不参与** DEM 时间积分（无独立 mass、vel、acc）
- Proxy **不需要** 粒子索引（无 sphID），只需要位置和速度的临时值
- 每个 InterfaceBond 在力计算时，**实时插值**得到 FEM 侧位置/速度
- InterfaceBond 数据结构仅需存储：FEM 单元编号 + 形函数系数 + DEM 颗粒编号

---

## 采用此假设的理由

1. 实现更轻量，不需要扩展 CPUCORE 颗粒数组
2. 与"函数式耦合"设计更一致，易于插拔
3. 若假设错误（实际是方案B），改造成本可控：只需增加 Particle 分配和初始化步骤，力计算逻辑基本不变

---

## 受此假设影响的设计决策

| 设计项 | 当前方案（基于假设A） | 若改为方案B |
|--------|-------------------|-----------|
| InterfaceBond 结构体 | 存 `elem_id` + `N[4]` + `dem_id` | 额外存 `proxy_particle_id` |
| 力计算入口 | 每步插值 → 计算 → 传力 | 先更新 proxy vel → 同上 |
| 内存分配 | 仅 InterfaceBond 数组 | 额外分配 proxy Particle 数组 |
| 初始化流程 | `User_preprocess` 建 Bond 表 | 同上 + 额外初始化 proxy 颗粒 |

---

## 可替换设计（Replaceable Design）原则

在方案A假设下编写代码时，所有插值逻辑集中在一个函数：

```c
/* 唯一需要替换的函数 — 若改为方案B，只改此函数内部即可 */
void get_proxy_kinematics(
    int elem_id,        /* FEM 单元编号 */
    Real N[4],          /* 形函数系数 */
    CPUCORE *core,      /* 全局数据 */
    Real *pos_out,      /* 输出：位置 xyz */
    Real *vel_out       /* 输出：速度 xyz */
);
```

**红线：** 以下代码在导师确认前不写：
- 扩展 `CPUCORE` 颗粒数组的代码
- 分配 proxy Particle 内存的代码
- 将 proxy 加入 DEM 时间积分循环的代码

---

## 源码阅读关键发现（2026-06-30）

读完 `User_solver/` 全部源文件后，发现以下事实：

### 1. InterfaceBond 实现度为 0%
- `User_solve.c`：`user_solver()` 和 `user_to_MultiFracS()` 全为空函数体（注释掉的 SPH 示例代码）
- `User_preprocess.c`：只有框架，无任何数据初始化
- `CPUUSER`：只有 4 个时间管理字段 + `snum`（三角面数），无任何 InterfaceBond 字段
- User Function DLL 源码（Source 目录）中无 `IbkFlag`、`ibond`、`InterfaceBond` 任何关键词

**结论：InterfaceBond 全部从零实现，无现有代码可复用。**

### 2. CPUCORE 中已有 SPH-FEM 耦合框架 — 这是关键！

`Cpucore.h` 已存在：
```c
int nsph;            // SPH 单元个数
int* i1sphfnid;      // [nsph*(ndim+1)+i] SPH 实体单元的有限元节点编号
Real* d1sphr;        // [nsph] 粒子半径
Real* d1sphdx;       // [nsph] 粒子初始间距
// ... 其他 SPH 属性数组
```

SPH 元素在 CPUCORE 中：
- **没有独立的 xyz 坐标数组**（无 `d1sphx/y/z`）
- 只有到 FEM 节点的映射 `i1sphfnid`
- 位置需要从 FEM 节点坐标通过形函数插值得到

**这直接支持方案A（Proxy Point）：SPH 元素本身就是嵌入 FEM 单元的代理点，没有独立自由度，位置由 FEM 节点决定。**

### 3. 可用数据汇总

| 数据 | CPUCORE 字段 | 说明 |
|------|------------|------|
| FEM 节点坐标 | `d1fnix/y/z` | FEM 节点当前位置 |
| FEM 节点数 | `nfn` | |
| SPH 单元数 | `nsph` | 即代理点数量 |
| SPH→FEM 节点映射 | `i1sphfnid` | 每个 SPH 对应 ndim+1 个 FEM 节点 |
| 离散节点（DEM）坐标 | `d1dncx/y/z` | DEM 颗粒当前位置 |
| 离散节点速度 | `d1dnvx/y/z` | DEM 颗粒速度 |
| 离散节点质量 | `d1dnmass` | |
| 离散节点力 | `d1dnfx/y/z` | 向此处写入 InterfaceBond 力 |
| 时间步 | `dtm` | 力学时间步 |

### 4. 调用钩子

| 函数 | 调用时机 | InterfaceBond 用途 |
|------|---------|------------------|
| `preprocess_cpuuser()` | 计算开始前，读 inp 后 | 建立 Bond 表，分配 CPUUSER 内存 |
| `user_solver()` | 每时间步，DEM 接触力之后 | 计算 InterfaceBond 力 |
| `user_to_MultiFracS()` | 每时间步，`user_solver` 之后 | 将 Bond 力分配到 FEM 节点（`d1dnfx`） |
| `Output_vtk_user()` | 每输出步 | 可输出 Bond 状态（可选） |

---

## 待确认问题

向导师确认的具体问题：

> "关于 InterfaceBond 实现，想确认一下：FEM 侧对应的代理对象，在程序里是否真的创建了 Particle 结构体，并分配了内存？还是每步由 FEM 节点速度插值临时得到，不存储为独立的粒子对象？"

---

## 确认后的处置流程

1. **若确认方案A（Proxy Point）：** 将本 ADR 状态改为 `Confirmed - Option A`，继续当前设计
2. **若确认方案B（Virtual Particle）：** 将状态改为 `Confirmed - Option B`，更新以下文档：
   - `ADR001_ProxyParticle.md`（本文档）
   - `03_Development/Design/Architecture.md`
   - `02_MultiFracS/DataStructure.md`
   - `05_Research/FormulaIndex.md`（F02 条目）
   - 受影响的 Issue 文档（Issue001、Issue002、Issue006）
   - `08_AIWorkspace/CursorRules/solver.md`

---

*状态追踪：此 ADR 在导师确认前保持 Working Assumption 状态。任何触碰本文档"红线"内容的设计请先停下，告知用户。*
