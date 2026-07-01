# Issue010：InterfaceBond VTK 输出扩展

**模块：** User_solver / User_postprocess.c
**状态：** OPEN
**优先级：** P2
**工作量：** 1天
**论文章节：** §3.5 MultiFracS平台集成与计算流程（论文图幅：键力可视化）

---

## 任务描述

在 `Output_vtk_user()` 中输出 InterfaceBond 的可视化数据：
- 每条 Bond 作为线段（VTK LINES）
- 颜色编码 Bond 状态（完整/断裂）和 Fn 大小

## 输出格式（VTK Legacy ASCII）

```vtk
# vtk DataFile Version 3.0
InterfaceBond Output Step XXXX
ASCII
DATASET UNSTRUCTURED_GRID

POINTS n_ibond*2 float
x_fem0 y_fem0 z_fem0
x_dem0 y_dem0 z_dem0
x_fem1 y_fem1 z_fem1
x_dem1 y_dem1 z_dem1
...

CELLS n_ibond n_ibond*3
2 0 1
2 2 3
...

CELL_TYPES n_ibond
[n_ibond 个 3（VTK_LINE）]

CELL_DATA n_ibond
SCALARS Fn float 1
LOOKUP_TABLE default
Fn_0 Fn_1 ...

SCALARS broken int 1
LOOKUP_TABLE default
0 1 0 ...
```

## 实现位置

`User_postprocess.c` — `Output_vtk_user()`：

```c
void Output_vtk_user(CPUUSER cpuuser, long long nhstep) {
    char fname[200];
    sprintf(fname, "result/ibond-%lld.vtk", nhstep);
    FILE* fp = fopen(fname, "w");

    // 写 VTK HEADER + POINTS + CELLS + CELL_DATA
    ...

    fclose(fp);
}
```

## 测试方法

```
通过条件：
1. 输出的 vtk 文件能在 ParaView 中打开（无格式错误）
2. Line 单元连接 FEM 侧和 DEM 侧颗粒位置正确
3. 颜色标量：完整Bond（broken=0）和断裂Bond（broken=1）可区分
4. 断裂后的步数中断裂Bond显示为另一颜色
```

## Review 要点

- [ ] VTK 文件名是否包含步号（nhstep），防止覆盖
- [ ] POINTS 数量是否等于 n_ibond×2
- [ ] `fopen` 返回值是否检查非 NULL
- [ ] 每步都重写（覆盖），而非追加

## 依赖

Issue006（力计算完成，cpuuser 中有 Fn 和 broken 数据）
