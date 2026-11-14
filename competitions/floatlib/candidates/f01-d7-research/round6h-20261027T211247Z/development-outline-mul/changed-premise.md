# 决策：只买冷边界能否改变真实 caller 的判别证据

原 748999 的新算法成本已经测过，不能用另一个 seed 或 leaf symbol 重新包装。旧 40432634558 完整 Suite 诊断保留四个 block：MUL guarded/control 为 1.017893301、1.136068921、1.024996980、0.980539722；whole 为 1.000853380、1.085395764、1.010710488、0.990035177。共享 SUM 的明显波动没有归因，不能删慢 block。旧 conclusion 是停放该精确运行体的昂贵公开证明投入，不是证明整数乘法永远慢。原 00ab、b271、f529 结论保持其原精确源、caller、基准和输入范围。

旧实际完整 caller 的接受路径为 `0..2d → 76..88 → 122..12f → 33d..3a4 → c06..c12`（hex），有一次整数乘积／bias RNE，无热 call、FP、表或显式数据 spill，却仍有 `push rbp/r15/r14/r12/rbx`、`sub rsp,16` 及对称恢复；B2 回退体还内联在同函数。原定义级 diagnosticEntry 的同类结果不是替代品；真实计时 Main 才是本次基线。旧完整诊断两个 MUL 闭包都是 captured Bool arity3，原 MainFull 是静态 arity2，这个限制继续标明。

本次改静态调用边界：完整旧 748999 为逐字前缀，旧 normalCore、守卫和接受结果全留；追加全局 `retainedMul x y`，标 `@[noinline]`，新 inline alias 只把它传给原 guardedMul。冷 wrapper 仍调用原 Submission.mul，normalCore 后没有检查。明确的新成本假设是 clang 可把 miss 写成直接尾跳，使 caller 热路径不再继承冷 B2 的保存寄存器与帧。`noinline` 只阻止 Lean 的内联意图，不保证所有后端布局，也不等于尾调用成立，必须检查实际 C、对象与最终 caller。

原 gate 4b7 原字节 SHA `1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194`，ATTRIBUTES 原 allowlist 含 inline/noinline；没有改官方 gate、contracts、bench、pins 或环境。旧正常核文本 SHA `ce7482a93a22ead5197aacaa94e71a1d467ca69fa64e5e84aece72c3f3edd4cc` 已逐字比较。当前源 228621B，距 256000B 上限 27379B。四个 public 入口与规格是逐字 B2，不包含新乘法等价根；statement/replay 也不能替代该等式。首稿1de584/228140B仅保留为版本记录。

最小真实判别由 D 当前成本框架负责：同 binary、同 discovery plans，保留完整 guards、miss、B2 回退、boxed callback ABI 与 Suite timer/pass/checksum/cleanup，所有原始逐项记录和慢样本。按 R 协调者 23:36Z 后追加的要求，提供三个 noinline `runControl/runInlineOld/runOutline : IO UInt32`，各自调用 Suite，main只选runner，意图防止 variant比较被提升成标量 captured Bool。这个 ABI 条件相对旧成本是第二个明确变化；同一新binary中的 inlineOld 给冷边界归因对照。先核 runner → selector → 实际 typed callback；wrapper 应为静态 arity2，无新增 runtime closure 分配／boxed intermediate，接受路径仍一 imul 且无 FP/table/call，不给 normalCore再包校验。热臂 save/frame 未减少即本路线当前 NO-GO；少量减少但无整体成本信号同样不进入昂贵公开证明。若机器成本和完整测量均给新信号，再讨论新公共等式桥及原完整 D/A/B。这里不新增采用门槛，也不由指令数推周期、命中率或收益。

首段成本上限为本子任务开始后约 15 分钟，产物为最小源、统一 patch、精确 manifest、该一页决策及交接。后续余窗用于实际代码审核或独立于结果的最小证明接口；不占额外 CI、不重复 D 的 8scalar/WordADD。已用 token/cache/CI 排队成本无实时读数，记 UNKNOWN；本子任务实际 CI 使用 0。
