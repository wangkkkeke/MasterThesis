# MultiFracS 硕士毕业论文项目

**题目：** 显式动力学有限元-离散元共生耦合方法及验证研究
**平台：** MultiFracS v5.8（团队版 2026-05-08）
**研究方向：** FEM-DEM共生耦合 / InterfaceBond / 显式动力学 / 断裂力学验证

---

## 快速导航

| 需求 | 入口 |
|------|------|
| 论文结构与进度 | `00_Project/ThesisOutline.md` + `00_Project/ProgressTracker.md` |
| 论文写作指南 | `00_Project/ThesisWritingGuide.md` |
| 开发任务列表 | `03_Development/Issues/` (Issue001-018) |
| InterfaceBond理论 | `05_Research/TheoryGuide.md` |
| 公式索引 | `05_Research/FormulaIndex.md` |
| MultiFracS架构 | `02_MultiFracS/Architecture.md` |
| 开发规范 | `08_AIWorkspace/CursorRules/` |
| 历史开发记录 | `03_Development/DevelopmentHistory.md` |
| 文献编号索引 | `01_KnowledgeBase/Literature/文献编码表.md` |

---

## 目录结构

```
MasterThesis/
├── 00_Project/          # 规划文档（论文框架、进度、写作计划）
├── 01_KnowledgeBase/    # 外部知识（文献、历史聊天、课题要求）
├── 02_MultiFracS/       # 软件分析（架构、接口文档、源码）
├── 03_Development/      # 开发过程（Issues、历史、设计）
├── 04_VerificationCases/# 验证算例（inp文件、计算结果、分析）
├── 05_Research/         # 本课题研究成果（推导、设计、公式）
├── 06_Results/          # 计算结果（VTK、CSV、图片）
├── 07_Thesis/           # 论文正文（各章节Word/Markdown）
├── 08_AIWorkspace/      # AI工作空间（规范、规则、知识图谱）
└── 09_Log/              # 开发日志
```

---

## 当前状态

- InterfaceBond 开发：Issue001-018 已拆分，待开始执行
- 论文正文：框架完成，正文未动笔
- 已完成验证：圆孔（MC本构）、UCS单元

## MultiFracS 版本

使用 `02_MultiFracS/Source/2026-05-08/`（团队版，无单元限制）
详见 `02_MultiFracS/Source/版本说明.md`
