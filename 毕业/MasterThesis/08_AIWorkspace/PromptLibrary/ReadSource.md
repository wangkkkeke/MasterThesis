# ReadSource.md — 阅读源码提示词

## 触发条件
需要理解 MultiFracS 源码某个模块时使用。

## 提示词模板

```
进入研究模式。

阅读以下源码文件：
[文件路径]

目标：
1. 理解函数签名和参数含义
2. 找到 [关键字/功能] 的实现
3. 确认是否有 [待确认问题]

输出格式：
- 关键发现（必须来自源码，引用具体行号）
- 与 DataStructure.md / DeveloperGuide.md 的一致性或差异
- 更新建议（若发现文档描述有误）
```

## 常用搜索关键字

InterfaceBond：`i1sphfnid`, `BoundaryParticle`, `VirtualParticle`, `ibond`
速度映射：`ShapeFunction`, `Interpolation`, `fnvx`
断裂：`IbkFlag`, `broken`, `damage`
力注入：`d1dnfx`, `d1fnfx`, `user_to_MultiFracS`
