# Round 10 同 hotkey 前沿支付条件

snapshot **27460**（评分时间北京时间 2026-10-08 04:57:46.588，Pareto 492 点）中，#453 仍在前沿，`payable_weight=0.0034836620532421396`，也就是竞争 Pareto 池的 **0.348366%**。起始 snapshot **27331** 中 #453 的坐标和份额相同。两份公开分页的 capture 与 SHA 清单见 [official-mid-payability/receipt.json](official-mid-payability/receipt.json) 和 [official-start/receipt.json](official-start/receipt.json)。两份 API 都标 `freshness=unknown`。

本次复核了公开的 [SCORING.md](../../sources/conjectures-optimisation-deflate/docs/SCORING.md) 和 [combine.py `score`](../../sources/conjectures-optimisation-deflate/validator/scoring/combine.py)。规则顺序是：先给获准前沿点计算几何权重，再按 hotkey 从前沿点中选 `(submitted_at, submission_id)` 最早的一点；同 hotkey 后续前沿点的 Pareto `payable_weight` 为 0。当前 snapshot 的 `improvement_share=0`，所以重复点没有 improvement 权重补回；未付份额不会在其余矿工间重新分配。`frontier.py:score_frontier` 负责几何前沿权重，`combine.py:score` 负责身份支付筛选。

[round10_payability.py](../../scripts/round10_payability.py) 提供纯函数 `analyze_payability(rows, time_ratio, compressed_pct, reference_submission_id, scorer, ...)`。它用传入的官方 Pareto scorer，把假设点加入当前官方前沿，返回几何份额、仍留在更新前沿的较早同 hotkey ID，以及“当前 hotkey 新增份额”和“独立合格 hotkey 条件份额”。命令 `python scripts/round10_payability.py` 会重放以下示例并写入 [payability-start.json](payability-start.json)。当前 74 个前沿权重用本地官方 Pareto 源码复算，最大绝对误差为 `6.94e-18`。

| 情景 | 更新后几何份额 | #453 是否仍在前沿 | 较早同 hotkey 前沿 ID | 同 hotkey 新增份额（条件值） | 独立合格 hotkey 份额（条件值） |
|---|---:|---|---|---:|---:|
| 假设点 `1.25 / 34.18%` | 2.599213% | 是 | #453 | 0% | 2.599213% |
| 合成点 `0.436873 / 36.998729%`，严格支配 #453 | 0.619161% | 否 | 无 | 0.619161% | 0.619161% |

第一种情景里，#453 在合并后的前沿继续作为这个 hotkey 的最早点；新点即使获得 2.599213% 的几何权重，也不会给当前 hotkey 增加 Pareto payable weight。更新后的 #453 几何份额约为 0.345522%。第二种纯合成情景支配并移除 #453，因此当前 hotkey 没有更早的前沿点；若候选通过准入、该 hotkey 保持注册且未触发 bounty cap，候选才可条件性获得 0.619161%。它不是实际候选成绩。

表中份额是竞争 Pareto 池内的份额，不是已支付 emissions。`weights/current` 返回 snapshot **27461**，与本次 Pareto snapshot 27460 不同；receipt 已标 `weights_same_snapshot=false`，不能据此确认 27460 对应的链上权重是否接受。snapshot 27460 中 #453 的记录标出 `payment_eligible=true`、`bounty_capped=false`，这只是该次公开评分记录；未来候选的 admission、注册、(hotkey, submission) bounty 和链上接受状态仍为 **UNKNOWN**。新候选是否具有合法身份属于后续授权范围，本审查不推断身份、不访问钱包或链私密信息，也不建议通过更换身份绕过规则。
