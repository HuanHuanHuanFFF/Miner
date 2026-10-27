# 低normal缩放：本地推导与待判别成本

原始域是UInt32编码指数1..23，全sign与fraction；不包括e=0，保留该域限制。输入字u+0x10000000将指数提高32到33..55，sign及fraction不变且UInt32加法不回绕，因此处于原公开R2 tableProduct的已验24..254域。先用既有normal_eq关闭第一次转换；第二次乘以真实2^-32才是新增需要证明的运算。

原公开60f的`R2W01cModel.mul_eq_of_finite_value`可提供恰当的实际舍入桥：从真实Model有限x/y/z、非零z和精确real乘积，先证明无溢出，再经实际roundAt与roundAt_toReal_eq得到完整Model相等。这允许在明确表示/舍入证明内部使用实数等式，而非把实数结合律直接当浮点等价。原始、放大、缩放常量和输出均normal；第一native乘法的整数mantissa转换精确，第二次舍入也须独立关闭。e=0反例已有限检查，网页需以真实固定模型再证。

代码生成必须按路径核对。现有header中lean_float32_once是static inline：热状态读state/value，冷状态才调用lean_float32_once_cold。看到C中的once名字不能断言每次都发生外部调用；也不能断言热状态的atomic load/条件分支免费。需要真实clang-O3循环路径、FP保存位置和普通路径控制项。候选公式的Float32.ofBits常量是否落入这种getter，由W14实际C/asm判别。

若getter保留实质成本，一个后续待评估实现选项是复用现有R2 scaleTable中表达2^-32的固定条目（指数索引118，scaleBits生成(118-23)<<23=0x2f800000），用已有表加载替换新增常量getter。此处仅为基于实际公开表公式的预案，不实施、不派发第二方案，不声称更快；必须先读W14实际路径后才能决定是否值得进行一次针对性修订。

本地只有23,874有限原字模型检查以及公开807输入曝光；没有新竞赛候选、运行性能或正式收益结论。单遍rawNaN sum3d9仍为独立当前候选，不能将两路线收益相加。原截止与冻结时间不变。

完整decoder若以后集成，还需一个独立守卫接线义务：原wrapped低条件为假时，a≠0且a<0x0c000000；再加a≥0x00800000，才推出真实wordExp∈1..23。W12b已给的a<Inf较弱，不能单独作为这个域证书。这个义务可直接按UInt32.toNat模减与真实wordExp/magnitude分解证明。低条件真时保持原table/high判别；e=0 subnormal走原ofBits；±0仍原wrap零快路；NaN/Inf仍原高端fallback。任何正式unconditional decode_eq必须关闭四个分支，不把低normal条件藏成最终前提。
