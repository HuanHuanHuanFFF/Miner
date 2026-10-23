# FloatLib 冲冠看板

冠军 [#285](https://conjectures.io/v1/competitions/floatlib/submissions/285)｜官方倍率 **8.12×（scoring-v2-2026-10）**｜2026-10-23 19:58核对。

当前保留[单遍求和＋矩阵优化＋结果守卫组合](competitions/floatlib/candidates/f01-r8-combined-result-guard/Kernel.lean)，整包对公开原版 **4.15–4.55×**。

| 运算 | 冠军耗时基准 | 我方 / 冠军耗时 | 我方对公开原版加速 | 我方耗时占比 |
| --- | ---: | ---: | ---: | ---: |
| 加法 add | 1.00× | 待正式评测 | 3.46–3.80× | 30.5% |
| 乘法 mul | 1.00× | 待正式评测 | 1.71–1.89× | 33.6% |
| 求和 sum | 1.00× | 待正式评测 | 8.77–18.68× | 7.0% |
| 矩阵乘法 bmm | 1.00× | 待正式评测 | 6.08–6.26× | 28.8% |

**结论：尚无取代#285的已验方案；新版本相对上一保留版再降耗7.7%–12.4%。** [数据](competitions/floatlib/candidates/f01-d7-research/multiplier-comparison.json)
