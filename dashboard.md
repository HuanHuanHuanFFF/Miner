# FloatLib 冲冠看板

冠军核对：[2026-10-22 18:10 北京时间](competitions/floatlib/candidates/f01-d5-costsplit/window90m-20261022/operation-comparisons.json)｜各项均以现任完整包冠军为 1.00×，耗时越低越好。

| 运算 | 现任冠军 | 我方首选 | 我方／冠军耗时 | 验证 |
| --- | --- | --- | ---: | --- |
| 加法 add | [#174](https://conjectures.io/v1/competitions/floatlib/submissions/174) | [内联数值解码](competitions/floatlib/candidates/f01-d4-final-lowmul/Kernel.lean) | **约 1.1×** | 通过4次 |
| 乘法 mul | #174 | [低位软件回退](competitions/floatlib/candidates/f01-d4-final-lowmul/Kernel.lean) | **约 2.2×** | 通过4次 |
| 求和 sum | #174 | [机器字有序求和](competitions/floatlib/candidates/f01-d4-final-native/Kernel.lean) | **约 1.8×** | 通过3次 |
| 矩阵乘法 bmm | #174 | [十列矩阵＋坐标内联](competitions/floatlib/candidates/f01-d4-final-lowmul/Kernel.lean) | **约 4.4×** | 通过4次 |

**结论：差距进一步缩小，当前仍不能取代冠军。**
