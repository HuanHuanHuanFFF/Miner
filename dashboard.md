# FloatLib 冲冠看板

冠军核对：[2026-10-27 12:42 北京时间](competitions/floatlib/candidates/f01-d7-research/official-20261027T044250Z/receipts.json)｜各项均以现任完整包冠军为 1.00×，耗时越低越好。

| 运算 | 现任冠军 | 我方首选 | 我方／冠军耗时（预估） | 验证 |
| --- | --- | --- | ---: | --- |
| 加法 add | [#323](https://conjectures.io/v1/competitions/floatlib/submissions/323) | [原生加法＋特殊值选择](competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean) | **约 1.03×** | 完整通过16次 |
| 乘法 mul | #323 | [数值转换＋特殊值选择](competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean) | **约 1.16×** | 完整通过16次 |
| 求和 sum | #323 | [单遍求和＋快速修复](competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean) | **约 1.17×** | 完整通过16次 |
| 矩阵乘法 bmm | #323 | [双列复用＋B2成对存储](competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean) | **约 3.00×** | 完整通过16次；[新循环证明通过，整包待测](competitions/floatlib/candidates/f01-d7-research/round45m-20261027T074758Z/development-round-result.json) |

整包预估耗时：冠军的 **约 1.25×**。

**结论：预估暂不能取代#323；主要差距在矩阵乘法（约3.00倍耗时）。** [计算依据](competitions/floatlib/candidates/f01-d7-research/champion-time-estimate.json)
