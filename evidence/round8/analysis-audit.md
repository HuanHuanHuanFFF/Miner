# Round 8 汇总审计

范围：静态检查 scripts/summarize-round8.py 与 evidence/round8/frontier-targets.json；未运行 CI、未改源码。实际 R8 full/suffix source SHA 已由主线程核对，分别以 df40...、e952... 开头。

## 实质结论

1. **当前 full 与 suffix 不会跨组串 gate。**  
   [summarize-round8.py:97-110](../../scripts/summarize-round8.py) 按 parse.rs SHA 分组；full/suffix 的 Rust SHA 不同，因此属于两个组，组级 any(accepted) 不会把 full 的通过传给 suffix。JSON 的 gates 明细也保留 candidate 与文件哈希，第134行说明 proof 状态只适用于精确 source/proof pair。

   仍有一处展示边界值得收紧：若未来同一 Rust SHA 有多个 proof 变体，组级 full_public_gate_passed（第126行）表达的是“该源码组至少一个 proof 通过”，不能解释为组内每份 proof 均通过；终端输出（第138-139行）只打印这个布尔值。主线程计划改为列出通过的 source/proof pairs，并在终端输出 candidate 与 proof hash，足以消除这层歧义。

2. **计数是独立 CI 运行数，不是物理 runner 数。**  
   [summarize-round8.py:100-106,117-126](../../scripts/summarize-round8.py) 每个源码组拒绝重复 CI run ID，并以不同 run ID 计数；这适合称为独立 CI 运行。若同一源码组的多个 proof 变体在同一 CI run 中重复提供测量行，第117行会断言失败，而非合并该次性能观测。建议保留一次每源码、每 CI run 的性能点，同时独立保留精确 proof 的 gate 记录；文案使用“独立 CI 运行”，不要外推物理机器独立。

3. **目标文件中两个 x=1.35 的 share 用的是不同 y 点。**  
   [frontier-targets.json:155-164](frontier-targets.json) 的表格点 public y=33.897417%，条件权重为2.6217%；[第268-277行](frontier-targets.json) 的推荐点 public y=33.89%，条件权重为4.1493%。两者公式一致，差异来自推荐点压缩更好；为避免读者只按 x 比较，建议让每个 share 同列 public y 和保守 x/y，或只给推荐点的条件权重。

   [第215行](frontier-targets.json) 的 current_highest_conditional_weight_points 列的是当前 API 快照的官方 pareto_weight_pct。建议改名为 current_official_frontier_weights，与 hypothetical conditional weight 分开。

## 公式检查

公共阶段聚合和安全场景未发现算术问题：[summarize-round8.py:57-81](../../scripts/summarize-round8.py) 对每文件的11次 measured reps 取中位数，再平均每文件配对时间比和压缩率；[第118-126行](../../scripts/summarize-round8.py) 用各 CI run 的均值作平均点、用最差观测配对比乘1.02作时间压力项，并将大小压力写为 max(y + 0.01pp, public_y * 1.008)。第133-136行保留了 private corpus、线上 admission 与实奖未知的界限。

脚本将固定 --snapshot 的分页 ID 彼此校验，是可复现分析所需；不强制其永远等于抓取时的最新 pointer 并非问题。target 的 UTC/北京时间字段也标注正确。hypothetical share 仍只是当前几何评分下的条件数值，不是奖励预测。
