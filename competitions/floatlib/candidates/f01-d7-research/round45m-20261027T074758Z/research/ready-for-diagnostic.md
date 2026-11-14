# 两份精确机制源可承接诊断

时间：2026-10-27T08:10:00Z；回复D08:04与08:06分工。

1. **Row广播**：`research/row-broadcast/Probe-row-broadcast8.lean`，239638B，**ec40e88eb85730520a1cd1e6adcbaea3c8161fc5c0f7e4b2f5795e178d24a5a6**。完整B2字节前缀不变；Temporal B8只整调用准备一次，raw A每k只解码一次供8条原序链，删除A缓存。诊断入口`Submission.R20RowBroadcast.diagnosticBmm8`，当前只固定p=8／任意batch,m,n，返回Array。9根及HelperAudit在同目录；全public新BMM证明未做。重点采实际选中loop／row8／diagnosticBmm8的call、spill、状态分配、准备及finish，不把导出叶当真实caller。
2. **Terminal pair**：`research/representation/terminal-pair/Kernel-terminal-pair-diagnostic.lean`，230373B，**b6b77553d49e968db27639b84f104783a9cf474ed963ec9cff7753a7adb17962**。旧pair终态F2改直接finish+两push；原codec和每输出逐k序保留，输出跨loop存活可能增成本。8根及HelperAudit在同目录；抓`Submission.R20TerminalPair.control/terminal/loopPair/loopEmit`实际C／ASM。已纠正旧selected rawpair没有emitclosure，故只主张尝试删F2，不计虚构closure／UInt32输出堆对象。

R已独立核两份字节、SHA、256000上限、完整B2前缀、精确9／8根及public入口未改，见`research/ready-artifacts-review.json`。**Lean／性能NOT_RUN**，不作为新public规格或完整gate。

SUM数学资产已交`mathematical/AbsorptionInterface.lean`和精确oracle；31,056命中对＋1000个4项块无差异，保留binade反例及逐项吸收不允许合块求和反例。仍缺all-sign raw→FloatLib桥。接受D覆盖筛选，本窗不造SUM候选／性能CI。

两候选已冻结，本方后续只在隔离目录扩展接口／研究下一轮至共同08:32:58，不改上述源。D统一manifest／Git／CI；原公开版本保持B2。
