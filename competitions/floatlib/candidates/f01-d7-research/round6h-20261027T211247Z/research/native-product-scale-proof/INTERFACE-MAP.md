# Native product + combined scale：两条最小桥

阶段 **2026-10-27 23:52:12—2026-10-28 00:07:12 UTC**，共同截止03:12:47不变。只写本目录，不改B的e51a/92ff，不组public候选/CI。Broad-word三个小舍入根已停放为NOT_RUN储备，不继续其大证明。

`NativeScaleBridges.lean.inc`只有两根，均 **NOT_RUN**：

1. `synthetic_scale_decode s sign hs174 hs380` 直接针对源码形状 `((s-150)<<23) | signBit`。在证明体内闭UInt32减法/移位无wrap、magnitude NormalBand、wordExp=s−150及wordSign；再复用现成`R2W01c.scale_native_decode`，得到精确dyadic `⟨sign,2^23,S−323⟩`。不是假设一个未证NormalBand。
2. `native_product_scale_eq_target`：若actual first cast的decode为`⟨false,m,e⟩`，2^23≤m<2^24、e=23或24，则实际native乘scale等于`Float32.ofBits(mkBits sign (e+S−150) (m−2^23))`。目标E47..254正常有限非零；用现成`R2W01cModel.mul_eq_of_finite_value`和native decoded multiplication桥关闭第二乘，无浮点结合律或Float64新公理。

## 已有根如何接上

- **实际P**：6589/40588875685的五根原回执已核，其中`Submission.R21ScaledU32.native_integer_product_decode`给真实`(a.toUInt64*b.toUInt64).toFloat32`的decode。`R17UInt64Integer.product_word_nat`、`rounded_shift_cases`及`R14NatNormal.mantissa_bounds`给P、m、e与边界；不用复制旧reverse/clamp链。
- **原输入E1..23**：00ab R17完整源中的准确名字为`R18.R14NatNormal.raw_normal_decode`，只要求0<wordExp<255，覆盖1..254。**不要对原输入使用R2 NormalBand/target_raw_decode的E≥24接口。**
- **原Model目标**：同源`R18.R14ExponentShift.model_mul_normal_fields`接受sum128..380及两个原normal decode，输出`ofFields sign (middleExponent P+eu+ev−300) (storedFraction P)`。现固定174..380是其子域；`roundedShift P=middleExponent P−150`、`storedFraction P=mantissa P−2^23`将目标与第二小桥对齐。
- **真实signBits**：同源`R18.R18NumericMulSpec.sign_word_eq`已给 `(u xor v)&0x80000000 = if signXor then mask else0`，把actual e51a的word接到第一桥的Bool sign参数。移植时按真实namespace/精确新源重验，不仅凭简写名继承历史通过。

## 保留缺项与边界

两个新桥需要真实typing/replay/公理验收；没有生成normalCore完整输出/guard/fallback/public mul_spec。B在独立GuardFields接口处理原UInt32 guard与sum无wrap，本方不重复。最后carrier运输应通过正常目标的decode/canonical模型及原Model.mul字段等式；不能因为native结果相等就省掉raw payload与公开规格的连接。

S174对应scale的raw exponent1；S380仍有限，actual Pmax得到7f7ffffe。46→47的first-RNE carry仍保留在e∈{23,24}中；不把e固定成23。S173的旧table给0且实际guard拒绝，域不扩。第二桥只说已有RN24结果的power2乘法精确，并未声称第一cast保留48位精确P。

旧R17 UInt64逆cast/手工pack、R21/R22 scaled逆提取负结果仍只约束各自运行体；新直接native import的完整cost由D先决定。原manifest历史NOT_COMPILED/NOT_RUN字段不改，后来的验收以对应回执为准。
