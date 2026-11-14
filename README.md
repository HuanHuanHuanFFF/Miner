# Conjectures / SN66 多赛道工作区

共同执行约束见根目录 [AGENTS.md](AGENTS.md)。先选赛道，再读取该赛道的规则、当前记录和验证入口。

**当前目标：拿下任意 TorchLean 赛道冠军。** 各榜只与现任冠军比较；先看[冲冠看板 dashboard.md](dashboard.md)及[TorchLean当前开发](competitions/torchlean/README.md)。旧FloatLib四运算成绩保留历史。

继续开发读[双 worktree 开发入口](DEVELOPMENT.md)：当前保留版、Codex／DeepSeek成果、验证计划与交接路径集中在此导航。

FloatLib 的数学成果统一从[数学结论与可复用证明](competitions/floatlib/research/RESULTS.md)进入；包含 E 盘研究资料、失败路线和源码／验收对应关系。

| 赛道 | 状态与入口 | 验证与证据 |
|---|---|---|
| [TorchLean 完整模型](competitions/torchlean/README.md) | 任意分榜争冠；[R27五小时](competitions/torchlean/candidates/r27-5h-20261029T194443Z/README.md) | 原完整12义务与完整模型计时分别验证 |
| [FloatLib 浮点内核](competitions/floatlib/README.md) | 历史正式提交#336验证通过，第13；[开发状态](competitions/floatlib/coordination/development-status.json) | 官方原始报告、候选与研究记录由赛道入口索引 |
| [DEFLATE 压缩](competitions/deflate/README.md) | 官方已关闭新提交，保留全部研究与历史结果；[任务索引](competitions/deflate/docs/TASK_INDEX.md) | [赛道技术规则](competitions/deflate/docs/track-rules.md)、[历史提交看板](competitions/deflate/DASHBOARD.md)、[验证入口](competitions/deflate/docs/validation.md) |

`competitions/<slug>/` 内分别存放 candidates、references、docs、evidence、scripts。`.github/workflows/` 保留仓库级手动入口；根 `scripts/project.py` 负责多赛道自检与定位。

`.registration-private/` 是本地钱包及注册工具，保持原路径并由 Git 忽略；`.runtime/`、`.local-maintenance/` 等本地缓存和维护记录同样不发布。竞赛提交、资金动作与 GitHub CI 分别按授权执行。

DEFLATE 原根目录内容于2026-10-21迁入 `competitions/deflate/`，24257份已跟踪文件在任何有意修改前逐字节核对；[迁移回执](competitions/deflate/evidence/maintenance-20261021/migration-receipt.json)保留范围和原始哈希。历史回执内的旧路径按本次前缀迁移定位，不改写原始回执。
