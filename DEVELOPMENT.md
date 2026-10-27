# 后续开发入口

先读 [AGENTS.md](AGENTS.md)，再读所选赛道 README。FloatLib 当前候选、验收及冠军比较以[开发状态](competitions/floatlib/coordination/development-status.json)为准，[看板](dashboard.md)供快速查看。

## 两个 worktree

| 工作区 | 开发分支 | 用途 |
|---|---|---|
| `D:/CodingProject/Bitget` | `huan/codex-gpt` | Codex 开发验证及研究协调 |
| `D:/CodingProject/Bitget-DeepSeek` | `huan/dhs-deepseek` | DeepSeek 独立探索、开发与验证 |

两分支本次均从合并后的 `main` 重建；worktree 路径不变。各自维护文件和索引，开始工作先核对当前分支、改动、在途作业和公共交接区 `D:/CodingProject/Bitget-Collab/README.md`。同一工作区只由指定协调者操作 Git／CI。

## FloatLib 接续顺序

1. 读[赛道入口](competitions/floatlib/README.md)、技术规则及当前开发状态，确定保留版与验收缺项。
2. [数学结论](competitions/floatlib/research/RESULTS.md)索引可复用证明；当前保留 B2 的三组采用证据在 [R15](competitions/floatlib/candidates/f01-d7-research/round3h-20261025T043928Z/development-final-three-group-verification.json)。
3. [R18 结果与经验](competitions/floatlib/candidates/f01-d7-research/round11h-20261025T173831Z/README.md)：U32／U64往返接口已验；真正ADD／MUL重构完整正确但成本为负，避免仅换seed重跑。
4. [DeepSeek 最终总结](competitions/floatlib/research/deepseek-20261025/SUMMARY.md)：p≤8连续输出路由及原始CI已合入。其首个D未过，后续组仅作输入泛化诊断；相对旧df5c的收益不能继承为相对B2的收益或完整采用。
5. 准备新候选前查对应历史负结果；新一轮另定预算、命名、精确源和验证计划。公共入口[测试计划](competitions/floatlib/candidates/f01-d7-public-suite/suite-plan.json)现为HOLD，无排队候选；先冻结新计划，再按实际分支和远端精确提交派发。
6. [R19 六小时总结](competitions/floatlib/research/deepseek-20261025/R19-SUMMARY.md)：B2 分派放宽、逐行闭包、dot/finish 内联、convert→ofBits 均为负；mul 去低尺度分支在 EPYC 上 mul −8%—−12%，但 Intel 很小且整包不稳，确认失败已 REJECTED。**经验**：C 证据须确认 selected body；Xeon 单 run 标量可漂 ±10%；去 denormal 软件分支的候选必须记录 runner CPU 并做同 seed 对照。

原始证据保留在 Codex 的 `competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/` 和 DeepSeek 的 `competitions/floatlib/research/deepseek-20261025/ci-runs/`，不合并改写原回执。历史环境命令和分支名需按当前入口核对。

## 本地核查与维护记录

在各自工作区运行 `python -B scripts/project.py check`；大型编译及完整gate仍在临时标准runner执行。工作流仅手动触发，普通推送不启动CI。

[本次合并记录](competitions/floatlib/evidence/maintenance-20261026/consolidation.json)保存双方源提交及冲突处理；[原测试计划](competitions/floatlib/evidence/maintenance-20261026/source-plans/)按字节归档。Codex 本地未公开研究材料保留原位，逐文件清单在 `.local-maintenance/merge-20261026/before.json`；该本地清单和私人材料不随推送发布。
