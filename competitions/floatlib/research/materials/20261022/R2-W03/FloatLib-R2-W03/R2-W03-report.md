# FloatLib R2-W03：用可证明数值重构替代热循环 `Float32.ofBits`

研究日期：2026-10-22（Asia/Shanghai）  
研究范围：仅本轮任务说明、固定公开源码和本轮自造合成输入。  
最终状态：**数学成立；独立有限诊断通过；存在值得进入固定 Lean 环境验证的性能机会；Lean 编译、通用转换等价证明、官方 gate／整调用性能均未完成。**

## 1. 决策结论

**保留这条路线，首选“有符号纯常量表＋精确 UInt32 转换＋一次乘法”进入一次固定版本验证。不要先把无表实现当成更快的默认方案。**

本轮得出了四项可以改变下一步选择的结论：

1. 对 normal binary32，`M.toFloat32 * 2^(E-150)` 再施加符号，确实逐位重构原值。所有 `E=1..254` 都成立；`E=1..23` 的因子虽是 subnormal，乘积仍是精确 normal。主动把首个实现域限制为 `E>=24` 可减小证明和运行路径复杂度。
2. 固定 Lean 4.34.0 的 `UInt32.toFloat32`、`UInt64.toFloat32` 都是有公开逻辑模型的 `def`。无需 Float32→Float→Float32 往返，无需新 FFI 或公理。固定 FloatLib pin 已有尾零移位的 round 恒等式。
3. 可把一部分指数移进整数尾数，减少缩放常量：dense 7 档只需一个常量，wide 50 档只需两个常量。这在数学上成立，但新增分支可能让它更慢。
4. 本机独立 C 对照确实观察到：外部转换调用让累加器发生逐元素保存／恢复；内联重构命中路径消除了调用。但扩大到 64 个不同向量后，两常量 unsigned wide 方案在 wide 域反而从约 **1.27 ns/元素** 恶化到 **7.25 ns/元素**，慢于调用基线约 **3.70 ns/元素**；带符号表仍约 **1.00 ns/元素**。因此“去掉查表一定更快”已被本轮最小反例推翻。

这些数字仅是 **C surrogate** 的机制证据。它没有 Lean 实际输入对象、完整引用计数、数组边界路径及常量初始化代码，不能作为 Lean 性能、官方成绩或预计加速倍数。

### 证据分级

| 项目 | 本轮状态 | 能说明什么 |
|---|---|---|
| 固定公开源码读取与 SHA256 | 已完成 | 版本、定义、代码生成与默认编译选项可追溯 |
| normal 重构及整数移位推导 | 已完成数学推导 | 对所有允许的 sign/fraction 成立，不依赖计时数据 |
| 纯整数 RN-even 合成诊断 | PASS | 有限样本与精确反例；不是 Lean 证明 |
| 独立 C 转换／原序 sum 诊断 | PASS | 本机 native canonical-NaN 对照，不是 FloatLib raw 全域验收 |
| C 汇编检查 | 已完成 | 调用屏障、scalar mul/add、回退路径及无明显 DCE |
| Lean 片段编译 | **NOT_RUN** | 环境没有 lean/lake；未安装工具链 |
| 通用 `ConversionObligation` | **未闭合** | 交付定义和证明组件，没有冒充完成的定理 |
| SumObligation／BmmObligation／官方性能 | **NOT_RUN** | 本轮没有正式提交，也不提供验收成功声明 |

## 2. 固定合同与源码事实

固定版本是 Lean tag `v4.34.0`、FloatLib commit `0d91825727839f597fd06b22fdd038ea21480f0c`、官方 kernel 仓库 commit `978cc5b445edb9943fd9953b0a9037d97a9f33a8`。

官方 `ContractTensor.lean` 的 sum 是从 `posZero` 出发，对 `List.finRange n` 做 `ExecFloat.add` 左折叠；bmm 的每个输出按 k 左折叠，每步分别 `ExecFloat.mul` 后 `ExecFloat.add`。`BenchTensor.lean` 的长度是 1000，dense 指数 124..130，wide 102..151，relu 含约半数 +0，raw 另含特殊类。此轮没有改变这些定义、输入顺序、依赖或编译选项。[S1][S2][S3]

Lean runtime 的 `ofBits`／`toBits` 是外部函数；`ofBits` bit-cast 后规范化 NaN。C 头文件的 UInt32／UInt64 转 Float32、add、mul、neg 则是 inline C 算术。`Float32.ofBits` 的逻辑模型也会 canonicalize NaN。因此“转换等于原 native ofBits”与“保留 FloatLib 任意原始 NaN payload”是两种不同义务。[S4][S5][S6]

本轮只替代已经存在的转换点。既有 native 分支的有限性条件、原始位保存和 FloatLib 精确回退继续承担完整合同；没有把正在开发的 final-finite 守卫作为本轮新成果。

## 3. 原重构公式：完整证明

给定一个 UInt32 原始位型 u，定义

\[
s=u\gg31,\quad E=(u\gg23)\mathbin{\&}255,\quad
f=u\mathbin{\&}(2^{23}-1),\quad M=2^{23}+f.
\]

normal 条件为 `1<=E<=254`。其精确值为

\[
x=(-1)^s(1+f2^{-23})2^{E-127}
 =(-1)^s M2^{E-150}.
\]

binary32 的 24 位有效数、normal/subnormal 数值解释及正确舍入要求见官方数值指南。[S14] 以下结论由这些定义与本题合同直接推导。

### 3.1 整数转换没有误差

`0<=f<2^23`，所以 `2^23<=M<2^24`。M 的每一位都能装入 binary32 的 24 位有效数，正确舍入的整数转换精确返回 M。

不能把“一次整数转换”本身视为不精确步骤，再期待后面的乘法纠错；这里是前一步已经精确。

### 3.2 缩放因子自身可精确表示

当 `1<=E<=254`，`q=E-150` 满足 `-149<=q<=104`。每个 `2^q` 都可精确表示。其正位型为

\[
P(E)=
\begin{cases}
1\ll(E-1),&1\le E\le23,\\
(E-23)\ll23,&24\le E\le254.
\end{cases}
\]

前一段是 subnormal 的单个 fraction 位，后一段是 fraction=0 的 normal。

### 3.3 乘积也精确，不产生中间溢出

精确实数乘积 `M*2^(E-150)` 本来就是原编码 `E,f` 对应的 normal。最小值是 `2^23*2^-149=2^-126`；最大值是 `(2^24-1)*2^104`，恰为最大有限 binary32。既然乘积可表示，RN32 不改变它。

最后对非零有限值执行 native negation 可精确恢复 sign。normal 数值与符号唯一确定 bit pattern，因此得到的是逐位等价，而非仅实数近似。

重构步骤没有 tie，也没有两次不精确舍入互相抵消。精确性甚至不依赖 tie-breaking 的选择；完整 sum／bmm 仍严格使用合同规定的 RN-even。

### 3.4 最小有用域与不同边界

| 支持域 | 数学情况 | 本轮建议 |
|---|---|---|
| normal E=1..23 | 因子 subnormal，乘积精确 normal | 数学保留；首个候选回退以减少证明分支 |
| normal E=24..254 | 因子、输出均 normal | 首个通用表候选域 |
| normal E=102..151 | 50 个指数，覆盖题设 wide 与 dense | 更窄的充分域也合法；不是只证明计时样本 |
| raw +0 | 可直接返回已定义 +0 常量 | 必须仍执行后续原序 add；不是 skip-zero sum 优化 |
| raw -0 | 位型必须保留 | 首个实现原样回退 |
| subnormal E=0,f!=0 | 需改 M=f、因子2^-149 | 首个实现原样回退 |
| Inf／NaN E=255 | 不属于有限重构公式 | 转换层走原 ofBits；全算法仍保留 raw FloatLib 路径 |

对于题设数据，E>=24 的表候选覆盖全部 dense/wide normal；增加独立 +0 常量分支后，relu 的转换也基本全部命中。若 +0 仍走 ofBits，则 relu 约半数调用不会消失。

## 4. 边界、反例与完整回退

### 4.1 subnormal 和 signed zero

数学上可以把公式扩展到所有有限编码：E=0 时改用 `M=f`、`q=-149`；E>0 时保持原式。每个 `f*2^-149` 本来就是可表示的 subnormal 或 +0，最后真正取负可得到 -0。

但整数零没有负号；若使用 signed integer cast，不能指望 `Int32 0` 或 `Int64 0` 恢复 -0。首个候选保留负零回退最窄。实数值相等也不足以证明 +0 与 -0 的位型相等。

### 4.2 NaN 不能通过 native 通道再恢复 payload

`Float32.ofBits` 已经 canonicalize NaN。交付的候选定义在非命中输入直接执行同一个函数，所以其目标是逐点等于旧 native 转换，不能据此宣称任意 FloatLib 原始 NaN payload 已保持。

如果既有完整实现进入 native 路径前保存原始输入并在必要时回退，就只替换该路径中的转换表达式。一般证明方式是先证明 `∀u, convert u = Float32.ofBits u`，再用函数相等或循环归纳替换现有调用。无需结合律，无需重组有序 sum，也不改变 bmm 的 k 顺序及 mul→add 节点。

### 4.3 已固化的精确反例

| 错误方案 | 输入 raw | 错误值／中间值 | 正确 raw |
|---|---:|---:|---:|
| subnormal 仍补 hidden bit | `00000001` | `00800001` | `00000001` |
| E=0 沿用2^(E-150)，把2^-150先舍入为零 | `00000001` | `00000000` | `00000001` |
| E<24仍用 `(E-23)<<23`，UInt32回卷 | `00800000` | 因子`f5000000`，输出`ff800000` | `00800000` |
| 先乘2^(E-127)，最后再乘2^-23 | `7f000000` | 第一步已为`7f800000` | `7f000000` |
| DAZ把 subnormal 因子当零 | `00800000` | `00000000` | `00800000` |
| 用 `+0 - magnitude` 代替负号 | `80000000` | `00000000` | `80000000` |
| dense UInt32移位错误放行到E=133 | `42800000` | M左移9位回卷为0 | `42800000` |

DAZ 例属于违反 gradual-subnormal 前提的环境反例，不是合同内对正确公式的反例。本次 C 诊断已读取 MXCSR，FTZ=0、DAZ=0。

若确要覆盖 E<24 而避免 subnormal 因子，可先计算 `RN32(M*2^-23)` 得到精确 `[1,2)`，再乘 normal 因子 `2^(E-127)`；此顺序合法，但多一次乘法。反向顺序会中间溢出，见上表。

## 5. 更少常量的数学变体，以及为何暂不主推

### 5.1 通用“移位尾数＋块常量”定理

取起始指数 L、块宽 B，令

\[
j=\lfloor(E-L)/B\rfloor,\quad r=(E-L)\bmod B,\quad
N=M2^r,\quad C_j=2^{L+Bj-150}.
\]

只要整数移位不溢出、C_j 可表示，则 N 虽可能大于 `2^24`，仍最多只有 24 个有效位；额外低位全是零，因此整数→Float32 转换精确。随后

\[
N C_j=M2^{r+L+Bj-150}=M2^{E-150}
\]

又是目标 normal，乘法精确。

用 W 位无符号整数，`B<=W-23` 足以容纳所有 r；若要同时保证对应 signed 正范围，取 `B<=W-24`。实际代码还需证明定宽 shift 等于这个 Nat 移位，不能仅引用实数等式。

### 5.2 两个最窄可执行变体

**dense：** `124<=E<=130`，取 `N=M<<(E-124)`、`C=2^-26`。r<=6，N<2^30，UInt32 不溢出，只需要一个常量。

**wide：** `102<=E<=151`，分成两段：

- E=102..133：`N=(UInt64 M)<<(E-102)`，`C=2^-48`，N<2^55。
- E=134..151：`N=(UInt64 M)<<(E-134)`，`C=2^-16`，N<2^41。

这两个公式均对允许域的任意23位 fraction和sign成立。另一种更通用的32档分块从L=24开始，只需8个常量；题设wide只落在其中两个块。证明细节保存在 `analysis/SHIFT_REFINEMENT.md`。

### 5.3 符号与分支

表方案可把 sign 放进因子，直接索引 `u>>>23` 得到带符号 `2^(E-150)`。这样不必在每个 normal 上执行随机 sign 分支。

移位方案可先计算二补码 signed integer `(N xor mask)-mask`，其中 `mask=0-sign`，再调用 Int32／Int64 转换。dense 和 wide 的幅值界都满足 signed 范围，但这带来独立的 signed 解释与转换证明义务。

本轮数据说明这些选择不能只数操作条数：无表 wide 的随机 sign、指数分支在多向量对照中成为明显负担。有符号 wide 版本只完成单向量计时，多向量 **NOT_RUN**，不能将单向量好结果作为它已经解决问题的证据。

## 6. Lean 证明路线与交付代码边界

### 6.1 透明整数转换桥已经存在

固定源码定义了：

```lean
@[extern "lean_uint32_to_float32"] def UInt32.toFloat32 (n : UInt32) : Float32 :=
  .ofModel (.ofUInt32 n)
```

这个 extern 是既有 Lean primitive，本轮没有新增。其文件进入 `@[expose] public section`。mul、neg、ofBits 也有逻辑模型，所以不需要不透明的 Float32↔Float 往返。[S6][S7]

可直接写出的模型桥如下；本轮没有 Lean 工具，因此这些片段仍统一标 **NOT_RUN**，不把源码可展开性写成已编译证据：

```lean
import ContractTensor

theorem uint32_toModel (n : UInt32) :
    n.toFloat32.toModel = Float32.Model.ofUInt32 n := rfl

theorem uint32_mul_toModel (n scaleBits : UInt32) :
    (n.toFloat32 * Float32.ofBits scaleBits).toModel =
      Float32.Model.mul (Float32.Model.ofUInt32 n)
        (Float32.Model.ofBits scaleBits) := rfl
```

这证明的是与模型定义的连接，不是任意 u 的重构等价定理。

### 6.2 固定 pin 已有的关键定理

FloatLib 的公开 `Model.round_shiftLeft` 给出：

```lean
round spec sign (n <<< k) (e - k) = round spec sign n e
```

条件是 `n!=0`。另外有 `roundWithAccuracy_exact_eq_round_of_le_targetExponent` 与 `unpack_pack_finite_normal`。它们经 `ContractTensor → Contract → FloatLib` 的公开导入链可用，本轮无需升级 pin。[S8][S9][S10]

`ProofBridges.lean` 还给出 `round_at_target`、`round_normalized24`、`round_shifted24` 的证明文本。其中一个约12行的帮助引理根据固定 FloatLib 的 private 引理局部改写，保留 MIT 来源和许可证；没有直接调用 private 名称。

`round_shifted24` 的结论在 unpacked 模型上说明 `m.log2=23` 时 `round (m<<<k) 0 = finite m k`。它尚未证明 UInt shift 不回卷，也尚未证明最后 pack 的上界，不能被误读为完整 native conversion 定理。

### 6.3 仍须闭合的通用引理

1. 从 UInt32 位运算得到 `M=2^23+f`、`M.log2=23`、指数与符号的精确关系。
2. 整数转换后的 pack/unpack 是所需 finite 值；移位版另证 no-wrap。
3. 表长、下标界、每个被消费表项的精确位型；证明不可仅针对样本 fraction。
4. 把乘法的 `roundWithAccuracy ... .exact` 归约为目标 finite，再证明 pack 不溢出。
5. 符号恢复、+0 快路，以及其余输入定义上执行旧 ofBits。
6. 得到 `∀u, convert u = Float32.ofBits u` 后，替换已有 native 分支中的转换节点，保留原完整合同证明。

首轮选 E>=24 可以避开 subnormal 因子 pack/unpack 分支。不能以新增 `CorrectCast` 假设、未经证明的表正确性假设或有限样例代替上述结论。

### 6.4 signed casts 的额外可见性问题

`Int32.toFloat32`／`Int64.toFloat32` 是 model-backed def，但 `SInt/Float32.lean` 没有相同的 `@[expose]` 标记，不应只凭 unsigned 的 `rfl` 经验推断它们也能在此导入边界直接展开。固定 FloatLib 已提供公开 `toModel_ofFloat32_int32ToFloat32`／`...int64ToFloat32`，可以沿这些桥接，代价是更长的证明链。[S11][S12]

### 6.5 文件实际提供什么

`ConversionCandidates.lean` 只有 `import ContractTensor`，提供有符号表、dense UInt32、wide UInt64及其 signed 变体。常量用闭合 `Float32.ofBits` 定义，未走 Float64。`With` 入口允许调用者在循环外绑定表／常量；下标暂用总函数 `getD`，**其边界/default成本保留待检查，未假定被消除**。

文件最后定义 `ConversionObligation` 这个 Prop，并明确没有断言其成立。它不是完整 Kernel，也没有 SumObligation／BmmObligation。

`ProofBridges.lean` 给出桥接／round 帮助引理、10个具体 `by decide` 闭项以及 `#print axioms`。所有 Lean 文件都未编译；没有 proof hole、新公理或 `native_decide`。两文件合计约12 KB，远低于256000字节；正式合并时仍须对实际完整 Kernel 重新计 UTF-8 字节数与公理集合。

## 7. 代码生成：真正可能省下什么

### 7.1 收益可能来自调用边界

本轮 C 汇编的基线热循环包含：

```text
load input word
store accumulator to stack
call runtime_of_bits
reload accumulator
addss
```

重构命中路径包含字段提取、整数转float、乘法、addss，不需要每元素外部调用。减少调用不仅省 call/ret，也可能减少 caller-saved 寄存器压力和累加器 spill。该形状已在自写 C surrogate 中观察到；**实际 Lean 生成代码仍 NOT_RUN**。

原序 sum 的加法依赖链依然存在。没有由此推导自动 SIMD reduction，也没有把跨输出 bmm、预转换数组或分段重结合列为本轮成果。

### 7.2 常量表不是免费 C float 数组

固定 Lean 的通用 `Array Float32` 是对象数组。读取可能涉及数组对象、元素指针和 boxed Float32 unbox；其读取路径是否带引用计数、边界判断，要看生成的借用与特化结果。`FloatArray` 使用的是 Float（binary64），不是可未经证明使用的 Float32 原始数组。[S4][S13]

普通无参数命名 def 在模块初始化中可赋给全局，后续直接读取。编译器自动提升的 closed 值则可能使用 `lean_float32_once`／`lean_obj_once`；热路径有状态检查。不能笼统断言所有常量每次重建，也不能笼统断言所有常量都免费成为 rodata。[S13]

建议用纯、命名、与输入无关的常量表，在每次 sum 调用进入循环前绑定；实际检查是否仍在热循环出现初始化访问、RC 或分配。不要对含表的定义无判断地加 inline，导致字面量或闭合项被复制。

### 7.3 初始化总账

本轮示例使用512项有符号表，直接由 `u>>>23` 索引；只消耗E24..254项，其余槽无意义但定义为 signed zero。这样索引简单，但冷启动包含512次因子构造以及数组／boxed值构建。实际 Lean 对象内存不等于512×4字节。

更窄的E102..151域可以用50个正因子或100个带符号因子，减少初始化与存储，但多出索引归一化／符号处理。它尚未测量，不能把较小表直接宣称为更快。

完整成本应记录：

\[
T_{\rm total}=T_{\rm module/table\ init}+T_{\rm invocation\ setup}
+\sum_i T_{\rm guard+decode+add}(u_i)
+T_{\rm fallback}+T_{\rm result/cleanup}.
\]

表在进程生命期内是否重复、哪些初始化发生在官方计时窗口外，都必须明确。本题要求计入准备成本，因此至少同时报告新进程冷总时间和既定官方计时窗口，不能用窗口外初始化冒充无成本。

### 7.4 FMA 与编译选项

Lean v4.34.0 的 `src/CMakeLists.txt` 明确把 `-ffp-contract=off` 加入 `LEANC_EXTRA_CC_FLAGS` 与 `LEAN_EXTRA_CXX_FLAGS`；Lake release 默认 `-O3 -DNDEBUG`。本轮没有改动这套参数。[S15][S16]

仍需检查实际固定环境构建日志及生成汇编，确认没有其他覆盖。即使重构乘法在数学上精确，也不能因此擅自违反用户明确的 no-FMA 约束；尤其 bmm 原来的 mul/add 节点不可融合。

## 8. 实际诊断与能支持的结论

### 8.1 精确整数 RN-even 诊断

`diagnostics/exact_dyadic_checks.py` 不依赖宿主float，使用Python整数实现dyadic RN-even编码。每个指数选187种结构化fraction，覆盖零、低位边界、各二次幂附近及最大fraction附近，并取两个sign。

| 数学表达 | 实际检查数 | 结果 |
|---|---:|---|
| 原normal公式及安全两阶段公式 | 94,996 | PASS |
| 通用finite公式（含subnormal/±0） | 95,370 | PASS |
| dense UInt32移位 | 2,618 | PASS |
| UInt32八档分块 | 86,394 | PASS |
| UInt64三十二档分块 | 86,394 | PASS |

这些集合有重叠，不能相加当成互异输入数；也不是2^32穷举。7项精确反例另有断言和结果文件。

### 8.2 C 环境与正确性对照

环境为本次容器的 AMD EPYC 9V74 x86-64、GCC 13.3.0。独立诊断按多个翻译单元编译、无LTO，使用 `-O3 -std=c11 -ffp-contract=off -fno-fast-math`。没有执行／修改官方项目的编译或gate。日志确认：binary32 24位有效数、RN、`FLT_EVAL_METHOD=0`，MXCSR=`0x1f80`，FTZ=DAZ=0。

默认合成数据种子取运行时钟并记录，候选实现完全不依赖seed，也不缓存结果。可显式给seed只用于复现诊断输入，不参与准入条件或生产算法。

转换检查共 **4,194,448次比较**，来自 **524,306个输入位置**（256个指数各2048个随机位位置，加18个特殊输入），八个入口中还包括基线自比。不能称为419万个互异随机数。四类1000项sum比较共32次；扩展pool另有960次比较。全部通过 native canonical-NaN 对照。

raw sum最终是canonical NaN，可能掩盖后续错误；该对照不证明payload传播，也不证明完整FloatLib contract。relu-like合成生成器的归零选择与fraction使用同一随机字的最低位，非零fraction具有相关性；任意fraction的支持来自数学证明目标，而非这些样本。

### 8.3 单个1000项数组反复运行：容易乐观

下表为最终日志中的中位数，单位ns/元素；11轮、每轮重复4000次相同数组。它包含该C实现的guard、转换及逐项add，不包含表初始化与输入生成。

| C surrogate | dense | relu-like | wide |
|---|---:|---:|---:|
| 外部ofBits调用 | 3.7750 | 3.6183 | 3.5441 |
| 仅+0常量快路 | 3.6347 | 2.3701 | 3.5947 |
| 带符号flat表 | 0.8824 | 0.8511 | 0.8959 |
| 带符号boxed表近似 | 0.8866 | 0.8535 | 0.9204 |
| dense移位＋signed32 | 1.1771 | 0.8736 | 3.1575 |
| wide两常量＋UInt64＋sign分支 | 1.1484 | 0.8950 | 1.2671 |
| wide两常量＋signed64 | 1.3412 | 0.9089 | 1.4151 |

如果只看这组结果，会高估无表方案对新向量的表现。

### 8.4 64个不同向量的pool：本轮最有价值的证伪

补充对照使用64×1000个原始UInt32输入，256000字节连续pool；每向量仍从+0原序执行，每次sweep观察64个结果的checksum。没有预转换输入数组。此时分支历史不再局限于同一个短数组，输入也不全驻留于L1。

| C surrogate | dense | relu-like | wide |
|---|---:|---:|---:|
| 外部ofBits调用 | 3.4661 | 3.6075 | 3.6984 |
| 仅+0常量快路 | 3.5897 | 3.4846 | 3.6130 |
| 带符号boxed表近似 | **0.8446** | **2.0746** | **1.0031** |
| dense移位＋signed32 | 1.1199 | 3.6724 | 3.3627 |
| wide两常量＋UInt64＋sign分支 | 4.2111 | 3.2224 | **7.2452** |

wide signed64未纳入pool，本格性能为NOT_RUN，不能用上一表替代。

**观察：** 无表wide方案在wide反慢，而有符号表仍显著低于本地C调用基线。**推断：** 生成汇编仍含随机sign和指数条件分支，单短数组重复执行的预测优势可能是差异的重要来源；本轮没有硬件分支计数器证据，因此不把这个归因写成已量化结论。

这支持将带符号表列为首个Lean候选，并把当前unsigned wide无表形态暂存。它也说明单看算术指令数会做出错误排序。

### 8.5 冷成本的有限观察

一次新进程样本记录：baseline 1000项3425ns；C静态表初始化2574ns；初始化加boxed 1000项3435ns。这个样本不构成稳定性能结论，更不能视为Lean初始化的上下界：C表是静态存储，没有Lean堆对象分配和引用计数，且同一次初始化同时准备flat/boxed对照。

pool的输入生成也在日志中单列。它属于诊断输入构造；生产候选的准备成本主要是其自身常量／表与loop setup。本轮没有预先转换输入后把转换成本藏到计时外。

## 9. 最小固定版本验证与停止条件

下一步只需要一次有边界的开发验证，不需要继续扩大数学路线：

1. 在已有固定工程中编译 `ProofBridges.lean` 与 `ConversionCandidates.lean`，保留完整错误日志及 `#print axioms`。先修语法／可见性问题，再补通用转换定理。不要升级工具链或依赖。
2. 首个正式等价目标选带符号表的 E24..254＋+0，其余转换逐点回退。完成表索引／表项／整数转换／乘法pack链，再把已有native循环的ofBits替换掉。
3. 以原完整kernel作基线，比较“+0转换控制”与“带符号表转换”。只替换转换，其他守卫、fallback、输入读取、结果写回及sum顺序保持同一实现，才能归因。
4. 保存真实生成C与汇编：检查命中路径无ofBits/toBits或额外helper调用、无逐元素分配、表读取的RC/bounds/once成本，以及没有FMA或重结合。若未内联，先把它视为代码生成失败，不把C surrogate数字移植过来。
5. 用原gate验证全输入合同与raw类，用固定bench记录官方窗口，同时另报进程冷启动／表初始化／首次调用／稳态完整调用。全部准备、回退与清理均入账。

**停止／重访标准：**

- 无法在现有公开证明依赖与256000字节内完成通用等价，停止该实现，不用新公理或样本替代。
- 实际Lean热路仍有每元素ofBits、分配或显著RC/default/once路径，先定位这个具体原因；不得直接引用本地C速度比。
- 在原计时规则、完整成本及独立合成输入下不胜基线，就否决这版。后续仅在更好的表表示、可证的signed cast代码形态、或不同实际ABI证据出现时重访。
- 当前unsigned wide两常量实现已有pool负例，暂不投入完整证明；signed64多向量表现未知，也不列为已胜者。

## 10. 复现与文件结构

ZIP内包含完整报告、两个Lean片段、纯整数诊断、C有限诊断源码／脚本、运行日志／汇编、三份独立审查说明、固定源码URL与SHA256清单、FloatLib许可证及包内SHA256清单。没有捆绑工具链、依赖构建产物或任何旧私有资料。

在已有固定Lean工程的环境中（不修改lakefile）：

```bash
lake env lean /absolute/path/to/ProofBridges.lean
lake env lean /absolute/path/to/ConversionCandidates.lean
```

这两条本轮均NOT_RUN。C/Python复现从解压目录运行：

```bash
python3 diagnostics/exact_dyadic_checks.py
bash diagnostics/run_diagnostic.sh
```

运行脚本会在其自身诊断目录产生本地构建／日志，不提交任何项目。正式证明未完成前，不应把这些候选当作可提交Kernel。

## 11. 一手来源与审计入口

本报告的公式、反例、C诊断和排序结论为本轮推导／测量。源码事实由下列固定链接支持；实际下载文件的完整SHA256见 `sources/source_manifest.json`。

- [S1] [官方 ContractTensor.lean（固定commit）](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/contract/ContractTensor.lean)
- [S2] [官方 BenchTensor.lean（固定commit）](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/bench/BenchTensor.lean)
- [S3] [官方 lakefile.lean（固定commit）](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/lakefile.lean)
- [S4] [Lean v4.34.0 lean.h](https://github.com/leanprover/lean4/blob/v4.34.0/src/include/lean/lean.h)，重点3253..3272及array／unbox／once函数。
- [S5] [Lean v4.34.0 object.cpp](https://github.com/leanprover/lean4/blob/v4.34.0/src/runtime/object.cpp)，重点1987..2004。
- [S6] [Lean v4.34.0 Float/Float32.lean](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Float/Float32.lean)，重点13、38..44、90..109、132..146、303..316。
- [S7] [Lean v4.34.0 Model/Float32.lean](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Float/Model/Float32.lean)
- [S8] [FloatLib Native/Integer/Constructors.lean（固定pin）](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/IEEE754/Native/Integer/Constructors.lean)，公开round_shiftLeft与private帮助引理。
- [S9] [FloatLib ModelRounding/Proof.lean（固定pin）](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/ModelRounding/Proof.lean)
- [S10] [FloatLib Model/Packing/Finite.lean（固定pin）](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Model/Packing/Finite.lean)
- [S11] [Lean v4.34.0 SInt/Float32.lean](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/SInt/Float32.lean)
- [S12] [FloatLib Native/Integer/FromInt.lean（固定pin）](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/IEEE754/Native/Integer/FromInt.lean)
- [S13] [Lean v4.34.0 LCNF/EmitC.lean](https://github.com/leanprover/lean4/blob/v4.34.0/src/Lean/Compiler/LCNF/EmitC.lean)、[Array/Basic.lean](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Array/Basic.lean)、[FloatArray/Basic.lean](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/FloatArray/Basic.lean)。普通命名定义与closed-term cache区分见EmitC对应生成分支。
- [S14] [Oracle Numerical Computation Guide，IEEE Arithmetic](https://docs.oracle.com/cd/E19059-01/stud.10/819-0499/ncg_math.html)，第2.1.1节与表2-2／2-3。
- [S15] [Lean v4.34.0 src/CMakeLists.txt](https://github.com/leanprover/lean4/blob/v4.34.0/src/CMakeLists.txt)，219..221，关闭浮点收缩。
- [S16] [Lean v4.34.0 Lake/Config/LeanConfig.lean](https://github.com/leanprover/lean4/blob/v4.34.0/src/lake/Lake/Config/LeanConfig.lean)，117..121，release C优化参数。

最终决策：**GO，仅进入固定Lean的带符号表转换验证；没有授予性能或形式验收。当前无表wide分支实现PARK，等待新的代码生成／多向量证据。**
