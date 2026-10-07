# Miner — DEFLATE competition workspace

Conjectures.io / Bittensor SN66 的 DEFLATE 项目记录与本地开发环境。

- [优化方法与实验结论](OPTIMIZATION_METHODS.md)：第一至七轮的方法归纳、负面结果、正式校准经验和下一轮验证方向。
- [INIT_STATE](INIT_STATE.md)：官方入口、parser / correctness / benchmark / submission / reward 机制，以及初始化时的已知与未知。
- [ENVIRONMENT](ENVIRONMENT.md)：仅在 GitHub Actions 运行的工具链、验证入口及存储边界。
- [ROUND1](ROUND1.md)：首轮公开优化参照实验、候选差异和实测结论。
- [ROUND2](ROUND2.md)：吸收深度研究后的两槽桶、搜索深度及停止门槛对照实验。
- [ROUND3](ROUND3.md)：90 分钟内同时探索速度与压缩两端，按 #427 和同族正式参照校准，保留筛选、gate 与前沿缺口。
- [ROUND4](ROUND4.md)：五小时 CPU、匹配成本、规划与通用组合实验；原始回执、跨 runner 复测、证明状态和最新候选选择。
- [ROUND5](ROUND5.md)：H16 证明精简、旧速度候选复测和完整编码成本选择实验。
- [ROUND6](ROUND6.md)：H16 CPU 与核心优化的负面结果，以及后续 #474 正式结果校准。
- [第七轮总表](evidence/round7/final-summary.json)：17 个中段候选、四批完整 CI、76 次公共配对测量；方法说明见优化总览。
- [官方比赛](https://conjectures.io/competitions/deflate)
- [官方实现](https://github.com/conjectures-io/conjectures-optimisation-deflate)

截至 2026-10-07 第七轮归档，目标仍为可支付 Pareto 前沿。各 ROUND 文件保留当时的假设与状态；方法总览汇总后续证据。注册、提交额度和钱包状态须独立核对，正式提交与资金操作按相应用户请求处理。

速度端 [fast3](candidates/r3-432-fast3/parse.rs) 后续正式提交为 **#453**，已有通过 admission 和历史奖励记录，用户也已确认到账。压缩端 H16-small **#474** 的正式 gate 通过，但 admission 判定被支配；#427 的乐观迁移系数不能继续作为跨算法族的默认依据。两者的记录见 [保存的官方快照](evidence/round7/frontier-final/pareto-pages.json) 与 [#474 校准](evidence/round6/formal-474/calibration.json)。这些是历史时点，不是实时排名。

第七轮中段实验得到 [block1](candidates/r7-mid361-block1/VERIFICATION.json) 的完整公共 gate 通过记录；17 个候选在快照 26815 下经同族校准和保守情景均未进入预测前沿，没有新的正式提交。源码、证明、测试次数与原始回执见第七轮总表。

[probe2](candidates/probe2/parse.rs)、[probe3](candidates/probe3/parse.rs)、[bucket2](candidates/bucket2/parse.rs) 和 H 系列继续作为有明确来源及验证边界的研究对照；不从公共 gate 或单次速度改善推断线上支付资格。

大型工具链和依赖只在 GitHub Actions 的临时 Linux runner 中准备，本地不保留；最初核对资料的 `sources/` 副本被 Git 忽略。仓库保存源码、证明、原始研究回执和 CI 配置。第四轮证据按原字节归档，避免跨平台换行转换破坏已记录的 SHA256。
