# FloatLib R2-W01c：用目标表示见证闭合 normal 转换的证明尝试

## 结论与证据等级

**本轮交付了覆盖任意 normal word 的完整 Lean 证明尝试，并写出了不带 `hNormal` 参数的组合定理；但本环境没有 Lean，不能报告 Lean 已证明通过。**

本轮最有价值的源码发现是：固定 FloatLib `0d91825727839f597fd06b22fdd038ea21480f0c` 已有完整的 `roundDyadicWithRounding_toDyadic?`。它在 `Conversion/Text/Representation.lean`，不是固定版的 `DirectedSemantics/Exact.lean`。较新版本只是把相关七个定理移入 Exact：两处证明块逐字相同，6,615 bytes，SHA256 为 `a1534622adfdb290ef9af0a3985dbf98a4279444f626aa40d703c73cd2780dac`。**不需要为此升级依赖，也不需要局部移植新库。** [固定表示文件][F-REP] [新版 Exact][N-EXACT] [新版表示文件][N-REP]

最终选用的证明表示，比显式处理乘积舍入更短：**把目标 raw word 本身作为精确可表示性的见证。** 三个精确 dyadic 解码式给出输入和目标有限、精确乘积等于目标值；目标的有限幅值界排除乘法溢出；固定 `roundAt_toReal_eq` 和非零表示唯一性恢复完整 Model 字；最后使用给定公开父源的有限原生乘法桥及 codec 单射，关闭 native 值和最终 32 位关系。[固定舍入恒等式][F-ROUND] [固定乘法语义][F-MUL] [固定表示唯一性][F-REP] [公开父源][PARENT]

| 交付物 / 检查 | 本轮结果 | 能证明什么 |
|---|---|---|
| 纸面任意字推导 | 已完成 | 在给定 binary32 语义下推出 normal 等式，包含两种符号、任意 fraction、有限性、非零及完整表示恢复 |
| `lean/NormalEqAttempt.lean` | 44,176 bytes；完整脚本尝试 | 写出全量量词证明，无显式占位，没有把 normal 输出等式重新作为前提 |
| `R2W01c.convert_eq` | 声明没有 `hNormal` 参数 | 文本上的无条件组合证明；**并非编译通过的声明** |
| `lean/ReusableModel.lean` | 6,266 bytes | 可先独立验证的整数 dyadic 桥及 Model 精确乘法核心 |
| 固定 policy 文本扫描 | `TEXT_PASS_ONLY` | 唯一导入 `ContractTensor`、大小合格、禁止词零匹配、无选项修改、属性合规 |
| 公开原件身份检查 | 59 文件，955,551 bytes | SHA256 / Git blob 校验；其中适用的固定文件还与本会话已有固定 tree 核对 |
| Lean elaboration / 内核检查 | **NOT_RUN** | 没有可报告的编译成功或失败目标 |
| 允许公理集合审计 | **NOT_RUN** | 已提供独立审计命令，尚未得到真实输出 |
| 官方 gate / 性能 | **NOT_RUN** | 本轮不作任何新的性能结论 |
| 新 C 实验 | **未执行，遵照本轮范围** | 没有增加零合并或 bmm 变体 |

主要单文件 SHA256：`03292da65862a1dbf8a4b913d0cef3e25dadaa4ee2f70d04316eaf8bdf3d8db1`。小核心 SHA256：`9942856bfdac7b5cdd8126675e920a87f054a95a0a3b93e72dc59f192b3a46c3`。这些是交付文本的身份标识，不是形式化证明证书。

## 1. 范围、起点与名称约定

目标沿用 W01b 的完整定义：

```lean
theorem normal_eq (u : UInt32) (hn : NormalBand u) :
  tableProduct u = Float32.ofBits u
```

其中 `NormalBand u` 为 `0x0c000000 ≤ (u &&& 0x7fffffff) ∧ (u &&& 0x7fffffff) < 0x7f800000`；`mantissa u = (u &&& 0x7fffff) ||| 0x800000`；`tableProduct u = (mantissa u).toFloat32 * scaleAt u`。512 项表的定义、`u >>> 23` 索引以及 W01b 的准入和零证明均保留。基线文件按字节复制到本包，SHA256 仍为 `dddb4cd8dd2d3ba987fec1bcd7235e4875548e00b8bbb533431977966dfdfa0d`。

本轮新证明放在 `R2W01c` 与 `R2W01cModel` 命名空间。旧的 `R2W01b.convert_eq` 仍是带 normal 假设的组合引理；**新 `R2W01c.convert_eq` 的实参是本轮尝试证明的 `R2W01c.normal_eq`，其公开签名没有 normal 结果假设。** 两个同名定理的命名空间必须区分。

环境固定为 Lean 4.34.0、FloatLib 固定 pin、官方 `978cc5b445edb9943fd9953b0a9037d97a9f33a8`。候选唯一导入为 `ContractTensor`。没有改官方配置、依赖、bench、gate，没有正式提交，也没有访问 CI、其他会话或旧私有附件。[官方合同][CONTRACT] [官方配置][LAKE]

公开父源 `f01-d2-final-finite/Kernel.lean` 已下载并核对为 58,079 bytes，SHA256 与给定的 `86312a3759286cb207f946af9db95546777fdb16f1bd147f7892c0f9e1d79217` 完全一致。其两次 gate 通过是**用户给定反馈**；本轮没有验证该反馈，更没有将它转移成新证明文件的 gate 结果。[公开父源][PARENT]

## 2. 先反驳容易误用的证明步骤

### 2.1 数值相等本身不恢复位

`+0` 与 `-0` 都是 finite，实数语义相同，原字分别为 `0x00000000` 和 `0x80000000`。因此“finite + `toReal` 相等”仍不足以推出完整字相等。固定表示唯一性定理要求非零；本题用 `M ≥ 2^23 > 0` 和二的整数次幂非零满足它。[固定表示唯一性][F-REP]

另外，Model 的总 `toReal` 将 NaN 和 Inf 映为零。只有一个裸数值等式也不能区分异常字。这里不声称 finite 与 nonzero 前提逻辑独立：保留合适的非零数值等式时，某些 finite 前提可以从定义推出；本证明显式提供库接口要求的 finite 证据。[Model 实数语义][F-REAL]

### 2.2 raw roundtrip 不能直接用于未规范化乘积 dyadic

取 `u = 0x3f800001`。有 `E = 127`、`M = 8,388,609`，目标解码为

\[
(false,\ 8\,388\,609,\ -23).
\]

表项数值是 `2^-23`，但**表项的规范解码**是

\[
(false,\ 2^{23},\ -46).
\]

因此乘法规格的未舍入 dyadic 是

\[
(false,\ 8\,388\,609\cdot2^{23},\ -46),
\]

它和目标 dyadic 数值相同，结构不同。`roundDyadicWithRounding_toDyadic?` 的前提是精确的 `toDyadic? x = some d`，不能把这两个 d 直接替换。所选 Model 路线明确经过数值恒等式、有限舍入语义和非零表示唯一性；不会把 raw roundtrip 当作任意 dyadic 数值等价定理。[乘法规格][F-SPEC] [raw roundtrip][F-REP]

### 2.3 表项指数写错 23 位，会得到错误数值

同一例子若把表项错误解码为 `⟨false, 2^23, E-150⟩`，就把应为 `2^-23` 的 scale 写成 `1`；乘积成为 `8,388,609`，不再是原值。正确的三个指数分别是：整数 `0`、scale `E-173`、目标 `E-150`。

### 2.4 E=23 的相邻反例说明当前表域不能扩大

取 `u = 0x0b800000`，它是 E=23 的非零 normal word。当前表在该指数返回带符号零，因此 `tableProduct` 为零，不能重构输入。这不是本轮准入值；旧 `ofBits` 回退必须保留。E=24 时表项指数域恰为 1，成为最小正/负 normal scale，证明没有越过这个下界。

### 2.5 最大有限值必须允许等号

取 `u = 0x7f7fffff` 或 `0xff7fffff`：E=254、M=`2^24-1`，精确乘积幅值正好等于最大有限值。用严格 `< maxFinite` 作为必要条件会漏掉合同要求的边界；本证明调用的是 `≤` 幅值界，包含这两个字。[固定乘法有限性][F-MUL]

### 2.6 全域原始字 roundtrip 是错误的更强目标

本轮没有证明 `∀u, (convert u).toBits = u`。原 `Float32.ofBits` 对 NaN 会规范化；例如公开源码明确说明 `0x7f800001` 经原生转换再取 bits 得到 `0x7fc00000`。本轮全域结论是 `convert u = Float32.ofBits u`，严格 normal 域内才另有 `(tableProduct u).toBits = u`。完整算法对 raw FloatLib payload 的原有回退是另一层机制，继续保留。[固定 native 转换说明][F-NATIVE]

## 3. 选择哪一种数学表示

| 路线 | 本轮评价 | 决定 |
|---|---|---|
| 新版 raw roundtrip 的局部移植 | 固定 pin 已有相同七个证明，且通过唯一入口可见 | 停止移植；直接调用固定定理 |
| `roundDyadic_of_representable`，给乘积系数分解 `M·2^23` | 数学可行：取 `m=M,k=23`；但仍要整理 scale 指数、数值等式、幅值与最终表示 | 保留解释，不作为最终主证明 |
| 目标字提供可表示性，`roundAt_toReal_eq` 加 finite/nonzero uniqueness | 不必重证乘积的归一化、舍入位、targetExponent 或最终 pack；目标字自身提供幅值界 | **采用** |
| 为 normal 再展开 unpacked round/targetExponent/pack | 与另一路研究重叠，且固定库已经给出所需 Model 事实 | 本轮不重新发展；仅原样复用已给有限乘法桥的已有依赖 |

固定 `roundDyadic_of_representable` 的系数条件是 `d.significand = m * 2^k` 且 `m < 2^(fracWidth+1)`，并不要求整个未规范化 `d.significand` 已经只有24位。若走这条路线，乘积 `d = (s,M·2^23,E-173)` 可用 `m=M,k=23`；E≥24 给 `E-173≥-149`。不过最终采用目标见证后，不再需要在新证明里重走这些 roundDyadic 条件。[固定 Exact][F-EXACT]

## 4. 任意 UInt32 的字段证明

令 `w = u.toNat`，则 `0 ≤ w < 2^32`。定义

\[
q=\lfloor w/2^{31}\rfloor\in\{0,1\},\quad
E=\lfloor w/2^{23}\rfloor\bmod256,\quad
F=w\bmod2^{23},\quad s=(2^{31}\le w).
\]

W01b 已有 `magnitude_toNat`：`(u &&& 0x7fffffff).toNat = w mod 2^31`。因此 `NormalBand u` 推出

\[
24\le E<255,\qquad 0\le F<2^{23}.
\]

`mantissa_toNat` 用低23位掩码和低位与隐含位不重叠的 OR 定理证明

\[
M=(\operatorname{mantissa}u).toNat=2^{23}+F,
\quad2^{23}\le M<2^{24}.
\]

这是对任意输入字的符号化推导，既不枚举 fraction，也不使用某组性能数据。

### 4.1 表项完整 word 的自然数公式

`j = u >>> 23` 满足 `j.toNat < 512`，其低8位等于 E，第8位等于 q。normal 前提使表分支 `24≤e≤254` 为真，也使 UInt32 的 `e-23` 不发生回卷。新引理证明

\[
(\operatorname{scaleBits}(j)).toNat
=q\,2^{31}+(E-23)\,2^{23}.
\]

右侧低部分小于 `2^31`，所以原始按位 OR 等于这里的加法；全字小于 `2^32`。由这个公式恢复：

- 符号不变：`wordSign(scaleBits j) = wordSign u`；
- 指数字段是 `E-23`，范围 `1..231`；
- fraction 为0。

`WordFields.fragment.lean` 中，UInt32 掩码、移位和减法分别经固定 `toNat` 引理转成常数除余与自然数减法，之后用 `omega` 处理线性整数关系。静态复核发现并修正了一处真实接口形状错误：固定 Mathlib `Nat.and_two_pow` 返回 `(n.testBit i).toNat * 2^i`，不是 if 形式。最终稿使用准确的 Bool.toNat 形式。**这项修正经过源码核对，尚未实际执行 Lean。** [固定 Mathlib 位定理][M-BITS]

### 4.2 raw Model 与字段构造相等

新代码定义 `raw32 u := Model.ofUInt32 u`，先用 `BitVec.ofNat_uInt32ToNat` 证明其 bits 就是 `u.toBitVec`，再证明 sign、expField、fracField 分别是 s、E、F。固定

```lean
Model.ofFields_signBit_expField_fracField
```

由此给出完整表示等式，而非仅仅值等式：

```lean
raw32 u = Model.ofFields FloatFormat.binary32 (wordSign u) (wordExp u) (wordFrac u)
```

这里已经恢复原始 word 的全部字段，包括符号。[固定 Model 字段定理][F-MLEAN]

## 5. 三个精确 dyadic 解码式

以 `x` 表示原生整数转换后的 Model，以 `y` 表示原生表项的 Model，以 `z` 表示输入的 raw Model：

| Model | 精确 decode | 来源 |
|---|---|---|
| `x = nativeModel ((mantissa u).toFloat32)` | `some ⟨false,M,0⟩` | 原生 UInt32 构造桥加整数表示见证 |
| `y = nativeModel (scaleAt u)` | `some ⟨s,2^23,E-173⟩` | 表项完整字段证明；有限字的 native canonicalization 恒等 |
| `z = rawModel u` | `some ⟨s,M,E-150⟩` | 输入 normal 字段构造与固定 normal decode |

三项都由 `NormalBand u` 和本地全量字段定理给出；最终 `normal_eq` 不接收这些等式作为外部未证假设。

### 5.1 原生 UInt32 精确整数转换：不用重证 round

固定 Lean 定义将 `n.toFloat32` 表示为 `Float32.ofModel (Float32.Model.ofUInt32 n)`，后者经过 `pack (UnpackedFloat.ofUInt32 ...)`；`ofUInt32 → ofNat → ofInt` 的定义链已经公开。[Lean Float32][L-FLOAT] [Lean packed model][L-MODEL] [Lean 整数构造][L-OFNAT]

固定 FloatLib 的 `Model.ofFloat32Model_pack` 和

```lean
Model.ofModel_ofInt_eq_roundDyadic
  (fmt : FloatFormat) (hfmt : fmt.isIEEE = true) (n : Int)
```

直接给出任意 UInt32 的完整 Model 等式：

```lean
Model.ofFloat32Model n.toFloat32.toModel =
  Model.roundDyadic FloatFormat.binary32 ⟨false, n.toNat, 0⟩
```

这个等式还没有声称任意 UInt32 都能精确表示。精确性来自下一项表示见证。[固定整数舍入桥][F-INT] [固定 native Model 桥][F-NMODEL]

对 `2^23 ≤ n.toNat < 2^24`，取

```lean
z = Model.ofFields FloatFormat.binary32 false 150 (n.toNat - 8388608)
```

fraction 落在 `[0,2^23)`，指数150合法；固定 normal decode 给出 `toDyadic? z = some ⟨false,n.toNat,0⟩`。此时完整 `roundDyadicWithRounding_toDyadic?` 正好可用，因为其 d 就是 z 的**规范解码**。于是恢复整个 z 字，并得到所需 x 的解码。这里没有把一个 `toReal` 结论偷换成位相等，也没有证明数十亿个闭合样例。[字段 decode][F-FIELDS] [固定 raw roundtrip][F-REP]

### 5.2 表项进入 native Model 的 canonicalization

表项是 `Float32.ofBits scaleWord`，不能无条件声称其 Model 等于任意 raw Model。本轮先由 E−23∈`1..231` 证明 raw scale 解码成功，从而有限；复用父源的 `modelCanonicalOfFinite` 思路，排除 NaN 的非规范表示；再用固定 `ofFloat32Model_toFloat32Model` 和 `canonicalizeModel_eq_self`，恢复完整 raw scale Model。[父源有限回环][PARENT] [固定 native Model 桥][F-NMODEL]

这条桥写成 `nativeModel_ofBits_of_decode`，输入前提是成功的精确 dyadic decode。它没有错误地扩大成包含 NaN payload 的全域 raw 回环。

## 6. 核心命题：目标字作为可表示性见证

下面是本轮最值得独立复用的 Model 引理。所有 x、y、z 都在同一 IEEE 格式中：

```lean
theorem mul_eq_of_finite_value
    {fmt : FloatFormat} (x y z : Model fmt)
    (hfmt : fmt.isIEEE = true)
    (hx : isFinite x = true) (hy : isFinite y = true)
    (hz : isFinite z = true) (hz0 : toReal z ≠ 0)
    (hvalue : toReal x * toReal y = toReal z) :
    mul x y = z := by
  have hbound : |toReal x| * |toReal y| ≤ toReal (posMaxFinite fmt) := by
    rw [← abs_mul, hvalue]
    exact abs_toReal_le_posMaxFinite_of_isIEEE_of_isFinite z hfmt hz
  have hmulfinite : isFinite (mul x y) = true :=
    isFinite_mul_of_abs_mul_le_posMaxFinite x y hfmt hx hy hbound
  have hmulvalue : toReal (mul x y) = toReal z := by
    rw [toReal_mul_eq_roundAt x y hfmt hx hy hmulfinite,
      hvalue, roundAt_toReal_eq z hz]
  exact eq_of_toReal_eq_of_nonzero hmulfinite hz hmulvalue
    (by rw [hmulvalue]; exact hz0)
```

**状态：这是一段完整、无显式占位的证明脚本，Lean NOT_RUN。** 它调用的固定定理及前提已逐一从公开原件核对；不能因此把新脚本称为已通过内核。[有限值幅值界][F-BOUND] [乘法语义][F-MUL] [舍入恒等式][F-ROUND] [表示唯一性][F-REP]

推导依次是：

1. z 已经是有限存储字，故 `|toReal z| ≤ maxFinite`。
2. 精确乘积值等于 z 的值，因此这个界也是精确乘积的界。
3. 固定乘法有限性定理推出 `mul x y` finite。这里没有假设待证乘积 finite，因而没有循环。
4. finite 乘法的数值等于 `roundAt fmt (toReal x * toReal y)`。
5. 替换成 z 的值；固定 `roundAt_toReal_eq z hz` 表明有限已存值再次舍入不变。
6. 乘积与 z 都 finite、同值且非零。固定表示唯一性给完整 `Model` 等式。

本题中的数值恒等式仅是精确 dyadic 语义中的代数：

\[
M\cdot\left((-1)^s2^{23}2^{E-173}\right)
=(-1)^sM2^{E-150}.
\]

`dyadic_scale_value` 对 s 分两支，再用二的整数次幂加法律与环等式完成它。此处的实数乘法结合律只用于规格语义的证明；没有改变程序中的任何浮点加法或乘法序列。

`binary32_mantissa_scale_mul` 最终只要求三个精确解码及 `M≠0`。E 的上界和 M 的精度界不是被遗忘，而是已经用于构造那三个合法 raw/native 解码；在这个通用引理中无需重复列出。

### 6.1 表示唯一性真正关闭了什么

固定 `eq_of_toReal_eq_of_nonzero` 不是一个浮点等式公理。它先从两个 finite 字得到 decoded dyadic；借规范指数 `cexp` 证明指数相等；消去非零的 `2^e` 得到 signed significand 相等；再恢复符号与自然数系数，最后调用 decoded 表示单射恢复整个 Model word。该证明在固定源码中已有，候选只调用它。[完整表示唯一性证明][F-REP]

因此最终结论包括负号和 fraction 的每一位，也没有“精确总和”或“更准确结果”替代 ordered 输出的问题。

## 7. 从 Model 等式到原生值与最终 packed 字

记 `B = FloatLib.Floats.ExecFloat.Binary`。定义

```lean
nativeModel x = B.toModel (B.ofFloat32 x)
rawModel u    = B.toModel (B.ofBits32 u)
```

`rawModel u` 与泛型 `Model.ofUInt32 u` 的小表示差异用 `BitVec.ofNat_toNat` 关闭。父源的 `NativeBridge.toModelNativeMul` 对 finite 原生 x、y 给出

```lean
nativeModel (x * y) = Model.mul (nativeModel x) (nativeModel y)
```

它是父源 `ofFloat32Mul` 的 Model 层前置事实。本轮复用了它及所需依赖，没有重新发展有限原生乘法。父源中已有的三个 targetExponent 引理随该桥原样保留，来源和 MIT notice 也保留；这不属于本轮为 normal 新增的 unpacked 证明路线。[公开父源][PARENT]

三 decode 分别推出原生 x、y finite。上节给出的完整 raw Model 等式随后推出

```lean
B.ofFloat32 (x * y) = B.ofBits32 u
```

所用的是 `B.toModel` 的注入性。[固定 codec 注入性][F-CINST] 之后有两个严格的终点：

- 对等式应用 `B.toFloat32`，使用 native roundtrip 和原始 codec，得到 `x*y = Float32.ofBits u`；
- 对等式应用 `B.toBits32`，得到 `(x*y).toBits = u`。

这就是最终 packed 字节关系，不再留下“只有实数相等”的接口。乘积终点不需要额外调用 `GuardBridge.finiteRoundtrip`：完整 raw Model 等式已经更直接地锁定了目标字。该父源定理仍已审计；表项的 native/raw 连接则明确处理了 canonicalization。[固定 native 表示桥][F-NREP] [固定 native 原始 codec][F-NATIVE]

## 8. 已组装的 normal 与无条件转换接口

完整单文件的最终部分包含：

```lean
theorem normal_eq (u : UInt32) (hn : NormalBand u) :
    tableProduct u = Float32.ofBits u := by
  exact native_mul_eq_of_decoded_raw_model_mul_eq
    (mantissa u).toFloat32 (scaleAt u) u
    (mantissa_native_decode u) (scale_native_decode u hn) (normal_model_mul u hn)

theorem normal_bits (u : UInt32) (hn : NormalBand u) :
    (tableProduct u).toBits = u := by
  exact native_mul_bits_eq_of_raw_model_mul_eq
    (mantissa u).toFloat32 (scaleAt u) u
    (nativeFinite_of_decode _ (mantissa_native_decode u))
    (nativeFinite_of_decode _ (scale_native_decode u hn)) (normal_model_mul u hn)

theorem convert_eq (u : UInt32) : convert u = Float32.ofBits u := by
  exact R2W01b.convert_eq normal_eq u
```

这里 `normal_model_mul` 的三 decode 前提均由本文件的全量字段与整数定理提供，不是外置 `hNormal` 的改名。`NormalBand` 本身是准入域条件，仍应保留在 normal 专用命题中。**`convert_eq` 的签名已经无条件，但其有效性仍等待整个文件实际编译。**

全域组合分三种输入：

1. magnitude 为零：使用 W01b 已有两种 signed zero 的证明文本。
2. `NormalBand`：使用本轮 `normal_eq`。
3. 非准入：定义上就是旧 `Float32.ofBits`。

本包还给出 `normal_finite`、全域 `convert_bits_eq`、函数替换 `replace_decoder` 和 `foldl_convert_eq`。fold 引理是对原 step、原初始 accumulator、原输入列表逐项替换转换函数；任何前缀的转换值都相同，后续消去、溢出、次正规结果和 signed zero 的行为也随同保留。这里没有跳零，没有重排，没有融合乘加。

这是一组转换定理，**不是完整参赛 Kernel 的 `SumObligation` 提交**。现成整包末尾 finite 守卫和 raw payload 回退属于给定基线，本轮没有重新声称其 gate 或性能结果。

## 9. 使用的固定定理与全部关键前提

下表省略 namespace 前缀 `FloatLib.Floats.Formats.BinaryInterchange.Model`；各源码原件与 SHA256 在 `public_sources/source_manifest.json` 中。

| 定理 / 定义 | 必须满足的前提 | 本轮如何满足 |
|---|---|---|
| `toDyadic?_ofFields_normal` | exponent 非零；exponent `< expAllOnesNat`；fraction `< 2^fracWidth` | 目标 E24..254；scale E−23∈1..231；整数见证指数150；F 与 M−2^23 的范围 |
| `ofModel_ofInt_eq_roundDyadic` | IEEE descriptor；任意 Int | binary32 固定描述符，`n = (M : Int)` |
| `roundDyadicWithRounding_toDyadic?` | IEEE descriptor；给定 rounding mode；精确成功解码 `toDyadic? z = some d` | `.nearestEven`；整数见证的规范 d=`⟨false,M,0⟩` |
| `isFinite_eq_true_of_toDyadic?_some` | 某个 d 的成功 decode | 三 decode 各自提供 |
| `Dyadic.toReal_eq_zero_iff` | 任意 dyadic | M≥2^23 排除 coefficient 为0 |
| `abs_toReal_le_posMaxFinite_of_isIEEE_of_isFinite` | IEEE descriptor；目标 z finite | z 是合法 normal 输入 raw word |
| `isFinite_mul_of_abs_mul_le_posMaxFinite` | IEEE descriptor；x/y finite；`|x|·|y|≤maxFinite` | 三 decode 与目标值见证推导；包括等于最大有限值 |
| `toReal_mul_eq_roundAt` | IEEE descriptor；x/y finite；运算结果 finite | 前项已经推出结果 finite |
| `roundAt_toReal_eq` | z finite | 目标字精确可表示；不额外假设具体 round 输出 |
| `eq_of_toReal_eq_of_nonzero` | 两字 finite；数值相等；左值非零 | 结果 finite、z finite、舍入恒等式、M≠0 |
| 父源 `modelMulFinite` | IEEE descriptor；两个 `toModel` unpacked 值 finite | 复用父源 native multiplication 连接，不重证该规格 |
| 父源 `toModelNativeMul` | 原生 x/y 的 `isFinite = true` | 从 native Model 的成功 decode 推导 |
| `ofFloat32Model_toFloat32Model` + `canonicalizeModel_eq_self` | 后者要求 canonical Model | 表项先成功 decode→finite→canonical |
| `B.toModel_inj` | 相同 configured 格式的完整 Model 等式 | 上述 Model product 等式 |
| `B.toFloat32_ofFloat32` | 任意 native Float32 | 仅在原生返回原生的方向使用，无 raw NaN payload 假设 |
| `B.toBits32_ofFloat32` / `B.toBits32_ofBits32` | 对应构造子 | 将完整 ExecFloat 字等式投影到 UInt32 |

原生 finite、Model finite、unpacked finite 是三个不同谓词。代码没有靠名字相似互换它们；使用固定 `toDyadic?_ieee_eq_model` 和 unpacked 构造子分析建立所需连接。该定理的准确源位置是 `Dyadic/Classification.lean`。[固定 dyadic 分类][F-CLASS]

### 9.1 为什么唯一 `import ContractTensor` 足够

表示唯一性与 raw roundtrip 的公开链是：

`ContractTensor → Contract → FloatLib → Floats → Formats → BinaryInterchange → Configured → Conversion.Text.Roundtrip → Conversion.Text.Representation`。

整数桥经 `Formats.IEEE754 → Native.Integer → Integer.Constructors / FromInt → Integer.Rounding` 可见。相关声明在固定模块的公开 section 内。本轮已做源码级导入链核对；仍不把它描述成实际 elaboration 成功。[固定配置模块][F-CONFIG] [固定 Text Roundtrip][F-TEXT] [固定 IEEE 入口][F-IEEE] [固定整数入口][F-INTEGER]

## 10. 文件、诊断和首次真实编译顺序

### 10.1 包内入口

- `lean/NormalEqAttempt.lean`：完整单文件转换证明尝试，唯一导入、含父源所需许可。
- `lean/ReusableModel.lean`：可独立编译的较小全量词核心；不依赖本轮 UInt32 表项字段证明。
- `lean/components/`：W01b 基线、父源桥、整数核心、Model 乘法核心、字段和组合片段。带 `.fragment.lean` 的文件供拼接，不作为独立 module 使用。
- `diagnostics/rebuild.py`：从包内组件重建两份单文件；不调用 Lean。
- `diagnostics/verify_static.py`：校验源文件哈希、两版证明块相同、官方 policy 文本规则、基线字节不变。
- `diagnostics/run_lean.py`：只使用已有工具链和已有固定官方目录；没有下载或安装步骤；拒绝已识别的 elan launcher shim。
- `diagnostics/AuditCommands.lean`：审计命令单独保存，未放入候选或候选注释。
- `results/`：本轮实际静态检查与 **NOT_RUN** 记录。
- `public_sources/`：公开原件、固定/较新版本清楚分目录、来源和许可。
- `appendices/`：整数桥、表示桥、父源桥和字段的独立静态审查记录。

### 10.2 本轮已运行的诊断

在包根目录下：

```sh
python3 diagnostics/rebuild.py
python3 diagnostics/verify_static.py
python3 diagnostics/run_lean.py
```

前两项完成；第三项真实输出 `lean_executable = null`、`lake_executable = null`、`status = NOT_RUN`，原因是 PATH 中没有 Lean/lake。没有伪造编译日志或 Lean goal。

`verify_static.py` 使用固定 gate 中提取的同一禁止词正则、允许属性集合、大小限制和 import 规则。它刻意不运行官方 gate，也没有执行 gate 的提交或构建流程。[固定 gate][GATE]

### 10.3 在已经存在的固定环境中的下一步

将现有 Lean4.34.0 工具链的真实二进制目录放在 PATH，传入**现有**官方 `lean` 目录，例如：

```sh
python3 diagnostics/run_lean.py --official-lean /absolute/path/to/existing/official/lean
```

脚本先核对固定版本和 `lakefile.lean` / `lean-toolchain` 原件，再依次运行小核心、完整文件；成功后才把审计命令临时追加到独立副本，输出实际公理集合供复核。调用中沿用固定 lakefile 的 `autoImplicit=false` 与 `relaxedAutoImplicit=false`，没有改变这些取值或提高证明资源选项。它不执行 package update，不构建 benchmark，不写入官方候选文件；独立文件检查仍不能替代官方 gate。

**应优先得到的证据是小核心的真实 Lean 输出，然后才是完整文件。** 若小核心不能通过，精确失败点已被压缩到整数构造定义归约、固定 raw roundtrip 调用或 Model 同值乘法引理。若小核心通过而完整文件失败，再处理 UInt32 位域和 native/raw 接口，不必重新展开全部乘法舍入。

## 11. 当前未验证事项与明确停止条件

### 11.1 未验证事项不能包装成已闭合 Lean 目标

没有 Lean 环境，所以本轮**不存在编译器报告的未解 goal**。以下只是首次编译时已隔离的检查位置，不是伪造的错误日志：

| 检查位置 | 需要 Lean 实际接受的目标 |
|---|---|
| `uint32_model_eq_roundDyadic` | native 整数构造定义与固定 `ofModel_ofInt_eq_roundDyadic` 的 definitional equality / rewrite |
| `fields32_toDyadic` | binary32 固定常数归约及 `(E:Int)-127-23 = E-150` |
| `tableSign_nat`、`scaleBits_nat` | UInt32 移位、掩码、减法的 `toNat` 形状；常数除余与 OR 分离 |
| `scale_wordExp`、`normal_wordExp_bounds` | `omega` 对嵌套常数除余关系的实际证明资源需求 |
| `nativeModel_ofBits_of_decode` | finite→canonical 与 native pack/unpack 连接 |
| `normal_eq`、`normal_bits` | 三 decode、Model 完整等式、native codec 的最终接合 |
| 公理审计 | 所有新结果的实际依赖是否只落在允许集合 |

源码静态审查没有发现新的数学缺口，但没有执行的 elaboration、内核检查和资源消耗依然是实质风险。不能因为多个独立审查者没有发现问题，就称其为形式化证明。

### 11.2 停止条件

1. **停止新版 raw roundtrip 移植。** 已确认固定 pin 有逐字相同的公开证明，再移植只增加维护和归属负担。
2. **不再增加本轮 C、零分布或 bmm 实验。** 当前任务价值在缩短 normal 的证明路径，既有性能判断保持为给定背景。
3. **实际编译失败时，保留精确 goal 和最大已接受前缀。** 不把失败替换成新的 `hNormal`、目标位等式假设或有限样例，不扩成未经验证的“大库搬运”。
4. **若只剩字段归约或常数除余失败，局部修正该引理。** 不为它改固定配置、提高被禁止的选项、升级依赖或安装大工具链。
5. **若真实公理集合越界，或必要名字未在固定入口可见，不能称无条件转换已证明。** 应回到包内更小核心，记录具体依赖和失败；不要根据本报告的静态可见性审计越过验证。
6. **完整 Lean 成功、公理审计成功后，才把这份源码提升为已闭合的转换定理。** 官方整包 gate 仍是另一个整合步骤，本轮没有执行它。

## 12. 来源版本与许可

所有研究输入限于本轮消息、当前会话已有的公开研究材料及新读取的公开源码。

| 来源 | 版本身份 | 许可 / 用途 |
|---|---|---|
| FloatLib 固定库 | `0d91825727839f597fd06b22fdd038ea21480f0c` | MIT，Copyright 2026 FloatLib；主要 Model、dyadic、native 接口 |
| FloatLib 对比库 | `1f5771b3e36a98f17fcac2c6d76aaa024b36aa37` | 同一 MIT LICENSE；仅用于确认定理搬移，未作为依赖 |
| Lean | tag `v4.34.0`，对应 commit `293d5d0c0c3f3dded4688b3ccd6a33939ac5102b` | Apache 2.0；逻辑定义和 UInt/BitVec 公开事实 |
| Mathlib | 固定 FloatLib manifest 中的 `5ed2965256430c3649e86755f9576b54eca72435` | Apache 2.0；核对 `Nat.and_two_pow` 等固定依赖事实 |
| 公开父源 Kernel | `46a9f085db7634a22324d25623f715829f7074f9` | 源文件嵌入完整 Conjectures.io / FloatLib / TorchLean MIT notices；复用部分保留这些 notices |
| 官方合同与 policy | `978cc5b445edb9943fd9953b0a9037d97a9f33a8` | 固定规则原件；父源同时携带相关来源许可通知；未修改或执行提交流程 |

没有把新版本七定理复制进候选，因此这项调查的**新增库证明代码为零**。父源已有有限乘法桥的复制是显式、带来源和许可的复用。其内部已有的较新来源三个 targetExponent 引理仍保留原来的归属说明；它们不是本轮发现，也不是一次依赖升级。

完整 URL、Git blob、SHA256、字节数在 `public_sources/SOURCE_LIST.md` 与 JSON manifest。源原件和候选分目录保存，源文件可能包含官方不允许候选新增的定义或工具命令；**不要把整个源码资料目录拼入候选。** 候选扫描只针对两份清楚标识的单文件。

## 13. 关键来源链接

1. [固定 raw roundtrip 与非零表示唯一性][F-REP]
2. [较新 Exact 中的同一证明块][N-EXACT]；[较新 Text 薄转导入文件][N-REP]
3. [固定有限值舍入恒等式][F-ROUND]
4. [固定乘法有限性与数值语义][F-MUL]
5. [固定目标有限幅值界][F-BOUND]
6. [固定 `ofModel_ofInt_eq_roundDyadic`][F-INT]
7. [固定 fields decode][F-FIELDS]
8. [固定 native Model / canonicalization][F-NMODEL]；[native 表示桥][F-NREP]
9. [给定公开父源，原件哈希已核对][PARENT]
10. [Lean4.34 Float32 定义][L-FLOAT]；[整数构造定义][L-OFNAT]
11. [固定 Mathlib 位运算定理][M-BITS]
12. [官方 ContractTensor][CONTRACT]；[官方 gate][GATE]

[F-REP]: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Conversion/Text/Representation.lean
[N-EXACT]: https://github.com/lean-dojo/FloatLib/blob/1f5771b3e36a98f17fcac2c6d76aaa024b36aa37/FloatLib/Floats/Formats/BinaryInterchange/DirectedSemantics/Exact.lean
[N-REP]: https://github.com/lean-dojo/FloatLib/blob/1f5771b3e36a98f17fcac2c6d76aaa024b36aa37/FloatLib/Floats/Formats/BinaryInterchange/Conversion/Text/Representation.lean
[F-EXACT]: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/DirectedSemantics/Exact.lean
[F-ROUND]: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Rounding/Proof.lean
[F-MUL]: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Arithmetic/Semantics.lean
[F-BOUND]: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/DirectedSemantics/Basic.lean
[F-REAL]: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Model/RealSemantics.lean
[F-SPEC]: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Spec/Dyadic.lean
[F-INT]: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/IEEE754/Native/Integer/Rounding.lean
[F-FIELDS]: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Model/Fields/Proof.lean
[F-MLEAN]: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Model/Lean.lean
[F-CINST]: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Configured/Instances.lean
[F-NMODEL]: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/IEEE754/Native/Model.lean
[F-NREP]: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/IEEE754/Native/Representation.lean
[F-NATIVE]: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/IEEE754/Native.lean
[F-CLASS]: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Dyadic/Classification.lean
[F-CONFIG]: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Configured.lean
[F-TEXT]: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Conversion/Text/Roundtrip.lean
[F-IEEE]: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/IEEE754.lean
[F-INTEGER]: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/IEEE754/Native/Integer.lean
[PARENT]: https://github.com/HuanHuanHuanFFF/Miner/blob/46a9f085db7634a22324d25623f715829f7074f9/competitions/floatlib/candidates/f01-d2-final-finite/Kernel.lean
[L-FLOAT]: https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Float/Float32.lean
[L-MODEL]: https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Float/Model/Float32.lean
[L-OFNAT]: https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Float/Model/Unpacked/Operations/OfNat.lean
[M-BITS]: https://github.com/leanprover-community/mathlib4/blob/5ed2965256430c3649e86755f9576b54eca72435/Mathlib/Data/Nat/Bitwise.lean
[CONTRACT]: https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/contract/ContractTensor.lean
[LAKE]: https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/lakefile.lean
[GATE]: https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/gate.py
