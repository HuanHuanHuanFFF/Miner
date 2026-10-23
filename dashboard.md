# FloatLib 冲冠看板

冠军核对：[2026-10-23 20:35 北京时间](competitions/floatlib/candidates/f01-d7-research/official-20261023T123457Z/receipts.json)｜各项均以现任完整包冠军为 1.00×，耗时越低越好。

| 运算 | 现任冠军 | 我方首选 | 我方／冠军耗时（预估） | 验证 |
| --- | --- | --- | ---: | --- |
| 加法 add | [#285](https://conjectures.io/v1/competitions/floatlib/submissions/285) | [原生结果守卫](competitions/floatlib/candidates/f01-r8-combined-result-guard/Kernel.lean) | **约 0.94×** | 完整通过2次 |
| 乘法 mul | #285 | [结果守卫＋低位回退](competitions/floatlib/candidates/f01-r8-combined-result-guard/Kernel.lean) | **约 1.02×** | 完整通过2次 |
| 求和 sum | #285 | [单遍有序求和](competitions/floatlib/candidates/f01-r8-combined-result-guard/Kernel.lean) | **约 0.88×** | 完整通过2次 |
| 矩阵乘法 bmm | #285 | [直接点积＋矩阵布局](competitions/floatlib/candidates/f01-r8-combined-result-guard/Kernel.lean) | **约 3.05×** | 完整通过2次 |

整包预估耗时：冠军的 **约 1.21×**。

**结论：预估暂不能取代#285；主要差距在矩阵乘法（约3.05倍耗时）。** [计算依据](competitions/floatlib/candidates/f01-d7-research/champion-time-estimate.json)
