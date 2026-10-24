# 采用包草稿：f01-deepseek-p2contp8（BMM p≤8 直算）

状态：DRAFT；等 run 5（seed 1525002）结果补齐第三/第四 seed 证据后定稿。
所有数字来自 public-v2 原版 full gate（独立 checkout，25 轮，500k pairs），不是正式准入。

## 精确对象

- 候选：`competitions/floatlib/candidates/f01-deepseek-p2contp8/Kernel.lean`
- SHA-256：`699017452ec031efd8f0f161c944c4f45aab4c4eed8fff88f30faac533354049`
- 字节：248158（≤256000）
- 父本：`f01-d12-scalar-combined`，SHA `df5c61a0ca24a8ef18c0c42d83bdd23466872d3fe8f39dd912e9c347b27fb172`

## 改动（2 处谓词，0 新证明）

1. `bmmBeforeUnderflowZero` 的 p=2 Cross 守卫：
   `p=2 ∧ 4≤batch*m ∧ ...` → `p=2 ∧ batch*m < 4 ∧ ...`
   （p=2 且 batch*m≥4 时不再走 R11CrossRows，落到后面的 DirectContinuous。）
2. `bmmBeforeR11Cross` 的 DirectContinuous 守卫：
   `n ≤ 4 ∧ 2 < p` → `(n ≤ 4 ∧ 2 < p) ∨ p ≤ 8`
   （p≤8 全部走 DirectContinuous；p>8 仍走 Packed10。）

`bmmBeforeDirectRows` 与 `bmmBeforeR11Cross_spec` 的证明均未改：两支都有全形状定理。

## 证据

| seed | run | whole/df5c | bmm/df5c | 备注 |
|---|---|---:|---:|---|
| 1425002 | 40126911323 | — | — | 该 run 用 p2cont8（p3–8→DirectSmall），0.9584/0.8319 |
| 1425003 | 40128718577 | **0.9667** | **0.8384** | p2contp8，3 full gate 全 PASS |
| 1525001 | 40130503671 | **0.9914** | **0.9522** | p2contp8，3 full gate 全 PASS |
| 1525002 | 待 run 5 | 待补 | 待补 | p2contp8 + p2cont 对照 |

同 run 其它类（add/mul/sum）均在 1.001 附近，说明变化只落在 BMM。

## 风险与未闭合

- specials：NaN 密度敏感，seed 1425002 +26.8%、1425003 −14.1%；
- extremes：seed 1425003 +33.2%（绝对值小，1.23→1.63 ms）；
- p3–8→DirectSmall 不稳定，故最终候选用 DirectContinuous；
- 单侧 public runner 结果，不是正式 admission；如需组合，开发侧须在保留版本上重跑完整 gate。

## 建议

1. 由开发侧决定是否把上述两处谓词应用到保留候选（或把 248158B 文件作为新候选引入）；
2. 组合版本必须重新跑原版 full gate + 新 seed 计时；
3. 不合并本分支的 `suite-plan.json`，按精确 SHA 与各自 plan 引用。
