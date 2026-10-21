# R 检查点 07：最终具体修补与已验收native路径

2026-10-21 11:15:51 UTC。已进入冻结／回收阶段；不增加算法候选。以下是已有乘法包的具体编译修复。

CI39589987380中，native-sum原包 `75524a31...` 的statement与bench build通过。native-both的数学主体已无roundWithAccuracy残留目标；实际错误只有：

1. D包749行：`/-- Stage 1's mul... -/` 文档注释后插入 `namespace`，Lean期待声明。把该前置文档注释改为普通 `/- ... -/`，或放回实际mul定义前。此问题在D集成位置，R桥接源本身不包含该注释。
2. 三处 `Numerics.Dyadic.mk.injEq` 未解析，随后hdecode字段投影失败。R桥接处在Submission.NativeBridge，原公开源在FloatLib之下；这属于命名空间适配。为避免自动生成注入引理名称，改用 `congrArg FloatLib.Numerics.Dyadic.significand/exponent (Option.some.inj hdecode)` 取得所需字段等式。

新修补 `native-mul-bridge-proof2.lean`，SHA-256 `697ed97c9ba9988aa472c47eeaef5885311037cd511196f9e89e3f37d739deff`，10235字节。只替换上述字段抽取，所有声明与运行算法不变。NOT_COMPILED；D可将它用于已有native-both证明修复，旧失败原件保留。新长实验截止不延长，是否只作短编译回收或来得及完整确认由D依据剩余窗口决定。

独立原始回执审计已确认native-add-proof1 `7f51b433...` 在run39589111347完整通过：仅允许三公理，12类25轮；整体／起始参考0.623247，add0.619428、sum0.378156、bmm0.584480，mul0.999893。尚未独立复测，不等于冠军同机成绩。原件路径与SHA在 `window-audit.json`，可运行audit-window.py重新核验。

本轮已经实证：pinned公开native加法逻辑模型路线可通过官方完整gate，并显著加速；单靠通用循环改写不是巨大差距的主要解决方案。native乘法与原生累加状态的完整收益仍待现有作业。
