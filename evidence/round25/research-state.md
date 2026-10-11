# R25 续跑状态

固定北京时间窗口：2026-10-11 16:06:21–21:06:21；原起点 main `48baf622`，实验分支 `codex/round25-fast-quality`，一个 worktree。执行规则见 [AGENTS.md](../../AGENTS.md)。

目标：快速端低成本改善压缩，争取稳定竞赛池份额榜首。新候选尚无成绩。R24 B 后续正式 #625 的旧快照份额不能作为本轮当前事实。

当前阶段（北京时间17:12附近）：已完成A/B/C/D四批原编码器检查，A/C两批原协议计时和end4完整gate收齐；D计时与E机会域诊断进行中。最后 90 分钟预留精确冻结、跨 runner 独立复测、完整 Lean 和原版 gate 及交付；发现期可提前证明，不挪用该余量。

分工：Astra/xhigh 独立算法设计（`astra/`）；Sol/xhigh 实现（`candidates/r25-sol-*`、`scripts/build-round25-sol*.py`、`sol/`）；Luna/max 官方只读快照与来源检查（`official-*`、`luna/`及三份 capture 脚本）；主线程负责实验、验收、评分、提交和共享入口。工具允许主线程加三子线程同时运行，无嵌套。

关键旧反例：快速端 #595 系列多次高峰伴随零值；同源码参照足以改变判断。新增压缩必须计入 encoder 后果；局部 parser 计时不替代原协议。高信号先逐块重放评分与邻居切换，然后决定测量诊断及确认。

最新已捕获官方快照29676（官方计算16:59:58，freshness unknown），612当前20.524717%；来源规则commit6bf303f1，公式重放误差<3e-17。原始目录official-score-c/，规则official-rules-start/。rank脚本使用严格大于所有旧几何份额；合格支付身份仍是条件，不称正式榜首。此前29673/29674原始快照均保留。

当前候选：end4 原encoder对combo少7397B/-0.0328587pp，15文件体积均下降，原Lean接口可复用但编译未知；backtie少1964B/-0.00742976pp，15文件体积/token均下降；gap1少1007B/-0.00583408pp，保留文件级损失。tail4替换多6533B，暂停；tiny-tail少8B，保留微组件，暂停单项完整证明。全部性能份额尚未知。反馈在feedback-a-native.json、feedback-b-native.json和feedback-b-decision.json。

已结束收齐：38124303645 quality-a-native；38124536539 proof-a-extract（真实Funs/Types/Constants，end4和backtie提取成功）；38124984085 quality-b-native；38124524718 screen-a（18原协议配对）；38125243582 gate-end4（556.1秒、原900秒Lean、公理白名单、5325224B，VERIFICATION已绑定）；38125636793 quality-c-native（dual8少14674B）；38126033837 proof-c-extract（dual8提取成功）；38126014186 screen-c（20原协议配对）；38126399623 quality-d-native（wordtail 444有限等价及28token/encoder全同end4）。

正在运行：38126675905 screen-d（wordtail两块9方法，共18配对原协议，25分钟job上限）；38127500920 counts-e-native（dual8临时副本82字段事件计数，12分钟）。运行结束后用collect-round4.py pull，标准阶段gate，原版验收exact-gate，native/extract是diagnostics。所有作业自然完成/超时，不主动取消。

当前性能决定：A三份各2块主/595影子全0，end4对combo慢0.72%–0.92%；gap1慢0.12%–0.48%；backtie慢0.20%–0.34%。已保留end4质量+完整正确性组件，另两份暂停单项完整gate。dual8虽更小，C主块慢3.019%/3.264%，副本也慢且595/影子/578三个参照视图均0，停止完整证明；描述性拆分确认主要是被改动路径parser代价约3%，见astra/dual8-existing-cost-decomposition.json。计数E用于决定按需查询/更新是否有据，不能把callcount当提速。局部wordtail试图复用end4/end1共同字节，仍等真实总时间，不能靠有限相同输出称性能通过。

下一动作：收齐D并查询最新官方后analyze-round25.py、rank-round25.py；收齐E计数并交Astra分析。`analyze-round25-anchors.py`用于595/578迁移分列，C回测质量差约0.00719pp、时间约0.1%–0.57%，不可挑乐观口径。若有候选复制品的排序分歧先诊断，其他机制继续。Sol负责wordtail后续；Astra负责dual8计数后的机制；Luna数字审计已完成，可复用其做最终独立审核。

当前已推送提交80027989；工作分支仍codex/round25-fast-quality，只有一个worktree。本轮0重置/0购买/0正式上传；最近账户读数16:54为used8%/剩92%（共享读数，变化不当任务独占消耗）。轻量project.py check在17:00附近通过32任务、715链接、10手动workflow、342文件对。
