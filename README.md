# Miner — DEFLATE competition workspace

Conjectures.io / Bittensor SN66 的 DEFLATE 项目记录与本地开发环境。

- [INIT_STATE](INIT_STATE.md)：官方入口、parser / correctness / benchmark / submission / reward 机制，以及初始化时的已知与未知。
- [ENVIRONMENT](ENVIRONMENT.md)：仅在 GitHub Actions 运行的工具链、验证入口及存储边界。
- [ROUND1](ROUND1.md)：首轮公开优化参照实验、候选差异和实测结论。
- [官方比赛](https://conjectures.io/competitions/deflate)
- [官方实现](https://github.com/conjectures-io/conjectures-optimisation-deflate)

当前范围：初始化和原版模板 CI 已完成，按 2026-10-06 的新指令开始公开首轮优化参照实验。目标为可领奖 Pareto 前沿及较大持续奖励份额。未注册、操作钱包、支付或正式提交。

大型工具链和依赖只在 GitHub Actions 的临时 Linux runner 中准备，本地不保留；最初核对资料的 `sources/` 副本被 Git 忽略。仓库保存轻量源码、证明、记录、证据和 CI 配置。
