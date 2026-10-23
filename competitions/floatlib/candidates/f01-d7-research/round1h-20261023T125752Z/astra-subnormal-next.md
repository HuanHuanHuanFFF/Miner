# 次正规数矩阵路线：只读结论

先检验输入域，不把821/822的3.15%/10.60%完整subnormal cell时间当作可省成本。硬件次正规乘加可能较慢目前只是机制假设，没有实际FP assist或指令计时证据。本次没有生成Kernel或外部作业。

**一个安全的充分零乘积guard是原始8位指数之和ex+ey≤102。** 每个有限binary32（包括e=0的次正规数）满足|x|<2^(e−126)，故此域乘积严格小于2^-150，即最小次正规数的一半；RNE结果为signBit异或决定的有符号零。指数255自动被排除，8位字段之和≤510不会UInt32回绕。数学推导尚未形成新Lean定理。

边界不能放宽成103：精确有理数舍入核对，19ffffff×19ffffff（指数和102）为00000000；19ffffff×1a7fffff（103）为00000001。99ffffff×19ffffff必须保留80000000。单有次正规输入也不够：00000001×3f800000仍是00000001，007fffff×40000000为00fffffe。零×Inf是NaN，不能用无有限前提的零判断。

不能随意跳过随后加法：一般acc=-0时加+0应为+0，跳过会保留-0。保留原native add最直接；若整矩阵每个乘积都已证明是±0，才可从+0种子归纳得整个dot为+0。可先用maxExp(A)+maxExp(B)≤102筛整矩阵，但扫描/输出成本和实际命中都需计入。

**更接近现有证明的路线是direct路径在ex+ey<128时复用LowScale.mul。** 当前41已有LowScale.roundLow_eq、roundSelect_eq、core_eq、mul_eq、mul_spec及FastMul.roundP_eq/rseAny_eq；R7W05.mul_toFloat32可连接实际word乘积到native乘积。R6已有outer_finite/outer_special_false。仍保持每次乘法先舍入，再做原native加法，不采用FMA或重排。word路径的guard miss、舍入、ofBits以及次正规结果上的native add成本仍在。packed保存的是已解码Float32，若增加toBits或重读raw，成本可能更高，因此先诊断direct。

第一最小判别：只用已暴露821/822输入，统计direct乘法的指数guard命中/miss，以及整矩阵max指数条件是否曾成立；无命中就停止零快捷路线，避免先投入新舍入证明。若命中，再把guard连接到真实roundP/RNE有符号零定理，并量实际调用上下文的完整成本。e139已有“零输入”分支全gate但整包变慢2.4%，不能拿它当本路线的性能支持。

适用域、原件位置、五个精确有理数边界样例及UNKNOWN见[JSON](astra-subnormal-next.json)。没有新Lean编译或收益结论。
