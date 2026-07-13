# Verification Report — Case03

**Title:** Global Sphere Embedding — Algorithm Capability Demonstration  
**Date:** 2026-07-13  
**Code:** `Prototype/verify/verify_case03.c`  
**Result:** **ALL PASSED (71 / 71)**

---

## 1. Purpose

Case01 / Case02 已完成力学闭环与多耦合对叠加验证。

Case03 **不再验证新力学公式**，而验证共生耦合的核心建模能力：

在整个连续构件域内自动生成 Sphere 后，算法能否自动完成：

1. Host Tet 搜索  
2. Region → Motion Mode 继承分类  
3. Bond 自动建立  

从而形成完整共生拓扑。

本阶段称为 **Algorithm Capability Demonstration**，不是新公式 Verification。

---

## 2. Classification Rule (Adjusted)

禁止按球心坐标直接指定类型。

必须：

```
Host Tet  ->  tet_region  ->  sphere_region / motion_mode
```

| Condition | Region | Motion |
|-----------|--------|--------|
| hostTet >= 0 and tet_region = FEM | FEM | PROXY |
| hostTet >= 0 and tet_region = DEM | DEM | FREE |
| hostTet < 0 (no covering tet) | DEM | FREE |

V9 专门检查该一致性。

---

## 3. Model Schematic

```
x: 0 -------- 1 -------- 2 -------- 3
   |  FEM     |   DEM    |   FEM    |
   |  (tets)  | (no tet) |  (tets)  |
   |  Proxy   |   Free   |  Proxy   |
```

- Left cube `[0,1]^3`：5 Tet，全部 `REGION_FEM`
- Right cube `[2,3]x[0,1]x[0,1]`：5 Tet，全部 `REGION_FEM`
- Middle `(1,2)`：无 Tet → Sphere 无 Host → `MOTION_FREE`

Regular packing：`R=0.12`，`spacing=0.24`，`rcut=0.26`

---

## 4. Pipeline

```
build mesh (FEM|DEM|FEM)
    -> sphere_generate() / sphere_generate_regular()
    -> sphere_find_host_tet()     /* all spheres */
    -> sphere_classify()          /* HostTet -> Region -> Mode */
    -> bond_search_neighbor()     /* O(N^2), no Cell List */
    -> bond_create()
    -> VTK / CSV
```

---

## 5. Statistics

| Quantity | Value |
|----------|-------|
| Sphere | 192 |
| Proxy | 128 |
| Free | 64 |
| Bond (all pairs < rcut) | 464 |
| Boundary Bond (Proxy–Free) | 32 |
| Isolated Sphere | 0 |

---

## 6. Verification Items

| ID | Item | Result |
|----|------|--------|
| V1 | Sphere Generation count | PASS (192=192) |
| V2 | Classification Proxy/Free | PASS (128/64) |
| V3 | Host Tet + N for sampled Proxy | PASS |
| V4 | sum Ni = 1 | PASS |
| V5 | Bond Generation count | PASS |
| V6 | Boundary Bond exists | PASS (32) |
| V7 | Connectivity (no isolated / bad) | PASS |
| V8 | VTK visualization | PASS (`output/case03.vtk`) |
| V9 | Region Consistency | PASS (bad=0) |

容差：1e-12。完整数据：`output/verify_case03.csv`。

---

## 7. Visualization

`output/case03.vtk`：

- Proxy：蓝色 RGB (0,0,1)
- Free：红色 RGB (1,0,0)
- Bond：Line cells
- Tet：Tetra cells

可用 ParaView 直接观察 FEM|DEM|FEM 共生网络与界面 Bond。

`output/case03.csv`：逐球坐标、mode、region、hostTet、N1–N4。

---

## 8. Error Analysis

- 生成数量与理论格子公式一致（误差 0）。
- 分类数量与「Host Tet ∈ FEM」计数一致（误差 0）。
- 抽样 Proxy 的 N 与独立 barycentric 重算一致。
- V9：全部 Sphere 的 Motion Mode 与 Host Tet Region 继承规则一致。
- 界面 Proxy–Free Bond 自动出现（32 条），证明分区共生拓扑成立。

---

## 9. Conclusion

Case03 **通过**。

算法已具备：

1. 全域规则布球  
2. Host Tet → Region → Motion 自动分类  
3. O(N²) 自动建 Bond  
4. 界面耦合边自然形成  
5. 无孤立球、VTK 可显示完整拓扑  

**未实现（保持冻结）：** Cell Linked List、断裂、接触、波传播、完整 FEM 动力学求解、DEM 大规模优化。

允许进入 Case04（三分区梁 / 后续加载与传播）前，仍按规范逐步扩展。

---

## 10. Reproduce

```text
proto_verify_case03.exe
# or: make verify_case03
```

Exit code `0` = ALL PASSED.

Regression: Case01 (33 PASS), Case02 (70 PASS) 在本轮接口调整后仍通过。
