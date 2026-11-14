# Pro研究技术提炼与本地原件索引

六份Pro技术报告已先下载到E盘并在本地逐字节核对，共105617B。原始报告及带私人会话URL的receipt只保留E盘和本地pro-results，不自动公开；公开记录为本页技术提炼、public-pro-receipts.json及相应自写代码/公开一手出处。本文不包含私人对话原文或会话链接，不能作为Lean、计时或准入证据。

| 原技术报告摘要 | 字节/SHA前缀 | 影响的研究决定 |
|---|---|---|
| 独立链/配对审查 | 41235 /30a03fd6 | 严格signed62与有限K界支持整数分组；操作节点数不当cycles。 |
| Rational/指数证书审查 | 35083 /35b8b904 | 完整合法反例显示shift overflow guard和舍入前normal条件不能省；不反驳带guard的声明。 |
| 宽域exact128/截断dot | 8130 /3e4207ba | general128原S−c必须只补一次，实际base可能含tinybias；后来只读确认packed QY6G另为标准补码c0，不能混用。 |
| quotient/interval statistics | 6769 /91cb357a | 有效输入能使粗统计证书拒绝；不把反例数写成生产miss率。既有wordRNE/wordNewton不能误判成GMP成本。 |
| strict midpoint64 checker | 7825 /8976c8cd | 精确midpoint固定点+单调RNE支持strict反推，无需outward rounding或cast准确性；minnormal低侧特殊。H+2L≥406只排除当前半径的normal接受，不排除整个路线。 |
| actualNative32 cell/scale接口 | 6575 /5b2b2464 | 任意ghost Nat宽度可接actual roundRatScaled；power前一binade与minnormal subnormal分支分开。Scale pair不字面组合，运输商RNE结果。报告范围e≤253，e254由本方另查，不扩大外部结论。 |

本方已将关键结论写成actual word/nativeFloat/model helper并做单次关键审查；是否经过Lean/replay/allowedAX只看精确源的实际CI。新Native64/word2等未通过的完整源仍NOT_RUN；有限模型不补全证明。

新的真实参照profile改变了投入：主要dot层约66–100%，norm在nmlp6.2%、mixer26.1%（仅normal/b1单机，含hash/touch）；见ALLOCATION-AFTER-ACTUAL-PROFILE.md。后续优先完整成本和已存在断点，不按论文描述数量判断进展。

固定一手入口：[FloatLib0d918](https://github.com/lean-dojo/FloatLib/tree/0d91825727839f597fd06b22fdd038ea21480f0c)、[实际Native32rounder](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/ExecFloat/Backends/Word/Narrow/Base/Runtime.lean)、[Native/Model](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/IEEE754/Native/Model.lean)。对应原字节/固定Gitblob回执保留在research源码记录。

资源历史：初期网页请求未纳入同一执行者统计，精确历史重叠UNKNOWN；发现后已更正，并在每个新阶段按D2+R3或D2+R2+Pro1调度，不嵌套。UI显示Pro第五档，后端版本/真实usage UNKNOWN。六项现均完成，web在途0；未产生zip。
