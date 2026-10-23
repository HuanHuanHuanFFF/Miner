# R10：矩阵两小时

用户继续优化2h，并要求多测1—2组不同输入。共同窗口17:00:31—19:00:31 UTC（北京时间10月24日01:00:31—03:00:31）；晚启动不延期。D独占Git/CI/采用/状态；你沿用Astra研究角色，不派额外agent/线程或Goal，不本地装工具链。

你只写 `competitions/floatlib/candidates/f01-r10-bmm-*` 和本目录 `astra-bmm.md/json`。D负责低指数word乘积类型修复、复测与看板基准修复；不要改D文件或41/旧候选。17:13前给实质检查点，17:25前交可冻结单一候选或关键缺口。优先从仍为Nat的DirectSmall循环/地址开销或n=1专化中选较大收益且可证明的一条。参考旧47d singleton-native-normalize（未跑完整）、Packed10Index的真实USize证明及R9机会报告；与既有两条负面机制区分，不扩大packed width网格。

实际起点41bce485全包235169B。R9已验直接numericdecoder BMM慢17.3%、NaN native eventreplay慢2.22%，不重试同样机制。现有n1源码的负零normalize证明块可调查；每次乘积先舍入，+0起点、负零及NaN payload必须保留。全源≤256000B、四导出/四spec、仅原允许公理，官方contracts/gate/bench/pins不变。看板冠军预估仍是假设锚，不能作为这轮采用的测量证据。

先读R9 README/bmm-opportunity-review.md、实际Kernel和旧失败，比较一两条不同路线，给预期曝光、完整成本、证明/字节代价、证伪条件。只生成一份候选；若证明难先交关键引理/最小诊断，不造无证明近似替代。源码/manifest先完整写、hash核对，最后发布READY状态；待D确认冻结后不再改源。普通交接落文件，D在检查点读。D会用新种子至少三组完整对照，收齐CI原件，正确性与性能分开。
