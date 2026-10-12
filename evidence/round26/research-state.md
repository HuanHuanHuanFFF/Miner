# R26 当前状态

检查点 UTC **2026-10-12 00:28**。固定研究窗口为北京时间 **2026-10-12 05:06:52–13:06:52**（UTC21:06:52–次日05:06:52），不能重新起算。已用约3小时21分钟，剩约4小时39分钟；最后2小时预留冻结、原完整gate、独立确认和交付，新的研究派发止于UTC03:06:52。详见budget.json。

目标：两份不同候选单独条件投影稳定达到竞赛奖励池5%／10%，另算联合前沿；正式可支付结果仍需另行授权上传后的证据。当前两个目标均未完成，R26完整gate和冻结后独立确认均未运行。

## 当前工作与已知结果

- 唯一worktree，分支codex/round26-stable-pair；main保持48baf622。最新已推送cb279a93；root统一Git与CI。默认两路线，第三角色只用于具体验证瓶颈，不嵌套。
- route_a（Astra/xhigh）：A8链扩展原两块慢2.3244/2.5317%，暂停。A9在线距离码tiny2292B，比combo少195B，编码总clone/lookup仍高于combo；原quality成功、后置observer占位编译失败，单独fix成功，原failure保留。A10单次第二位置少6470B/.028152pp但多33145token、约60万额外验证，10文件小/16同/2大，停止paired与lookahead扩展。613/631/641静态比较主要是旧路由/预算交换，不派盲对照CI。A11固定4096×8完整PC索引影子观察38187224205已成功：13活动输入局部longer均多于shorter，原赢家98.8324%保留，仍有7778驱逐及198个len3丢失；27.96%预取空tag、3923285次维护，计数域不同不能当加速。root批准一份实际row候选原编码器检查，不扫容量；route_a正在实现，尚无新质量或速度结果。派发后遥测范围文字澄清独立留addendum，原required预声明已恢复精确字节。
- route_b（Sol/xhigh）：B7缓存、B9完全状态重复都已关闭。B10贪心拟合+12213B/.039518pp；B11端点entropy拟合追回部分但仍+4555B/.016605pp，且新fit+末轮诊断成本几乎抵消原节省，两者均NO_GO paired/proof，不继续恢复原架构。B12观察38186466076成功：12257237继承前缀有效，普通低价域仅333183条、11718位置改善旧best，fixed-only多数同价tie，停止补fixed gap。单一普通域B13 r26-b-552-overlap-select Rust9e0aa3b2...已于UTC00:20:39派发38187644253（20mincap），原packed和逐项wrapping-sub双min保原XL/XD及递推；原28encoder成功但+9B/+0.000009945pp，停止paired/gate。下一项获批固定稀疏discarded消费者观察，route_b准备中，未派CI。
- score_verification（Sol/xhigh）已完成评分核验及有限计时诊断并停等。ROOT追加重要范围校正：raw process_affinity由外层Python driver记录，不是engine；原sandbox另请求AllowedCPUs=0，实际engine生效CPU/cgroup未记录。数值和原因UNKNOWN均不改变。证据measurement-diagnosis/affinity-scope，诊断草案v2仍未实现/启动。
- range_review（Astra/xhigh）约7分钟有限审查完成并停等。R10 prefixmask→A直接移植NO_GO，存在packed23位顺序反例；guard需要额外max/维护。旧A映射552七文件同价格段均宽2.29，不能当当前轨迹；root独立重放23输入SHA/有限模型一致。无新候选/CI。
- interval_review早先约8分钟短审已结束：前向长域事件扩边，当前提案NO_GO。此时仅两路线活跃。

## 最新官方与份额

完整捕获 **29805 official-loop3/**，计算UTC23:23:59.408586、查询约23:37。API freshness=unknown，评分政策compression-policy-c255effb7d5afeef未变；UTC00:20:59最新identity查询仍为29805（official-check-0320）。所有原协议已在all-analysis-29805.json重放。此前29799自标stale的原捕获及所有旧快照保留，不改写。

五次标准运行的原始逐文件reps按同一29805重算：all-analysis-29805.json／role-summary-29805.json，84份配对进程。6份主候选各只有1runner两发现块，主参照投影全0；hash17与allow-near影子校准各第一块约1.572506%／1.481724%、第二块0。控制副本、校准视图不增加主样本或runner。全部仍未达到5%，不能用平均坐标或峰值晋升。

629与628源码/证明逐字相同，作为迁移分歧参照，不算两个候选。新公开548与552主机制相同，来源和作者已存references/round26-public-548，未单开实验。外部libdeflate/zstd只读机制比较及精确版本在external-mechanisms/，没有移植竞赛encoder。

## 资源、失败与下一步

30次已派CI均已自然结束（27成功、3失败），未取消。audit-checkpoint-0330.json核对713文件／75.62MB，17份不同Rust；candidate-ledger-0330.json区分6份做过原协议计时与11份未测份额UNKNOWN，按Rust去重，保留精确证明哈希。无R26完整gate或独立确认。三失败为B3初版编译、A3末尾summary（18份计时完整）、A9后置观察器（28×5质量完整，另有只补observer的成功run）。

账户上次真实读数UTC00:06:00：已用40%、剩60%，共享窗口，不是任务独占成本。重置0、购买0、正式上传/注册/签名/链支出0。

继续两路线循环：消费A11真实row实现和B13普通重叠质量反馈。值得晋升的候选冻结精确Rust/Lean，通过原版提取、原obligation、公理白名单及roundtrip完整gate，再安排新runner独立原协议确认（计划至少3runner各3主块，实际需按剩余时间调整并诚实标记不足）。保留最低、中位、范围、零份额、达标次数和同源码分歧，所有公共份额仍为条件估算；正式收益UNKNOWN。结束前刷新看板、方法结论和任务入口，审核原字节/实际消耗并按授权提交推送实验分支，不自动merge或正式提交。
