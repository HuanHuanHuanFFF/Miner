# 验证环境：GitHub Actions

按 2026-10-06 的最新要求，工具链与大型依赖只运行在 GitHub CI，本地不保留 Linux 开发环境。

## 运行入口

[DEFLATE baseline](https://github.com/HuanHuanHuanFFF/Miner/actions/workflows/deflate-baseline.yml)：在 Actions 页点击 **Run workflow**，或修改 CI 配置/脚本后推送 main。

固定官方源码 `a356bbff18b60c4527fbcc85d5a28ef9c20214e0`，只验证未修改的 `miner/template` 和公共 stage1 corpus。每次在临时 Ubuntu 24.04 runner 安装官方固定工具链，检查 pins、doctor、公理与完整 gate/benchmark。详细版本、模板/corpus 哈希及结果输出到运行日志和 Summary。

CI 通过表示该 runner 上的公共 corpus 基线可复现，不表示正式提交通过、stage2 成绩或可获得奖励。此阶段不实现优化，不运行提交客户端或任何链上操作。

## 存储与费用

已核对本仓库公开，使用标准 `ubuntu-24.04` runner；公开仓库的标准 runner 免费。流程没有付费 larger runner，没有 Actions cache、工具链镜像或 artifact 上传；保留文本日志/Summary，不占 artifact 存储额度。

runner 每次是临时机器，运行结束后释放。CI 是自动验证入口，后续需要在本地编辑的代码仍可以直接推送后验证。

依据：[GitHub Actions 计费](https://docs.github.com/en/billing/concepts/product-billing/github-actions)、[标准 runner 规格](https://docs.github.com/en/actions/reference/runners/github-hosted-runners)。若仓库变私有，job 会跳过，避免自动转入私有仓库计费。

## 本地状态

本次创建的 `DeflateMiner-20261006` WSL、Ubuntu 镜像和下载/缓存已删除；原有 `docker-desktop` 保留。D 盘可用空间已恢复至约15 GiB。最初用于资料核对的小型 `sources/` 源码副本仍在本地并被 Git 忽略；不包含工具链或依赖环境。

INIT_STATE 保留初始化时的历史观察；本文件记录此后采用的环境安排。

首次 CI 验证：待实测；以 Actions 的实际结果为准。
