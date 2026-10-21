# 等待 A11 时的读取删除排重

没有新增候选或实验。检查原 PC 的提前读取后，三条看似自然的低风险删除已经有直接先例，不能因为行表诊断显示“预取多”就自动改成这些候选。

1. `pc_xlen16` 在第一组 XOR 非零时仍提前计算第二组 XOR。R4 `r4-cpu-x2lazy` 已将第二组移到 `x==0` 分支；原 fast3 汇编当时明确存在 eager load，不是编译器早已删除。两块原协议约慢 0.792%，未晋升。当前同域不能仅凭可省 load 数重开。
2. match end 的 `ae` 提前读取加 `ahead_fix_m`。R4 `r4-cpu-endreload` 改为记录后直接读取，两轮四块约慢 0.1144%；binary/machine-code parser 正面，但 bundle parser 反面。不能按局部正例选路由或简单认为重复读取是浪费。
3. successful non-lazy 路径的下一位置只准备 slot。R4 `r4-cpu-slotonly` 保留失败/lazy完整预取，两块约慢 1.135%。先判 probe 再预取引入的新依赖顺序，足以抵消读数减少。

证据：`scripts/make-round4-cpu.py` 的明确单机制源码，`evidence/round4/cpu-notes.md` 111–120、135–139、295–304 及其原始回执链接。数值属于旧父/旧 runner 的历史，不是本轮复测。它们限制重访理由，不证明任何 PC 新结构永远无效。

对 A11 的要求仍是完整主索引表示是否带来足够大的新消费变化，而非把旧 eager/endreload/slot-only 消融包装成新方向。VERIFIED：直接历史定义与报告；UNKNOWN：当前641对应微消融实际时间；决定：没有新差异证据，不消耗CI再测这些旧点。
