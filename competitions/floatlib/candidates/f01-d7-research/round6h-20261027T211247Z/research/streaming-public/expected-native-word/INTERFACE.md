# 原始word到native导入word：一次检查的整数目标

阶段 **2026-10-28 01:50:33—02:10:33 UTC**；共同截止03:12:47。独立新目录，仅3根小数学接口；无新运行版本、Kernel、CI或确认数据读取。FloatArray f5a/303a/91ac继续冻结。

`ExpectedNativeWord.lean.inc`给出：

1. `canonical_nan_raw`：固定`ofFloat32 Float32.nan`的raw为0x7fc00000，闭常量`decide`证明尝试。
2. `import_raw_eq_expected`：对任意Binary32 x，`ofFloat32(toFloat32 x)`的raw等于`expectedWord x.raw.1`。定义只用原`R7W12.rawNotNaN`，即absraw≤0x7f800000时原raw，否则正canonical qNaN。
3. `checkNative_eq_expected`：对**任意stored:Float**，旧fb7d的native双边word检查与“backcast导入word == expectedWord raw”这个Bool完全相等。包括检查false，未假设opaque宽转换正确。

证明复用既有R7W12.rawNotNaN_eq_native_classifier、NotNaNProbe.roundtrip、R7W05.native_eq_nan_of_isNaN；true/false分类的Bool.not_inj形式与保留B2中native_step_eq/repair_quiet相同。没有Float64算术定理、非NaN前提或新公理。**3根均NOT_RUN**，不是Lean验收。

## 常量来源不是猜测

固定FloatLib `0d91825727839f597fd06b22fdd038ea21480f0c` 的旧Native/Model.lean `ofFloat32Model_nan`与R7W12.ofFloat32_nan_toModel已把native nan接到`Model.canonicalNaN binary32`。Carrier.lean272–273定义canonicalNaN为expMask OR quietBit。

本次补取同一固定commit的Format源码，全部存于primary/并按Git blob SHA验证原字节：Catalog78–84给expWidth8/fracWidth23；Properties209–210、319–320、327–328给`(2^8−1)*2^23`及`2^(23−1)`；Storage39–40、64–65将它们变为相同storage word。故mask0x7f800000 OR quiet0x00400000=0x7fc00000，不带sign位。URL、Git SHA、文件字节/SHA256在primary/source-index.json；MIT/FloatLib Team版权原样保留。源码日期早于本轮冻结，不是新确认输入。

## 覆盖与未来成本变化

±0、正负normal/subnormal、±Inf均原word保留；任何正负qNaN/sNaN及payload都映射到正0x7fc00000。这描述**native导入值**，不是修改原rawB或原NaN回放策略。旧raw目标检查会拒绝非canonical NaN；这里严格等价于fb7d的原native目标检查。

未来若有成本支持，producer可以保留本来已读出的rawB，仍只计算一次sourceF32和一次storedF64，检查backcast的ofFloat32 raw与expectedWord(rawB)。它在源级去掉sourceF32那侧的toBits表达式，换成一次整数mask、比较、选择；每字段2个toBits表达式变1个，不增加decode。仍保留backcast narrow、一次toBits、原bool失败fallback以及原rawB用于finish。**实际外部调用是否减少、收益及额外整数依赖均UNKNOWN**；没有改f5a源，也没有把这一接口混入当前确认候选。

首最小反证边界是±Inf必须保留（条件为≤而不是<）、−0不得丢sign、非canonical负NaN不得保sign/payload。有限纯整数检查只核这些分类与变异，不证明Float32模型或opaque cast。后续先原型真实typing及成本；不继续铺public bmm证明。
