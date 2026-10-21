# FloatLib 首个候选：乘法最高位快捷路径

当前候选：[f01-mul-log2](../candidates/f01-mul-log2/manifest.json)。状态权威入口为 [development-status.json](../coordination/development-status.json)，环境及 CI 回执从 [environment-status.json](../coordination/environment-status.json) 读取。研究窗口为北京时间 2026-10-21 13:16—15:16，准备、等待与收尾均在窗内。

## 固定工件与本次决定

官方来源：`conjectures-io/conjectures-optimisation-float-kernels`，commit `978cc5b445edb9943fd9953b0a9037d97a9f33a8`，`kernels/full/incumbent/Kernel.lean`。保留官方作者对 TunedAdd、FastMul、tensor 循环和原证明的归属。Lean 为 `leanprover/lean4:v4.34.0`，full 槽，仅导入 `ContractTensor`。

| 工件 | SHA-256 | 字节 |
| --- | --- | ---: |
| 官方精确原版基线 | `5d0cef3ff21093ca05cde92e516edfe45afca8e11996ad4858e7fb2407d65868` | 33043 |
| 初期阅读副本 | `46cbe66d7c14ffbead19c6fbb7d47b1b8d161f6f2793fd7ff0442ecdb585636b` | 33044 |
| 首个冻结 Kernel.lean | `ac4f32a610e1e4b66141d8cb8d099411cda476ffe6c5cd821df0ede41c8158d7` | 34641 |

13:31 的环境回执提供官方精确文件；已逐字节核实阅读副本只多一个末尾 LF。候选由阅读副本改写，保留其冻结哈希；官方 paired gate 必须用上表 33043 字节的精确原版。各 manifest 已分列这两个来源身份。

缺口是官方 runner 尚无本轮基线／候选结果。首个最小实验选择改写 `FastMul.fastLog2`：先检查 `x >>> 47 == 1`，再检查 `x >>> 46 == 1`，其他值使用原六级二分。两个正常 24 位尾数之积位于 `[2^46,2^48)`；可直接覆盖这一常见域，同时保持所有其他 UInt64 输入的原逻辑。

证明使用原 `log2_shift`：当 `x >>> k = 1` 时，`log2 x = k + log2 1 = k`。新增 `fastLog2_eq` 接回原 `roundP_eq`、`mul_spec`。add、舍入、NaN／无穷回退、±0、次正规数以及 sum／bmm 的索引和累加顺序没有改写。编译未执行时，这只是待验收证明源码。

## 已执行与待执行

已运行 [有限整数模型诊断](../candidates/f01-mul-log2/probe-result.json)：检查全部 64 位 binade 边界附近 313 个值、20 万个均匀 UInt64、20 万个正常尾数乘积和 20 万个次正规／混合尾数乘积，共 600313 个值；与 Python 整数 `bit_length` 及原二分模型均零差异。正常尾数乘积全部命中 46／47 快捷路径。此诊断只覆盖翻译后的 helper，不能替代 Lean、完整 gate 或计时。

| 项目 | 状态／结果 | 参照与证据 |
| --- | --- | --- |
| Lean 编译／四个原始义务 | NOT_RUN | 待环境会话 runner |
| kernel replay／公理审计 | NOT_RUN | 待完整官方 gate |
| 官方逐类 checksum | NOT_RUN | 待官方 harness |
| 公共 full 时间比 | UNKNOWN | 候选／精确原版基线；未计时 |
| 配对轮次统计与独立确认 | NOT_RUN | 待有值得确认的信号 |
| 正式参赛成绩／奖励 | UNKNOWN | 未正式上传；未测当前冠军 |

本赛道按官方单一时间比评价，不能套用 DEFLATE 的大小轴与份额投影。官方 headline 为十二个计时类各自跨轮最小时间之和的候选／参照比；正式 admission 另检查至少五个配对轮次及 bootstrap。公共基线的提速不代表战胜当前冠军。

最小有效下一步是对冻结哈希运行 pinned full gate，并与同 runner 的原版基线配对计时，保留十二类与逐轮数据。任一证明／审计／checksum 失败则先修复或弃用；若正确但全路径无可复核收益，则记录该具体实现的负面结果，不仅凭 helper 操作数晋升。首候选可用即交接，CI 期间只做不依赖该结果的分析，避免积压未测变体。

## 公开源码检查

北京时间 2026-10-21 13:25:59—13:26:01 只读查询官方冠军与源码端点，原始响应及 SHA-256 见 [回执](../candidates/f01-mul-log2/source-survey/network-receipts.json)。冠军端点 HTTP 200；#174、#165、#147 的 `/source` 均 HTTP 404，响应为 `no competition 'floatlib' is served here`。这只证明本次未取到源码，不能解释为特定算法不可公开或该提交没有源码。官方中央 API 文档的 FloatLib 章节目前只列详情与 report 读取；DEFLATE 的源码发布路由不能直接假定适用于 FloatLib。

因此首候选使用公开、固定 commit 的完整参考，未借用当前或历史冠军实现，历史冠军占比也不作本候选收益证据。官方禁用构造正则、唯一 import、四个 spec 名称及 256000 字节上限已作本地词法检查；官方 policy、Lean 和 gate 仍为 NOT_RUN。

## 独立的第二个局部改写

[f01-mul-rse-threshold](../candidates/f01-mul-rse-threshold/manifest.json) 从同一原版独立派生，未合入最高位候选。仅 FastMul 的 `rse` 将三路最近偶数舍入变为 `remainder > half - (quotient &&& 1)` 时加一，否则不变。`half` 是 UInt64 的移位一，始终为正；奇偶位只有 0 或 1，减法不下溢。偶数商排除精确中点，奇数商包括精确中点，因此保留最近偶数规则。证明把比较搬到 Nat，用 `omega` 关闭阈值条件，再接回原 `rseAny_eq`。

冻结 Kernel SHA-256 为 `28a60458bc2e8a1a69d1d65f18a1d35d15542aeddc38e7744f12d70690bee3ed`，35983 字节。有限模型共检查 924800 次决定，包含小域穷举、全部移位的中点／binade 边界、均匀 UInt64 helper 和 20 万次独立整数舍入 oracle，零差异；见 [原始读数](../candidates/f01-mul-rse-threshold/probe-result.json)。这仍不是 Lean 或性能验收。

优先先验收首候选，再按 runner 吞吐检查此候选；两者独立测量前不组合。两个候选的 Lean、完整 gate、公共时间比和独立确认均为 NOT_RUN／UNKNOWN，未获任何冠军或正式奖励结果。

## 环境验收阻塞与交付边界

13:37 读取环境状态与交接提交 `62392732`：环境入口为 CI_READY，但 `publication_approval=PENDING_USER_CONFIRMATION`、`ci_runs=[]`、基线 gate 为 NOT_RUN。环境回执记载，自动审批拒绝在缺少明确发布授权时把新候选和 CI 文件推送到公开远端。发布与 CI 由环境会话拥有，开发会话不派发、不绕过该审批。

目前已完成两份独立冻结实现、等价证明源码、来源身份核对、本地词法与差异检查、有限整数模型和原始回执；没有 Lean／性能验收结论。继续堆积变体不会解决当前关键缺口，故保留这两个候选待实际回执。环境会话解决所需授权后，先跑 f01-mul-log2，再按吞吐验收 f01-mul-rse-threshold；开发依据精确编译日志修复，并对有信号的版本安排独立确认。

13:37 的根项目只读自检通过：共同入口、链接、语法、manifest 与工作流检查无失败；该自检不运行 Lean 或 CI。两份 Kernel 的实际 SHA-256 已重新核对，与 manifest 及开发状态一致。研究窗口仍止于 15:16；当前为外部审批依赖下的候选就绪状态，不代表整个验证目标完成，也不代表两小时预算耗尽。
