# 40302810209 三处实际rewrite失败：最小证明修复

**新Kernel.lean：255728B，余272B，SHA00ab99c7ff16a8f0f58c5a0b6ad5c87c10c2407589ee17c5f9cba444b7cfd080。** 父本是D实际23ad，已与本次archive原始输入逐字核对；保留其try dsimp及全部运行代码。原23ad/176/365和D文件未改。

仅改原L6849、6873、6907三个证明行：将rw列表改为simp only，并将UInt32.toNat_ofNat换为UInt32.toNat_ofNat'。固定Lean293d5d0c的UInt/Lemmas.lean明确区分：primed声明针对显式(UInt32.ofNat n).toNat；非primed声明针对no_index(OfNat.ofNat n)。两处由FastMul.toUInt32_eq引出显式ofNat，另一处本来即显式ofNat掩码。限定simplifier规则不要求第二个rewrite模式仍存在，也不添加假设。

verdict与gate.log只保存三个rewrite失败位置，没有完整goal；这里没有编造goal，也不把“第一rw已归一化”定为已观测原因。采用显式构造子定理＋simp only处理这两个相容的表示状态。若新源仍失败，D应先保存该精确源的完整statement stdout/goal，再按实际目标修复。

proof-only.patch为唯一三行差异；逆向替换还原23ad全部字节通过。原intake/policy/options、LF检查通过；67根和public/fallback接线不变，HelperAudit.lean.inc同步。**实际Lean、模块重放、67根审计、全gate和性能仍NOT_RUN。** 没有本机Lean、CI、Git、模型重跑或新路线。
