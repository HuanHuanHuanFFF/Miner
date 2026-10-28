# R22完整成本关键复核

检查对象为D冻结的`22c60285`诊断源及`development-cost/BmmCost.lean.inc`，而非A全形状v1。此为一次源级/测量边界审查；实际机器入口及计时待本批原件，未宣称Lean或性能通过。

- 矩阵先保留原underflow-zero快路。既定`n>1,m>=2,p>=2`进入stream；其余回到完整B2。每batch只配对本batch的`floor(m/2)`组，原始A行是`b*m+2*r`与下一行；尾部恰`(m%2)*p`个输出。`m=0`的减一表达式不被零次emit求值。B基址`b*n*p+j`、步幅p，所有输出保留原始k序及原raw finish/NaN replay。
- 新调用的计时入口直接传入完整guarded矩阵和guarded scaled MUL；计时体包含pack/初始化、逐k状态维护、两遍finish、输出以及fallback，未传入只含updateCell的局部函数。原三个公共scalar/sum函数在矩阵变体保持B2；乘法变体其他三端点保持B2。
- driver明确先固定两发现seed、control/stream/stream/control和control/scaled/scaled/control顺序、156个case/152个计分项。保留所有逐项日志和checksum，非25轮正式成绩；该两个发现seed不能改标为未见确认组。源码变体与正式/public采用证据仍须另验。
- 独立Lake配置只增自己的诊断target；原配置/bench/contracts/pins/OWN_STEMS和原build产物前后均有哈希检查。编译/link/rsp实际参数需在回收后核仅root/target路径不同；捕获工具在计时之后，实际C/ASM caller语义审查仍未完成。
- 原R21准备的同形raw DC对照不是保留B2；本次control为真实Submission.bmm/B2，源级codec计数`4np→n(p+2)`不能当作对B2的速度预测。mapIdx的if-possible复用、每k闭包/floatbox、第一扫共享Cell和state释放均可能抵消省去的读取。

待改变投入的证据是：完整调用相对B2是否改善、哪些场景退化、实际稳态是否复制整个state或分配每slot Cell。D回收首次screen后按这些结果选择继续2row、转4row有效lane或停该表示。A的`ebfb6408`只在同一既定dispatcher上补公共证明，身份与性能均仍待验。
