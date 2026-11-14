# RSE接口储备：无运行时log2，旧MUL负面使本窗不追加独立CI

20分钟限时调查实际首工具01:51:32Z。9038完整原gate/25轮的三个选定原件已重新hash，source233544B与stage=score/passed/25 rounds匹配40155753018；创建时manifest的NOT_COMPILED保留当时状态。该验收只覆盖原精确源。旧whole/df5c=1.04714、MUL/df5c=1.29080、p05=-0.04566，保持PARK；不能当当前B2或新outlined成本。

**运行体不经过log2。** productWord为两个24位尾数的UInt64积，high=P>>47，shift=23+high；roundedWord只调用原FastMul.rseAny，随后carry=rounded>>24、exponent/fraction/mkW打包。rseAny内部还有shift分类；rse有quotient、remainder mask、half、两比较及tie parity。这比DirectBias多保留具体工作，编译器能否删shift分类／复用重复product与rounded表达式、hot frame是否消失均UNKNOWN。math里的p.log2只用于证明/抽象定义，不是该core的可达调用。

9038当轮codegen_present=false，没有选中caller ASM。其他新批次ASM里只出现R14的section标题，相关index也未选R14 core，不能据此宣称真实机器零log2或已删frame。本调查在R14/R18/R19相关索引未找到这个精确RSE+B2冷尾已测记录；不是全仓/所有历史的不存在性证明。

`Runtime.lean.inc` **2273B／908ae8d016c50bc1c72614f3d04ae95e5fd7d7d63ee0204dabd611f762156e8f**，复制9038的13个运行定义，唯一新增机制为B2 retainedB2 noinline冷尾；同时给inlineOld对照。B2的rse/rseAny/mkW/mantissa文本与原9038逐字一致。三normal/S守卫与原eligible不动，无FP/cast/table或新NatBias。仅限精确B2 carrier，4 public仍B2；未编译/计时。

证明复用件 `AcceptedMathSupport.lean.inc` 为原连续23596B逐字切片，含R14NativeProduct→R14NatNormal→R14ExponentShift→R14DIntegerNormal→generic guardedMul_spec。roundedWord_nat直接组合FastMul.rseAny_eq和FixedWord.roundShiftRightEven_toNat，独立于新NatBias。`ColdBoundary.lean.inc`＋`ProofTransport.lean.inc`给新wrapper到既有全输入定理的最小接线，仍NOT_COMPILED。两种组装只能选一种：B2+Runtime做成本；B2+MathSupport+Boundary+Transport做后续证明，不能双加重名定义。

B2+完整support共250425B，距cap5575B，可容wrapper/新public aliases；本调查没造大public Kernel。后续可将Submission等长改名R22RseBase，再从新Submission导出四入口；保留原源maxRecDepth8192，不增资源。若从旧9038接线，其public mul已经是RSE，冷fallback必须指mulBeforeExponent；不得把它误当B2或回指新public造成双guard/递归。

**决定：留接口，不抢当前F7验收／NatBias诊断。** 无log2阻断且无需重写IEEE数学，但旧29%MUL负面和额外RSE工作不足以支持独立CI/大工程。只有D现有低边际slot可做一次同binary静态IO控制/inlineOld/outlined完整cost：先追实际Suite callback与generic RSE残余分支/冷热frame，再看全部guard miss与原Suite计时。新proof、selectedASM、B2比较与速度均NOT_RUN/UNKNOWN；不继承9038、B2或DirectBias成绩。
