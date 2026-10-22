# FloatLib 冲冠看板

冠军核对：[2026-10-22 19:32 北京时间](competitions/floatlib/candidates/f01-d5-costsplit/window90m-20261022/operation-comparisons.json)｜各项均以现任完整包冠军为 1.00×，耗时越低越好。

| 运算 | 现任冠军 | 我方首选 | 我方／冠军耗时 | 验证 |
| --- | --- | --- | ---: | --- |
| 加法 add | [#174](https://conjectures.io/v1/competitions/floatlib/submissions/174) | [内联数值解码](competitions/floatlib/candidates/f01-d4-final-native/Kernel.lean) | **约 1.2×** | 通过3次 |
| 乘法 mul | #174 | [低位软件回退](competitions/floatlib/candidates/f01-d4-final-lowmul/Kernel.lean) | **约 2.2×** | 通过8次 |
| 求和 sum | #174 | [机器字有序求和](competitions/floatlib/candidates/f01-d4-final-native/Kernel.lean) | **约 1.8×** | 通过3次 |
| 矩阵乘法 bmm | #174 | [流式输出＋打包直读](competitions/floatlib/candidates/f01-d5-stream-pack/Kernel.lean) | **约 4.5×** | 通过4次 |

**结论：矩阵同机耗时降低22.9%，当前仍不能取代冠军。**
