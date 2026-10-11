# R24 续跑状态

## 最终确认已收齐，仍在固定窗口内收尾

固定窗口：UTC 2026-10-10 19:28:08 至 2026-10-11 05:28:08，北京时间03:28:08–13:28:08。不得重新计时。10%与15%稳定份额目标**未完成**；未正式上传，admission／私有成绩／正式可支付份额UNKNOWN。当前没有运行中的CI。

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
