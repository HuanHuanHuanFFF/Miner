# 第二十五轮：五小时快速端低成本压缩研究

北京时间 **2026-10-11 16:06:21–21:06:21**，目标稳定冲击竞赛奖励池份额榜首。状态：研究进行中。执行规则见 [AGENTS.md](../../AGENTS.md)，预算与接手状态见 [budget](../../evidence/round25/budget.json)、[研究状态](../../evidence/round25/research-state.md)、[GitHub 接手回执](../../evidence/round25/github-start.json)。

起点 main `48baf622466792f4d505c5c06d5696f784e27b7a` 与 origin/main 一致，工作区干净、只有一个 worktree；远端公开、最近查询的作业均结束。使用同一 checkout 的实验分支 `codex/round25-fast-quality`。

先比较低成本质量机制与既有快速端负例，再做少量受控实现。新候选的公共条件估算、完整验收与正式可支付成绩分别记录；本轮不包含正式上传。

## 前两圈：实际压缩与取舍

本轮首次捕获官方快照29673，计算北京时间15:48:20、freshness为unknown；[原始响应](../../evidence/round25/official-feedback-a/receipt.json)与[评分源码](../../evidence/round25/official-rules-start/receipt.json)分列。该快照612为可支付榜首20.524717%，新626已进入快速前沿。纯scorer重放官方权重最大差异2.78e-17；[目标区域](../../evidence/round25/target-map-start.json)只是合成坐标网格，并非候选成绩。

两圈共五份不同Rust经过原encoder的28文件decode/真实字节检查；[首批逐文件结果](../../evidence/round25/feedback-a-native.json)、[第二批](../../evidence/round25/feedback-b-native.json)。相对精确combo父版：end4少7397B、均衡压缩率少0.0328587pp；backtie少1964B/0.00742976pp；gap1少1007B/0.00583408pp并保留文件级损失。替换尾key的tail4多6533B，暂停；tiny-tail只少8B，先留作微组件。[后两者取舍](../../evidence/round25/feedback-b-decision.json)。这些是质量筛选，时间、份额和完整正确性另行验收。

end4/backtie实际重新提取均成功，[原始模型与日志](../../evidence/round25/38124536539/proof-a-extract/diagnostics/research5/research.json)支持证明接口迁移；提取本身不证明完整Lean。后续end4通过原版完整gate，首批计时已结束，结果见下。

把R23旧快速组合的原始确认重放到29673，四个主块仍2次零、影子3次零，详见[历史数据当前快照重放](../../evidence/round25/historical-fast-rank-29673.json)。这是旧测量重算，不能增加本轮独立样本数，亦不能解释为成功概率。


## 截至北京时间18:02的阶段结果

下列时间变化来自单runner两块原协议的逐文件总压缩时间；这是发现样本，未增加冻结后的跨runner确认。份额是列明官方快照上的公共条件估算，正式成绩仍UNKNOWN。

| 候选 | 对实际父版公共质量变化 | 原协议时间变化 | 阶段决定 |
|---|---:|---:|---|
| end4 | 对combo少7397B / -0.032859pp | +0.720%～+0.924% | 29673两主块及595影子均0；保留通过完整gate的质量组件 |
| backtie | 对combo少1964B / -0.007430pp | +0.202%～+0.344% | 同次估算全0，暂停单项完整gate |
| gap1 | 对combo少1007B / -0.005834pp | +0.124%～+0.479% | 同次估算全0，保留逐文件损失，暂停单项完整gate |
| tail4 | 对combo多6533B / +0.029023pp | 未测 | 暂停该固定替换；没有份额测量，不能记0 |
| tiny-tail | 对combo少8B / -0.002381pp | 未测 | 保留小组件，未投入单项完整证明 |
| dual8 | 对combo少14674B / -0.050599pp | +3.019%～+3.264% | 29676主/候选副本/595影子/578参照均0；先诊断维护成本 |
| end4-wordtail | 与end4逐token及编码字节全同 | 对end4 -0.060%～+0.495% | 29677全0，未确认速度收益；444有限等价不替代完整gate |
| dual8-mainonly | 对dual8多17230B；对combo多2556B | 测量进行中 | 不因体积退步直接淘汰；测减少维护的真实代价端点 |
| tiny-pc8 | 对combo少332B / -0.098810pp | 测量进行中 | 只tiny-config改变；实际提取与证明准备并行 |
| duplicate-hop | 对combo少3497B / -0.016728pp | 测量进行中 | 单次有条件额外链跳；先总时间再决定证明 |

[首批评分](../../evidence/round25/rank-a-29673.json)、[dual8评分](../../evidence/round25/rank-c-29676.json)、[wordtail评分](../../evidence/round25/rank-d-current.json)保留主测与同源码对照。旧快照下结果不可直接称为交付时当前成绩。

end4的精确Rust `03ec0aa4e617d622755e85324a9d4fbc77ef74e6572485b3170e2790681ed8e6`、Lean `4ff09d168269ae8d9c93e602496b01078d2d0ec80f27d6cd16041d91a76c70a6`通过原始obligation、原900秒Lean上限、公理白名单及完整round trip；[绑定证明](../../candidates/r25-astra-end4/VERIFICATION.json)与[原始gate回执](../../evidence/round25/38125243582/gate-end4/exact-gate/exact-gate/gate-receipt.json)独立于性能结论。

### 用诊断选择下一次实验

E的临时观测副本与冻结dual8在28文件token/decode一致，数到4130586次8字节哈希/写入，其中2538080次来自匹配内记录。F继续区分来源，全部82个旧计数逐文件复核一致：记录来源贡献53017次成功提示，不能视为可免费删掉的冗余。删除记录更新的H真实多17230B，说明来源计数不能直接换算保留压缩收益。[E原始计数](../../evidence/round25/38127500920/counts-e-native/diagnostics/r25-dual8-counts/counts.json)、[F原始计数](../../evidence/round25/38128787484/origins-f-native/diagnostics/r25-dual8-origins/counts.json)、[H实际质量](../../evidence/round25/feedback-h-native.json)。

G在原combo上观察到61444次短主匹配/重复8字节前缀；最多8步的只读机会探测能找到部分不同来源，但长主匹配的同前缀节点本身也贡献有效改进。因此J只给短匹配重复来源多看一次prev，不改插入，不把只读8步探测直接部署成搜索深度。[G原始计数](../../evidence/round25/38129145575/prefix-g-native/diagnostics/r25-prefix-diversity-counts/counts.json)、[J预声明](../../evidence/round25/sol/duplicate-hop-predeclared.json)、[J实际质量](../../evidence/round25/feedback-j-native.json)。

I来自历史同输入原编码器证据：public584在tiny-config上比当前ETINY少332B。新候选只替换已有短文件路由中的引擎，保留原路由与其他路径，以父版已验证的正常emitter和独立PC插入函数实现。实际28文件只有tiny-config从2487B降到2155B；这是固定公共语料按文件平均的收益，不是私有集保证，也不从旧584时间猜测新候选耗时。[预声明](../../evidence/round25/cycle-i-tiny-plan.json)、[I原始质量](../../evidence/round25/feedback-i-native.json)、[HI计时计划](../../evidence/round25/cycle-hi-screen-plan.json)。


## HI/J反馈与下一缺口

北京时间18:14–18:15重新抓取[官方快照29680](../../evidence/round25/official-score-hi/receipt.json)，官方计算18:12:14、freshness unknown。[38个新增原协议进程](../../evidence/round25/analysis-hij-29680.json)与[按主候选统计的份额](../../evidence/round25/rank-hij-29680.json)已经逐raw重算。

H mainonly相对真实dual8父版快1.276%–1.456%，但相对combo仍慢1.120%–1.155%，且比combo多2556B，两块主/影子估算0；删除全部维护没有取得目标位置。J的12个目标文件全部变小，另外16个输出相同，但总时间增加0.617%–0.815%，主/影子估算均0，暂停该精确实现的完整证明。

I tinyPC主两块总时间增加1.574% / 1.682%，最新主参照份额0.071394% / 0%；595影子0.111155% / 0%。候选副本和真实时间全部保留，不能将四个别名观察当四块确认。实际总时间中位数逐rep分解发现：唯一改变的tiny-config，其解析增加仅贡献约0.178–0.193个百分点，而编码增加贡献约1.499–1.654个百分点；27个同输出文件不是主要来源。该分解是原始坐标变化的描述性恒等式，不是改造后的提速承诺或新官方成绩。

因此下一圈针对原encoder对token形状的成本，而非继续扩大匹配搜索。Astra检查tiny长度/距离符号及块树工作；Sol在R13已知反例约束下，对当前PC最终三字节匹配做未计时代码价格覆盖诊断，先判定是否有可实现的便宜规则。I完整gate已在发现结果前启动，仍按既定规则完成；质量组件与性能失败分别保留。详见[HIJ决定](../../evidence/round25/feedback-hij-decision.json)、[I原始分解](../../evidence/round25/cost-i-screen.json)、[H分解](../../evidence/round25/cost-h-screen-vs-combo.json)、[J分解](../../evidence/round25/cost-j-screen.json)。
