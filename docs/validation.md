# 验证环境与入口

运行策略、授权和证据要求统一见 [AGENTS.md](../AGENTS.md)。本页说明现有工具如何定位和使用。

## 选择入口

| 任务 | 入口 |
|---|---|
| 原版模板和公共 corpus 基线 | `.github/workflows/deflate-baseline.yml` |
| 复现某一轮批次 | 相应工作流，ref 选择原始 run 的 `source_commit`；批次 JSON 位于 `evidence/roundN/`。第十至十九轮复用 `deflate-round9.yml`，输入对应的 `experiment_round` |
| 通用批次预检 | `ROUND4_SPEC_DIR=evidence/roundN` 与 `scripts/round4.py preflight BATCH`；具体参数见冻结JSON |
| 第十七轮精确证明预检 | `ROUND17_SPEC=gate-proof1` 与 `scripts/verify-round17-exact.py --preflight`；只检查已冻结文件对 |
| 第十八轮精确配对与冻结确认 | `scripts/verify-round18-exact.py`、`scripts/dispatch-round18.py`；已通过配对与最终确认计划见[第十八轮](rounds/round18.md)，实际绑定以冻结批次及原始回执为准 |
| 第十九轮90分钟研究 | `scripts/dispatch-round19.py`、`scripts/verify-round19-exact.py`；候选与截止时间见[第十九轮](rounds/round19.md)，复用原版公共协议与同源码对照 |
| 下载已有 CI 回执 | `scripts/collect-round4.py status/pull 37700280634 --round 10 --batch confirm-j` |
| 最近结果复算 | `scripts/analyze-round18.py`与`scripts/summarize-round18-final.py`；精确最终pair、两台runner八块确认及单独/联合估算见[第十八轮](rounds/round18.md)。第十七轮正式#582与波动诊断仍见[第十七轮](rounds/round17.md) |
| 第十八轮字节审计 | `scripts/audit-round18-evidence.py`核对原始artifact清单、官方快照、已提交Git字节与两文件审阅ZIP；`scripts/summarize-round18-cost.py`从已收齐作业统计资源 |
| 文档和路径自检 | `python scripts/project.py check` |

所有 workflow 现为 `workflow_dispatch`，都提供默认 false 的 `allow_private`。每次派发前通过 GitHub 元数据检查仓库当前可见性；近期每批均重新核实公开状态。源码 push 不产生自动实验。`deflate-round9.yml` 当前支持第9至23轮，复现以原始回执绑定的精确 source_commit 和批次JSON为准，不依赖已清理的实验分支。

## 实际执行版本

准备脚本为 `scripts/ci-prepare.sh`、`scripts/ci-setup.sh`。固定官方提交 `a356bbff18b60c4527fbcc85d5a28ef9c20214e0`；临时 runner 使用 Ubuntu 24.04、Rust nightly-2026-08-18、Lean／Mathlib 4.31.0，以及官方 setup 固定的 Charon、Aeneas、uv 和 just。具体版本、70 项 pins、输入哈希、CPU、编译与运行参数从实际回执读取。

公共 benchmark 通常每文件一次 warmup、11 次 measured，保留 parser、encoder、总时间及重复输出信息；汇总工具从原始 measured reps 重算两轴。额外诊断使用临时源码副本，与官方性能计时分开。

`gate` artifact 的名字不证明 Lean 已跑过。读取 `state.json` 的 `gates` 和原始 gate 日志；已通过的候选若有 `VERIFICATION.json`，核对它绑定的源码、证明与 run。未通过、未运行和仅有限检查各自保留。

## 本地查阅和常见故障

本地可用 Git、轻量 Python；任务查找工具只使用 Python 标准库，配置自检额外读取 PyYAML。工具链和 corpus 的运行副本位于 CI 的 `RUNNER_TEMP`，不会搬回 C 盘。本地 `sources/` 阅读副本用于加载官方纯 scorer 等只读分析。

已有 GitHub CLI 收集脚本通过现有 Git credential helper 在子进程内取凭据，不打印或落盘。某些本地 PAT 没有 Actions 权限；重用收集脚本的 `gh_env()`，不要把 token 放在命令或日志。

Windows 的换行转换曾破坏原始 receipt 的字节哈希；`evidence/.gitattributes` 已统一关闭文本转换。路径映射覆盖被去重的早期副本。基线初期的 CI 环境变量／Aeneas 预编译故障记录在 [环境历史](history/environment-setup.md)，不作为新的运行要求。

第21轮通过`dispatch-round21.py`固定两小时截止，使用原版协议；容量与生成路径由`round21-preflight.py`预检。最终完整/超时测量、独立复现、两次gate失败与字节审计见[第21轮](rounds/round21.md)。

第22轮通过`dispatch-round22.py`固定追加一小时；`round22-preflight.py`绑定实际候选数量及原始文件。`verify-round22-exact.py`与`bind-round22-gate.py`绑定新精确验收，确认批次按通过的文件对派发。独立确认、同源码／分母分解、单独／联合重放及诊断协议边界见[第22轮](rounds/round22.md)。后续顺序诊断保留fixed11／fixed20／balanced20三组；本轮已冻结F实际只有fixed11／balanced20，不能按新准备器补写历史。

第23轮固定50分钟，`check-round23-route.py`跨工作流与派发器实际参数预检；首次旧轮次路由失败另列。`verify-round23-exact.py`、`bind-round23-gate.py`分别绑定原组合及新链三精确gate；冻结确认与等20次顺序诊断见[第23轮](rounds/round23.md)。收集器的平均坐标输出明确标为非逐块份额结论；控制缺少同块实际父参照时记录UNKNOWN，候选本身仍要求实际父参照齐全。
