# 第十八轮：八小时双候选研究交付

**最终两个精确候选及八块独立确认已收齐；固定八小时窗口尚未结束，15% / 5% 目标未完成。**
交付两份不同算法的公共 gate 通过包：A 为 DNA 前缀域分离，B 为按内容类别保留 RF 规划。没有正式竞赛上传；正式 admission、私有集成绩、注册归属、额度与实际可支付份额均为 **UNKNOWN**。

固定北京时间 **2026-10-10 01:32:51—09:32:51**（UTC 17:32:51—次日 01:32:51），上下文压缩和额度重置没有重计时间。执行规则见 [AGENTS.md](../../AGENTS.md)。逐阶段原始判断见 [研究状态](../../evidence/round18/research-state.md)；早期峰值和负面结果保留，没有用最后快照改写历史观察。

## 结果与口径

本表固定在官方快照 **29456**，官方计算时间 **2026-10-09T23:51:08.730471+00:00**；读取区间 2026-10-09T23:57:55.050593+00:00 至 2026-10-09T23:58:16.731374+00:00。共有 595 条提交、557 个榜单账户。竞赛 context freshness 为 `unknown`；另外读取的 weights/current freshness 为 `stale`，没有提升为实时一致性保证。

以下均为 **INFERRED 公共条件估算**，单位是竞赛奖励池百分比；没有乘验证者总权重中的 20%。使用各自同场正式参照 #582 / #586 校准，分别插入当前前沿、重新归一化。主对照与 shadow 使用相同源码和二进制，但独立配对测量；shadow 不是新算法。达标次数是观测计数，不是正式成功概率。

| 候选 / 对照 | 单独份额中位数 | 观测范围 | 最佳值 | 零份额 | ≥5% | ≥15% |
|---|---:|---:|---:|---:|---:|---:|
| A / primary | 0% | 0%—0.043445% | 0.043445% | 5/8 | 0/8 | 0/8 |
| A / shadow | 0.008114% | 0%—0.075091% | 0.075091% | 4/8 | 0/8 | 0/8 |
| B / primary | 1.667652% | 1.400194%—1.892112% | 1.892112% | 0/8 | 0/8 | 0/8 |
| B / shadow | 1.668148% | 1.379048%—2.03431% | 2.03431% | 0/8 | 0/8 | 0/8 |

A 对应单候选 15% 目标，B 对应另一个单候选 5% 目标。两份 Rust 不同，A 的多个 proof 修复版本仍只算一个候选。

| 同时插入前沿 | A 中位数（范围） | B 中位数（范围） | 同时达到 A≥15%、B≥5% |
|---|---:|---:|---:|
| primary | 0%（0%—0.043385%） | 1.766202%（1.400194%—2.02213%） | 0/8 |
| shadow | 0.008081%（0%—0.075039%） | 1.700934%（1.379048%—2.284438%） | 0/8 |

联合值由同一 runner、同一计时块、同一对照类型的两个点共同插入后计算，不能把单独份额相加。几何份额还以两者使用无旧前沿提交的不同合格 hotkey、通过正式 admission 且奖励未封顶为条件。

**VERIFIED 规则重放**：若使用公开 #573 的 hotkey，#573 在所有上述插入情景中仍存活，新 A/B 的新增可支付份额均为 0。#453 所属公开归属组的另一组情景也已保存。当前用户是否拥有这些注册、可用槽位与额度没有重新核验，不作当前事实；本轮未读取私密注册材料。[支付条件逐块重放](../../evidence/round18/final-payability-scenarios-current.json)。

完整入口：[最终汇总](../../evidence/round18/final-confirmation-summary-current.json)、[逐文件原协议复算与联合几何](../../evidence/round18/final-confirmation-analysis-current.json)、[官方快照原始回执](../../evidence/round18/official-confirmation/receipt.json)。

## 精确文件、证明和审阅包

### A：r18-dna-base6-proof2

保留 65,536 个 heads，把 A/C/G/T/N/换行的六字符前缀放入 46,656 个无碰撞槽，其余前缀使用剩余槽。公共实际输出 5,339,229 B，比 #582 少 1,622 B；改善只出现在 genome。

- Rust：`f5c1437c6e613a5a3c0740d590ac7ce972a24b86d963122c6ace3c576c3a98fd`
- Lean：`02a21f164476aa843a97e3cb947c27c8fc74345aa625c497e76151721b63ec01`
- 完整原版公共 gate：run **38001724485**，**506.4 秒**；Git `fdbce211915620eced680b08860546b25e4bd664`。
- [源码](../../candidates/r18-dna-base6-proof2/parse.rs) · [证明](../../candidates/r18-dna-base6-proof2/Parse.lean) · [原始完整 gate 回执](../../evidence/round18/38001724485/gate-base6-3/exact-gate/exact-gate/gate-receipt.json) · [两文件审阅 ZIP](../../evidence/round18/review-packages/r18-dna-base6-proof2-f5c1437c6e61-02a21f164476.zip)。
- ZIP SHA-256：`15627a1a839c8888c0d851de9903991a1ec83f3a8307b9cb20e50dd0271a9a2e`；[包清单](../../evidence/round18/review-packages/r18-dna-base6-proof2-f5c1437c6e61-02a21f164476.json)。

### B：r18-586-selective-rf

保留 #586 原有基础引擎和分类器，仅在类别 13/25/26/29 继续 RF 规划。公共实际输出 4,865,533 B，比 #586 多 678 B；这是质量与总时间的交换。

- Rust：`b03af48fe3916b5b82dd563a4a69dbcc6e3e424579bd98ed0a11add6ef8b1bc6`
- Lean：`8c5d3ebbcf0f681f7005cc86a5d4a3045778af7165ffd145439b4d9b125ca9f2`
- 完整原版公共 gate：run **37982026752**，**507.3 秒**；Git `702574d549986e392fad11cbe36a048cb9f4e0f9`。
- [源码](../../candidates/r18-586-selective-rf/parse.rs) · [证明](../../candidates/r18-586-selective-rf/Parse.lean) · [原始完整 gate 回执](../../evidence/round18/37982026752/gate-selective-1/exact-gate/exact-gate/gate-receipt.json) · [两文件审阅 ZIP](../../evidence/round18/review-packages/r18-586-selective-rf-b03af48fe391-8c5d3ebbcf0f.zip)。
- ZIP SHA-256：`bc3fe52256ba8bc2378dbfec59f695d2434d5cfd0bc47e58c744b1241f27525e`；[包清单](../../evidence/round18/review-packages/r18-586-selective-rf-b03af48fe391-8c5d3ebbcf0f.json)。

两次成功 gate 均重新进行官方 Charon/Aeneas 提取、检查原始 `LZ77.Obligation slot.parse`、公理白名单和完整公共 corpus-stage1 round trip；官方源码、contract、encoder、pins 未改动。公理只有 `Classical.choice`、`Quot.sound`、`propext`。本地有限等价或 proof 复用没有替代完整验收。

A 第一次 gate 的掩码转换边界及 WP 续体证明失败、第二次宽泛简化触发原 900 秒超时，均保留原始失败；最终通过版本改为局部边界引理与续体证明，Lean 主体 418.9 秒，没有提高超时或添加公理。这三版 Rust 相同。

## 冻结后的独立确认

先冻结两个精确文件对，再启动 AT 与 BA。BA 在查看 AT 结果前登记，未按高低点选择性补跑。两台各四块，共八块；不是八台 runner。

| Runner / run | CPU | 原协议配对进程 | A 主 / shadow 中位 | B 主 / shadow 中位 |
|---|---|---:|---:|---:|
| confirm-at / 38003736134 | AMD EPYC 9V74 80-Core Processor | 40 | 0% / 0.008114% | 1.801934% / 1.768969% |
| confirm-ba / 38004111809 | AMD EPYC 7763 64-Core Processor | 40 | 0.017836% / 0.011461% | 1.519666% / 1.472731% |

每个进程包含 28 个固定公共文件、15,930,000 原始字节；每文件 1 次预热、11 次计时，取每文件候选/配对 incumbent 总压缩时间中位数之比，再等权平均。原始所有 reps、文件哈希、token/输出哈希和环境均保留；两个 runner 的统计分列。没有用 parser 单独耗时或总字节加权比替代两轴。

两个 runner 均为 Linux x86_64、rustc 1.100.0-nightly（2026-08-17，固定 nightly-2026-08-18 工具链）。原测量入口记录请求 CPU 0，但实际进程 affinity 为 0–3；原协议结果如实保留。显式 CPU0 / 平衡顺序的另行诊断与原协议分列，不宣称原确认已严格绑单核。

A 在 5/8 块更换同源码参照后发生零/非零切换；B 为 0/8。两者都没有 5%/15% 达标判断分歧，因为本次所有逐块值均低于门槛。DNA 同源码时间差实测范围 −0.6131%—+0.6906%，#586 同源码范围 −0.3310%—+0.5284%。

[预先冻结计划](../../evidence/round18/final-confirmation-plan.json)；早期 Y 的一台四块确认、AP 的发现块及之后作为 control 的测量仍分别保存，未混入本节八块。

## 评分敏感性与目标缺口

**VERIFIED 复算，INFERRED 收益**：A 的 shadow 平均坐标在该快照得到 **20.318689%**，但八个实际 shadow 块的最大值只有 **0.075091%**。平均坐标落入邻居切换的狭窄位置，不能当成期望收益。AP 历史单块 18.27497% 与其余低值、shadow 全零仍保留，不作最终达标证据。

在保存的快照 29456 上，仅以极小的合成坐标变化跨过 #533，评分由稍慢侧约 24.0223% 变成稍快侧约 0.00958%：候选支配并删除 #533 后成为最快端点，局部系数、全局系数与大小改善预算同时改变。跨过 #539 的慢侧则被支配为 0。该审计只解释评分跳变，不是新速度实测或收益达标。[边界逐项重放](../../evidence/round18/score-boundary-audit-29456.json)。

同一最终测量从旧快照 29434 换到 29456，B 的主中位预测由 2.35364% 降到 1.66765%；这是竞争前沿变化，不是代码测量变慢。两次快照及同测量对比在 [前沿变化重放](../../evidence/round18/confirmation-frontier-change.json)。后续新快照的值见本文首表，不覆盖这个历史观察。

A 的最后八块逐文件分解中，唯一输出变化的 genome 对相对时间轴始终是正贡献（变慢）；看似变快的块由其他 27 个输出未变文件的计时贡献推动。程序、编码器与配对分母均参与变化。输出不变并不能证明执行路径不变，这只是观测分解，不把噪声宣布为唯一因果原因。[最终分解](../../evidence/round18/base6-final-time-components.json)。

| 固定另一轴的有限坐标搜索 | 5% 最近样本 | 15% 最近样本 |
|---|---:|---:|
| A / 改时间 | -0.088169% 时间 | -0.101176% 时间 |
| A / 改大小 | 所查范围无样本 | 所查范围无样本 |
| B / 改时间 | -11.67% 时间 | -38.33% 时间 |
| B / 改大小 | -0.00193 pp 大小 | -0.004027 pp 大小 |

这里以实际观测的描述性中心为坐标参照，时间搜索 0.5—1.5 倍、大小搜索降低最多 0.1 pp，并检查每个已知前沿切换的两侧。它不是可实现算法、穷尽证明、压力测试或正式成功概率；更快也可能因删除邻居而获得更低份额。A 的实际时间跨度约 1.612%，远大于其近邻 15% 窗口约 0.0945%。

[全部采样点与分段](../../evidence/round18/final-coordinate-gaps-current.json)。对 B 的七处原 RF 质量收益做 128 种固定文件选择，每种固定选择应用于全部八块，而非逐块挑赢家；快照 29456 下没有任何组合/对照达到 5%。最好混合的对照变体中位约 1.8271%、最大约 2.8207%。这是零路由开销的文件级机会模型，不是可运行分类器，也不是任意新机制不可能的证明。[已有 RF 恢复机会](../../evidence/round18/final-rf-restoration-options-current.json)。

## 已完成的路线取舍

| 路线 | 直接反馈与当前取舍 | 证据 |
|---|---|---|
| DNA 早期 dense4^6、字面量、成本、浅链 | 缩表版多 16,312 B；字面量少字节却大增 token；修正为真实 2.5 bit 成本后少 9,932 B 但最终筛选仍 0；多一个前驱少 321 B，筛选仍 0。暂停这些精确版本，未永久排除 DNA。 | [D](../../evidence/round18/mechanisms-d-decision.json)、[AR](../../evidence/round18/dna-ar-decision.json)、[AV](../../evidence/round18/dna-av-decision.json) |
| DNA 前缀分区 | 保留原表容量后 split4/base6 分别少 1,637/1,622 B，base6 出现高峰后完成诊断、证明修复及八块确认；高份额不稳定。 | [AL](../../evidence/round18/dna-al-native-decision.json)、[AP](../../evidence/round18/dna-ap-decision.json) |
| RF 支配裁剪 | 实际更新减少 62.7435%，原协议两块 +0.504% / −0.153%；同进程诊断 +0.033% / +0.064%，没有建立提速，不投入新证明。 | [AE](../../evidence/round18/dominance-ae-decision.json)、[AN](../../evidence/round18/noise-an-decision.json) |
| RF 前缀复用 / span / A ring | 输出相同但总压缩时间回退：prefix +0.322% / +0.805%，span +0.890% / +1.444%，ring 约 +9.8%。操作减少和有限等价不等于收益。 | [AG/AH](../../evidence/round18/rf-ag-ah-decision.json)、[X](../../evidence/round18/screen-x-decision.json)、[AK](../../evidence/round18/aring-ak-decision.json) |
| A block8 范围最小值 | 2,400 个真实 DP 差分与 28 文件相同；原协议约慢 27%、预测 0，停止该实现。 | [AW](../../evidence/round18/block-aw-decision.json)、[AX](../../evidence/round18/block-ax-decision.json) |
| 共享匹配 / 强种子 / 模型沿用 | 弱共享损失 1,949 B，保留强种子降到 290 B 但故意重复搜索；额外匹配仅省 136 B。模型沿用也有大小回退，均未证明总时间收益。 | [AJ](../../evidence/round18/shared-aj-decision.json)、[AM](../../evidence/round18/strongseed-am-native-decision.json)、[AY](../../evidence/round18/cache-extra-ay-decision.json) |
| 旧底座组合 | #361 加 RF 质量改善 0.055739 pp，但约慢至原来的 4.1 倍；#579 去高成本阶段快约 15.6%但多 1,025 B，仍 0 份额；#573 short-range 微小变化被对照分歧覆盖。 | [AD](../../evidence/round18/screen-ad-decision.json)、[I](../../evidence/round18/alternatives-h-decision.json)、[R](../../evidence/round18/short-p-decision.json) |

本轮发现并纠正了预检解释错误：原 gain40 减 24，对实际 `pc_HLIT=80` 是 3.5 bit，并非 2.5 bit。原源码和负面回执未删除；另建减 40 的真实 2.5 bit 候选重新检查。[更正记录](../../evidence/round18/dna-cost-preflight-correction.json)。

## 替代起点与下一步

1. **优先研究低成本的真实质量改善。** B 离 5% 的当前坐标缺口已量化；恢复原有 RF 开关的免费组合仍不够。下一次实验应证明新增匹配、成本模型或共享阶段能在所需质量上保住总时间，再付完整证明成本。先做有限语料的原 encoder 字节和阶段归因；不能以少循环次数晋升。
2. **把 DNA 作为保留路线，先解决可辨识性。** 精确 radix6 包和完整证明已留存；若改键计算成本或其他质量机制，先对新点重放邻居切换，再用原协议及同源码对照判断。已有观测不支持仅移动平均速度约 0.1% 就宣布 15% 可支付。
3. **检查新公开 #591 的 SF 家族。** 本轮首次取得其源码时间是 00:13:41 UTC；实际公开释放时间未知。它与旧 #550 的基础引擎路由、候选缓存宽度/深度及编码块边界价格不同。原始来源及作者保留；精确长度条件仍是原作者代码，其私有迁移能力未验证。[来源和差分](../../evidence/round18/new-public-reference-check/receipt.json)、[有界诊断预检](../../evidence/round18/shape-bb-preflight.json)。

新公开 #591 的 BB 原生诊断已通过 28 文件原 encoder/decode。仅保留 SFbase 后多 1,336 B、公共大小轴增加 0.00628209 pp；原版观测器记录 SFshape 累计 0.853 s（嵌套阶段，不作官方提速）。随后安排单独的原协议两块测量，证据与最终 A/B 八块分列；派生端点尚无完整 gate。 [完整诊断结论](../../evidence/round18/shape-bb-decision.json)

这些是后续最高价值动作，不是已执行实现或新授权；正式上传仍需另行审阅精确文件、当时官方要求、注册归属和额度。

## 资源、可复核性与工作区

截至 2026-10-10T00:44:44.157706+00:00，派发 **55** 次手动云端运行，收齐 **54** 次；51 次成功、3 次失败。三次失败分别为首次计时环境检查、A 的证明缺口和 A 的证明超时，并非三个算法正确性反例。已完成 runner 作业累计 **27655 秒**（7.682 小时，允许并行，不能当作研究墙钟时间或账单分钟）。原协议筛选/确认共 **338** 个配对进程，另列原生、诊断及完整 gate。

账户初始用量 0%，最新已用 13%、剩余 87%；这是共享账户观察，不是本任务费用。成功兑换重置卡 **0** 次，没有购买额度；没有达到剩余≤1%的授权触发点。工具不支持指定某张卡，未试兑。实际云端账单和可归属于本任务的模型金额 **UNKNOWN**。[逐运行耗时与资源回执](../../evidence/round18/cost-preclose.json)。

原始 artifact、所有逐文件 reps、失败、官方响应均保留字节和 SHA-256。审阅 ZIP 仅含 `parse.rs` / `Parse.lean`，不含密钥、钱包、私密配置或正式上传动作。最终审计索引见 [研究状态](../../evidence/round18/research-state.md)。

官方主分支复核到 `6bf303f14e6c7bccc63e9a557e4ac83e032fa9e8`，比本轮固定 pin `a356bbff18b60c4527fbcc85d5a28ef9c20214e0` 多一个发生在本轮之前的数据库保留/发布变更。SCORING、MINER、pareto 字节与开场相同，contract、encoder、verifier 和工具链未改变；线上实际部署字节身份仍 UNKNOWN。[完整比对](../../evidence/round18/official-code-final-check/receipt.json)。官方 API 旧快照可被清理，本仓库原始捕获不依赖旧 URL 长期可用。

工作仅位于隔离分支 `codex/round18-frontier`，从 `e000933527c41b9c5881401731d863b9898f571a` 开始。main 上其他任务的 `b5cb035d44ce7da96fe3b309373203bfde369396` 被排除，没有一起推送、合并或删除。最新远端核对与收尾提交见研究状态。

**VERIFIED**：精确完整公共 gate、原始测量、哈希、公开规则重放和保存的快照。**INFERRED**：族内校准、当前单独/联合几何估算、坐标要求和机制取舍。**UNKNOWN**：正式上传后的 gate/admission、私有语料迁移、当前注册/额度、未来榜单与实际支付。八小时研究交付不能改写为两个奖励目标已完成。
