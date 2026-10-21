# FloatLib 开发与 CI 环境

执行授权和通用规则见根 [AGENTS.md](../../../AGENTS.md)。最新安装、基线和候选结果以 [环境状态](../coordination/environment-status.json) 及其原始回执为准；文档中的命令不代表已执行。

## 固定环境

- 官方仓库与精确提交见 [pins.json](../pins.json)：`978cc5b445edb9943fd9953b0a9037d97a9f33a8`，Lean `v4.34.0`。
- 免费标准 GitHub `ubuntu-24.04` runner，单个任务上限 45 分钟；只检出本赛道，避免下载 DEFLATE 历史大回执。
- 大型 Linux 工具链只安装在临时 runner。本地 Windows 保留源码、轻量调度脚本和证据。
- 原版 `setup.sh` 安装后运行 `setup.sh --check`，记录 Lean、Python、bwrap 版本及官方源码无修改检查。
- 官方 gate 的 systemd 内存上限保持启用；准备阶段验证用户级 systemd 与受限内存进程可用。使用 runner 允许的第一个逻辑 CPU，固定 25 轮和 500000 配对输入；具体 CPU 型号和亲和性记录于 `provenance.json`。
- Lean 与官方 `.lake` 依赖缓存按操作系统和官方提交隔离；缓存命中不替代安装自检或完整 gate。

## 手动验证入口

当前默认分支还没有登记新的 `floatlib-validate.yml`，因此使用已有的 `deflate-baseline.yml`，在本实验分支选择 `competition=floatlib`。DEFLATE job 会跳过；没有因此合并默认分支。

在仓库根目录执行，示例中的候选名须替换为已冻结、已提交和已推送的目录：

```powershell
python scripts/github-ci.py dispatch --workflow deflate-baseline.yml --candidates f01-mul-log2 --seed 42
python scripts/github-ci.py status --run 39554146703
python scripts/github-ci.py collect --run 39554146703
```

`dispatch` 在启动前检查公开仓库、远端精确提交、工作流及候选字节与 Git 一致。凭据通过已有 Git 凭据服务只进入进程环境。一次启动未能识别结果时，应先查运行记录，不能直接重复启动。

候选目录为 `competitions/floatlib/candidates/<name>/Kernel.lean`；当前入口接受 `baseline` 或 `f01-*`，一次最多四个候选，并自动先验证原版基线。每个输入须在 256000 字节以内。

工作流只手动启动，常规推送不启动 CI，不取消已运行任务。新的独立工作流保留为以后默认分支登记后的入口；现阶段使用上述桥接入口。

## 验收与证据

官方完整 `--slot full` gate 对精确 `Kernel.lean` 重新提取、验证原始 obligation、公理和 round trip，再执行原版配对计时。安装自检、完整基线 gate、候选 gate 和公开性能结果分别记录。

CI 无论成功或失败都尝试上传 `floatlib-<run_id>-receipts`，保留 7 天。收集脚本保存运行元数据、完整日志、原始 artifact、逐文件字节数与 SHA-256；回执目录在本赛道 `evidence/<run_id>/`。`environment.json` 证明安装自检；`summary.json`、各候选 `*-verdict.json` 与 `*-gate.log` 证明相应 gate 的实际结果。失败或超时不能写成通过，未执行写 `NOT_RUN`。

基准对照是固定官方仓库附带的参考实现。公开 runner 的统计结果不是线上 admission、当前冠军比较或实际竞赛奖励。

## 本会话收尾

用户已将环境会话范围收紧为：配置完成后停止。环境会话只收齐已启动的运行 `39554146703`，不再派发新的候选或独立确认。后续开发会话在自然检查点读取 [交接文件](../coordination/HANDOFF.md) 和环境状态，依其自身授权继续。
