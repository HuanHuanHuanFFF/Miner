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
