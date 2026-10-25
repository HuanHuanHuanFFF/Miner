# 整数正常域乘法：当前证明缺项

UTC2026-10-24约22:15，开发侧自己的组件草稿；不改研究冻结源。

运行体在development-integer-normal-draft.lean：24×24位UInt64乘积，乘积最高位决定23/24移位，R14BiasRNE偏置舍入，R>>24给进位，直接设置指数/小数/符号。正常域仍用研究侧已做有限全指数域核对的normal1..254与指数和128..380守卫；域外保持原公共mul。运行路径不调用Float32转换、浮点乘法或toBits。

当前已写出的证明尝试包括乘积无回卷、最高位与log2对应、23/24移位、偏置舍入到原RNE、rounded范围及carry对应。全部NOT_COMPILED，不把代码存在当作Lean接受。

尚须把exponentWord.toNat证明为middleExponent(P)+ex+ey−300，把fractionWord.toNat证明为mantissa(P)−2^23，再接FastMul.mkW_eq与完整raw/spec链。证明只在guard内要求输出normal有限；域外不改语义。舍入R=2^24时fractionWord自动为零，指数加一；P在h47时不能出现该进位，128/380边界必须用真实乘积最大值保证。

最终独立候选应替换原proof1中的first_product_bits/core_word实现证明，而不是把两个运行实现及备用proof全堆进包；完整包仍≤256000B。研究侧指出的两条无属性未引用辅助定理共1543B仅可从新集成版本移除，原56773d4d保留。尚未构造声称闭合的完整整数候选。

这是原先只改log2而更慢的M19之后的结构差异：整个正常域直接偏置RNE和打包，删去通用rounder的zero/subnormal/overflow分支及全部浮点转换调用。实际成本仍需目标机器码和原版完整配对计时，不从操作条数估算提速。
