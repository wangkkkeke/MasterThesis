# Issue005：InterfaceBond 弹簧力计算

**模块：** User_solver / User_solve.c
**状态：** OPEN
**优先级：** P0（核心算法）
**工作量：** 2-3天
**论文章节：** §3.2 InterfaceBond界面键力学模型（Kn/Kt弹簧力，公式3-x）

---

## 任务描述

实现 InterfaceBond 的弹簧力计算：
- 法向力：Fn = Kn × δn（拉伸时为正，压缩时限制为0或由参数控制）
- 切向力：Ft = Kt × δt（矢量累积）

## 理论公式（来自 FormulaIndex.md F-20/21）

```
法向相对位移：
δn = (x_dem - x_fem) · n̂       n̂ = 单位法向量（指向DEM侧）

切向相对位移（矢量，增量累积）：
δt += (v_dem - v_fem) × dt - [(v_dem - v_fem)·n̂] × n̂ × dt

弹簧力：
Fn = Kn × δn                  （标量，法向）
Ft_vec = Kt × δt_vec          （矢量，切向）

合力矢量：
F_bond = Fn × n̂ + Ft_vec
```

## 实现位置

`User_solve.c` — `user_solver()` 中（Step1速度映射后）：

```c
// Step2：计算每个 InterfaceBond 的力
for (int ib = 0; ib < cpuuser->n_ibond; ib++) {
    int fid = cpuuser->i1ibond_fid[ib];  // 代理颗粒ID
    int did = cpuuser->i1ibond_did[ib];  // DEM颗粒ID

    // 相对位移（DEM - FEM）
    Real dx = cpucore->d1dncx[did] - cpucore->d1dncx[fid];
    Real dy = cpucore->d1dncy[did] - cpucore->d1dncy[fid];
    Real dz = cpucore->d1dncz[did] - cpucore->d1dncz[fid];

    // 法向方向（初始法向量，需在preprocess中计算存储）
    Real nx = cpuuser->d1ibond_nx[ib];
    Real ny = cpuuser->d1ibond_ny[ib];
    Real nz = cpuuser->d1ibond_nz[ib];

    // 法向相对位移
    Real dn = dx*nx + dy*ny + dz*nz;
    cpuuser->d1ibond_dn[ib] = dn;

    // 切向相对速度（增量累积）
    Real dvx = cpucore->d1dnvx[did] - cpucore->d1dnvx[fid];
    Real dvy = cpucore->d1dnvy[did] - cpucore->d1dnvy[fid];
    Real dvz = cpucore->d1dnvz[did] - cpucore->d1dnvz[fid];
    Real dvn = dvx*nx + dvy*ny + dvz*nz;
    cpuuser->d1ibond_dt_x[ib] += (dvx - dvn*nx) * cpucore->dtm;
    cpuuser->d1ibond_dt_y[ib] += (dvy - dvn*ny) * cpucore->dtm;
    cpuuser->d1ibond_dt_z[ib] += (dvz - dvn*nz) * cpucore->dtm;

    // 弹簧力
    Real Kn = cpuuser->d1ibond_Kn[ib];
    Real Kt = cpuuser->d1ibond_Kt[ib];
    Real Fn = Kn * dn;
    // 存储到 cpuuser 供 user_to_MultiFracS 使用
    cpuuser->d1ibond_fn[ib] = Fn;
    cpuuser->d1ibond_ft_x[ib] = Kt * cpuuser->d1ibond_dt_x[ib];
    cpuuser->d1ibond_ft_y[ib] = Kt * cpuuser->d1ibond_dt_y[ib];
    cpuuser->d1ibond_ft_z[ib] = Kt * cpuuser->d1ibond_dt_z[ib];
}
```

> 注：d1ibond_nx/ny/nz（初始法向量）需在 Issue003 preprocess 中计算并存储到 CPUUSER。

## 测试方法

```
通过条件（静态标准验证）：
1. 两颗粒（FEM代理 + DEM）初始间距 d0，施加已知拉伸 δ
   Fn = Kn * δ，误差 < 0.1%

2. 切向测试：纯切向相对速度 v，经 N 步后
   δt = v * N * dt，Ft = Kt * δt，误差 < 0.1%

3. 模型：最小2颗粒模型，手动计算理论值对比输出
```

## Review 要点

- [ ] 法向量 n̂ 是否归一化（`> SmallPositiveNumber` 检查）
- [ ] 切向分量是否正确去除法向分量（`dvn * n̂` 正确投影）
- [ ] 所有字面量是否用 R0, R1, RP5 等常量
- [ ] 断裂后跳过计算（与 Issue007 联动：`i1ibond_broken[ib] == 1` 时跳过）

## 依赖

Issue003（Bond配对表），Issue004（速度映射）
需先在 CPUUSER 中添加 d1ibond_nx/ny/nz, d1ibond_fn, d1ibond_ft_x/y/z 字段（Issue002扩展）
