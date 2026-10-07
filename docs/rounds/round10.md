# 第十轮：五小时结构研究（进行中）

执行规则见 [AGENTS.md](../../AGENTS.md)。本轮会话 ID：`01a117eb-0257-7f51-a1b9-a7621bdf16dc`，原始接续会话为 `01a11272-3ca5-75d3-aa0a-68376e856f18`。实际开始北京时间 **2026-10-08 03:50:52**，五小时截止 **08:50:52**；当前预算读数见 [budget.json](../../evidence/round10/budget.json)，路线变化见 [research-state.md](../../evidence/round10/research-state.md)。本页是阶段报告，尚非本轮最终交付。

## 起点与当前门槛

从已通过完整公共 gate 的 `r9-block-scalar` 继续。起始官方完整快照为 **27331，03:54:35 +08:00**，491 个 Pareto 条目、74 个前沿点；API freshness 仍为 `unknown`。原始响应及哈希见 [receipt.json](../../evidence/round10/official-start/receipt.json)，当前函数重放见 [frontier-start.json](../../evidence/round10/frontier-start.json)。官方前沿权重与本地公开 scorer 的最大误差为 `6.94e-18`，不证明线上部署代码逐字相同。

固定 scalar 输出时，同族 #361 校准需再快约 **6.074%**；按已声明的大小系数和最慢块加 2% 场景需再快约 **16.654%**。这些是推算门槛，不是私有集或奖励保证。

## 第一轮已完成的结果

两个 CI 均自然成功结束：`37679261323` / `explore-a` 与 `37680712729` / `rmq-a`。共六份新 Rust、40 个公共配对测量进程；每份候选两块，每文件一次预热和 11 次测量。所有指标从原始 reps 重算，包含 parser 和公共 encoder。结果见 [first-loop-summary.json](../../evidence/round10/first-loop-summary.json)。

下表均相对**同一 CI、同一块**的 scalar；不比较跨 runner 的绝对时间。

| 候选 | 机制 | 总时间变化 | 大小变化 pp | 决策 |
|---|---|---:|---:|---|
| forward-seed | 删首遍价格 DP，改用贪心统计种子 | −5.607% | +0.1351735 | 停止此种子扩展 |
| forward-lazyseed | 同种子增加一字节 lookahead | −5.132% | +0.0926915 | 质量损失仍过大 |
| forward-seed2 | 同种子后做两遍后向规划 | +9.545% | +0.0583781 | 比父版本更慢、更大 |
| finder-tag4 | 两槽精确四字节标签补充缓存 | +6.071% | −0.0013716 | 收益不足，停止 |
| finder-hash5 | 五字节最近位置补充缓存 | +4.484% | −0.0053775 | 新匹配有效，但叠加成本过高 |
| rmq8 | 已完成端点的八元素最小值摘要 | +5.133% | 0 | 同字节但变慢，停止 |

六者在同族校准与保守场景下均被支配，条件份额为 0。首两批的 `gate` artifact **未执行完整 Lean gate**（`gates={}`），不能用 CI 成功或 artifact 名称声称证明通过。

**VERIFIED：** seed 的原／新匹配记录流在 18 个公共 D 路由输入及 66 个生成输入上逐字相同；它的质量损失出现在后续种子／成本规划。tag4/hash5 各完成 444 个有限检查，检查解码、确定性、插桩一致性及所访问节点的原候选保留。rmq8 完成 444 个有限 token/decode 等价检查，公共输出也相同。三种代表及 rmq8 通过了官方重新提取，但并未因此关闭原始 Lean obligation。

**INFERRED：** 简单恢复原生 D 路由仍留下显著文本质量损失，不继续增加同类种子遍数。hash5 的 97,744 次公共新增中，92,650 次来自已有最佳长度 4..7；下一步检验替换原长键，而非叠加维护表。源与机制分析分别见 [forward-notes](../../evidence/round10/forward-notes.md)、[finder-notes](../../evidence/round10/finder-notes.md)、[原始资料检索](../../evidence/round10/research-sources.md)。

采样微函数计时包含计时成本和相互嵌套，甚至产生单项大于整体的外推值，不作为百分比分解。collect+seed 与旧前向的粗比较只作诊断，不能替代正式总时间。

## 正在推进的确认与第二轮

- [prove-a / 37682364860](https://github.com/HuanHuanHuanFFF/Miner/actions/runs/37682364860)：seed/seed2 独立复测与 seed 精确源／证明对的原始完整 gate。它在性能首批结果出来前启动；即使性能不够，仍收齐自然终态。源与证明接口审计见 [interface-audit.json](../../candidates/r10-forward-seed-proof/interface-audit.json)。
- [struct-b / 37684506856](https://github.com/HuanHuanHuanFFF/Miner/actions/runs/37684506856)：保留原初始计划，比较 16-bit 链距离、五／六字节长链键、空记录消除。delta16 与空记录消除要求有限 token 等价；后者另运行完整原始 gate。记录流省略的独立源码边界见 [record-review.md](../../evidence/round10/record-review.md)。

目前没有新正式提交或资金动作。最终需要收齐全部 CI、冻结最好源码／证明对、跨运行复测、刷新完整官方快照，再给两轴、条件前沿、具体缺口和是否达成研究目标；这些仍待完成。
