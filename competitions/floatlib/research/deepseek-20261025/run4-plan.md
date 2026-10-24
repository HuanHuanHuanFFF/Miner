# Run 4 计划：p≤8 直算的新 seed 确认

## Run 3 结果（public-v2 seed 1425003，3 个 full gate 全 PASS）

| 候选 | whole/df5c | bmm/df5c | dense | ml | sparse | specials | extremes |
|---|---:|---:|---:|---:|---:|---:|---:|
| `p2contp8`（p≤8 全 DirectContinuous） | **0.9667** | **0.8384** | 0.974 | 0.619 | 0.935 | 0.859 | 1.332 |
| `p2cont`（只改 p≤2） | 0.9799 | 0.9062 | — | — | — | — | — |
| `directall`（p≤64 全直算） | 0.9881 | 0.9494 | — | — | — | — | — |

- p3–8 走 DirectContinuous（p2contp8）比走 Packed10（p2cont）明显更好；p>8 走 DirectContinuous（directall）反而变差
  → **p≤8 直算 + p>8 Packed10** 是本 seed 的最优组合。
- run 2（seed 1425002）里 `p2cont8`（p3–8→DirectSmall）bmm 0.8319，与 directall 0.8346 持平；
  两 seed 合并看：p3–8 直算 ≥ DirectSmall，p>8 保留 Packed10。
- specials 在 run 2 退化、run 3 改善，说明该类对 NaN 密度敏感，方向不稳定，单列记录。

## Run 4

- seed `1525001`（DeepSeek 新 seed 段），嵌套 `f01-d7-public-suite`，3 候选：
  1. df5c anchor
  2. `p2contp8`（当前最优）69901745
  3. `p2cont8`（p3–8→DirectSmall 对照）169f8198
- 目的：新 seed 确认 p≤8 直算收益；区分 p3–8 的两种直算实现；为最终建议提供第二个独立 draw。
- 预计 18—20 分钟；`sample_role=CONFIRMATION`，但仍属公开 runner 的发现/确认，不是正式准入。

## 判定

- `p2contp8` 若再次 whole < 0.98、bmm < 0.90，则建议采用该最小改动。
- `p2cont8` 与 `p2contp8` 的差即 p3–8 实现差异；若一致，选改行更少者。
- 结论仍需与开发侧候选组合时重核精确版本；不合并 suite-plan。
