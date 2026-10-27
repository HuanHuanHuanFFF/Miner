# 2026-10-27 整理与合并

- [源合并](source-integration.json)：Codex与DeepSeek的原提交、两份原测试计划；当前旧计划为HOLD，新一轮另定。
- [散落资料](../../research/materials/20261027-scattered/README.md)：1373份技术文件首次同步，36份原件归档；15个未完备候选草稿移出候选入口。
- [清理回执](consolidation.json)：两工作区共移除约3.35 GB已识别的大型原始输出、重复副本及生成缓存；这是删除载荷总量，净占用还受新归档及Git对象变化影响。
- [恢复索引](recoverable-evidence.json)：保留每文件Git blob、SHA-256、路径、源提交及CI链接。先推送原件再清理；不改Git历史。
- [本地保留清单](local-only-index.json)：148份快照、参考缓存或受限来源原文继续留在本地，仅公开位置、哈希与处置分类。
- [既有测试问题](preexisting-estimate-test-issues.json)：旧估算测试3项样例错误已在清理前存在；本次未改估算器或冻结模型。

从仓库根运行 `python -B scripts/restore-evidence.py --run <CI运行ID>` 恢复某组；`--path <原路径>` 恢复单文件；历史完整审计前用 `--all`。恢复时逐字节校验并拒绝覆盖本地改动。CI附件可能过期，Git原件是持久来源。

后续开发与“merge”完整流程见根目录[DEVELOPMENT.md](../../../../DEVELOPMENT.md)。
