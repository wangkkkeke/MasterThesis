# Issue011：悬臂梁纯 FEM 算例建模与计算

**模块：** Gmsh + inp配置 + Ce3D.dll
**状态：** OPEN
**优先级：** P1
**工作量：** 2天
**论文章节：** §4.2 悬臂梁算例（显式FEM几何非线性精度，对比Abaqus）

---

## 任务描述

建立悬臂梁纯FEM模型，验证 Ce3D（四面体）单元在显式动力学下的精度：
- 端点挠度与理论解（Euler-Bernoulli梁）对比
- 根部应力与理论解对比
- 与 Abaqus 静力学结果对比

## 几何参数

```
梁尺寸：L × b × h = 1m × 0.1m × 0.1m（典型参数，可按开题报告调整）
加载：端面集中荷载 P = E × I × δ / L³（反算，使挠度约为 L/100 = 0.01m）
边界：左端面完全固定（FixBoundary，x/y/z方向速度=0）
荷载：右端面 SForceBoundary，z方向集中力
```

## 理论解

```
端点挠度：δ = PL³ / (3EI)
根部应力：σ = M×c/I = P×L×(h/2) / I
I = b×h³/12
```

## Gmsh 建模要点（来自 DevelopmentHistory.md 踩坑记录）

```
1. 建 1m×0.1m×0.1m Box
2. Physical Volume → "rock"（材料组名）
3. Physical Surface 左端面 → "fix"（固定边界组）
4. Physical Surface 右端面 → "load"（荷载边界组）
5. 全局单元尺寸：0.02m（5个单元/每维）
6. 导出 .inp 格式

注意：
- CCW（逆时针）建面，法向量指向外（否则面力方向反）
- Physical Group 名称与 inp 中完全一致
```

## inp 配置

```
*Material, name=rock, type=Ce3D
E nu rho damp_n damp_s
2e10 0.25 2500 0.3 0.3

*FixBoundary
fix

*SForceBoundary, type=1
load

*TimeStepSize
0.1

*Begin
*solve
*End

*MonitorPoint
1.0 0.05 0.05    ← 梁端中心节点（精确坐标）
```

## 测试方法

```
通过条件：
1. 端点挠度误差 < 5%（对比理论解）
2. 根部正应力误差 < 5%（压上表面负，拉下表面正）
3. 与 Abaqus C3D4 静力结果误差 < 5%

输出：
- MonitorPoint 时程曲线（位移）收敛到稳定值
- ParaView 查看应力云图（σzz 分量）
```

## Review 要点

- [ ] Physical Group 名称是否与 inp 完全一致
- [ ] Monitor Point 坐标是否落在网格节点上
- [ ] Ce3D 中压应力为负（Bug001 历史教训）
- [ ] SBoundary 返回力（N），已乘以面积份额
- [ ] 单位全部 SI（Pa, kg, m, s）

## 依赖

无（此Issue可与InterfaceBond开发并行）
论文依赖：此算例用于 §4.2，需在 Issue012 之前完成
