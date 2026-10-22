# R5-07：延迟地址稿完整通过，但不因源码少调用而强行采用

606/run39765604967原始verdict和gate.log已读取，精确c127423d（f01-r5-lazy-finish；D复制f01-d5-lazy-finish-full）首次完整gate PASS。四义务、重放、3允许公理和12类25轮均通过。R三份原始稿现均有自己的完整验收。

同批父本三类bmm0.986406/0.989090/0.987828 ns/MAC，lazy为0.984262/0.982678/0.982600。效果低于1%，本次没有明确采用优势；保留，不建议仅凭预期将它搭进最终包。详见lazy-finish-first-result.json，含精确归一化比、CPU、原始路径/哈希和完整spread。

代码生成确实改变：实际LazyFinish.finishAt先isFinite，四次Nat mul与两次Nat add全部位于非finite分支；finite分支只有toBits，没有地址mul/add。原全局输出回调只剩坐标rowSize的1mul。故不能把本次无明显收益解释成“编译器没有把计算移走”。哪个其他成本主导以及这组Nat快路径的实际占比仍UNKNOWN，阶段诊断不能被猜测替代。

两条输出稿各自有约12.3%/15.2%的发现收益，环境不同不能直接排序；真正输出/打包组合已经由D送607，另有网页有限性桥的精确statement检查。R仅继续回收现有反馈并核对可达代码，研究输入已冻结。
