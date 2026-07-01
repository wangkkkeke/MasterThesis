# Issue007：InterfaceBond 断裂准则

**模块：** User_solver / User_solve.c
**状态：** OPEN
**优先级：** P1
**工作量：** 2天
**论文章节：** §3.2 InterfaceBond界面键力学模型 — 断裂部分（公式3-x）

---

## 任务描述

在 InterfaceBond 弹簧力计算（Issue005）基础上，加入断裂判断：
- 拉伸断裂：Fn > ft（法向力超过抗拉强度）
- 剪切断裂：|Ft| > fs（切向力超过抗剪强度）
- 断裂后：Bond 失效，仅保留摩擦接触（可选）

## 断裂准则（来自 Cjoint3D.c 参考，应用于 InterfaceBond）

```c
// 在 user_solver() 的力计算后加入：
for (int ib = 0; ib < cpuuser->n_ibond; ib++) {
    if (cpuuser->i1ibond_broken[ib]) continue;

    Real Fn  = cpuuser->d1ibond_fn[ib];
    Real ft_x = cpuuser->d1ibond_ft_x[ib];
    Real ft_y = cpuuser->d1ibond_ft_y[ib];
    Real ft_z = cpuuser->d1ibond_ft_z[ib];
    Real Ft_mag = sqrt(ft_x*ft_x + ft_y*ft_y + ft_z*ft_z);

    Real ft_strength = cpuuser->ibond_ft;  // 抗拉强度（Pa·m）
    Real fs_strength = cpuuser->ibond_fs;  // 抗剪强度（Pa·m）

    // 拉伸断裂（Fn > 0 为拉伸）
    if (Fn > ft_strength) {
        cpuuser->i1ibond_broken[ib] = 1;
        // 清零历史位移（Bond失效）
        cpuuser->d1ibond_dn[ib]   = R0;
        cpuuser->d1ibond_dt_x[ib] = R0;
        cpuuser->d1ibond_dt_y[ib] = R0;
        cpuuser->d1ibond_dt_z[ib] = R0;
    }
    // 剪切断裂
    else if (Ft_mag > fs_strength) {
        cpuuser->i1ibond_broken[ib] = 1;
        // 清零历史位移
        ...
    }
}
```

## 断裂后行为

断裂后 InterfaceBond 不再传递拉力或剪力。
是否保留 DEM-DEM 普通接触（Hertz-Mindlin）由 Core Engine 自动处理，
User_solver 不需要额外处理断裂后接触力。

## 测试方法

```
通过条件：
1. 单 Bond 拉伸断裂测试：
   设 ft_strength = 1000 N，逐渐增大拉伸量，
   Bond 在 Fn = 1000 N 时断裂，断裂后 Fn = 0

2. 单轴拉伸杆算例（Issue012）：
   拉断截面处 InterfaceBond 全部断裂，无应力残余

3. 断裂不可逆：已断裂 Bond（i1ibond_broken=1）后续步骤不再传力
```

## Review 要点

- [ ] 断裂判断在力计算之后，力注入之前执行
- [ ] 断裂后历史累积位移是否清零（防止残余力）
- [ ] `Ft_mag` 计算是否有 `> SmallPositiveNumber` 保护
- [ ] 断裂后 `i1ibond_broken[ib]` 不会被重置为0（不可逆）

## 依赖

Issue005（Bond力计算完成）
