# Issue001：User_solver.dll 框架编译验证

**模块：** User_solver
**状态：** OPEN
**优先级：** P0（所有InterfaceBond开发的前提）
**工作量：** 1天
**论文章节：** §3.5 MultiFracS平台集成与计算流程

---

## 任务描述

在 User_solver 模板代码基础上，完成最小可运行版本的编译和验证。
确认框架正确接入 MultiFracS.exe，为后续所有开发打基础。

## 具体工作

1. 用 Visual Studio 打开 `User_solver/` 目录，配置编译环境
2. 保持默认空实现（User_solve.c 中 user_solver 函数体为空）
3. 编译生成 `User_solver.dll`
4. 将 DLL 复制到 MultiFracS.exe 同目录
5. 用任意已有算例（如圆孔）带 User_solver 运行，确认不崩溃

## 测试方法

```
通过条件：
1. 编译无报错无警告
2. MultiFracS.exe 带 User_solver.dll 启动不崩溃
3. 在 User_solve.c 中加 printf("[Issue001] Step=%d\n", nstep);
   运行后控制台能看到输出（每步一行）
```

## Review 要点

- [ ] `USERDLL` 宏是否正确（Windows用 `__declspec(dllexport)`）
- [ ] `Cpucore.h` 是否为只读（不得修改）
- [ ] `Create_cpuuser` 是否正确 malloc 并返回
- [ ] 编译平台是否与 MultiFracS.exe 匹配（x64 vs x86）

## 依赖

无前置依赖，最优先执行。

## 完成标志

控制台打印出步数输出，算例正常完成。
