# Conjectures / SN66 多赛道工作区

共同执行约束见根目录 [AGENTS.md](AGENTS.md)。先选赛道，再读取该赛道的规则、当前记录和验证入口。

**先看 [冲冠看板 dashboard.md](dashboard.md)**：按加法、乘法、求和、矩阵乘法查看冠军与我方首选。

FloatLib 的数学成果统一从[数学结论与可复用证明](competitions/floatlib/research/RESULTS.md)进入；包含 E 盘研究资料、失败路线和源码／验收对应关系。

| 赛道 | 状态与入口 | 验证与证据 |
|---|---|---|
| [FloatLib 浮点内核](competitions/floatlib/README.md) | 冲冠研究与 Astra 协作；[开发状态](competitions/floatlib/coordination/development-status.json) | [当前十小时协作](competitions/floatlib/candidates/f01-d7-research/README.md)、候选与官方 gate 回执均在本赛道目录 |
| [DEFLATE 压缩](competitions/deflate/README.md) | 官方已关闭新提交，保留全部研究与历史结果；[任务索引](competitions/deflate/docs/TASK_INDEX.md) | [赛道技术规则](competitions/deflate/docs/track-rules.md)、[历史提交看板](competitions/deflate/DASHBOARD.md)、[验证入口](competitions/deflate/docs/validation.md) |

`competitions/<slug>/` 内分别存放 candidates、references、docs、evidence、scripts。`.github/workflows/` 保留仓库级手动入口；根 `scripts/project.py` 负责多赛道自检与定位。

`.registration-private/` 是本地钱包及注册工具，保持原路径并由 Git 忽略；`.runtime/`、`.local-maintenance/` 等本地缓存和维护记录同样不发布。竞赛提交、资金动作与 GitHub CI 分别按授权执行。

DEFLATE 原根目录内容于2026-10-21迁入 `competitions/deflate/`，24257份已跟踪文件在任何有意修改前逐字节核对；[迁移回执](competitions/deflate/evidence/maintenance-20261021/migration-receipt.json)保留范围和原始哈希。历史回执内的旧路径按本次前缀迁移定位，不改写原始回执。
