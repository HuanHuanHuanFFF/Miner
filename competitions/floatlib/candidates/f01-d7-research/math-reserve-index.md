# R7 可复用数学与证据入口

初次审查范围为 W01、W01b、W02–W09、W08b 共 11 份交付，22:12:04 UTC 开始、22:57:04 UTC 预算上限，当时按分工排除 W10。随后独立审查 W10/W10b，当前覆盖 **13 份交付、10 项结论**；新增 92 个来源/日志/审查文件逐项重哈希，当前索引共 270 个文件。只读原件，没有本地运行 Lean；原 11 份完整性回执的冻结哈希仍由 `8b016d66` 定位，13 份回执另列，未覆盖历史字节。

以下 **10 项**分为 1 项已用组件、7 项数学储备、1 项具体证明修复、1 项代码生成证据。网页固定 Lean 4.34 的普通编译/规格/公理日志，与精确候选原版 full gate 分列；新整合与性能不继承网页结果。原件均为 **LOCAL_ONLY**，精确相对路径、source/log SHA-256、退出码与 `E:/Download` 原包恢复位置保存在同名 JSON；本页只链接已核对本地 Git 字节的候选。

当前 [c760 非NaN基座](../f01-r7-nonnan-runtime/Kernel.lean)（`c7605688…`）已有 805/807/809 原版 gate；[60f 保留包](../f01-d7-direct-nonnan/Kernel.lean)使用该基座。W05 复制的既有 NativeBridge/NotNaNProbe/R7Native 不重复计为新储备，也不把 W01/W01b 误记为这些既有非NaN证明的原创来源。

| 编号／交付 | 可迁移结论及必要条件 | 实际证据与当前边界 | 下个外部证伪点 |
|---|---|---|---|
| MR01 · W01/W01b · **已用，不计储备** | `R7W01.mul32_not_snan`、`exec_add_mul_absorb`：quiet NaN 可吸收后续逐步 mul-then-add；`R7W01b.rawExecQuietGuard_eq_isQNaN` 连接原始 word 与实际 carrier。 | [9a fullpath](../f01-r7-nan-replay-fullpath/Kernel.lean)（`9a2a05cd…`）806/808 原版完整通过；[7ac raw guard](../f01-r7-nan-replay-word/Kernel.lean)（`7acff965…`）808 完整通过但运行版停放。没有声称当前 60f 采用全部 9a/7ac 路径。 | 新组合仍须重跑精确整包。一般 sum 的后续原始 sNaN、FMA 都不满足这里的吸收条件。 |
| MR02 · W02 · **数学储备** | `R7W02.step_eq_add`、`sumSuffix_eq_fold`、`sumSuffixAtCut_eq_sumSpec`：真实前缀已为 **quiet** NaN 时，后缀仅扫描原始 sNaN，保留最后一次 quieted word 的符号/payload。 | 精确 `3651723f…` 源/成功快照一致；普通编译与公理打印均 exit 0。原 List 适配器有分配成本。[0fe 新整合](../f01-r7-sum-native-repair-proof2/Kernel.lean)（`0fe7884f…`）只复用部分 step 引理并另写 Nat 适配，仍 NOT_RUN。 | 证明当前实际循环的前缀 quietness、读取及后缀映射。有限 seed `0+1`、signaling seed `7f800001+0` 都反驳无前提扫描。 |
| MR03 · W03 · **数学储备** | `R7W03.sumSpec_from_exists_original_snan`、`findLastSignalingRaw_some_eq_sumSpec_raw`：实际 +0 起点的一般 sum，只要含原始 sNaN，最后原始 sNaN 决定完整原始结果；无须另给 quiet 前缀。 | 精确 `2ac243dd…` 整源/快照、编译、公理日志均闭合。`findLastSignalingRaw_none_iff` **只证明无原始 sNaN**，不决定 sum 值；原 List.reverse 实现尚非运行优化。LOCAL_ONLY。 | 无分配扫描必须另证 some/none 两条实际接口。任意 signaling 初值不在一般 fold 定理域内；取“第一个 sNaN”已有逐位反例。 |
| MR04 · W04 · **数学储备** | `R7W04.self_beq_eq_not_isNaN`、`nonNaN_eq_true_iff`：实际 IEEE Float32 的 `x == x` 恰好识别非NaN，含 Inf、±0、次正规数。 | 精确 `3668cbf3…` 编译/公理均 exit 0；[1f4 整合](../f01-r7-self-nonnan-guard-proof2/Kernel.lean)（`1f4d31aa…`）尚未继承完整编译/gate。 | 编译整合并查真实调用处 C/汇编。不能把命题 `x=x` 或 raw word 相等替代 IEEE BEq；±0 比较相等但位型不同。 |
| MR05 · W05 · **数学储备** | `R7W05.add_toFloat32`、`mul_toFloat32` 是全输入 canonical 同态；`sum_first_nan_event`、`dot_first_nan_event` 以前态非NaN、前态匹配及原始输入恢复精确 quiet word；含实际 `sumSpec_first_event_repair`。 | 精确 `7ebaf282…` 整源/快照、编译及公理日志闭合；[a4f 探针](../f01-r7-canonical-bridge-probe-policy1/Kernel.lean)（`a4f26514…`）的新映射仍 NOT_RUN。canonical 等式不是原始 NaN 元数据等式。 | 用当前实际循环建立事件前态不变量和后缀接口。直接导入已NaN native 结果得到 `7fc00000`，原步修复可为 `ffc00011`，不能互代。 |
| MR06 · W06 · **仅代码生成证据** | `R7W06` 的 Guard/Contexts/NativeLoop 提供实际上下文 C、GCC/clang 对象与汇编；既有 guard 数学不重复算储备。 | 所查 4 份对象编译命令均 rc 0。plain proof-driver **exit UNKNOWN**，不能把其 PASS 文本当退出码。没有当前候选原版完整 gate/收益证据。LOCAL_ONLY。 | 对精确整包调用处复查内联、分类、装箱及完整成本；小 guard 的代码形状不能推出整包提速。 |
| MR07 · W07 · **数学储备** | `R7W07.checkpoint_initial/commit`、`blockedSum_eq_sumSpec`、`blockedSum_raw_eq_sumSpec`：任意正 K、任意长度/原始 Binary32 输入；失败块从保存的块起点和前态重放完整原始后缀。 | 精确 `2e39ffec…` 整源/快照、编译/公理闭合，连接真实 sumSpec。内部完整前缀结论需要真实 checkpoint；未证明运行次数/成本上界，未形成当前 full gate 候选。LOCAL_ONLY。 | 检查 0/31/32/33、跨块 Inf invalid 后出现晚 sNaN 的精确回放。不能从失败块末端或 canonical NaN 继续，也不能把块总和重关联。 |
| MR08 · W08/W08b · **后续闭合的数学储备** | `R7W08.nat_segment_comp`、`usize_blocked_eq`；W08b 的 `flat_eq_natBlocked`、`flat_eq_usizeBlocked`、`all_three_eq` 对 **K=32、Array Float32、相同任意 UInt32 fallback** 成立，含空数组/任意初值。 | 原 W08 的 flat gap 保持历史 **NOT_PROVED**；后续 W08b `96e99343…`/`e9e7eace…` 与 6 份原依赖哈希吻合，8 模块 final-recheck 明确 exit 0，新增 10 项公理打印仅三允许公理。这是 native wrapper 等价，**不是 raw sumSpec 整合**。LOCAL_ONLY。 | 以当前原始 decode/fallback 实例化并证明 sumSpec。内部 `nat_blocks_eq_final` 保留“非空后缀或前态非NaN”条件；不能推广成任意 K、任意 raw payload 吸收。 |
| MR09 · W09 · **完整源码证明修复储备** | `Submission.NativeFinal.dot_eq` 对部分应用 step 先 `congrArg` 到 Fin.foldl，再 `funext acc i`，逐点改写，运行定义不变。 | 原 `b1696ff9…`、同 token simpa 稿 `3b7b8744…` 原日志均 exit 1；[0e8 精确修复](../f01-r7-nonfinite-combined-proof2/Kernel.lean)（`0e8bc05c…`）整源编译 exit 0，另有四个原始全输入 spec 类型断言与 5 项公理审计 exit 0。**不是原版 full gate**。 | 验证精确 0e8 的完整 gate；各 proof2 派生稿单独编译，不继承 0e8 结果。源码运行定义不变也不等于机器码身份已证。 |
| MR10 · W10/W10b · **数学储备** | 实际逐步 `ExecFloat.mul` 输出永非 sNaN，故 `add +0 (mul a b)` 可替换为：只将该乘积 raw `80000000` 改为 `00000000`，其他 word 原样保留。一般 q 版本仍要求 q 非 sNaN。 | 精确源/成功快照/退出码均闭合，W10/W10b 原始公理日志各 218/26 个声明仅三允许公理。[独立审查](zero-seed-proof-review.md)记录完整单位的 policy 禁用词与朴素拼接超 256000 字节；W10b 原始字 helper 的 C 消除了旧 once 分支，但尚非整包 C/计时。 | 提取最小允许依赖，编译实际 Submission 桥及 n=1 分支。全部新适配、leanchecker、原版 full gate、收益仍 NOT_RUN/UNKNOWN；不能直接删除初项 +0，负零反例仍须处理。 |

关键原始公理日志已直接解析并与机器审计交叉核对：W02/W03/W04/W05/W07 分别为 **52/115/38/206/273 个声明**，不是报告自述。对应成功 source 快照均与本次引用整源逐字节一致；W09 的 SpecAudit 也包含精确修复源码完整前缀和四原规格类型断言。原版 gate 则另核到 9a、7ac、c760 的 `mode=gate, passed=true, stage=score`、kernel replay、允许公理、26 cell/25 轮原始记录。

证据缺项保持原样：W01 编译命令有 exit 0，但其成功快照未随包提供、命令未记 source hash，故网页原件的精确编译字节绑定为 UNKNOWN；不因此撤销另有原版 gate 的候选。W06 及原 W08 的一般 proof-driver 缺显式 exit 均写 UNKNOWN，W08b 后续明确的重验单列。所有新储备的实际整包性能与冠军比较仍 UNKNOWN；没有重写旧阶段当时的 gap 或状态。

## MR08 的精确接口与缺失组合桥

八个 LOCAL_ONLY 模块均在原包位置，完整工作区相对路径、SHA 与显式 exit 记录在 JSON 的 `MR08.wrapper_modules`：W08 原包的 `src/NatLoops.lean`、`src/W06GuardProof.lean`、`src/GuardBridge.lean`、`src/USizeBlocks.lean`、`src/USizeProof.lean`、`src/SegmentProof.lean`，以及 W08b 原包的 `src/NanAbsorption.lean`、`src/FlatEquivalence.lean`。不为这些未跟踪原件生成远端链接。

三个原始定理签名如下，原上下文为 `namespace R7W08b; open R7W08`，仅略去证明体；`flat/natBlocked/usizeBlocked` 均是 **固定 32** 的 W08 原函数：

```lean
theorem flat_eq_natBlocked (xs : Array Float32) (initial : Float32)
    (fallback : UInt32) :
    flat xs initial fallback = natBlocked xs initial fallback

theorem flat_eq_usizeBlocked (xs : Array Float32) (initial : Float32)
    (fallback : UInt32) :
    flat xs initial fallback = usizeBlocked xs initial fallback

theorem all_three_eq (xs : Array Float32) (initial : Float32)
    (fallback : UInt32) :
    flat xs initial fallback = natBlocked xs initial fallback ∧
    natBlocked xs initial fallback = usizeBlocked xs initial fallback
```

接到 W07 仍缺一条实际 raw 组合桥：对任意原始 `x : Vector Binary32 n`，令 `native = x.toArray.map ExecFloat.Binary.toFloat32`，`initial = toFloat32 posZero`，`F = (R7W07.blockedSum32 x).raw.1`，证明 **`R7W08.flat native initial F = F`**。之后才可用 W08b 改写到 USize wrapper，再由 W07 接到原始 `sumSpec`。这条组合义务当前没有在所审源码中证明。

它需要四个具体衔接：实际数组读取与原序 fold 的 canonical 同态；非NaN结果的完整 word roundtrip/UInt32 codec（含±0与Inf）；NaN时 fallback 等于精确原始结果；空输入的真实 +0。若实际 fallback 使用保存 checkpoint 的原始后缀，必须另证该起点、前态和区间确实给出同一个 F，不能导入已NaN native 结果替代。

此外，W08 的 `fallback : UInt32` 是已给定的值，不是惰性函数。把完整 raw replay 先算成 F 再传入，会保留这项计算成本；上述数学组合桥即使成立，也没有建立候选“只在 NaN 冷路计算回放”的控制流或收益。实际冷路适配和完整成本仍须另验。
