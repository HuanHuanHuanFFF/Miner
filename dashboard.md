# FloatLib 冲冠看板

冠军核对：[2026-10-22 12:42 北京时间](competitions/floatlib/candidates/f01-d3-word-packed4/window1h-20261022/operation-comparisons.json)｜各项均以现任完整包冠军为 1.00×，耗时越低越好。

| 运算 | 现任冠军 | 我方首选 | 我方／冠军耗时 | 验证 |
| --- | --- | --- | ---: | --- |
| 加法 add | [#174](https://conjectures.io/v1/competitions/floatlib/submissions/174) | [混合乘法组合优化](competitions/floatlib/candidates/f01-d2-hybrid-preconverted-usize/Kernel.lean) | **约 1.5×** | 通过两次 |
| 乘法 mul | #174 | [整数判断组合优化](competitions/floatlib/candidates/f01-d2-word-preconverted-usize/Kernel.lean) | **约 2.3×** | 通过两次 |
| 求和 sum | #174 | [最终检查原生归约](competitions/floatlib/candidates/f01-d2-final-finite/Kernel.lean) | **约 4.5×** | 通过3次 |
| 矩阵乘法 bmm | #174 | [四输出矩阵累加](competitions/floatlib/candidates/f01-d2-web-packed4-proof1/Kernel.lean) | **约 8.3×** | 通过一次 |

**结论：差距进一步缩小，当前仍不能取代冠军。**
