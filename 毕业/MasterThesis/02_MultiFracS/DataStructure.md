# MultiFracS v5.8 核心数据结构文档

> 来源：`User_solver/Cpucore.h` + `User_solver/Cpuuser.h` + 所有 `.h/.c` 文件分析
> 注意：主程序为闭源，以下为基于开放接口的完整推断，带 [推断] 标注的字段无源码直接证明。

---

## 一、Node — FEM 有限元节点

### 描述
FEM 计算的基本自由度单元。MultiFracS 将 FEM 节点和 DEM 颗粒统一编号进入"离散节点"数组，通过不同字段区分。

### SOA 数组（CPUCORE 中）

| 字段名 | 类型 | 尺寸 | 物理意义 |
|--------|------|------|---------|
| `nfn` | `int` | 标量 | FEM 节点总数 |
| `d1fnix[nfn]` | `Real*` | [nfn] | 初始 X 坐标（只读参考，不随变形更新） |
| `d1fniy[nfn]` | `Real*` | [nfn] | 初始 Y 坐标 |
| `d1fniz[nfn]` | `Real*` | [nfn] | 初始 Z 坐标 |
| `ndn` | `int` | 标量 | 离散节点总数（FEM+DEM 统一编号） |
| `ndim` | `int` | 标量 | 维数：2=2D，3=3D |
| `d1dncx[ndn]` | `Real*` | [ndn] | 当前 X 坐标（随时间步更新） |
| `d1dncy[ndn]` | `Real*` | [ndn] | 当前 Y 坐标 |
| `d1dncz[ndn]` | `Real*` | [ndn] | 当前 Z 坐标 |
| `d1dnvx[ndn]` | `Real*` | [ndn] | X 方向速度（半步格式） |
| `d1dnvy[ndn]` | `Real*` | [ndn] | Y 方向速度 |
| `d1dnvz[ndn]` | `Real*` | [ndn] | Z 方向速度 |
| `d1dnmass[ndn]` | `Real*` | [ndn] | 节点质量（集中质量阵） |
| `d1dnfx[ndn]` | `Real*` | [ndn] | X 方向合力（各模块汇集，每步清零再累加） |
| `d1dnfy[ndn]` | `Real*` | [ndn] | Y 方向合力 |
| `d1dnfz[ndn]` | `Real*` | [ndn] | Z 方向合力 |
| `i1dnbnflag[ndn]` | `int*` | [ndn] | 边界节点标志（>0 为边界节点） |

### 关键说明
- `d1fnix/y/z`（初始坐标）与 `d1dncx/y/z`（当前坐标）分开存储，初始坐标仅用于参考插值
- FEM 节点在 `d1dncx/y/z` 中通过 FEM-DEM 统一节点编号索引，`[0, nfn)` 为 FEM 节点，`[nfn, ndn)` 为 DEM 颗粒节点 [推断]
- `d1dnfx/y/z` 是各 DLL 写入的汇集点：Ce3D、Cjoint3D、Cd3D、SBoundary、VBoundary 均向此数组累加力

### 生命周期
```
主程序 preprocess → 读 .inp *Node → 分配 ndn*sizeof(Real)*9 → 填充 d1dncx/y/z d1fnix/y/z
    ↓
每步时间积分：
    d1dnfx/y/z 清零 → 各 DLL 累加力 → 计算加速度 a=F/m → 更新 d1dnvx/y/z → 更新 d1dncx/y/z
    ↓
计算结束：释放内存
```

---

## 二、Element — 实体单元（C3D4 四面体）

### 描述
FDEM 中 FEM 侧的基本计算单元，3D 主要为 4 节点四面体（C3D4，`IeType=11`）。

### SOA 数组（CPUCORE 中）

| 字段名 | 类型 | 尺寸 | 物理意义 |
|--------|------|------|---------|
| `ndsolidelem` | `int` | 标量 | 实体单元总数 |
| `i1enid[ndsolidelem*(ndim+1)]` | `int*` | [ne*4] | 单元-节点映射（C3D4：4个节点编号） |
| `i1ebeflag[ndsolidelem]` | `int*` | [ne] | 边界单元标志（用于接触检测范围） |
| `d1epn[ndsolidelem]` | `Real*` | [ne] | 单元法向接触罚参数 |
| `d1ept[ndsolidelem]` | `Real*` | [ne] | 单元切向接触罚参数 |
| `d1efr[ndsolidelem]` | `Real*` | [ne] | 单元接触内摩擦系数 |

### 隐含字段（传递给 Ce3D.dll 的参数，主程序维护）[推断]

| 参数 | 物理意义 | 对应 inp 关键词 |
|------|---------|----------------|
| `G` | 剪切模量（由 Ela, vp 计算） | `*Material` |
| `lamda` | 拉梅常数 λ | `*Material` |
| `imat` | 材料编号（0起） | `*Material` 顺序 |
| `s11,s22,s33,s12,s23,s31` | 6分量应力张量（每单元维护） | — |
| `de11,...,de31` | 应变增量（由节点速度+B矩阵计算） | — |

### Ce3D.dll 接口

```c
// 每时间步每个实体单元调用一次
Tet_constitutive_equation_increment(
    G, lamda, imat,
    de11, de22, de33, de12, de23, de31,  // 输入：应变增量（由速度梯度计算）
    &s11, &s22, &s33, &s12, &s23, &s31  // 输入输出：应力（累加更新）
)
// 内部：各向同性线弹性 ds = 2G·de + λ·tr(de)·I
// 用户可修改为塑性、黏弹性等本构
```

### 生命周期
```
preprocess → 读 *Element → 填充 i1enid d1epn d1ept d1efr
    ↓
每步力计算：
    主程序读取单元4节点速度 → 计算 B 矩阵 → 应变增量 de
    → 调用 Ce3D.dll → 更新单元应力 s → 积分得节点力 → 汇入 d1dnfx
    ↓
每步输出（outvtk）：主程序读取单元应力 → 写入 VTK sigma/strain 字段
```

---

## 三、Particle — DEM 颗粒

### 描述
DEM 侧的基本运动单元（矩阵DEM：球形颗粒）。在 CPUCORE 中有两套字段：SPH 颗粒参数（`d1sph*`）和统一离散节点（`d1dn*`，颗粒同样是节点）。

### SPH/DEM 特有字段（CPUCORE）

| 字段名 | 类型 | 尺寸 | 物理意义 |
|--------|------|------|---------|
| `nsph` | `int` | 标量 | SPH/DEM 颗粒总数 |
| `i1sphfnid[nsph*(ndim+1)]` | `int*` | [nsph*4] | 颗粒所属 FEM 单元的节点编号（用于形函数插值） |
| `i1sphmatid[nsph]` | `int*` | [nsph] | 颗粒材料编号 |
| `d1sphrho[nsph]` | `Real*` | [nsph] | 初始密度 ρ₀ |
| `d1sphnu[nsph]` | `Real*` | [nsph] | 流体黏性系数 ν |
| `d1sphcs[nsph]` | `Real*` | [nsph] | 流体声速 cs |
| `d1sphp0[nsph]` | `Real*` | [nsph] | 参考压力 p₀（大气压 1.013e5 Pa） |
| `d1sphdx[nsph]` | `Real*` | [nsph] | 初始颗粒间距 dx |
| `d1sphh[nsph]` | `Real*` | [nsph] | 光滑长度 h（1.2~1.5 · dx） |
| `d1sphr[nsph]` | `Real*` | [nsph] | 颗粒半径 r |

### 运动状态（复用 d1dn* 数组）[推断]

| 字段 | 物理意义 |
|------|---------|
| `d1dncx/y/z[nfn + iparticle]` | 颗粒当前坐标（颗粒在统一编号中从 nfn 开始） |
| `d1dnvx/y/z[nfn + iparticle]` | 颗粒当前速度 |
| `d1dnmass[nfn + iparticle]` | 颗粒质量 = ρ · (4/3)πr³ |
| `d1dnfx/y/z[nfn + iparticle]` | 颗粒合力（Cd3D 接触力 + InterfaceBond 力） |

### 关键字段：`i1sphfnid`
```
i1sphfnid[nsph*4] 存储每个颗粒所属 FEM 单元的4个节点编号
→ 用于 InterfaceBond 的形函数插值：
   v_proxy = N0*v[i0] + N1*v[i1] + N2*v[i2] + N3*v[i3]
   其中 i0~i3 = i1sphfnid[iparticle*4 + 0~3]
```

### 生命周期
```
preprocess → 读 *Element（FEM）→ 生成每个 FEM 单元内部的颗粒（或由 DEM 直接离散）
    → 填充 i1sphfnid（记录颗粒属于哪个 FEM 单元的哪4个节点）
    ↓
每步接触力计算（Cd3D.dll）：
    空间格搜索邻近颗粒 → Hertz-Mindlin 接触力 → 汇入 d1dnfx
    ↓
每步 InterfaceBond 力（论文新增模块）：
    读 i1sphfnid → 形函数插值 FEM 侧代理速度 → 键力计算 → 汇入 d1dnfx + d1dnfx(FEM侧)
```

---

## 四、Material — 材料参数

### 描述
材料参数不作为独立结构体传递，而是通过函数参数逐个传递给各 DLL。主程序维护一个材料参数表，调用 DLL 时按需传入。

### 实体单元材料参数（来自 inp `*Material`）

| 参数 | 物理意义 | 单位 |
|------|---------|------|
| `IeType` | 单元类型（11=C3D4） | — |
| `ro` | 密度 | kg/m³ |
| `Ela` | 弹性模量 E | Pa |
| `vp` | 泊松比 ν | — |
| `pn` | 法向接触罚参数（~100E） | Pa/m |
| `ps` | 切向接触罚参数 | Pa/m |
| `kf11/22/33` | 渗透率张量对角项 | m² |
| `kT11/22/33` | 热传导系数 | W/(m·K) |
| `kM11/22/33` | 湿度传导系数 | m²/s |
| `Cp` | 比热容 | J/(kg·K) |
| `tec` | 热膨胀系数 α | 1/K |
| `ft` | 实体单元抗拉强度 | Pa |

### 节理单元材料参数（来自 inp `*Joint`）

| 参数 | 物理意义 | 单位 |
|------|---------|------|
| `IbkFlag` | 初始断裂状态（0=完整，1=断裂，-1=允许流体通过） | — |
| `co` | 粘聚力 c（>0） | Pa |
| `fric` | 内摩擦系数 tan(φ) | — |
| `ft` | 抗拉强度 | Pa |
| `pn` | 法向罚参数（~100E） | Pa/m |
| `ps` | 切向罚参数 | Pa/m |
| `gi` | I 型断裂能 GfI | J/m² |
| `gii` | II 型断裂能 GfII | J/m² |
| `a0,amin,amax` | 初始/最小/最大张开度 | m |
| `h` | 特征长度（由主程序计算，等于节理单元最短边/面的特征尺寸） | m |

### 材料编号规则（来自 FGM.c 注释）
```
imat 从 0 开始，按照 *Material 关键词在 .inp 文件中出现的顺序整体编号
节理单元 imat 接续实体单元 imat 继续编号
```

### 多物理场耦合时的动态修改
- `Mech.dll` → `Mech_Ela(imat, sigma, strain, ...)` 在每步返回当前 Ela
- `Seepage.dll` → `Pore_seepage_Ela(imat, p, sat, ...)` 返回压力相关 Ela
- `Thermal.dll` → `Thermal_Ela(imat, T, ...)` 返回温度相关 Ela
- 主程序每步以这些返回值覆盖材料参数表，再传给本构计算

---

## 五、Contact — 接触对

### 描述
DEM 颗粒间或颗粒-结构面间的接触关系，由 `Cd3D.dll`（闭源）维护。接触信息不在 CPUCORE 中暴露，仅通过接触力汇集到节点力。

### 接触检测参数（来自 inp）

| 参数 | 物理意义 |
|------|---------|
| `*DetectionContactForce 1` | 开启接触检测 |
| `*MaxNumPossibleContact` | 最大可能接触对数 |
| `*SetSearchRange` | 空间搜索范围 |
| `*RoundRadiusRatioContact` | 圆角半径比（0<λ<1，接触软化处理） |

### 接触力模型（来自 inp `*SetDllToContactForce` + `Architecture.md`）

| 选项 | 模型 |
|------|------|
| 1（默认） | `Cf2D/3D.dll` |
| 2 | `Cf2D/3D_vol.dll` |
| 3 | 嵌入量接触力算法 |

### DEM 接触本构（来自技术建议书，Cd3D.dll 内部实现）
```
法向力：Fn = kn · δn   （罚参数法，pn*overlap）
切向力：Ft = min(kt·δs,  -Fn·fric)   （Mohr-Coulomb 限制）
```

### 用户可定制部分
- `SRM.dll` → `Reduction_contact_fric()` 按强度折减系数缩减接触摩擦
- `SRM.dll` → `Set_contact_fric_as_function_of_vs()` 滑动速度相关摩擦

### 接触状态（来自 Real.h 与 VTK 输出）
```c
// 节理单元状态（i1jebk）：
JEInterfaceIntact  = 1   // 完整（有凝聚力）
JEInterfaceBroken  = 2   // 断裂（仅摩擦接触）
JEBKT1            = 11   // 拉裂缝
JEBKT2            = 12   // 剪裂缝
JEBKT3            = 13   // 拉剪混合
JEGrout           = -10  // 注浆加固
JEEXCA            = 14   // 已开挖
```

---

## 六、InterfaceBond — FEM-DEM 界面键（论文开发目标）

### 描述
本论文需要实现的核心模块。负责连接 FEM 区域与 DEM 区域，通过弹簧键传递力和位移。

### 理论数据结构（待实现）

```c
// 建议的 InterfaceBond 单元数据（类比节理单元扩展）
struct InterfaceBond_struct {
    // 几何关系
    int femElemID;          // 所属 FEM 单元编号
    int femNodeID[4];       // FEM 单元的4个节点编号（取自 i1sphfnid 或新建）
    Real shapeFuncN[4];     // 形函数系数 N0~N3（由颗粒在四面体内的位置决定）
    int demParticleID;      // 对应的 DEM 颗粒编号
    
    // 界面键参数
    Real Kn;                // 法向键刚度（来自 *JointBetweenMat 或新关键词）
    Real Kt;                // 切向键刚度
    
    // 状态量
    Real relDispN;          // 法向相对位移（当前步）
    Real relDispT[3];       // 切向相对位移向量
    Real bondForce[3];      // 当前键力向量
    
    // 断裂标志
    int ibondState;         // 0=完整，1=已断裂
};
```

### 与现有数据结构的接口关系

```
FEM 侧代理颗粒速度（由 i1sphfnid 提供索引）：
    v_proxy = sum(N_i * d1dnvy[femNodeID[i]],  i=0..3)

DEM 侧颗粒速度（直接读取）：
    v_dem = d1dnvy[nfn + demParticleID]

相对速度 → 相对位移增量 → 键力：
    dv_rel = v_proxy - v_dem
    ddisp = dv_rel * dtm
    dF = Kn * ddisp_n + Kt * ddisp_t

力反馈：
    d1dnfx[demParticleID] += -bondForce[0]       // 作用于 DEM 颗粒
    对4个 FEM 节点按形函数权重分配：
    d1dnfx[femNodeID[i]] += +bondForce[0] * N_i   // 作用于 FEM 节点
```

### 生命周期（设计）
```
preprocess → 识别 FEM-DEM 界面 → 生成 InterfaceBond 列表
    → 计算各键的 shapeFuncN（颗粒在四面体内的重心坐标）
    ↓
每步：主循环第③步
    读 FEM 节点速度 → 形函数插值 → v_proxy
    读 DEM 颗粒速度 → v_dem
    计算键力 → 写入 d1dnfx（FEM节点+DEM颗粒）
    ↓
断裂判断（如需）：键力超过临界值 → ibondState = 1 → 不再计算键力
```

---

## 七、CPUCORE 完整结构体（汇总）

```c
struct CPUCORE_struct {
    // 输出控制
    int outvtk;           // VTK 输出间隔（步）
    int outconsole;       // 控制台输出间隔

    // 时间步
    Real dtm;             // 力学时间步长（Rayleigh 判据）
    Real dtsph;           // SPH 时间步长

    // 阻尼
    Real dampCn;          // 法向接触阻尼
    Real dampCt;          // 切向接触阻尼

    // FEM 节点
    int nfn;              // FEM 节点数
    Real *d1fnix, *d1fniy, *d1fniz;  // 初始坐标 [nfn]

    // SPH/DEM 颗粒参数
    int nsph;
    int *i1sphfnid;       // 颗粒所属FEM单元节点 [nsph*4] ← InterfaceBond关键
    int *i1sphmatid;      // 材料编号 [nsph]
    Real *d1sphrho, *d1sphnu, *d1sphcs;
    Real *d1sphp0, *d1sphdx, *d1sphh, *d1sphr;

    // 统一离散节点（FEM+DEM）
    int ndn, ndim;
    Real *d1dncx, *d1dncy, *d1dncz;   // 当前坐标 [ndn]
    Real *d1dnvx, *d1dnvy, *d1dnvz;   // 速度 [ndn]
    Real *d1dnmass;                     // 质量 [ndn]
    Real *d1dnfx, *d1dnfy, *d1dnfz;   // 合力 [ndn] ← 各DLL写入点
    int  *i1dnbnflag;                   // 边界标志 [ndn]

    // 实体单元
    int ndsolidelem;
    int  *i1enid;         // 单元节点映射 [ne*(ndim+1)]
    int  *i1ebeflag;      // 边界单元标志 [ne]
    Real *d1epn;          // 法向罚参数 [ne]
    Real *d1ept;          // 切向罚参数 [ne]
    Real *d1efr;          // 接触摩擦系数 [ne]

    // 节理单元
    int njelem;
    int  *i1jenid;        // 节理节点映射 [nj*6（3D三角节理）]
    int  *i1jebk;         // 断裂状态 [nj]
};
```
