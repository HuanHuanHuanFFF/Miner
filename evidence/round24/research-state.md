# R24 续跑状态

## 最终确认已收齐，仍在固定窗口内收尾

固定窗口：UTC 2026-10-10 19:28:08 至 2026-10-11 05:28:08，北京时间03:28:08–13:28:08。不得重新计时。10%与15%稳定份额目标**未完成**；未正式上传，admission／私有成绩／正式可支付份额UNKNOWN。最后两份原生诊断也已收齐；当前没有运行中的CI。

研究分支`codex/round24-stable-dual`，工作区`D:/CodingProject/Bitget/.runtime/r24-worktree`。主工作树保留；不合并、不清理分支或worktree。普通commit带`[skip ci]`，按现有授权推送研究分支。

### 冻结交付

- A：`r24-609-root-word-price-proof1`；完整gate38099485452。Rust257fdd0d54ff0c3007c57f154fc91d92179d71cc5e0d920871e3fa5c4d780c80；Lean2108c3e042247eae8e6e0433155b830c085de736d32d80209092ef990f6700ca。
- B：`r24-609-fast-adaptive-proof1`；完整gate38104425023。Rustef3268f4b4183b50af7825e505266c7dc05b49e9bb1aebb1f642a5609fc6423e；Lean09f79e1d6b4d60bdcc692425a7baae6503f3995f8cc6f9937d7f23a347e9e20e。
- 两份均已通过原版重新提取、原始obligation、公理白名单及roundtrip；原Lean900秒限制不变。冻结后未修改Rust/Lean。B在两个匹配函数增加短匹配自适应搜索及对应Lean循环迁移，公共输出比A少69B，是真实不同实现。
- `review-packages/packages.json`含已核验的两文件ZIP及SHA；不要重写已有审阅包。source-delta-audit.json与两份diff保留。

### 独立确认与当前分析

`38106900587/confirm-final-1`、`38106909000/confirm-final-2`、`38106920250/confirm-final-3`全部success并已收集。GitSHA d05e119ba5b9162cc0d9063bbc454a35bd701862，冻结时间UTC02:53:23，三份均之后启动；不同GitHubrunner/jobID已核对，不宣称不同物理host。

每候选3runner×3块=9主块。A额外有fast-stack父alias和ownshadow，B有ownshadow；副本和三个参照视图不增加独立样本数。原协议每文件1warmup/11measured，108最终配对进程。

快照29647，computedUTC03:43:07，捕获UTC03:55，freshnessunknown。`confirmation-29647/summary.json`为当前完整汇总，另有main-blocks、same-source-aliases、joint-blocks、per-file-total-times四CSV。analysis/anchors-confirmation-29647及原始jsonl是复核入口。两种联合工具PASS18。

|候选|参照|最低/中位/最高条件份额|零/目标次数|
|---|---|---|---|
|A|609|3.142733/3.199050/3.781004%|0/9零；0/9达10%|
|A|609影子|3.134216/3.167952/3.704145%|0/9零；0/9达10%|
|A|607|0.170855/0.333928/0.472995%|0/9零；0/9达10%|
|B|609|2.713093/3.590919/3.978665%|0/9零；0/9达15%|
|B|609影子|2.604751/3.525488/3.886660%|0/9零；0/9达15%|
|B|607|2.593366/3.227289/3.764666%|0/9零；0/9达15%|

所有alias也无零/达标判断分歧，但B实测同源码最大速度轴差5.832211%。`confirmation-control-final.json`四角诊断主要定位数值变化于incumbent分母，不是已确认底层原因或新成绩。包含alias后全视图最低仍A0.170855/B2.593366%。A609影子alias最低3.120157%，B609alias最高3.987944%，均保留。

联合609主中位A0.280486%、B3.488968%；607中位A0.225926%、B3.821257%，不可相加独立估算或中位数充当联合合计中位。

### 已完成审计和正在做的收尾

`audit-confirmation-complete.json`：80dispatch全部收齐，1239原始artifact文件140389842B、444原协议配对进程、39种R24 Rust哈希，runner总942.6667分钟。这是并发作业时长之和，不是研究墙钟或金钱。失败原样保留。

看板已按29647固定刷新：`evidence/dashboard/20261011T040557472726Z`，6历史正式提交，累计10.242238300α（API记录非钱包到账）。没有新增submissionID。官方源HEAD及5份源文件与起点逐字相同，含commitmetadata共6文件；final-comparison.json保留。

最后账户读数0%used/100%remaining，与先前17%used不连续；本任务未调用重置或购买，原因UNKNOWN，不将差值当本任务消耗。usage-0840m.json已去除账户身份与余额。

`closing-analysis-plan.json`预声明已有数据归因/邻居/目标几何，最多45分钟且留足最终刷新。`attribute-round24-final.py`已通过真实18个主候选原始JSONL校验，final-file-attribution.json保存逐文件统计；官方轴是逐文件总时间比的平均，不能改成总walltime或parser-only。

### 截止前剩余动作

1. 完成已有数据几何/反方核对、最终报告和方法积累，保留全部负例；不修改冻结候选。
2. 截止前重新capture最新官方快照与规则；按该同一快照重算全部主块/副本/联合，并`update-dashboard.py --snapshot-id N`。
3. 刷新audit、package/source绑定、project.pycheck，检查主工作树／远端／CI状态；commit/push研究分支。
4. 到固定截止，更新budget/status为窗口结束且目标未完成，交付独立确认、完整gate、精确哈希、最新条件估算、成本与最高价值下一步。不能将公共条件估算写成正式可支付份额。

无正式竞赛上传、新注册、钱包签名或支出授权。无子agent授权，不派发。

## UTC04:30补充：最后的热路径与端点诊断

自动审批曾拒绝推送，要求核实远端与新增回执外发范围。只读核实origin是既有公开HuanHuanHuanFFF/Miner、父SHA与已推送分支一致，新增228文件无私密路径／凭据模式；push-review-local/remote.json保存。之后审批通过，4c1b3221、747c450b均已推送，未绕过审批。原始CI日志空格不格式化；源码／文档diffcheck通过，1878已提交原始／源码／包文件190749689B的Gitblob逐字审计通过，git-byte-audit-confirmation.json。

38111345139 closing-b-profile-native：冻结B真实函数观察器通过28文件token及解码一致，原始总parse3431.864ms，其中SFbase61.07%、SFshape38.45%，嵌套不可加。按原版逐文件时间轴权重作条件归因，SFshape约31.06–32.40%而非38.45%；此为模型，非实测省时或新成绩。closing-profile-analysis.json。

38111633233 closing-base-native：新`r24-609-base-endpoint`只让Zmain返回完整SFbase、去掉SFshape，Rusta07a4780010619907f04eaaf2fc9d8a444aef698f7be9b86c6558bf8e4496ffb，Lean草稿88612c57659d99f8b3565ae7e8bdc1557a06c0a1e11e0a1337dfa3fcb71622bf。28文件原encoder/decode通过，但比A多1558B。条件质量34.099826/34.100048，需要时间轴约2.825/2.385才达10/15；原profile理想删除SFshape模型仍4.483–4.838。停止该精确端点的原协议计时／gate；其时间UNKNOWN、Lean未编译，不能叫零分实测候选或最终第三份。两个被冻结交付pair不变。closing-base-feedback.json与预声明plan保留。

累计dispatch现在82，先前80次审计是中途值，最终audit要重跑。32种原协议已计时Rust不变，总源码哈希将增至40。正式目标仍未完成，剩余工作为最新榜单重放／同快照看板、最终审计和截止交付。

## UTC04:46 收尾复核进展

最新checkpoint快照29650（computedUTC04:12:17，captured约04:31），按此重跑全部主块/副本/联合及32种已测Rust；A/B统计逐项与29647一致。confirmation-29650、all-measured-29650保留新输出；看板同29650累计10.311602623α。

82run最终诊断后审计：全部收集、1248原始artifact文件141780700B、444原协议paired、40不同R24Rust、944.3runner-min。audit-closing-diagnostics.json。新baseendpoint没有原协议计时，也未证明，不混入32已测候选。

fast-headroom-29650是现有screen-a实际reps的解析缩放／编码固定条件模型，factor1复核原实测。gain只有0.925–0.930窄段共同达10/15，chain3无共同段，factor0约1.3%；不是新成绩或实测成功概率。next-actions.md保留跨阶段共享机会的首检与R18弱共享／精确缓存零命中反例。

剩余必须完成：UTC05:15–05:20左右最终官方完整capture和规则查询，逐块重放+同快照看板、原始/Gitbyte审计、projectcheck、提交推送；截止UTC05:28:08结束窗口且目标UNMET。当前无活动CI，不新开预计无法收齐的作业。源文件最终pair不变。
