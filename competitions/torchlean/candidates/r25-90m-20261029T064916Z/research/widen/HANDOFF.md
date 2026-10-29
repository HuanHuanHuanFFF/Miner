# R25 Widen carrier 当前交接

本方首次工具 UTC 06:52:26；共同截止 08:19:16，不延长。首段06:52:26—07:20:09后释放并发位；07:41:15由主控按实际CI反馈唤醒，空档不算持续执行。新阶段见prepare-bridge/HANDOFF.md和prepare-source-receipt.json。应用huan-open-research、huan-collaborate文件交接；源码状态按verification-before-completion。

- **精确首包已接受**：`Kernel.lean` 54289 B / `a88c70e52a12c7c9e60bdd3e021323772353fc1e5e46290bdd71c1db97185bd3` 在CI40834710293通过原full proof gate、Submission/VerifyExact replay与6 helper allowed-axiom审计，55.314s，默认资源；原件已复读并hash。`WidenCarrier.lean` 15804 B / `2b6dea8d4abf7bb0b37046022d6c0effd1f4aa2008cc8ae2ea7f1f6b6f44230e` 是不含正式obligation的独立片段，不能把它混作同一受验Kernel。actual/finite/prepare均不继承PASS。
- **最小诊断**：`WidenShiftProbe.lean` 1242 B / `bee26f39749be591b17464e6a9854eaefd142f37e6bfd7c5b731eb996d09e65d` 仅测 W7 的 `hcNum` 修复。R24 run `40810384656` 原 `full-build-output.txt` 只见两处 `↑536870912` mismatch；旧35 roots FAIL，W7 NOT_RUN，不继承旧 core 的接受。
- **依赖与改动**：`WidenSupport.lean.inc` 3182 B，包含 canonicality、raw32 字段与 normal decode；`expWord_toNat` 直接展开 UInt32 shift/mask，排除 `tableExp_nat/tableIndex/R2W01b`。W7 所有 inline runtime 声明完全不变，全部 B2 runtime 不需要。ContractExact → Values → Decode → Congr → Round → FloatLib；Limbs 提供 Mathlib。固定 Lean4.34.0 / FloatLib0d918257，详见 controller 固定依赖回执及本目录 `import-closure.json`。
- **当前验收状态**：首包完整Kernel与六根验收已完成，证据绑定在prepare-bridge/prepare-source-receipt.json。独立ShiftProbe、actual/finite/prepare均尚未验收；是否安排下一检查由主控按overall吞吐决定，本方不排队。任何实际报错先绑定精确SHA/行号/原错误，不扩大simp或资源。
- **实际 runtime 连接已成源**：`actual-bridge/ActualWidenCarrier.lean` 19467 B / `df8f957dd84e1e33a5ac83103b026ceb53115ee890cb379ab9ea984174c9dce4`；完整 Kernel 57952 B / `1961bff12e3b1b45ec63cca0cfd120ee714923189f1a16d21cc70ae651e4cb0b`。原 sx/sr/fastLog2/widenBits 仅1012 B，6新根连接实际normal/±0与W7。07:02:50交，NOT_RUN。
- **总 finite 连接已成源**：`finite-bridge/FiniteWidenCarrier.lean` 37776 B / `5460ffc4a24fbd5eb833396af20910a112943e707b7a98d90b316d94c110c443`；完整 Kernel 76261 B / `e5613ee190d4185d665b0cd52482e37dc0770ac468c19ee676cac7a6ba964ab6`。原log2证明仅3183 B；修旧subnormal count_nat独立rfl风险，复用W7 native桥，通用shift改显式cast/zpow路线。5新根将实际非零subnormal纳入全部finite。07:07:36交，NOT_RUN。首组及actual组保持不变。
- **真实producer新片段**：prepare-bridge/PrepareAgreement.lean.inc 6042B / `b08041257148669ba988ca15a319f0ad188aa6a5a95205b2555f24fd12dcf5a0`，原Prepared/index32/prepare补片883B / `b785d5e7a97703f717c7a310cddafb8376ee4ff2d9cb1af0897f1c3ecd261880`。实际prepare→forIn→fold→size/finite/getter的可组合Lean源码，NOT_RUN；必须先过prepare_eq_forIn。没有新大Kernel或CI排队。peak/Tail/radius/native语义接入仍缺。
- **覆盖缺口**：仅首包normal/±0 W7已受验，其他新源码、prepare/getter/Tail/checker/rounder/fallback组合未接受，没有性能成绩。旧Math9资源条件与新包不同已记录；本轮首包实际默认资源已通过，不能据此继承actual/finite资源或证明结果。

`build_carrier.py` 可重建首包；`carrier-receipt.json` 绑定所有输入/输出哈希。`upstream-source-evidence.json` 为只读固定 GitHub 内容回执，含官方来源许可 UNKNOWN 的全文，**公开 allowlist 排除该文件**；公开依赖说明使用 `import-closure.json`。无本机 Lean、无自发 CI、无 Git 操作。实耗 token/cache/reasoning 均 UNKNOWN。

后续只读接口见 `PREPARE-INTERFACE.md`；`producer-prefix-receipt.json` 已逐字节确认本轮分析的完整实际PortableF64 namespace与R24 run40811305126的cost2候选一致。最小Prepared/index32/widenBits/prepare/ceilLog2/sumRemaining正文合计1600B，另加现有sx/sr/fastLog2即可，无需完整B2。该核对不是producer证明或新计时。
