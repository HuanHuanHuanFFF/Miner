# 四行后继的成本前提：与当前 proof 工作分开

这是冻结前源码层分析，没有计时结论，也没有新运行候选。D 正在测 e4bf 原四行与 PreparedQuad；A 不改其运行体或阈值。

**21:49 UTC 证据修正**：已读 `development-cost1-actual-loop-audit.json`。真实两行计时 loop 及其专化 map helper 的 closure_alloc / float_box 静态调用点均为 0；loop 的 ctor_alloc 为 0，map helper 留 1 个 ctor allocation site。standalone advance 的分配不能外推到这个 actual loop。下方单 Cell 捕获只保留为“未来新的实际 quad 调用链确实出现分配且占比足够”时才重开的条件性想法；当前不优先、不组源、不请求 CI。静态 site 数也不等于 Cell 分配或复用的动态频率。

四行在 m 可整除 4 时，相对两个双行块，A raw decode 数量不变，B raw decode 数量减半；按这一窄计数，二行总 raw codec 为 `m*n + (m/2)*n*p`，四行为 `m*n + (m/4)*n*p`。该计数不含初态、closure、floatbox、RC、状态访问、原 finish、NaN replay 或析构，也不适用于保留 B2 已预打包 B/A 的分支。不能把它当整包速度。

现有 B2 对窄 p=2..8、m>=4、n>1 走预打包 B2；更宽且 n>4 经 RowStream/Packed10 走另一种预打包布局。新 broad eligibility 会覆盖这些域，因此必须比较真实 B2 caller，不能继续以逐点 DC 的重复 decoder 数量估计收益。

如果四行仍被实际每 k 的四个 Float32 box / closure 支配，可考虑一个单独判别：把四个 A 值作为一个固定 Cell 交给 mapper，而不是四个标量捕获。该想法目前 UNKNOWN：普通 let Cell 很可能被编译器标量拆分回四个捕获，增加 noinline 边界又可能引入每列调用；批量 packA 则增添数组和生命周期。只有实际 C 表明当前四标量包装仍在、且占据足够总成本时，才值得构造这一探针。不是已实现优化，不自动建议新 CI。

轻量历史检索仅覆盖 R20/R21 表示研究及当前 R22 小片段，未找到这个具体四值捕获方式的已测原件；这不证明它从未尝试，更不证明有收益。完整实现前还应回查更早 R19 packing / closure 负结果。A 当前仍优先等待精确 writer/public 的真实编译反馈。
