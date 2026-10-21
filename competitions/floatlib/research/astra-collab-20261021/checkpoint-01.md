# R 检查点 01：先拆开实际循环与计时边界

2026-10-21 10:39 UTC。状态：SOURCE_VERIFIED / MECHANISM_INFERRED；尚无新候选 Lean 结果。

## 可以立即改变选择的事实

1. 已成功且仅作 tensor inline 的 `f01-tensor-specialization` 生成 C 中，bmm 每输出仍分配闭包，调用外部 `l_Fin_foldl_loop___redArg`；sum 仍调用带 Monad 字典及闭包的 `Array_foldlMUnsafe_fold___redArg`。具体 C 为 `candidates/f01-mul-log2-proof1/ci-runs/39577094266/download-0d62ed7335f5477db52ce52528cae461/diagnostics/f01-tensor-specialization/candidate-generated-0.c`，bmm 20265—20292 行、sum 16350—16451 行。算术已经展开到各个回调，但循环没有形成直接 UInt32 累加的 C 循环。因此“简单 inline 无效”并未排除直接尾递归循环。
2. 核对 Lean v4.34.0 原始 `Init/Data/Fin/Fold.lean`：foldl 本身 inline/expose，内部 loop 为 specialize/semireducible。存在属性不等于当前编译产物已特化；以上 C 是实际未特化证据。
3. pinned BenchBmm 形状是 50×100×50，默认两批、500000 次乘加、5000 个输出。#174 历史原始响应 bmm dense 为 0.197304 ns/乘加，即整次约98652 ns、每输出19.7304 ns；relu/wide 几乎相同。该形状与低且近乎数据无关的数值，使“计时中主要剩输出遍历/分配”值得排查，但绝不证明冠军做了工作移动，更不证明违规。
4. BenchFull 的 pass 里纯 bmm 调用不依赖校验种子 r，但该 pass 在 IO 内重复。仅凭源码不能断言优化器外提；必须看实际 MainFull/BenchFull C 中 monoNanosNow 与 bmm 调用的先后。当前只回收 Submission C，不能确认该原因。sum 的 kernel 调用位于 sweepSum 的遍历中，结构不同，不宜用同一个解释覆盖两者。
5. 零回退真实存在：pinned Addition.Runtime 的 `addFiniteImpl?` 对任一零尾数转入 exact dyadic。relu 至少一半乘积为零；dense/wide 主要是每输出初始 +0，单靠零路径很难解释三个 bmm 类同样数百倍差距。计划用精确有限模型给出频率，不把次数比例当耗时比例。

## D 的最小判别请求

继续 D 已计划的 scalar+tensor compiler-boundary 试验；回收精确候选生成 C，确认实际调用是否变成直接循环。若已有诊断入口能无侵入保留 MainFull/BenchFull C，也一并保留，核对计时区内是否有完整计算。不要改官方 bench/gate。

R 已冻结新机制候选 `candidates/f01-r1-direct-dot-loop/Kernel.lean`，SHA-256 `cb09e9c6913100097f21ebdc5059345885bce090894f53f8f876377edad8fcab`，35211 字节：在候选内直接定义尾递归 dotLoop，显式读取 A/B、执行原加乘并递增 k；源级 Binary32 累加器预期被编译器擦除成 UInt32（待 C 确认）。基址外提，按 Fin.foldl.loop 的逐步递推写了全域等价证明草稿。优先 bmm，一份待测后停增积压。成本预期为一次 statement/full gate，真实耗时 UNKNOWN。此候选不改变标量算术，不靠零捷径。D 请复制到自己的候选目录修复／验证；R 原包冻结。

## 公开起点

继承已完成的 27 份官方源码、分支、历史 digest 及下载接口调查；本次补充网页搜索未发现历史冠军源码。可合法复用的实际来源是 pinned 官方完整参考及 Lean 的标准 Fin.foldl 定义，分别保留官方许可归属；不把公开原型或不存在的冠军源码当领先起点。SoftFloat 已有副本和归属，GRS 上轮负结果保留，暂不重复。

原始来源副本在本目录 sources/，URL/版本和哈希将由 source-receipts.json 绑定。候选与证明未编译，正式冠军对比 UNKNOWN。
