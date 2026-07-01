# Issue016：模式 I 裂纹板建模与计算

**模块：** Gmsh + InterfaceBond + Cjoint3D
**状态：** OPEN
**优先级：** P1
**工作量：** 2-3天
**论文章节：** §5.3 模式I裂纹板算例（动态裂纹扩展 + 界面行为）

---

## 任务描述

建立含预制裂缝的矩形板 FEM-DEM 耦合模型：
- 中心水平预制裂缝（Notch）
- 上下端施加拉伸速度
- 观察 Mode I 裂纹扩展路径和速度
- 进行 DEM 区宽度敏感性分析

## 几何参数

```
板尺寸：W × H = 0.1m × 0.2m（宽×高），厚度 0.005m
预制裂缝：水平，长度 a = W/4 = 0.025m，位于中心
加载：上下端面 VBoundary，v = 1 m/s（动态加载）

分区方案：
  DEM区：中心区域（裂缝扩展路径），约 0.04m × 0.04m
  FEM区：其余区域
  InterfaceBond：两区域界面
```

## DEM 区宽度敏感性配置

**论文 §5.3 核心分析内容（Table 5-x）：**

| 工况 | DEM区宽度 | Ghost Force | KIC误差 | 计算时间 |
|------|---------|------------|---------|---------|
| W1 | 1d（1个颗粒直径）| — | — | — |
| W2 | 2d | — | — | — |
| W3 | 3d | — | — | — |
| W5 | 5d | — | — | — |

其中 d = 颗粒直径（约 0.002m）

## Gmsh 建模要点

```
1. 建 W×H 矩形板
2. 在中心线上添加一条水平线段（预制裂缝，长度 a）
3. 预制裂缝区域：Physical Line "notch"
4. DEM区：围绕裂缝的小矩形（Physical Volume "dem_zone"）
5. FEM区：其余体积（Physical Volume "fem_zone"）
6. 裂缝处节理单元：需要在 Gmsh 中明确建立（共面两个 Physical Surface）

注意：预制裂缝两面需要共节点（FEM断裂），或由Cjoint3D初始断裂状态设置
```

## KIC 计算（来自 FormulaIndex.md F-28）

```
KIC = σ_applied × sqrt(π × a) × F(a/W)

其中 F(a/W) = 几何修正因子（参考手册）
σ_applied = P / (W × t)
```

## 测试方法

```
通过条件：
1. 裂纹沿预制裂缝扩展方向（Mode I，水平）
2. KIC 误差 < 15%（对比理论解）
3. DEM区宽度敏感性分析完成（4个工况的Ghost Force和KIC）
4. 裂纹扩展速度在理论范围内（< 0.6 × Rayleigh波速）
```

## Review 要点

- [ ] 预制裂缝初始状态：`ijebk = 1`（已断裂）通过 FGM.dll 设置
- [ ] 加载速度是否满足准静态条件（如需）
- [ ] DEM区宽度参数化：4种工况只需改 DEM区尺寸，其余不变

## 依赖

Issue007（断裂准则），Issue009（Ghost Force量化方法），Issue008（Kn/Kt标定）
