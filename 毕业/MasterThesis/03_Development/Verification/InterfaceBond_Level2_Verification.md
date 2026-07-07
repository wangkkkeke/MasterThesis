# InterfaceBond Level-2 验证报告 — Interface Representation

> 状态：**已归档**（M4-A + M4-B）  
> 版本：v1.0 | 2026-07-07  
> 路径：`03_Development/Verification/InterfaceBond_Level2_Verification.md`  
> 设计依据：`03_Development/Design/InterfaceBond_Level2.md`

---

## 1. 验证目标

M4 验证 **FEM 界面表示（Interface Representation）** 从 R1（Node）升级到 R2（Face Centroid）：

| 子阶段 | 内容 |
|--------|------|
| M4-A | 质心 `FaceForce` 计算，暂不分配节点 |
| M4-B | \(\mathbf F_{node,i} = N_i \mathbf F_{face}\)，力守恒 |

单 Bond 力学 \(F_n = K_n \Delta u\) 未改；M2/M3 回归保持通过。

---

## 2. 验证环境

| 项目 | 取值 |
|------|------|
| MultiFracS | 6.4.80 |
| 算例 | `minimal_coupling.inp` |
| R2 面单元 | CPS3 elem 60，节点 36/42/41 |
| `Kn` | `1×10⁸` N/m，`rcut=0.02` m |
| 形函数 | 质心处 `N_i = 1/3` |

---

## 3. 验证 Case 结果

| Case | `verify_case` | 预期 | 实测 | 结论 |
|------|---------------|------|------|------|
| **I** | 9 | `nibond=1`，R2 面键 | `representation=R2`，`nibond=1` | 通过 |
| **J** | 10 | `Σ F_node = F_face` | `FaceForce=-1e5`，`sum_NodeForce=-1e5` | 通过 |
| **K** | 11 | `F_face ∥ n`，\|Fn\|=1e5 | `FaceForce=(-1e5,0,0)`，`dun=1mm` | 通过 |

### Case J 明细（力守恒）

| 节点 | `N_i` | `F_node,x` |
|------|-------|------------|
| 36 | 1/3 | `-3.333×10⁴` N |
| 42 | 1/3 | `-3.333×10⁴` N |
| 41 | 1/3 | `-3.333×10⁴` N |
| **求和** | 1.0 | **`-1.000×10⁵` N** |

---

## 4. 回归

M2（1–3）、M3（5–8）、M4（9–11）在改码后均应通过。

---

## 5. Milestone

| Milestone | 状态 |
|-----------|------|
| M4 Interface Representation | **已完成**（R2 Face Centroid + 形函数分配） |
| M5 Real DEM Coupling | **Next**（Data Source Transition，见 `InterfaceBond_Level3.md`） |

---

## 6. 结论

**Interface Representation（R2）已完成 M4-A/M4-B 验证。** 面质心识别、`FaceForce` 计算及形函数分配满足力守恒；论文可表述为 FEM 界面表示升级，而非改动键力本构。
