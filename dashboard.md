# FloatLib 冲冠看板

官方核对：[2026-10-27 18:29 北京时间](competitions/floatlib/evidence/formal-b2-336/comparison.json)｜冠军为1.00×；四项显示官方各输入组的耗时比范围，越低越好。

| 运算 | 现任冠军 | 我方首选 | 我方／冠军耗时（官方各组） | 验证 |
| --- | --- | --- | ---: | --- |
| 加法 add | #323 | [原生加法＋特殊值选择](competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean) | **1.35–1.53×** | [#336 官方通过](https://conjectures.io/v1/competitions/floatlib/submissions/336) |
| 乘法 mul | #323 | [数值转换＋特殊值选择](competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean) | **1.52–1.65×** | [#336 官方通过](https://conjectures.io/v1/competitions/floatlib/submissions/336) |
| 求和 sum | #323 | [单遍求和＋快速修复](competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean) | **1.03–1.61×** | [#336 官方通过](https://conjectures.io/v1/competitions/floatlib/submissions/336) |
| 矩阵乘法 bmm | #323 | [双列复用＋B2成对存储](competitions/floatlib/candidates/f01-r15-dev-packed-b2-1/Kernel.lean) | **2.23–4.73×** | [#336 官方通过](https://conjectures.io/v1/competitions/floatlib/submissions/336) |

整包官方耗时：冠军的 **1.63×**；原预估1.25×，实际比预估慢 **30.4%**。

**结论：官方验证通过，当前第13；尚不能取代#323，主要差距仍在矩阵乘法。**
