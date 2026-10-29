# FloatLib 当前协作交接

当前分支`huan/codex-gpt`，D统一Git／公共CI；普通消息走`D:/CodingProject/Bitget-Collab`。R24共同窗口UTC2026-10-28 20:38:56—2026-10-29 03:38:56；全部12个已启动CI均已收齐终态，本轮七小时窗口已结束，证明接口与下一确认计划已交接。

- 当前入口：[R24结果](../candidates/f01-d7-research/round7h-20261028T203856Z/README.md)、[精确作业版本](../candidates/f01-d7-research/round7h-20261028T203856Z/development-jobs.json)、[开发状态](development-status.json)。
- FloatLib本轮成功响应已关闭新提交；TorchLean为不同的12算子接口，目标选择待用户回复。03:20末次GET全403，最新状态UNKNOWN，保留早前原件；不绕过限制、不据旧值称刚核验。旧四运算看板及保留B2/622d不套用新点积成本。
- 主路线为原生双精度累加＋精确证书／整数回退。Tail去掉普通MAC每项Float装箱，64进程完整点积对照已独立重算。多行、多列共用缓存的完整调用在40811305126通过464输出及16进程成本检查；eager耗时／自建整数参照0.2723–0.2892，包含每行列准备、所有输出和释放。它是通用一次舍入点积实验，不是旧逐次舍入BMM、冠军成绩或已采用代码。
- 精确core049b：9新增helper＋4原公开义务，共13项statement/kernelReplay/AX通过。35根组合island9仍余常量cast；Widen7修复为NOT_RUN。运行时完整证明仍缺prepare／Tail／orderKey／实际rounder连接，见[R研究前沿](../candidates/f01-d7-research/round7h-20261028T203856Z/research/CERTIFICATE-INTEGRATION-FRONTIER.md)。
- 下一轮先确认目标，再按[研究交接](../candidates/f01-d7-research/round7h-20261028T203856Z/research/HANDOFF.md)完成最小checker及实际完整调用；采用前另冻结新确认输入／runner。两链精确整数为独立备选。R23乘法和矩阵接口记录保留在[R23入口](../candidates/f01-d7-research/round40m-20261028T142626Z/README.md)，不继承为新源正确性／速度。无本机Lean、正式上传、资金或reset。

## 历史：首次环境与开发交接

用户要求两个独立会话并行：环境会话整理多赛道目录、通用根规则和 GitHub CI；开发验证会话使用 GPT-6.1 Sol / xhigh 准备首个候选及证明。交接按 writing-for-agents 与 prompt-entropy 编写；共同授权以根 AGENTS.md 和用户当前请求为准。

## 固定接口

- 工作区：`D:/CodingProject/Bitget`，共享分支 `codex/multi-track-floatlib`。双方不切分支、不重置、不暂存对方文件。
- 官方版本及公理：`../pins.json`。候选：`../candidates/f01-*/Kernel.lean`，单文件含四函数与四个规格证明。
- 环境会话拥有根目录迁移、根 AGENTS.md、`.github/`、本赛道 scripts、pins、references、README、environment-status.json 和本文件。
- 开发会话拥有本赛道 `candidates/f01-*/`、`docs/first-candidate.md`、`coordination/development-status.json`。其他路径只读；不操作钱包，不正式参赛上传，不安装大型本地 Linux 工具链。
- 环境会话工作期间汇总提交、推送与派发 CI；此时开发会话不提交、推送、切分支或独立派发 CI，以免共享索引与实验相互干扰。环境会话在 `environment-status.json` 标记 `environment_owner_state=STOPPED_AFTER_ENVIRONMENT_CONFIGURATION` 后，停止 Git 和 CI 操作；后续开发会话可依据其自身已有授权接管提交、推送和 CI，不需等待本会话继续，不扩大授权范围。

## 无打断交接

`environment-status.json` 是环境状态的权威入口；`development-status.json` 是候选准备状态的权威入口。普通交接只写文件并进入 Git 提交，不给正在运行的会话追加消息。

各会话在自然检查点读取对方状态与 `git log -5 --oneline -- competitions/floatlib/coordination`：开始下一候选、证明告一段落、CI前后或需要对方环境时。无需持续轮询，也不把文件出现当作工作已执行。

环境状态：`CONFIGURING` → `CI_READY`（脚本及工作流可派发）→ `CI_RUNNING`（已识别精确run，执行尚未结束）→ `BASELINE_VERIFIED`（完整官方基线gate有成功回执）。失败用 `FAILED` 并附原始run、原因及剩余缺项。`CI_READY` 不代表Lean或计时已通过。

开发状态应绑定候选路径、Kernel SHA-256、变化机制、证明状态、最小检查和缺项。未在官方环境执行的证明／速度均写 `NOT_RUN`。候选冻结后，环境会话使用精确提交与文件哈希运行 gate 和原版配对测量，再把原始回执位置写回环境状态；开发会话读取反馈后决定修复、保留或换路。

## 本窗验收与边界

准备、迁移、排队、执行、修复和收尾均计入本轮两小时窗口：北京时间2026-10-21 13:16—15:16。窗口到期前预留回执回收与交付；已启动CI按成功、失败或既定超时收齐，不因预算临近随意取消。

首轮目标是多赛道结构可查、官方环境可复现、基线gate和首个候选实际CI结果可复核；不承诺3%提速或夺冠。正式竞赛上传、后续注册、签名与资金动作不在本次范围。GitHub仓库当前为公开仓库，只用标准runner；私有运行需另有对应授权。

用户随后将环境会话范围收紧为“配置完环境就可以停下”。本会话收齐已启动的 `39554146703` 后记录安装与基线验证结果、发布交接并停止；不启动 proof1、第二候选或新的确认运行。原始候选失败时保留负面回执，开发会话按自身授权处理。环境使用和结果定位见 [environment.md](../docs/environment.md)。
