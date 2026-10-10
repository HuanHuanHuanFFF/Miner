# DEFLATE 提交看板

最近查询：北京时间 **2026-10-10 19:07:17**。官方快照 **29533**，计算时间 **2026-10-10 19:00:54**；官方 freshness=`unknown`。

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
| [#573](https://conjectures.io/competitions/deflate/submissions/573) | R15 · [r15-550-base-only](candidates/r15-550-base-only) | 2026-10-09 20:37:41 | [1.736517% · 29346](evidence/round16/formal-573-start.json) | 0.230132% | 2.546447 | 准入通过；在前沿 |
| [#582](https://conjectures.io/competitions/deflate/submissions/582) | R17 · [r17-dna-nofold-proof1](candidates/r17-dna-nofold-proof1) | 2026-10-10 00:29:09 | [0.000000% · 29394](evidence/round17/formal-582/result-summary.json) | 0.000000% | 0.000000 | gate 通过；准入未通过 |
| [#603](https://conjectures.io/competitions/deflate/submissions/603) | R18 A · [r18-rf-sf-content-proof1](candidates/r18-rf-sf-content-proof1) | 2026-10-10 14:05:41 | [5.712702% · 29505](evidence/round18/formal-a/result-summary.json) | 5.781256% | 3.328310 | 准入通过；在前沿 |

已知累计奖励合计：**7.594385 α**（6/6 条具有官方数值；VERIFIED API 记录，非钱包余额或净利润）。

[本次完整数据](evidence/dashboard/20261010T110709258232Z/summary.json) · [原始响应 SHA-256 与查询时间](evidence/dashboard/20261010T110709258232Z/receipts.json) · [提交登记表](docs/submissions.json)

初始记录计算时间（北京）：

- #427：2026-10-06 23:15:37。
- #453：2026-10-07 14:10:41。
- #474：2026-10-07 21:32:25。
- #573：2026-10-09 20:53:28。
- #582：2026-10-10 00:37:57。
- #603：2026-10-10 14:20:47。

研究方法与机制结论见 [DEFLATE 优化方法与实验结论](docs/research/optimization-methods.md)。
