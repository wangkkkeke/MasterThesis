# InterfaceBond Level-1 验证报告 — Bond Management

> 状态：**已归档**  
> 版本：v1.0 | 2026-07-07  
> 路径：`03_Development/Verification/InterfaceBond_Level1_Verification.md`  
> 设计依据：`03_Development/Design/InterfaceBond_Level1.md`（v1.1 冻结）  
> 前置：`InterfaceBond_Level0_Verification.md`（M2 已完成）

---

## 1. 验证目标

Level-1 不再关注单条 InterfaceBond 的力学正确性，而是验证 **InterfaceBond Bond Management Framework** 在多键条件下的工程管理能力：

- Identify（多键识别）
- CreateBond / BondTable 存储
- RemoveBond（删除与压缩）
- Re-Identify（唯一性，Case H）
- Force Accumulation（同节点多键力汇集）

单 Bond 力学（`Fn = Kn·dun`）沿用 Level-0 实现，本阶段 **未修改** `ibond_compute_forces()` 公式。

---

## 2. 验证环境

| 项目 | 取值 |
|------|------|
| MultiFracS | 6.4.80，`Source/2025-12-14` |
| 算例 | `minimal_coupling.inp` |
| 架构 | `BondManager` + `BondTable` + `Particle` |
| `Kn` | `1×10⁸` N/m |
| `rcut` | `0.02` m |
| 切换 | `ibond_verify_case.txt`（`5`–`8` 为 Level-1；`1`–`3` 为 M2 回归） |

---

## 3. 验证 Case 结果

### 3.1 Level-1 Case（论文可引用）

| Case | 内容 | 预期 | 实测 | 结论 |
|------|------|------|------|------|
| **E** | 3 Bond → 同一 Node36 | `ΣF = 3×10⁵ N` | `F_accum = (-3.0×10⁵, 0, 0)` | 通过 |
| **F** | 删除 `bond[1]` | `nibond = 2`，表可遍历 | `nibond=2`，无崩溃 | 通过 |
| **G** | 删除后 Re-Identify | `nibond` 恢复为 3 | 重建 3 条 Bond | 通过 |
| **H** | 连续两次 Identify | `nibond = 3`（非 6） | 第二次 `nibond=3` | 通过 |

### 3.2 M2 回归（改码后仍通过）

| Case | 预期 | 实测 | 结论 |
|------|------|------|------|
| A (`verify_case=1`) | `\|Fn\|=10⁵ N` | `femF_x=-10⁵` | 通过 |
| B (`verify_case=2`) | `\|Fn\|=10⁵ N` | `femF_x=+10⁵` | 通过 |
| C (`verify_case=3`) | `nibond=0` | `nibond=0` | 通过 |

### 3.3 关键日志

```text
[ibond_identify] CreateBond bond[0..2] node=36 particle=0..2
[ibond_identify] nibond=3 (created=3)
[ibond_apply] Case E accumulated node=36 F=(-3.000e+05,...)
[User_solver] after remove: nibond=2          # Case F
[User_solver] Case H: nibond=3 (expect 3, not 6)
```

---

## 4. 实现要点

| 模块 | 文件 | 职责 |
|------|------|------|
| 数据层 | `ibond_table.c` | 连续存储、增删、查重 |
| 逻辑层 | `ibond_manager.c` | Identify、CreateBond、Clear |
| 力汇集 | `ibond_apply.c` | 按 `node_id` 累加后写 `d1dnfx` |
| 粒子抽象 | `Particle` | 替代 `MockSphere`；Level-3 换 `is_mock=0` |

---

## 5. 回归测试约定

每次修改 `InterfaceBond/` 后：

```text
1 → 2 → 3    # M2 力学回归
5 → 6 → 7 → 8    # M3 Bond Management
```

约 2 分钟可完成全部检查。

---

## 6. Milestone

| Milestone | 状态 |
|-----------|------|
| M1 Interface 接口验证 | 已完成 |
| M2 Single Bond Verification | 已完成 |
| **M3 Bond Management** | **已完成** |
| M4 Surface/Particle Coupling | 下一步 |
| M5 Real DEM Coupling | 待定 |

---

## 7. 结论

**InterfaceBond Level-1 Bond Management Framework 已完成验证。**

多键识别、Bond 表连续存储、删除压缩、重复 Identify 唯一性及同节点力汇集均符合设计预期；M2 回归未退化。下一阶段为 **M4：Interface Representation**（见 `Design/InterfaceBond_Level2.md`），先 M4-A（FaceForce）再 M4-B（形函数分配）。
