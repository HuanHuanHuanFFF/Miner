# 第十八轮研究状态

固定窗口：北京时间 2026-10-10 01:32:51—09:32:51；UTC 2026-10-09 17:32:51—2026-10-10 01:32:51。压缩上下文与额度重置不重计。新方向冻结点 UTC 23:12:51，最后140分钟留独立确认、两个完整gate和交付。

目标仍未完成：两个不同可提交候选，竞赛奖励池分别15%与5%；正式提交、注册、资金、签名不在授权范围。主目录 main 的未推送 b5cb035 已保留，本worktree从远端 e000933 建立。当前研究分支 codex/round18-frontier；可复核阶段已持续提交/推送，未推送 main。原版 sources/contract/encoder/pins/gate未修改。

当前官方快照29409，计算时间北京时间01:28:06，587条提交/552账户，freshness unknown；完整证据 official-start-live。当前官方scorer文本与本地一致，原始SHA差异只是CRLF，见official-code。目标地图 target-map.json：DNA高分窄窗仍对噪声敏感；573维持大小，有限采样约需16.5%时间下降达到5%、40.5%达到15%，不是全域或私有保证。

已完成：
- 37968740636 baselines-b-native：公开576/579/583/584的原编码器/解码，原作者及哈希保留在references/round18-public-*。539源码403，不绕过访问限制。
- 37968763899 ranges-c-native：40111987次范围查询，平均3.541项，常价段压缩不足；暂不实现全面RMQ。ranges-c-decision.json。
- 37969565393 repeat-e-native：136次完整DP、13362864位置，0次相同价格表/输入复算。停止精确重复缓存假设。repeat-e-decision.json。
- 37969110773 mechanisms-d-native：DNApack6仅genome多16312B；583abs15仅bundle.min.js少4B。均publicdecode通过，证明草稿。进入真实总时间筛选，未按大小单项否决。
- 37968372355 noise-a-diagnostic：失败已完整归档。原版隔离测量8进程完成；实际将exec测量引擎的进程请求CPU0却允许0-3，cpuset.effective也是0-3。首个multi的原始stdout因断言先于保存而遗失，不补造；stderr/context保留。只证明亲和性偏差，尚未证明噪声根因。

当前在途：
- 37969976740 screen-f：两个候选 r18-dna-pack6/r18-583-abs15，2镜像块，10版本/对照，540wholedecode、444DNA直接decode、原版提取。无完整gate。
- 37970399568 noise-g-diagnostic：修正保存顺序；2原版隔离块、4同进程未显式绑核块、4同进程绑CPU0块、2绑CPU0隔离块。不同协议分列，使用同一原测量引擎和encoder。40分钟作业上限。
- 37970737877 alternatives-h-native：r18-dna-literals（DNA路由纯literal）与 r18-579-base-tiny（去掉579通用SFshape，保留tiny选择），先核对原编码器大小。

工具：scripts/dispatch-round18.py BATCH --max-minutes N 只允许本研究分支/公开仓库/剩余窗口，默认通过已有 deflate-round9.yml 调用新round18可复用工作流。脚本都用既有gh_env凭据助手，不打印秘密。网络/提交需要exec require_escalated；已自动审核通过的授权不重复询问用户。scripts/collect-round4.py status/pull RUN diagnostics或gate --round18 --batch LABEL；实际语法是 --round 18。

新分析器 scripts/analyze-round18.py RECEIPT... --capture ... --output ... 核对原始SHA、11次rep、28文件、两轴、同源码ELF、逐块单独及同块联合几何。已在原R17完整回执上真实复算通过；analyzer-old-receipt-check.json仅分析器预检，不能计入本轮新测量。无任意压力情景。最终需按run与block展示峰值/中位/范围/零值/5与15达标次数/对照分歧，单独和同时加入的份额不可直接相加。

下一步：收齐H与F，按真实时间/大小重放评分并做敏感边界；读G诊断，区分实际绑核、共同分母、顺序效应。不停止其他路线。尚未为新候选跑完整Lean，至少预留最终两份精确pair gate；不能用提取或有限decode代替。

账户最新读数剩余99%、已用1%，未触发剩余≤1%。最多一次成功重置；工具没有指定卡的参数，当前可用卡实际到期也需再核验。共享账户用量不等于本任务成本。额度不延长窗口。

已用技能：huan-open-research及实验/数学/搜索细则；噪声调查使用diagnosing-bugs，历史份额重放和实际affinity检查均为red。当前3个解释已向用户展示：AllowedCPUs未限制实际mask、进程间incumbent漂移、方法顺序/缓存；以新观测区分，不能提前宣布修复。
