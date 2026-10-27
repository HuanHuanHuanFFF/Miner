# R19：B2 按 p 带收窄负结果（2026-10-27T00:16Z）

run [40422242456](https://github.com/HuanHuanHuanFFF/Miner/actions/runs/40422242456)，seed 1826020，
runner AMD EPYC 7763，B2 anchor + 三个 predicate-only 变体，4 full gate 全 PASS（归一化口径）：

| 候选 | p 下界 | bmm/B2 | whole/B2 |
|---|---|---:|---:|
| `b2-p3` | p≥3 | 1.0422 | 1.0070 |
| `b2-p4` | p≥4 | 1.0411 | 1.0067 |
| `b2-p6` | p≥6 | 1.0559 | 1.0095 |

- 控制项 add/mul/sum 均 ~1.000，差异真实：收窄到 p≥3/4/6 都让 BMM 慢 4—5.6%。
- 结论：B2 的 pair core 对 p=2、3 也是净收益（packB 在 m 行上摊销），**保持 p≥2 原条件**。
- 与 m 放宽（m≥2 负）合看：B2 的覆盖边界是“p≥2 且 m≥4 且 n>1”，两个方向都不能扩也不能收。
- 三个变体源码保留为负结果，不进入确认。
