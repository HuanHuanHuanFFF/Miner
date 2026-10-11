# R25 续跑状态

固定北京时间窗口：2026-10-11 16:06:21–21:06:21；main基线48baf622，分支codex/round25-fast-quality，一个worktree。执行规则见[AGENTS.md](../../AGENTS.md)。目标为快速端低成本改善压缩、争取稳定竞赛池份额榜首；截至18:23尚未建立稳定正份额，更未达成榜首。

截止不重算。19:36:21拟冻结，最后90分钟保留完整原版gate、精确文件对独立确认与交付；20:06后不派新普通发现实验。已启动CI自然完成或既定超时，不主动取消。

分工：Astra/xhigh做tinyPC新helper Lean迁移，独占r25-astra-tiny-pc8-proof1等新增路径；Sol/xhigh完成duplicate-hop并审边界；Luna/max官方来源/算术审计当前空闲；主线程管理Git、CI、评分与共享入口。工具支持根加3子线程，无额外worktree，无嵌套。

已收齐19个成功作业：原15个，加HI screen/I extraction/J native/J screen。原协议共94配对进程，均发现测量。完整gate已通过end4，tinyPC proof1 gate38130996700仍运行。所有raw保留。F一次dispatch前只读网络失败另存，不是CI失败；一次本地Git暂存文件名错误也在dispatch前被冻结检查挡住，没有新增CI。

性能：A end4/backtie/gap1各两块595主影子均0；end4对combo慢0.72%–0.92%。end4完整原版gate通过，Rust03ec0aa4.../Lean4ff09d16...绑定VERIFICATION，仅保留质量/正确性组件。C dual8少14674B但总时间慢3.02%–3.26%，595/影子/578视图全0；D wordtail与end4真实444有限等价和28文件输出相同，但主测时一块慢0.495%、一块快0.060%，份额全0，暂无收益，不扩展gate/asm。

诊断：E确定dual8主成本为额外8字节哈希/维护；F的2538080次record写入贡献53017次获胜提示，不可视为无用。H mainonly实际删除这些写入后，比dual8多17230B，比combo多2556B；耗时未知，仍给一次原协议代价端点实验。G发现父链短匹配遇相同8字节前缀时有有据机会，但长匹配也依赖同前缀链，因此不整体替换prev；J只在短主匹配、dp1、合法重复前缀时多看一次prev，保持所有插入。

最新质量信号I：r25-root-tiny-pc8 Rust5c20b99c...，只替换已有row12的ETINY为专用PC引擎，8头插入、正常验证过的emitter、原路由不变。28原编码器仅tiny-config变化2487→2155B，少332B，平衡压缩比例改善0.0988095pp；总时间/份额/完整gate未知。与历史584同文件体积一致不代表整体时间相同。

最新HI/J反馈：H比dual8快1.276%–1.456%，但比combo慢1.120%–1.155%且多2556B，份额全0，暂停。J实际3497B改善、目标12文件全部较小，仍慢0.617%–0.815%，份额全0，暂停完整证明。I慢1.574%/1.682%，主份额0.071394%/0、595影子0.111155%/0，不是高份额候选。cost-i-screen逐rep恒等分解表明唯一改变的tiny-config编码成本贡献+1.50至+1.65pp，parser仅+0.18至+0.19pp；27原输出文件不是主因。

下一批K/L：counts-k-native临时encoder观察，combo/I各tiny-config和tiny-app控制，核对原token、原/观察encoder字节与decode，观察三棵Huffman树live/包数/复制量及len/dist查表；price-l-native对combo/public578/public584各28文件的len3真实原block码价与亏损覆盖做未计时观察。两个脚本分别Astra、Sol准备，root已建batch/路由，须等完整preflight通过再提交/dispatch，各12分钟上限。没有新候选/掩码/阈值扫。Luna在统计已落盘CI成本检查点。观察结果不能替代原协议时间。

当前运行：38130996700 gate-tiny-pc8-proof1，Rust5c20b99c...不变，Lean3bd53694...，真实提取14新定义/9局部定理已静态核对；尚未完整Lean/axiom/roundtrip。最终确认次数仍0。

最新完整官方捕获official-score-hi快照29680，查询18:14附近，计算18:12:14，freshness unknown；#612份额20.524717%，规则policy未变。其前29678对29677稳定字段逐项一致，Luna审计及全部raw保存。每次后续当前投影前重新捕获。

最新提交5ff84aa8已推送，HI/J原始回执和新评分待下次提交。官方source/contract/encoder/pins阅读副本未改；临时诊断副本单列。

账户北京时间17:56真实used11%/剩89%，仅共享读数，不当任务独占消耗；0重置/购买/正式上传/签名/注册。本轮推送仅实验分支。结束必须刷新看板、研究方法、round25报告/索引，核对原始回执与成本并project.py check。
