# 首10分钟工程决定

UTC23:46:50接手；20分钟上限次日00:06:50，首判别23:51完成。只写本目录，无Git/CI/Lean/新agent，原route/prefix包不动。

**决定：存在真实删工作，支持一次有界数学闭合尝试。** 已认证40420540388全部83原件及精确74899988…/228187B源、C/ASM索引。实际diagnosticEntry正常数且S128..380成功路径58条指令，无FP/table/codec/call/内部spill；只计算一次P。standalone normalCore为28条含ret、无frame，但没有用它代替完整caller。

literal23/24选择不是branch或cmov：编译为P>>47构造bias与BT索引，再bt/adc加奇偶位。biased之后另取>>47处理carry；最终保留`shr ...,cl`。无重复乘P，没有额外postguard/FP结果判定。完整成功路径仍5save/16Bframe，冷native/table/codec/software臂完整保留。

Jam17实际MainFull成功路径62条/5save/16B已按原ASM逐项复核。可作有限机制对照：DirectBias删去Jam17的FP往返及相关夹位工作，但两者符号/源码包装/对象不同，不是同binary timing，不按58/62推速度。普通声明、两模块重放和7根审计通过仅认证runtime定义与旧public规格；新MUL等价证明缺失，public仍精确B2，未来public caller可另行降级。

详细原范围/哈希、完整冷路径、指令表与边界在audit.json。继续预算的依据是实际成本前提成立，不是已达整包收益；本阶段不修1180，不作数值/速度或新public MUL正确性结论。
