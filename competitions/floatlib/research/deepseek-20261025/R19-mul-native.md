# R19：mul 去掉低尺度软件分支（发现组，2026-10-26T21:05Z）

## 候选

`f01-deepseek-multh0`，SHA `14a6ae2f9afd31cd584b5087fe24e001663d16222856515c9a4c4e10c1322ea5`。
父本 B2 `622d8394`。唯一改动：`mul` 的低尺度分派常数 `128` → `0`，
即 `if ex + ey < 0 then LowScale.mul else nativeMul` 恒走 `nativeMul`。
两支原证明不变，**0 新证明**；编译器可 DCE 掉 `expField` 提取与整个软件分支。

## 发现组（run 40397668271，seed 1826011，AMD EPYC 7763）

| 指标 | 值 |
|---|---:|
| whole/B2 | **0.9691** |
| mul/B2 | **0.9228** |
| add / sum / bmm /B2 | 1.0001 / 1.0000 / 1.0009 |
| p05（本地 bootstrap） | **+0.021156** |
| headline ≤0.97 | 是（0.96905） |

mul 各类/B2：sparse **0.812**、specials 0.900、dense 0.948、ml 0.946、paired 0.946、
extremes 0.958、subnormal 0.964。标量其它项与 bmm 是干净的 1.000 控制。

## 解释

- 当前 runner 是 AMD EPYC（Zen 3/5 系），denormal 结果没有 Intel 那种明显惩罚；
  `LowScale` 软件舍入对多数输入已是净开销。
- 常数 0 让整个 `ex+ey<128` 分支、`expField` 提取与 `LowScale` 代码被优化器删除，
  因此连 dense/ml 也快约 5%（不只是 subnormal）。
- 与 R14 的 `low-zero`（零操作数分支）不同：那次是加数据相关分支，这次是删分支。

## 边界

- 官方验证硬件 CPU 未知；若为有 denormal 惩罚的 Intel，本改动可能反向。
  确认组必须记录每次 runner CPU，并在不同 CPU 上复现。
- 单 seed 发现组；正在 seed 1826012 起做独立确认（B2 anchor + th0，2 候选）。

## 确认组 1（失败）与 CPU 依赖

run 40400995011，seed 1826012，runner **INTEL XEON PLATINUM 8573C**：

| 指标（对 B2） | 值 |
|---|---:|
| whole | 0.9940 |
| mul | 0.9854 |
| p05 | **−0.020359** |
| add / sum / bmm | 0.9939 / 1.0168 / 1.0008 |

mul 各类/B2：dense 1.034、extremes 1.060、**subnormal 1.229**；
ml 0.928、sparse 0.934、specials 0.726。

**结论**：该改动是 CPU 相关的。EPYC 上 native denormal 没有明显惩罚、且 DCE 掉整条分派，
mul −7.7%；Intel 上 subnormal 慢 23%，净收益消失且整包未过 0.97。
官方验证硬件未知，**不能把 th0 作为通用候选**；不进入确认组 2，也不组合。
保留为“CPU 敏感”负结果，确认组 1 失败原样记录。