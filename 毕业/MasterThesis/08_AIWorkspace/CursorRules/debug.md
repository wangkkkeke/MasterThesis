# debug.md — 调试规范

> 来源：`DevelopmentHistory.md` Bug记录+失败方案 + `CallGraph.md` + `inp数据格式文件5.8.md`

---

## 1. 退出码解读

**来源：** `DevelopmentHistory.md` 踩坑记录

| 退出码 | 十六进制 | 含义 | 首要排查 |
|--------|---------|------|---------|
| `4294967295` | `0xFFFFFFFF` | -1，程序异常返回 | virbox锁/DLL缺失 |
| `3221225477` | `0xC0000005` | 访问违规（NULL指针/越界）| 数组越界/空指针 |
| `33554435`   | `0x2000003` | 自定义错误码 | 查 stderr 输出 |
| `0`          | `0x0`        | 正常完成 | — |
| 非零其他值   | —           | 多为内存错误 | Valgrind/Dr.Memory |

---

## 2. 调试分层策略

### 第一层：静力学验证（必做）

**来源：** `DevelopmentHistory.md` 成功方案1

新本构或新模块上线前，必须先通过**悬臂梁静力学**验证：

```
验证指标：
1. 端点挠度 δ = FL³/(3EI)        误差 < 5%
2. 固定端应力 σ = M*c/I            误差 < 5%
3. 应力方向：上表面拉（正），下表面压（负）
4. 阻尼合理时程序稳定无发散
```

如果静力学通不过，禁止进行动力学或破坏性测试。

### 第二层：已知解析解算例

按复杂度依次：
1. 悬臂梁 → 验证 Ce3D 本构
2. 单轴拉伸 → 验证 Cjoint3D 节理起裂
3. 巴西劈裂 → 验证 Mode I 断裂
4. 圆孔应力集中 → 验证 FEM 精度

### 第三层：InterfaceBond 专项

1. 纯 FEM 区域（无 DEM）：应力场与参考解一致
2. 纯 DEM 区域（无 FEM）：颗粒运动与理论解一致
3. FEM-DEM 界面：Ghost Force 量级 < 1% 的荷载

---

## 3. 常见错误及排查路径

### 错误A：程序启动即崩溃（exit_code 0xC0000005）

**来源：** `DevelopmentHistory.md` 失败方案3（三轴压缩崩溃）

排查顺序：
```
1. 检查 DLL 是否存在且版本匹配
   → 在 exe 同目录查找所有需要的 dll

2. 检查 inp 文件关键字是否完整
   → 必须有 *Begin, *solve, *End

3. 检查数组越界
   → 循环中 ip < nfn（不是 <=）
   → CPUUSER 中分配的数组大小是否足够

4. 检查 NULL 指针
   → malloc 后是否检查返回值
   → CPUCORE 字段是否在 User_preprocess 后才能使用
```

### 错误B：应力输出量级错误（1000倍）

**来源：** `DevelopmentHistory.md` Bug002

```
排查步骤：
1. 检查 inp 中 E 的单位
   E = 2e10  → Pa（正确）
   E = 20000 → MPa（单位混用，错误）

2. 检查力边界 SBoundary 的量
   fx = 1e6  → Pa (压强，错误)
   fx = 1e6 * area → N (力，正确)

3. 运行悬臂梁基准，对比理论解
```

### 错误C：节理不断裂 / 断裂异常

**来源：** `DevelopmentHistory.md` IbkFlag 失败记录

```
排查步骤：
1. 检查强度参数量纲（Pa，不是 MPa）
2. 检查 IbkFlag 是否被手动设置（应删除）
3. 检查节理单元是否正确生成（Gmsh Physical Group 名称是否对应）
4. 检查荷载是否足够大（与强度同量纲比较）
```

### 错误D：Monitor Point 输出全零

**来源：** `DevelopmentHistory.md` 踩坑2

```
排查步骤：
1. 在 Gmsh 中找到最近节点坐标（Tools → Statistics 或查看 .msh 文件）
2. 将精确节点坐标填入 inp 的 *MonitorPoint
3. 重新计算
```

### 错误E：颗粒速度发散（显式动力学不稳定）

**来源：** `TheoryGuide.md` 显式动力学稳定性 + `DevelopmentHistory.md`

```
排查步骤：
1. 降低 TimeStepSize 倍率（如从0.5降到0.1）
2. 增加阻尼（damp_n, damp_s 从0.1增到0.5）
3. 检查 InterfaceBond Kn 是否过大（过大会降低临界时间步）
4. 检查 Rayleigh 波速计算：c = sqrt(E/ρ)，确认材料参数无误
```

---

## 4. MultiFracS 调试输出方法

由于 MultiFracS.exe 是闭源黑盒，调试信息只能通过：

### 4.1 Monitor Point（最推荐）

```
*MonitorPoint
x y z
```

输出到 `.csv` 文件，可在 Excel/Python 中分析时程曲线。

### 4.2 User_solver 内 printf

在 `User_solve()` 中可以使用 `printf`：

```c
// 每100步输出一次调试信息
if (nstep % 100 == 0) {
    printf("[Debug] Step=%d, maxVx=%.4e\n", nstep, maxVx);
}
```

输出到 MultiFracS 命令行窗口。

### 4.3 VTK 场量可视化（ParaView）

- 查看变形场、应力场、断裂状态
- Calculator：自定义场量（如 von Mises 应力）
- Threshold：过滤已破坏单元

---

## 5. 调试日志记录规范

每次调试后，在 `03_Development/Debug/` 下创建记录文件：

```
文件名格式：Debug_YYYYMMDD_现象简述.md

内容：
1. 现象描述（程序行为/输出）
2. 排查过程（尝试了什么）
3. 根本原因
4. 解决方案
5. 预防措施
```

---

## 6. Ghost Force 量化调试

**来源：** `TheoryGuide.md` §Ghost Force + `FormulaIndex.md`

Ghost Force 是 FEM-DEM 界面的非物理残差力。判断标准：

```
接受标准：
Ghost Force < 1% × 施加荷载

测量方法：
1. 在无外载荷情况下初始化 FEM-DEM 耦合模型
2. 统计界面节点/颗粒的不平衡力
3. 与施加荷载量级比较

Ghost Force 过大的原因：
- FEM 与 DEM 的刚度不匹配（Kn 需调整）
- 时间步在 FEM 侧与 DEM 侧不一致
- 界面颗粒速度映射不完整
```
