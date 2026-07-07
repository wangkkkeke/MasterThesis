# InterfaceBond Level-0 验证报告

> 状态：**已归档**  
> 版本：v1.0 | 2026-07-07  
> 路径：`03_Development/Verification/InterfaceBond_Level0_Verification.md`  
> 设计依据：`03_Development/Design/InterfaceBond_Level0.md`（v1.1 冻结）  
> 算例：`04_VerificationCases/00_MinimalFEMDEM/Input/minimal_coupling.inp`

---

## 1. 验证目标

本报告验证 InterfaceBond **Level-0** 最小实现中下列三个核心环节是否正确：

| 环节 | 函数 | 验证内容 |
|------|------|----------|
| 识别与建键 | `ibond_identify()` | 界面节点选取、`rcut` 截断、`nibond` 与 Bond 表 |
| 力计算 | `ibond_compute_forces()` | 法向弹簧 `Fn = Kn · dun`、作用-反作用 |
| 力施加 | `ibond_apply_forces()` | FEM 端写入 `d1dnfx/y/z`（mock 模式） |

**验证意义：** 此前工作主要验证 User Solver 平台链路（DLL 加载、`CPUCORE` 字段、`preprocess` 参数链）。Level-0 是 **InterfaceBond 创新算法第一次脱离平台、可独立回归验证** 的节点。

---

## 2. 验证环境

| 项目 | 取值 |
|------|------|
| MultiFracS 版本 | **6.4.80** |
| 运行目录 | `02_MultiFracS/Source/2025-12-14/` |
| 算例 | `minimal_coupling.inp`（`CalulationType=1`） |
| FEM 几何 | 平面应力柱，`x∈[0,0.05]` m，`y∈[0,0.10]` m，网格 0.01 m |
| Level-0 拓扑 | 1 个界面节点（BondAnchor）↔ 1 个 MockSphere |
| MockSphere 默认中心 | `(0.06, 0.05, 0.10)` m（Case C 时改为 `x=1.0`） |
| 界面法向 | `+x` |
| `Kn` | `1×10⁸` N/m |
| `Kt` | `4×10⁷` N/m（Level-0 未使用切向力） |
| `rcut` | `0.02` m |
| 实测 FEM 规模 | `nfn=66`，`ndn=300`，`nsph=0` |

**代码模块：** `User_solver/InterfaceBond/`（`ibond_init.c`、`ibond_kinematics.c`、`ibond_force.c`、`ibond_apply.c`），由 `User_solve.c` 薄调度。

---

## 3. 四个验证 Case

切换方式：在运行目录放置 `ibond_verify_case.txt`，写入 `1`/`2`/`3`/`4`（或 `0` 表示正常模式）；`preprocess` 读取后调用 `ibond_config_mock()`。无需重编译。

```text
# 回归测试（约 1 分钟）
echo 1 > ibond_verify_case.txt && MultiFracS.exe minimal_coupling.inp
echo 2 > ibond_verify_case.txt && MultiFracS.exe minimal_coupling.inp
echo 3 > ibond_verify_case.txt && MultiFracS.exe minimal_coupling.inp
```

### 3.1 结果汇总（论文可引用）

| Case | 内容 | 预期 | 实测 | 结论 |
|------|------|------|------|------|
| **A** | 球沿法向 +1 mm，节点固定 | `\|Fn\| ≈ Kn×1 mm = 1×10⁵ N` | `femF_x = -1.0×10⁵ N`，`\|Fn\| = 1.0×10⁵ N` | 通过 |
| **B** | 节点沿法向 +1 mm，球固定 | 与 Case A 相同 `\|Fn\|` | `femF_x = +1.0×10⁵ N`，`\|Fn\| = 1.0×10⁵ N` | 通过 |
| **C** | 球心距界面 `dist > rcut` | `nibond = 0`，无力输出 | `dist = 0.95 m`，`nibond = 0` | 通过 |
| **D** | 默认几何，`dist < rcut` | `nibond = 1`，识别日志可查 | `dist = 0.01 m`，`nibond = 1`，锚点节点 36 | 通过 |

### 3.2 补充说明

**Case A / B**

- `verify_case = 1` 或 `2` 时，运动学层 **仅使用规定位移**（不叠加 FEM 背景位移），以满足设计文档 §6 手算核对要求。
- Case A 与 B 的 `\|Fn\|` 相对误差为 0%；符号相反，符合相对位移定义 `du = u_sphere - u_anchor`。
- 作用-反作用：`|f_fem + f_dem| = 0`（数值上为零）。

**Case C**

- `verify_case = 3` 将 MockSphere 置于 `(1.0, 0.05, 0.10)`，最近界面节点仍为 36，但 `dist = 0.95 > rcut = 0.02`，正确跳过建键。

**Case D**

- `verify_case = 0`（默认）使用 FEM 实际节点位移计算相对位移；首步 `\|Fn\| ≈ 5×10⁶ N`（对应 `dun ≈ 0.05 m`），来自 `d1dncx - d1fnix` 的 FEM 状态，非 Case A/B 的规定位移测试。

### 3.3 关键日志摘录

```text
[ibond_identify] nibond=1 anchor node_id=35 (1-based 36)    # Case D
[ibond_apply] bond[0] femF=(-1.000e+05,...) demF=(1.000e+05,...)  # Case A
[ibond_identify] dist > rcut -> nibond=0 (Case C ok).       # Case C
```

输出文件：`ibond_identify_status.txt`、`user_preprocess_done.txt`。

---

## 4. 回归测试约定（长期保留）

| `ibond_verify_case` | 模式 | 用途 |
|---------------------|------|------|
| `0` | 正常算法 | 使用 FEM 实际位移 + MockSphere 配置 |
| `1` | Case A | 回归：球 +1 mm |
| `2` | Case B | 回归：`dev_anchor_ux = 0.001` m |
| `3` | Case C | 回归：`rcut` 外不建键 |
| `4` | Case D 显式 | 与 `0` 同几何，可用于识别专项测试 |

**约定：** 每次修改 `InterfaceBond/` 或 `User_solve.c` 后，依次运行 Case 1、2、3，确认 `nibond` 与 `\|Fn\|` 未退化。

---

## 5. 项目里程碑（截至 2026-07-07）

| 里程碑 | 内容 | 状态 |
|--------|------|------|
| **Milestone 1** | Interface 接口验证（User Solver + 参数链） | 已完成 |
| **Milestone 2** | Single Bond Verification（Level-0，Case A/B/C/D） | **已完成** |
| **Milestone 3** | **Bond Management**（Level-1，BondManager，Case E/F/G/H） | 下一步 |
| **Milestone 4** | Surface/Particle Coupling（Level-2 面质心） | 待定 |
| **Milestone 5** | Real DEM Coupling（Level-3，Particle real） | 待定 |

---

## 6. 结论

**InterfaceBond Level-0 已完成最小验证。**

识别、法向弹簧力计算与力施加在四个 Case 下均符合设计预期；`verify_case` 机制已固化为长期回归测试入口。下一阶段为 **Milestone 3：Bond Management（Level-1）**——在单 Bond 力学不变前提下，验证 `BondTable` 的多键识别、循环、力汇集、删除与重复识别；详见 `Design/InterfaceBond_Level1.md`。Level-2/3 分别为几何升级与 DEM 数据源替换。

---

## 附录：相关文档

| 文档 | 路径 |
|------|------|
| Level-0 设计（冻结） | `03_Development/Design/InterfaceBond_Level0.md` |
| 最小算例说明 | `04_VerificationCases/00_MinimalFEMDEM/提醒.txt` |
| 项目 Level 路线图 | `00_Project/ProjectRoadmap.md` § InterfaceBond Level |
