# R28数学、证明与成本成果

当前目标仍未达成；完整新候选、独立数学归约、模型和准入分开验收。共同截止UTC20:15:58不变。

| 成果 | 当前可核实证据 | 缺口/采用边界 |
|---|---|---|
| LayerNorm guard26的完整迁移 | 79615bd5/255514B，原all12至axioms PASS183.17s；D CI3 quick360pairs，当前56链式估计1.1014× | 比公开36约5.56%探索改善；非冠军、尚无冻结后独立标准确认。intake/norm26-and-singleton-review、ci3-measurement-route-decision |
| GEMM双行linear完整组合 | 7b6e0cba/252828B，原all12至axioms PASS181.79s，quick360pairs | 当前56估计1.2179×，停止该精确结构的大证明/扩变体；D原件为准 |
| 空间Winograd字长 | 父通用14安全/15溢出纸面界、203指数端点；15通道finite词4d86ffff→cd720002，A独立重放四输出 | 非原11漏洞；新runtime/producer/全12未证明。winograd-bounds/BLOCK-BOUND.md |
| 四倍body重标度 | T=4S用B0−2并重建bias，20000 exact模型检查；漏改bias让1→0.25 | 需B0≥2、bias/128界、raw零符号桥；A空间原型已采用但仍NativeOnly。REBASE-NOT-DIVIDE |
| 空间模128证明架构 | 64位块先真实，128加减只保同余，最终T<2^89恢复唯一signed128 | Lean/实际数组与索引桥未闭合。MODULAR-CLOSURE |
| 非零支撑63bit打包 | 56bit偏置factor+7bitindex<2^63；父100298 codec/1100四累加器模型，A具体patch/Word接口 | 同一家族，不算两份独立证据。cache扩张、getter/shape与全12/成本未知。sparse-input、A Packed* |
| 非负输入单边偏移 | exact Σa(b+Q)−QΣa；保持span15的unsigned64域。父2548模型，B38026旧PW输出重放；signedcarry错4200003f→c1ffff82 | 新表示未接Kernel/计时，非冻结pointwise缺陷；需真实非负guard/producer/偏置/零符号/all12。ONE-SIDED-POSITIVE-DOT |
| 重叠32位寄存器累加 | 两个独立sum寄存器、终端一次carry；n<2^32纸面证明，2304字数组和越界反例，固定Int64算术shift接口已查 | 未Lean编译、未Kernel、未测新ASM/成本；不用于截断更宽产品。overlap-accumulator |
| 证明失败定位 | actual source原q8 PASS63.53s、修q14 FAIL65.99s，定位两个termination goal，失败AX含sorryAx不采信 | v3 all_goals修订未编译；零项runtime已测负，不继续600s整证明。B CI4-RESULT-DECISION |

两条已明确的成本负结果另保留：zero474eff完整360pairs当前57估计1.2712×；centered64c5完整360pairs当前56估计1.3061×。它们不否定数学恒等式，只停止这些具体实现的主要投入。pointwise5ecf编译失败无计时；typed17befe修7处typing/size-proof后在CI5实测负，当前57估计1.1621×，停止大证明；不能继承为完整正确性。

科学边界：所有当前冠军倍数是跨报告/config/runner的INFERRED校准，无现任私有源码同机配对或正式排名。旧6.07%Res差距已随64晋级留为历史；当前链式规划19.015%，active policy本轮未变。原11稀疏直接代码36个scalar乘，不是18；父错误归因已在SPARSE-BASELINE-CORRECTION中修正。全部full上游源/私人聊天锚点忽略保留，公开自己的推导、配方、模型、失败和回执。

CI5追加已释放：typed pointwise17befe/245601B编译、360pair校验/计时完成，当前57链式估计1.1621×且guard失败；停止该consumer大证明。它完成了“类型错误→真实成本”的区分，仍无新correct/冠军。overlap32另补SHA绑定的SHARP-LENGTH：该固定两状态表示signed可到2^32项、unsigned到2^32+1，闭式越界反例不分配大数组；原保守运行草稿不变、无当前性能收益。

关闭补记：共同截止20:15:58已到，R及三子线已停止新研究。共享支持摊销式仅为下一轮数学/成本接口，尚无候选/计时。CI6仅由D/verify收齐验收，冻结的研究文件不依其结果调整。最终角色时段见FINAL-RECEIPT.json。
