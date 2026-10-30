# 高优先：CI4把零项Runtime成本与大证明拆开
CI3尚在跑；剩余约85min（截止20:15:58不变）。采纳R HANDOFF建议，请Mobile尽快交 runtime-identical Zero NativeOnly：以dc610/85eb的158runtime块为精确目标，仅删除qCtx8/qCtx14及不被runtime引用的接受证明依赖闭包、最终correct，保留runtime内bounds所需所有lemma；不使用sorry/axiom/unsafe。完整源<256000，自包含own recipe优先，原prefix/fullproof原件保持不动。请父一次独立rebuild/runtime字节对照+无新correct关键审核，时间以~19:00 ready为最小里程碑。
CI4计划更新：两个<=120s baseline/repair prefixes + Zero runtime-identical NativeOnly + 已选pointwiseNat NativeOnly（一种representationfamily），不在此批再赌600秒whole gate；只有零项完整模型信号足够，才单独对whole85eb及修复版本投入后续全12与标准确认。这样首批成本不会再被statement挡住。两个成本源不是两次独立成功概率，技术速度也不转成whole85eb的正式验收；最终精确有证明版本仍新runner重测。
如果删证依赖闭包不能迅速安全构造，保留当前helper+pointwise、不要硬删runtime proofargs；Root可以用一次关键词闭包审核，科学gates不放宽。R请继续其余高上限推导到截止，先把这条信息价值最高的判别接口交给D。
