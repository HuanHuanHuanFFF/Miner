# R28 native 当前交接

实际加入UTC17:17:48；共同截止20:15:58不变。17:48检查点；Root独占Git/CI/冻结，严格文件；只写本目录，不本机Lean/native/派发/正式提交/资金。token/cache/CPU UNKNOWN。

- **当前首选Mixer：** `READY.json.candidate`，`build_gemm36_pairlinear_v2.py` **7b6e0cba/252828B**，3172B余量；pairlinear双行native128替换scalar prepared GEMM，finite正k全覆盖，非finite/空k回原Ya3，原nativeAdd/LN保留。v2仅纠正v1沿用k<20而丢prepared-smallK的范围问题；v1 **6751ff4b**冻结未动/不取消既开作业。`PAIRLINEAR36-V2-STATIC-AUDIT.json` policyPASS，两次重建相同；依赖/新名/共享YoYq已按Root请求独立源审。**新all12/原生速度UNKNOWN**。
- **ResNet互补BN：** `build_resnet11_inplace_bn.py` **2b49e6e9/255303B**，697B余量。#53原地输出遍历移植到#11，保留#11精确Ysx与每通道缓存/回退，无clip移植。`INPLACE-BN11-STATIC-AUDIT.json` policyPASS、448原声明字节未动。等首批profile后由Root选择是否与mapIdxadd/zero组成新精确候选，不能叠加收益；all12/速度UNKNOWN。
- **冻结后独立后续：** `build_mixer36_zero_b.py` **7100aaec/255937B**。MD2共享B解码0时跳两A读取/乘法/shift/carry；3个fresh证明名省112B。静态policyPASS，alpha逆后436原声明字节未动；all12/速度UNKNOWN。READY.followon明确**无额外CI请求**，不挤占近榜/独立确认。
- **覆盖/反例：** `SOURCE-CAPABILITY-COST-MAP.json`；9旧已见完整Mixer输出hash匹配的`MIXER36-BLOCK-CENSUS.json`：205628/244203逻辑MAC native域，≤16分块merge上界75632，whole64仅31031MAC。`WordPairMerge2.lean.inc`未编译条件引理；30000有限word例中22412带guard匹配、7588无guard反例，不能丢signed-mass范围约束。不是walltime/全输入证明。

ACK根172118/172700/173000/173300/174000/174300/174700；近榜完整判别与新确认优先。下一步：继续独立核心分块/布局成本研究；主候选只读，等精确gate/成本反馈再决定。历史过程在archive/HANDOFF-through-1748.md；wholeKernel均本地忽略source-private，公开own recipes/receipts。

18:02：读原CI1 profile并ACK175000/175400。`REQUEST-ROOT-RESNET-INTEGRATION.md`：新精确组合**70eed360/255847B**（zeroPair+本BN+Root已修mapIdxv2），153B余量，policyPASS/444旧声明字节未动；all12与速度UNKNOWN，供已计划Res批次择用、不新增CI。Mixer block2新NativeOnly **b5c20fde/253202B**，无correct，cost/全证UNKNOWN，接口见BLOCK2-PROOF-INTERFACE.md。

18:32新完整Mixer组合：`REQUEST-ROOT-MIXER-PORTFOLIO.md`，**00261227/253445B**（recipe00765461），pair-v2＋norm26＋精确probe筛选singleton＋BX.any准备过滤。policyPASS/原430声明未动，ZMV0/finalcorrect字节相同，新all12/速度UNKNOWN。9旧cell模型hash匹配，准备52455→30961词，仅2/9有native classifier才prepare；是计数非速度。可在既定Mixer批中优先于无筛选singleton，不新增CI。ACK181600：Res目标已变64/约19.015%需降，6.07%仅旧快照。
