# MultiFracS v5.8 调用流程图

> 来源：`User_solver/` 源码 + `inp数据格式文件5.8.md` + DLL接口分析（逆向推断主程序逻辑）
> 注意：MultiFracS.exe 为闭源程序，本图为基于接口规范和文档的重建。

---

## 一、整体工作流（外部视角）

```
gmsh
  └─ 建几何 → 划分物理组 → 划分网格 → 导出 .inp
        ↓
  手动在 .inp 末尾添加：
    *Material *Joint *FixBoundary *SForceBoundary *VBoundary
    *CalulationType *TimeStepSize *Begin *solve *End
        ↓
  将 .inp 拖入 MultiFracS.exe（或命令行传参）
        ↓
  MultiFracS.exe 求解
        ↓
  输出：.vtk .csv .sav .dat
        ↓
  ParaView 后处理
```

---

## 二、主调用流程图（Mermaid）

```mermaid
flowchart TD

    A([MultiFracS.exe 启动]) --> B[解析命令行\n获取 .inp 文件路径]
    B --> PRE

    subgraph PRE["前处理 Preprocessing"]
        direction TB
        P1[解析网格数据\n*Node *Element *Nset *Elset\n兼容 gmsh/abaqus 格式]
        P1 --> P2[解析材料参数\n*Material *Joint\n*JointBetweenMat *ContactBetweenMat]
        P2 --> P3[解析边界条件\n*FixBoundary *SForceBoundary *VBoundary\n*InitSituStress *InitVelocity]
        P3 --> P4[解析计算控制\n*CalulationType *NumTHMpStep\n*TimeStepSize *DetectionContactForce\n*SetDllToJoint *SetDllToContactForce]
        P4 --> P5[解析输出控制\n*OutResultFileFrequency\n*OutRestoreFileFrequency\n*MonitorNode *MonitorElem]
        P5 --> P6[动态加载 DLL\nCe3D Cjoint3D Cd3D Cf3D cseepage\nSBoundary VBoundary Mech\nSeepage Thermal Moisture\nUser_solver FGM InSitu SKE Exca ...]
        P6 --> P7[SOA 内存初始化\nnfn ndn njelem 分配数组\nd1fnix/y/z d1dnvx/y/z d1dnfx/y/z\nd1jebk i1jenid ...]
        P7 --> P8[初始条件 — InSitu.dll\nInitVel InitSituStress\nInitPorePre InitPoreSat\nInitSolidTemperature InitMoisture]
        P8 --> P9[单元坐标调整 — SKE.dll\nSKE_3D 按内切球半径向外扩展\n避免零厚度节理单元干涉]
        P9 --> P10[梯度材料 — FGM.dll\nFGM_ela vp ro kT kM\n材料参数随空间坐标连续赋值]
        P10 --> P11[User 预处理 — User_solver.dll\nCreate_cpuuser\npreprocess_cpuuser\n读用户自定义 inp]
        P11 --> P12[自动计算时间步长\ndtm = α · hmin / Cp\nRayleigh 临界时间步]
    end

    PRE --> CMD{解析命令序列\n*Begin ... *End}

    CMD -->|*solve 或 *step N| LOOP
    CMD -->|*save filename.sav| SAV["写重启动文件 .sav\n保存全部场变量状态"]
    CMD -->|*restore filename.sav| REST["读重启动文件 .sav\n恢复历史状态"]
    CMD -->|*excavate elemSet nstep| EXCA["Exca.dll\nMech_Exca_v\n按时间步激活开挖标志"]
    CMD -->|*setdispzero / *setvelzero| ZERO["位移/速度/时间清零"]
    CMD -->|*plug itype| PLUG["Plug.dll\nPlug 判断堵塞节理"]
    CMD -->|*addrockbolt| BOLT["添加锚杆结构单元"]
    CMD -->|*outvtkfile| VTKFORCE["立即输出一帧 VTK"]
    CMD -->|*modifyMat / *modifyJoint| MOD["动态修改材料参数"]
    CMD -->|*End| DONE([计算完成])

    SAV --> CMD
    REST --> CMD
    EXCA --> CMD
    ZERO --> CMD
    PLUG --> CMD
    BOLT --> CMD
    VTKFORCE --> CMD
    MOD --> CMD

    subgraph LOOP["显式动力学时间推进主循环（每时间步 dtm）"]
        direction TB

        T0["步数 nstep++\n时间 t += dtm"]
        T0 --> T1

        subgraph T1["接触检测\n(Cd3D / Cf3D 内部)"]
            C1["Cell List 空间分格\n颗粒-颗粒 颗粒-单元 相邻搜索\n确定可能接触对"]
        end

        T1 --> T2

        subgraph T2["DEM 接触力 — Cd3D.dll"]
            D1["Hertz-Mindlin 接触力\n法向 Fn = kn · δn^(3/2)\n切向 Ft = kt · δs"]
            D1 --> D2["Hertz-Mindlin with Bonding\nBond 法向/切向刚度"]
            D2 --> D3["接触阻尼\nDampContact Cn Ct"]
            D3 --> D4["颗粒力汇集\n→ d1dnfx/fy/fz"]
        end

        T2 --> T3

        subgraph T3["FEM 单元内力 — Ce3D.dll"]
            E1["Ce3D.dll\nTet_constitutive_equation_increment\n四面体 C3D4 应力增量"]
            E1 --> E2["Mech.dll → Mech_Ela(σ)\n弹性模量随应力更新"]
            E2 --> E3["计算应变增量 dε\n由节点速度 → B 矩阵 → dε"]
            E3 --> E4["本构积分 → 应力增量 dσ"]
            E4 --> E5["单元力 → 节点力汇集\n→ d1fnfx/fy/fz"]
        end

        T3 --> T4

        subgraph T4["节理单元力 — Cjoint3D.dll"]
            J1["Cjoint3D_intact\n完整节理单元\n法向/切向开口量 → op_ot_sp_st"]
            J1 --> J2["损伤计算 D(o,s)\n判断是否超过临界开口量"]
            J2 --> J3{断裂判断\ni1jebk}
            J3 -->|未断裂 ijebk<=0| J4["计算键力 sig tao\n线性/双线性软化曲线"]
            J3 -->|已断裂 ijebk>0| J5["Cjoint3D_broken\n摩擦接触 Mohr-Coulomb\ntao = fric · sig"]
            J4 --> J6["力施加到节理两侧节点\n→ d1fnfx/fy/fz"]
            J5 --> J6
            J6 --> J7["声发射能量统计\ndEkbj += ΔKE"]
        end

        T4 --> T5

        subgraph T5["裂缝与渗流力 — Cf3D / cseepage"]
            F1["Cf3D.dll\n裂隙水压 → 节点开裂力\n立方定律 q = a³/12μ · Δp"]
            F1 --> F2["cseepage.dll\n孔隙压力 → Biot 体力\nf = -∇p · Biot系数"]
        end

        T5 --> T6

        subgraph T6["边界条件施加"]
            B1["SBoundary.dll\nUser_surface_force_boundary\n用户面力/吸收边界"]
            B1 --> B2["VBoundary.dll\nUser_node_velocity_boundary\n速度/位移约束\n地震波输入"]
        end

        T6 --> T7

        subgraph T7["多物理场耦合参数更新"]
            M1["Mech.dll → Mech_kf(σ)\n渗透率随应力变化"]
            M2["Seepage.dll → Pore_seepage_Ela(p)\n弹模随孔压变化"]
            M3["Thermal.dll → Thermal_Ela(T)\n弹模随温度变化"]
            M4["Moisture.dll → Moisture_Ela(w)\n弹模随含湿量变化"]
            M5["Bhm.dll → Bingham_fluid\n非牛顿流体流量"]
        end

        T7 --> T8

        subgraph T8["用户求解器 — User_solver.dll"]
            U1["solve_user(cpucore, cpuuser)"]
            U1 --> U2["user_solver 循环 nuser 次\n自定义场求解（如 SPH）"]
            U2 --> U3["user_to_MultiFracS\n将用户场力注入 d1dnfx/fy/fz"]
        end

        T8 --> T9

        subgraph T9["显式时间积分（中心差分）"]
            I1["节点加速度\na = (F_total) / m"]
            I1 --> I2["速度更新（半步）\nv(t+dt/2) = v(t-dt/2) + a · dt"]
            I2 --> I3["位移更新\nx(t+dt) = x(t) + v(t+dt/2) · dt"]
            I3 --> I4["应变率阻尼\nDampStrainRate → 速度衰减"]
            I4 --> I5["局部阻尼 FLAC 式\nDampNode itype=2/3/4"]
        end

        T9 --> T10{输出触发判断}

        T10 -->|step % OutResultFileFrequency == 0| OV["写 VTK 结果文件"]
        T10 -->|step % OutRestoreFileFrequency == 0| OR["写 .sav 重启动"]
        T10 -->|step % UpdateMonitorDataFrequency == 0| OM["写 zMonitor-*.csv"]
        T10 -->|step % OutConsoleFrequency == 0| OC["控制台输出\nnstep t Ek nbj..."]
        T10 -->|step % OutBrokenJointFrequency == 0| OBJ["写 broken-joint.csv\n裂纹玫瑰图数据"]

        OV --> T11
        OR --> T11
        OM --> T11
        OC --> T11
        OBJ --> T11

        T11{终止条件} -->|step < maxstep 且 未收敛| T0
        T11 -->|达到终止条件| LDONE[时间循环结束]
    end

    LOOP --> CMD

    subgraph OUTPUT["VTK 输出文件结构"]
        direction LR
        O1["filename-步数.vtk\nPOINTS 节点坐标\nCELLS 单元拓扑\nPOINT_DATA:\n  U 位移矢量\n  V 速度矢量\n  sigma 应力张量\n  strain 应变张量\n  maxprinstress 最大主应力\n  vonMises\n  crpre 裂隙压力\n  popre 孔隙压力\n  Ts 固体温度\n  moisture 湿度"]
        O2["filename-crack-I.vtk\n拉伸裂纹几何\nfilename-crack-II.vtk 剪切\nfilename-crack-III.vtk 拉剪"]
        O3["filename-AE-energy.vtk\n声发射能量 AE_energy(J)"]
        O4["zmhis.csv\n整体历史：t Ek Es nbj\n裂缝面积 体积 尖端坐标"]
        O5["zMonitor-Node/Elem/Joint.csv\n节点/单元监测时程"]
        O6["z-BD.csv z-UCS.csv z-UT.csv\n试验曲线（巴西劈裂/单轴压缩/拉伸）"]
    end

    OV --> OUTPUT
```

---

## 三、数据结构流（SOA 布局）

```
CPUCORE 结构体（传递给 User_solver.dll）
│
├── FEM 节点信息
│   ├── nfn          : FEM 节点总数
│   ├── d1fnix[nfn]  : 初始 X 坐标 (SOA)
│   ├── d1fniy[nfn]  : 初始 Y 坐标
│   └── d1fniz[nfn]  : 初始 Z 坐标
│
├── 离散节点信息（FEM+DEM 统一编号）
│   ├── ndn           : 节点总数
│   ├── d1dncx[ndn]   : 当前 X 坐标
│   ├── d1dnvy[ndn]   : Y 方向速度
│   ├── d1dnmass[ndn] : 节点质量
│   └── d1dnfx[ndn]   : X 方向节点力（各模块汇集）
│
├── 实体单元信息
│   ├── ndsolidelem      : 实体单元数
│   ├── i1enid[ne*(3+1)] : 单元-节点映射 (3D 四面体 4节点)
│   └── i1ebeflag[ne]    : 边界单元标志
│
└── 节理单元信息
    ├── njelem        : 节理单元数
    ├── i1jenid[nj*6] : 节理单元节点映射 (3D 三角节理 6节点)
    └── i1jebk[nj]    : 节理断裂状态 (<=0 完整 / >0 断裂类型)
```

---

## 四、DLL 调用时序（单时间步内）

```
每步调用顺序（近似）：

nstep++
  ├─① Cd3D.dll        (DEM 接触力)
  ├─② Ce3D.dll        (FEM 单元内力)  ← 调用 Ce3D_Tet_constitutive_equation_increment
  │    └─ Mech.dll    (弹模/渗透率随应力更新)
  ├─③ Cjoint3D.dll   (节理单元力)   ← 调用 Cjoint3D_intact / Cjoint3D_broken
  ├─④ Cf3D.dll        (裂缝流体压力)
  ├─⑤ cseepage.dll   (孔隙压力 Biot 体力)
  ├─⑥ SBoundary.dll  (面力边界)
  ├─⑦ VBoundary.dll  (速度边界 + 地震波)
  ├─⑧ Seepage/Thermal/Moisture.dll (多场参数更新)
  ├─⑨ User_solver.dll → solve_user → user_solver → user_to_MultiFracS
  └─⑩ 显式积分 (主程序内核) → x(t+dt) v(t+dt/2)

  if (nstep % outvtk == 0):
    └─ 写 VTK  ← Output_vtk_user (用户扩展) + 主程序内建 VTK writer
```

---

## 五、论文开发定位

### InterfaceBond 将介入的位置（第③步）

```
nstep 循环中，第③步节理单元力计算：

现有：Cjoint3D.dll
  └─ Cjoint3D_intact(rs, vnor, area, h, pn, ps, co, fric, ft, gi, gii,
                      imat, ijesf, ijebk, damge, d1jefs, p1,p2,p3, fnt)

新增（论文目标）：InterfaceBond.dll 或扩展 Cjoint3D
  └─ InterfaceBond_intact(
       femNodeVel[4][3],    ← FEM 四节点速度
       shapeFuncN[4],       ← 形函数插值系数
       demParticleVel[3],   ← DEM 颗粒速度
       Kn, Kt,              ← 界面法向/切向刚度
       fnt[2][3]            ← 力传递到两侧
     )

调用位置：
  主程序在处理 JEInterfaceBond 类型节理时
  → 调用形函数插值获得 FEM 侧代理颗粒速度
  → 调用 InterfaceBond_intact 计算界面力
  → 将力分别反馈到 FEM 节点和 DEM 颗粒
```

---

*本文件由源码阅读和文档分析自动生成，仅用于论文开发参考，非官方文档。*
