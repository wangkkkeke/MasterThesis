# Issue009：Ghost Force 量化与消除

**模块：** User_solver + 测试算例
**状态：** OPEN
**优先级：** P1
**工作量：** 2天
**论文章节：** §3.3 显式动力学稳定性指标 + §2.4 Ghost Force既有认识

---

## 任务描述

量化 InterfaceBond 界面的 Ghost Force（非物理残差力），
提出消除/控制方法，并给出量化指标。

## Ghost Force 定义（来自 TheoryGuide.md）

```
Ghost Force：
在无外载荷的静止初始状态，FEM-DEM 界面不平衡力。

来源：
1. 刚度不匹配：FEM连续刚度 ≠ DEM离散等效刚度
2. 时间步不一致：FEM与DEM采用相同dt但波速不同
3. 颗粒尺寸 vs 单元尺寸不匹配

公式：
Ghost Force = Σ|F_interface_residual| / F_applied
可接受标准：< 1%（参考桥接域方法文献）
```

## 测量方案

```
算例设置：
1. FEM 块（如 1m×1m×0.2m，C3D4单元）+ DEM 层（一层颗粒）
2. 无外载荷，初始静止，InterfaceBond激活
3. 运行 100 步

测量：
在 user_solver() 中统计界面处不平衡力：
F_ghost = max(|d1fnfx[fnid]|) for fnid in 界面节点集合

对比：
当有 P 荷载时，Ghost Force / P 的比值
```

## 消除策略（按优先级）

| 策略 | 原理 | 代价 |
|------|------|------|
| 调整 Kn（Issue008）| 刚度匹配降低残差 | 需重新标定 |
| 增加 InterfaceBond 宽度 | 过渡区扩展平滑应力 | 影响精度 |
| 速度梯度平滑 | 代理颗粒插值更光滑 | 增加计算量 |
| 降低 TimeStepSize | 减少离散误差 | 增加计算时间 |

## DEM区宽度敏感性（§5.3 联动）

Ghost Force 与 DEM 区域宽度有关，这是 §5.3 模式I裂纹板的敏感性分析内容：

```
DEM区宽度：1d, 2d, 3d, 5d（d=颗粒直径）
测量每种配置的 Ghost Force
期望：宽度增大→Ghost Force减小→但计算量增加
```

## 测试方法

```
通过条件：
1. 无载荷算例，运行100步后 Ghost Force < 1% × E × ε0
2. DEM区宽度敏感性曲线至少3个数据点（单调趋势）
3. 最终采用的配置 Ghost Force < 1%
```

## Review 要点

- [ ] Ghost Force 测量点是否在界面处（而非体内）
- [ ] 比较基准是否合理（用后续施加的荷载量级）
- [ ] 消除方法是否记录到 §3.3 论文（量化结果写入Table 3-y）

## 依赖

Issue006（力注入完成），Issue008（Kn已初步确定）
