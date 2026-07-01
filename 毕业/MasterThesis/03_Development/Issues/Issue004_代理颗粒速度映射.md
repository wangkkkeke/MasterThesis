# Issue004：FEM侧代理颗粒速度映射

**模块：** User_solver / User_solve.c
**状态：** OPEN
**优先级：** P0
**工作量：** 1天
**论文章节：** §3.2 InterfaceBond — "FEM侧颗粒速度由节点形函数插值获得"

---

## 任务描述

在 `user_solver()` 最开始，每时间步将 FEM 节点速度映射到界面代理颗粒，
使代理颗粒速度与所属FEM单元位移场保持一致。

## 理论依据

**来自 TheoryGuide.md + KnowledgeSummary.md：**
```
v_proxy = Σ Ni(ξ) * vi     （形函数插值）

若代理颗粒绑定到单一FEM节点（i1sphfnid[id] = fnid）：
v_proxy = v_fnid             （直接赋值，形函数值=1）
```

## 实现位置

`User_solve.c` — `user_solver()` 函数开头：

```c
void user_solver(CPUCORE cpucore, CPUUSER cpuuser) {
    // Step1：代理颗粒速度映射（每步最先执行）
    for (int id = 0; id < cpucore->ndn; id++) {
        int fnid = cpucore->i1sphfnid[id];
        if (fnid >= 0) {
            cpucore->d1dnvx[id] = cpucore->d1fnvx[fnid];
            cpucore->d1dnvy[id] = cpucore->d1fnvy[fnid];
            cpucore->d1dnvz[id] = cpucore->d1fnvz[fnid];
        }
    }
    // Step2：InterfaceBond力计算（Issue005）
    ...
}
```

> 注：若实际绑定为形函数插值（4节点插值），需改为从 i1enid 查找单元节点并计算 Ni*vi。
> 这取决于 Issue003 对 i1sphfnid 语义的确认结果。

## 测试方法

```
通过条件：
1. 代理颗粒速度 == 对应FEM节点速度（在纯FEM无DEM的情况下）
2. FEM模型（悬臂梁）加速度场中，界面处颗粒速度与节点速度一致
3. 验证：在 user_solver 中输出第0个代理颗粒的速度，
   与 d1fnvx[i1sphfnid[0]] 对比，应相等
```

## Review 要点

- [ ] 映射是否在 InterfaceBond 力计算之前执行
- [ ] 只对 `i1sphfnid[id] >= 0` 的颗粒执行，纯DEM颗粒跳过
- [ ] 是否覆盖了 vx/vy/vz 三个分量

## 依赖

Issue003（界面颗粒识别完成，已知哪些颗粒是代理颗粒）
