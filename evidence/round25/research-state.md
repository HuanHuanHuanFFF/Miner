# R25 续跑状态

固定北京时间窗口：2026-10-11 16:06:21–21:06:21；main基线48baf622，分支codex/round25-fast-quality，一个worktree。执行规则见[AGENTS.md](../../AGENTS.md)。目标为快速端低成本改善压缩、争取稳定竞赛池份额榜首；截至18:00尚未建立稳定正份额，更未达成榜首。

截止不重算。19:36:21拟冻结，最后90分钟保留完整原版gate、精确文件对独立确认与交付；20:06后不派新普通发现实验。已启动CI自然完成或既定超时，不主动取消。

分工：Astra/xhigh做tinyPC新helper Lean迁移，独占r25-astra-tiny-pc8-proof1等新增路径；Sol/xhigh完成duplicate-hop并审边界；Luna/max官方来源/算术审计当前空闲；主线程管理Git、CI、评分与共享入口。工具支持根加3子线程，无额外worktree，无嵌套。

已收齐15个成功作业：A native/screen/extract；B native；end4完整gate；C native/screen/extract；D native/screen；E counts；F origins；G prefix；H native；I native。screen原协议共56配对进程，均发现测量。所有raw保留。F一次dispatch前只读网络失败另存，不是CI失败。

性能：A end4/backtie/gap1各两块595主影子均0；end4对combo慢0.72%–0.92%。end4完整原版gate通过，Rust03ec0aa4.../Lean4ff09d16...绑定VERIFICATION，仅保留质量/正确性组件。C dual8少14674B但总时间慢3.02%–3.26%，595/影子/578视图全0；D wordtail与end4真实444有限等价和28文件输出相同，但主测时一块慢0.495%、一块快0.060%，份额全0，暂无收益，不扩展gate/asm。

诊断：E确定dual8主成本为额外8字节哈希/维护；F的2538080次record写入贡献53017次获胜提示，不可视为无用。H mainonly实际删除这些写入后，比dual8多17230B，比combo多2556B；耗时未知，仍给一次原协议代价端点实验。G发现父链短匹配遇相同8字节前缀时有有据机会，但长匹配也依赖同前缀链，因此不整体替换prev；J只在短主匹配、dp1、合法重复前缀时多看一次prev，保持所有插入。

最新质量信号I：r25-root-tiny-pc8 Rust5c20b99c...，只替换已有row12的ETINY为专用PC引擎，8头插入、正常验证过的emitter、原路由不变。28原编码器仅tiny-config变化2487→2155B，少332B，平衡压缩比例改善0.0988095pp；总时间/份额/完整gate未知。与历史584同文件体积一致不代表整体时间相同。

下一批：screen-hi共11方法/22原协议配对进程、2块，含H/I两候选副本、595主影子、combo、dual8实际父；proof-i-extract实际提取供Astra迁移；quality-j-native测试duplicate-hop。计划与冻结hash在对应JSON，提交后手动派发。任何高份额先重放最新快照、邻居切换与同源码差异，再做冻结后跨runner确认。

最新完整官方捕获official-score-d快照29677，计算北京时间17:09:45，freshness unknown；#612份额20.524717%，公式来自官方commit6bf303f1。此为最后已查证快照，不应当作18:00实时事实；每次当前投影前重新捕获。原始规则/快照和SHA全部保存。

账户北京时间17:56真实used11%/剩89%，仅共享读数，不当任务独占消耗；0重置/购买/正式上传/签名/注册。本轮推送仅实验分支。结束必须刷新看板、研究方法、round25报告/索引，核对原始回执与成本并project.py check。
