# paper.md — 论文写作规范

> 来源：`00_Project/开题工作/论文总体框架_v1.md` + `KnowledgeSummary.md` + `FormulaIndex.md` + `TheoryGuide.md`

---

## 1. 论文结构（固定，不可变动）

**来源：** `ThesisOutline.md` + `论文总体框架_v1.md`

```
第一章  绪论（≈10页）
第二章  显式动力学 FEM-DEM 耦合理论（≈20页）
第三章  InterfaceBond 耦合机制（≈20页）
第四章  MultiFracS 实现与验证（≈20页）
第五章  工程算例（≈20页）
第六章  结论与展望（≈5页）
```

**开发 → 论文 对应关系：**

| 开发内容 | 对应章节 |
|---------|---------|
| Ce3D 三维本构 | 第二章 §2.2 |
| Cjoint3D 节理 | 第二章 §2.3 |
| InterfaceBond 开发 | 第三章 §3.2-3.4 |
| 悬臂梁验证 | 第四章 §4.1 |
| 单轴拉伸验证 | 第四章 §4.2 |
| 巴西劈裂 | 第四章 §4.3 |
| Mode I 断裂 | 第四章 §4.4 |
| 工程算例 | 第五章 |

---

## 2. 公式写作规范

**来源：** `FormulaIndex.md` + `TheoryGuide.md`

### 2.1 公式编号格式

```
(章节号-公式序号)
例：(2-1), (3-5), (4-12)
```

### 2.2 已确定的核心公式（必须出现在论文中）

**第二章：**
- 运动方程（Newton第二定律离散形式）：`M*a = F_ext - F_int`  [来源：TheoryGuide.md §显式动力学]
- 中心差分时间积分：`v_(n+1/2) = v_(n-1/2) + a_n * dt`  [来源：FormulaIndex.md F-13]
- Rayleigh 时间步：`dt ≤ α * L_min / c_wave`  [来源：FormulaIndex.md F-14]
- 四面体形函数：`u = N1*u1 + N2*u2 + N3*u3 + N4*u4`  [来源：TheoryGuide.md §FEM]

**第三章：**
- InterfaceBond 法向力：`Fn = Kn * δn`  [来源：FormulaIndex.md F-20]
- InterfaceBond 切向力：`Ft = Kt * δt`  [来源：FormulaIndex.md F-21]
- FEM侧代理颗粒速度：`v_proxy = Σ Ni * vi`  [来源：DeveloperGuide.md §InterfaceBond]

### 2.3 公式符号统一（来自 FormulaIndex.md 规范）

| 符号 | 含义 | 备注 |
|------|------|------|
| E | 弹性模量 | Pa |
| ν | 泊松比 | 无量纲 |
| ρ | 密度 | kg/m³ |
| Kn | 法向刚度 | N/m³ |
| Kt | 切向刚度 | N/m³ |
| δn | 法向相对位移 | m |
| dt | 时间步长 | s（论文中不要写 Δt）|
| Ni | 形函数 | 无量纲 |

---

## 3. InterfaceBond 描述规范（第三章核心）

**来源：** `KnowledgeSummary.md` v1.2 + 用户与GPT讨论结论

### 3.1 已确认的标准描述（直接使用）

> FEM区域采用四面体有限元离散，在界面附近建立与有限元位移场绑定的边界代理颗粒，其运动学状态由所属有限元节点经形函数插值确定；DEM区域采用可自由运动的离散颗粒描述。InterfaceBond根据几何关系识别界面两侧的FEM边界代理颗粒与DEM边界颗粒，在颗粒之间建立法向与切向键连接，实现跨界面的力与位移传递。因此，InterfaceBond本质上属于颗粒-颗粒之间的键连接，而非有限元节点与DEM颗粒之间的直接连接。

### 3.2 待源码确认后补充的描述

**尚未确认项（来自 KnowledgeSummary.md 未知问题）：**
- 代理颗粒在源码中是否为真实 `Particle` 对象，还是仅为计算中间量
- 确认后需在第三章 §3.2 补充实现细节

**确认方法：** 在源码中搜索 `VirtualParticle`, `BoundaryParticle`, `i1sphfnid` 相关初始化代码

### 3.3 禁止在论文中使用的表述

- "虚拟DEM颗粒由FEM节点直接控制" — 技术建议书的原话，不够严谨
- "四面体和球之间的弹簧" — 描述错误，应为颗粒之间
- "位移边界条件施加到颗粒" — MultiFracS 无此接口

---

## 4. 算例描述规范

**来源：** `开题后算例参数待查.txt` + `ChapterPlan.md`

每个验证算例描述必须包含：
1. 几何模型（尺寸、边界条件示意图）
2. 材料参数表（与来源文献一致）
3. 荷载施加方式（SForceBoundary/VBoundary，量值）
4. 网格划分（单元类型、节点数）
5. 时间步设置（TimeStepSize 倍率）
6. 与理论解/实验值的误差表

### 4.1 验证算例最低标准

| 算例 | 验证指标 | 可接受误差 |
|------|---------|-----------|
| 悬臂梁 | 端点挠度、固定端应力 | < 5% |
| 单轴拉伸 | 应力-应变曲线 | < 10% |
| 巴西劈裂 | 劈裂荷载、裂纹路径 | 定性一致 |
| Mode I 断裂 | KIC、裂纹扩展速度 | < 15% |

---

## 5. 图表规范

**来源：** `FigureTablePlan.md`

### 5.1 图片命名格式

```
Fig_CH{章}_NO{序号}_{描述}.png
例：Fig_CH3_NO1_InterfaceBond机制示意图.png
```

### 5.2 必须包含的图（来自 FigureTablePlan.md）

- FEM-DEM 耦合示意图（第三章）
- InterfaceBond 力学模型图（第三章）
- 时间步循环流程图（第四章）
- 各验证算例：几何模型 + 应力云图 + 对比曲线（第四章）

### 5.3 ParaView 图导出设置

- 格式：PNG，至少 300 DPI
- 使用白色背景（Edit → Settings → Background Color）
- 颜色映射：应力用 Blue-White-Red（压-零-拉），位移用 Rainbow

---

## 6. 论文写作顺序建议

**来源：** `ProjectRoadmap.md` + `ChapterPlan.md`

```
推荐顺序（最小依赖冲突）：
1. 完成第四章算例 → 有图有数据
2. 写第二章理论  → 参考 TheoryGuide.md
3. 写第三章实现  → 参考 DeveloperGuide.md + DataStructure.md
4. 写第四章验证  → 直接使用第1步的结果
5. 写第五章应用  → 最后做
6. 写第一章绪论  → 最后写，文献综述等全部完成后
7. 写第六章结论  → 最后写

不要先写绪论（会反复修改）
```

---

## 7. 引用规范

- 所有来自 MultiFracS 开发团队的方法必须引用导师相关论文
- InterfaceBond 机制引用：结合技术建议书描述，引用开发组文献
- 显式动力学相关：引用 Belytschko、Hughes 经典教材
- FDEM 相关：引用 Munjiza 系列文献
