# 后续开发入口

先读 [AGENTS.md](AGENTS.md)，再读所选赛道 README。FloatLib 当前候选、验收及冠军比较以[开发状态](competitions/floatlib/coordination/development-status.json)为准，[看板](dashboard.md)供快速查看。

## 两个 worktree

| 工作区 | 开发分支 | 用途 |
|---|---|---|
| `D:/CodingProject/Bitget` | `huan/codex-gpt` | Codex 开发验证及研究协调 |
| `D:/CodingProject/Bitget-DeepSeek` | `huan/dhs-deepseek` | DeepSeek 独立探索、开发与验证 |

两分支本次均从合并后的 `main` 重建；worktree 路径不变。各自维护文件和索引，开始工作先核对当前分支、改动、在途作业和公共交接区 `D:/CodingProject/Bitget-Collab/README.md`。同一工作区只由指定协调者操作 Git／CI。

## FloatLib 接续顺序

当前先看[R20四十五分钟交接](competitions/floatlib/candidates/f01-d7-research/round45m-20261027T074758Z/README.md)：八列广播9根、终端写出8根通过；完整终端候选39626d已接原public入口但尚未编译，下一轮先验该精确源。保留版仍为B2。

1. 读[赛道入口](competitions/floatlib/README.md)、技术规则及当前开发状态，确定保留版与验收缺项。
2. [数学结论](competitions/floatlib/research/RESULTS.md)索引可复用证明；当前保留 B2 的三组采用证据在 [R15](competitions/floatlib/candidates/f01-d7-research/round3h-20261025T043928Z/development-final-three-group-verification.json)。
3. [R18 结果与经验](competitions/floatlib/candidates/f01-d7-research/round11h-20261025T173831Z/README.md)：U32／U64往返接口已验；真正ADD／MUL重构完整正确但成本为负，避免仅换seed重跑。
4. [DeepSeek 最终总结](competitions/floatlib/research/deepseek-20261025/SUMMARY.md)：p≤8连续输出路由及原始CI已合入。其首个D未过，后续组仅作输入泛化诊断；相对旧df5c的收益不能继承为相对B2的收益或完整采用。
5. 准备新候选前查对应历史负结果；新一轮另定预算、命名、精确源和验证计划。公共入口[测试计划](competitions/floatlib/candidates/f01-d7-public-suite/suite-plan.json)现为HOLD，无排队候选；先冻结新计划，再按实际分支和远端精确提交派发。
6. [R19 六小时总结](competitions/floatlib/research/deepseek-20261025/R19-SUMMARY.md)：B2 分派放宽、逐行闭包、dot/finish 内联、convert→ofBits 均为负；mul 去低尺度分支在 EPYC 上 mul −8%—−12%，但 Intel 很小且整包不稳，确认失败已 REJECTED。**经验**：C 证据须确认 selected body；Xeon 单 run 标量可漂 ±10%；去 denormal 软件分支的候选必须记录 runner CPU 并做同 seed 对照。

7. [Codex R19 总结](competitions/floatlib/candidates/f01-d7-research/round9h-20261026T194639Z/README.md)：保留 B2，新候选未通过采用门槛；研发窗口及研究侧提前停止的更正在原记录中，不能把旧轮次时长用于新轮次。

原始证据分别按 Codex／DeepSeek 的原路径索引，薄记录及结论留在工作区，大型可恢复输出见下方恢复方式。历史环境命令和分支名需按当前入口核对。

## “merge”的完整操作

1. 核对各worktree、分支、未提交内容及在途作业；整理尚未同步的源码、证明、技术资料和结论，保留私人材料边界，逐字节核验后推送。
2. 清理无后续研究价值的日志、采样、重复副本和生成缓存。先把唯一原始证据推送并记录源提交、文件路径、字节数、哈希及CI链接，再移除工作区大文件；源码、证明、反例、结论及薄回执保留。CI附件到期后仍须可从Git原提交恢复；不重写历史。
3. 合并各方开发分支，包括DeepSeek，解决冲突并保留双方原件，运行本地自检，推送main。
4. 确认旧分支全部提交已包含在main，各worktree干净后，从最新main为两个worktree重建上表原名分支，并同步远端。不得覆盖其他会话未提交内容。

## 原始证据按需恢复

[恢复索引](competitions/floatlib/evidence/maintenance-20261027/recoverable-evidence.json)同时覆盖FloatLib和DEFLATE，记录原始路径、Git blob、SHA-256、源提交及CI链接。原始字节已先推送到 `09dd94ccf1697417880acc69363a21eca25c2dd5`，附件保留期有限，Git是持久恢复来源。以下命令在工作区根运行：

```text
python -B scripts/restore-evidence.py --list
python -B scripts/restore-evidence.py --run <CI运行ID>
python -B scripts/restore-evidence.py --path <索引中的相对路径>
python -B scripts/restore-evidence.py --all
```

恢复工具核验长度和哈希，已有文件不一致则拒绝覆盖。历史完整审计会逐项核验原附件清单，运行前先恢复对应组；跨多组审计如 `audit-suites.py` 先用 `--all`。冻结验证器保持原样；也可在原提交单独checkout复现。

## 本地核查与维护记录

在各自工作区运行 `python -B scripts/project.py check`；大型编译及完整gate仍在临时标准runner执行。工作流仅手动触发，普通推送不启动CI。

[本次源合并记录](competitions/floatlib/evidence/maintenance-20261027/source-integration.json)保存双方源提交及原测试计划；[散落资料索引](competitions/floatlib/research/materials/20261027-scattered/README.md)收录技术资料和旧草稿。[前次合并记录](competitions/floatlib/evidence/maintenance-20261026/consolidation.json)保留历史映射。私人材料和本地盘点清单留在 `.local-maintenance/`，不随推送发布。
