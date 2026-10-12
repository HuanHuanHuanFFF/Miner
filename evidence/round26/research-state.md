# R26 当前状态

检查点 UTC **2026-10-11 23:58**。固定研究窗口为北京时间 **2026-10-12 05:06:52–13:06:52**（UTC21:06:52–次日05:06:52），不能重新起算。已用约2小时51分钟，剩约5小时9分钟；最后2小时预留冻结、原完整gate、独立确认和交付，新的研究派发止于UTC03:06:52。详见budget.json。

目标：两份不同候选单独条件投影稳定达到竞赛奖励池5%／10%，另算联合前沿；正式可支付结果仍需另行授权上传后的证据。当前两个目标均未完成，R26完整gate和冻结后独立确认均未运行。

## 当前工作与已知结果

- 唯一worktree，分支codex/round26-stable-pair；main保持48baf622。最新已推送85a9be62；root统一Git与CI。默认两路线，第三角色只用于具体验证瓶颈，不嵌套。
- route_a（Astra/xhigh）：A8链扩展原两块慢2.3244/2.5317%，暂停。A9在线距离码tiny2292B，比combo少195B，编码总clone/lookup仍高于combo；原quality成功、后置observer占位编译失败，单独fix成功，原failure保留。A10单次第二位置少6470B/.028152pp但多33145token、约60万额外验证，10文件小/16同/2大，停止paired与lookahead扩展。613/631/641静态比较主要是旧路由/预算交换，不派盲对照CI。当前获root批准准备一个固定4096×8完整PC索引row的父轨迹影子判别：空tag免源读机会、固定验证预算、原赢家丢失/3字节风险/额外维护，先观察，不建候选。
- route_b（Sol/xhigh）：B7缓存、B9完全状态重复都已关闭。B10贪心拟合+12213B/.039518pp；B11端点entropy拟合追回部分但仍+4555B/.016605pp，且新fit+末轮诊断成本几乎抵消原节省，两者均NO_GO paired/proof，不继续恢复原架构。当前获root批准准备原552 A反向续接的低价重叠候选观察（B12），不改原递推和token，先判断实际packed-best/长度域覆盖再定是否实现。
- score_verification（Sol/xhigh）已完成评分核验及有限计时诊断并停等。ROOT追加重要范围校正：raw process_affinity由外层Python driver记录，不是engine；原sandbox另请求AllowedCPUs=0，实际engine生效CPU/cgroup未记录。数值和原因UNKNOWN均不改变。证据measurement-diagnosis/affinity-scope，诊断草案v2仍未实现/启动。
- range_review（Astra/xhigh）约7分钟有限审查完成并停等。R10 prefixmask→A直接移植NO_GO，存在packed23位顺序反例；guard需要额外max/维护。旧A映射552七文件同价格段均宽2.29，不能当当前轨迹；root独立重放23输入SHA/有限模型一致。无新候选/CI。
- interval_review早先约8分钟短审已结束：前向长域事件扩边，当前提案NO_GO。此时仅两路线活跃。

## 最新官方与份额

完整捕获 **29805 official-loop3/**，计算UTC23:23:59.408586、查询约23:37。API freshness=unknown，评分政策compression-policy-c255effb7d5afeef未变。所有原协议已在all-analysis-29805.json重放。此前29799自标stale的原捕获及所有旧快照保留，不改写。

五次标准运行的原始逐文件reps按同一29805重算：all-analysis-29805.json／role-summary-29805.json，84份配对进程。6份主候选各只有1runner两发现块，主参照投影全0；hash17与allow-near影子校准各第一块约1.572506%／1.481724%、第二块0。控制副本、校准视图不增加主样本或runner。全部仍未达到5%，不能用平均坐标或峰值晋升。

629与628源码/证明逐字相同，作为迁移分歧参照，不算两个候选。新公开548与552主机制相同，来源和作者已存references/round26-public-548，未单开实验。外部libdeflate/zstd只读机制比较及精确版本在external-mechanisms/，没有移植竞赛encoder。

## 资源、失败与下一步

27次已派CI均已自然结束（24成功、3失败），未取消。audit-checkpoint-02.json核对678文件／73.70MB，16份不同Rust；candidate-ledger-29805.json区分6份做过原协议计时与10份未测份额UNKNOWN，按Rust去重，保留精确证明哈希。无R26完整gate或独立确认。三失败为B3初版编译、A3末尾summary（18份计时完整）、A9后置观察器（28×5质量完整，另有只补observer的成功run）。

账户上次真实读数UTC23:14:26：已用35%、剩65%，共享窗口，不是任务独占成本。重置0、购买0、正式上传/注册/签名/链支出0。

继续两路线循环，先消费A8/B9反馈再选新机制。值得晋升的候选冻结精确Rust/Lean，通过原版提取、原obligation、公理白名单及roundtrip完整gate，再安排新runner独立原协议确认（计划至少3runner各3主块，实际需按剩余时间调整并诚实标记不足）。保留最低、中位、范围、零份额、达标次数和同源码分歧，所有公共份额仍为条件估算；正式收益UNKNOWN。结束前刷新看板、方法结论和任务入口，审核原字节/实际消耗并按授权提交推送实验分支，不自动merge或正式提交。
