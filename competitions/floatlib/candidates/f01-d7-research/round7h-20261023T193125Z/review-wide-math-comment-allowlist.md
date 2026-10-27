# 28b819 纯数学注释 allowlist

已逐段完整读取此前182段、16174 B普通说明原文。**只放行137段纯数学定义/性质或引理说明，共12112 B；其余45段4062 B继续保留。** 纯数学安全池不足约13.5 KB，不为补数放宽来源/运行义务保护。加全部1538 B原始普通空白行可回收13650 B；未写压缩Kernel。

父本必须精确为253315 B / `28b819120cd3aaa1f19038f66042a9ceffe0c9329baab20fe223e98d151ce00b`。[JSON receipt](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/round7h-20261023T193125Z/review-wide-math-comment-allowlist.json)包含每一段的半开UTF-8原始byte start/end、原始行号、SHA-256、完整original_text及逐项保留/放行理由，也包含全部普通空白组与完整inverse ledger。此前容量与927报告保持原字节。

这不是自动全文heuristic删注释：182段pool均在本次输出全文逐一阅读，再以明确comment index决定。原scanner已保护的9段notice、前审额外保护的19段源码归属/拼接/历史状态，以及本次45段运行/表示/证明工程义务全部保留，共73段。其原始comment文本/hash/顺序在内存dry-run中逐一核对相同。

保留内容包括：每次mul/add的原顺序和非融合要求、NaN精确回放/读停止规则、caller前提与guard/fallback、共享输入加载、无额外row/lane分配、word index/bounds只建立一次、column-major布局、buildTiles求值次数、全局nativeA/packedB准备与尾行共用、原入口状态、计时边界，以及named FloatLib实现归属。没有删除once-evaluation/lifetime说明来凑容量。

| 只读规划 | 源B | 备注 |
| --- | ---: | --- |
| 28b819原件 | 253315 | 当前余2685 B |
| 仅137段allowlist | 241203 | 回收12112 B |
| allowlist+全部原普通blank | 239665 | 回收13650 B |
| 再加既有Cross增量15499 B | 255164 | 仅算术投影，余836 B，未含任何新增glue |

若仅删allowlist而不删blank，加Cross后为256702 B，仍超702 B。Root可按真实组合精确大小选择整条原普通blank；全部blank也仅留下836 B投影余量，不能据此承诺Panel4尾部模块有空间。Astra的新组合必须实际dry-run、核最终字节，不得把这张加法表当成生成结果。

两个内存结果的SHA仅用于复现，不存在对应压缩源码文件：

- 仅数学注释：`a032bac4750e66591ce711a1b56dd685a5fdbd3c5529c1c4c20c238b04e413a3`。
- 数学注释+全部原普通blank：`acba1e31db0521a93e454990269d26afde50dc656563bd5098d6baf8d7eed18c`。

应用边界：先核原28b819与冻结helper/parser，再对原byte区间按倒序精确删除；replacement为空，不能扩展到相邻代码、notice、缩进或行内comment。若先组合Cross导致offset移动，必须依据完整edit/source映射重绑定，不能对新稿直接套原offset。prefer先在精确28b819上做receipt变换，再组合Cross。任何子集/新增glue都要重新记录最终SHA及inverse，JSON里现有inverse只绑定“全allowlist+全原blank”。

普通blank仅指原源中comment外、物理整行只有空白的行，不含comment内部空行，也不含移除注释后新出现的空行。未进行任何单token间空白压缩。所有未选中的comment原文保留，完整原28b819和receipt用于恢复原文。

已在内存验证：完整inverse逐字恢复28b819；live物理代码行和leading indent字节相同；法律notice hash序列相同；73段未选comment字节与顺序相同；R8 namespace/declaration inventory的506个限定名及重数不变。这里仍只证明选定字节操作的边界，**新Lean、policy、四spec、fullgate和性能均NOT_RUN**，不能继承父本验收。未删unused定理、改变资源选项或绕过256000 B限制，未改Kernel/helper/Git/CI。
