# 第十二轮研究状态

执行规则见 [AGENTS.md](../../AGENTS.md)。北京时间2026-10-08 20:02起记账（含准备），22:02截止。起点main b713727，干净工作区；实验分支codex/round12-frontier。预算见budget.json。

官方完整起始快照29107，523 Pareto行、497 leaderboard行，freshness unknown。#514速度0.43226820825565、大小36.65058590774305，#453保持大小的速度差约1.280%。当前官方规则仍要求两阶段、公理/原始obligation、速度优势admission和前沿支付分别验收。

本次独立机制：(1)wordhead把实际输入word从head hashing携带到probe，减少重复load；(2)strideword保留st_find的距离及三字节前缀守卫，借已有common_from按8字节延伸。先444有限检查、真实提取、两个顺逆序公共配对块和同源fast-shadow；不在首筛套用父证明通过状态。没有有用总时间信号就停止这版；值得确认则冻结并在新runner确认，再完整gate。

与旧R4 lazy-second-load/slotonly及R11 skipahead不同：wordhead改变循环间共享的数据，strideword改变stride路径的延伸单位。精确来源归属和source-reversal在候选manifest；源码/证明冻结在batch JSON。首批job35分钟上限，排队另外计入墙钟。

用户在本聊天明确回复“允许推送到云端验证；当前已改为公开仓库”。允许本轮实验分支推送及最多4次、每次35分钟手动runner验证；仓库visibility在每次dispatch前读取GitHub元数据，公开仓库保持allow_private=false。之前自动审批拒绝外发的尝试未执行，不通过其他路径绕过。

首个dispatch37775674308的CLI输入仍为experiment_round=11：复制脚本漏改无round前缀的数字常量。实际作业回放旧R11 probe-a而非新候选，已有r11 artifact确认；不取消，按既定35分钟自然结束。该作业消耗本轮授权4次中的1次，单独记录，不计作新Rust实测。本轮新probe-b合并wordhead、strideword与刚公开#507的PC浅链delta16重访，余3次用于筛选、冻结确认及完整gate。
#507公开提供新起点：旧R10 delta16在D深搜索两张表未获益；本次为PC浅链depth1/2、每输入一张表，固定链存储由128KiB减到64KiB。不是新机制发明，而是明确改变计算条件的重访。其原路由包含精确长度，保持原版且未增加任何长度；公开到私有迁移仍UNKNOWN。
