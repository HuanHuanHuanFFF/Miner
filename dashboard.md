# FloatLib 冲冠看板

冠军 [#269](https://conjectures.io/v1/competitions/floatlib/submissions/269)｜[2026-10-23 02:26 北京时间核对](competitions/floatlib/candidates/f01-d7-research/current-official-snapshot.json)。官方耗时口径：**我方耗时 ÷ 冠军耗时，越低越好**。

当前采用[完整包](competitions/floatlib/candidates/f01-d5-stream-pack/Kernel.lean)，下表加速倍数为新版公开套件两轮完整实测，**公开原版耗时 ÷ 我方耗时，越高越好**。

| 运算 | 冠军耗时基准 | 我方 / 冠军耗时 | 我方对公开原版加速 | 我方耗时占比 |
| --- | ---: | ---: | ---: | ---: |
| 加法 add | 1.00× | 待正式评测 | 2.46–3.39× | 18.7% |
| 乘法 mul | 1.00× | 待正式评测 | 1.43–1.63× | 20.7% |
| 求和 sum | 1.00× | 待正式评测 | 3.95–4.10× | 10.9% |
| 矩阵乘法 bmm | 1.00× | 待正式评测 | 1.90–2.15× | **49.6%** |

整包：我方 **2.14–2.47×**；官方累计冠军 **579.26×** 包含跨套件历史链，不能与新版相除计算差距。[数据与基准](competitions/floatlib/candidates/f01-d6-research/multiplier-comparison.json)

**结论：尚无取代#269的已验方案；十小时协作进行中，先验矩阵宽度与特殊值回退。**
