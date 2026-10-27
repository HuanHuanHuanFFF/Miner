# R14：纯整数 add 对齐与小位移 RNE 首份片段

时间：2026-10-25T00:08Z。接开发 20261024T230553016Z 请求；只交数学片段，不增候选或编译队列。

- `astra-word-add-alignment1.lean`：4007 B，SHA-256 `3628f637670621b049cfb3935e3e782ea2aa8403193f461a060082cb3a7ff5ca`。提供高指数尾数左移到低指数、同号加/异号 gap>=2 减的 exact_high_low、通过 addDyadic_comm 得到原输入反序 exact_low_high，以及显式 finite decode 到 Model.Spec.add 的桥。交换律只在已解码 dyadic 层使用，未声称 raw add 的 NaN 交换律。
- `astra-small-shift-bias1.lean`：3173 B，SHA `cc00612794e473d1e404606df2b502cda0321f0c6ac086bfb542dfed8dd03b66`。新命名空间 R14SmallShiftBias；Nat 和 UInt64 的 t.toNat 1..8 偏置 RNE，p<2^48，逐步证明加半/减1/加奇偶位不回卷。原 t23/24 片段保留。
- `astra-biased-rne2.lean`：2484 B，SHA `e9abe15eaebf5dab13f717558292f49871f8fdde07b3075145915a493bb5db0a`。仅修旧片段局部 let parity 的展开：`dsimp only [parity]` 后 `rw [UInt64.toNat_and, hshift]`。旧 3515 源文与 2f88 完整候选不改。

旧 `rw [parity,...]` 的问题已经固定 Lean 293d 源码交叉核对：Elab/Tactic/Rewrite.lean 对 local ident 不取全局定义方程，直接交给 Meta rewrite；Meta/Tactic/Rewrite.lean 要求实参类型为 Eq/Iff，parity 实际类型 UInt64。证据及原始文件哈希收在 `astra-word-add-fragments-intake.json`。这项是源码层确认，不是编译回执。6f88/新组合中若复用了旧 word_bias，应在新版本中带入修正版，不修改冻结原件。

以上全部 **NOT_COMPILED / NOT_RUN**。alignment 的具体 API 来自已存固定 FloatLib AddDyadic/Proof.lean，未本地跑 Lean。后续我继续补 gap<=7 的 N/h/t/完整 E<=256 边界与一比特 log2 恒等式，开发可先接独立对齐片段。Git/index/公开发布/CI 仍归开发协调，新公开授权仍等待人类。

完整路径基准：`D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z/`。
