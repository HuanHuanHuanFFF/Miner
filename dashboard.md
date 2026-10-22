# FloatLib 冲冠看板

冠军 [#274](https://conjectures.io/v1/competitions/floatlib/submissions/274)｜2026-10-23 06:32核对。**我方/冠军耗时越低越好；公开原版/我方加速越高越好。**

当前保留[直接点积＋非NaN完整包](competitions/floatlib/candidates/f01-d7-direct-nonnan/Kernel.lean)，两轮新版公开套件完整通过。

| 运算 | 冠军耗时基准 | 我方 / 冠军耗时 | 我方对公开原版加速 | 我方耗时占比 |
| --- | ---: | ---: | ---: | ---: |
| 加法 add | 1.00× | 待正式评测 | 2.57–2.81× | 25.2% |
| 乘法 mul | 1.00× | 待正式评测 | 1.41–1.49× | 26.3% |
| 求和 sum | 1.00× | 待正式评测 | 4.49–4.56× | 14.1% |
| 矩阵乘法 bmm | 1.00× | 待正式评测 | 3.43–3.54× | 34.3% |

整包我方 **2.84–2.94×**；冠军官方累计 **6.38×** 含跨套件历史，不能相除算差距。[数据](competitions/floatlib/candidates/f01-d7-research/multiplier-comparison.json)

**结论：尚无取代#274的已验方案；组合包相对上一保留版本再降耗9%–14%，继续冲冠。**
