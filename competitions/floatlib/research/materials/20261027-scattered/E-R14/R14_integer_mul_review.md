# R14 正常域纯整数乘法候选 6f8808d0：严格审阅

日期：2026-10-25（Asia/Shanghai）  
对象：已接入 `Submission.mul`、当前 `NOT_COMPILED` 的完整 Kernel。  
结论：**确认 1 个 Lean 证明名称错误；未发现所审正常域整数算法的数学反例；性能未知。最小补丁仅改一个证明引用，补丁编译状态仍为 `NOT_RUN`。**

## 1. 决策所需的三项结论

| 项目 | 结论 | 证据边界 |
|---|---|---|
| 确认的 Lean 阻断 | `R14DIntegerNormal.core_word` 第 3649 行引用 `FastMul.mkW_eq`；父本实际提供 `FastMul.mkW_ofNat`，两者不是同名声明。 | 可由完整源码和已有定理类型静态确认；没有伪造编译器错误日志。 |
| 数学与 public mul 接线 | 未发现反例。乘积容量、23/24 位移、偏置 RNE、carry/fraction、指数截减、真实 Pmax、guard/fallback 和 public mul 均有具体对应关系。 | 下文给出推导及源码位置；不等于所有 Lean tactic 已通过。 |
| 性能接受缺口 | 重复 `productWord`/`roundedWord` 是否共享，以及守卫、变量移位、最终 caller 成本未知。 | 新生成 C、最终汇编、完整 25 轮和冻结新输入确认全部 `NOT_RUN`。不能给出加速比。 |

本次没有发现第二个可以靠现有证据坐实的数学或 Lean 缺陷，因此不把未执行的 `simp`、`omega` 或 `rw` 风险包装成确定错误。不创建运行变体或阈值网格。

## 2. 输入、约束和实际执行范围

### 2.1 原件身份

| 文件 | UTF-8 字节数 | SHA256 |
|---|---:|---|
| `astra-web-pro-integer-6f8808d0-input.txt` | 253520 | `6f8808d0a6ea0c05e0ba2416a583e5ce388fa75f2ce62b04c408d2699b048dc3` |
| `astra-web-pro-native-reference.txt` | 10380 | `b2bb153c1e20e2e7ab0046f0e25583c4645cc5fc69ce9f94a2bbd482909a86f8` |

两者均已读取原始本地字节并计算哈希。下文 `[K:行号]` 指第一份原件的行号；`[N:声明]` 指第二份冻结的一次 FP 参考。该参考没有被当作候选的额外导入，也没有被改写。

固定版本：Lean 4.34.0，commit `293d5d0c0c3f3dded4688b3ccd6a33939ac5102b`；FloatLib commit `0d91825727839f597fd06b22fdd038ea21480f0c`。

源码检查结果：只有 `import ContractTensor`；253520 < 256000；唯一显式 `set_option` 是原件中的 `maxRecDepth 8192`；全文没有 `sorry`、`admit`、`axiom`、`unsafe`、`extern`、`implemented_by` 或 `native_decide` 标记。**这些是文本检查，不是传递公理审计。**

没有找到现成 Lean/lake/elan 可执行文件或已安装的精确版本工具链。没有安装工具链、编译候选、修改 gate/bench/编译参数、启动 CI、推 Git 或公开源码。已有 compact 父本通过原 gate 是用户提供的前提，本次不将其重新表述为亲自执行的结果。

本次实际执行：字节/哈希检查；新增声明和依赖的静态审阅；固定版本主源核对；独立复核；少量具体整数边界样例的算术核算；修复片段与原声明的精确差异比较。没有运行 Float32 候选或性能套件。

## 3. 确定问题与精确最小修复

### F1：打包桥使用了不存在的定理名

位置：`Submission.R14DIntegerNormal.core_word`，[K:3634–3650]。其中第 3649 行是：

```lean
          FastMul.mkW_eq _ _ _
```

完整文件只有这一处 `mkW_eq`，没有对应声明。已有父本 [K:2206–2210] 实际声明：

```lean
theorem mkW_ofNat (sign : Bool) (e f : Nat) :
    mkW sign (UInt32.ofNat e) (UInt32.ofNat f) = mkBits sign e f := by
  unfold mkW mkBits
  cases sign <;> rfl
```

它正好提供当前 `calc` 第二步所需的类型：取 `sign := R14ExponentShift.sign u v`、`e := (exponentWord u v).toNat`、`f := (fractionWord u v).toNat`。不需要添加公理、额外前提、运行包装或新打包定理。

精确最小差异：

```diff
-          FastMul.mkW_eq _ _ _
+          FastMul.mkW_ofNat _ _ _
```

影响：原件不能据当前证明声称 public `mul_spec` 已闭合。该错误处于 `DIntegerNormal.core_word → ExponentShift.core_word → core_model → core_spec → guardedMul_spec → Submission.mul_spec` 的实际依赖链中，不是未使用的旁支。

交付的 `R14_integer_mul_fixes.lean` 只包含该定理的完整替换片段。它沿用原位置已经打开的 namespace/open；应在原 namespace 内替换原声明，不能在文件尾追加同名声明，也不能再套一层同名 namespace。片段不是独立 Kernel，没有添加 import，也没有任何运行定义。

| 应用方式 | 结果 |
|---|---|
| 只对原件做上述唯一字符串替换 | 253523 B，余量 2477 B |
| 该唯一替换的预期完整 Kernel SHA256 | `b8a11a6a1c647df5031505b7effa5c3d21e653631db0638815a3062c7d20b6c2` |
| 替换片段字节数 / SHA256 | 1428 B / `80db9437246cc5b5339f37f39ebdff4c2810e4f449b999d27c480fa6314dc1af` |

预期完整哈希由原字节应用这一个替换计算，未改写输入附件。片段内的定理体已逐字核对，除定理名替换外与原声明一致。**该修复静态类型意图明确，但修复后整包仍为 `NOT_RUN`；不能据此承诺只剩这一个编译问题。**

## 4. 数学审阅：各边界成立的原因

记输入的 24 位有效数为 `Mx`、`My`，原始指数域为 `Ex`、`Ey`，并令：

\[
P=M_xM_y,\quad S=E_x+E_y,\quad h=P\mathbin{\gg}47,\quad t=23+h.
\]

### 4.1 24×24 乘积与位移选择

`R2W01b.mantissa` 用 fraction 加隐含位构造机器字，已有 `mantissa_bounds` 给出：

\[
2^{23}\le M_x,M_y\le2^{24}-1.
\]

因此：

\[
2^{46}\le P\le(2^{24}-1)^2
=2^{48}-2^{25}+1
=281474943156225<2^{48}<2^{64}.
\]

`productWord` 先把两个 UInt32 扩宽到 UInt64 再乘，因此没有先在 32 位乘法中截断的问题。`productWord_nat` 使用真实 `UInt64.toNat_mul` 和扩宽引理，把 `% 2^64` 用上界消掉。[K:3476–3493]

`log2 P` 只能是 46 或 47，而 `P >>> 47` 恰好是对应的 0 或 1。于是 `shiftWord = 23 + highWord` 确实等于 `log2 P - 23`，只取 23/24。`highWord_nat`、`shiftWord_values`、`shiftWord_nat` 连接的是实际机器定义；运行时没有调用 `log2`。[K:3495–3538]

### 4.2 偏置舍入等于 ties-to-even，且中间值不回卷

令 `D=2^t`、`H=D/2`，写成 `P=qD+r`，其中 `0≤r<D`。候选实现：

\[
R=\left\lfloor\frac{P+H-1+(q\bmod2)}D\right\rfloor.
\]

分析 `r+H−1+(q mod 2)`：

| 余数条件 | 是否产生加一 | 与原 RSE 的关系 |
|---|---|---|
| `r < H` | 否 | 小于半数，向下 |
| `r > H` | 是 | 大于半数，向上 |
| `r = H` 且 q 偶 | 否 | 保持偶商 |
| `r = H` 且 q 奇 | 是 | 舍入到下一偶数 |

这给出任意 Nat `p`、`t∈{23,24}` 的 `nat_bias` 数学等式。固定 FloatLib 的 `roundQuotientEven` 和 `roundShiftRightEven_eq_roundQuotientEven` 正是该语义，后者没有遗漏的附加前提。[K:3413–3422；源 S2、S3]

对机器字桥，`H∈{2^22,2^23}`，parity∈{0,1}。在 `P<2^48` 下，加偏置全过程小于 `2^48+2^23<2^49`；`P+H≥1` 保证减 1 不下溢。因此实现的每一步与 Nat 等式一致。`word_bias` 显式处理了位移计数 `%64`、低位奇偶、加法模数和减法前提，并通过 `UInt64.toNat_inj` 回到真实 UInt64 等式。[K:3424–3463]

固定源中 `FixedWord.roundShiftRightEven_toNat` 对所有 UInt64 value 和 Nat shift 成立，不要求在使用处另补输入大小或 shift 界；本文并未误把有条件引理当无条件引理。[源 S4:68–71]

候选用 `roundedWord_nat` 把 `biased` 接到 `R14NatNormal.rounded`。与旧 `FastMul.rse` 的联系也具体存在：旧 `FastMul.rseAny_eq` [K:2182–2203] 连接同一 FixedWord rounder；在 23/24 时 `rseAny` 的定义直接选择原 `rse` 分支。因此不是只证明了一个与旧运行舍入器无关的抽象公式。

### 4.3 carry 与 fraction

舍入前的商在 `[2^23,2^24−1]`，RNE 至多加一，故：

\[
2^{23}\le R\le2^{24}.
\]

于是 `R >>> 24` 等于 1 当且仅当 `R=2^24`，否则等于 0；与 `R14NatNormal.carry` 的等值判断一致。[K:3548–3575]

fraction 用 `R & (2^23−1)`：若没有进位，它等于 `R−2^23`；若 `R=2^24`，它等于 0，正好对应规范化有效数改成 `2^23` 后的尾数。这里不能一般地把进位分支省掉，但当前以掩码处理该分支是正确的。[K:3581–3582、3621–3632]

### 4.4 真正的 Pmax 排除 h=1 的进位

在 `h=1` 时，`t=24`。真实上界给出：

\[
\left\lfloor\frac{P}{2^{24}}\right\rfloor
\le\left\lfloor\frac{2^{48}-2^{25}+1}{2^{24}}\right\rfloor
=2^{24}-2.
\]

即使商增加 1，R 也至多为 `2^24−1`，所以 carry=0。候选 `no_carry_at_47` 正是这一论证；`middle_bounds` 在 log2=47 分支实际调用它，`core_model.hmax` 又实际使用 `middle_bounds`。[K:3220–3231、3363–3378、3683–3689]

边界说明，**不是候选反例**：若把真实上界错误地弱化到单独的 `P<2^48`，可取 `P=2^48−1`。此时 h=1、R=2^24、carry=1；在 S=380 会得到 exponent 255。这个 P 不可能由本域两个 24 位有效数产生。当前代码保留真实 Pmax，因此排除了该情况。

反过来，h=0 的进位真实存在：`Mx=8388609, My=16777214` 给出 `P=2^47−2`，RNE 得 `R=2^24`。当前 `carryWord` 保留了它。

### 4.5 指数表达式与 Nat 截减

令 `c=carry`。运行式为：

\[
E_{out}=S-127+h+c.
\]

guard 保证 `S≥128`，所以运行 UInt32 的 `S−127` 没有下溢；`ex` 各自小于 256，初始和也不会在 UInt32 中回卷。后续加上 h、c 同样远低于 `2^32`。`exponentWord_nat` 是在这些前提下消掉实际机器模数。[K:3593–3619]

数学桥中的写法是：

\[
\operatorname{middleExponent}(P)+E_x+E_y-300
=\operatorname{middleExponent}(P)+S-300.
\]

这里 subtraction 位于总和之后；不能改成 `middleExponent + (S−300)`，因为 Nat 减法截零。例如 middleExponent=173、S=128 时，前式为 1，后式为 173。当前源码没有犯这个重结合错误。

由 `log2 P=46+h`、`middleExponent=log2 P+c+127`，以及 h=1 时 c=0，可得 `173≤middleExponent≤174`。故在 `128≤S≤380` 下：

\[
1\le E_{out}\le254.
\]

最终结果严格处于 normal 域。`core_model` 的最小指数界和包括 carry 的最大指数界与实际 `NativeBinary32.roundDyadic` 分支吻合；没有以“尚未进位的指数不溢出”代替“最终指数不溢出”。[K:3263–3285、3671–3708；源 S5]

## 5. 准入、异常值与公开规格接线

### 5.1 guard 是机器字谓词，域外完整回退

实际准入式 [K:3727–3730]：

```lean
(decide (ex u - 1 ≤ 253) && decide (ex v - 1 ≤ 253)) &&
  decide (ex u + ex v - 128 ≤ 252)
```

因为 `ex∈[0,255]`，UInt32 的 `ex−1≤253` 恰好选择 1..254：0 减 1 得 `0xffffffff` 被拒绝，255 减 1 得 254 也被拒绝。因为 `ex u+ex v≤510`，和减 128 的回卷值不可能误落入 0..252；该比较恰好选择 S=128..380。

| 输入/输出边界 | 新增层的行为 |
|---|---|
| 两输入 normal 且 S=128..380 | 纯整数核心 |
| 任一输入 exponent=0，包括 subnormal 和 ±0 | 原始 x、y 传给 `mulBeforeExponent` |
| 任一输入 exponent=255，包括 Inf、qNaN、sNaN | 原始 x、y 传给 `mulBeforeExponent` |
| 两输入 normal，但 S 在区间外 | 原始 x、y 传给 `mulBeforeExponent` |

`guardedMul` 的失败分支没有先执行 `Float32.ofBits`、修改 raw word 或规范化 NaN。[K:3747–3750] 因而新增层不改变旧路径的 NaN 选择、payload/符号与 signaling quieting 规则，也不改变旧路径对 Inf、subnormal 和 ±0 的处理。这里说的是保持原规格行为，不是承诺 signaling NaN 的输出保持 signaling 状态。

### 5.2 public mul 确实绑定了新核心

源码顺序与依赖为：

1. `mulBeforeExponent` 与其 spec 已在新增模块前声明。[K:3153–3164]
2. `R14DIntegerNormal.core` 使用 `FastMul.mkW` 打包 exponentWord/fractionWord。[K:3584–3585]
3. `R14ExponentShift.core` 是上述整数核心的直接别名。[K:3659]
4. `core_word → core_model → core_spec` 连接真实字到 `ExecFloat.Spec.mul`；其中 F1 的打包桥必须先修复。
5. `eligible_conditions` 为 guard 成功建立实际域前提；`guardedMul_spec` 分别使用核心 spec 和旧 fallback spec。
6. 最终公开定义与证明 [K:3766–3770] 是：

```lean
@[inline] def mul (x y : Binary32) : Binary32 :=
  R14ExponentShift.guardedMul mulBeforeExponent x y

theorem mul_spec (x y : Binary32) : mul x y = ExecFloat.Spec.mul x y := by
  exact R14ExponentShift.guardedMul_spec mulBeforeExponent mulBeforeExponent_spec x y
```

后面还用该 `mul_spec` 建立 `mul_eq`。没有把新算法仅挂在一个无人调用的 helper 名称下。此结论仅确认 public scalar mul 的接线，不能据此声称已有原生 BMM 快路的每次乘法都会自动走该核心。

## 6. 运行核心与可证伪成本分析

### 6.1 源码正常路径没有偷偷使用 Nat/log2/Float32

实际正常域调用图包括 `eligible/ex`、`productWord/highWord/shiftWord/roundedWord`、`R14BiasRNE.biased`、`carryWord/exponentWord/fractionWord`、`FastMul.mkW` 和 `R7W02.fromRaw`。数据运算是 UInt32、UInt64 与 Bool。

`productNat`、`middleExponent`、`storedFraction`、`R14NatNormal.rounded`、Nat.log2 和 FixedWord RSE 出现在证明表示或证明等式中，没有由正常核心的运行定义调用。`R7W02.fromRaw` 的 `u.toNat_lt` 是证明字段，擦除后不构成运行时 Nat 计算。[K:657–658、3349–3351、3476–3585]

这支持“源级正常核心是机器整数运算”的判断。最终 caller 是否保留辅助调用、产生装箱或重复计算仍必须由实际生成代码确认；本次没有该证据。

### 6.2 旧 DF 基线和一次 FP 参考的正确比较边界

旧 DF 正常路径的实际 runner C 成本按用户提供的冻结事实使用：2 次 UInt32→Float32 数值转换、2 次 scaleTable 读取及缩放乘法、1 次结果乘法、self-beq NaN guard、最终 toBits。本次未重新提取或执行该 runner，不能把这个前提记成新测量。

固定 Lean `object.cpp` 1987–2004 已核对：of_bits 是 bit_cast 后 NaN 规范化；to_bits 是 NaN 判断后 bit_cast。它们不是昂贵的软件浮点解码器。源码中没有分配大整数的逻辑；实际调用、寄存器、分支与 ABI 成本仍不能按零计算。[源 S6，文件 SHA256 `b53499ae7db8ed722a489ae5a79a394b93f6fda2e6663a3784d886867583985a`]

此外，旧路径的 `UInt32.toFloat32` 是数值转换，与 of_bits 的位解释不是一回事。不能用某一个 helper 的性质代替整条旧路径的成本。

一次 FP 参考 [N:`R14ExponentShift.core`] 在 `mid.toBits` 之后还要平移/相加指数并合入符号。因此，即使旧最终 return toBits 可以形成尾调用，参考中的 mid.toBits 也不能直接承担同样的尾位置。这里是调用形状差异，实际是否内联、是否尾调用以及最终机器成本仍未知。该参考没有实测收益，本次也未产生新结果。

### 6.3 重复表达式是首要生成代码核验点

候选的 `core` 没有用一个局部 let 显式共享全部 product 与 rounded。若把运行定义机械展开为不共享的表达式树：

| 路径 | productWord 表达式次数 | roundedWord 表达式次数 |
|---|---:|---:|
| exponentWord 中直接 highWord | 1 | 0 |
| exponentWord → carryWord → roundedWord | 2：直接 product，加 shift 中的 high | 1 |
| fractionWord → roundedWord | 2：同上 | 1 |
| 合计 | 5 | 2 |

**5 和 2 是源表达式树的计数，不是最终执行次数。** Lean/C 编译器可能把它们合并，也可能因未内联的调用边界未能全部共享。既不能断言“实际有 5 次乘法”，也不能断言“写了一个 productWord 定义，所以只乘一次”。本次不为处理该风险另造运行定义。

即使成功合并为一个乘积，仍有根据 h 决定的变量移位、构造 bias、提取奇偶、最终右移、carry/fraction/exponent 打包与准入判定。产品→h→t→偏置/移位→R→carry→exponent 存在连续数据依赖。消除 FP 操作数量不能直接换算时间收益，尤其还存在每次回退输入新增准入成本。

可证伪检查应针对最终 public mul 的实际 caller：检查乘积与 rounded 是否共享；变量移位和剩余 helper/call 边界；guard 的指数提取与 fallback 是否重复；正常路径是否出现 Nat/log2/Float32 helper；实际分支、返回与寄存器使用。只看一个未被实际调用的 helper 汇编不足以回答这些问题。

## 7. 少量可实现边界见证

以下不是阈值网格，也不是 Lean/正式输入验收。每对输入都取 Ex=Ey=127（S=254），直接由真实 24 位有效数构造。用整除/余数判定 RNE 与偏置公式核算结果；没有执行编译后的候选，也没有依赖主机 Float32 行为。

| 原始 u / v（十六进制） | 见证 | t | 舍入后 R | carry | 预期 raw 输出 |
|---|---|---:|---:|---:|---|
| `3f800001 / 3fc00000` | t23 正好半数，q=12582913 为奇 | 23 | 12582914 | 0 | `3fc00002` |
| `3f800003 / 3fc00000` | t23 正好半数，q=12582916 为偶 | 23 | 12582916 | 0 | `3fc00004` |
| `3fc00000 / 3faaaaae` | t24 正好半数，q=8388610 为偶 | 24 | 8388610 | 0 | `40000002` |
| `3fc00000 / 3faaaab2` | t24 正好半数，q=8388613 为奇 | 24 | 8388614 | 0 | `40000006` |
| `3f800001 / 3ffffffe` | P=2^47−2，h=0 的真实进位 | 23 | 16777216 | 1 | `40000000` |
| `3f800001 / 3fffffff` | h=1，余数=2^23−1，略低于半数 | 24 | 8388608 | 0 | `40000000` |
| `3fffffff / 3fffffff` | 真实 Pmax，q=16777214、余数=1 | 24 | 16777214 | 0 | `407ffffe` |
| `3f800000 / 3f800000` | Pmin=2^46，无舍入损失 | 23 | 8388608 | 0 | `3f800000` |

在指数端点，S=128 配 Pmin 得输出 exponent 1；S=380 配 Pmax 得 exponent 254、fraction `0x7ffffe`。guard 的外侧 127/381 以及 exponent 0/255 都按前面的机器字论证回退。以上边界说明不替代全域证明、原 gate 或冻结新输入确认。

## 8. 开发侧最小交接与未执行项

建议按证据依赖顺序继续，保持原验收协议：

1. 核对原 SHA，应用唯一证明名替换；若严格只改该处，核对 253523 B 与第 3 节的预期 SHA。
2. 在既有 Lean/FloatLib 精确版本及原官方编译 argv 下编译完整单文件；优先记录新模块的首个真实错误。本次没有实际编译证据，不能推断任何 tactic 已实际成功。
3. 沿用原 gate 的规格与传递公理检查，确认最终四公开规格及新 public mul 的实际依赖；只接受 `propext`、`Classical.choice`、`Quot.sound`。文本扫描不能代替该检查。
4. 编译通过后查看该候选的实际最终 caller C/asm，回答第 6 节的共享与调用成本问题。
5. 最后按既定完整 25 轮与冻结新输入流程确认收益；不以少量边界算术核算宣称通过，不以指令数量宣称加速。

| 验证项 | 本次状态 |
|---|---|
| 输入字节、SHA、源码长度 | 已执行，一致 |
| 新数学公式/guard/public 绑定静态审阅 | 已执行，除 F1 外未发现确定缺陷 |
| 固定版本 rounding 与 UInt 定理签名核对 | 已执行 |
| 最小补丁字节差异、预期整包哈希 | 已执行 |
| 原件或补丁精确 Lean 编译 | **NOT_RUN** |
| 内核传递公理审计与原 gate | **NOT_RUN** |
| 新 C / 最终 caller 汇编 | **NOT_RUN** |
| 完整 25 轮 / 冻结新输入确认 | **NOT_RUN** |
| 性能结论 | **未知** |

## 9. 固定主源与可追溯引用

所有外部定义只采用固定 commit 的一手源码。公开网页读取接口未返回正文；固定原始源通过只读下载或已缓存原件的哈希核对取得。没有据当前分支或其他工具链推断精确版本行为。

- **S1 — Lean UInt 定理。** [Init/Data/UInt/Lemmas.lean](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Data/UInt/Lemmas.lean)，宏生成的 `toNat_add`、`toNat_sub_of_le`、`toNat_mul` 与扩宽/截窄引理。SHA256：`197db99e55771dbf24ef299a091e9266fb23758643c24ea31a24a8908239dc5c`。
- **S2 — Nat quotient RNE。** [Numerics/Quantization/Deterministic/Quotient.lean](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Numerics/Quantization/Deterministic/Quotient.lean)，`roundQuotientEven`。SHA256：`0820d848554b3a54a216d040aa6fbb77f4909ed5af046cff55a4358e970654fb`。
- **S3 — Nat shift RNE。** [Numerics/Quantization/Deterministic/ShiftRight.lean](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Numerics/Quantization/Deterministic/ShiftRight.lean)，`roundShiftRightEven_eq_roundQuotientEven`、上下界引理。SHA256：`7727da5783057bd05d61c72d95c6c3495e05fa4faa3ff3bae4c55005bbf94b74`。
- **S4 — Word/Nat RNE 桥。** [Kernels/FixedWord/Core/Proof/Rounding.lean](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Kernels/FixedWord/Core/Proof/Rounding.lean)，`roundShiftRightEven_toNat`。SHA256：`a4228690ac703796feb6b46184523c816f7d61240510b5ab85a7b30883e02424`。其实际 [Core/Runtime.lean](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Kernels/FixedWord/Core/Runtime.lean) SHA256：`ce5135ec19019a5240a7d7e596f5ef015d8def9d63ebe74d17fba86c83d1c989`。
- **S5 — 实际 binary32 roundDyadic。** [ExecFloat/Backends/Word/Narrow/Base/Runtime.lean](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/ExecFloat/Backends/Word/Narrow/Base/Runtime.lean)，`mkBits`、`roundDyadic`、`expField`；检查 normal 分支的原 RNE、carry、normalizedExponent 和 fraction。重新取得固定 commit 原始源，与现成缓存逐字节一致；6683 B，SHA256：`1a00aeab50520759e90e3af0cbcea0e61a03ec1b2648907409f4da9d6c73ef67`。不将本次 native-reference 附件误认为此底层源。
- **S6 — Lean Float32 runtime。** [src/runtime/object.cpp](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/runtime/object.cpp#L1987-L2004)，`lean_float32_of_bits` 和 `lean_float32_to_bits`；100916 B，SHA256：`b53499ae7db8ed722a489ae5a79a394b93f6fda2e6663a3784d886867583985a`。

最终接受边界：本报告支持交开发侧验证这个**只改证明引用**的补丁；不支持把 6f8808d0 或其修复版标记为已编译、已过 gate、已完成公理审计或已获得性能收益。
