# SN66 DEFLATE 竞赛工作区

目标是优化可验证的 LZ77 parser，争取 Conjectures.io 的可支付 Pareto 前沿。项目执行规则统一在 [AGENTS.md](AGENTS.md)，资料按任务查找。

| 要做什么 | 从这里开始 |
|---|---|
| 继续优化与查重 | [任务索引](docs/TASK_INDEX.md) → 最近轮次；先看正式结果与[方法总览](docs/research/optimization-methods.md) |
| 回看 fast3、H16、bucket2 等选择理由 | [优化方法总览](docs/research/optimization-methods.md) |
| 运行或诊断公共验证 | [验证环境与入口](docs/validation.md) |
| 核对比赛、提交和奖励机制 | [比赛与提交入口](docs/competition.md) |
| 查历史文件或老路径 | `python scripts/project.py find H16`；`python scripts/project.py resolve ROUND9.md` |

最近归档更新于 **2026-10-10**。正式结果采用已保存快照 **29394（00:37:57 +08:00）**；以下历史份额都有对应快照，实时状态需查询官方。

- **base-only／#573**：正式 gate 和 admission 通过，曾在快照29346取得竞赛池份额1.7365%；后续快照29388为0.4774%。[正式结果](evidence/round16/formal-573-start.json)、[预测回测](evidence/round17/formal-calibration-backtest.json)。
- **DNA nofold／#582**：修补 Lean 后公共及正式 gate 均通过；正式两轴被#539支配，快照29394份额0%。[精确文件包](candidates/r17-dna-nofold-proof1)、[正式结果](evidence/round17/formal-582/result-summary.json)、[第十七轮报告](docs/rounds/round17.md)。原版DNA的旧Lean失败记录保留，不能与修补证明混用。
- **fast3／#453**：曾有正式份额及奖励，用户已确认历史到账；快照29388已退出前沿。[第三轮](docs/rounds/round03.md)。
- **H16-small／#474**：正式 gate 通过、admission被支配。[校准记录](evidence/round6/formal-474/calibration.json)。
- **近期复用结论**：份额峰值不能替代独立确认；#533/#539之间的窄区间可触发评分跳变，原始时间与大小、同源码对照、公共gate、正式admission分别核实。[波动诊断](evidence/round17/dna-variance-diagnosis.json)。

文件分工：

- `docs/`：任务目录、历轮报告、机制和环境资料；`docs/history/` 为历史初始化记录。
- `candidates/`：可回溯的源码／证明包；`references/`：公开参照与作者归属。
- `evidence/roundN/`：批次、原始回执、分析和冻结快照；早期逐字重复文件通过路径映射定位。
- `scripts/` 与 `.github/workflows/`：生成、收集、复算和手动验证入口。
- `sources/`、`.registration-private/`、`.local-maintenance/`：本地忽略资料，不作为 Git 交付内容。

本次整理已把历轮分支合入 main，工作流改为手动启动。查询任务使用 `python scripts/project.py tasks`，检查文档、路径和配置使用 `python scripts/project.py check`；这些操作不会启动 CI。
