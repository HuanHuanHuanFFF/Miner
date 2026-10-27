# 待接的public出口：优先尝试现有FastMul word等式

当前1180和1359B运行体不变。WordBias的6根是无回卷B/high/shift/mantissa typedword尝试，仍NOT_RUN；这里只记录root建议经本方源码核对后的下一接口，不是新定理或第二实现。

B2已有FastMul.fastLog2_eq、rseAny_eq、fracW_eq、mkW_ofNat、sm1_eq、mul_spec；UnderflowZero.finiteScale_toNat也对任意UInt32指数给出正确分支。原件Kernel.lean的roundP在1924、fastLog2_eq在2076、roundP_eq在2156、finiteScale_toNat在6018。

正常域双方E1..254且S128..380：分别证明finiteMantissa等于已有24bit隐藏位尾数，finiteScale和为S−2。P范围给leading46/47，position=leading+S−2≥172，跳过零/次正规分支；leading−23为literal23/24。旧rseAny由seed接bias，PostBias给posth=(leading−46)+carry及newq=旧normalizedMantissa。实际product cap排除leading47再carry，所以normalizedPosition≤425；newE=S−127+posth=旧normalizedPosition−171。剩余mkW mask/frac及fromRaw与FastMul.ofBits载体运输后，可由FastMul.mul_spec闭合public域内结果；域外沿原B2fallback。

这避开新增Float32/Model乘法桥，可能比移植R14正常字段段短；实际源码长度/Lean资源/完成时间UNKNOWN。不要因这个出口重写WordBias或已冻runtime；1180真实编译/完整caller成本先行。若word证明展开比已验R14字段更昂贵，保留R14直接复用路径，不把本纸面分解当已证明捷径。
