# WritePaper.md — 论文写作提示词

## 触发条件
需要写某章节正文时使用。

## 提示词模板

```
进入执行模式。

写作任务：第[X]章 §[X.X] [节名]

素材来源：
- [开题报告/TheoryGuide.md/FormulaIndex.md 的具体章节]

要求：
1. 学位论文语气（正式、第一人称"本文"或"本节"）
2. 公式编号格式：(章节号-序号)，例如 (3-1)
3. 符号与 FormulaIndex.md 一致
4. 不要引用 CursorRules 目录或 Issue 编号
5. 字数约 [X] 字
6. 如有图表引用，写 [图X-X] 或 [表X-X] 占位符

禁止：
- 把开发实现细节（如 User_solver.dll）直接写进论文
- 使用英文变量名（应替换为数学符号）
```

## 常用写作参考文件

- 论文框架：`00_Project/ThesisOutline.md`
- 写作计划：`00_Project/ChapterPlan.md`
- 公式：`05_Research/FormulaIndex.md`
- 已定稿表述：`08_AIWorkspace/CursorRules/paper.md`
