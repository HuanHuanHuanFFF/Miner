# FloatLib 冲冠看板

冠军核对：[2026-10-28 23:15 北京时间](competitions/floatlib/candidates/f01-d7-research/round40m-20261028T142626Z/official-final-20261028T151511Z/comparison.json)；冠军为 **1.00×**，耗时越低越好。

| 运算 | 现任冠军 | 当前开发 | 开发／冠军（预估） | 保留版／冠军（官方） |
| --- | --- | --- | ---: | ---: |
| 加法 add | #323 | [原生冷尾加法](competitions/floatlib/candidates/f01-r22-dev-nativecombo-public1/Kernel.lean) | **1.25–1.42×** | 1.35–1.53× |
| 乘法 mul | #323 | [原生冷尾乘法](competitions/floatlib/candidates/f01-r22-dev-nativecombo-public1/Kernel.lean) | **1.46–1.58×** | 1.52–1.65× |
| 求和 sum | #323 | [保留单遍求和](competitions/floatlib/candidates/f01-r22-dev-nativecombo-public1/Kernel.lean) | **1.03–1.61×** | 1.03–1.61× |
| 矩阵乘法 bmm | #323 | [保留B2双列](competitions/floatlib/candidates/f01-r22-dev-nativecombo-public1/Kernel.lean)；[缓存与输出连接已验](competitions/floatlib/candidates/f01-d7-research/round40m-20261028T142626Z/development-matrix-proof-status.json) | **2.23–4.73×** | 2.23–4.73× |

整包：保留版官方 **1.63×**；当前开发预估 **1.56×**。[依据](competitions/floatlib/candidates/f01-d7-research/round6h-20261027T211247Z/development-dashboard-forecast.json)

**结论：仍不能取代#323；开发组合完整验证通过，稳定性门槛未过，保留B2。**
