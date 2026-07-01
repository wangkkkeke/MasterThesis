# issue.md — 问题跟踪规范

> 来源：`03_Development/Issues/` 目录结构 + `DevelopmentHistory.md` + 项目历史记录

---

## 1. Issue 文件命名与存放

```
路径：03_Development/Issues/
文件名：Issue{编号}_{模块}_{简述}.md
示例：Issue001_InterfaceBond.md
      Issue002_Ce3D_应力符号.md
      Issue003_SBoundary_单位错误.md
```

编号：三位数字，从001开始递增，不重用。

---

## 2. Issue 模板

```markdown
# Issue{编号}：{简述}

**模块：** Ce3D / Cjoint3D / InterfaceBond / SBoundary / VBoundary / User_solver / inp / 其他
**状态：** OPEN / IN_PROGRESS / RESOLVED / WONTFIX
**优先级：** P0（阻塞） / P1（重要） / P2（一般）
**发现日期：** YYYY-MM-DD
**解决日期：** YYYY-MM-DD（未解决留空）

---

## 现象描述

（程序的具体表现，包含退出码、输出数据、截图等）

## 复现步骤

1. inp 文件配置
2. 运行命令
3. 观察到的错误

## 根本原因

（分析后确认的原因，未确认时写"待查"）

## 解决方案

（具体的代码修改或参数调整）

## 预防措施

（如何避免同类问题再次出现）

## 相关文件

- 源码文件：
- inp 文件：
- 参考文档：
```

---

## 3. 现有已记录问题清单

**来源：** `DevelopmentHistory.md` Bug/失败记录

### RESOLVED

| ID | 模块 | 问题 | 解决方案 |
|----|------|------|---------|
| Bug001 | Ce3D | 压缩应力符号为正 | Ce3D 压应力取负，修改本构输出符号 |
| Bug002 | inp/SBoundary | 应力差1000倍 | 统一 SI 单位（Pa），SBoundary 返回力而非压强 |
| Bug003 | Gmsh | 裂纹路径不连续 | CCW（逆时针）建立几何面，法向量方向正确 |

### OPEN（未解决）

| ID | 模块 | 问题 | 状态 |
|----|------|------|------|
| Issue001 | InterfaceBond | 代理颗粒是否为真实Particle对象 | 待源码确认 |
| Issue002 | InterfaceBond | Ghost Force 量化标准与消除方案 | 待实现后测试 |
| Issue003 | User_solver | i1sphfnid 的初始化时机 | 待阅读 User_create.c |

---

## 4. 失败方案记录规范

每次尝试失败后立即记录，防止重复踩坑：

```markdown
# 失败记录：{方案名称}

**尝试日期：** YYYY-MM-DD
**尝试原因：** （为什么想到这个方法）
**失败现象：** （程序行为/报错）
**失败原因：** （根本原因分析）
**教训：** （不要再尝试什么）
```

### 已记录失败方案（禁止重试）

**来源：** `DevelopmentHistory.md`

1. **位移边界条件（直接设置节点位移）**
   - 失败原因：MultiFracS 无此接口，显式积分只能施加速度或力
   - 禁止重试

2. **用 SBoundary 施加位移时程**
   - 失败原因：SBoundary 接口设计为返回力（N），不是位移（m）
   - 禁止重试

3. **三轴压缩直接运行（无静力学预验证）**
   - 失败原因：参数未经验证，程序崩溃 exit_code=0xC0000005
   - 教训：必须先过悬臂梁静力学验证

4. **手动设置 IbkFlag 控制节理激活**
   - 失败原因：IbkFlag 是输出状态变量，由引擎内部维护，手动设置会被覆盖
   - 禁止重试

5. **Monitor Point 放在几何中心**
   - 失败原因：不在节点上，输出恒零
   - 禁止重试

---

## 5. 问题升级流程

```
P2 一般问题 → 自行排查 → 记录到 Issue 文件
P1 重要问题 → 参考 DevelopmentHistory.md → 排查无果则升级
P0 阻塞问题 → 立即停止开发 → 咨询导师 → 记录确认结论到 KnowledgeSummary.md
```

---

## 6. 导师确认必须记录

每次与导师沟通后，将确认结论记录到对应 Issue 和 KnowledgeSummary.md：

```
Issue 中新增一节：
## 导师确认（YYYY-MM-DD）
确认内容：
结论更新：
```

当前待确认（来自 KnowledgeSummary.md 未知问题）：
- [ ] 代理颗粒在 MultiFracS 源码中的实现方式（Particle 对象 or 计算中间量）
- [ ] InterfaceBond 刚度 Kn/Kt 的推荐取值范围
- [ ] Ghost Force 可接受阈值
