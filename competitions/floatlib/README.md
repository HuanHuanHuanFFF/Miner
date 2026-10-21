# FloatLib：精确 binary32 内核

共同约束见根 [AGENTS.md](../../AGENTS.md)，赛道技术要求见 [track-rules.md](docs/track-rules.md)。官方固定版本见 [pins.json](pins.json)。

正式包是一个 `Kernel.lean`，包含 add、mul、sum、bmm 及四个全输入等价证明。当前阶段只配置环境并运行公开验证，不正式上传。

- [首次双会话交接](coordination/HANDOFF.md)：环境与开发文件所有权、状态、自然检查点和本窗预算。
- [环境状态](coordination/environment-status.json)：CONFIGURING、CI_READY、BASELINE_VERIFIED 分开记录。
- [环境使用说明](docs/environment.md)：固定工具链、当前手动入口、回执收集及验收边界。
- `candidates/f01-*/`：开发会话负责的首轮候选；目录名与文件存在不代表已通过 gate。
- `references/official-incumbent/`：精确官方参考和来源；正式现任冠军源码尚未取得，不能把旧参考提速当作夺冠。
- `scripts/`：在临时 Linux GitHub runner 准备环境、运行官方完整 gate 和配对计时。
- `evidence/`：精确源码哈希、runner、官方日志、原始 JSON 和查询快照；原始文件保留字节。

当前手动入口为已有 `.github/workflows/deflate-baseline.yml` 的 `competition=floatlib` 模式；独立 `.github/workflows/floatlib-validate.yml` 尚未在默认分支登记。具体命令见环境使用说明。本地只保留轻量源码与回执，大型 Linux 工具链、依赖、缓存与二进制留在临时 runner。
