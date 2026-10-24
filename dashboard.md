# FloatLib 冲冠看板

冠军核对：[2026-10-24 21:05 北京时间](competitions/floatlib/candidates/f01-d7-research/official-20261024T130512Z/receipts.json)｜各项均以现任完整包冠军为 1.00×，耗时越低越好。

| 运算 | 现任冠军 | 我方首选 | 我方／冠军耗时（预估） | 验证 |
| --- | --- | --- | ---: | --- |
| 加法 add | [#285](https://conjectures.io/v1/competitions/floatlib/submissions/285) | [原生加法＋特殊值选择](competitions/floatlib/candidates/f01-d12-scalar-combined/Kernel.lean) | **约 1.02×** | 完整通过8次 |
| 乘法 mul | #285 | [数值转换＋特殊值选择](competitions/floatlib/candidates/f01-d12-scalar-combined/Kernel.lean) | **约 1.13×** | 完整通过8次 |
| 求和 sum | #285 | [单遍求和＋快速修复](competitions/floatlib/candidates/f01-d12-scalar-combined/Kernel.lean) | **约 1.14×** | 完整通过8次 |
| 矩阵乘法 bmm | #285 | [跨行计算＋快速回放](competitions/floatlib/candidates/f01-d12-scalar-combined/Kernel.lean) | **约 1.84×** | 完整通过8次 |

整包预估耗时：冠军的 **约 1.18×**。

**结论：预估暂不能取代#285；主要差距在矩阵乘法（约1.84倍耗时）。** [计算依据](competitions/floatlib/candidates/f01-d7-research/champion-time-estimate.json)
