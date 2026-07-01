# Issue003：FEM-DEM 界面颗粒识别算法

**模块：** User_solver / ibond_init.c
**状态：** IN PROGRESS（2026-06-30 实现，待编译测试）
**优先级：** P0（InterfaceBond建立的前提）
**工作量：** 2天
**论文章节：** §3.2 InterfaceBond界面键力学模型（识别策略）

---

## 任务描述

在 `preprocess_cpuuser()` 中实现界面颗粒识别：
- 找出所有"FEM侧代理颗粒"（`i1sphfnid[id] >= 0` 的颗粒）
- 找出所有"DEM侧界面颗粒"（与代理颗粒距离 < 阈值）
- 建立 Bond 配对表（填充 i1ibond_fid / i1ibond_did）

## 关键源码依据

**来自 Cpucore.h：**
```c
int  nsph;           // 可以与FEM绑定的球数量
int* i1sphfnid;      // [ndn] 颗粒i绑定的FEM节点ID（-1表示纯DEM颗粒）
Real* d1dncx/cy/cz; // DEM颗粒当前坐标
Real* d1dncr;        // DEM颗粒半径
```

## 算法步骤

```
Step1：遍历所有 DEM 颗粒（id = 0..ndn-1）
       if (i1sphfnid[id] >= 0) → 记入 fem_side[] 列表

Step2：遍历所有 DEM 颗粒（id = 0..ndn-1）
       if (i1sphfnid[id] < 0) → 候选 dem_side[] 列表

Step3：对每个 fem_side 颗粒，遍历 dem_side 颗粒
       计算距离 dist = sqrt(dx²+dy²+dz²)
       if dist < (r_fem + r_dem) * bond_range_factor → 建立 Bond
       记录配对到 i1ibond_fid[], i1ibond_did[]

Step4：统计总 Bond 数 n_ibond，malloc 各历史数组，初始化为0
```

## 待确认项（影响算法）

> Issue001 注：i1sphfnid 的语义需在源码中确认（见 KnowledgeSummary.md）
> - 若 i1sphfnid[id] >= 0 即为代理颗粒 → 直接用上述算法
> - 若代理颗粒未显式存储 → 需改为按 FEM 边界面识别

## 测试方法

```
通过条件：
1. 简单 FEM-DEM 模型（一层FEM接一层DEM），运行后：
   n_ibond 输出值 == 预期界面颗粒对数（手动统计）
2. 无配对错误：i1ibond_fid/did 中的ID均在有效范围内
3. 每个 dem_side 颗粒至多配对一个 fem_side（无重复Bond）

验证模型：FEM块（4个C3D4单元）+ DEM层（4颗粒），
手动数出界面颗粒对数，对比程序输出 n_ibond
```

## Review 要点

- [ ] `i1sphfnid` 读取是否来自 cpucore（只读）
- [ ] `bond_range_factor` 是否作为可配置参数（不要硬编码）
- [ ] 数组访问是否在 `[0, ndn-1]` 范围内
- [ ] `n_ibond` 确定后才 malloc，preprocess 末尾执行

## 实现说明（2026-06-30）

**与原设计的偏差：**
1. `preprocess_cpuuser` 无 CPUCORE 参数，几何识别移至 `user_solver` 第一次调用时（static flag 保护）
2. `i1sphfnid` 实际按 `[nsph*(ndim+1)+k]` 索引（SPH单元→FEM节点），而非按 DEM 颗粒索引
3. FEM侧代理用 SPH 单元质心（4节点平均），而非单颗粒坐标

**新增文件：** `ibond_init.c`（`ibond_identify` 函数）

**inp 文件需添加：**
```
*InterfaceBond
Kn, Kt, ft, fs, phi, rcut
```

## 依赖

Issue001, Issue002
