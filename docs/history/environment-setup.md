# 验证环境：GitHub Actions

> 历史记录，保留当时的观察与故障原因。当前执行规则以 [AGENTS.md](../../AGENTS.md) 为准，工作入口见 [任务索引](../TASK_INDEX.md)。本文件中的阶段状态、授权与价格不代表现状。

按 2026-10-06 的最新要求，工具链与大型依赖只运行在 GitHub CI，本地不保留 Linux 开发环境。

## 运行入口

[DEFLATE baseline](https://github.com/HuanHuanHuanFFF/Miner/actions/workflows/deflate-baseline.yml)：在 Actions 页点击 **Run workflow**，或修改 CI 配置/脚本后推送 main。

固定官方源码 `a356bbff18b60c4527fbcc85d5a28ef9c20214e0`，只验证未修改的 `miner/template` 和公共 stage1 corpus。每次在临时 Ubuntu 24.04 runner 安装官方固定工具链，检查 pins、doctor、公理与完整 gate/benchmark。详细版本、模板/corpus 哈希及结果输出到运行日志和 Summary。

CI 通过表示该 runner 上的公共 corpus 基线可复现，不表示正式提交通过、stage2 成绩或可获得奖励。首轮优化另用 [DEFLATE round 1](https://github.com/HuanHuanHuanFFF/Miner/actions/workflows/deflate-round1.yml) 工作流和 `codex/deflate-round1` 分支，见 [ROUND1](../rounds/round01.md)。不运行提交客户端或任何链上操作。

## 存储与费用

已核对本仓库公开，使用标准 `ubuntu-24.04` runner；公开仓库的标准 runner 免费。流程没有付费 larger runner，没有 Actions cache、工具链镜像或 artifact 上传；保留文本日志/Summary，不占 artifact 存储额度。

runner 每次是临时机器，运行结束后释放。CI 是自动验证入口，后续需要在本地编辑的代码仍可以直接推送后验证。

依据：[GitHub Actions 计费](https://docs.github.com/en/billing/concepts/product-billing/github-actions)、[标准 runner 规格](https://docs.github.com/en/actions/reference/runners/github-hosted-runners)。若仓库变私有，job 会跳过，避免自动转入私有仓库计费。

## 本地状态

本次创建的 `DeflateMiner-20261006` WSL、Ubuntu 镜像和下载/缓存已删除；原有 `docker-desktop` 保留。空间和路径核对见[清理回执](../../evidence/environment-cleanup-2026-10-06.json)。最初用于资料核对的小型 `sources/` 源码副本仍在本地并被 Git 忽略；不包含工具链或依赖环境。

INIT_STATE 保留初始化时的历史观察；本文件记录此后采用的环境安排。

## 已实测结果（2026-10-06）

**VERIFIED**：[CI 37353587399](https://github.com/HuanHuanHuanFFF/Miner/actions/runs/37353587399) 全部步骤成功，核验的 CI 配置提交为 `0823166f8c72916541599556ab71da54ed46b070`。

- 官方固定源码 70/70 pins 匹配；doctor 与 check-pins 通过；官方源码工作树未修改。
- 原版模板完成 Rust 检查、重新提取、`LZ77.Obligation` 类型检查和公理检查；仅使用 `Classical.choice`、`Quot.sound`、`propext`。
- 公共 stage1 的 28 文件、15,930,000 原始字节完成 benchmark/round trip；完整 gate 输出 `accepted=true`。
- 实测工具包括 Lean 4.31.0、Rust nightly-2026-08-18、just 1.58.0、uv 0.12.15；模板及每个 corpus 文件的哈希已保存。

证据：[run 元数据](../../evidence/ci/37353587399.json)、[完整 gate 日志](../../evidence/ci/37353587399-baseline.log)、[基线 JSON](../../evidence/ci/37353587399-baseline.json)、[版本/输入哈希](../../evidence/ci/37353587399-provenance.txt)。JSON 中的字节总量、总秒数和 slowdown 是该机器上的绝对 telemetry，不能当作官网的 balanced 两轴评分。

首轮[CI 37351619154](https://github.com/HuanHuanHuanFFF/Miner/actions/runs/37351619154) 在只读依赖缓存中补建 `AeneasMeta.Utils` 时返回 VALIDATOR ERROR。固定 Aeneas 的 `lakefile.lean` 根据 `CI` 是否存在决定模块预编译；官方 verifier 的环境白名单不保留 `CI`。CI 准备脚本移除这个变量后，同一份模板的原始验证通过。未改 parser、证明、官方 gate 或其只读权限。[首轮失败日志](../../evidence/ci/37351619154-failure.log)

## 第二轮开始时的环境变化

**VERIFIED**：2026-10-06 第二轮提交 `76af598a166524be0c460916673094c04742973d` 的 [CI 37447313800](https://github.com/HuanHuanHuanFFF/Miner/actions/runs/37447313800) 被仓库可见性条件跳过。即时 GitHub 元数据为 `isPrivate=true`；此前“公开仓库标准 runner 免费”的观察不能继续当作现状。本轮不改变仓库可见性。

第二轮入口见 [ROUND2](../rounds/round02.md)。自动 push 对私有仓库仍跳过；经用户明确授权的手动运行使用 `allow_private` 参数，默认 false。用户已在本轮明确回复“允许运行私有 CI，继续实测”。私有运行可能消耗套餐内分钟额度或产生超额费用；仅使用标准 ubuntu-24.04 runner，不缓存/上传大型 artifact。
