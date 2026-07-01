# Issue002：CPUUSER 数据结构设计（InterfaceBond专用字段）

**模块：** User_solver / Cpuuser.h
**状态：** OPEN
**优先级：** P0（InterfaceBond所有模块的数据基础）
**工作量：** 1天
**论文章节：** §3.2 InterfaceBond界面键力学模型 / §3.5 平台集成

---

## 任务描述

在 `Cpuuser.h` 的 `CPUUSER_struct` 中添加 InterfaceBond 所需的全部字段，
并在 `User_create.c` / `User_preprocess.c` 中完成内存分配与初始化。

## 需要添加的字段

```c
// InterfaceBond 键对信息
int    n_ibond;          // 识别到的界面Bond数量
int*   i1ibond_fid;      // [n_ibond] FEM侧代理颗粒ID（在DEM颗粒数组中的下标）
int*   i1ibond_did;      // [n_ibond] DEM侧颗粒ID
Real*  d1ibond_Kn;       // [n_ibond] 各Bond法向刚度（Pa/m）
Real*  d1ibond_Kt;       // [n_ibond] 各Bond切向刚度（Pa/m）

// Bond状态（历史变量，每步更新）
Real*  d1ibond_dn;       // [n_ibond] 法向相对位移累积（m）
Real*  d1ibond_dt_x;     // [n_ibond] 切向相对位移x分量（m）
Real*  d1ibond_dt_y;     // [n_ibond] 切向相对位移y分量（m）
Real*  d1ibond_dt_z;     // [n_ibond] 切向相对位移z分量（m）
int*   i1ibond_broken;   // [n_ibond] 断裂标志（0=完整，1=断裂）

// 标定参数
Real   ibond_Kn_default; // 全局默认法向刚度
Real   ibond_Kt_default; // 全局默认切向刚度
Real   ibond_ft;         // 抗拉强度（Pa）
Real   ibond_fs;         // 抗剪强度（Pa）
```

## 内存分配位置

`User_create.c` 中的 `Create_cpuuser()`：
- 分配结构体本身
- 指针字段先置 NULL（n_ibond 在 preprocess 后才能确定）

`User_preprocess.c` 中 `preprocess_cpuuser()`：
- 识别界面后（Issue003完成）才 malloc 各数组
- 初始化所有 d1ibond_dn = 0, i1ibond_broken = 0

## 测试方法

```
通过条件：
1. 编译无报错
2. 运行后 User_preprocess 中 printf n_ibond 值合理（>0）
3. 无内存泄漏（valgrind 或 Dr.Memory，或手动检查 malloc/free 配对）
```

## Review 要点

- [ ] 所有浮点字段是否使用 `Real` 类型
- [ ] 指针字段在 Create 阶段是否初始化为 NULL
- [ ] malloc 后是否检查返回值非 NULL
- [ ] n_ibond 确定后才 malloc，时序是否正确（在 Issue003 之后）

## 依赖

Issue001（编译框架通过）
