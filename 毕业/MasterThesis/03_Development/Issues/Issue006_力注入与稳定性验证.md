# Issue006：InterfaceBond 力注入与时间步稳定性验证

**模块：** User_solver / User_solve.c（user_to_MultiFracS）
**状态：** OPEN
**优先级：** P0
**工作量：** 1-2天
**论文章节：** §3.3 显式动力学求解框架（稳定性，公式3-x）

---

## 任务描述

1. 在 `user_to_MultiFracS()` 中将 InterfaceBond 力注入主程序节点数组
2. 验证时间步设置合理，FEM-DEM 界面不发散

## 力注入位置（来自 DeveloperGuide.md §3.3）

```c
// user_to_MultiFracS() — 这是写入 d1fnfx/d1dnfx 的唯一合法位置
void user_to_MultiFracS(CPUCORE cpucore, CPUUSER cpuuser) {
    for (int ib = 0; ib < cpuuser->n_ibond; ib++) {
        if (cpuuser->i1ibond_broken[ib]) continue;  // 跳过断裂Bond

        int fid = cpuuser->i1ibond_fid[ib];
        int did = cpuuser->i1ibond_did[ib];

        Real nx = cpuuser->d1ibond_nx[ib];
        Real ny = cpuuser->d1ibond_ny[ib];
        Real nz = cpuuser->d1ibond_nz[ib];
        Real Fn = cpuuser->d1ibond_fn[ib];
        Real ftx = cpuuser->d1ibond_ft_x[ib];
        Real fty = cpuuser->d1ibond_ft_y[ib];
        Real ftz = cpuuser->d1ibond_ft_z[ib];

        // 合力矢量
        Real fx = Fn*nx + ftx;
        Real fy = Fn*ny + fty;
        Real fz = Fn*nz + ftz;

        // FEM代理颗粒 → 传递到绑定的FEM节点
        int fnid = cpucore->i1sphfnid[fid];
        cpucore->d1fnfx[fnid] += fx;   // FEM节点受Bond力
        cpucore->d1fnfy[fnid] += fy;
        cpucore->d1fnfz[fnid] += fz;

        // DEM颗粒受反向力（牛顿第三定律）
        cpucore->d1dnfx[did] -= fx;
        cpucore->d1dnfy[did] -= fy;
        cpucore->d1dnfz[did] -= fz;
    }
}
```

## 时间步稳定性验证

**来自 TheoryGuide.md + solver.md：**

InterfaceBond 引入额外刚度，会降低临界时间步：

```
dt_critical_bond = sqrt(m_min / Kn_max)

需满足：dtm × TimeStepRatio < min(dt_critical_FEM, dt_critical_DEM, dt_critical_bond)
```

验证步骤：
1. 估算 Kn（初始取值参考 Issue008 参数标定）
2. 估算最小颗粒质量 m_min
3. 计算 dt_critical_bond
4. 确保 inp 中 `*TimeStepSize` 倍率合理（初始用0.1）

## 测试方法

```
通过条件：
1. 力平衡验证：
   静止模型（FEM区+DEM区，无外载荷），开启InterfaceBond，
   运行100步后系统总动能 < 1e-10 J（接近零，无非物理力）

2. 稳定性验证：
   逐渐增大 TimeStepSize，从0.1到0.5，找到发散临界点，
   工作时间步应 < 临界值的80%

3. Ghost Force 初步检测：
   无外载荷情况下，界面处不平衡力 < 1e-6 × 施加荷载（量级检验）
```

## Review 要点

- [ ] 力是否注入到 `d1fnfx`（FEM节点）而非 `d1dnfx[fid]`（代理颗粒）
- [ ] FEM和DEM两侧力是否严格反向（`+=` vs `-=`）
- [ ] `user_to_MultiFracS` 而非 `user_solver` 中写入（来自 DeveloperGuide §3.3）
- [ ] dtm × Ratio < dt_critical_bond 验证是否完成

## 依赖

Issue005（Bond力已计算完毕存储在 cpuuser）
