# review.md — 代码审查清单

> 来源：`DevelopmentHistory.md` 踩坑/Bug记录 + `C语言编程规范.txt` + 源码接口约束

---

## 审查触发时机

每次提交 User Function DLL 或 User Solver DLL 修改前必须过此清单。

---

## 清单一：编译前检查

### C.1 类型检查
- [ ] 所有浮点变量是否使用 `Real`，而非 `float`/`double`？（`Real.h` 强制）
- [ ] 字面量数值是否已替换为 `R0`, `R1`, `R2`, `RP5` 等常量？（`Real.h`）
- [ ] 归一化操作前是否有 `> SmallPositiveNumber` 保护？

### C.2 函数签名
- [ ] User Function DLL 函数签名是否与原始头文件完全一致？（禁止添加/删除参数）
- [ ] 新增函数是否加了 `USERDLL` 宏前缀？（`Real.h`）
- [ ] 头文件是否有 `#ifndef` 保护？

### C.3 内存
- [ ] 所有 `malloc` 是否配套 `free`？
- [ ] 数组访问是否有边界检查（尤其是 `d1xxx[nfn]` 类 SOA 数组）？
- [ ] 指针使用前是否检查非 NULL？

---

## 清单二：物理一致性检查

### P.1 单位系统（历史血泪：1000倍应力误差）
- [ ] 所有材料参数单位是否统一为 SI（Pa, kg, m, s）？
- [ ] inp 文件中弹性模量单位是否为 Pa（不是 MPa，不是 GPa）？
- [ ] 验证：静力学算例理论解与程序输出应力数量级是否一致？

### P.2 应力符号约定（Bug001）
- [ ] Ce3D 本构中压应力是否取**负**值？
- [ ] 输出 VTK 后 ParaView 中压缩区域是否为负应力？

### P.3 边界条件
- [ ] SForceBoundary 返回的是**力（N）**，不是压强？
- [ ] 每个节点力是否乘以该节点对应的面积份额？
- [ ] FixBoundary 节点不应在 SForceBoundary 中再次施加力？

### P.4 IbkFlag（失败方案4警告）
- [ ] 代码中是否有手动设置 `IbkFlag` 的操作？
  - 如果有 → **删除**，IbkFlag 由引擎内部维护，是输出不是输入
- [ ] 程序中读 IbkFlag 是否只用于判断断裂状态，而非控制激活？

---

## 清单三：InterfaceBond 专项

### I.1 界面识别
- [ ] 界面颗粒通过 `i1sphfnid[id] >= 0` 判断，而非通过坐标范围？
- [ ] 识别在 `User_preprocess()` 中完成一次，结果缓存到 CPUUSER？

### I.2 速度映射时序
- [ ] 代理颗粒速度映射是否在 `User_solve()` **最开始**执行？
- [ ] 映射完成后才计算 InterfaceBond 力？

### I.3 力平衡
- [ ] InterfaceBond 力是否同时更新了 FEM 节点力 `d1fnfx` 和 DEM 颗粒力 `d1dnfx`？
- [ ] 两侧力是否方向相反（牛顿第三定律）？

### I.4 时间步稳定性
- [ ] InterfaceBond 刚度 Kn 加入后是否重新检验时间步稳定性？
- [ ] dt_critical 是否已按新 Kn 重新估算？

---

## 清单四：inp 文件检查

### N.1 关键字顺序（来自 `inp数据格式文件5.8.md`）
- [ ] `*Material` 先于 `*Joint` 先于 `*Boundary`？
- [ ] `*Begin` 在所有定义之后？
- [ ] `*solve` 和 `*End` 存在且在 `*Begin` 之后？

### N.2 Monitor Point
- [ ] Monitor Point 坐标是否精确对应某个网格节点？（否则输出恒零）
- [ ] 验证方法：在 Gmsh 中查找节点坐标，复制到 inp

### N.3 物理组命名
- [ ] Gmsh Physical Group 名称与 inp 中 `*Elset`/`*Nset` 名称是否完全一致？
- [ ] 特殊字符和空格是否已去除？

---

## 清单五：运行环境

- [ ] virbox 加密锁是否已插入 USB？（否则程序无法启动）
- [ ] 编译后的 DLL 是否已复制到 MultiFracS.exe 同目录？
- [ ] 旧版本 DLL 是否已备份（防止覆盖后回退困难）？
- [ ] 输出目录是否有足够磁盘空间（VTK文件可能很大）？

---

## 快速故障判断表

| 现象 | 最可能原因 | 检查项 |
|------|-----------|--------|
| 应力值差1000倍 | 单位混用 Pa/MPa | P.1 |
| 压缩区应力为正 | Ce3D符号约定 | P.2 |
| Monitor输出全零 | Monitor Point不在节点上 | N.2 |
| 程序无法启动 | virbox锁未插 / DLL缺失 | 环境检查 |
| 颗粒速度异常大 | 时间步不稳定 | I.4 |
| 节理不断裂 | IbkFlag被手动重置 | P.4 |
| 静力算例不收敛 | 显式动力学阻尼设置错误 | damp_n/damp_s |
