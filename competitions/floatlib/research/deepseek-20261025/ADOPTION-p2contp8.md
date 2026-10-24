# 采用包：BMM p≤8 直算路由（DeepSeek R14）

状态：FINAL（2026-10-24T21:52Z）。所有数字来自 public-v2 原版 full gate
（独立 checkout、25 轮、500k pairs），不是正式准入。

## 终选

`competitions/floatlib/candidates/f01-deepseek-p2contp8/Kernel.lean`
SHA-256 `699017452ec031efd8f0f161c944c4f45aab4c4eed8fff88f30faac533354049`，248158 B。
父本 `f01-d12-scalar-combined`（`df5c61a0…`）。

最小替代：`f01-deepseek-p2cont`（`e878b0f2…`），只改 p≤2，无 p3–8 改动。

## 改动（2 处谓词，0 新证明）

1. `bmmBeforeUnderflowZero` 的 p=2 Cross 守卫：`4≤batch*m` → `batch*m < 4`；
2. `bmmBeforeR11Cross` 的 DirectContinuous 守卫：`n ≤ 4 ∧ 2 < p` → `(n ≤ 4 ∧ 2 < p) ∨ p ≤ 8`。

两支都保留原全形状定理；public-v2 full gate 的 statement/policy/axiom/roundtrip 检查均通过。

## 证据（whole / bmm，均对同 run 的 df5c）

| seed | run | p2cont | p2contp8 | p2cont8 |
|---|---|---:|---:|---:|
| 1425002 | 40126911323 | — | — | 0.9584 / 0.8319 |
| 1425003 | 40128718577 | 0.9799 / 0.9062 | 0.9667 / 0.8384 | — |
| 1525001 | 40130503671 | — | 0.9914 / 0.9522 | 1.0074 / 1.0286 |
| 1525002 | 40131881480 | 0.9654 / 0.7877 | 0.9706 / 0.8188 | — |
| 1525003 | 40133209118 | 0.9257 / 0.7110 | 0.8912 / 0.5784 | — |
| 1525003 复跑（顺序颠倒） | 40134598315 | 0.9257 / 0.7112 | **0.8911 / 0.5788** | — |
| 1525004（阈值检查） | 40135988993 | — | 0.9736 / 0.8641 | — |

- `p2contp8`：6 次测量全部为正，whole 中位数约 0.9689（范围 0.8911—0.9914），
  bmm 中位数约 0.8268（范围 0.5784—0.9522）。
- `p2cont`：4 次测量全部为正，whole 中位数 0.9456。
- 阈值检查：同 run `p2contp16` 为 whole 0.9873 / bmm 0.8857，比 p2contp8 差约 1.4% → **锁定 p≤8**。
- 同 seed 颠倒顺序复跑几乎逐位相同（0.8912 → 0.8911），run-order 偏差可排除。
- 同 run 的 add/mul/sum 均在 1.00 附近，变化只落在 BMM。

## 完整 gate 证据（run 40134598315 的原始 gate log）

`f01-deepseek-p2contp8-gate.log` 逐阶段通过：

```
[intake] ok
[policy] ok
[statement] ok
[kernel] Submission replays cleanly
[kernel] VerifyFull replays cleanly
[axioms] ['Classical.choice', 'Quot.sound', 'propext']
[score] seed=1525003 pairs=500000 rounds=25 cpu=0
[score] suite public-v2 (156 cases)
[score] ratio 0.208 of the incumbent over all timed cases
```

verdict：`passed=true`、`stage=score`、`verifier_fingerprint == verifier_fingerprint_end`，
suite SHA `a16494e9…`。回执目录
`ci-runs/40134598315/download-*/diagnostics/f01-d7-public-suite/public-suite/`。

## 类级一致性（6 个 run，p2contp8 / df5c）

| cell | mean | min | max |
|---|---:|---:|---:|
| add:*（7 类） | 0.997–1.001 | — | — |
| mul:*（7 类） | 0.999–1.003 | — | — |
| sum:*（6 类） | 0.998–1.001 | — | — |
| bmm:dense | 0.769 | 0.522 | 1.131 |
| bmm:ml | 0.704 | 0.524 | 1.040 |
| bmm:sparse | 0.869 | 0.585 | 1.129 |
| bmm:subnormal | 0.898 | 0.611 | 1.259 |
| bmm:specials | 0.908 | 0.670 | 1.004 |
| bmm:extremes | 1.028 | 0.892 | 1.332 |

- 前 5 个 run 的 add/mul/sum 同源码控制落在 1.000±0.003，标量侧噪声 <0.3%；
- run 40135988993（seed 1525004）的 scalar 控制出现 ±3.8% 偏差（如 mul:dense 1.038），
  属该 run 的机器噪声；该 run 只用于同 run 的 p8 vs p16 阈值比较。
- bmm 优势集中在 dense/ml（5/6 个 run 改善），extremes 是唯一平均退化的类。

## 风险与边界

- specials 对 NaN 密度敏感：seed 1425002 +26.8%、1425003 −14.1%；
- extremes 在 seed 1425003 +33.2%（绝对值小：1.23→1.63 ms）；
- 单 runner、公开套件；不是冠军比较、正式 admission 或链上收益；
- 与开发侧 83a9（同 guard + n1 缓存）可能重叠；组合版本必须重新验收。

## 建议

1. 开发侧决定是否把两处谓词应用到保留候选，或把本文件作为新候选引入；
2. 组合版本重跑原版 full gate + 新 seed 计时；负结果保留；
3. 不合并本分支 `suite-plan.json`。
