Algorithm Specification v1.0
Prototype：显式动力学 FEM–DEM 共生耦合算法（从零实现）
1. 角色定位（必须遵守）

你现在是一名计算力学算法工程师。

你的任务不是查找已有 FEM–DEM 算法，而是严格按照本文档设计并实现一种新的显式有限元–离散元共生耦合算法 Prototype。

这是导师提出的一种全新算法思想。

禁止自动套用以下已有方法：

MultiFracS
FDEM
Ghost Particle
Bridging Domain
Arlequin
Embedded Particle
Mortar
CDEM
任何已有商业软件实现

如果发现设计存在问题，请指出并讨论，不允许自行修改算法思想。

2. 开发目标

本项目不是开发工业软件。

目标只有一个：

实现一个可以运行的 Prototype，验证整个共生耦合算法闭环。

需要验证的信息流：

Tet

↓

Proxy Sphere

↓

Bond

↓

Free Sphere

↓

Bond Reaction

↓

Force Mapping

↓

Tet Node

能够正确工作。

第一阶段只关注算法正确性。

不考虑工程优化。

3. 编程规范（必须严格遵守）
编程语言

固定：

ANSI C（C99）

禁止：

C++
Python
Rust
Java
Matlab

禁止：

class
template
new/delete
STL
vector
面向对象
数据结构

整个工程固定采用：

Structure of Arrays（SoA）

禁止：

Array of Structures（AoS）

例如：

禁止：

typedef struct
{
    double x;
    double y;
    double z;
} Sphere;

必须采用：

double *sphere_x;
double *sphere_y;
double *sphere_z;

double *sphere_vx;
double *sphere_vy;
double *sphere_vz;

double *sphere_fx;
double *sphere_fy;
double *sphere_fz;

所有对象统一采用 SoA。

内存管理

统一采用：

连续数组

统一 ID

统一 Index

禁止：

链表
指针对象
malloc 一个 Sphere
malloc 一个 Bond

对象之间全部采用：

SphereID

TetID

BondID

NodeID

关联。

例如：

hostTetID

sphereID

bondID

不要保存对象指针。

4. 物理背景

研究对象：

一根连续均质梁。

整个梁：

同一种材料
同一个连续体
没有材料界面
没有接触界面

仅为了数值计算方便，

将梁划分为：

────────────────────────

   FEM     DEM     FEM

────────────────────────

注意：

这里只是数值区域。

不是两个不同物体。

不是两个不同材料。

整个模型始终只有一个连续构件。

5. 算法思想

传统方法：

FEM区只有Tet。

DEM区只有Sphere。

本算法不同。

整个计算域全部生成Sphere。

例如：

Tet Tet Tet Tet

○ ○ ○ ○ ○ ○ ○

Tet Tet Tet Tet

整个区域：

同时存在：

Tet

Sphere

其中：

Tet：

仅存在于FEM区域。

Sphere：

存在于整个区域。

6. Sphere 与运动学模式（必须遵守）

整个程序只有一种 Sphere。

禁止：

ProxySphere

FreeSphere

两个结构。

必须：

Sphere

控制计算的不是对象类型，而是运动学更新方式。

增加：

sphere_motion_mode

取值（第一阶段）：

#define MOTION_PROXY 0

#define MOTION_FREE 1

预留扩展（第一阶段不实现）：

MOTION_FIXED

MOTION_BOUNDARY

MOTION_GHOST

MOTION_RIGID

禁止再使用 sphere_type。

MOTION_PROXY

位于 FEM 区。

特点：

不积分
不求解运动方程
没有独立自由度
位置由Tet插值
速度由Tet插值

需要保存：

hostTetID

N1

N2

N3

N4

MOTION_FREE

位于 DEM 区。

特点：

独立积分
独立运动
DEM显式动力学更新
7. 自动布球

输入：

Tet Mesh

Sphere Radius

输出：

整个区域的 Sphere。

统一接口：

sphere_generate()

内部实现（预留）：

sphere_generate_regular()

sphere_generate_random()

sphere_generate_fcc()

第一版：

仅实现 sphere_generate_regular()。

后续：

增加 random / FCC，接口保持统一。

8. Sphere 分类（继承机制，必须遵守）

禁止：

仅根据球心几何坐标直接指定 motion_mode。

必须采用继承链：

Host Tet

↓

tet_region

↓

sphere_region / sphere_motion_mode

流程：

1. 对全部 Sphere 执行 sphere_find_host_tet()
2. 再执行 sphere_classify()

规则：

hostTet >= 0 且 tet_region == REGION_FEM

→ MOTION_PROXY

hostTet >= 0 且 tet_region == REGION_DEM

→ MOTION_FREE

hostTet < 0（无 Host Tet）

→ REGION_DEM，MOTION_FREE

9. Host Tet

对全部 Sphere（分类之前）寻找 Host Tet。

采用：

Point in Tetrahedron

与

Barycentric Coordinate。

若找到：

保存 hostTetID 与 N1..N4。

若未找到：

hostTetID = -1。

分类之后：

仅 MOTION_PROXY 在 Proxy Update 中使用已保存的 N；

不得在时间循环中重复搜索 Host Tet。

10. Bond

建立统一 Bond。

整个程序：

只有一种 Bond。

增加：

bond_active

Bond 建立拆分为两步（必须遵守）：

bond_search_neighbor()

↓

bond_create()

原因：

邻域搜索以后可替换为 Cell Linked List / KDTree 等，

而不必改动 Bond 创建逻辑。

第一版：

bond_search_neighbor() 可为简单距离搜索。

后续：

替换为 Cell Linked List，API 不变。

Bond规则：

Free—Free

ACTIVE

参与计算。

Proxy—Free

ACTIVE

参与计算。

Proxy—Proxy

INACTIVE

保留拓扑。

不参与力计算。

11. 时间循环

严格按照下面顺序。

Case01（Driver FEM，给定位移，不积分）：

Step0

sphere_clear_force()

清空 Sphere Force / Reaction。

Step1

driver_fem_step()

人为给定 Node Position / Velocity。

例如：Node1：x = 0.001 * sin(t)，其余节点固定。

禁止在 Case01 中做 FEM 中心差分积分。

Step2

更新所有 Proxy（MOTION_PROXY）。

Position = ΣNiUi

Velocity = ΣNiVi

Proxy 不积分。

Step3

遍历所有 Active Bond（只看 bond_active）。

Bond 模块不知道 Proxy / Free。

只做：

读取 sphereA / sphereB

计算力

写回双方 Sphere Force（作用反作用 ±F）

INACTIVE Bond 跳过。

Proxy 上的 Force 即后续 Mapping 所用的 Reaction。

DEM 只积分 MOTION_FREE，自然忽略 Proxy 上的力。

Step4

更新所有 MOTION_FREE Sphere（F=ma）。

Step5

force_mapping_proxy_to_tet()

Node Force += Ni × Reaction

Step6

写出 VTK / CSV。

Step7

下一时间步。

Case02 及以后：

将 Step1 的 driver_fem_step() 替换为真正的 fem_step()（中心差分）。

时间循环其余顺序禁止改变。

12. 软件模块

建议采用：

Prototype/

├── mesh/
├── geometry/
│      point_in_tet.c
│      barycentric.c
│      shape_function.c
├── sphere/
├── bond/
├── neighbor/
├── fem/
│      driver_fem_step.c
│      fem_solver.c
├── dem/
├── coupling/
│      force_mapping_proxy_to_tet.c
├── vtk/
├── csv/
├── driver/
│      driver_case01.c
│      driver_case02.c
│      ...
├── verify/
└── main.c

模块之间：

只能通过接口通信。

禁止：

模块互相访问内部数据。

说明：

vtk/ 与 csv/ 分目录：VTK 后续会变复杂，CSV 主要用于 Debug。

每个验证算例对应一个独立 Driver（driver/），便于论文验证与扩展。

13. 第一阶段（Prototype）

仅实现：

prototype_initialize / prototype_finalize
Tet读取（或 Case01 手工构造）
sphere_generate（内部调用 regular）
Sphere分类（设置 motion_mode）
Host Tet搜索
bond_search_neighbor
bond_create
sphere_clear_force
driver_fem_step（Case01）
Proxy插值
Bond计算
DEM积分
force_mapping_proxy_to_tet
VTK / CSV 成果输出

Case02 起再实现真正的 fem_step（中心差分）。
14. 本阶段禁止实现

不要实现：

Bond断裂
接触算法
动态邻域
动态建Bond
GPU
OpenMP
MPI
多线程
自适应时间步
工程优化
GUI
文件系统优化

全部不要。

15. 第一阶段验证算例

不要直接做整根梁。

先做最小验证。

建立：

1 Tet

↓

Driver FEM（给定位移，不积分）

↓

1 Proxy Sphere（MOTION_PROXY）

↓

1 Bond

↓

1 Free Sphere（MOTION_FREE）

验证：

Tet 位移（由 driver 给定）

↓

Proxy 是否正确插值。

Bond 力是否正确。

Free Sphere 是否运动正确。

Reaction 是否正确返回。

Tet 四节点是否收到正确外力。

整个闭环：

Driver FEM

↓

Tet

↓

Proxy

↓

Bond

↓

Free

↓

Bond

↓

Reaction

↓

force_mapping_proxy_to_tet

↓

Tet

必须成立。

只有最小算例验证成功后，再扩展到：

多Sphere
一排Sphere
DEM区域
三分区梁
完整梁模型

并从 Case02 起将 driver_fem_step 替换为真正的 fem_step。
16. 工作要求

不要立即开始编码。

第一步先完成：

检查整个算法逻辑；
绘制系统架构图；
设计 SoA 数据结构；
设计模块接口；
绘制时间循环流程图；
检查算法漏洞；
输出开发计划（Development Roadmap）。

待方案确认后，再逐模块编写 ANSI C（C99）代码。

任何超出本规范的设计，不允许自行添加，应先提出讨论。
17. 数据结构设计（必须遵守）

整个工程采用 SoA（Structure of Arrays）。

所有对象均采用统一数组管理。

17.1 Node
int node_num;

double *node_x;
double *node_y;
double *node_z;

double *node_vx;
double *node_vy;
double *node_vz;

double *node_ax;
double *node_ay;
double *node_az;

double *node_fx;
double *node_fy;
double *node_fz;

double *node_mass;
17.2 Tet
int tet_num;

int *tet_node1;
int *tet_node2;
int *tet_node3;
int *tet_node4;

int *tet_region;

Tet 不保存任何 Sphere 信息。

17.3 Sphere

整个程序只有一个 Sphere。

int sphere_num;

double *sphere_x;
double *sphere_y;
double *sphere_z;

double *sphere_vx;
double *sphere_vy;
double *sphere_vz;

double *sphere_ax;
double *sphere_ay;
double *sphere_az;

double *sphere_fx;
double *sphere_fy;
double *sphere_fz;

double *sphere_radius;

double *sphere_mass;

int *sphere_motion_mode;

int *sphere_region;

int *sphere_hostTet;

Shape Function

double *sphere_N1;
double *sphere_N2;
double *sphere_N3;
double *sphere_N4;

Motion Mode

#define MOTION_PROXY 0

#define MOTION_FREE 1

禁止使用 sphere_type / SPHERE_PROXY / SPHERE_FREE。

说明：

sphere_fx/fy/fz：Bond 写入力（双方 ±F）。

对 MOTION_PROXY：该力即 Mapping 读取的 Reaction。

对 MOTION_FREE：该力供 DEM 积分。

每步开始必须 sphere_clear_force() 清零。

禁止单独维护 sphere_rx 一类 Reaction 数组（Freeze：Bond 只写 Force）。
17.4 Bond
int bond_num;

int *bond_sphereA;

int *bond_sphereB;

char *bond_active;

参数：

double *bond_kn;

double *bond_ks;

double *bond_L0;

double *bond_fn;

double *bond_fs;

第一版：

不用断裂。

bond_L0：建 Bond 时记录的初始中心距（线弹性弹簧原长）。

17.5 Neighbor

采用 Cell Linked List。

int *cell_head;

int *cell_next;

不要 KDTree。

不要 BVH。

不要八叉树。

Case01 可用简单距离搜索实现 bond_search_neighbor()，

但 API 必须保留，以便后续替换为 Cell Linked List。

18. 软件模块

建议目录如下：

Prototype/

│

├── geometry/

│      point_in_tet.c

│      barycentric.c

│      shape_function.c

│

├── sphere/

│      sphere_generate.c

│      sphere_generate_regular.c

│      sphere_classify.c

│      sphere_proxy_update.c

│      sphere_clear_force.c

│

├── bond/

│      bond_search_neighbor.c

│      bond_create.c

│      bond_force.c

│

├── fem/

│      driver_fem_step.c

│      fem_solver.c

│

├── dem/

│      dem_solver.c

│

├── coupling/

│      force_mapping_proxy_to_tet.c

│

├── neighbor/

│      cell_list.c

│

├── vtk/

│      vtk_write.c

│

├── csv/

│      csv_write.c

│

├── driver/

│      driver_case01.c

│      driver_case02.c

│

├── verify/

│      case01_check.c

│

└── main.c

所有模块：

一个功能。

不要写 God File。

19. API 设计

Cursor 第一件事不是写 main。

而是设计 API。

生命周期：

prototype_initialize();

prototype_finalize();

Sphere：

sphere_generate();

sphere_generate_regular();

sphere_classify();

sphere_find_host_tet();

sphere_clear_force();

proxy_update();

Bond：

bond_search_neighbor();

bond_create();

bond_compute_force();

FEM：

driver_fem_step();

fem_step();

DEM：

dem_step();

Coupling：

force_mapping_proxy_to_tet();

输出：

vtk_write();

csv_write();

整个程序围绕 API 组织。

20. Time Loop（固定）

Case01：

while(time<t_end)
{

sphere_clear_force();

driver_fem_step();

proxy_update();

bond_compute_force();

dem_step();

force_mapping_proxy_to_tet();

vtk_write();

csv_write();

}

Case02 及以后：

将 driver_fem_step() 替换为 fem_step()。

禁止改变其余顺序。

21. Force Mapping（固定）

API 名称：

force_mapping_proxy_to_tet()

明确数据流方向：Proxy Reaction → Tet Node。

对于每一个 MOTION_PROXY：

Reaction

↓

N1 N2 N3 N4

↓

Tet Nodes

公式：

Fi += Ni × Reaction

必须满足：

作用反作用。

不要采用其它 Mapping。

22. Bond Force（固定）

第一版：

采用最简单线弹性。

Normal

Fn=Kn×δn

Tangential

Fs=Ks×δs

不要加入：

Mohr-Coulomb

不要加入：

断裂。

不要加入：

阻尼。

23. Explicit FEM（固定）

Case01：

禁止实现完整 FEM 中心差分。

必须使用 Driver FEM：

driver_fem_step()

人为给定节点位移/速度。

一次只验证一个模块：闭环插值与映射。

Case02 及以后：

切换为真正的 fem_step()。

采用：

中心差分。

不要：

Newmark。

不要：

隐式。

不要：

牛顿迭代。

不要：

矩阵求解器。

24. Explicit DEM（固定）

采用：

F=ma

↓

a

↓

v

↓

x

仅对 MOTION_FREE 更新。

第一版：

不要：

旋转。

不要：

角速度。

不要：

Rolling Resistance。

不要：

颗粒接触。

25. 第一阶段验证

不要做梁。

不要做裂纹。

不要做复杂模型。

只验证：

Case 01

Driver FEM（给定位移）

↓

Tet

↓

Proxy（插值）

↓

Bond

↓

Free

↓

Reaction

↓

force_mapping_proxy_to_tet

目的：

验证 Proxy 是否正确。

验证 Mapping 是否正确。

不验证完整 FEM 积分。

要求输出：

Proxy Position

Bond Force

Free Position

Reaction Force

Tet Node Force

能够人工计算验证。

Driver 示例：

Node1：x = 0.001 * sin(t)

其余节点固定。

对应文件：

driver/driver_case01.c

25.1 算例成果与可视化（必须遵守）

每个算例必须导出可核查、可可视化的成果文件。

固定要求：

VTK（vtk/ 模块）

用于几何与场量可视化（ParaView 等）。

至少包含：

Node / Tet 网格

Sphere 位置

Bond 连接（可选，但推荐）

关键场量（如位移、力、Reaction）

CSV（csv/ 模块）

用于数值核对与时程分析。

至少包含：

时间步

Proxy Position

Free Position

Bond Force

Reaction Force

Tet Node Force

要求：

输出内容须能支撑人工计算验证。

第一阶段只要求文件可读、量可核对。

禁止：

GUI

交互式可视化界面

工程级后处理优化

Case02 — Multi-Coupling Pair Verification（多耦合对验证）

唯一目标：

验证算法从单耦合对扩展到多耦合对后，
力的叠加、映射叠加和整体守恒仍然成立。

模型拓扑（固定）：

           P1
          /  \
        B1    B2
        /      \
       F1      F2
        \      /
        B3    B4
          \  /
           P2

2 Proxy + 2 Free + 4 ACTIVE Bond（全部 Proxy–Free）。

明确不验证：

邻域搜索（Cell Linked List）
自动布球
复杂几何
Bond 断裂
接触
波传播
梁模型
完整 FEM 中心差分

验证项 V1–V8：

V1 Shape Function（回归）
V2 Sphere Force = Σ Bond Force
V3 Proxy Reaction = Σ Bond 对 Proxy 的力
V4 Node Force Mapping（单 Proxy）
V5 Multi-Proxy Mapping（多 Proxy 对同节点累加）
V6 Action-Reaction（每条 Bond）
V7 Global Force（ΣF≈0）
V8 Bond Independence（删一条 Bond，其余结果不变）

通过标准：

全部 Verification PASS
全局力守恒满足容差
每条 Bond 作用-反作用成立
Mapping 与理论一致
误差达到双精度量级（建议 1e-12）

产物：

output/verify_case02.csv
VerificationReport_Case02.md

Case03 — Global Sphere Embedding

定位：Algorithm Capability Demonstration（算法能力验证）

唯一目标：

验证全域自动布球后，算法能自动完成

Host Tet 搜索、Region→Motion 继承分类、Bond 建立，

形成完整共生耦合拓扑。

不验证：新力学公式、梁加载、裂纹、完整 FEM/DEM、邻域优化。

能力：

M1 sphere_generate_regular（全域规则布球）
M2 sphere_classify（HostTet→Region→Mode）
M3 sphere_find_host_tet（全部球）
M4 bond_search_neighbor O(N²) + bond_create

模型：

极小 FEM | DEM | FEM 分区网格（DEM 区无 Tet）。

验证项 V1–V9：

V1 Sphere Generation
V2 Sphere Classification
V3 Host Tet Search
V4 Shape Function sum N=1
V5 Bond Generation
V6 Boundary Bond（Proxy–Free 界面）
V7 Connectivity
V8 Visualization（VTK：Proxy 蓝 / Free 红）
V9 Region Consistency（Motion 与 Host Tet Region 一致）

产物：

output/case03.vtk
output/case03.csv
output/verify_case03.csv
VerificationReport_Case03.md

Case04 — Automatic Neighborhood Construction（Phase III）

定位：Computational Capability

验证：

Cell Linked List
自动建键与 O(N²) 一致性
Bond Graph 构建效率

不验证新力学公式，不做梁/裂纹物理基准。

Case05 — Computational Efficiency（Phase III）

效率与规模扩展（在 Case04 通过后）。

Phase IV — Physical Capability

Beam / Crack / Benchmark（物理能力，另立案）。

30. Prototype_v0.1 Release（里程碑冻结）

Release: Prototype_v0.1
Status: Verified
Date: 2026-07-13

已完成：

Phase I Mathematical Verification：Case01、Case02
Phase II Algorithm Capability：Case03

Capability：

Automatic Symbiotic Model Construction

冻结文档：

RELEASE_Prototype_v0.1.md
Algorithm_Note_01.md
ADR002_GlobalSphereEmbedding.md
CONCEPT_MODEL_AutomaticSymbioticTopology.md

政策：

不得再修改 v0.1 内容。
后续一律从 Tag Prototype_v0.1 分支到 Prototype_v0.2。

正式路线图：

Phase I  Mathematical Verification     → Case01, Case02
Phase II Algorithm Capability          → Case03  （= Prototype_v0.1）
Phase III Computational Capability     → Case04 Neighborhood, Case05 Efficiency
Phase IV Physical Capability           → Beam, Crack, Benchmark

26. 开发原则（必须遵守）

任何实现必须遵守以下原则：

原则1

先验证算法。

后优化代码。

原则2

先最小算例。

后复杂模型。

原则3

先保证正确。

后保证效率。

原则4

一次只验证一个模块。

Case01 不混入完整 FEM 积分。

原则5

所有设计必须能够迁移至 MultiFracS 风格工程。

因此：

ANSI C
SoA
ID Index
模块化
motion_mode 控制运动学

不得改变。

27. Cursor 工作流程（强制）

第一轮：

不要写代码。

输出：

①总体架构

②模块设计

③数据结构

④API

⑤流程图

⑥开发路线

第二轮：

逐模块实现（ANSI C / C99 / SoA）。

第三轮：

逐 Case 验证（含 VTK / CSV）。

第四轮：

扩展三分区梁。

28. Architecture Freeze v1.0（强制锁死）

自本节起，除非发现严重 Bug，否则：

不再修改算法框架。
不再增加新模块。
不再调整 API。
不再讨论理论。

后续工作仅围绕 ANSI C（C99）+ SoA 实现 Prototype，
按 Case01 → Case02 → Case03 → Case04 验证。

① Bond 永远不知道 Proxy / Free

Bond 禁止出现 if(proxy) / if(free)。

Bond 只知道 sphereA、sphereB。

是否参与计算只由 bond_active 决定。

流程：读取两球 → 计算力 → 写回双方 Sphere Force（±F）。

bond_create 阶段可一次性设置 bond_active；
bond_compute_force 运行期不得再按 motion_mode 分支。

② Proxy Update 不计算任何力

唯一职责：Tet 插值 → Position / Velocity。

禁止：清 Force、算 Force、Mapping。

③ Force Mapping 不修改 Sphere

唯一允许修改：Node Force。

禁止修改 Sphere Position / Velocity / Force。

单向：Proxy 的 Sphere Force（作 Reaction）→ Node。结束。

④ DEM Solver 不认识 Proxy

仅允许：

for 全部 sphere：若 mode != MOTION_FREE 则 continue。

禁止存在 proxy_solver()。

⑤ FEM Solver 不认识 Sphere

只知道 Node / Tet。

Sphere 信息只能经 force_mapping_proxy_to_tet 进入节点力。

⑥ 数据流必须单向

Tet → Proxy Update → Bond → Free → Reaction(Force on Proxy) → Mapping → Node

禁止反向调用（例如 Bond 调用 FEM）。

⑦ Time Loop 不允许模块互调

禁止在某模块内部调用其它阶段模块。

全部由 driver / 调度层统一调用。

⑧ SoA 冻结

禁止：Sphere sphere[100] 等 AoS。

必须：sphere_x[] / sphere_y[] / sphere_z[] 等。

直至 Prototype 结束。

⑨ 所有 API 单职责、无额外副作用

一个 API 一个职责。

例如 proxy_update 只更新 Proxy 位姿，不建 Bond、不做 Mapping。

⑩ Debug 输出规范

统一前缀：

[Sphere]
[Bond]
[FEM]
[DEM]
[Mapping]
[Driver]
[VTK]
[CSV]

29. 第二轮实现顺序（按依赖，禁止按目录乱序）

Stage 1：SoA + Memory + Initialize / Finalize
Stage 2：Geometry（point_in_tet / barycentric / shape_function）
Stage 3：Sphere Generate（regular）
Stage 4：Host Tet
Stage 5：Proxy Update
Stage 6：Bond Force（含 search_neighbor + create 的最小实现）
Stage 7：DEM Step
Stage 8：Force Mapping
Stage 9：Driver Case01
Stage 10：VTK / CSV

每一 Stage 须可独立编译与验证后再进入下一 Stage。