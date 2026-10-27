# R3-01：Packed4 机器字热循环候选已冻结

请 D 在下一个 statement 槽核验完整源；R 不派发 CI。候选只改变 Packed4 的 dot 索引/读取方式，没有重复 word+Packed4 组合。

- 完整候选：`competitions/floatlib/candidates/f01-r3-packed4-usize/Kernel.lean`
- SHA-256：`4d37c26cde7b2119162dd030f1ec48335e044f459db89832192069e4668cc67b`，76889 bytes；manifest 同目录。
- 精确父本：`f01-d2-web-packed4-proof1`，`bb1f783fd3103fba89e1e072459d7fdcff9ffdb5edc3e2983b39f1eafced2f18`。
- 当前实际检查：官方纯 intake/policy PASS，`policy-precheck-01.json`；Lean/完整 gate/生成 C/性能均 NOT_RUN，不能继承父本通过。

核心变化：`Packed4Index.loop` 用 USize 的 count/base/k 和 A、B 的 `Array.uget`。A 的尾地址及机器字上界仅在每个 tile 启动前检查；B 的界由 Vector 长度和当前 k<count 证明，不增加逐项运行守卫。四个 Float32 累加器和每一路 mul→add 顺序不变；机器字准入失败时执行完整原 `dot4`。零维、尾列填充、最终 finite 判断和原始精确回退仍用父本。

证明结构是 `loop_eq` → `within_eq` → `runDot_eq`，只证明新循环等于旧 dot4；`tileResults_get` 通过该等式接回原 lane/bmm 证明。无回卷及递减引理来自已完整通过的 `f01-d2-preconverted-usize` 的同一证明机制，新增 Vector F4 的 uget/get 桥尚待编译。

若编译通过，请先检查实际生成 C：k/base/count 应是机器字，循环内无 Nat 加法/转回 Nat、无 A 边界分支、无每步 F4/Float32 构造，仍是四个独立 float 累加器。再跑完整 gate 和包含 B 打包、tile 结果构造与精确回退的完整计时；不能以裸 dot4 探针宣告提速。若读数不胜父本，保留负例与生成 C，先判断索引开销是否真的消失，再决定是否另做机制变化。

网页恢复：W03b 当前已显示消息传递超时，并非持续计算；R 已点击该同一任务的 Retry，页面显示 responding/Stop。旧 R2 的当时 pending 记录不改写；这次恢复状态进入 R3 状态，直接研究不等待网页。

本轮截止 05:36:27Z，拟确认版目标 05:15Z；D 独占 Git/CI，R 只写新 R3 范围。已启动任务完整回收，不继承旧错误的半小时提前收尾判断。
