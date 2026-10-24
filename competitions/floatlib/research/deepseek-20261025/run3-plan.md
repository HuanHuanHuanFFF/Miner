# Run 3 计划：p≤2 直算的隔离与确认（新 seed）

## Run 2 结论（public-v2 seed 1425002，4 个 full gate 全 PASS）

| 候选 | 路由 | whole/df5c | bmm/df5c |
|---|---|---|---|
| `f01-deepseek-p2cont8` | p≤2 → DirectContinuous；p≤8 → DirectSmall | **0.9584** | **0.8319** |
| `f01-deepseek-directall` | p≤64 全部 DirectContinuous | 0.9585 | 0.8346 |
| `f01-deepseek-p8-direct` | 仅 p3–8 → DirectSmall | 1.0070 | 1.0329 |
| df5c anchor | Cross p=2 / DirectSmall / Packed10 | 1.0000 | 1.0000 |

归因：
- `p8-direct` 的 dense 0.9625，但 ml 1.066、sparse 1.063、specials 1.222 → p3–8 改 DirectSmall 单独并不好。
- `p2cont8` 的 dense 0.707、ml 0.838、sparse 0.888、subnormal 0.785、extremes 0.924；
  与 p8-direct 的唯一差别是 **p≤2（含 p=1）改走 DirectContinuous**，因此增益主要来自这里。
- specials 1.268 退化：NaN-heavy 的 p2 行直接重放成本更高；净 bmm 仍 −16.8%。
- directall ≈ p2cont8（bmm 1.0033）→ p>8 的 direct 与 Packed10 在本 seed 基本等价。

## Run 3

- seed `1425003`（新），嵌套 `f01-d7-public-suite` 入口，4 候选：
  1. df5c anchor
  2. `f01-deepseek-p2cont`（只改 p≤2 → DirectContinuous，Cross 旁路；不含 p8 改动）e878b0f2
  3. `f01-deepseek-p2contp8`（p≤8 全部 DirectContinuous）69901745
  4. `f01-deepseek-directall`（p≤64 全部 DirectContinuous）ad91388b
- 目的：在新 seed 上确认 p≤2 直算收益，并区分 p3–8 走 DirectSmall（run 2 的 p2cont8）与 DirectContinuous；
  同时检查 directall 是否稳定。
- 预计 18—22 分钟；单 seed 仍只作发现组。

## 判定

- `p2cont` 若与 `p2cont8` 持平，说明可去掉 p8 改动，候选最小化。
- `p2contp8` 若更好，说明 p3–8 也应直算；`directall` 若继续持平，则 Packed10 在当前套件没有净收益。
- 任何结论需新 seed 或新 runner 复核；specials 退化单独记录。
