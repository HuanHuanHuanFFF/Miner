# DEFLATE 提交看板

最近查询：北京时间 **2026-10-13 00:18:27**。官方快照 **29973**，计算时间 **2026-10-13 00:13:20**；官方 freshness=`stale`。

汇总本项目已核验的正式提交；研究中的未提交候选见[任务索引](docs/TASK_INDEX.md)。执行与更新规则见 [AGENTS.md](AGENTS.md#提交看板维护)。

- **初始份额**：目前归档可核验的早期正式评分记录，固定保留原快照；不保证恰为服务端首次评分。提交瞬间、排队状态与公共预测不作为初始成绩。
- **当前份额**：本次同一官方快照的竞赛奖励池可支付份额 `payable_weight × 100%`。
- **累计 α**：官方按该提交记录的 `bounty_earned_alpha`，截至该快照；不同于本看板核验的钱包到账。钱包当前到账状态为 UNKNOWN。
- **VERIFIED** 表示已核对官方原始响应及本地源码；缺失字段保留 UNKNOWN，不补零。

| 正式提交 | 轮次／候选 | 提交时间（北京） | 初始份额／快照 | 当前份额 | 累计 α | 当前状态 |
|---|---|---|---:|---:|---:|---|
| [#427](https://conjectures.io/competitions/deflate/submissions/427) | R2 · [probe3](candidates/probe3) | 2026-10-06 21:43:46 | [0.000000% · 23753](evidence/round3/pareto-pages.json) | 0.000000% | 0.000000 | gate 通过；准入未通过 |
| [#453](https://conjectures.io/competitions/deflate/submissions/453) | R3 · [r3-432-fast3](candidates/r3-432-fast3) | 2026-10-07 13:32:46 | [0.503550% · 25678](evidence/round5/frontier-25678/submission-453.json) | 0.000000% | 1.719629 | 准入通过；已退出前沿 |
| [#474](https://conjectures.io/competitions/deflate/submissions/474) | R5–6 · [r5-h16-small-proofopt](candidates/r5-h16-small-proofopt) | 2026-10-07 19:33:54 | [0.000000% · 26566](evidence/round6/formal-474/official-result.json) | 0.000000% | 0.000000 | gate 通过；准入未通过 |
| [#573](https://conjectures.io/competitions/deflate/submissions/573) | R15 · [r15-550-base-only](candidates/r15-550-base-only) | 2026-10-09 20:37:41 | [1.736517% · 29346](evidence/round16/formal-573-start.json) | 0.000000% | 4.379391 | 准入通过；已退出前沿 |
| [#582](https://conjectures.io/competitions/deflate/submissions/582) | R17 · [r17-dna-nofold-proof1](candidates/r17-dna-nofold-proof1) | 2026-10-10 00:29:09 | [0.000000% · 29394](evidence/round17/formal-582/result-summary.json) | 0.000000% | 0.000000 | gate 通过；准入未通过 |
| [#603](https://conjectures.io/competitions/deflate/submissions/603) | R18 A · [r18-rf-sf-content-proof1](candidates/r18-rf-sf-content-proof1) | 2026-10-10 14:05:41 | [5.712702% · 29505](evidence/round18/formal-a/result-summary.json) | 0.000000% | 5.012090 | 准入通过；已退出前沿 |
| [#625](https://conjectures.io/competitions/deflate/submissions/625) | R24 B · [r24-609-fast-adaptive-proof1](candidates/r24-609-fast-adaptive-proof1) | 2026-10-11 14:43:26 | [0.383037% · 29668](evidence/dashboard/20261011T071532846821Z/625.response.json) | 0.000000% | 0.722519 | 准入通过；已退出前沿 |

已知累计奖励合计：**11.833629 α**（7/7 条具有官方数值；VERIFIED API 记录，非钱包余额或净利润）。

[本次完整数据](evidence/dashboard/20261012T161750465331Z/summary.json) · [原始响应 SHA-256 与查询时间](evidence/dashboard/20261012T161750465331Z/receipts.json) · [提交登记表](docs/submissions.json)


## 扣除注册费用后的累计收益

- 已核实注册成本：**0.024254898 TAO**，包括对应提交的注册扣款及成功／失败交易手续费；同一交易只计一次。
- 注册成本按当前价格折算：**8.270504 α**。
- 扣除注册成本的累计净收益估算：**3.563125 α**（INFERRED_SPOT_MARK_TO_MARKET；约 0.010450 TAO）。
- 兑换口径：SN66 池储备 `subnetTAO / subnetAlphaIn`，1 α ≈ 0.002932699 TAO；finalized 区块 **9268271**，查询北京时间 **2026-10-13 00:18:25**。

范围：本看板 7 笔已提交记录的注册成本，含 2 次失败注册手续费；未使用注册额度、模型／CI成本不计入本项。净收益采用当前价格估值，不代表已经卖出或钱包已到账，未计兑换滑点及提现费用。未来新增提交若缺少成本记录，净收益显示 UNKNOWN。
[注册成本登记与交易证据](docs/registration-costs.json) · [折算储备与原始回执](evidence/dashboard/20261012T161750465331Z/summary.json)

初始记录计算时间（北京）：

- #427：2026-10-06 23:15:37。
- #453：2026-10-07 14:10:41。
- #474：2026-10-07 21:32:25。
- #573：2026-10-09 20:53:28。
- #582：2026-10-10 00:37:57。
- #603：2026-10-10 14:20:47。
- #625：2026-10-11 15:05:48。

研究方法与机制结论见 [DEFLATE 优化方法与实验结论](docs/research/optimization-methods.md)。
