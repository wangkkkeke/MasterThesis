# Benchmark-2 — Single Tetrahedron + Single Sphere

> 物理验证（`verify_case=0`）| Level-2 R2 面质心 + 形函数分配  
> 前置：Benchmark-1（CPS3 / Level-1）已归档

---

## 1. 目标

在 **1×C3D4 四面体 + 1 球** 最小算例上，复用 Benchmark-1 的 Test0–4，验证：

| 项 | 内容 |
|----|------|
| 几何 | 真实 3D 四面体（非 CPS3 代理） |
| 表示 | R2 面质心锚点，\(N_i=1/3\) 分配到界面节点 2,3,4 |
| 力学 | \(F_n=K_n\Delta u_n\)、力守恒、超 `rcut` 不建键 |
| 输出 | VTK：四面体、界面三角、球、键连线、节点力箭头 |

---

## 2. 几何

| 节点 | 坐标 | 角色 |
|------|------|------|
| 1 | (0, 0, 0) | 固定 |
| 2 | (L, 0, 0) | 界面 |
| 3 | (L, H, 0) | 界面 |
| 4 | (L, 0, H) | 界面 |

- `L=H=0.05` m，界面法向 **+x**
- 球心：界面质心 + `d0=0.01` m → `(0.06, H/3, H/3)`
- `Kn=1e8` N/m，`rcut=0.02` m

---

## 3. Test 列表（同 Benchmark-1）

| Test | test_id | 说明 |
|------|---------|------|
| 0 | 0 | 初始化 / identify |
| 1 | 1 | 法向 +1 mm |
| 2 | 2 | 超 rcut |
| 3 | 3 | 反向 −1 mm |
| 4a | 40 | 球 +1 mm |
| 4b | 41 | 锚 −1 mm（相对运动等价） |

---

## 4. 运行

```bash
python Scripts/build_benchmark2_inp.py
# 复制 Input/benchmark2_testN.inp + User_solver.dll 到 Source/2025-12-14/
# 删除 ibond_verify_case.txt
MultiFracS.exe benchmark2_test0.inp
```

输出：`output/benchmark2_testN.vtk`、`benchmark2_testN_log.txt`

inp 关键字：`*Benchmark2`（非 `*Benchmark1`）

---

## 5. 通过判据

| 指标 | 判据 |
|------|------|
| Bond 数 | Test 0/1/3/4：1；Test 2：0 |
| 力本构 | \(\|F_n-K_n\Delta u_n\|/\|K_n\Delta u_n\|<10^{-6}\) |
| 力守恒 | \(\|\mathbf F_{FEM}+\mathbf F_{Particle}\|<10^{-6}\) |
| 形函数分配 | \(\sum_i N_i\mathbf F_{node,i}=\mathbf F_{face}\) |
| Test 4 | 4a 与 4b 同 \(\Delta u_n\)、同 \(F_n\) |

---

## 6. 与 Benchmark-1 区别

| | Benchmark-1 | Benchmark-2 |
|---|-------------|-------------|
| FEM | CPS3 三角 | C3D4 四面体 |
| 表示 | R1 单节点 | R2 面质心 |
| 力分配 | 单锚点 | 形函数 → 3 界面节点 |
| inp 标签 | `*Benchmark1` | `*Benchmark2` |
