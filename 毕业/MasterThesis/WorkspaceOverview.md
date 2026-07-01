# WorkspaceOverview.md — 整个工作区认知地图

> 课题：显式动力学有限元-离散元共生耦合方法及验证研究
> 研究者：王可
> 平台：MultiFracS 5.8
> 更新：2026-06-29

---

## 一、项目基本信息

| 项目 | 内容 |
|---|---|
| 论文题目 | 显式动力学有限元-离散元共生耦合方法及验证研究 |
| 英文题目 | Development and Verification of a Symbiotically Coupled FEM-DEM Method for Explicit Dynamics |
| 论文类型 | 学术型硕士学位论文 |
| 研究平台 | MultiFracS 5.8（严成增，C语言，SOA结构） |
| 目标页数 | 104-122页 |
| 总图幅数 | 33幅 |
| 总表格数 | 8个 |
| 算例总数 | 约11个工况 |
| 课题来源 | 面向迈曦显式动力学的有限元离散元自适应耦合算法研发（联合协议） |
| 预计答辩 | 2027年4月-5月 |

---

## 二、目录结构与职责

```
MasterThesis/
├── 00_Project/        → 项目控制中心（规划、进度、规范）
├── 01_KnowledgeBase/  → 知识库（文献、历史聊天、开题报告）
├── 02_MultiFracS/     → 软件理解（源码阅读、格式文档、示例）
├── 03_Development/    → 软件开发（设计、调试、审查、Issues）
├── 04_VerificationCases/ → 验证算例（输入文件、结果、分析）
├── 05_Research/       → 理论研究（公式推导、FEM/DEM理论）
├── 06_Results/        → 最终计算结果（CSV/VTK/图/动画）
├── 07_Thesis/         → 论文正文（各章、图表、模板）
├── 08_AIWorkspace/    → AI工作区（Rules/KnowledgeGraph/Memory）
└── 09_Log/            → 全过程日志（日志/Bug/会议/经验）
```

### 各目录详细说明

| 目录 | 当前状态 | 主要内容 | 进入时机 |
|---|---|---|---|
| `00_Project` | 已建立规划文档 | ThesisOutline / ChapterPlan / FigureTablePlan / ProgressTracker / 编程规范 / 课题来源文件 | 每次工作前必看 |
| `01_KnowledgeBase` | 文献已就绪，部分目录待填 | A/B/C三类文献全文、课题组论文50篇、往届论文24篇、历史聊天4条 | 写作和理论推导时查阅 |
| `02_MultiFracS` | INP格式文档已建 | MultiFracS 5.8输入格式文档、示例INP文件、SDK/DLL说明 | 开发前必须理解 |
| `03_Development` | Issue001已建，其余待填 | Issues / Design（InterfaceBond/Solver/SoA设计文档）/ Debug / Review | 每次开发时使用 |
| `04_VerificationCases` | 目录结构建立，算例未开始 | 按算例分4个子目录（悬臂梁/拉伸杆/巴西劈裂/模式I），每个含Input/Output/Analysis | 算例建立后使用 |
| `05_Research` | 目录结构建立，待填 | 公式推导（Formula/Derivation）/ FEM/DEM理论 / 显式动力学 / InterfaceBond理论 | 推导公式时使用 |
| `06_Results` | 全空，待算例完成 | CSV / VTK / Figures / Animation / Tables / Comparison | 算例计算完成后存放结果 |
| `07_Thesis` | 全空，待写作 | Chapter01-05 / Figures / Tables / References / Template / Final | 写论文时使用 |
| `08_AIWorkspace` | 目录建立，内容待填 | CursorRules（coding/solver/architecture等）/ KnowledgeGraph / Memory / PromptLibrary | AI每次进入项目时加载 |
| `09_Log` | 建议文件已建 | Daily / Weekly / Meeting / Bug / LessonsLearned / Archive | 每天记录 |

---

## 三、目录关联关系（数据流）

```
知识输入层
  01_KnowledgeBase（文献/论文/历史）
  00_Project/开题工作（开题报告各版本）
        ↓ 理论依据 / 写作素材
        
理论研究层
  05_Research（公式推导、FEM/DEM理论）
  02_MultiFracS（软件理解、接口格式）
        ↓ 算法设计
        
开发层
  03_Development（Issue/Design/Debug/Review）
        ↓ 代码实现（在MultiFracS源码中）
        ↓ 验证
        
验证层
  04_VerificationCases（算例Input/Output/Analysis）
        ↓ 计算结果
        
结果层
  06_Results（CSV/VTK/图/动画/表格）
        ↓ 整理图表
        
论文层
  07_Thesis（各章正文 + 图 + 表）
        ↓
  最终答辩
  
支撑层（贯穿全程）
  00_Project（进度管控）
  08_AIWorkspace（AI记忆/规则）
  09_Log（全过程记录）
```

---

## 四、论文章节与目录映射

| 论文章节 | 写作素材来源 | 依赖目录 | 依赖条件 |
|---|---|---|---|
| **第1章 绪论** | 开题报告§1-§2扩写 | `01_KB/Literature` / `00_Project/开题工作` | 全文完成后写 |
| **第2章 理论基础** | 开题报告§3 + A/B类文献 | `01_KB/Literature` / `05_Research/FEM` / `05_Research/DEM` | 文献阅读完成即可写 |
| **第3章 方法建立** | 开题报告§3.2-§3.3 + 公式推导 | `05_Research/InterfaceBond` / `05_Research/Derivation` / `03_Development/Design` | 最先写，不依赖算例 |
| **第4章 精度验证** | 悬臂梁+拉伸杆算例 | `04_VerificationCases/01_Cantilever` / `04_VerificationCases/02_TensionBar` / `06_Results` | 部分可先写，结果依赖算例 |
| **第5章 断裂验证** | 巴西劈裂+模式I算例 | `04_VerificationCases/03_Brazilian` / `04_VerificationCases/04_ModeI` / `06_Results` | 大部分依赖算例 |
| **第6章 结论** | 全部章节综合 | 全部 | 最后写 |

---

## 五、项目时间线（论文工作计划）

| 时间段 | 主要工作 | 预期成果 |
|---|---|---|
| 2026-06-23 至 2026-09-02 | 完善InterfaceBond模块；建立预分区建模流程；开展单轴拉伸杆二维算例 | InterfaceBond模块验证 + 拉伸杆结果 |
| 2026-09-03 至 2026-11-01 | 巴西劈裂、模式I裂纹板二维算例 | 两类开裂算例二维结果 |
| 2026-11-02 至 2027-01-01 | 模式I三维算例；局部共生vs全域共生效能对比 | 三维算例 + 效能对比 |
| 2027-01-02 至 2027-01-31 | 整理图表，撰写各章 | 论文初稿 |
| 2027-02-01 至 2027-03-31 | 修改、格式规范、查重 | 论文定稿 |
| 2027-04-01 至 2027-05-31 | 准备答辩 | 通过答辩 |

---

## 六、当前优先任务（截至2026-06-29）

按 `00_Project/ProgressTracker.md` 记录的TOP 5：

| 优先级 | 任务 | 依赖 | 对应论文 |
|---|---|---|---|
| 1 | InterfaceBond模块调通 | 无（立即开始） | 第3章§3.5 + 第4/5章所有算例 |
| 2 | 第3章§3.1-3.3正文写作 | 无（立即可写） | 第3章核心 |
| 3 | 绘制图3-1、图3-2、图3-4 | 无（立即可绘） | 第3章配图 |
| 4 | 制作表4-1、表4-2、表5-3 | 无（30分钟内完成） | 第4/5章参数表 |
| 5 | 阅读A17/B11确定模式I几何参数 | 无（立即可读） | 第5章§5.3 |

---

## 七、开发流程（Software Development Flow）

```
Step 1  阅读 00_Project → 理解当前任务与论文目标
        ↓
Step 2  阅读 01_KnowledgeBase → 理论依据与文献支撑
        ↓
Step 3  阅读 05_Research/InterfaceBond → 公式与算法理解
        ↓
Step 4  阅读 02_MultiFracS → 理解软件接口与数据结构
        ↓
Step 5  在 03_Development/Design 写设计文档
        ↓
Step 6  等待确认 → 开始编码（在MultiFracS源码中）
        ↓
Step 7  在 03_Development/Issues 记录问题
        ↓
Step 8  在 03_Development/Debug 记录调试过程
        ↓
Step 9  在 04_VerificationCases 建立算例验证
        ↓
Step 10 结果存入 06_Results
        ↓
Step 11 更新 09_Log 日志
```

开发规范：C语言，SOA数据结构，驼峰命名法（见 `00_Project/C语言编程规范.txt`）

---

## 八、论文写作流程（Thesis Writing Flow）

```
波次1（立即开始，不依赖算例）
  ├── 第3章全部（方法章，本文核心，最先写）
  ├── 第2章全部（前人理论综述，与Ch3并行）
  ├── 第4章§4.1-4.2.2（验证框架+悬臂梁模型描述）
  ├── 第4章§4.3.1-4.3.2（拉伸杆模型描述）
  ├── 第5章§5.1（概述）
  └── 第5章§5.2.1-5.3.2（模型描述段）
  
波次2-5（随算例完成依次填写结果分析）
  ├── 悬臂梁算例完成 → 第4章§4.2.3-5
  ├── 拉伸杆算例完成 → 第4章§4.3.3-6 + §4.4
  ├── 巴西劈裂完成 → 第5章§5.2.3-6
  └── 模式I完成 → 第5章§5.3.3-7 + §5.4
  
波次6（全部算例完成后）
  ├── 第1章（绪论，需全局视角）
  └── 第6章（结论）

最后
  └── 摘要、关键词
```

写作素材获取路径：
- 公式 ← `05_Research/Derivation`
- 算例参数 ← `04_VerificationCases/*/Analysis.md`
- 图表 ← `06_Results` + Python脚本
- 参考文献 ← `01_KnowledgeBase/Literature`
- 最终存放 ← `07_Thesis/ChapterXX`

---

## 九、图表制作规范

| 图类型 | 工具 | 典型图号 | 依赖 |
|---|---|---|---|
| 示意图/流程图 | Visio / Inkscape / draw.io | 图1-1、2-1至2-4、3-1至3-6、4-1 | 无，立即可绘（共14幅） |
| 数据曲线图 | Python / Matplotlib | 图3-3、4-3至4-9、5-4至5-12 | 大部分依赖算例 |
| 渲染/模型截图 | Paraview / MultiFracS | 图4-2、4-5至4-6、5-1至5-6 | 依赖算例建模与计算 |

---

## 十、AI工程师工作守则（本项目）

1. 每次进入项目前先读 `00_Project/ProgressTracker.md` — 了解当前进度
2. 每次开发前先看 `03_Development/Issues` — 了解当前问题
3. 所有工作必须对应论文章节，无法对应时主动提醒
4. 每次获得新资料 → 更新 `08_AIWorkspace`（Rules/KnowledgeGraph/Memory）
5. 新资料与旧知识冲突 → 不自行判断，先告知用户
6. 完成工作后更新 `09_Log/Daily`
7. 开发流程：理解需求 → 理解论文目标 → 理解理论 → 阅读源码 → 提出方案 → 等待确认 → 编码
