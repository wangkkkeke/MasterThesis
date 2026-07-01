# Issue012：单轴拉伸杆 FEM-DEM 耦合建模

**模块：** Gmsh + inp配置 + InterfaceBond
**状态：** OPEN
**优先级：** P1
**工作量：** 2天
**论文章节：** §4.3 单轴拉伸杆算例（连续响应与界面协调）

---

## 任务描述

建立单轴拉伸杆 FEM-DEM 耦合模型，
FEM 区域 + InterfaceBond 界面 + DEM 区域共存，
验证界面处位移/速度连续性，无 Ghost Force 发散。

## 几何设计

```
拉伸杆（x方向）：

|←—— FEM区（0~0.5m）——→|←—InterfaceBond—→|←—— DEM区（0.5~1.0m）——→|

尺寸：总长1m，截面0.1m×0.1m

FEM区（左半）：C3D4单元，网格尺寸0.02m
DEM区（右半）：DEM颗粒，半径0.01m
界面：FEM-DEM交界面，宽度约2个颗粒直径
```

## Gmsh 建模要点

```
FEM区：
- Physical Volume "fem_zone"
- Physical Surface 左端面 "fix"（固定）
- Physical Surface 右侧界面 "fem_interface"

DEM区：
- 由 MultiFracS 内部颗粒生成模块创建（不在Gmsh中建）
- 在 inp 中通过 *Particle 关键字指定（待查 inp格式）

界面识别：
- 依赖 i1sphfnid（Issue003完成后自动识别）
```

## inp 配置

```
*Material, name=rock, type=Ce3D
2e10 0.25 2500 0.3 0.3

*DEMMaterial, name=dem_rock
...（颗粒材料参数）

*FixBoundary
fix

*VBoundary, type=1
load_face    ← 右端面速度加载

*TimeStepSize
0.1

*Begin
*solve
*End

*MonitorPoint
0.5 0.05 0.05    ← 界面处节点
```

## 测试方法

```
通过条件：
1. 界面协调性：界面两侧位移连续（FEM侧 ≈ DEM侧，误差 < 2%）
2. 应力场对比：耦合模型应力场 vs 纯FEM参照模型，误差 < 5%
3. Ghost Force：界面处不平衡力 < 1% × 施加力
4. 稳定性：1000步内无发散

验证工况（来自 ThesisOutline.md §4.3）：
- 工况A：弹性段（低应变，无断裂）
- 工况B（可选）：拉断InterfaceBond，观察断裂界面
```

## Review 要点

- [ ] FEM区和DEM区材料参数是否一致（保证连续介质假设）
- [ ] 界面处网格尺寸与颗粒尺寸是否接近（减少Ghost Force）
- [ ] Monitor Point 在界面处，两侧各一个监测点

## 依赖

Issue006（InterfaceBond力注入完成），Issue008（Kn/Kt已初步确定）
