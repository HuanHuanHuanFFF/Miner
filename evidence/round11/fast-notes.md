# R11 fast3 独立速度端路线

首检 2026-10-08 11:25 北京时间。根任务窗口 11:14:07–13:14:07。候选基线为已正式提交过的 `r3-432-fast3`；公开 #432 原作者归属保留在 `references/round3-public-432/PROVENANCE.md`，本轮不是独立重写的 parser。#453 已退出前沿，旧 R10 中“更早同 hotkey 前沿阻止新增支付”的前提不能继续套用。当前精确几何由主线程保存的新官方快照决定。

父 Rust SHA-256：`bae8014121e4710f4a34ce63452578b4bf69121b4f695e1b1356780a019108ef`。父 Lean：`e2c200cf084eca95eb70d26c0efb04e70d88f015315610d2a54d20b6adb7cf04`。

先读取项目规则、任务索引、研究 skill 的 experiments/search-examples/mathematics、优化方法、R10 `fast3-opportunity.md`、R4 CPU 失败说明及对应候选 manifest。工作区开始时干净，分支 `codex/round10-balanced`，HEAD `196513f`；主线程负责后续分支／提交／CI。本子任务只写分配的源码、生成器、诊断及本说明；不启动 CI、提交、访问钱包或尝试 withheld 源码。

**瓶颈边界。** R10 对 R3 四块原始公共计时的诊断显示 parser 占组件中位数和的 16.39%，encoder 为 83.61%；把 parser 人为设为零的乐观模型只降低轴约 13.60%。这些是历史诊断，不是当前机器 profile，更不是可达到的收益。官方 `validator/measure/src/deflate.rs` 每 16,384 tokens 组块，然后构建各块的字面量／长度、距离和头部编码树。因此同字节 parser CPU 改动作用范围有限；只有真正改变 token 流的结构才可能间接减少 encoder 工作，仍须总压缩时间和大小双轴实测。

旧 R4 的 read-ahead 关闭、outline、fold 属性、flushzero、直接发射、布局等方案均没有稳定新增速度证据。下面两项没有修改 NICE、skip、depth、lazy、inline 或表大小；没有重复旧旋钮扫参。

| 候选 | 精确 Rust SHA-256 | 新机制 | 第一证伪条件 |
|---|---|---|---|
| `r11-fast-pendingfold` | `ccd54cde565dc2617f00e95e48cc87c23280cf54a59c2b33b016ab4451b5e34c` | 在 flush 前消耗即将被 backward fold 吞掉的 pending literals，避免写出后立即撤销；总 BACKTOK=64 预算不变 | 任一 native token 差异或 decode 失败立即拒绝等价前提；同字节总时间无可辨收益则停止 |
| `r11-fast-continuation` | `72129aa1e666d7d0faf51731b7ba6fd99922dc6b9149b5b1c6cf2067c7ee3c7a` | 仅满 258 字节 match 后，在原下一次 head 已无法通过原前缀／距离检查时，缓存同 distance 的合法前缀候选，下一轮仍用原 probe 扩展 | decode 失败立即停止；实际替换为零、总时间退化或两轴不能接近当前前沿则关闭，不继续扫阈值 |

两份 Rust 已交给主线程冻结，后续不覆盖。各复制父 Lean，状态均为 **UNADAPTED / UNKNOWN**，不是已通过证明。`scripts/build-round11-fast.py --check` 核对生成字节；生成器将 helper 和单一 run1 调用点反转后，必须逐字恢复父源码，其他路由和常量保持原样。

**pendingfold 的保持条件与证明代价。** 原 run1 先将 `ls..p` 写成 literal tokens，再由 `fold_w` 消耗这些 token。新 helper 先从输入向后比较相同距离，最多吃掉 pending 区间、剩余 match 长度和原 token 预算允许的字节；只有 pending 全部消耗后，才把剩余预算交给现有 `fold_bt` 扫已写 tokens。原累计端点 `p+l` 不变，因此搜索、插入和 read-ahead 调度保持。

等价论证依赖 **run1 的有效状态**：`Dec input out nt ls`、`ls<=p`、完整输出容量、原 MatchAt 和合法距离／长度等条件。不能把本地 Python 可增长列表模型升级为任意 slice/任意 nt 的 generic helper 定理。正式证明需给 pending 循环维护 MatchAt 与剩余预算，再组合 `flush4_spec`／`fold_bt_spec`，并把新 helper 的 Dec/MatchAt 规格接到 `main1_loop_spec`；现有 fold_bt 定理位于后面的 E section，需要合法重排依赖或提供前置引理。证明成本中等，先看收益再做。

已执行的 Python 模型有 30,000 个固定种子用例，覆盖 0/1/4/63/64/65/127 个 pending、长度 257/258、距离边界、64 次预算以及跨入旧 token。结果：reference/新调度的 nt、p、length 和计数前缀相同；记录 pending 消耗 195,139 字节、预算打满 2,099 例、length cap 5,241 例、进入旧 token 3,977 例。它只检验模型调度，含不要求 decode 的任意旧 token-tag 组合；不是 Rust 编译、全 parser 等价或性能证据。回执在候选 `model.json`。

**continuation 的保持条件与证明代价。** 原 head 候选有效时绝不替换；只在刚发出最大长度 token 后检查一次备用前缀，既不扫描整段匹配，也不维护新表。保留原 hash slot，候选位置改成 `p-d`，缓存字为现有 `be8` 的返回值；原下一轮 `probe_m` 提供真正的 MatchAt。与旧 `round3-tiny-rep1` 在小输入各位置先试上次距离且改变 tie 优先级不同，本项只针对大 run1 的最大长度截断边界和原候选失败。新增合法匹配仍可能改变后续规划及编码分块，**不保证输出大小单调**。

理论上只需新 helper 证明返回 slot 范围、candidate 不在未来、缓存字等于 `word8`；原 `MainInv1` 本来允许任意满足这些事实的候选，搜索 schedule 正确性不在原义务内。没有新增主循环状态，总性／规格迁移可能较低，但须真实提取接口后核对，当前未适配。

**已准备、尚未执行的 runner 判别。** `scripts/research-round11-fast.py` 由 `spec.fast_diagnostics=true` 或候选名列表启用，未请求则早退。冻结与计数插桩版本各跑 28 公共和 416 固定合成输入，逐项验证 tokens 相同及 decode；pendingfold 另要求对 fast3 token 相同；continuation 允许变化并保存文件清单。计数包括 pending 被吞掉字节、continuation 满长边界、原 head 失效、备用 key 检查与实际替换次数。来源 SHA、公共输入 SHA、harness SHA、run_id/git_sha/batch、逐例数据和失败日志存入 `RUNNER_TEMP/round4-receipts/fast-diagnostics`。编译 180 秒、运行 240 秒 timeout；不采微函数时间，不把 relaxed atomic 调用计数作硬件读写计数或计时占比。

本地仅执行生成、反转审计、30,000 模型和诊断注入 self-check；没有编译 Rust、执行 Lean 或新增大型依赖。实际原生等价、官方提取、配对两轴和完整 gate 均等待主线程临时 Linux runner。

## 首批已派发与证明连接预审

主线程于 11:27:13 派发 probe-a / run `37722786008`，冻结提交 `02e8095`。此处只记录已启动，不预填运行结果。主线程给出的官方快照 28214 的速度端门槛：固定 #453 大小时需时间严格低于约 0.4342678（相对 #453 再快约 0.82345%）；固定 #453 时间时需大小低于约 36.6646026%（减少约 0.335126 pp）。旧同 hotkey 前沿为空。门槛和新候选公共到正式迁移仍需分开：它们不使任何当前候选自动通过私有准入。

等待真实提取期间，已按父 Lean 实际源码预审 continuation 的最小连接；**尚未写入新 Lean 定理，也没有假造提取签名**：

- `Parse.lean:3586` 的 `MainInv1` 只要求 `ps < N`、`pc <= p`、`pw = word8 input pc`，不要求缓存候选仍等于 head 的当前单元。
- 新 helper 的目标规格可以只声明返回 slot 等于输入 `a`、候选位置不超过 `p`、缓存字等于该位置的 `word8`。前提为 `lim+8=input.length`、旧候选 `c<=p` 和旧缓存字正确；slot 界由原值恒等传回。`span`、`d`、`km` 无需额外全局不变量，因为新分支自行检查。
- `p<lim` 与上述 `hlim` 足以证明第一次读取 `p+8<=input.length`；`d<=p` 再给 `p-d+8<=input.length`。两次都复用 `be8_spec`（父 Lean 第 1334 行）。不必证明前缀筛选最优性、哈希位置归属或旧距离检测的性能含义。
- `ahead_fix_m_spec`（第 3201 行）已经提供旧缓存的三个事实；新规格可注册为 `@[local step]`，放在该规则之后。`probe_m_spec`（第 3218 行）及 `FoundAt.real` 继续证明真正的匹配；因此没有新的 MatchAt 推导、循环或主循环状态。旧 `main1_loop_spec` 的 `step*` 可能直接消费新规则，仍须真实 Funs 的返回 tuple、分支和调用顺序核验。
- 预计最低证明改动为一个无循环 helper 定理，最多修补主循环自动化收尾；任何估计均非 Lean 验收结果。若收益成立，另建 `r11-fast-continuation-proof`，保留首批字节。

pendingfold 的额外成本也已定位：`MatchAt.back_lit`（第 2228 行）可直接用于未写出字面量的向左延伸；但必须新建维护 `ls<=p`、原 `Dec nt ls`、`MatchAt p l d`、`p+l=E` 和预算／终止量的循环不变量，再调用 `flush4_spec`。跨入旧 tokens 后可用 `fold_bt_spec`，其两条定理目前在第 3768／3798 行、位于 main1 之后，需要不破坏依赖地前移。不能直接套 `BackInv.lit`，因为其 Dec 指向的是已写出 token 的末端；本项保持只估计，不与 continuation 同时展开适配。

## 真实提取与第一份 continuation 证明候选

11:41 已读取 probe-a 的 `extraction/research.json` 和实际 Funs，两个冻结 Rust 均获官方 extraction accepted，proof 均为 NOT_RUN。continuation 实际 Funs SHA 为 `1e4de3ba6d82b1123ebac92c68dc4f9f85f7f662600174021e0615000febb820`；新 helper 的实参顺序为 `s p lim span d a c cw km`，主循环在 `ahead_fix_m` 之后调用，主循环返回状态仍是原十元组。其 fallback 代码在提取中出现两个分支副本，但没有新增循环或状态。

已新增独立 `candidates/r11-fast-continuation-proof`：Rust 保持 `72129aa1e666d7d0faf51731b7ba6fd99922dc6b9149b5b1c6cf2067c7ee3c7a`；Lean 为 `57df49048ddf50bb8219fd88779dde2e1381f756299ad3db4abe3086e12f1cfa`。与父 Lean 的唯一差异是 `r11_continuation_spec`，置于 ahead-fix 与 probe-m 两条规则之间，声明原 slot、候选界和缓存字事实。无新增 axiom、sorry 或义务替换，所有原定理原文保留。生成器 `scripts/build-round11-fast-proof.py --check` 和反转／实物 SHA／参数顺序审计已通过；`proof-audit.json` 列出实际接口及剩余检查。

状态仍为 **ADAPTED_TO_REAL_EXTRACTION_UNCOMPILED**：本地未运行 Lean；`step*` 对新 helper 两条分支的收尾和旧 main1 自动消费新规格仍需真实 gate。主线程根据性能决定是否投入。

已直接读取并重加 `diagnostics/fast-diagnostics/fast.json` 的逐例计数：两份各 444 例均 decode，冻结／插桩 token 相同。pendingfold 对 fast3 全等；公共 helper 调用 1,274,968 次，其中 407,829 次有 pending，吞掉 44,991 个尚未写出的 literal。continuation 公共满长边界 2,063 次、原候选失效 248 次、实际替换 237 次；12 个公共文件 token 改变，全部 444 例中 32 例改变。此时公共压缩大小和配对总时间仍未收到，不据次数宣布收益。

## 首批关闭与最后一份跨 gap 探索

随后完整 probe-a 数据到手：pendingfold 两块相对 fast3 慢 0.742774500%／0.695778837%，均值 **+0.719276668%**，公共 bytes 不变；continuation 慢 0.609618120%／0.483303492%，均值 **+0.546460806%**，大小 **-0.006406698 pp**。同源码 shadow 两块 +0.517555615%／-0.174695750%，均值 +0.171429932%。两候选当前两轴都不足前沿，停止完整 gate；已适配未编译 continuation proof 保留，不把它标成接受。没有把两个负版组合。

为重新核对实际瓶颈，11:56 从本批 fast3 的两份原始 JSONL 重算 56 个文件／块，每文件每组件各取 11 次 measured 中位数后等文件平均：parser 占组件中位数和 **15.7968106%**，encoder 占 **84.2031894%**。总轴为 0.4283697544；保留实际 encoder、将 parser 理想化为零的反事实轴为 0.3718825681（改善 13.1865487%）。这再次说明单纯减少 parser 写入范围有限，但不是可达到的性能预测。输入回执 SHA 分别为 `366ff1bb38490161d0f9a5833bde31c3140579af712438b82a20de3ec2bb2e50`、`b98a8179f992ada090d2a3b30d5ff0e0af5b913121536cd04c18a10a4f298efc`；路径为该 run 的 `gate/round{1,2}-r3-432-fast3.jsonl`。组件中位数和与 median(total_s) 并非同一统计量，未将其当成精确总轴分解。

最后只新增 `r11-fast-gaprepeat`，父版本仍为原 fast3，Rust SHA `d9871c561eea64f98c7e976644198c5798f028c8d6e8c17b83f34feae74da9b7`，父 Lean 原样复制、未适配。生成器 `scripts/build-round11-fast-gaprepeat.py --check` 已通过；一处 run1 probe 调用替换及一个无循环 helper，反转精确恢复父源码。

机制从立即匹配边界换为**实际 literal gap 内的失败搜索点**。run1 延迟写出 pending literals，所以 `out[nt-1]` 仍保存上次 match token，可用作隐式距离缓存，不增加 loop 状态或表。helper 先运行原 `probe_m`；原匹配合法即原样返回。仅在原 probe 失败且 `ls<p`、有可读的旧 token 时，从该 token 的合法编码范围解出候选距离，再调用原 `probe_m` 一次。输出中该值只提供候选，完全不承担“它必然是正确 match”的证明前提；新 bytes 仍由 probe 验证。原短 match 的立即末端不尝试，因为它通常刚由下一字节不等终止；跨过已知 literal 后相同偏移片段可以重新出现。

这与旧 tiny-rep1 的“tiny planner 各点优先试上次距离并改变 tie 顺序”不同，也不是把关闭的 258 边界条件放宽：它换用了延迟输出提供的隐式历史、只在已跨 gap 的原失败搜索点执行，保留每个原有效 probe 结果。可能减少 literal tokens，从而减少 encoder 的频率统计／块数／符号工作；但新增失败探测也可能更贵。没有大小单调、收益或前沿保证，不扫 gap 宽度／长度阈值。

原生诊断沿用 `fast_diagnostics` 接口，新增 `calls/original_match/gap_with_previous_token/attempts/rescued/rescued_bytes` 六个计数，要求 444 例 decode 与 frozen/插桩 token 相同，允许且记录父 token 差异。诊断脚本现 SHA `820debef0c7dcad5e16a1e22f63bdd0c871c09bb6d15051810bcebfd46e43f47`；两旧候选的插桩源码 SHA 保持原样。当前尚未运行新 Rust，也未取得新提取或配对结果。预计证明仅需在 `probe_m_spec` 后加一个返回同样 FoundAt／length／distance 界的 wrapper 规格；主循环 tuple 不变。新提取前不冒充真实接口或可编译证书。
