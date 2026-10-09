# 验证环境与入口

运行策略、授权和证据要求统一见 [AGENTS.md](../AGENTS.md)。本页说明现有工具如何定位和使用。

## 选择入口

| 任务 | 入口 |
|---|---|
| 原版模板和公共 corpus 基线 | `.github/workflows/deflate-baseline.yml` |
| 复现某一轮批次 | 相应工作流，ref 选择原始 run 的 `source_commit`；批次 JSON 位于 `evidence/roundN/`。第十轮复用 `deflate-round9.yml`，输入 `experiment_round=10` |
| 最新已验证包的批次预检 | `ROUND4_SPEC_DIR=evidence/round10` 与 `scripts/round4.py preflight confirm-j` |
| 下载已有 CI 回执 | `scripts/collect-round4.py status/pull 37700280634 --round 10 --batch confirm-j` |
| 最近结果复算 | `scripts/summarize-round10.py RECEIPT... --snapshot SNAPSHOT`；13 个原始 run 见 [第十轮报告](rounds/round10.md) |
| 文档和路径自检 | `python scripts/project.py check` |

所有 workflow 现为 `workflow_dispatch`，都提供默认 false 的 `allow_private`。每次派发前通过 GitHub 元数据检查仓库当前可见性；第十四轮已核实为公开仓库。源码 push 不产生自动实验。`deflate-round9.yml` 当前支持第9至14轮，复现以原始回执绑定的精确 source_commit 和批次JSON为准，不依赖已清理的实验分支。

## 实际执行版本

准备脚本为 `scripts/ci-prepare.sh`、`scripts/ci-setup.sh`。固定官方提交 `a356bbff18b60c4527fbcc85d5a28ef9c20214e0`；临时 runner 使用 Ubuntu 24.04、Rust nightly-2026-08-18、Lean／Mathlib 4.31.0，以及官方 setup 固定的 Charon、Aeneas、uv 和 just。具体版本、70 项 pins、输入哈希、CPU、编译与运行参数从实际回执读取。

公共 benchmark 通常每文件一次 warmup、11 次 measured，保留 parser、encoder、总时间及重复输出信息；汇总工具从原始 measured reps 重算两轴。额外诊断使用临时源码副本，与官方性能计时分开。

`gate` artifact 的名字不证明 Lean 已跑过。读取 `state.json` 的 `gates` 和原始 gate 日志；已通过的候选若有 `VERIFICATION.json`，核对它绑定的源码、证明与 run。未通过、未运行和仅有限检查各自保留。

## 本地查阅和常见故障

本地可用 Git、轻量 Python；任务查找工具只使用 Python 标准库，配置自检额外读取 PyYAML。工具链和 corpus 的运行副本位于 CI 的 `RUNNER_TEMP`，不会搬回 C 盘。本地 `sources/` 阅读副本用于加载官方纯 scorer 等只读分析。

已有 GitHub CLI 收集脚本通过现有 Git credential helper 在子进程内取凭据，不打印或落盘。某些本地 PAT 没有 Actions 权限；重用收集脚本的 `gh_env()`，不要把 token 放在命令或日志。

Windows 的换行转换曾破坏原始 receipt 的字节哈希；`evidence/.gitattributes` 已统一关闭文本转换。路径映射覆盖被去重的早期副本。基线初期的 CI 环境变量／Aeneas 预编译故障记录在 [环境历史](history/environment-setup.md)，不作为新的运行要求。
