# SN66 DEFLATE 竞赛工作区

目标是优化可验证的 LZ77 parser，争取 Conjectures.io 的可支付 Pareto 前沿。项目执行规则统一在 [AGENTS.md](AGENTS.md)，资料按任务查找。

| 要做什么 | 从这里开始 |
|---|---|
| 继续优化与查重 | [任务索引](docs/TASK_INDEX.md) → 最近轮次；先看正式结果与[方法总览](docs/research/optimization-methods.md) |
| 回看 fast3、H16、bucket2 等选择理由 | [优化方法总览](docs/research/optimization-methods.md) |
| 运行或诊断公共验证 | [验证环境与入口](docs/validation.md) |
| 核对比赛、提交和奖励机制 | [比赛与提交入口](docs/competition.md) |
| 查历史文件或老路径 | `python scripts/project.py find H16`；`python scripts/project.py resolve ROUND9.md` |

最近研究归档更新于 **2026-10-10**。最新保存榜单为 **29551（20:38:51 +08:00）**，榜单抓取复核至21:12:31；实时状态需重新查询官方。

- [正式提交收益看板](DASHBOARD.md)：历史提交、初始份额、快照份额和累计α；累计α采用官方API字段，不能当作钱包余额或净收益。
- [第十八轮：十一小时研究](docs/rounds/round18.md)：候选A随后正式提交为#603，初始竞赛池份额5.7127%；在快照29551被#607支配，份额0%。
- [第十九轮：高份额候选](docs/rounds/round19.md)：保留完整公共gate通过的候选；历史约7%预测随竞争变化失效，未正式上传。
- [第二十轮：冲击第一名](docs/rounds/round20.md)：两份精确候选通过完整公共gate，四块冻结确认显示条件竞争影响；全部十二块原协议观察仍有零份额和无影响反例，未获得稳定Top1，未正式上传。
- [优化方法与实验结论](docs/research/optimization-methods.md)：复用机制、负面结果、测量对照和独立确认方法；公共条件估算与正式可支付成绩分别记录。
- 历史正式参照：#573初始1.7365%，#582正式gate通过但被支配；完整历史见看板与[任务索引](docs/TASK_INDEX.md)。

文件分工：

- `docs/`：任务目录、历轮报告、机制和环境资料；`docs/history/` 为历史初始化记录。
- `candidates/`：可回溯的源码／证明包；`references/`：公开参照与作者归属。
- `evidence/roundN/`：批次、原始回执、分析和冻结快照；早期逐字重复文件通过路径映射定位。
- `scripts/` 与 `.github/workflows/`：生成、收集、复算和手动验证入口。
- `sources/`、`.registration-private/`、`.local-maintenance/`：本地忽略资料，不作为 Git 交付内容。

本次整理已把历轮分支合入 main，工作流改为手动启动。查询任务使用 `python scripts/project.py tasks`，检查文档、路径和配置使用 `python scripts/project.py check`；这些操作不会启动 CI。
