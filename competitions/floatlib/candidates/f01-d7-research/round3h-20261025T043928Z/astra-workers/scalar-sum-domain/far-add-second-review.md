# Far-add 复核：本窗不交第二运行候选

2026-10-25；cutoff84 源837341a5保持冻结。新证据在 `far-add-screen.json`，外部5秒上限实际执行，32,256个scalar样本与65,536对8位指数guard模型检查约0.246秒。

## 已有数学无需重做

R14 `astra-far-add-nat-draft.lean`／`astra-far-add-model-draft.lean` 是未编译的另一条归约，需要 nearest-multiple、NatNormal、WordAddAlignment 一整条依赖。**同一个正常输入 gap≥26结论其实已有原版完整验收源**：`f01-r6-web-absorption26-proof2/Kernel.lean`，SHA65cd1338…，39796984460/seed720，原gate PASS。

直接复用的接口是 `Submission.Absorption26.spec_right/spec_left`，其条件为两原字正规有限且指数差≥26。下层 `R6W02Dyadic26.roundDyadic_addDyadic_far26` 已处理异号且高数恰为2幂时下降binade的更密spacing；不需重新证明R14草稿的log/rounding链。

不能错误降到gap25：`0x3f800000 + 0xb3000001` 原结果为 `0x3f7fffff`，返回高数 `0x3f800000` 错。gap24同号奇尾数tie也不能普遍吸收。不能全局交换raw add，既有spec_left只在有限dyadic域用交换律。

## 负结果是具体已测源，不是整个命题失败

R6完整D实际candidate/parent add=1.0774068，whole归一化=1.0042271。以同组原始verdict重算cell：dense1.2946282、ml1.0677501、sparse1.0491429、specials1.0200992、subnormal1.0730562、paired1.0666503、extremes1.0544313。不能说它尚未做过完整性能实验。

该运行源用两个有方向的 `rightGuard`（gap先行，再normal/finite检查）；其父add用输入finite守卫，与df5c的结果nonNaN守卫不同，因此旧结果不直接证明所有df5c集成都慢。但新输入或新父源本身也不构成应重试的收益证据。

39796984460目录确有生成C，但 `candidate-c-index.json` 绑定的是8eb父源，不是65cd吸收源；不能把这份C/asm当作吸收路径机器成本。当前没有新near-guard实际C/asm或计时。

## 一个有区别但尚不足以升优先级的改法

将普通近距离拒绝改为一次UInt32区间判断：`(ex - ey + 25) ≤ 50`（32位回卷）。对8位指数它等价于 `|ex-ey|≤25`，65,536对完整枚举通过。near时直接走df5c，far时走已有Absorption26.add；正确性甚至不依赖这个区间等价，因为两侧已有全输入spec。它减少近距离上的两个有向guard，但新增subtract/add/compare及分支，far命中还保留normal/finite验证。这是可测的新实现形状，**不是已知提速**。

三组实际draw的normal-gap26样本命中：dense21.94%–40.43%、extremes35.84%–39.94%、sparse0%–22.07%；ml0%–0.83%、paired0%–12.5%。相关cell占whole见JSON，频率不能当作耗时占比或可消除成本。特别是40155753018的sparse完全没有normal-gap26命中，而79.49%的样本含finite zero；扩展零/次正规域又是另一组待验证桥与判断成本，不在此偷换。

决定：优先给cutoff84精确编译/首次D；不为far-add重新开数学证明链，不把未测廉价guard包装为第二个值得立即跑完整D的候选。重访条件是根/开发能拿到真实caller成本证据，或有空余验证吞吐明确比较near-prefilter与原guard；仍需新精确源自己的首次D，不用旧负结果换seed重挑。

## cutoff84反方检查转入

继续检查新cutoff的wrap排除、scale上界、特殊值排除、负零、原符号与LowScale桥。运行源不动，发现具体问题才发出修正证据；当前未发现数学前提缺口。Lean状态等待开发实际回执。
