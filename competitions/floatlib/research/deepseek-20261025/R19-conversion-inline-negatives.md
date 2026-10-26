# R19：转换与内联负结果（2026-10-26T21:56Z）

## 1. `Float32.ofBits` 替代表解码（add/nativeMul）

候选 `f01-deepseek-bits-addmul`（79022b4a），statement PASS（证明改写在 CI 通过）。
run [40405652739](https://github.com/HuanHuanHuanFFF/Miner/actions/runs/40405652739)，seed 1826015，
runner EPYC 9V45，2 个 full gate PASS：

| 比值（对 B2） | 值 |
|---|---:|
| add | **1.1599** |
| mul | **1.1350** |
| sum | 1.0833 |
| bmm | 1.0006 |
| whole | **1.1215** |

- 结论：`R2W01b.convert`（fastOK 表解码）明显快于 `Float32.ofBits`；后者在热路径上是更贵的接口。
  表解码保留，不再尝试 bitcast 替代。
- sum 的 +8.3% 与 add 相关（sum 的软件路径会调用 `Submission.add`），方向一致。

## 2. `NativeFinal.dot` / `R14ThinBCache.dot` 内联

候选 `f01-deepseek-inline-dot`（c4f184d3），attribute-only。
run [40403277972](https://github.com/HuanHuanHuanFFF/Miner/actions/runs/40403277972)，seed 1826013，
runner Xeon 8573C：

| 比值（对 B2） | 值 |
|---|---:|
| bmm | 0.9947 |
| add | 1.1161 |
| mul | 1.0121 |
| sum | 0.9495 |
| whole | 1.0409（p05 −0.032） |

- bmm 无收益；未改动的 add 出现 +11.6%、sum −5.1%，说明该 runner 的单 run 标量噪声可达 ±10%。
- 结论：不内联，不进入确认。

## 测量教训

2 候选、单 run 的标量差异在 Xeon runner 上可漂移 ±10%（同源代码）。以后小效应必须靠：
同一 run 的多候选中重复对照，或 ≥3 seed 的确认组；单 run 的 1—2% 不作为结论。
