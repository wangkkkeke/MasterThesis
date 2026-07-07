# Benchmark-1 预期结果与记录表

> 配套：`README.md`  
> 参数：\(K_n = 10^8\) N/m，\(r_{cut} = 0.02\) m，\(d_0 = 0.01\) m（Test 2 除外）

---

## 1. 手算基准

### Test 1 / Test 3（\(\Delta u_n = \pm 1\) mm）

\[
F_n = K_n \cdot \Delta u_n = 10^8 \times 10^{-3} = 10^5 \ \text{N}
\]

| Test | 球 [mm] | 锚 [mm] | \(\Delta u_n\) [mm] | \(F_n\) [N] | FEM 端 | Particle 端 |
|------|---------|---------|---------------------|-------------|--------|-------------|
| 1 | +1.0 | 0 | +1.0 | +1.0e5 | \(-10^5\) | +1.0e5 |
| 3 | −1.0 | 0 | −1.0 | −1.0e5 | +1.0e5 | −1.0e5 |

### Test 4 — Relative Motion Equivalence（相同 \(\Delta u_n\)）

\(\Delta u_n = u_{particle} - u_{anchor}\)。4a 球动、4b 锚动，**相对位移相同**则 \(F_n\) 相同。

| Test | 球 [mm] | 锚 [mm] | \(\Delta u_n\) [mm] | \(F_n\) [N] | FEM 端 | Particle 端 |
|------|---------|---------|---------------------|-------------|--------|-------------|
| 4a | +1.0 | 0 | +1.0 | +1.0e5 | 同 Test 1 | 同 Test 1 |
| 4b | 0 | −1.0 | +1.0 | +1.0e5 | 同 Test 1 | 同 Test 1 |

### Test 0

| 量 | 预期 |
|----|------|
| \(\Delta u_n\) | 0 |
| \(F_n\) | 0 |
| \(\Sigma F\) | 0 |

### Test 2（\(d > r_{cut}\)，方案 A）

| 量 | 预期 |
|----|------|
| Bond Active | No |
| nibond | 0 |
| \(F_n\) | N/A（无键） |

---

## 2. 记录表模板（论文用）

### Test N 运行记录

| 字段 | 手算 | 程序 | 相对误差 | 通过 |
|------|------|------|----------|------|
| Bond Active | | | — | |
| Distance \(d\) [m] | | | | |
| \(\Delta u_n\) [m] | | | | |
| \(F_n\) [N] | | | | |
| FEM Force (N) | | | | |
| Particle Force (N) | | | | |
| \(\|\Sigma F\|\) [N] | 0 | | | |

**通过：** 满足 `README.md` §7 全部判据。

---

## 3. 汇总表（答辩 / 论文 Table）

| Test | 名称 | 预期 nibond | 预期 \(\|F_n\|\) [N] | 状态 |
|------|------|-------------|----------------------|------|
| 0 | Initialization | 1 | 0 | 待跑 |
| 1 | Normal Loading | 1 | 1.0e5 | 待跑 |
| 2 | Beyond rcut | 0 | — | 待跑 |
| 3 | Reverse Loading | 1 | 1.0e5 | 待跑 |
| 4a | Rel. Motion（球动） | 1 | 1.0e5 | 待跑 |
| 4b | Rel. Motion（锚动） | 1 | 1.0e5 | 待跑 |

---

## 4. 与软件验证对照

| 软件 Case | Benchmark 对应 | 区别 |
|-----------|----------------|------|
| Level-0 Case A | Test 1 | mock 球 vs 真实 DEM |
| Level-0 Case C | Test 2 | 同方案 A |
| Level-0 Case B | Test 4b 部分 | mock 规定位移 vs 真实 FEM 运动 |
| M5 Case O | Benchmark 全流程 | Benchmark 含手算与论文表格 |

---

## 5. 实测填写区（完成后更新）

```
日期：
平台：MultiFracS _____ / User_solver _____
nsph：
nibond（Test0）：
F_n（Test1）：
nibond（Test2）：
F_n（Test3）：
F_n（Test4a）= F_n（Test4b）：
回归 verify_case：通过 / 未通过
结论：通过 / 未通过
```
