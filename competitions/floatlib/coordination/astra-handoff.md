# FloatLib 一小时研究／开发协作

用户本轮授权：创建 GPT-6 Astra 研究会话，使用 huan-collaborate；优先优化当前落后最多的运算，协作推进 1 小时。
共同窗口：2026-10-21 10:32:09—11:32:09 UTC（北京时间 18:32:09—19:32:09）。准备、排队、修复、计时与回收均计入。已启动 CI 自然结束并回收；11:15 UTC 前转入冻结与确认，后续只启动可在剩余窗口内产生有效反馈的小动作。

## 职责与文件

- D：本会话 `01a15ce7-bf54-74b2-8a2b-4a1e2f3828d7`，负责实际开发、完整证明、计时、采用、唯一 Git／推送／CI 协调及 dashboard.md。当前分支 codex/multi-track-floatlib，不切换或重置。
- R：新建 GPT-6 Astra／xhigh 独立会话，负责差距机制调查、反例、证明桥接与可运行候选。只写 `competitions/floatlib/research/astra-collab-20261021/` 和 `competitions/floatlib/candidates/f01-r1-*/`；不提交、不推送、不派 CI，不修改官方源、pins、contracts、gate、bench、D 候选或共同状态。
- D 候选使用 `candidates/f01-d1-*/`。研究候选完成后冻结，D 复制到自己的候选目录验证，原包保留。双方不得暂存或覆盖对方未完成文件。
- 唯一总体状态为 `coordination/development-status.json`。R 自身状态写 `research/astra-collab-20261021/research-status.json`；阶段交付列出精确文件 SHA-256、变化、适用域、证明状态、反例、成本、最小验证请求。普通交接落盘，双方在自然阶段节点读取，不频繁消息打断。

## 当前起点与首批问题

- 先读根 AGENTS.md、FloatLib README、docs/track-rules.md、pins.json、现有状态与本交接。协作使用用户指定 `C:/Users/幻/.codex/skills/huan-collaborate/SKILL.md`；研究按 huan-open-research。
- `evidence/dashboard-operations-20261021T102009Z/operation-comparisons.json` 保存分项比较及原始依据。目前 bmm 约 280×、sum 约 32×、add 约 3.4×、mul 约 3.1× 冠军耗时；这些是历史链换算，不是同机冠军计时。优先 bmm，再 sum；先解释差距而非按旧 helper 继续微调。
- 完整正式榜冠军为 #174，digest 67e44fd4b17186dbe6b1728dea49611288bb16d2586ebbb3a8a2f93aea74c009。四个练习榜本次均无已晋升冠军。冠军源码尚未取得；当前 source 调查见 `evidence/public-source-survey-20261021T101011Z/README.md`，不要重复已经证实不支持的下载路径。
- 已证明组件：`f01-rebuilt-mul-proof1`（两个 runner），`f01-index-hoist-proof2`（基址外提），`f01-tensor-specialization`（sum/bmm inline），`f01-word-tensors-proof1`（UInt32 位状态）。上一窗报告：`candidates/f01-rebuilt-mul-proof1/window90/README.md`；完整原始 CI 在 `candidates/f01-mul-log2-proof1/ci-runs/`。
- 独立最好结果不是集成版本；正常数同号 GRS 原型未证明且变慢，另一同尺度加法完整通过但变慢。旧张量位状态和简单 inline 都没有量级收益；重访须给出不同机制。
- 首个研究检查点应尽早交付：从官方计时和已收回 C/IR 判断 bmm/sum 的巨大差距可能来自何处，选一个能区分真实算术、零回退、调用／分配、索引和编译工作移动的最小实验。然后优先产出有较大机会的候选与关键证明桥接；允许受保护快路径、共享计算和循环改写，保持每输出 k 顺序、逐次舍入与全域位等价。

## 验收与资源

所有 Linux 大型工具链、依赖和二进制只在临时 GitHub runner。R 可本地做轻量 Python/C 模型或源码研究，不安装 Lean；无钱包、签名、注册、资金和正式提交。官方完整包 Kernel.lean ≤256000 字节，四函数四证明；不引入 forbidden native axioms、FMA、近似或结合顺序变化。
D 运行固定官方完整 gate 与十二类25轮配对计时，保留原始日志、CPU、种子、精确源码／参照。冠军源码不可得时保持直接比值 UNKNOWN，对起始参考的配对仅作研发反馈；用户看板继续四运算、冠军基准、少字。
R 每次交付后读取 D 状态反馈，再决定修复、换路或停放，控制待测积压。11:32:09 UTC 前完成自身收尾并明确终态；不要创建额外会话、子 agent、自动化或 Goal。
