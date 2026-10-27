# R19：逐行闭包消除负结果（2026-10-26T20:45Z）

run [40395050251](https://github.com/HuanHuanHuanFFF/Miner/actions/runs/40395050251)，public-v2 seed 1826010，
B2 anchor + 三个一阶循环候选，4 个 full gate 全 PASS。

| 候选 | 改动 | bmm/B2 | add/B2 | mul/B2 | sum/B2 |
|---|---|---:|---:|---:|---:|
| `loopb2row` | pair 行改 `rowLoop` | 0.9976 | 1.0212 | 1.0039 | 1.0128 |
| `loopdc1` | DirectContinuous 改 `emitLoop` | 1.0012 | 1.0114 | 1.0124 | 1.0259 |
| `loopboth1` | 两者组合 | 0.9832 | 0.9901 | 0.9833 | 1.0003 |

- 同 run 的 add/mul/sum 出现 ±2% 漂移；三个 bmm 差异（−1.7%—+0.1%）都在该噪声内。
- C 证据已确认改动生效：`rowLoop` / `emitLoop` 的生成 C 内无 `lean_alloc_closure`；
  但性能无可测收益 → **逐行闭包分配不是 B2 BMM 的瓶颈**。
- 内层仍有每输出 `lean_nat_add`（baseB+j、j+1）与 `lean_array_push`，以及每次 `NativeFinal.dot` 调用；
  后续若继续 BMM，应针对这些，而不是闭包。
- 结论：该路线停止，不进入确认；三个候选保留为负结果。

回执：`ci-runs/40395050251/`、`ci-runs/40394386767/`（编译与 C）。

> 口径说明（2026-10-26T23:32Z 更正）：本文中若标注 raw 的 op 比值仅作诊断；采用口径为归一化 (sub/inc)_cand ÷ (sub/inc)_B2。归一化值见 R19-SUMMARY.md 的更正表与 messages/20261026T233200000Z-r19-normalized-correction.md。
