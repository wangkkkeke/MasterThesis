# ProjectStatus.md — 项目当前状态

> 每次新对话开始时，AI 先读此文件以恢复上下文。
> 每次对话结束后，更新此文件。

---

## 当前阶段

**阶段：** 前期准备完成，InterfaceBond 开发待启动

## 开发进度

| 模块 | 状态 | 当前Issue |
|------|------|---------|
| User_solver 框架 | 未开始 | Issue001 |
| CPUUSER 数据结构 | 未开始 | Issue002 |
| 界面颗粒识别 | 未开始 | Issue003 |
| InterfaceBond 力计算 | 未开始 | Issue005 |
| 断裂准则 | 未开始 | Issue007 |
| 参数标定 | 未开始 | Issue008 |

## 论文进度

| 章节 | 进度 |
|------|------|
| 第3章（本文核心） | 框架30%，正文未动笔 |
| 第4章 | 0% |
| 第5章 | 0% |
| 其他章节 | 0% |

## 当前最高优先任务

1. Issue001：User_solver.dll 框架编译验证
2. 第3章 §3.1-3.4 正文写作（不依赖算例）
3. 图3-1、图3-2 绘制（Visio）

## 已确认的关键决策

- MultiFracS 版本：`Source/2026-05-08/`（团队版）
- InterfaceBond 代理颗粒语义：`i1sphfnid[id] >= 0` 即代理颗粒（待源码确认）
- 单位制：全部 SI（Pa, kg, m, s）

## 待确认问题

- InterfaceBond 源码中是否有真实 Particle 对象（见 KnowledgeSummary.md 未知问题）
- Kn/Kt 具体取值（待 Issue008 标定）

## 最近更新

2026-06-30：前期文档准备完成（Architecture/CallGraph/DataStructure/DeveloperGuide/Issues/CursorRules/ThesisWritingGuide）
