# FloatLib 首轮开发与公开验收

已得到一份通过完整官方公开 gate 的候选：[f01-mul-log2-proof3](../candidates/f01-mul-log2-proof3/Kernel.lean)。本次 headline 为 **0.967676976**，相对精确公开原版参考耗时降低 **3.2323%**。这是一次公开 runner 的观测，未做跨 runner 独立确认，未取得线上现任冠军源码或正式参赛成绩。

当前权威状态：[development-status.json](../coordination/development-status.json)。执行边界见根 [AGENTS.md](../../../AGENTS.md)、[赛道技术要求](track-rules.md)与[交接](../coordination/HANDOFF.md)。

## 时间与精确版本

开发接续窗口：北京时间 2026-10-21 **14:07:40—15:07:40**，含准备、等待、修复和 CI。最终验收于 **15:07:18** 在截止前启动，按用户要求运行至 **15:16:00** 自然成功；之后只收集回执、核算和交付，未新增研究或 CI。

- 官方仓库：`conjectures-io/conjectures-optimisation-float-kernels`，commit `978cc5b445edb9943fd9953b0a9037d97a9f33a8`，Lean **4.34.0**，full 槽。
- 基线 Kernel：33043 字节，SHA-256 `5d0cef3ff21093ca05cde92e516edfe45afca8e11996ad4858e7fb2407d65868`。
- 最终 Kernel：34737 字节，SHA-256 `0f4c999aa1c5375cfb2533550017189a51b5de8d8733be37765b8f38606ad8fd`。
- 最终 CI：[39559796985](https://github.com/HuanHuanHuanFFF/Miner/actions/runs/39559796985)，源码提交 `4c291af2d7967f0d1119a5228a58830830ee7e26`，seed **44**，CPU **INTEL(R) XEON(R) PLATINUM 8573C**，绑定 CPU **0**。
- 初期阅读副本比官方精确文件多一个末尾 LF；其 SHA 为 `46cbe66d7c14ffbead19c6fbb7d47b1b8d161f6f2793fd7ff0442ecdb585636b`。manifest 分列两种来源，实际 gate 使用精确官方基线。

## 实现与完整验收

仅改写 FastMul 的最高位 helper：先测试 `x >>> 47 == 1`，再测试 `x >>> 46 == 1`，其他词回退原六级二分。正常 24 位尾数乘积位于 `[2^46,2^48)`；等价证明覆盖全部 UInt64，而非只证明常见域。add、舍入、特殊值回退以及 sum／bmm 索引和累加顺序保留原版。

最终证明保留原版显式机器字到 Nat 转换，显式归约 `log2(1)=0` 和 `+0`，再使用等式对称。原始四个 obligation、Submission／VerifyFull 内核重放、公理审计与官方逐类 checksum 均通过；依赖仅 `Classical.choice`、`Quot.sound`、`propext`，验证器 fingerprint 首尾一致。原作者归属保存在 Kernel 注释与各 manifest 中。

## 实际结果

headline 按官方十二类记录分别取跨轮最小值、分别求和后相除；配对中位数与 bootstrap 是另外的统计量，不能互相替代。

| 对象 | seed／运行 | 完整 gate | headline（候选／公开原版） |
| --- | --- | --- | ---: |
| 同源码基线 | 42／39554146703 | PASS | 1.000952241 |
| 原始 f01-mul-log2 | 42／39554146703 | FAIL：statement 645、657 行 | UNKNOWN，未计时 |
| 同源码基线 | 43／39558841465 | PASS | 1.004505119 |
| f01-mul-log2-proof2 | 43／39558841465 | FAIL：statement 638、648 行 | UNKNOWN，未计时 |
| f01-mul-rse-threshold | 43／39558841465 | FAIL：statement 656、659、665、684 行 | UNKNOWN，未计时 |
| 同源码基线 | 44／39559796985 | PASS | 0.998219387 |
| **f01-mul-log2-proof3** | **44／39559796985** | **PASS** | **0.967676976** |

proof1 是保留的未执行预检包，没有 CI 成绩。早先关于多余 rfl 的担心未在实际错误中出现；原版失败在最终 broad simp，proof2 失败在新引入的字转换。proof3 合并两次实际反馈后通过；所有最高位版本的运行定义保持一致。

最终候选的 25 个配对轮次：比值中位数 **0.967234598**，范围 **0.942770112—0.978035865**；2000 次官方方法重采样的收益 p05 **3.175130%**。相对公开原版的本地统计判定为 `qualifies`；这不是线上对现任冠军的 admission。

| 函数 | 三类官方时间记录分别求和后的比值 |
| --- | ---: |
| add | 1.002210576 |
| mul | 0.889553027 |
| sum | 1.000361572 |
| bmm | 0.965331772 |

同源码控制在最终 runner 的配对中位数为 0.999492024，范围 0.675680626—1.003476772，含慢参照异常轮，均保留。它未满足公开统计门槛。候选的一次正向结果不能替代独立 runner 确认。

## 证据与缺项

- [最终 manifest](../candidates/f01-mul-log2-proof3/manifest.json)、[逐文件原始回执 SHA 索引](../candidates/f01-mul-log2-proof1/ci-runs/39559796985/original-artifact-hashes.json)、[独立复算](../candidates/f01-mul-log2-proof1/analyses/39559796985.json)。
- 首次环境与失败原件：[39554146703](../evidence/39554146703/original-artifact-hashes.json)；两份候选失败原件：[39558841465](../candidates/f01-mul-log2-proof1/ci-runs/39558841465/original-artifact-hashes.json)。三次作业全部到自然终态，没有取消。
- [源码可用性回执](../candidates/f01-mul-log2/source-survey/network-receipts.json)：13:25—13:26 查询冠军端点成功，174／165／147 的源码端点返回404；本轮未取得这些提交源码，不据此推断具体算法。来源核验与性能范围分开保留。
- 最高位有限模型 600313 个值零差异；舍入有限模型 924800 次零差异。舍入候选仍未通过 Lean，因此证明未完成、性能 UNKNOWN，不构成算法反例。
- 首次冷安装约1904秒；固定环境缓存保存成功。后两次复用缓存，未在本机安装大型 Linux 工具链。

本窗交付为一份完整公开验收通过且有单 runner 速度信号的冻结候选。独立新 runner／新种子确认、线上冠军对比及正式成绩仍为 UNKNOWN／NOT_RUN；未正式上传或执行资金操作。后续若另有研究预算，先对 proof3 做独立确认；舍入路线先在 runner 保存完整 Lean stdout，再修字转换与依赖型重写，避免只依赖官方压缩错误摘要。

交付字节核验：[final-byte-audit.json](../candidates/f01-mul-log2-proof1/analyses/final-byte-audit.json) 已逐一核对三次运行的60份原始 artifact 工件及5份 Kernel，本地、提交后的 Git 内容与所记 SHA-256 一致；未删除或改写任何原始失败工件。
