# style.md — 代码风格规范

> 来源：`02_MultiFracS/Source/` 实际源码风格 + `C语言编程规范.txt` + `Real.h` / `Cjoint3D.c` / `Ce3D.c` / `VBoundary.c` 直接观察

---

## 1. 文件头风格

**来源：** `Cjoint3D.c`, `Ce3D.c`, `SBoundary.c` 观察

```c
#include "Real.h"
#include "ModuleName.h"
#include <math.h>
#include <stdio.h>
```

规则：
- 自定义头文件（`Real.h`, 模块头文件）在前
- 标准库头文件在后
- 不引用不需要的头文件

---

## 2. 宏定义风格

**来源：** `Cjoint3D.c` 顶部宏块

```c
// 状态标志类：全大写，下划线分隔
#define JEISOFT1 1
#define JEISOFT2 2
#define JEBKT1   11
#define JEBKT2   12

// 内联运算宏：大写函数名，参数用括号保护
#define V3DDot(s,x1,y1,z1,x2,y2,z2) \
    {(s)=((x1)*(x2))+((y1)*(y2))+((z1)*(z2));}

#define V3DNor(s,x1,y1,z1) \
    {(s)=sqrt((x1)*(x1)+(y1)*(y1)+(z1)*(z1));   \
    if((s)>SmallPositiveNumber)(x1)=(x1)/(s);  \
    if((s)>SmallPositiveNumber)(y1)=(y1)/(s);  \
    if((s)>SmallPositiveNumber)(z1)=(z1)/(s);  }
```

规则：
- 状态常量对齐值（空格补齐使等号列对齐）
- 多行宏末尾用 `\` 续行，最后一行无 `\`
- 宏参数全部加括号防止运算优先级错误

---

## 3. 函数签名风格

**来源：** `Cjoint3D.h` + `VBoundary.h` + `SBoundary.h`

```c
// 长参数列表：每组参数一行，按物理意义分组
USERDLL void Cjoint3D_intact(
    Real rs[][3], Real vnor[3], Real area,   // 几何量
    Real h,                                  // 单元尺寸
    Real pn, Real ps,                        // 刚度参数
    Real co, Real fric, Real ft, Real gi, Real gii,  // 强度参数
    int imat, int* ijesf, int* ijebk, Real* damge, Real* d1jefs,  // 状态
    Real p1, Real p2, Real p3,               // 附加参数
    Real fnt[][3]                            // 输出
);
```

规则：
- `USERDLL` 必须是第一个词
- 输入参数在前，输出参数（指针）在后
- 参数超过5个时换行，按物理含义分组，并用注释说明每组

---

## 4. 局部变量声明风格

**来源：** `Cjoint3D.c` 函数体

```c
void Cjoint3D_intact(...) {
    // 变量全部在函数顶部声明（C89兼容风格）
    double op, sp, ot, st;
    double o, s, sabs, D, fD;
    int ip;
    Real n1, n2, n3;

    // 声明完毕后才开始逻辑
    op = R2 * h * ft / pn;
    ...
}
```

规则：
- 变量在函数顶部集中声明（C89风格，与 MinGW GCC 兼容）
- 同类型变量可以合并到一行
- 不在 for 循环括号中声明变量（兼容性）

---

## 5. 控制流风格

**来源：** `Cjoint3D.c` 条件分支

```c
// if-else 必须有大括号，即使只有一行
if (o <= op && sabs <= sp) {
    D = R0;
}
else if (o > op && o <= op + ot) {
    D = (o - op) / ot;
}
else {
    D = R1;
}

// 三元运算符用于简单赋值（不嵌套）
val = (condition) ? a : b;
```

规则：
- `else` 与 `}` 同行（K&R 风格）
- 复杂条件换行时，逻辑运算符放行首

---

## 6. 数组访问风格

**来源：** `Ce3D.c`, `User_solve.c`（SOA 模式）

```c
// SOA：按分量顺序访问，直观清晰
for (int ip = 0; ip < nfn; ip++) {
    d1fnvx[ip] += ax * dtm;
    d1fnvy[ip] += ay * dtm;
    d1fnvz[ip] += az * dtm;
}

// 二维数组：[粒子ID][分量]
for (int ip = 0; ip < 3; ip++) {
    fnt[ip][0] = n1 * force;
    fnt[ip][1] = n2 * force;
    fnt[ip][2] = n3 * force;
}
```

规则：
- SOA 数组按维度（x/y/z）分开循环，不要结构体
- 二维数组第一维为对象ID，第二维为分量

---

## 7. 注释风格

**来源：** `Mech.c`, `InSitu.c`, `FGM.c` 实际注释

```c
// 参数物理意义注释（中文，项目惯例）
// imat从0开始，按照*Material关键词在inp文件中出现的顺序进行整体编号
// pn: 法向刚度 (Pa/m)，ps: 切向刚度 (Pa/m)

// 算法关键步骤注释
// 计算等效开裂位移（Hillerborg模型）
op = R2 * h * ft / pn;

// 版本/修改记录注释
// 2019-4-22添加 LON 类型
// 2019-12-7重新添加 R27
```

规则：
- 参数注释写物理意义和单位，不写"赋值给xxx"
- 日期格式：YYYY-MM-DD
- 修改记录写在被修改行旁边，不单独建修改日志块

---

## 8. 输出调试风格

**来源：** `User_solve.c` 用法惯例

```c
// 调试输出：条件触发，附带步数标识
if (nstep % 100 == 0) {
    printf("[Step %d] maxVx=%.4e, tm=%.4e\n", nstep, maxVx, tm);
}

// 错误输出：用 stderr
fprintf(stderr, "[Error] Bond index %d out of range (n_ibond=%d)\n", id, n_ibond);
```

规则：
- 调试 printf 加 `[Step N]` 前缀，方便过滤
- 错误信息用 `fprintf(stderr, ...)`
- 正式提交前删除或注释掉调试 printf（影响性能）

---

## 9. 编译器兼容性

**来源：** `Real.h` 跨平台宏 + MinGW GCC 开发环境

```c
// 跨平台 DLL 导出（不要直接写 __declspec）
#ifdef __linux__
    #define USERDLL extern
#else
    #define USERDLL __declspec(dllexport)
#endif

// 跨平台安全字符串（Real.h 第一行）
#define _CRT_SECURE_NO_WARNINGS
```

规则：
- 不直接使用 MSVC 专属语法（`__cdecl`, `__forceinline` 等）
- User Function DLL 用 MinGW GCC 编译
- User Solver DLL 用 Visual Studio 编译（因为 CPUCORE 结构体依赖 MSVC ABI）
