# TheoryGuide.md
# 理论知识索引手册

**版本：** v1.0（2026-06-30）
**用途：** 论文写作与开发过程中的理论快速查阅索引
**覆盖主题：** FEM · DEM · InterfaceBond · 显式动力学 · Ghost Force · SOA
**对应章节：** 主要服务于 Ch2（理论基础）和 Ch3（本文方法）

---

## 目录

1. [FEM — 有限元法基本框架](#1-fem)
2. [DEM — 离散元法基本框架](#2-dem)
3. [InterfaceBond — 界面键力学模型](#3-interfacebond)
4. [显式动力学 — 时间积分与稳定性](#4-显式动力学)
5. [Ghost Force — 界面力残差机制](#5-ghost-force)
6. [SOA — 数据结构规范](#6-soa)
7. [知识索引速查表](#7-知识索引速查表)

---

## 1. FEM

### 1.1 基本方程

**更新拉格朗日格式下的运动方程：**

$$M\ddot{u} + C\dot{u} = F_{ext} - F_{int}$$

- $M$：质量矩阵（集总质量，对角阵）
- $C$：阻尼矩阵
- $F_{ext}$：外荷载向量
- $F_{int}$：内力向量（由单元应力积分得到）

**对应论文位置：** Ch2.1.1，Ch3.3.1（式3-5）

---

### 1.2 单元类型（MultiFracS 约定）

| 单元类型 | 代码 | 说明 |
|---|---|---|
| 4节点可变形四面体 | IeType=11 (C3D4) | 本文主用单元 |
| 4节点刚体四面体 | IeType=12 | 刚性区域 |
| 10节点可变形四面体 | IeType=13 | 高阶单元 |

**统一拆分原则：** 三棱柱、六面体、金字塔单元均拆分为多个四面体处理。所有单元计算统一转化为四面体。

---

### 1.3 应变与应力计算流程

```
初始节点坐标 + 当前节点坐标
        ↓
    变形梯度 F
        ↓
    应变矩阵 B（Green-Lagrange 或工程应变）
        ↓
    本构方程（线弹性：σ = D·ε）
        ↓
    单元应力 σ
        ↓
    节点内力 F_int = ∫ B^T · σ dV
```

---

### 1.4 质量集总（Mass-lumping）

**作用：** 使质量矩阵对角化，从而可显式求解，无需矩阵求逆。

**常用方法：** 行求和法（Row-sum）——将一行的非对角项全部加到对角项上。

**影响：** 临界时间步、高频振荡抑制能力。

**对应论文位置：** Ch2.1.3

---

### 1.5 临界时间步（FEM侧）

$$\Delta t_{c}^{FEM} = \frac{h_{min}}{c_p}$$

- $h_{min}$：最小单元特征尺寸
- $c_p$：P波速度，$c_p = \sqrt{E(1-\nu)/[\rho(1+\nu)(1-2\nu)]}$

简化（一维线弹性）：$c_p \approx \sqrt{E/\rho}$

**对应论文位置：** Ch2.1.3，Ch3.3.2（式3-6）

---

### 1.6 节理单元（Joint Element）

MultiFracS中特有概念：在四面体单元之间插入节理单元（零厚度），通过内聚力本构描述裂缝扩展。

**节理单元参数（来自INP格式）：**
- `c`：粘聚力（必须 > 0）
- `phi`：内摩擦角
- `ft`：抗拉强度
- `GfI`、`GfII`：I型/II型断裂能
- `IbkFlag`：节理单元断裂状态标记（0=未断，1=已断）

**注意：** 这是传统FDEM方法（节理单元法）。本论文的共生耦合方法不使用节理单元，而是使用 InterfaceBond。

---

## 2. DEM

### 2.1 颗粒运动方程

**平动：**
$$m\ddot{x} = F_{contact} + F_{bond} + F_{body}$$

**转动：**
$$I\ddot{\theta} = M_{contact} + M_{bond}$$

- $m$：颗粒质量
- $I$：转动惯量
- $F_{contact}$：接触力
- $F_{bond}$：键力
- $F_{body}$：体力（重力等）

---

### 2.2 键粒模型（BPM，Bonded Particle Model）

**法向力：**
$$F_n = K_n \cdot \delta_n$$

- $K_n$：法向刚度
- $\delta_n$：法向相对位移（正=压缩，负=拉伸）

**切向力（增量更新）：**
$$\Delta F_s = K_s \cdot \Delta \delta_s$$

**拉伸断裂准则：**
$$\delta_n > \delta_{n,b} \Rightarrow \text{键断裂，法向力归零}$$

**剪切断裂（Mohr-Coulomb）：**
$$|F_s| > F_{s0} + \mu_p \cdot |F_n| \Rightarrow \text{键断裂，转为滑动摩擦}$$

**对应论文位置：** Ch2.2.2

---

### 2.3 颗粒临界时间步（Rayleigh 时间步）

$$T_{min} = 2\pi\sqrt{\frac{m}{K_n}}$$

**稳定条件：**

$$\Delta t_{DEM} \leq 0.005 \cdot T_{min}$$（取0.5%）

**对应论文位置：** Ch2.2.3，Ch3.3.2（式3-6）

---

### 2.4 宏微观参数转换（粗粒化）

线弹性模型中，颗粒微观参数可由宏观参数推导：

$$K_n \sim f(E, \nu, r)$$
$$K_s \sim f(E, \nu, r)$$
$$F_{s0} \sim f(c, \phi)$$
$$\mu_p \sim \tan(\phi)$$

（具体公式见技术建议书 §2.1.4）

---

### 2.5 接触检测

MultiFracS采用**矩阵离散元**并行接触检测：
- 建立邻居矩阵 $N$（每行记录一个颗粒的邻居）
- 虚单元（m+1号）填充短行，保持矩阵规整
- 每步更新接触布尔矩阵

**对应论文位置：** Ch5.4（效能评价中的接触检索规模统计）

---

## 3. InterfaceBond

### 3.1 完整机制链路

```
FEM节点速度 v_i
      ↓  形函数插值 v = Σ Ni·vi
FEM侧边界代理颗粒（运动学状态由FEM控制）
      ↓  InterfaceBond（Kn/Kt弹簧键）
DEM侧边界颗粒（自由运动）
      ↓  DEM颗粒系统
```

**关键定性结论（来自导师 + GPT分析）：**
- "本质还是颗粒之间连接，不是节点和颗粒连接"
- FEM侧代理颗粒可能是真实的 `Particle` 对象（待源码确认）
- 技术建议书描述"虚拟DEM颗粒"与开题报告描述"InterfaceBond弹簧键"是同一机制的不同层级

---

### 3.2 速度插值（式3-2）

$$v_{proxy} = \sum_{i=1}^{n_{node}} N_i(\xi) \cdot v_i^{FEM}$$

- $N_i$：有限元形函数（四面体线性形函数，4个节点）
- $v_i^{FEM}$：有限元节点速度
- $v_{proxy}$：代理颗粒速度（用于后续相对位移计算）

**说明：** 代理颗粒没有独立的积分自由度，每时间步实时插值。

---

### 3.3 接触力增量更新（式3-1）

$$\Delta F = K \cdot \Delta \delta$$

展开为法向/切向：

$$\Delta F_n = K_n \cdot \Delta \delta_n$$
$$\Delta F_s = K_s \cdot \Delta \delta_s$$

**相对位移增量：**
$$\Delta \delta = (v_{DEM} - v_{proxy}) \cdot \Delta t$$

**累积接触力：**
$$F^{n+1} = F^n + \Delta F$$

---

### 3.4 断裂准则

**法向拉伸断裂准则（式3-3）：**
$$\frac{F_n}{A_{eq}} \geq \sigma_t \Rightarrow \text{键断裂}$$

断裂后：$F_n = 0$，$F_s = 0$

**剪切断裂准则——Mohr-Coulomb（式3-4）：**
$$\frac{|F_s|}{A_{eq}} \geq c + \frac{F_n}{A_{eq}} \cdot \tan\phi \Rightarrow \text{键断裂}$$

断裂后：$F_s$ 转为残余摩擦滑动修正，$\sigma_t = 0$，$c = 0$

- $A_{eq}$：等效截面积（待源码确认具体计算方式，见 Q6）
- $\sigma_t$：抗拉强度
- $c$：粘聚力
- $\phi$：内摩擦角

---

### 3.5 键参数配置原则

| 参数 | 说明 | 配置原则 |
|---|---|---|
| $K_n$ | 法向刚度 | 结合FEM网格与DEM颗粒特征尺寸，预试算标定 |
| $K_s$ | 切向刚度 | 通常取 $K_s = \beta \cdot K_n$，$\beta \in [0.2, 1.0]$ |
| $\sigma_t$ | 抗拉强度 | 对应材料抗拉强度 |
| $c$ | 粘聚力 | 对应材料粘聚力 |
| $\phi$ | 内摩擦角 | 对应材料内摩擦角 |

**配置原则：** 避免界面过软（力传递失真）或过硬（引起数值振荡）。需通过预试算调整。

---

### 3.6 待确认问题

| 编号 | 问题 | 当前状态 | 解决途径 |
|---|---|---|---|
| Q6 | 等效截面积 $A_{eq}$ 计算方式 | 未确认 | 阅读InterfaceBond源码 |
| Q_NEW_1残留 | 代理颗粒是否存在真实Particle对象 | 未确认 | 搜索 BoundaryParticle / VirtualParticle |

---

## 4. 显式动力学

### 4.1 中心差分法（Central Difference Method）

**核心格式（半步速度预测-校正）：**

$$a_n = M^{-1}(F_{ext}^n - F_{int}^n)$$

$$v_{n+1/2} = v_{n-1/2} + a_n \cdot \Delta t$$

$$u_{n+1} = u_n + v_{n+1/2} \cdot \Delta t$$

**特点：**
- 条件稳定（必须满足 $\Delta t \leq \Delta t_c$）
- 无需矩阵求逆（质量矩阵集总后为对角阵）
- 适合强非线性、大变形、接触碰撞

**对应论文位置：** Ch2.1.2，Ch3.3.1

---

### 4.2 Velocity Verlet（DEM侧常用）

**分步-校正格式：**

$$v_{n+1/2} = v_n + \frac{a_n}{2} \cdot \Delta t$$

$$u_{n+1} = u_n + v_{n+1/2} \cdot \Delta t$$

$$a_{n+1} = F_{n+1}/m$$

$$v_{n+1} = v_{n+1/2} + \frac{a_{n+1}}{2} \cdot \Delta t$$

**精度：** 二阶精度，良好稳定性。

---

### 4.3 统一时间步选取策略（式3-6）

共生耦合系统的全局时间步须同时满足两个子域的稳定条件：

$$\Delta t \leq \min(\Delta t_c^{FEM}, \Delta t_c^{DEM})$$

$$\Delta t_c^{FEM} = \alpha \cdot \frac{h_{min}^{FEM}}{c_p^{FEM}}$$

$$\Delta t_c^{DEM} = 0.005 \cdot 2\pi\sqrt{\frac{m_{min}}{K_n^{max}}}$$

- $\alpha$：安全系数（通常取0.5~0.9）
- $h_{min}^{FEM}$：FEM最小单元特征尺寸
- $c_p^{FEM}$：P波速度

**注意：** FEM子域与DEM子域的 $\Delta t_c$ 可能相差数倍甚至数量级，这是Ghost Force和不稳定性的重要来源。

**对应论文位置：** Ch3.3.2

---

### 4.4 临界时间步失配问题

当 $\Delta t_c^{FEM} \gg \Delta t_c^{DEM}$ 时（或反之），系统必须取较小值作为全局步长，导致计算效率降低。

**异步长并行（参照）：** 李佟2023 [文献A30] 提出FEM与DEM采用不同时间步异步推进，以缓解失配问题。本课题不将其作为核心贡献，仅作背景参照。

**对应论文位置：** Ch2.4.1，Ch3.3.2

---

## 5. Ghost Force

### 5.1 定义

**Ghost Force（界面力残差）：** 在FEM-DEM耦合界面处，由于两侧子域在尺度、刚度、数值格式上的不匹配，导致界面处产生非物理的残差力，表现为：
- 界面力偏离物理值
- 系统能量非物理增大或耗散

### 5.2 产生机制

```
FEM子域（宏观，网格较粗，刚度高）
         ↕ InterfaceBond界面
DEM子域（细观，颗粒较小，刚度不同）
```

1. **刚度失配：** FEM有限元刚度矩阵与DEM颗粒刚度量级不同 → 界面处产生非平衡力
2. **尺度失配：** FEM节点间距 ≠ DEM颗粒间距 → 形函数插值引入近似误差
3. **时间步失配：** 中心差分在非均匀介质中传播误差在界面处累积

**参照：** Bürchner 2026 [B08]（特征值稳定化），李佟 2023 [A30]（异步长并行）

**对应论文位置：** Ch2.4.2，Ch3.3.3，Ch4.3.4

---

### 5.3 监测指标体系

论文中须监测以下指标以评估Ghost Force影响：

| 指标 | 计算方式 | 预期行为（正常） |
|---|---|---|
| 界面力残差 $R_{if}$ | 界面两侧合力之差 | 接近0 |
| 系统总能量 $E_{total}$ | $E_k + E_p + E_d$ | 应守恒或单调衰减 |
| 各子域临界时间步 | 实时记录 FEM/DEM 的 $\Delta t_c$ | 无突变 |
| 应力波传播特征 | 界面两侧应力时程 | 波形应连续传递 |

**对应论文位置：** Ch3.3.3，Ch4.3.4，Ch4.3.5

---

### 5.4 控制策略

| 策略 | 原理 | 本课题角色 |
|---|---|---|
| 合理的 $K_n$、$K_s$ 配置 | 避免界面刚度突变过大 | **核心手段** |
| 界面处适当的网格过渡 | 减少尺度突变 | 建模时注意 |
| 粗粒化映射 | 改善颗粒-连续体接触力振荡 | 背景参照（程宏旸2023 [A31]） |
| 异步长并行 | 各子域独立时间步 | 背景参照（李佟2023 [A30]） |

---

## 6. SOA

### 6.1 概念

**SOA（Structure of Arrays，数组的结构体）：** 与 AOS（Array of Structures，结构体的数组）相对。

| 布局 | 代码示例 | 内存特征 |
|---|---|---|
| **AOS** | `struct Particle{double x,y,z;} p[N]` | 单个颗粒属性连续，跨颗粒不连续 |
| **SOA** | `double x[N], y[N], z[N]` | 同一属性在内存中连续，利于SIMD/GPU |

---

### 6.2 MultiFracS 中的 SOA 规范

MultiFracS 采用 SOA 数据结构，原因：
- GPU并行中，每个线程处理一个颗粒，访问 `x[i]`, `y[i]` 时内存连续（coalesced memory access）
- CPU SIMD（SSE/AVX）指令集也能高效利用 SOA

**实际影响（开发时）：**
- 新增字段须在对应数组中增加：如新增 `vx_interface[N]`，而非在颗粒结构体中加字段
- 不能用 `p[i].x = ...`，应用 `x[i] = ...`

---

### 6.3 C语言 SOA 开发规范

来源：`00_Project/C语言编程规范.txt`

**命名规范：**
- 局部变量：小写 `count`
- 全局变量：`g_` 前缀，如 `g_totalAmount`
- 指针变量：`p` 前缀，如 `pName`
- 常量：全大写 `MAX_SIZE`
- 函数：驼峰+动词，如 `calculateTotal()`
- 结构体：大写开头驼峰，如 `StudentInfo`

**函数规范：**
- 函数体不超过50行，参数不超过5个
- 函数名用动词+名词，如 `computeInterfaceForce()`

**注释要求（函数头）：**
```c
/*
 * 函数功能：计算InterfaceBond界面力
 * 参数：nodeVel - FEM节点速度数组
 *      demVel  - DEM颗粒速度
 * 返回值：界面力向量
 */
```

---

### 6.4 SOA 在 InterfaceBond 中的预期体现

根据SOA规范，InterfaceBond 相关数组可能形如：

```c
// FEM侧代理颗粒（若存在真实对象）
double proxy_x[N_bond];   // 代理颗粒位置
double proxy_y[N_bond];
double proxy_z[N_bond];
double proxy_vx[N_bond];  // 代理颗粒速度（由FEM节点插值）
double proxy_vy[N_bond];
double proxy_vz[N_bond];

// InterfaceBond 键属性
double bond_Fn[N_bond];   // 当前法向力
double bond_Fs[N_bond];   // 当前切向力
int    bond_broken[N_bond]; // 0=未断, 1=已断
int    bond_femElemId[N_bond]; // 对应FEM单元ID
int    bond_demPtclId[N_bond]; // 对应DEM颗粒ID
```

**注意：** 以上为推测结构，实际结构需阅读源码确认。

---

## 7. 知识索引速查表

### 7.1 公式索引

| 公式编号 | 描述 | 所属主题 | 论文位置 |
|---|---|---|---|
| 式2-1 | FEM运动方程 $M\ddot{u}+C\dot{u}=F$ | FEM | Ch2.1.1 |
| 式2-2 | 中心差分时间积分格式 | 显式动力学 | Ch2.1.2 |
| 式2-3 | FEM临界时间步 $\Delta t_c = h/c_p$ | 显式动力学 | Ch2.1.3 |
| 式2-4 | DEM颗粒运动方程 | DEM | Ch2.2.1 |
| 式2-5 | BPM键力计算（法向/切向） | DEM | Ch2.2.2 |
| 式2-6 | DEM临界时间步（Rayleigh） | DEM | Ch2.2.3 |
| 式3-1 | InterfaceBond接触力增量更新 $\Delta F=K\Delta\delta$ | InterfaceBond | Ch3.2.2 |
| 式3-2 | FEM侧速度插值 $v=\Sigma N_i v_i$ | InterfaceBond | Ch3.2.1 |
| 式3-3 | 法向拉伸断裂准则 $F_n/A\geq\sigma_t$ | InterfaceBond | Ch3.2.3 |
| 式3-4 | Mohr-Coulomb剪切断裂准则 | InterfaceBond | Ch3.2.4 |
| 式3-5 | 共生耦合系统运动方程（含界面键力） | 显式动力学 | Ch3.3.1 |
| 式3-6 | 统一时间步选取策略 | 显式动力学 | Ch3.3.2 |

---

### 7.2 论文章节 → 理论主题索引

| 章节 | 涉及理论主题 |
|---|---|
| Ch2.1 | FEM基本框架、更新拉格朗日、中心差分、质量集总 |
| Ch2.2 | DEM颗粒方程、BPM键模型、Rayleigh时间步 |
| Ch2.3 | 共生耦合方法综述（桥接域法、Arlequin法、InterfaceBond思想来源） |
| Ch2.4 | Ghost Force、临界时间步失配、能量守恒监测 |
| Ch3.2 | InterfaceBond完整力学模型（本文推导） |
| Ch3.3 | 显式动力学求解框架、统一时间步、稳定性监测指标 |
| Ch3.4 | 参数标定、DEM破裂区范围原则 |
| Ch3.5 | MultiFracS SOA数据结构、模块集成 |
| Ch4.3 | Ghost Force量级评估、系统能量演化 |
| Ch5.4 | 接触检索规模对比（SOA矩阵DEM的接触对数统计） |

---

### 7.3 理论主题 → 关键文献索引

| 理论主题 | 关键文献 | 备注 |
|---|---|---|
| FEM更新拉格朗日/FDEM | Lei 2023 [A10] | Ch2参考基准 |
| FEM显式断裂 | Scheidt 2026 [B12]，质量集总 | 稳定性参照 |
| 共生耦合（桥接域） | Voisin-Leprince 2023/2024 [A22/A25] | Ch2.3对比方法 |
| InterfaceBond | 李晓光 2023 [A27] | Ch3.2核心参考 |
| Ghost Force/异步长并行 | 李佟 2023 [A30] | 稳定性背景 |
| 粗粒化映射 | 程宏旸 2023 [A31] | 稳定性背景 |
| 广义特征值稳定化 | Bürchner 2026 [B08] | 显式稳定性背景 |
| 单轴拉伸杆（FDEM验证） | 徐浩然 2024 [B10] | 算例2对标 |
| 巴西劈裂 | Zhang 2026 [B13]，Heng 2025 [B15] | 算例3对标 |
| 模式I裂纹板 | Zhou 2022 [A17]，Wang 2026 [B11] | 算例4对标 |

---

### 7.4 开发时理论对应速查

| 开发任务 | 对应理论 | 参考公式/章节 |
|---|---|---|
| InterfaceBond键力计算函数 | §3，式3-1/3-2 | Ch3.2 |
| 键断裂判断函数 | §3.4，式3-3/3-4 | Ch3.2.3/3.2.4 |
| FEM侧代理颗粒速度赋值 | §3.2，式3-2 | Ch3.2.1 |
| 时间步计算 | §4.3，式3-6 | Ch3.3.2 |
| Ghost Force监测输出 | §5.3 | Ch3.3.3 |
| 接触检索规模统计 | §2.5（DEM矩阵法） | Ch5.4 |
| SOA数组扩展 | §6.3/6.4 | Ch3.5 |

---

## 附录：待更新事项

| 编号 | 问题 | 触发更新条件 |
|---|---|---|
| T1 | InterfaceBond代理颗粒数据结构（6.4节为推测） | 阅读源码后确认/修正 |
| T2 | $A_{eq}$ 等效截面积计算方式 | 阅读源码后补充 |
| T3 | 悬臂梁算例具体几何（237单元的网格划分方式） | 建模后补充 |
| T4 | 单轴拉伸杆脉冲加载参数 | 算例设计确认后补充 |
| T5 | 各子域实测临界时间步比值 | 预试算后补充 |

---

*生成时间：2026-06-30 | 基于：开题报告终版docx、技术建议书附件4、论文总体框架v1、KnowledgeSummary v1.2、MultiFracS INP格式文档5.8*
