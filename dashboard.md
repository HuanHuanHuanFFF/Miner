# FloatLib 冲冠看板

冠军核对：[2026-10-25 20:12 北京时间](competitions/floatlib/candidates/f01-d7-research/official-20261025T121232Z/receipts.json)｜各项均以现任完整包冠军为 1.00×，耗时越低越好。

| 运算 | 现任冠军 | 我方首选 | 我方／冠军耗时（预估） | 验证 |
| --- | --- | --- | ---: | --- |
| 加法 add | [#309](https://conjectures.io/v1/competitions/floatlib/submissions/309) | [原生加法＋特殊值选择](competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean) | **约 1.03×** | 完整通过7次 |
| 乘法 mul | #309 | [数值转换＋特殊值选择](competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean) | **约 1.11×** | 完整通过7次 |
| 求和 sum | #309 | [单遍求和＋快速修复](competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean) | **约 1.18×** | 完整通过7次 |
| 矩阵乘法 bmm | #309 | [双列复用＋B2成对存储](competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean) | **约 2.45×** | 完整通过7次 |

整包预估耗时：冠军的 **约 1.21×**。

**结论：预估暂不能取代#309；主要差距在矩阵乘法（约2.45倍耗时）。** [计算依据](competitions/floatlib/candidates/f01-d7-research/champion-time-estimate.json)
