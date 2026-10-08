# 第十二轮：浅链表示与独立确认

执行规则见 [AGENTS.md](../../AGENTS.md)。北京时间2026-10-08 20:02起记账（向下取整，含准备），本窗22:02截止。起点main `b713727`，实验分支 `codex/round12-frontier`。预算及实际变化见 [budget](../../evidence/round12/budget.json) 和 [research-state](../../evidence/round12/research-state.md)。

## 当前结果：有小幅重复信号，仍无新前沿或奖励证据

本窗收束时，已完成5份不同Rust的测量与一份冻结版本独立确认，共3次实际R12性能作业、62个公共配对进程。另1次误派发的旧轮回放自然成功结束，有16个额外配对进程，单独归档，不计作新候选成绩。所有新候选完成官方提取和444有限检查；没有新完整Lean gate被运行或接受，没有正式上传、admission或新奖励记录。

最接近的是 `r12-fast-pc507-abs15`：发现阶段对公开#507均值快0.355395%，新runner四块独立确认快 **0.323029%**；相对同源码PC副本快 **0.106563%**，3块改善、1块小幅回退。公共只在bundle.min.js.txt少1字节（大小轴−0.000007143pp）。这些是重复小信号，不是官方95% bootstrap admission。

独立确认同族投影为 **0.432864972 / 36.685601872%**，最终快照29141下仍被#514支配；保持该大小时需严格越过0.432268208，从这次投影还需约 **0.137864%** 时间缩减。公开到正式的同族迁移仍是INFERRED，stage2结果UNKNOWN。发现阶段和独立确认分别保存，未用发现成绩替代独立读数。

| 候选 | 相对同场父版总时间 | 公共大小变化pp | 验证／决定 |
|---|---:|---:|---|
| wordhead | +1.780385% | 0 | 444 token/decode等价、提取、公共同输出；关闭该版 |
| strideword | +0.222246% | 0 | 同上；唯一改动路由的parser慢约57–59%，关闭该版 |
| pc507-prev16 | +0.994149% | 0 | 444等价、提取、公共同输出；距离编码工作未换来总时间收益 |
| pc507-abs16 | −0.231339% | 0 | 444 decode-only、提取；实际有限/public仍同token；相对同源副本一慢一快，未晋升 |
| pc507-abs15发现 | −0.355395% | −0.000007143 | 444 decode-only、提取；允许搜索/token变化，实际仅1公共文件变化 |
| pc507-abs15独立确认 | −0.323029% | −0.000007143 | 新runner四块、444解码通过；有小信号但未进入预测前沿，无完整gate |

## 实际机制与取舍

wordhead在hash和probe之间携带完整输入字，减少重复加载，但额外状态／调度成本没有取得收益。父版实际有2,436,186次run1搜索、4,019,230次ahead读取；读取次数减少不能直接换成加速。具体寄存器或缓存归因没有硬件计数器证据。

strideword把逐字节延伸换成现有common_from。真实weights-bf16.bin有92,349次三字节前缀命中，却总共只延伸442字节，**没有长度>=11的匹配**，即没有种子之后的完整8字节块。该输入parser中位数由约1.20/1.22ms升到1.92/1.91ms。关闭此实现，不从搜索次数推断宽比较机会。见 [机制读数](../../evidence/round12/mechanism-conclusions.json)。

#514支配后，官方公开了#506/#507的原版Rust与Lean。本轮保留原响应、字节SHA和作者hotkey。#507原路由包含精确输入长度；沿用而未增加新长度，仍不能推断私有迁移保证。距离16位重访明确区别于R10的D深搜索两张表：本次为PC浅链depth1/2的一张表。绝对模位置版本随后去掉每次插入的距离编码，恢复出的地址仅为hint，原pc_f_try保留严格递减、距离、输入界和实际字节验证。

各候选的来源、机制、重访条件和精确文件见manifest。复制父证明不继承其通过状态；strideword／prev16适配稿及两个模位置稿均未编译，所有完整gate仍NOT_RUN。

## 独立确认与条件gate

冻结abs15 Rust `093d2fc36678d9598aa24df3cef444ecf413e712ef1068ff2da4623096653b14`、Lean `ff47a7025633a831438bd29ee1a7c79842dad1828a74249afa570bfd00598716`（完整正确值以 [confirm-d](../../evidence/round12/confirm-d.json) 为准）。confirm-d只用新runner四块反馈：均值改善两个对照、各至少3/4块改善、同族投影进入冻结官方快照前沿，全部满足才分配原始完整gate。实际前四项成立、前沿项失败，正确跳过gate；workflow成功不等于Lean通过。见 [独立确认](../../evidence/round12/independent-confirmation.json) 和原始state的gate_confirmation_decisions。

## 作业与证据

| 作业 | Run ID | 结果 |
|---|---|---|
| 误派发旧R11 probe-a | 37775674308 | success；16配对进程；独立记为旧轮回放 |
| R12 probe-b | 37776887371 | success；3新Rust、18配对进程、原生计数与提取 |
| R12 probe-c | 37779759066 | success；2新Rust、16配对进程、444 decode-only与提取 |
| R12 confirm-d | 37782962022 | success；冻结abs15、28配对进程、未分配完整gate |

首个派发脚本复制时漏改experiment_round=11常量，实际回放旧轮；修正后的作业以r12 artifact前缀、真实输入和冻结Git对象核对。失败配置与旧回放均保留，不混入新候选或独立确认。用户明确允许云端推送，并说明仓库已公开；每次dispatch从GitHub元数据核实public，allow_private保持false。初始最多4次授权已用完；后获准的第5次没有实际启动。

官方完整起始快照29107有523 Pareto行、497 leaderboard行；中途29121有530/499行。最终快照29141有533 Pareto行、504 leaderboard行。三次均完整分页、原始哈希核对，API freshness仍unknown。以 [官方原始回执](../../evidence/round12/official-final/receipt.json)、[首四次字节审计](../../evidence/round12/final-byte-audit.json)、[复算总表](../../evidence/round12/final-summary.json) 为证据，不宣称finalized链状态或到账。

## 已准备但未测的最后布局版本

`r12-fast-pc507-pad64`把abs15的前驱数据区向后偏移32个u16（64字节），所有逻辑索引仍模32768；最大物理索引32799小于32800。只这一份布局，不做padding扫参。它针对两张power-of-two表的相对对齐，但编译器可能改变数组次序，需查实际库机器码及配对总时间。原语义由偏移映射保持只是INFERRED；本地source-reversal／哈希／配置通过，Rust原生、提取、Lean、性能均UNKNOWN。

用户已明确允许额外1次且仍按原22:02截止。收到授权后准备了最多3分钟native-only入口；实际派发前时限检查因剩余不足而拒绝，**第五次没有发出**，不能记为成功、失败CI或有效测量。源、证明稿和probe-e已保存，原生等价、提取、性能与完整gate均NOT_RUN。原始预算拒绝记录见probe-e-budget-refusal.json。

本轮整体上榜／奖励目标尚未完成。

最终原始文件审计225份通过，冻结Git对象、源码/证明哈希、作业/批次和条件gate决策绑定通过。累计成功job3051秒，账单未查询。所有实际CI均已终止；预算内没有后续作业。全局上榜／奖励目标保持未完成。
