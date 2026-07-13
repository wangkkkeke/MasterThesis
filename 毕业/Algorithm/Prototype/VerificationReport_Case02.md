# Verification Report — Case02

**Title:** Multi-Coupling Pair Verification（多耦合对验证）  
**Date:** 2026-07-13  
**Code:** `Prototype/verify/verify_case02.c`  
**CSV:** `Prototype/output/verify_case02.csv`  
**Tolerance:** abs ≤ 1e-12 or rel ≤ 1e-12  
**Result:** **ALL PASSED (70 / 70)**

---

## 1. Purpose

唯一目标：验证算法从 Case01「单耦合对」扩展到「多耦合对」后，力的叠加、映射叠加与整体守恒仍然成立。

本 Case **不验证**：邻域搜索、自动布球、复杂几何、断裂、接触、波传播、梁模型、完整 FEM 中心差分。

---

## 2. Model Schematic (ASCII)

```
           P1 (id=0, MOTION_PROXY)
          /    \
        B1      B2
        /        \
     F1 (1)     F2 (2)     MOTION_FREE
        \        /
        B3      B4
          \    /
           P2 (id=3, MOTION_PROXY)
```

F1–F2 仅为布局示意，**无** Free–Free Bond。

### 2.1 Sphere Index

| ID | Name | Mode | Region | Initial Position (before stretch) |
|----|------|------|--------|-----------------------------------|
| 0 | P1 | PROXY | FEM | (0.40, 0.40, 0.40) |
| 1 | F1 | FREE | DEM | (1.20, 0.40, 0.40) |
| 2 | F2 | FREE | DEM | (1.20, 0.90, 0.40) |
| 3 | P2 | PROXY | FEM | (0.50, 0.30, 0.50) |

验证前对 Free 施加受控拉伸：F1→(1.50,0.40,0.40)，F2→(1.50,1.00,0.40)，使全部 Bond 产生非零力。

### 2.2 Bond Index

| Bond | Endpoints | Type | Kn | L0 (at create) |
|------|-----------|------|-----|----------------|
| B1 | P1–F1 | Proxy–Free ACTIVE | 1000 | 0.800000 |
| B2 | P1–F2 | Proxy–Free ACTIVE | 1000 | 0.943398 |
| B3 | F1–P2 | Proxy–Free ACTIVE | 1000 | 0.714143 |
| B4 | F2–P2 | Proxy–Free ACTIVE | 1000 | 0.927362 |

### 2.3 Host Tet

单 Tet：节点 (0,0,0), (2,0,0), (0,2,0), (0,0,2)。

| Proxy | hostTet | N1 | N2 | N3 | N4 |
|-------|---------|----|----|----|-----|
| P1 | 0 | 0.40 | 0.20 | 0.20 | 0.20 |
| P2 | 0 | 0.35 | 0.25 | 0.15 | 0.25 |

两 Proxy 共享同一 Tet，用于验证 **Multi-Proxy Mapping 叠加**。

---

## 3. Verification Items

| ID | Item | What is checked |
|----|------|-----------------|
| V1 | Shape Function | 回归：`u = Σ Ni ui` |
| V2 | Sphere Force | `F_sphere = Σ F_bond`（逐球） |
| V3 | Proxy Reaction | `R_proxy = Σ F_bond→proxy` |
| V4 | Node Force Mapping | 单 Proxy：`Fi = Ni R` |
| V5 | Multi-Proxy Mapping | `Fi = N_i^{P1} R^{P1} + N_i^{P2} R^{P2}` |
| V6 | Action-Reaction | 每条 Bond：`F_AB = −F_BA`；全体球力矢量和为 0 |
| V7 | Global Force | `Σ F_sphere = 0`；`Σ F_node = Σ R_proxy` |
| V8 | Bond Independence | 删除任意一条 Bond 后，其余 Bond 的 `fn` 不变 |

---

## 4. Theory (summary)

### Bond force (normal spring)

\[
L=\|x_A-x_B\|,\quad
n=\frac{x_A-x_B}{L},\quad
F_n = K_n(L-L_0)
\]

\[
F_A = -F_n\, n,\quad F_B = +F_n\, n
\]

### Sphere force superposition

\[
F^{(s)} = \sum_{b\ni s} F^{(b\rightarrow s)}
\]

### Mapping

\[
F_i += N_i\, R_{\mathrm{proxy}}
\]

多 Proxy：

\[
F_i = N_i^{P1} R^{P1} + N_i^{P2} R^{P2}
\]

### Bond independence

`bond_compute_force` 对每条 ACTIVE Bond 仅依赖其两端坐标与 `Kn,L0`，与其它 Bond 的力无关。删除 Bond \(k\) 后，其余 Bond 的 `fn` 应与全系统时相同。

---

## 5. Program Output (key numbers)

| Quantity | Value |
|----------|-------|
| P1 Reaction Rx, Ry, Rz | 571.795, 148.252, 0 |
| P2 Reaction Rx, Ry, Rz | 535.705, 199.258, −53.571 |
| Σ Sphere Fx | 0 |
| Σ Node Fx (mapping) | 1107.500 (= Rx_P1 + Rx_P2) |
| V8 | 删除 B0..B3 各一轮，其余 `fn` 均不变 |

完整逐项数据见 `output/verify_case02.csv`。

---

## 6. Error Analysis

- 全部检查项：**AbsError = 0**，**RelError = 0**（双精度下与手算公式一致）。
- 容差 1e-12 全部满足。
- V5 证明两 Proxy 对同一节点的 Mapping 可正确累加（Case01 未覆盖）。
- V8 证明 Bond 之间无隐藏耦合。

---

## 7. Conclusion

Case02 — Multi-Coupling Pair Verification **通过**。

算法在多 Proxy、多 Free、多 Bond 条件下：

1. 力叠加正确；  
2. Proxy Reaction 叠加正确；  
3. 多 Proxy Mapping 叠加正确；  
4. 作用-反作用与全局力守恒成立；  
5. Bond 计算相互独立。

因此，允许进入后续 Case03（力传播 / 一排 Sphere）。本 Case **未**引入 Cell Linked List，也 **未**切换完整 `fem_step()`。

---

## 8. Reproduce

```text
# MSVC (example)
cl /std:c11 /Iinclude /D_CRT_SECURE_NO_WARNINGS /Fe:proto_verify_case02.exe ... verify\verify_case02.c
proto_verify_case02.exe

# or Makefile (gcc)
make verify_case02
./proto_verify_case02
```

Exit code `0` means ALL PASSED.
