# R19：B2 分派放宽负结果（2026-10-26T20:12Z）

run [40390827505](https://github.com/HuanHuanHuanFFF/Miner/actions/runs/40390827505)，public-v2 seed 1826008，
B2 anchor + 三个 predicate-only 变体，4 个 full gate 全 PASS。

| 候选 | 分派条件 | bmm/B2 | add/B2 | mul/B2 | sum/B2 |
|---|---|---:|---:|---:|---:|
| `b2-m2` | `m≥2` | **1.1523** | 1.0120 | 1.0133 | 0.9820 |
| `b2-m1` | `m≥1` | **1.1855** | 0.9770 | 0.9699 | 0.9461 |
| `b2-all` | `m≥1 ∧ n≥1` | **1.1814** | 0.9833 | 0.9679 | 0.9351 |

- 放宽后 BMM 明确变慢 15—19%，不是噪声；标量侧出现 −5%—+1% 的漂移（b2-m1/all 的 run 噪声较大）。
- 解释：B2 的 `packB` 按 `batch × groups` 准备，收益依赖每 batch 的行数 m；m=2/3 时摊销不足，
  而 DirectContinuous 更轻。**保留 B2 的 `m≥4` 条件**，不再扩大。
- 该 seed 的 B2 anchor bmm 仅 12.38ms（占整包 95ms 的 13%），与 adoption seed 的 32.4ms 不同，
  再次说明 seed 间形状差异大。

回执：`ci-runs/40390827505/`；三种变体源码仅改 dispatch 谓词，保留为负结果。

> 口径说明（2026-10-26T23:32Z 更正）：本文中若标注 raw 的 op 比值仅作诊断；采用口径为归一化 (sub/inc)_cand ÷ (sub/inc)_B2。归一化值见 R19-SUMMARY.md 的更正表与 messages/20261026T233200000Z-r19-normalized-correction.md。
