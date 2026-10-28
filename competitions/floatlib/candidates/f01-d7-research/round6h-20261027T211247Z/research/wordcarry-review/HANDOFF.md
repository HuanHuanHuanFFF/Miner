# R22 A：当前 word-carry 独立核验

**本阶段已交root并冻结**。当前A唯一索引转[../streaming-public/floatarray-storage/HANDOFF.md](../streaming-public/floatarray-storage/HANDOFF.md)；word-carry纸面及有限检查不变。

共同截止 **2026-10-28 03:12:47 UTC**；A实际首工具 **21:17:47 UTC**。本阶段恢复时钟00:47:32，限15分钟；D唯一Git/CI/运行体，本方无新候选/Lean编译。

- **纸面结论成立**：[PAPER-PROOF.md](PAPER-PROOF.md)对D精确5806bb25/1166B与旧fa652 normalCore作三情形代数证明；h0跨位Q恰2^24，由最终加法带进指数；h1由Pmax推出Q≤2^24−2；所有UInt64/UInt32操作在S128..380无wrap，最终符号不相交。无需重证RNE，正常乘积值理论仍复用旧端点。
- **有限边界检查**：[boundary-receipt.json](boundary-receipt.json)，46对mantissa×253个S×2符号，共23276个整数端点比较。跨位P=2^47−2、Pmax、tie parity、S端点覆盖；错误Q掩23位变异被抓。不是Lean/Float32/public正确性。
- **最小证明接口建议**：`new.normalCore S u v = old.normalCore S u v`对任意u/v只需S128..380，因为mask/implicit位已保证两个24位mantissa。不造public证明，不抢D Sol对88cdf的typing。旧fa652完整公共根仍未验；当前88cdf真实gate结果以D回执为准。
- **历史范围**：未找到同一初始leading-bit+加法pack的既有MUL完整成本；有界检索不作新颖性证明。旧DirectBias/Jam负面保留，新成本UNKNOWN。

前阶段已收束：[cache-layout-closeout.md](../streaming-public/cache-layout-closeout.md)：B2没有第二次B转置/复制；逐batch缓存已有28af实际完整调用，当前B2迁移的边际收益才是未闭前提。Native product e51a精确体四组MUL1.035/1.041/1.099/1.043停放；5f5b两桥仍NOT_RUN储备。下一实际typing/成本反馈优先；继续共同研究窗口。
