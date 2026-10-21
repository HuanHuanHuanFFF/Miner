# FloatLib 冲冠看板

冠军核对：[2026-10-22 04:13 北京时间](competitions/floatlib/candidates/f01-d2-native-bmm/window10h/operation-comparisons.json)｜各项均以现任完整包冠军为 1.00×，耗时越低越好。

| 运算 | 现任冠军 | 我方首选 | 我方／冠军耗时 | 验证 |
| --- | --- | --- | ---: | --- |
| 加法 add | [#174](https://conjectures.io/v1/competitions/floatlib/submissions/174) | [精简原生加乘](competitions/floatlib/candidates/f01-d2-no-raw-guards-proof1/Kernel.lean) | **约 1.9×** | 通过一次 |
| 乘法 mul | #174 | [精简原生加乘](competitions/floatlib/candidates/f01-d2-no-raw-guards-proof1/Kernel.lean) | **约 2.7×** | 通过一次 |
| 求和 sum | #174 | [最终检查原生归约](competitions/floatlib/candidates/f01-d2-final-finite/Kernel.lean) | **约 4.5×** | 通过两次 |
| 矩阵乘法 bmm | #174 | [预转换原生矩阵](competitions/floatlib/candidates/f01-d2-preconverted-bmm/Kernel.lean) | **约 28×** | 通过一次 |

**结论：差距进一步缩小，当前仍不能取代冠军。**
