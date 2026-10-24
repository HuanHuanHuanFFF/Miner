# R13 三小时冲冠研究

研究窗口已完成：[完整结束回执](round-results.json)。预算完成与夺冠目标分列，未获得新冠军。

北京时间2026-10-24 19:26:22—22:26:22。保留 df5c、248144B；冠军 #285，整包预估1.18、矩阵1.84。模型5d946保持原字节。

[窗口与权限](round-plan.json) · [唯一当前状态](../../../coordination/development-status.json) · [前轮验收](../round6h-20261024T051445Z/README.md) · [用户看板](../../../../../dashboard.md)。10项已启动CI均成功终态、原件全部回收；四份新源码的正确性均通过，增量性能均未达固定0.97门槛，未采用或正式提交。

| 精确候选 | 整包／df5c | BMM／df5c | 发现组 |
| --- | ---: | ---: | --- |
| [708：一次性转换](../../f01-r13-preparation-convert/Kernel.lean) | 1.003435 | 1.005952 | [1324003](result-1324003-f01-r13-preparation-convert-vs-f01-d12-scalar-combined.json) |
| [252b：短点积复用打包](../../f01-d13-short-packed/Kernel.lean) | 1.001618 | 1.006563 | [1324005](result-1324005-f01-d13-short-packed-vs-f01-d12-scalar-combined.json) |
| [3c5e：Cross直接输出](../../f01-r13-cross-fused-output/Kernel.lean) | 1.001426 | 1.008952 | [1324007](result-1324007-f01-r13-cross-fused-output-vs-f01-d12-scalar-combined.json) |
| [8661：n=1行共享](../../f01-r13-n1-prepared-row-output/Kernel.lean) | 0.997634 | 0.993289 | [1324009](result-1324009-f01-r13-n1-prepared-row-output-vs-f01-d12-scalar-combined.json) |

3c5e的p05为正0.001656，8661为正0.001970；二者仍未达到headline≤0.97。失败发现组不换成有利seed，也不启动独立确认。

先后完成[细粒度诊断](profile-analysis-40092014611-summary.md)、[低频外层诊断](profile-coarse-analysis-40094358287-summary.md)、[三组已见输入的同binary完整调用](profile-whole-multi-analysis-summary.md)。逐元素探针造成约8倍扰动；低频方案仍不能把阶段比例直接当可消收益。跨输入BMM热点明显变化，n=1,p>2仅占整包1.2%–1.8%；3c5e发现组没有原n=1高输出热点，结论限于该输入。

下一较大数学方向是[同宽Float32缩放合并](astra-scale-fusion-feasibility.json)。当前只有纸面边界和8852个有限整数检查，缺Lean normal-rounder指数平移及精确第二乘证明；还不是运行候选或性能结果。[跨宽Float64路线](profile-scalar-wide-summary.md)因原生cast模型桥缺失停放。全局经验已合并到[数学入口](../../../research/RESULTS.md)。原一次重置已在前轮用完，本轮未再使用；无私有或付费runner。
