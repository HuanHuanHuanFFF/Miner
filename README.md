# SN66 DEFLATE 竞赛工作区

目标是优化可验证的 LZ77 parser，争取 Conjectures.io 的可支付 Pareto 前沿。项目执行规则统一在 [AGENTS.md](AGENTS.md)，资料按任务查找。

| 要做什么 | 从这里开始 |
|---|---|
| 继续均衡附近的优化 | [任务索引](docs/TASK_INDEX.md) → 第九轮；重点是前向搜索和初始规划 |
| 回看 fast3、H16、bucket2 等选择理由 | [优化方法总览](docs/research/optimization-methods.md) |
| 运行或诊断公共验证 | [验证环境与入口](docs/validation.md) |
| 核对比赛、提交和奖励机制 | [比赛与提交入口](docs/competition.md) |
| 查历史文件或老路径 | `python scripts/project.py find H16`；`python scripts/project.py resolve ROUND9.md` |

最近研究记录更新于 **2026-10-08**，使用已保存快照 **27127（02:14:49 +08:00）**。这里的排名与份额不是实时值。

- **速度端 fast3／#453**：有正式 admission 和历史奖励记录，用户已确认到账。源码在 [候选目录](candidates/r3-432-fast3)，来源与选择过程见第三轮。
- **H16-small／#474**：正式 gate 通过，admission 判定被支配；正式两轴和迁移系数见 [校准记录](evidence/round6/formal-474/calibration.json)。
- **最近均衡研究 scalar**：公共两轴 `1.400032 / 33.934366%`，相对同场 block1 平均时间变化 `−0.884%`，已过完整公共 gate；保守估值仍在前沿外。[第九轮结果](docs/rounds/round09.md)保留测试次数和边界。

文件分工：

- `docs/`：任务目录、历轮报告、机制和环境资料；`docs/history/` 为历史初始化记录。
- `candidates/`：可回溯的源码／证明包；`references/`：公开参照与作者归属。
- `evidence/roundN/`：批次、原始回执、分析和冻结快照；早期逐字重复文件通过路径映射定位。
- `scripts/` 与 `.github/workflows/`：生成、收集、复算和手动验证入口。
- `sources/`、`.registration-private/`、`.local-maintenance/`：本地忽略资料，不作为 Git 交付内容。

本次整理已把历轮分支合入 main，工作流改为手动启动。查询任务使用 `python scripts/project.py tasks`，检查文档、路径和配置使用 `python scripts/project.py check`；这些操作不会启动 CI。
