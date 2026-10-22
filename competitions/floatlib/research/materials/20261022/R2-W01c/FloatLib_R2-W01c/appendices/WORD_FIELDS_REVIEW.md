# WordFields / IntegerDyadic 独立静态压力复核

**Lean 编译 NOT_RUN。** 本记录只说明固定源码的名字、参数、表达式形状以及证明策略检查；没有把静态检查称为 kernel 验证。

## 已修正的具体问题

1. `high_bit_of_lt512` 原 `change` 把 `Nat.and_two_pow` 的输出误认成布尔 if。固定依赖实际定理为：

   ```lean
   lemma and_two_pow (n i : Nat) :
     n &&& 2 ^ i = (n.testBit i).toNat * 2 ^ i
   ```

   已改为 `(decide (n / 256 % 2 = 1)).toNat * 256`，然后分别用商为0、1归约。该分支划分对所有 `n < 512` 有效，不是输入枚举或浮点样例。

2. 为避免 `rw` 已经通过反身性关闭目标后留下多余 `rfl` 的风险，`raw32_sign` 使用单条 `simp only`；highbit 两分支使用 `simp [hd]`；无回卷减法桥直接 `simpa only [het] using UInt32.toNat_sub_of_le ...`。

3. 所有比较与 `decide` 中的 `(tableIndex u &&& 255)` 加显式括号；不依赖读者或编辑者记忆运算优先级。

没有改数学域、指数阈值、任意 fraction / sign 量词，没有加 normal 等价假设。

## 固定定义与签名核对

- `Model.ofUInt32` 是 `ofNatBits u.toNat`；binary32 的 `bits` 是32位 BitVec。因此 `raw32_bits` 的 `change` 与 `BitVec.ofNat_uInt32ToNat` 对齐。
- `Model.signBit_eq_msb` 输出 `x.bits.msb`；`BitVec.msb_eq_decide` 输出 `decide (2^(w-1) ≤ x.toNat)`。`w=32` 给精确阈值2^31。
- `Model.expField` 定义为右移fracWidth后与expAllOnes做按位与；binary32为移23、掩码255。
- `Model.fracField` 为低23位掩码；`Nat.and_two_pow_sub_one_eq_mod` 正好转成模2^23。
- `UInt32.toNat_shiftLeft` 给 `(aN <<< (bN % 32)) % 2^32`；本证明移位常数23，`change` 已保留32位回卷后再由范围消除。
- `UInt32.toNat_sub_of_le (a b)` 前提确为 `b ≤ a`。`E ≥24` 先导出23≤E，再做整数相减，未误用可能回卷的自然数减法。
- `Nat.or_two_pow_eq_add_of_lt` 前提是低字段 `< 2^n`；mantissa低字段范围来自模2^23。
- `Nat.two_pow_add_eq_or_of_lt` 的形状是 `2^i*a+b = 2^i*a ||| b`；scale字段低项小于2^31，恰足以将sign与低项的OR转换成加法。
- `fields32_toDyadic` 所用 normal fields 定理前提分别为 exponent非零、exponent<255、fraction<2^23；原word和scale的E/ E−23都满足。

所有保留的 `omega` 目标只涉及常数倍、常数除余、Nat减法、Nat/Int嵌入以及线性不等式。数学上充分；首次实际运行仍需验证 tactic 的归约与约束收集能力。

## Mathlib 来源

固定 FloatLib `lake-manifest.json` 锁定：

- Mathlib `5ed2965256430c3649e86755f9576b54eca72435`（inputRev为v4.34.0）。
- [Mathlib/Data/Nat/Bitwise.lean:243](https://github.com/leanprover-community/mathlib4/blob/5ed2965256430c3649e86755f9576b54eca72435/Mathlib/Data/Nat/Bitwise.lean#L243)。Apache 2.0；文件声明作者 Markus Himmel、Alex Keizer。

本轮读取此固定公开文件核对签名，未安装或升级依赖。完整raw下载SHA256：`457f9b6ea6b6b639d7219cd5f00e7fb390604730cf51f25d8f01d2a14a3b87d2`。

编辑后的 `WordFields.fragment.lean` 为7,533 bytes，SHA256：`5ee69b435617b295d3fc2ef3d7e3e72e75dc448f8252dcba0ccce5b098413def`。
