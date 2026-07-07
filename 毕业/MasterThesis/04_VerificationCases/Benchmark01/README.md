# Benchmark-1：Single Tetrahedron – Single Sphere Interface Verification

> 类型：**物理验证（Physical Verification）/ Reference Benchmark**  
> 版本：v1.0 | 2026-07-07  
> 状态：**Step-1 完成（identify only + VTK）**  
> 平台：MultiFracS 6.4.80（`Source/2025-12-14`），`CalulationType=1`

---

## 1. 定位

Benchmark-1 是论文中的**标准参考算例**，用于验证 InterfaceBond 方法的**物理意义**，不用于软件开发回归。

| 体系 | 路径 | 职责 |
|------|------|------|
| **软件验证** | M0–M5，`verify_case` 1–23 | 代码有没有写错 |
| **物理验证** | **Benchmark-1**（本文） | 物理模型对不对 |

**二者不混用：** Benchmark-1 使用 `verify_case=0`（正常模式）+ 专用 inp，**不**通过 `ibond_verify_case.txt` 切换。

论文表述建议：

> 本文首先采用 Benchmark-1 对所提出的 InterfaceBond 方法进行验证，然后再应用于复杂算例。

---

## 2. 验证目标

Benchmark-1 **不**验证整个 MultiFracS，仅验证：

| 编号 | 内容 |
|------|------|
| V1 | 界面识别（Interface Identification） |
| V2 | 界面键本构（Bond Constitutive Law）：\(F_n = K_n \Delta u_n\) |
| V3 | 相对位移定义（Relative Displacement） |
| V4 | 力守恒（Action–Reaction） |
| V5 | FEM 端力注入（R1：单节点；R2 力分配见 Benchmark-2） |

本 Benchmark 采用 **R1（Node Anchor）**；形函数分配（\(\Sigma N_i F_i = F_{face}\)）留给 Benchmark-2。

---

## 3. 几何与模型

```
        Sphere (nsph=1)
           ●
           │
        (Bond)
           │
      ┌────────┐
     /|       /|
    / |      / |
   └──┼─────┘  |
   |  |     |  |
   |  └─────|──┘
   | /      | /
   |/       |/
   └────────┘
   C3D4（1 个四面体单元）
```

| 项 | 规格 |
|----|------|
| FEM | 1 × **C3D4** 四面体 |
| DEM | 1 × 球体颗粒（`nsph=1`） |
| Bond | 1 条（`nibond=1`） |
| 界面 | 四面体一个面 → `NSET=fem_interface` |
| 锚点 | 界面上距球心最近节点（R1） |
| 维度 | 3D（若团队暂只能 2D，可先用 CPS3 预研，正式 Benchmark 以 C3D4 为准） |

### 3.1 推荐几何参数（初值，实施时可微调）

| 符号 | 值 | 说明 |
|------|-----|------|
| \(K_n\) | \(10^8\) N/m | 与 Level-0 一致 |
| \(r_{cut}\) | 0.02 m | 识别截断距离 |
| \(d_0\) | 0.01 m | 初始球心到锚点距离，\(d_0 < r_{cut}\) |
| \(r_{sphere}\) | 0.005 m | 球半径（示意） |
| \(\mathbf{n}\) | 界面外法向（单位向量） | 键法向，建键时固定 |

**约束：** 四面体底面固定；球与锚点初始共线于 \(\mathbf{n}\)。

---

## 4. rcut 准则（冻结：方案 A）

**Test 2 采用方案 A（与当前实现一致）：**

```
distance > rcut  →  identify 阶段不建立 Bond（nibond = 0）
```

**不采用方案 B**（先建键、超距后 Delete Bond）作为 Benchmark-1 判据。方案 B 属于键管理扩展，不在本 Benchmark 范围。

---

## 5. 测试项（Test 0 – Test 4）

每个 Test 为**独立 inp 或独立荷载步**；运行前全回归 `verify_case` 1–3, 5–8, 9–11, 20–23。

### Test 0 — Initialization

| 项 | 内容 |
|----|------|
| 目的 | 初始几何正确、Bond 已建立、零位移零力 |
| 操作 | 零荷载、零位移边界 |
| 预期 | Bond Active = Yes；\(\Delta u_n = 0\)；\(F_n = 0\) |

### Test 1 — Normal Loading（Magnitude Test）

| 项 | 内容 |
|----|------|
| 目的 | 验证 \(F_n = K_n \Delta u_n\) 量级 |
| 操作 | 球沿 \(+\mathbf{n}\) 位移 \(\Delta u = 1\) mm（真实 DEM 位移或等效边界） |
| 预期 | \(\|F_n\| = K_n \times 10^{-3} = 10^5\) N |

### Test 2 — Beyond rcut

| 项 | 内容 |
|----|------|
| 目的 | 验证方案 A 识别准则 |
| 操作 | 球初始位置使 \(d > r_{cut}\)（如 \(d = 0.95\) m） |
| 预期 | Bond Active = No；`nibond = 0` |

### Test 3 — Reverse Loading

| 项 | 内容 |
|----|------|
| 目的 | 相对位移反号时力反号 |
| 操作 | 球沿 \(-\mathbf{n}\) 位移 \(\Delta u = 1\) mm |
| 预期 | \(F_n\) 与 Test 1 等幅反向；FEM / Particle 力方向共线相反 |

### Test 4 — Relative Motion Equivalence

| 项 | 内容 |
|----|------|
| 目的 | 验证界面力**仅由相对位移** \(\Delta\mathbf{u}=\mathbf{u}_{particle}-\mathbf{u}_{anchor}\) 决定，与球或锚点谁运动无关 |
| 操作 | 见下表；**不是**“相同位移输入”，而是“相同相对位移” |

| Test | 球位移 [mm] | 锚点位移 [mm] | \(\Delta u_n\) [mm] | 预期 \(F_n\) [N] |
|------|-------------|---------------|---------------------|------------------|
| 4a | +1 | 0 | +1 | +1.0e5 |
| 4b | 0 | −1 | +1 | +1.0e5 |

| 项 | 内容 |
|----|------|
| 预期 | 4a 与 4b 的 \(\Delta u_n\)、\(F_n\) 一致（误差在判据内） |
| 注意 | 锚点 \(+1\) mm、球固定 → \(\Delta u_n=-1\) mm，属**反向加载**（同 Test 3），**不是**本 Test 的等价情形 |

---

## 6. 统一输出（所有 Test 必填）

每个 Test 运行后生成 `benchmark1_testN_log.txt`（或统一 `benchmark1_results.csv`），字段固定：

| 字段 | 说明 |
|------|------|
| Bond Active | Yes / No |
| Distance \(d\) | 球心–锚点（或质心–锚点）距离 [m] |
| \(\Delta u_n\) | 法向相对位移 [m] |
| \(F_n\) | 法向键力 [N] |
| FEM Force | \((F_x, F_y, F_z)\) 写入 FEM 锚点 |
| Particle Force | \((F_x, F_y, F_z)\) 写入 DEM 节点 |
| \(\Sigma F\) | FEM + Particle 合力，应 \(\approx 0\) |

---

## 7. 通过判据

| 指标 | 判据 |
|------|------|
| Bond 数 | 与预期一致（Test 0/1/3/4：1；Test 2：0） |
| 力本构 | \(\|F_n - K_n \Delta u_n\| / \|K_n \Delta u_n\| < 10^{-6}\)（或 \(\|F_n\| < 10^{-6}\) 当 \(\Delta u_n=0\)） |
| 作用-反作用 | \(\|\mathbf{F}_{FEM} + \mathbf{F}_{Particle}\| < 10^{-6}\,\max(\|\mathbf{F}_{FEM}\|, 1\) N |
| 相对运动等价 | Test 4a 与 4b：\(\|F_n^{(4a)} - F_n^{(4b)}\| / \|F_n^{(4a)}\| < 10^{-6}\) |
| 软件回归 | 改码后 `verify_case` 1–3, 5–8, 9–11, 20–23 全绿 |

---

## 8. 文件规划

```
04_VerificationCases/Benchmark01/
├── README.md                 ← 本文（规格）
├── expected_results.md       ← 手算预期与记录表模板
├── Input/
│   ├── benchmark1_test0.inp  （待建）
│   ├── benchmark1_test1.inp
│   ├── benchmark1_test2.inp
│   ├── benchmark1_test3.inp
│   ├── benchmark1_test4a.inp
│   └── benchmark1_test4b.inp
├── Scripts/
│   └── build_benchmark1_inp.py  （待建）
└── Results/                  （运行输出，gitignore 可选）
```

**与开发算例关系：**

| 算例 | 用途 |
|------|------|
| `00_MinimalFEMDEM` | M0–M5 软件回归（mock / `verify_case`） |
| **Benchmark01** | 论文物理验证（真实 `nsph=1` FEM-DEM） |

---

## 9. 运行步骤（inp 完成后）

1. 编译 `User_solver.dll` 并复制到 `Source/2025-12-14/`
2. 确认 `ibond_verify_case.txt` 为 `0` 或不存在
3. `MultiFracS.exe benchmark1_testN.inp`
4. 对照 `expected_results.md` 填表
5. 撰写 `03_Development/Verification/InterfaceBond_Benchmark1_Verification.md`

---

## 10. 阻塞项

| 项 | 说明 |
|----|------|
| `nsph=1` FEM-DEM inp | 需团队提供或按本文规格自建 |
| 位移施加方式 | 优先 inp 边界条件，不用 `dev_anchor_ux` 开发钩子 |
| M5 Case O | Benchmark-1 是 M5 端到端的**目标应用场景** |

---

**下一步：** Step-2 加载荷 + 力验证（待 Step-1 评审后）。

---

## 11. Step-1 运行（identify only）

```bash
python Scripts/build_benchmark1_inp.py
# 复制 Input/benchmark1.inp 与 User_solver.dll 到 Source/2025-12-14/
# 勿放置 ibond_verify_case.txt
MultiFracS.exe benchmark1.inp
```

**输出目录：** `output/`

| 文件 | 内容 |
|------|------|
| `benchmark1_test0_setup.txt` | anchor、sphere、d0、rcut、nibond |
| `benchmark1_test0.vtk` | FEM + 球 + Bond 线（力向量当前为 0） |
| `benchmark1.vtk` | 与 test0 相同（基算例别名） |

**Step-1 预期：** `nibond=1`，`d0=0.01`，`rcut=0.02`，不调用 compute/apply。

---

## 12. ParaView 可视化

1. 打开 ParaView → File → Open → 选择 `output/benchmark1_testX.vtk`
2. Apply，点 `Reset Camera`
3. `Representation` 选 `Surface With Edges`，可见三角单元与 Bond 线
4. **球直接可视（无需手动猜点）：**
   - Coloring 选 `sphere_marker`
   - 对对象做 `Threshold`：`sphere_marker` 取 `1~1`
   - 再做 `Glyph`：Glyph Type=`Sphere`，Scale Array=`sphere_radius_vis`，Apply
5. **力箭头（Step-2 起可见）：**
   - 对原对象做 `Glyph`
   - Vectors 选 `node_force` 或 `sphere_force`
   - Glyph Type=`Arrow`
   - Scale Factor 建议 `1e-5`

**字段说明：**
- `point_role`: 0=FEM 节点，1=锚点，2=球心
- `sphere_marker`: 球点掩码（球点为 1）
- `sphere_radius_vis`: 仅用于显示放大，不参与计算
