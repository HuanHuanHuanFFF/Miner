# cutoff84 反方静态核对

核对对象始终是 `Kernel-cutoff84.lean`，SHA256 `837341a52575cffa9b5dfee6a44ba9369d1ee7ae4f6bb47fa47af11ae1f5831b`。没有改源码；此稿不声明Lean通过。

## 逐层攻击点与结果

1. **UInt32指数和回卷。** 原始Word expField是 `(bits>>>23)&&0xff`，值0…255，和≤510；新cutoff_nat用实际 `expField_lt (ofUInt32 a)` 与 `toUInt32_ofUInt32` 得界，再用UInt32.toNat_add去模。h约束不是无界Nat指数的替代，也没有依赖测试输入。
2. **特殊值伪装成低和。** NaN/Inf至少一侧exp=255，另一侧非负，且无回卷，因此不能满足≤84。`cutoff_special_false`由此接已有FastMul.special/sm1_eq；zero×Inf与zero×sNaN留原fallback。模型专门保留这两种拒绝样本。
3. **subnormal尺度和与normal尺度和混淆。** 实际finiteScale UInt32先零扩展为UInt64，再按0→0、正值→e−1。copied finiteScale_toNat覆盖e=0；新scale_sum_le只用scale≤e，不假设双方normal，也不无条件减2。
4. **UInt64 scale加法回卷。** 上述两侧scale≤原指数，其Nat和≤84；证明在UInt64.toNat_add后明确消去2^64模。没有把机器加法无条件当Nat加法。
5. **下溢判定是否依赖24位乘积界。** 本版故意不依赖它。对任意UInt64 product，fastLog2≤63，position≤147<172；149−scale≥65，所以实际rseAny落在>64的零分支。product=0也走原signed-zero分支。复制的roundP_zero正是这个全UInt64命题，故无需新RNE中点/尾数定理。
6. **负零符号。** 新返回严格使用原FastMul.core中的 `Bool.xor(signBit x.raw)(signBit y.raw)`；没有把乘法结果零统一成+0。实际signBit定义为 `(bits&&0x80000000)!=0`。两异号tiny输入模型均为0x80000000。
7. **绕过原LowScale guard是否丢规格。** `shortcut_eq_low`先用已验LowScale.mul_eq，再用special=false展开FastMul.mul/core，最后反向调用roundP_zero。它不靠浮点实数相等、不改NaN策略、不跳过新分支的证明。
8. **影响sum/BMM顺序。** 逆patch只能改回一个scalar mul定义和其spec，加上独立证明namespace；add/sum/BMM/LowScale/nativeMul源逐字保持。任何代码布局影响仍由整包实测发现，静态相同不宣称耗时不变。
9. **隐式新公理／工具链。** 新片段无sorry、admit、axiom、unsafe、extern或implemented_by；仅沿用ContractTensor。没有改maxRecDepth、gate、pins或bench。标准三公理的实际审计仍等本源Lean回执，父源审计不代替它。

## 实际待验的elaboration点

- `cutoff_nat`的 `rw [UInt32.le_iff_toNat_le, UInt32.toNat_add, Nat.mod_eq_of_lt hsum]` 与现有outer_finite证明相同结构，差别是≤84而非<128；数值类型均已由UInt32固定。
- `scale_sum_le`两次finiteScale_toNat重写后`split <;> omega`只处理Nat零/减一关系，没有乘法或指数搜索。
- `shortcut_eq_low`的`simp only`展开后两端同为FastMul.ofBits；`congr 1`后等式方向是roundP_zero.symm。
- root mul_spec的两层split对应先<128再≤84，hcut必须绑定内层cutoff；实际Lean可能暴露匹配/简化问题，出现诊断后按精确目标修正，不预先重写稳定源码。

结果：没有发现具体数学前提缺口。**确认范围为静态证明审查与既有6256模型样本；本源Lean/fullgate/性能仍NOT_RUN/UNKNOWN。**
