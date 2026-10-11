# R25 续跑状态

固定北京时间窗口：2026-10-11 16:06:21–21:06:21；原起点 main `48baf622`，实验分支 `codex/round25-fast-quality`，一个 worktree。执行规则见 [AGENTS.md](../../AGENTS.md)。

目标：快速端低成本改善压缩，争取稳定竞赛池份额榜首。新候选尚无成绩。R24 B 后续正式 #625 的旧快照份额不能作为本轮当前事实。

当前阶段（北京时间16:35附近）：已完成两圈原编码器质量筛选，首批原协议计时与end4完整gate进行中。最后 90 分钟预留精确冻结、跨 runner 独立复测、完整 Lean 和原版 gate 及交付；发现期可提前证明，不挪用该余量。

分工：Astra/xhigh 独立算法设计（`astra/`）；Sol/xhigh 实现（`candidates/r25-sol-*`、`scripts/build-round25-sol*.py`、`sol/`）；Luna/max 官方只读快照与来源检查（`official-*`、`luna/`及三份 capture 脚本）；主线程负责实验、验收、评分、提交和共享入口。工具允许主线程加三子线程同时运行，无嵌套。

关键旧反例：快速端 #595 系列多次高峰伴随零值；同源码参照足以改变判断。新增压缩必须计入 encoder 后果；局部 parser 计时不替代原协议。高信号先逐块重放评分与邻居切换，然后决定测量诊断及确认。

最新已捕获官方快照29673（16:32附近重抓仍相同，官方计算15:48:20，freshness unknown），612当前20.524717%；来源规则commit6bf303f1，公式重放误差<3e-17。原始目录official-feedback-a/，规则official-rules-start/。rank脚本使用严格大于所有旧几何份额；合格支付身份仍是条件，不称正式榜首。

当前候选：end4 原encoder对combo少7397B/-0.0328587pp，15文件体积均下降，原Lean接口可复用但编译未知；backtie少1964B/-0.00742976pp，15文件体积/token均下降；gap1少1007B/-0.00583408pp，保留文件级损失。tail4替换多6533B，暂停；tiny-tail少8B，保留微组件，暂停单项完整证明。全部性能份额尚未知。反馈在feedback-a-native.json、feedback-b-native.json和feedback-b-decision.json。

已结束收齐：38124303645 quality-a-native；38124536539 proof-a-extract（真实Funs/Types/Constants，end4和backtie提取成功）；38124984085 quality-b-native。

正在运行：38124524718 screen-a（两块9方法，共18配对原协议，25分钟job上限）；38125243582 gate-end4（原冻结pair，30分钟上限）。运行结束后用collect-round4.py pull，标准阶段gate，原版验收exact-gate。所有作业自然完成/超时，不主动取消。

下一动作：收齐screen-a，analyze-round25.py逐块用最新官方快照回放，再rank-round25.py计算严格第一及控制分歧；收齐end4 gate并用bind-round25-gate.py核验。Sol等待具体gate错误再修复，不制造改名pair；Astra做实质不同的候选保留机制设计。新public578已合法获取，但只有旧路由/参数改变，暂不作为新机制投入。

当前已推送提交9227639f；工作分支仍codex/round25-fast-quality，只有一个worktree。本轮0重置/0购买/0正式上传；账户设置阶段used5%（共享读数）。
