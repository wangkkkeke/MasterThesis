# coding.md — C语言编码规范

> 来源：`00_Project/C语言编程规范.txt` + `02_MultiFracS/Source/MultiFracS-User Developement-cpu/` 源码实证

---

## 1. 类型系统

### 1.1 浮点精度统一使用 `Real`（强制）

**来源：** `Real.h` 第1行

```c
// 默认双精度（当前配置）
#define Real double

// 单精度编译开关（取消注释启用）
//#define SinglePrecision
// #define Real float
```

**规则：**
- 所有物理量变量类型必须用 `Real`，禁止直接写 `float` 或 `double`
- 精度切换只需在 `Real.h` 中注释/取消注释一行，无需修改任何其他文件
- InterfaceBond 开发中所有新变量同样使用 `Real`

### 1.2 整数循环变量使用 `int`

**来源：** `Ce3D.c`, `Cjoint3D.c` 等

```c
for (int ip = 0; ip < 3; ip++) { ... }  // 正确
```

### 1.3 长整型使用 `LON`

**来源：** `Real.h`

```c
#define LON long long  // 2019-4-22添加
```

用于步数（nhstep）等可能超过 int 范围的计数器。

---

## 2. 数值常量

### 2.1 禁止魔数，必须使用预定义常量（强制）

**来源：** `Real.h` 全文 + `Cjoint3D.c` 使用示例

```c
// 已定义常量（必须使用这些，不要写字面量）
#define R0   0.0    // 零
#define R1   1.0    // 一
#define R2   2.0    // 二
#define R3   3.0    // 三
#define RP5  0.5    // 0.5
#define RP25 0.25   // 0.25
#define PI   3.1415926535897932384626

// 数值保护常量
#define SmallPositiveNumber  1.0e-10   // 防止除零
#define SmallNegativeNumber -1.0e-10
#define LargePositiveNumber  1.0e+15
```

**正确写法（来自 `Cjoint3D.c`）：**
```c
op = R2 * h * ft / pn;    // 正确：使用R2
sp = R2 * h * co / ps;
ot = R3 * gi / ft;        // 正确：使用R3
fD = R1 - ...;            // 正确：使用R1
```

**禁止写法：**
```c
op = 2.0 * h * ft / pn;   // 禁止：直接写字面量
```

### 2.2 防除零：使用 SmallPositiveNumber

**来源：** `Cjoint3D.c` 中的宏

```c
#define V3DNor(s,x1,y1,z1) \
    {(s)=sqrt((x1)*(x1)+(y1)*(y1)+(z1)*(z1));   \
    if((s)>SmallPositiveNumber)(x1)=(x1)/(s);  }
```

所有归一化操作必须先判断长度 > SmallPositiveNumber 再做除法。

---

## 3. 命名规范

**来源：** `C语言编程规范.txt` §1 + `Cpucore.h` 实际命名

### 3.1 变量命名（匈牙利前缀，来自 Cpucore.h）

| 前缀 | 含义 | 示例（来自 Cpucore.h） |
|------|------|----------------------|
| `n` | 计数（int） | `nfn`, `ndn`, `njelem` |
| `d1` | 一维Real数组指针 | `d1fnix`, `d1dnvx`, `d1dnmass` |
| `d2` | 二维Real数组指针 | `d2egestress` |
| `i1` | 一维int数组指针 | `i1enid`, `i1jenid`, `i1jebk` |
| `i2` | 二维int数组指针 | — |
| `d` | 单个Real变量 | `dtm`, `dampCn` |

### 3.2 函数命名（动词+名词，驼峰）

**来源：** `C语言编程规范.txt` §1.2 + 实际函数名

```c
Tet_constitutive_equation_increment()   // 正确：动词+名词组合
Cjoint3D_intact()                       // 正确：模块名+状态
User_node_velocity_boundary()           // 正确
preprocess_cpuuser()                    // 正确
```

### 3.3 常量命名（全大写+下划线）

```c
#define EType_C3D4  11       // 单元类型常量
#define JEInterfaceIntact 1  // 节理状态常量
#define JEBKT1 11            // 断裂类型常量
```

---

## 4. 格式规范

**来源：** `C语言编程规范.txt` §2 + 源码实际风格

### 4.1 缩进

使用 **Tab（制表符）**，等价4个空格（以实际源码为准，Ce3D.c用Tab）

### 4.2 大括号风格（K&R）

```c
// 正确（来自源码）
void Cjoint3D_intact(...) {
    if (o <= op && sabs <= sp) {
        D = R0;
    }
    else if (o > op) {
        D = (o - op) / ot;
    }
}
```

### 4.3 行长度

每行不超过80字符；函数参数过多时换行并对齐（参考 `Cjoint3D.h`）：
```c
USERDLL void Cjoint3D_intact(
    Real rs[][3], Real vnor[3], Real area,
    Real h,
    Real pn, Real ps, ...
);
```

---

## 5. 头文件保护

**来源：** `Seepage.h`, `Thermal.h`, `Moisture.h`

```c
#ifndef SEEPAGE_H
#define SEEPAGE_H
// ... 声明 ...
#endif
```

所有头文件必须有 `#ifndef` 保护。

---

## 6. 内存管理

**来源：** `C语言编程规范.txt` §4.2 + `User_create.c`

```c
// User_create.c 中的标准用法
CPUUSER cpuuser = malloc(sizeof(CPUUSER_struct));
// 配对 free（在析构时）
```

规则：
- malloc 后立即检查是否为 NULL
- malloc/free 必须成对出现
- 静态数组用 `Real name[N]`，动态用 `Real* name = malloc(n * sizeof(Real))`

---

## 7. DLL 导出宏

**来源：** `Real.h`

```c
#ifdef __linux__
    #define USERDLL extern
#else
    #define USERDLL __declspec(dllexport)
#endif
```

所有导出函数必须加 `USERDLL` 前缀，不得直接写 `__declspec(dllexport)`。

---

## 8. 函数规模

**来源：** `C语言编程规范.txt` §6

- 函数体不超过50行（建议）
- 参数个数不超过5个（建议），超出时考虑结构体打包
- `Cjoint3D_intact` 参数16个，属于特殊接口（固定签名不可改）

---

## 9. 注释规范

**来源：** `Mech.c`, `InSitu.c`, `FGM.c`

```c
// imat从0开始，按照*Material关键词在inp文件中出现的顺序进行整体编号
// damagej节理单元的损伤系数
// 将节理单元换热系数htj写成damagej或nstep的函数 *hjt=f1(damagej,nstep)
```

规则：
- 参数含义用中文注释说明（项目惯例）
- 说明参数的物理意义和取值范围
- 不写"做什么"，写"为什么"
