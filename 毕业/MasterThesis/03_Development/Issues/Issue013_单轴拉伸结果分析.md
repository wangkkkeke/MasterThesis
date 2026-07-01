# Issue013：单轴拉伸杆结果分析与界面协调验证

**模块：** 后处理（Python + ParaView）
**状态：** OPEN
**优先级：** P1
**工作量：** 1-2天
**论文章节：** §4.3.3-4.3.6（结果图 + 对比分析）

---

## 任务描述

对 Issue012 完成的单轴拉伸算例进行结果分析：
- 提取界面处位移/速度/应力数据
- 与纯FEM参照模型对比
- 生成论文用图

## 需要生成的图（来自 FigureTablePlan.md）

| 图编号 | 内容 | 对应章节 |
|--------|------|---------|
| Fig_CH4_NO3 | FEM-DEM耦合 vs 纯FEM应力分布对比 | §4.3 |
| Fig_CH4_NO4 | 界面处位移时程曲线（两侧连续性） | §4.3 |
| Fig_CH4_NO5 | Ghost Force随时间变化 | §4.3 |

## 数据提取方案

### ParaView提取
```
1. 加载 vtk 序列
2. Plot Over Line：沿x轴（0~1m）提取 σxx 应力分布
3. 导出 CSV
```

### Python 分析脚本

```python
import numpy as np
import matplotlib.pyplot as plt

# 读取 Monitor Point CSV
data_fem = np.loadtxt("zMonitor-fem-side.csv", delimiter=",")
data_dem = np.loadtxt("zMonitor-dem-side.csv", delimiter=",")

# 界面处位移对比
plt.plot(data_fem[:,0], data_fem[:,3], label="FEM侧")
plt.plot(data_dem[:,0], data_dem[:,3], label="DEM侧")
plt.xlabel("时间 (s)")
plt.ylabel("位移 (m)")
plt.legend()
plt.savefig("Fig_CH4_NO4_界面位移连续性.png", dpi=300)
```

## 论文表格

**Table 4-1：单轴拉伸验证指标**

| 指标 | 纯FEM参照 | FEM-DEM耦合 | 误差 |
|------|-----------|------------|------|
| 端部位移 | — | — | — |
| 界面应力 | — | — | — |
| Ghost Force/P | — | — | — |
| 计算时间 | — | — | — |

（数值待计算完成后填写）

## 测试方法（后处理完整性）

```
通过条件：
1. 至少生成3张论文级图（300 DPI，白底）
2. 误差表格数据填写完整
3. 界面处位移连续性误差 < 2%
```

## Review 要点

- [ ] 图片保存为 PNG，300 DPI，路径：`06_Figures/CH4/`
- [ ] 图中轴标签和单位是否正确（SI制）
- [ ] 对比图中是否包含理论解或参照解（不能只有一条曲线）

## 依赖

Issue012（算例已运行完成，有结果数据）
