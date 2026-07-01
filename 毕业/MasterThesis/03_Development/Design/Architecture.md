# Architecture.md — InterfaceBond 软件架构设计

> 本文件记录 InterfaceBond 模块在 MultiFracS 中的架构设计决策。
> 对应论文 §3.5 MultiFracS 平台集成与计算流程。
> 详细接口文档：`02_MultiFracS/DeveloperGuide.md`

---

## 设计决策：使用 User Solver DLL

**决策：** InterfaceBond 全部实现在 `User_solver.dll` 中，不修改 User Function DLL。

**理由：**
- InterfaceBond 是"全局耦合"（需要同时访问 FEM 节点数组和 DEM 颗粒数组）
- User Function DLL 接口（如 Ce3D、Cjoint3D）只能访问单个单元的局部数据
- 只有 User Solver DLL 能通过 CPUCORE 访问全局数组

---

## 模块划分

```
User_solver.dll
│
├── User_preprocess.c     ← 一次性：界面颗粒识别（Issue003）
│                            一次性：Bond配对表建立
│                            一次性：CPUUSER内存分配
│
├── User_solve.c          ← 每步：代理颗粒速度映射（Issue004）
│                            每步：InterfaceBond弹簧力计算（Issue005）
│                            每步：断裂准则判断（Issue007）
│
├── user_to_MultiFracS()  ← 每步：力注入到FEM节点+DEM颗粒（Issue006）
│
└── User_postprocess.c    ← 定期：InterfaceBond VTK输出（Issue010）
```

---

## CPUUSER 字段规划

参见：`03_Development/Issues/Issue002_CPUUSER数据结构设计.md`

关键字段：
- `n_ibond`：Bond数量
- `i1ibond_fid/did`：配对ID
- `d1ibond_Kn/Kt`：刚度
- `d1ibond_dn/dt_x/y/z`：历史位移
- `i1ibond_broken`：断裂状态

---

## 调用时序（每时间步）

```
① Core Engine: FEM内力 + DEM接触力
② User_solve(): 速度映射 → Bond力计算 → 断裂判断
③ user_to_MultiFracS(): 力注入
④ Core Engine: 显式时间积分 a=F/m → v → x
⑤ Output: 定期VTK输出
```

**注意：** ②③不可颠倒（先算力再注入），②内部顺序不可颠倒（先映射速度再算力）。

---

## 已排除的备选方案

| 方案 | 排除原因 |
|------|---------|
| 修改 Ce3D.dll 实现耦合 | Ce3D 只能访问单个单元局部数据，无法看到全局 DEM 颗粒 |
| 修改 Cjoint3D.dll | 同上，且 Cjoint3D 针对节理单元，不针对粒子-粒子Bond |
| 新建独立 DLL（InterfaceBond.dll）| MultiFracS 无此扩展接口，只支持 User Solver |
