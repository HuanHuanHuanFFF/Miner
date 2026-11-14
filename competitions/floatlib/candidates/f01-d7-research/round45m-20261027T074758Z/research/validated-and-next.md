# R20回收与下一研究决定

时间：2026-10-27T08:22:00Z；回复D082005800。

**独立回收完成**：CI40471664006，head a0724a5b，ec40源；R逐字节核全部37原件／2418944B、原input源、9条原axiom输出、Submission与VerifyFull实际replay.log及diagnostic-only verdict。9根PASS，仅三允许公理；无新public BMM／计时。回执`research/originals-verified-40471664006.json`，原索引SHA31a379bcdeb16b6e9fefe6ea1b9c7140d1443e0f81229d2116f44b3ffd2f98c9。

**后半段新条件**：固定Lean安全Array.modify经既有后端先把槽替为box(0)，让旧record“if possible”保持不共享；值得研究独占Array<F2>的原位record更新，避免同时保持8标量跨codec的spill。实际CtorReuse、closure和净成本UNKNOWN，须计两次slot写、RC、最终输出。B写最小safe接口；A写任意状态载体／任意p的逐列原序投影，不重复实现，不新开长CI。

原Array.Basic.lean75780B／85b1fcc2eac430164656c02295d9cf5d3549826517a2a89083a7afae28b1e4f2已先落E盘，再逐字节入`research/source-intake/lean-runtime-293d5d0c`，许可证沿用同目录LICENSE，回执array-api-intake.json。候选不新增unsafe／implemented_by／extern。

**廉价否定**：R的exact raw行列复用筛选85批／34case、94035 raw读，1049626采样MAC仅93可理想消除，全部命中都n=1，n>1无，adjacentBpair=0；不是时间或全局上界，不买实现。与D110批／126MAC同源已见输入交叉参考，不作独立确认。见`research/next-round/exact-reuse-screen.json`。

数学保留：SubRound.lean给一般除法分母的严格半单位减法RNE、shift及真实binade少一位的carry接口；Lean NOT_RUN。root异号纸面桥经C窄审修正“编码指数”为“归一化无偏指数”，小项明确允许subnormal；原add raw桥仍未闭。所有研究侧持续至共同08:32:58；R不改D冻结源和总状态，终态原件继续收齐。
