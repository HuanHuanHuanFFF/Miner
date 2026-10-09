# 第十五轮：三小时、竞赛池至少1%

后续状态更新：研究已按用户要求提前停止，23个作业全部终态收齐，178个公共配对进程与一份精确完整gate通过。用户另行授权使用round3 hotkey正式提交；2026-10-09北京时间20:37收到#573回执。第十六轮启动时独立读取的官方快照29346（北京时间20:53计算）显示gate及admission通过、在前沿且可支付，竞赛池份额为**1.73651655%**。官方freshness仍为unknown；这不是链上到账回执。见[官方结果](../../evidence/round16/formal-573-start.json)、[完整gate](../../candidates/r15-550-base-only/VERIFICATION.json)、[23作业审计](../../evidence/round15/audit.json)。下文保留研究期间的观察与当时UNKNOWN状态。

窗口为2026-10-09北京时间16:46:11–19:46:11。用户明确目标口径为单个候选占竞赛奖励池至少1%，不接受两个hotkey合计；执行规则见 [AGENTS](../../AGENTS.md)。继承R14成果，保留两次既有机会；正式提交仍等待具体候选与份额审阅后的决定。

当前为研究中，未取得本轮新正式份额。初始官方快照为 [29289](../../evidence/round15/official-start/receipt.json)，freshness为unknown。公开的 [目标区域采样](../../evidence/round15/target-map.json) 只用于投入判断：#542/#553等中段参考约0.5%–1%的速度改善有机会超过1%；#550保持大小时约需8%速度改善。这是有限网格采样，不是全域最小门槛或私有保证。

## 当前动作

- R14已验证hash32上增加真实压缩工作：gain组合实际少1262B，depth2组合少21999B；两块原版配对结果分别为总时间−0.0629%和+0.5883%。depth2条件份额约0.3265%，未达1%；两者均完成540项有限decode和原版提取，尚未运行完整gate。见 [配对复算](../../evidence/round15/tradeoff-c-analysis.json)。
- 对原版#550做阶段诊断：一次预热加两次观察，显式阶段组合与原版完整parse在全部28文件逐token一致并可解码。诊断总秒数中base约78.3%、shape约21.3%，不是官方等权时间轴的占比。
- 后续函数诊断定位到SFsmallmatches和SFsolve分别约0.312s和0.231s；函数时间含嵌套重叠，不能相加冒充独立节省。由此准备base-only与shape-depth1两个受控变体，先用原编码器验证大小代价。
- 高压缩率变体的实际编码代价为base-only多830B、shape-depth1多468B；F批分别快18.586%和4.769%，条件份额约0.775%和0。见 [配对复算](../../evidence/round15/high-f-analysis.json)。
- depth3相对hash32累计少33797B，I批较depth2慢0.323%，条件份额约0.838%；depth2+gain约0.254%。前者进入一次新的四块确认，因为原版与同源码shadow两种发现校准分别约0.838%和1.040%。见 [复算](../../evidence/round15/deeper-i-analysis.json)、[确认理由](../../evidence/round15/depth3-confirmation-rationale.json)。
- 中段#553保留原路由，迁移PC专用U16前驱和32位hash，K批实测慢0.373%、多622B，无条件前沿份额，关闭该精确版本。见 [复算](../../evidence/round15/middle-k-analysis.json)。
- depth3+gain额外少2166B，但在相同时间坐标下条件份额降至约0.543%；保留源码，P批未派发。更小的输出不保证更高评分，见 [取舍](../../evidence/round15/deep-o-decision.json)。
- J/L诊断把高端剩余成本定位到后向规划，成本建模只占很少时间。range4改变归约顺序，ring1024改用512个活跃成本的镜像缓冲，两者均在28文件上保持逐token及编码输出一致。N/S批分别测实际总时间；证明仍未完成。见 [诊断](../../evidence/round15/profile-jl-decision.json)、[range4等价](../../evidence/round15/range-m-decision.json)、[ring等价](../../evidence/round15/ring-r-decision.json)。

## 确认边界

[预先冻结规则](../../evidence/round15/confirmation-policy.json) 要求新runner四块，正式锚与同源码shadow两种校准的中心都达到1%，且各至少3/4块达到1%，才分配完整gate。该规则允许真正的体积/时间交换，不要求压缩率更好的版本一定比父版更快。旧R14候选在这项新规则下未获晋级，见 [预检](../../evidence/round15/policy-preflight.json)。

10:36:11UTC冻结新方向，预留70分钟复测、证明与收集；硬截止11:46:11UTC。公共条件份额不等于正式admission或已支付份额。

记录：[预算](../../evidence/round15/budget.json)、[状态](../../evidence/round15/research-state.md)、[已确认编码收益](../../evidence/round15/tradeoff-b-decision.json)、[原版阶段诊断](../../evidence/round15/profile-a-decision.json)。
