# Debug.md — 调试提示词

## 触发条件
MultiFracS 程序崩溃或结果异常时使用。

## 提示词模板

```
进入研究模式。

问题描述：
[程序表现/错误现象/异常数值]

退出码：[exit_code]
运行步骤：[到第几步崩溃/哪个算例]

请按以下顺序排查：
1. 对照 08_AIWorkspace/CursorRules/debug.md 的退出码表
2. 检查 08_AIWorkspace/CursorRules/review.md 的快速故障判断表
3. 排查 03_Development/DevelopmentHistory.md 中是否有相同记录
4. 如是新问题，在 03_Development/Issues/ 新建 Issue
```

## 历史已知Bug快速查找

| 现象 | 查看 |
|------|------|
| 应力差1000倍 | DevelopmentHistory Bug002 |
| 压缩应力为正 | DevelopmentHistory Bug001 |
| Monitor输出0 | DevelopmentHistory 踩坑2 |
| 程序不启动 | 检查virbox锁+DLL |
