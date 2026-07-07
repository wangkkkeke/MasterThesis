# InterfaceBond Benchmark-2 验证报告 — C3D4 四面体 + 球

> 状态：**已归档**  
> 版本：v1.0 | 2026-07-07  
> 路径：`03_Development/Verification/InterfaceBond_Benchmark2_Verification.md`  
> 规格：`04_VerificationCases/Benchmark02_TetSphere/README.md`  
> 前置：`InterfaceBond_Benchmark1_Verification.md`（CPS3 / Level-1）

---

## 1. 验证目标

Benchmark-2 在 **1×C3D4 四面体 + 1 球** 最小算例上，复用 Benchmark-1 的 Test0–4，验证：

| 项 | 内容 |
|----|------|
| 几何 | 真实 3D 四面体（界面节点 2/3/4，法向 +x） |
| 表示 | Level-2 R2 面质心锚点 |
| 力分配 | \(F_{node,i} = N_i F_{face}\)，\(N_i = 1/3\) |
| 力学 | \(F_n = K_n \Delta u_n\)、力守恒、超 `rcut` 不建键 |
| 相对运动 | Test 4a/4b 同 \(\Delta u_n\) 同 \(F_n\) |

单 Bond 本构与 Benchmark-1 相同，**未修改** `ibond_compute_forces()` 公式。

---

## 2. 验证环境

| 项目 | 取值 |
|------|------|
| MultiFracS | 6.4.80，`Source/2025-12-14` |
| FEM | 1×C3D4，apex 节点 1 固定 |
| 界面 | 三角面 2–3–4，质心 \((0.05,\,H/3,\,H/3)\) |
| 球心 | \((0.06,\,H/3,\,H/3)\)，\(d_0 = 0.01\) m |
| `Kn` | `1×10⁸` N/m |
| `rcut` | `0.02` m |
| 颗粒 | `*Benchmark2` 元数据合成（`nsph=0`） |
| VTK | `Benchmark02_TetSphere/output/benchmark2_testN.vtk` |

---

## 3. 测试结果（meta 模式）

| Test | test_id | nibond | \(\Delta u_n\) [mm] | \(F_n\) [N] | \(\Sigma F\) | 形函数守恒 | 结论 |
|------|---------|--------|---------------------|-------------|--------------|------------|------|
| 0 初始化 | 0 | 1 | — | — | — | — | 通过 |
| 1 法向加载 | 1 | 1 | +1 | +1.0e5 | 0 | sum = FaceForce | 通过 |
| 2 超 rcut | 2 | 0 | — | — | — | — | 通过 |
| 3 反向加载 | 3 | 1 | −1 | −1.0e5 | 0 | sum = FaceForce | 通过 |
| 4a 球动 | 40 | 1 | +1 | +1.0e5 | 0 | 同 Test 1 | 通过 |
| 4b 锚动 | 41 | 1 | +1 | +1.0e5 | 0 | 与 4a 等价 | 通过 |

### Test 0（识别）

| 量 | 实测 |
|----|------|
| `ibond_level` | 2 |
| `nibond` | 1 |
| `d0` | 0.01 m |
| 界面节点 | 2, 3, 4 |
| `status` | OK_identify |

### Test 2（超 rcut）

| 量 | 实测 |
|----|------|
| `nibond` | 0 |
| Bond Active | No |
| 球心 | (1.0, H/3, H/3)，距质心 \(\gg r_{cut}\) |

### Test 1 形函数分配明细

\(F_{face} = (-10^5,\,0,\,0)\) N：

| 节点 | \(N_i\) | \(F_{node,x}\) [N] |
|------|---------|---------------------|
| 2 | 1/3 | −3.333×10⁴ |
| 3 | 1/3 | −3.333×10⁴ |
| 4 | 1/3 | −3.333×10⁴ |
| **求和** | 1 | **−1.0×10⁵** |

---

## 4. 与 Benchmark-1 对照

| | Benchmark-1 | Benchmark-2 |
|---|-------------|-------------|
| FEM 单元 | CPS3 三角 | C3D4 四面体 |
| 锚点 | R1 单节点 | R2 面质心 |
| 力写入 | 单锚点 | 形函数 → 3 界面节点 |
| inp 标签 | `*Benchmark1` | `*Benchmark2` |
| 力学结论 | 六项通过 | 六项通过 |

---

## 5. 说明

- `status=PARTIAL_meta_only_need_real_DEM` 仅表示 `nsph=0`，不否定力学核对。
- Test 0/2 输出 `*_setup.txt` 与 `*_log.txt`（identify only）；Test 1/3/4 输出完整 `*_log.txt`。
- 日志/VTK 统一目录：`04_VerificationCases/Benchmark02_TetSphere/output/`。
- 真实 FEM-DEM 端到端待团队提供 `nsph=1` inp。

---

## 6. 结论

**Benchmark-2（C3D4 / Level-2 R2）六项测试在 meta 模式下全部通过。**  
验证了四面体界面表示、面力形函数分配及与 Benchmark-1 一致的键力本构；可与 Benchmark-1 一并写入论文物理验证章节。
