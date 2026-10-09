# 第十五轮：三小时、竞赛池至少1%

窗口为2026-10-09北京时间16:46:11–19:46:11。用户明确目标口径为竞赛奖励池至少1%；执行规则见 [AGENTS](../../AGENTS.md)。继承R14成果，保留两次既有机会；正式提交仍等待具体候选与份额审阅后的决定。

当前为研究中，未取得本轮新正式份额。初始官方快照为 [29289](../../evidence/round15/official-start/receipt.json)，freshness为unknown。公开的 [目标区域采样](../../evidence/round15/target-map.json) 只用于投入判断：#542/#553等中段参考约0.5%–1%的速度改善有机会超过1%；#550保持大小时约需8%速度改善。这是有限网格采样，不是全域最小门槛或私有保证。

## 当前动作

- R14已验证hash32上增加真实压缩工作：gain组合实际少1262B，depth2组合少21999B；两块原版配对结果分别为总时间−0.0629%和+0.5883%。depth2条件份额约0.3265%，未达1%；两者均完成540项有限decode和原版提取，尚未运行完整gate。见 [配对复算](../../evidence/round15/tradeoff-c-analysis.json)。
- 对原版#550做阶段诊断：一次预热加两次观察，显式阶段组合与原版完整parse在全部28文件逐token一致并可解码。诊断总秒数中base约78.3%、shape约21.3%，不是官方等权时间轴的占比。
- 后续函数诊断定位到SFsmallmatches和SFsolve分别约0.312s和0.231s；函数时间含嵌套重叠，不能相加冒充独立节省。由此准备base-only与shape-depth1两个受控变体，先用原编码器验证大小代价。
- 高压缩率变体的实际编码代价为base-only多830B、shape-depth1多468B，标准配对测量进行中。单纯省掉阶段的诊断比例不能代替总时间轴。
- 深度二的新反馈后，仅扩展一个真实前驱和一个gain组合：depth3相对hash32累计少33797B，depth2+gain累计少23791B，28文件编码及解码通过，已进入配对时间筛选。见 [原始编码收益](../../evidence/round15/deeper-g-decision.json)。
- 中段#553保留原路由，迁移PC专用U16前驱和32位hash；这是不同前沿位置上的有界迁移，先测实际大小，不把#514/#542旧速度收益相加。

## 确认边界

[预先冻结规则](../../evidence/round15/confirmation-policy.json) 要求新runner四块，正式锚与同源码shadow两种校准的中心都达到1%，且各至少3/4块达到1%，才分配完整gate。该规则允许真正的体积/时间交换，不要求压缩率更好的版本一定比父版更快。旧R14候选在这项新规则下未获晋级，见 [预检](../../evidence/round15/policy-preflight.json)。

10:36:11UTC冻结新方向，预留70分钟复测、证明与收集；硬截止11:46:11UTC。公共条件份额不等于正式admission或已支付份额。

记录：[预算](../../evidence/round15/budget.json)、[状态](../../evidence/round15/research-state.md)、[已确认编码收益](../../evidence/round15/tradeoff-b-decision.json)、[原版阶段诊断](../../evidence/round15/profile-a-decision.json)。
