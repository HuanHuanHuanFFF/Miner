# R15 首批可执行优先级与最小检验

时间：2026-10-25T04:51:48Z（首次共享文件ID中的04:54为误标，以本时间为准）。两条Astra已实际开始，accepted文件与tool running状态可核对；见astra-status.json。R自己已完成原计分成本复算与ec82对旧177b的源码差异审查，尚无新候选通过声明/完整gate。

第一优先：D现有 ec82 矩阵候选可进入自己的首个完整D，但按真实变化描述：相较177b，public add/mul/sum定义全部已经相同；实际变化是p<=8直算路由、撤去R13 n1 prepared fallback及小batch Cross特例，加证明/死依赖瘦身。不是“177b去除慢标量”。三个dispatch有实质不同，故不是精确同源换seed；不能预先继承177b或9038的矩阵收益。核对回执astra-matrix-only-source-audit.json。若完整D未过whole<=.97/p05>0即停放该源，不换seed重置。

根复算3个R14原完整25轮的真实计分份额，精确class最小ns乘对应cell_work，重建headline一致：add31.97–36.15%、mul34.40–38.97%、sum6.94–8.22%、BMM18.17–26.27%。在其余不变的敏感性模型里，单项whole3%需add约8.3–9.4%、mul7.7–8.7%、sum36.5–43.3%、BMM11.4–16.5%降耗。它们是历史已见成本/路线选择边界，不是新候选性能或成功概率。见astra-priority-cost-evidence.json，原件/hash/输入份额逐批保留。

第二优先：matrix-structure worker在原逐格k次序下找覆盖更大/真实准备成本更低的复用结构；只有相较thinB/p8及已有Cross/RowStream有新差异才提出新源。scalar-sum-domain worker从实际昂贵域提出可复用既有证明的shortcut；sum路线需足够局部降耗，避免仅凭特殊值频率上马。二者05:00Z首检、争取05:15–05:20源码/引理，预留06:19冻结与完整确认。

请求开发下一自然检查点：核对ec82 manifest的真实相对起点；原版全gate+25配对DF及41优先。第一完整反馈目标05:29Z。不需要给R普通会话消息，结果按共享分题文件交接。R不开CI、不碰Git/index/开发文件；190旧资料仍HOLD。
