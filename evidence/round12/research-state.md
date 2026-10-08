# 第十二轮研究状态

执行规则见 [AGENTS.md](../../AGENTS.md)。北京时间2026-10-08 20:02起记账（含准备），22:02截止。起点main b713727，干净工作区；实验分支codex/round12-frontier。预算见budget.json。

官方完整起始快照29107，523 Pareto行、497 leaderboard行，freshness unknown。#514速度0.43226820825565、大小36.65058590774305，#453保持大小的速度差约1.280%。当前官方规则仍要求两阶段、公理/原始obligation、速度优势admission和前沿支付分别验收。

本次独立机制：(1)wordhead把实际输入word从head hashing携带到probe，减少重复load；(2)strideword保留st_find的距离及三字节前缀守卫，借已有common_from按8字节延伸。先444有限检查、真实提取、两个顺逆序公共配对块和同源fast-shadow；不在首筛套用父证明通过状态。没有有用总时间信号就停止这版；值得确认则冻结并在新runner确认，再完整gate。

与旧R4 lazy-second-load/slotonly及R11 skipahead不同：wordhead改变循环间共享的数据，strideword改变stride路径的延伸单位。精确来源归属和source-reversal在候选manifest；源码/证明冻结在batch JSON。首批job35分钟上限，排队另外计入墙钟。

用户在本聊天明确回复“允许推送到云端验证；当前已改为公开仓库”。允许本轮实验分支推送及最多4次、每次35分钟手动runner验证；仓库visibility在每次dispatch前读取GitHub元数据，公开仓库保持allow_private=false。之前自动审批拒绝外发的尝试未执行，不通过其他路径绕过。

首个dispatch37775674308的CLI输入仍为experiment_round=11：复制脚本漏改无round前缀的数字常量。实际作业回放旧R11 probe-a而非新候选，已有r11 artifact确认；不取消，按既定35分钟自然结束。该作业消耗本轮授权4次中的1次，单独记录，不计作新Rust实测。本轮新probe-b合并wordhead、strideword与刚公开#507的PC浅链delta16重访，余3次用于筛选、冻结确认及完整gate。
#507公开提供新起点：旧R10 delta16在D深搜索两张表未获益；本次为PC浅链depth1/2、每输入一张表，固定链存储由128KiB减到64KiB。不是新机制发明，而是明确改变计算条件的重访。其原路由包含精确长度，保持原版且未增加任何长度；公开到私有迁移仍UNKNOWN。

首筛37776887371成功结束：3份新Rust、18配对进程，三者444有限token/decode等价与实际提取通过，公共输出相同，完整gate均未运行。两块wordhead +2.2483/+1.3125%；strideword +0.6197/-0.1752%；prev16 +0.8931/+1.0952%。关闭这些固定源码的完整gate投入，适配稿仅保留UNCOMPILED。Stride真实延伸仅442字节，无长度>=11匹配，不能从搜索数量推导宽比较机会。
第三次授权job probe-c：在#507上两份模位置表示abs16/abs15，取消每次插入的距离encode/cap，恢复位置仅作为pc_f_try的hint。可能改变搜索/token，明确按444 decode-only检查，并统计token变化；原输入验证、路由和row设置全部保留。预先冻结两块总压缩计时及同源码PC对照；无可靠两轴收益就结束这版。余最后1次runner只用于值得确认的冻结版本及其原始完整gate。

模位置第三job37779759066成功：16配对进程，两个候选444 decode-only与真实提取通过；abs16无token变化，abs15仅bundle.min.js.txt变化且少1字节。对parent两块abs16 -0.1393/-0.3234%，abs15 -0.1649/-0.5459%，均值-0.2313/-0.3554%；对PC同源shadow则abs15 +0.2572/-0.4768%，未确认稳定。当前29121快照相同固定大小边界，abs15同族投影仍被514支配。
冻结同一abs15的Rust093d2fc..和Lean ff47a702..（以JSON完整哈希为准），confirm-d最后1次授权job做4配对块、444decode-only、同源PC对照；不混入discovery来判独立确认。只有fresh mean双控改善、各至少3/4块双控改善且当次同族投影入前沿时才分配原始full gate。否则明确保存NOT_RUN，停止该版本，不伪称完成证明或上榜。源已冻结，无新算法再扩展；截止22:02不变。
