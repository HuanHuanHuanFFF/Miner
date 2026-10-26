# R19 分析：BMM 的小 n 形状占比（2026-10-26T23:25Z）

对 B2 在四个 public-v2 seed 上的 bmm 逐 case 估算：用类级 `submission_ns × work`，
统计 `n ≤ 4` 的 case 占 bmm 时间的比例。类级 ns/work 会高估/低估个别 case，仅作量级判断。

| run | seed | bmm 总估时 | n≤4 估时 | 占比 |
|---|---:|---:|---:|---:|
| 40390827505 | 1826008 | 12.38ms | 1.31ms | 10.6% |
| 40395050251 | 1826010 | 23.52ms | 8.64ms | 36.7% |
| 40397668271 | 1826011 | 30.30ms | 10.70ms | 35.3% |
| 40416378615 | 1826018 | 25.13ms | 3.27ms | 13.0% |

- 小 n（1—4）形状在不同 seed 间占 bmm 的 11%—37%，是 BMM 计分成本的重要组成。
- 但这些形状的单输出成本由 writer/索引/分发开销主导；R18 的 d70（n=0…4 展开）已测为
  bmm 慢约 0.7%，本次不再重复同机制。
- 结合本轮闭包/内联/索引证据：per-output 的 `lean_nat_add`、`Array.push`、`dot` 调用都很难再压；
  若下一轮要做，应把 writer 改成 USize 索引 + 预分配直写（与 D 的 USize 诊断同向，不重复造）。
- p=1 且 n 很大（如 specials:4 n=252）不属于小 n 开销，不计入此结论。

证据目录：`ci-runs/<run>/.../public-suite` 的 `public-drawn-plan.json` 与 B2 verdict。
