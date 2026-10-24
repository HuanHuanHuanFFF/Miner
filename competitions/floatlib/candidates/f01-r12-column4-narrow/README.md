# R12 窄列四通道候选

冻结父本为 df5c61a0 的标量组合。本候选仅在原 p=2 Cross 分支之后，为 p=3/4、n>4 且 n/A 长度满足机器界的输入使用四列内核；保留外层 Underflow、短维度路径和完整 Nat 回退。

旧 96131686 的四列读取、逐 lane 递推和 USize 证明接入当前 Packed10.finish，保留 NaN-only 判断、原始字回放及当前标量冷路径。每行只计算一个 F4，使用 RowStream 前缀接口连续输出；没有四行 A 面板、F40 缓存、rowTiles、flatMap 或 append。

Kernel 为 255439 B，SHA-256 da09fb59fa456b498af6bde48d54adcd37f85c4ba7df272163b184a2b83038c4，余量 561 B。builder 默认只读重建并逐字节核对。27 条未使用证明正文合计 7387 B 的删除闭包绑定完整新源码；所有原注释、来源说明、八个导出类型、Cross/Direct/Underflow 和最终 1039 B 保留。静态文本依赖检查不替代 Lean。

新 Lean、完整 gate、真实代码和性能均 NOT_RUN。先原始 statement，再同输入全成本对照及实际四列机器码。旧全宽 F4 对 d9 的负面结果保留：seed809 whole 1.155963、BMM 1.457068，旧 finish 和 writer 不同，不能当作本次窄切片的正负结果。
