# FloatLib：精确 binary32 内核

共同约束见根 [AGENTS.md](../../AGENTS.md)，赛道技术要求见 [track-rules.md](docs/track-rules.md)。官方固定版本见 [pins.json](pins.json)。

新公开／付费私有套件适用范围先看[套件变更](docs/suite-transition-20261022.md)。

正式包是一个 `Kernel.lean`，包含 add、mul、sum、bmm 及四个全输入等价证明。开发比较统一以评测时的现任冠军为基准；当前尚未正式上传。

- [冲冠看板](../../dashboard.md)：按 add、mul、sum、bmm 四项查看现任冠军与我方首选。
- [当前开发状态](coordination/development-status.json)：当前比较口径、候选选择及证据入口。
- [数学结论与可复用证明](research/RESULTS.md)：按四项运算整理已验结论、数学储备、反例，以及 E 盘 12 包原文和全部候选的证据索引。
- [当前研究记录](candidates/f01-d7-research/round6h-20261024T051445Z/README.md)：六小时协作的标量实际热点与矩阵面板重构；[历史轮次](candidates/f01-d7-research/README.md)保留原验收。
- [前轮Astra／开发一小时协作](candidates/f01-d1-inline-all/window1h/README.md)：原生算术证明起点、逐项验收与原始回执。

- [首次双会话交接](coordination/HANDOFF.md)：环境与开发文件所有权、状态、自然检查点和本窗预算。
- [环境状态](coordination/environment-status.json)：CONFIGURING、CI_READY、BASELINE_VERIFIED 分开记录。
- [环境使用说明](docs/environment.md)：固定工具链、当前手动入口、回执收集及验收边界。
- [首次环境验收](docs/environment-validation-20261021.md)：环境与完整基线通过；原始候选证明失败，保留原始回执。
- `candidates/f01-*/`：开发会话负责的首轮候选；目录名与文件存在不代表已通过 gate。
- `references/official-incumbent/`：精确官方参考和来源；正式现任冠军源码尚未取得，不能把旧参考提速当作夺冠。
- `scripts/`：在临时 Linux GitHub runner 准备环境、运行官方完整 gate 和配对计时。
- `evidence/`：精确源码哈希、runner、官方日志、原始 JSON 和查询快照；原始文件保留字节。

独立手动入口 `.github/workflows/floatlib-validate.yml` 已在 `main` 登记并确认 active；已有 `deflate-baseline.yml` 的 `competition=floatlib` 桥接入口仍保留。具体命令见环境使用说明。本地只保留轻量源码与回执，大型 Linux 工具链、依赖、缓存与二进制留在临时 runner。
