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

## 后续确认与第二轮

- [prove-a / 37682364860](https://github.com/HuanHuanHuanFFF/Miner/actions/runs/37682364860) 自然失败：seed/seed2 的独立复测重现质量退化，seed 证明有四处终止度量未关闭。不是超时；原证明未通过，不为这份低收益版本再开 gate。源与证明接口审计见 [interface-audit.json](../../candidates/r10-forward-seed-proof/interface-audit.json)。
- [struct-b / 37684506856](https://github.com/HuanHuanHuanFFF/Miner/actions/runs/37684506856) 自然成功：delta16 +1.2501% 总时间、大小不变；key5 +4.7821% / -0.0005412 pp，key6 +2.2458% / -0.0031119 pp，均停止扩展。空记录消除 -1.2342%、输出不变，另通过完整公共 gate 和八个固定输入；精确 pair 见 [VERIFICATION](../../candidates/r10-record-nonempty/VERIFICATION.json)。有限 token 等价仍不等于全输入 token 等价，源码边界见 [record-review.md](../../evidence/round10/record-review.md)。

六个已终止 CI 共 **114 个公共配对测量进程、十二份新 Rust**。汇总见 [third-loop-summary.json](../../evidence/round10/third-loop-summary.json)，其中按 runner 内配对比值计算提速，再对 runner 等权；重复证明版本按同一 Rust 合并。

- `row-c / 37688325585` 自然成功。行式长链比同场 scalar 慢约 10.9%，大小增加 0.0079558 pp。空记录消除独立复测约快 1.17%，输出不变；两 runner 四块方向一致，但仍未进入当前预测前沿。
- `rebase-d / 37689247460` 自然成功。全表相对位置重基准两块分别慢 1.9954%、3.9353%，平均慢 2.9653%，输出不变，444 个有限等价检查通过。停止该实现，不追加完整证明。
- `selective-e / 37693029351` 在 05:57:53 启动：原长匹配尾部额外查一个位置，及行式标签扫描改成整字掩码。后者保留旧行式版本作同场对照；必须相对 scalar 有价值，不能仅以改进一个慢版本作为继续理由。
- `cost-f / 37693861172` 在 06:05:15 启动：静态长度／距离成本必须严格优于同跨度字面量才接受种子匹配。这检验短而远匹配污染统计的机制，保留原 lazyseed 作同场对照。

两组现已自然成功结束，全轮累计 **8 个已终止 CI、15 份独立新 Rust、152 个公共配对测量进程**，见 [fourth-loop-summary.json](../../evidence/round10/fourth-loop-summary.json)。新增结果：

| 候选 | 相对同场 scalar 总时间 | 大小变化 pp | 结果与决策 |
|---|---:|---:|---|
| endprobe | +0.0734% | −0.0017765 | 16 文件共少 319 字节，其余不变；两块时间变号，不宣称稳定免费，保留小幅质量备选 |
| row16-mask | +7.0641% | +0.0079558 | 比同场 row16 快 4.2889%，但仍慢且大；444 原生等价与公共同输出通过，关闭行表路线 |
| costseed | −3.0988% | +0.0656117 | 比 lazyseed 追回约 29% 的大小损失，同时更慢，关闭种子统计路线 |

endprobe 在 28 公共和 84 固定生成输入上检查了原首遍计划／节点保留、额外位置与字节匹配以及解码；公共额外 13,926 节点、23,234 候选并不等于实际节省字节。costseed 在 18 公共 D 路由与 66 生成输入上保留原 rs，质量差距仍存在。两组都只执行了提取和有限检查，**没有完整 Lean gate**。

06:16:26 启动 `cpu-g / 37695105461`，比较已验证 record 基础上的统计成本缓存与链指针预读；06:24:19 启动 `restore-h / 37695964878`，把原 DP 的插入流水迁入 D，或恢复迁移时丢失的原类别键长／更新／减半配置。这些是两项独立对照，不在结果前叠加。前者保留实际基准程序的机器码文本，后者的模型恢复仍保留 flen16 稀疏首遍，不能称为原 DP 计划的完全恢复。它们尚待性能筛选和必要的精确证明。

## 几何前沿与当前 hotkey 的支付边界

最新完整快照 **27641（06:26:41 +08:00）** 共 494 行、76 个前沿点，现有 #453 仍在可支付前沿。官方规则只支付同 hotkey 最早的前沿提交：新均衡点若未使 #453 退出前沿，即使几何份额为正，沿用该 hotkey 的新点额外份额仍为 0。详见 [payability-notes.md](../../evidence/round10/payability-notes.md) 与 [最新重放](../../evidence/round10/payability-late-research.json)。新增前沿 #492/#493 位于较慢一端，均衡附近阈值未变；这次 weights/current 也不与固定分页同一快照，不能拼成链上结论。最终会再次刷新该状态。

附近 #375/#418/#422/#443/#489 的官方源码接口均明确返回 `SOURCE_WITHHELD`，前沿提交尚未开放源码。已保留响应和时间／哈希 [审计](../../evidence/round10/public-neighbor-audit.md)，没有根据坐标推断它们实现了什么优化，也没有访问未开放代码。

目前没有新正式提交或资金动作。最终需要收齐全部 CI、冻结最好源码／证明对、跨运行复测、刷新完整官方快照，再给两轴、条件前沿、具体缺口和是否达成研究目标；这些仍待完成。
