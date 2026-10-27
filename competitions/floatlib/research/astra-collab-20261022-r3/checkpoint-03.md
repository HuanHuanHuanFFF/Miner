# R3-03：全局矩阵界证明及完整可选候选

优先收齐当前405矩阵与407求和结果、保留最终独立确认时间。以下候选已具体化，只有剩余收益和时间值得时才用 statement 槽；不以源码检查数量减少冒充实际提速，不要求立即再开完整 CI。R 后续先读405的真实生成C。

- 候选：`competitions/floatlib/candidates/f01-r3-packed4-global-guard/Kernel.lean`
- SHA：`abb650a68efb5e1c70f6bfa746670594d7d9c2ce62386da2370bbd744c1c043d`，88944 bytes。
- 父本为 D `f01-d3-word-packed4-usize-proof1`，SHA `e54f091df8f0b42e375c3fe0456f1cc0446be7bf8a93db53b8632df4a181472a`。它的实际 full405 仍待回收；新稿不继承通过。
- 官方纯 intake/policy PASS，`policy-precheck-03.json`；Lean/完整 gate/性能均 NOT_RUN。

新增数学联系：对真实的 `b : Fin batch`、`i : Fin m`，先证明 `row+1 ≤ batch*m`，再由乘法单调性得到 `row*n+n ≤ batch*m*n`。当 `0<n` 时完整行末地址有界；配合原 Vector 长度与 Array.size_map，从全局 `nativeA.size < USize.size` 推出每个 tile 所需的 n/base/末地址界。其余证明参数全部属于 Prop。

当前第一版 runDot 每 tile 有四项准入条件；此版本在完整 tile builder 外只新增一次 A.size 上限判断，叶子直接调用同一个 `Packed4Index.within`。热循环正文不改。失败分支复用已有 A/B 缓冲，保留父本 tileResults；最终非finite回退仍读原始输入。外层空输出/n=0分支原样保留，不能从空数组较小推断任意巨大 n 较小。

网页原片段以旧 Nat tileResults 为参照，我已完成实际接口适配：within命名改为Packed4Index；tile等价证明加runDot_eq以接上当前父本；保留旧bmm为bmmPacked4Base，再把经过bmmOnce_spec连接的新入口公开为bmm；独立命名空间显式打开Competition；处理可能冗余的dsimp。完整候选与manifest可直接复制，`global-guard-adapted-fragment.lean`供精确差异阅读。

这消除的是每个tile外围检查，不改变4路累加或B布局。默认形状有1300个tile，源码层从每tile四条件改为一项全局条件；真实C是否已自动消掉部分检查、完整调用净收益均UNKNOWN。若8路机器字版胜出，`MatrixBounds`的证明与lane宽度无关，可以供D适配8路；R没有另造8路候选，也不重复D的组合工作。

网页原件：

- `E:\Download\FloatLib_R3-W01_WholeCallBounds.zip`，31521 bytes，SHA `3afc5d2d28e4077e507df0148ebf390a85cd5ca20d67ae422c194a5628747805`。
- `E:\Download\FloatLib_R3-W01_Report_zh.md`，从ZIP报告逐字保存，SHA `b29d39bf3a2ef8c166f625206e9f397994ca62eb10bdd4d9506ed508ab71fa6f`。
- CRC及18项SHA全部PASS；原始片段9758 bytes，SHA `a84ced5d975f7caed47d3b9126f284b726815f81cccd268ef065b51de0dd981f`。原件没有改写或执行附带脚本。
- `web/R3-W01/download-receipt.json`记录原件路径。网页的所有新Lean依旧NOT_RUN，不据其“代码写齐”标成通过。

本轮仍于05:36:27Z结束新研究；所有已启动实验与CI回收实际终态后收尾。普通反馈继续走R3状态文件，D保留唯一Git/CI协调权。
