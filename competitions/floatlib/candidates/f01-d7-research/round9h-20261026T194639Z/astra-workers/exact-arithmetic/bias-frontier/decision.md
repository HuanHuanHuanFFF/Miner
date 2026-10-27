# Bias前沿判别：保留一个directP64原型，不开新CI

**结论：旧4307B证明已经显式normalize beq，Jam的经验不能被记为修好它。** 亲读40153361143：bias-rne4-minimal真实exit−15/26.6s，full-build-output仅1byte空行，原因UNKNOWN；不能把它当parity报错或数学反例。逐字复用的Retained-BranchlessRNE-seed.lean.inc仍NOT_COMPILED。需新的真实编译才关闭历史接口，不再凭纸面换同义proof。

**旧负结果已重绑。** f529源与40166656717原始input均SHAf529f4d4…，原verdict为完整gate/score/PASS。对df5c整包1.2448032059573961、MUL1.702577694686987，保留停止结论。40166091242同源statement C的实际BENCH_PLAN→lam3正常路径在8491算P，按原high选23/24，再做remainder mask、两次大小比较、三flag/OR/AND/add；7360汇合后为high还有第二P站点。不能说机器真乘两次或真有三条件跳转，因为scalar优化ASM缺失；完整计时批codegen=false。因此未证明旧机器码与bias同价，也不能由C直接承诺新收益。

| 表示 | 相对当前Jam17可删工作 | 新增/保留成本及证明 |
|---|---|---|
| 规范化Jam32、固定7位bias | 两次U32↔F32转换及其clamp | 保留shift17/sticky/OR，再规范化J到bit30；bias固定7位。需要Jam精确桥和新的规范化/加法打包桥。 |
| **所选directP64 literal23/24 bias** | 两次转换/clamp，并省掉Jam压缩 | 按P原bit47选择两字面量偏置臂；各一parity-shift/AND及两add，按偏置后B重取h，最后有一个依赖h的右移。保留normal/S128..380 guard、XOR符号和B2fallback。 |

选择directP64只是它省掉中间Jam且已有受限U64 bias桥；64位运算不天然比32位快，literal分支/最终变量shift/sharedprologue可能抵销收益。只落一个完整guard/caller片段Runtime-direct-bias.lean.inc，1359B/SHAf3e868424175ddeedf37711d6370afbc3702995e3aa0f3df111d8a0ce86cb2c4。Jam32仅作精确整数模型和成本比较，没有第二运行稿。

**无第二carry的关键条件。** k按未舍入P为23或24，B=P+(2^(k−1)−1)+((P>>k)&1)。P<(2^47)时B<2^47+2^23，故B越过bit47恰对应旧商2^24，B>>24恢复2^23。P≥2^47时，实际P≤(2^24−1)^2推出B≤281474951544833<2^48，h恒1且无第二carry；不能扩成任意U64。最终h=B>>47，q=B>>(23+h)。50,004实际尾数对比较两种表示均0差异，含P=2^47−2和最大产品，见math-discriminator.json；仅有限整数证据。

PostBias.lean.inc，2839B/SHAf60bed0349b0a2ad255636098cde7e9b28a2d874b7bb68fa6ee668b2d83cbc7e，给出依旧seed的biased_quotient/bounds/normalized_quotient证明尝试。连同4307B原seed共7146B数学片段，**均NOT_RUN**。还缺literal机器B.toNat、postbiasWord、完整字段/spec接线和真实完整caller C/ASM；实际完整source字节/成本UNKNOWN，未建Kernel、未CI。

SoftFloat497c81c1的f32_mul和roundPack原文已亲读：它用产品jam31、规格化、固定7位rounding和ties最低位清除。机制参考来自JohnHauser/UCRegents/BSD3，原件/许可证在../../../development-source-intake/softfloat（从本轮根进入）；未复制C实现或NaN规则。新Lean直式为已有本项目bias公式的继续，不声称新公式。

**下一决定**：Jam1234/b271实际反馈优先。只有其完整caller反馈显示cast/clamp仍值得移除、且尚有验证吞吐时，才考虑一次必要的最小bias接口/完整caller编译；不是现在新增队列。新runtime可能只是另一整数低收益改写，旧9038/f529及00ab负结果全部保留。原件身份、完整旧成本及新片段SHA见history-and-manifest.json；本子阶段CI0，token/cacheUNKNOWN。

