# FloatLib 冲冠看板

冠军核对：[2026-10-25 03:10 北京时间](competitions/floatlib/candidates/f01-d7-research/official-20261024T191026Z/receipts.json)｜各项均以现任完整包冠军为 1.00×，耗时越低越好。

| 运算 | 现任冠军 | 我方首选 | 我方／冠军耗时（预估） | 验证 |
| --- | --- | --- | ---: | --- |
| 加法 add | [#309](https://conjectures.io/v1/competitions/floatlib/submissions/309) | [原生加法＋特殊值选择](competitions/floatlib/candidates/f01-d12-scalar-combined/Kernel.lean) | **约 1.03×** | 完整通过10次 |
| 乘法 mul | #309 | [数值转换＋特殊值选择](competitions/floatlib/candidates/f01-d12-scalar-combined/Kernel.lean) | **约 1.15×** | 完整通过10次 |
| 求和 sum | #309 | [单遍求和＋快速修复](competitions/floatlib/candidates/f01-d12-scalar-combined/Kernel.lean) | **约 1.16×** | 完整通过10次 |
| 矩阵乘法 bmm | #309 | [跨行计算＋快速回放](competitions/floatlib/candidates/f01-d12-scalar-combined/Kernel.lean) | **约 2.73×** | 完整通过10次 |

整包预估耗时：冠军的 **约 1.25×**。

**结论：预估暂不能取代#309；主要差距在矩阵乘法（约2.73倍耗时）。** [计算依据](competitions/floatlib/candidates/f01-d7-research/champion-time-estimate.json)
