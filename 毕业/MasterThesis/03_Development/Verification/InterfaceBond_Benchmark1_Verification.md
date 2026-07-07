# InterfaceBond Benchmark-1 验证报告 — CPS3 物理基准

> 状态：**已归档**  
> 版本：v1.0 | 2026-07-07  
> 路径：`03_Development/Verification/InterfaceBond_Benchmark1_Verification.md`  
> 规格：`04_VerificationCases/Benchmark01/README.md`

---

## 1. 验证目标

Benchmark-1 为 **物理验证**（`verify_case=0`），与软件验证 M0–M5 分离。在最小 CPS3 三角 + 合成颗粒（`nsph=0`）上验证：

- Bond 识别（`d0`、`rcut`）
- 法向键力 \(F_n = K_n \Delta u_n\)
- 超 `rcut` 不建键（方案 A）
- 反向加载力反号
- 相对运动等价（Test 4a/4b 同 \(\Delta u_n\) 同 \(F_n\)）

---

## 2. 验证环境

| 项目 | 取值 |
|------|------|
| MultiFracS | 6.4.80，`Source/2025-12-14` |
| 表示 | Level-1 R1（单界面节点锚点） |
| `Kn` | `1×10⁸` N/m |
| `rcut` | `0.02` m |
| `d0` | `0.01` m |
| 颗粒 | `*Benchmark1` 元数据合成（`nsph=0`） |

---

## 3. 测试结果（meta 模式）

| Test | test_id | nibond | \(\Delta u_n\) [mm] | \(F_n\) [N] | \(\Sigma F\) | 结论 |
|------|---------|--------|---------------------|-------------|--------------|------|
| 0 初始化 | 0 | 1 | 0 | 0 | 0 | 通过 |
| 1 法向加载 | 1 | 1 | +1 | +1.0e5 | 0 | 通过 |
| 2 超 rcut | 2 | 0 | — | — | — | 通过 |
| 3 反向加载 | 3 | 1 | −1 | −1.0e5 | 0 | 通过 |
| 4a 球动 | 40 | 1 | +1 | +1.0e5 | 0 | 通过 |
| 4b 锚动 | 41 | 1 | +1 | +1.0e5 | 0 | 通过 |

Test 4b 采用锚点位移 **−1 mm**（非 +1 mm），使 \(\Delta u = u_{球} - u_{锚} = +1\) mm，与 4a 等价。

---

## 4. 说明

- 日志 `status=PARTIAL_meta_only_need_real_DEM` 仅表示尚未接入真实 DEM（`nsph=0`），**不否定**上述力学核对。
- VTK 输出：`04_VerificationCases/Benchmark01/output/benchmark1_testN.vtk`
- 后续真实 FEM-DEM 端到端待团队提供 `nsph=1` inp。

---

## 5. 结论

**Benchmark-1（CPS3 / Level-1）六项测试在 meta 模式下全部通过。** 可作为论文物理验证第一节；三维四面体验证见 Benchmark-2。
