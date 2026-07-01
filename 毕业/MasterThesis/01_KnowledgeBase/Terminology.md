# Terminology.md — 术语表

> 统一项目内所有文档的术语表述，防止歧义。

---

| 中文术语 | 英文/缩写 | 定义 | 注意事项 |
|---------|---------|------|---------|
| 共生耦合 | Symbiotic Coupling | FEM 与 DEM 在同一部件内同时使用 | 区别于"交界面耦合" |
| 界面键 | InterfaceBond | 连接 FEM 侧代理颗粒与 DEM 颗粒的弹簧键 | 来自 MultiFracS 文档 |
| 代理颗粒 | Proxy Particle / Virtual DEM Particle | FEM 边界处与节点绑定的 DEM 颗粒 | 运动由形函数插值，不独立积分 |
| 显式动力学 | Explicit Dynamics | 采用中心差分法的时间积分方案 | 无迭代，每步直接推进 |
| 幽灵力 | Ghost Force | 无外载荷时界面处的非物理残差力 | 量化标准：< 1% × 施加荷载 |
| 临界时间步 | Critical Time Step | 显式积分稳定的最大时间步长 | dt = α × L_min / c_wave |
| SOA | Structure of Arrays | 数据按分量而非对象组织的内存布局 | MultiFracS 全局采用 |
| Ce3D | — | 三维四面体单元本构 DLL（线弹性或MC本构） | 文件：`Ce3D.c/h` |
| Cjoint3D | — | 三维节理单元本构 DLL（Bilinear softening） | 文件：`Cjoint3D.c/h` |
| IbkFlag | — | 节理断裂状态标志（0=完整，1+=断裂） | 只读，不可手动设置 |
| CPUCORE | — | MultiFracS 主程序传给用户的全局数据结构 | 只读，字段不可修改 |
| CPUUSER | — | 用户自定义数据结构，可自由扩展 | 在 `Cpuuser.h` 中定义 |
| virbox | — | MultiFracS 的软件加密锁 | 运行时必须插入 USB |

---

## 公式符号表（核心）

| 符号 | 含义 | 单位 |
|------|------|------|
| $K_n$ | InterfaceBond 法向刚度 | N/m |
| $K_t$ | InterfaceBond 切向刚度 | N/m |
| $\delta_n$ | 法向相对位移 | m |
| $\boldsymbol{\delta}_t$ | 切向相对位移矢量 | m |
| $\sigma_t$ | 抗拉强度 | Pa |
| $N_i$ | 形函数 | — |
| $dt$ | 时间步长 | s |
| $l_p$ | 裂纹过程区长度（DEM区最小宽度参考）| m |
