# Algorithm Specification v1.0

**Release:** Prototype_v0.1  
**Status:** Verified Algorithm Definition  
**Date:** 2026-07-13  

本文档是**算法定义**，不是软件设计文档。  
不描述代码、目录或 API。  
它回答：这个算法叫什么、吃什么、吐什么、怎么走、假设什么、边界在哪、已证明什么、尚未证明什么。

---

## 1. Algorithm Name

**Working name:**

Global Sphere Embedding based Symbiotic FEM–DEM Coupling Algorithm

**中文工作名：**

基于全域布球的共生有限元–离散元耦合算法

（正式命名可在导师讨论后修订；本版名称用于冻结语义，不绑定最终论文标题。）

**One-line definition:**

在同一连续构件上全域生成 Sphere，由 Host Tet 继承区域并赋予运动学角色（Proxy / Free），以统一 Bond 传递相互作用，并将 Proxy 反力映射回 Tet 节点，从而实现无传统界面单元的显式共生耦合。

---

## 2. Input

算法输入为连续体数值模型与离散化参数，至少包括：

| Input | Meaning |
|-------|---------|
| Tet Mesh | 节点与四面体单元离散 |
| Region Mask | 每个 Tet 的区域标记（如 FEM / DEM 数值分区） |
| Sphere Radius | 全域布球半径（及由此导出的布球间距） |
| Bond Parameters | 键参数（如法向刚度 \(K_n\)；第一版可不含断裂） |
| Time Parameters | 时间步长、终止时间（进入显式积分时） |
| Boundary / Driver Data | 节点驱动或外载定义（验证阶段可为 Driver FEM） |

说明：

- FEM|DEM|FEM 等分区是**数值区域**，不是材料界面。  
- Region Mask 附着于 Tet；Sphere 的角色不由人工名单指定。

---

## 3. Output

算法输出为共生耦合所需的离散对象与拓扑，至少包括：

| Output | Meaning |
|--------|---------|
| Sphere Set | 全域 Sphere 集合（位置、质量、半径等） |
| Host Tet Mapping | 每个落入 Tet 的 Sphere 对应的 Host Tet 及形函数 \(N_1\sim N_4\) |
| Motion Mode | 每个 Sphere 的运动学模式（Proxy / Free 等） |
| Bond Graph | Sphere–Sphere 键集合及活性标记 |
| Coupling Topology | 由 Proxy、Free 与 Bond 形成的共生拓扑（含界面 Proxy–Free 键） |
| Nodal Reaction Field | 由 Mapping 得到的 Tet 节点力（进入连续体侧） |
| Optional Fields | 位移、速度、键力等时程/场量（用于验证与可视化） |

---

## 4. Algorithm Flow

流程为算法步骤，不是程序调用序的实现细节。

```
Input
  │
  ▼
Global Sphere Generation
  │
  ▼
Host Tet Identification
  │
  ▼
Region Inheritance
  │
  ▼
Motion Mode Assignment
  │
  ▼
Bond Construction
  │
  ▼
Explicit Time Integration
  │     （FEM/Driver 更新节点 → Proxy 插值 → Bond 力 → Free 积分）
  ▼
Reaction Mapping
  │
  ▼
Output
```

**Construction phase（建模）：** Input → … → Bond Construction → Coupling Topology  

**Evolution phase（演化）：** Explicit Time Integration ⇄ Reaction Mapping（逐步推进）

核心不变量：从 Mesh 出发自动得到共生拓扑，无需人工指定“谁是 Proxy、谁是 Free”。

---

## 5. Mathematical Assumptions

本版算法建立在以下假设之上：

1. **Proxy 不独立积分**  
   Proxy 无独立连续体自由度；其位置与速度由 Host Tet 形函数插值得到。

2. **Host Tet 在构造期唯一确定**  
   每个需要绑定的 Sphere 在点定位意义下归属一个 Host Tet；形函数 \(N_i\) 在构造期计算并保存，时间推进中不重新搜索（本版假设）。

3. **Motion Mode 继承 Tet Region**  
   运动学角色由  
   `Host Tet → Region → Motion Mode`  
   继承得到；禁止仅用球心坐标的临时规则作为算法定义的一部分。无 Host Tet 的 Sphere（如无 Tet 覆盖的 DEM 数值区）视为 Free。

4. **Bond 为 Sphere 间的唯一相互作用通道（本版）**  
   第一版不含接触、摩擦本构升级、断裂；相互作用由统一 Bond 描述。

5. **Mapping 满足作用–反作用与分配一致性**  
   Bond 对两端写入力满足作用反作用；Proxy 上的力作为 Reaction，按  
   \(\mathbf{F}_i \mathrel{+}= N_i \mathbf{R}\)  
   映射到节点，且 \(\sum_i N_i = 1\) 时节点力总和等于 Reaction。

6. **显式、小步长、单向数据流**  
   连续体侧与离散侧按固定顺序交换运动学与力信息；不允许 Bond 调用 FEM、或 Mapping 修改 Sphere 运动学。

---

## 6. Algorithm Boundary

**Included in v1.0 definition (Prototype_v0.1):**

- 全域布球（规则填充作为已验证实例）  
- Host Tet 识别与形函数  
- Region 继承与 Motion Mode  
- 统一 Bond 构图（距离准则；第一版可用 \(O(N^2)\)）  
- Proxy 运动学约束与 Free 显式积分  
- Reaction → Node Mapping  
- 数学验证与自动建模能力验证（见第 7 节）

**Excluded from v1.0 (explicitly out of scope):**

- Bond 断裂  
- 接触算法  
- 优化邻域（Cell Linked List 等）  
- 自适应加密 / 自适应时间步  
- 并行（OpenMP / MPI）  
- GPU  
- 完整工程梁基准与波传播物理算例（属后续物理能力阶段）  
- 转动、Rolling Resistance 等扩展 DEM 力学

这些排除项不是疏忽，而是**算法边界声明**，供论文与后续版本对照。

---

## 7. Verified Capabilities

对应 Prototype_v0.1 已完成验证：

| Case | Capability Proven |
|------|-------------------|
| Case01 | 单耦合对闭环：插值、Bond 力、Free 积分、Mapping、作用反作用 |
| Case02 | 多耦合对叠加：多 Proxy / 多 Free / 多 Bond；Mapping 累加；Bond 独立性 |
| Case03 | 自动共生建模：全域布球 → Host Tet → Region 继承 → Motion Mode → Bond → 界面键自然形成 |

因此，v1.0 已证明：

> 该算法可以被精确定义，并在最小到中等规模模型上自动构造共生拓扑且力传递自洽。

---

## 8. Unverified Capabilities

留给 Prototype_v0.2 及以后（Phase III / IV），**本规范不声称已验证**：

| Future | Capability Not Yet Claimed |
|--------|----------------------------|
| Case04 | Automatic Neighborhood Construction（与 \(O(N^2)\) 一致性） |
| Case05 | Computational Efficiency（规模与性能） |
| Phase IV | Physical Capability（梁、裂纹、波、基准算例） |
| Later | Fracture / Contact / Parallel / GPU / Adaptivity |

未验证 ≠ 否定；仅表示**不得在 v1.0 中作为已证明能力写入论文结论**。

---

## Closing Statement

导师提出的是一个 idea。  

`Algorithm Specification v1.0` 将该 idea 固定为：

**可定义、可实现、可验证、可复现**的算法对象。

Prototype_v0.1 是该定义的第一个已验证实例。  
此后开发应版本化演进（v0.2…），而不是静默改写 v1.0 的算法含义。
