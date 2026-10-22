# 原始 word 非有限冷分支：证明准备

开始时间：2026-10-22 22:09:05 UTC，主要准备及复核于 22:29 UTC 完成。本次只准备本文件、exceptional-word-design.json 和 exceptional-word-block.lean；没有生成候选，没有修改已有源、Git、CI 或上传。

**状态：PREPARED / 全部新 Lean 声明 NOT_RUN。** 没有实际 Lean elaboration、内核重放、公理审计、C/汇编或完整 gate 结果。有限整数模型检查通过不是形式证明；性能与收益 UNKNOWN。

## 精确目标与边界

只替换现有标量实现拒绝“双输入指数均非 255”后的冷分支。入口证明前提保留为：

    ¬ (expField a ≠ 255 ∧ expField b ≠ 255)

局部定理把它转成至少一侧指数为 255，再证明 word 结果等于固定真实 Model.Spec，最后接到真实 ExecFloat carrier。该命题覆盖前提内的任意两个 UInt32，包括所有 NaN 符号/payload 和两种零。**它不实现普通有限输入的算术。** 已保留域外反例：±0 组合和两个最大有限值；若误把此 helper 接到普通路径，会输出错误的 canonical NaN。有限输入产生 Inf 也不是这里的入口条件。

普通加法、native 高指数乘法、LowScale 低指数分支、sum/BMM 顺序与布局都不改。0×Inf 必须在这里返回 invalid，不能复用低指数零乘法的 signed-zero 早返。

独立草稿的精确编译上下文是：在 f01-d7-nan-choice-probe 的全局 DWordNaN 块之后追加；该 probe 的 SHA 为 ad014e0b1cdc6e42d3a9bd9437e32762d840b8047be740dca8894b0108aa3cb9。依赖 nan-choice-block.lean 的 SHA 为 584ace5443838454b3687f7a93cfca07be4f9cce2c889c7196b171b7cfd4c93c。已验证 probe 等于 retained60f 原字节加两个换行和该 NaN 块。该既有 NaN 块本身也不得假定已编译通过。

## 实际 word 算法

运行定义 addWord/mulWord 直接返回 UInt32：先检查 a signaling NaN，再检查 b signaling NaN，再检查 a NaN、b NaN；选中 word 只 OR quiet bit 0x00400000。没有 Float32 canonicalization，保留完整原始符号和 payload。

无 NaN 时，add 的处理顺序与真实 Spec 相同：

- a 为 Inf：b 也为 Inf 时，同号返回 a，异号返回 0x7fc00000；b 非 Inf 时返回 a。
- a 非 Inf、b 为 Inf：返回 b。
- 其余情况：返回 invalid 常量；在入口前提与无 NaN 下，这个默认分支不可达，但保留它可直接对应 Spec 的默认分支。

mul 则在任一 Inf 分支检查另一侧是否为任一符号的零；是零返回 0x7fc00000，否则返回符号异或的 Inf。草稿采用与 Spec 完全相同的 Bool 不等式表达异或，避免另加 wordxor/符号位证明。

rawInf/rawZero 使用 UInt32 exponent/fraction 字段测试，rawSign 使用既有 native signBit；运行定义不构造 Model，不读 Nat 字段，不调用 generic toDyadic。这里先选证明短、固定 API 直接可用的字段版本。单次 magnitude-mask 比较可另证，但没有把未验证的位拆分引理混入本轮草稿。

**Option 被留在证明层。** fused addWord/mulWord 不调用 rawChoose；addWord_eq_choice/mulWord_eq_choice 只是把直接 word 运行体等同于已有 NaN Option 选择，供证明复用，没有 csimp 属性。局部静态检查确认全部 11 个运行 def 未引用 Option、rawChoose、generic Spec/toDyadic/chooseNaN2。不能据此声称编译后的分配、boxing 或分支成本已经测得。

## 具体证明桥

exceptional-word-block.lean 共 296 行、12596 bytes，SHA-256：

    b884fff04a3353c02d37a824e57aa43ea3b79834569b47601b225441023c79f1

| 草稿行 | 目标与固定依据 | 状态 |
|---|---|---|
| 42、56、70 | rawInf/rawZero/rawSign 等于真实 Model 分类；使用 NativeBinary32 的公开 expField_beq_allOnes、expField_beq_zero、fracField_beq_zero、signBit_eq 及 word roundtrip | NOT_RUN |
| 76、83 | invalidResult binary32 精确为 0x7fc00000；nativeOverflow binary32 两种符号为 0x7f800000/0xff800000 | NOT_RUN |
| 126、141 | fused word 与既有 signaling-first rawChoose 表达式相同；只按四个 Bool 判据分支 | NOT_RUN |
| 156、171 | 无 NaN 的 word 分派通过分类及常量桥精确变成 Spec exceptional 分支 | NOT_RUN |
| 190 | 既有 rejected-finite 输入守卫推出至少一个 exponent=255 | NOT_RUN |
| 201、225 | some 复用 DWordNaN selected_model；none 先推出真实 chooseNaN2=none，再用 specialDecode 得到实际 dyadic none，之后展开真实 Spec | NOT_RUN |
| 250、259 | 真实 Binary32 raw.1 到完整 Model bits 的投影及 FastMul.ofBits 的反向构造 | NOT_RUN |
| 270、283 | Configured carrier 注入性与父本 toModelExecAdd/toModelExecMul 接上实际 ExecFloat.Spec | NOT_RUN |

**已确认的 API 陷阱：** 固定库 Agreement.lean 的 ofUInt32_posInf、ofUInt32_negInf、ofUInt32_canonicalNaN、ofUInt32_signedInf 都是 private，不能按公开名字调用。草稿自建闭常量证明；这里的 decide 仅计算固定 32-bit 常量，两个符号分支不是原始输入枚举。nativeOverflow 使用库中确实公开的 nativeOverflow_eq_signedInf_of_isIEEE。

carrier_model 按已公开 R7-W01b Codec.lean 的实际投影形状写：从 raw.1/raw.2 构造 BitVec.ofNatLT，与 UInt32.toBitVec 比较 toNat，再经 Model.ofBits。没有把原始 NaN carrier 往返当作 native Float32 往返。该公开模块附带的历史验证记录保留为来源；本草稿的整合仍须重新编译。

## 精确 primary 来源

全部指向 FloatLib 0d91825727839f597fd06b22fdd038ea21480f0c；没有使用默认分支的新接口。JSON 保存原始源码片段、行范围、文件 SHA/Git blob、依赖哈希和只读获取记录：

- [Spec/Dyadic.lean](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Spec/Dyadic.lean#L36)：只有两侧 dyadic 都 some 才走有限算术，否则选择 NaN 和 exceptional 分支。
- [Model/Carrier.lean](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Model/Carrier.lean#L196)：isInf/isZero、invalidResult、canonicalNaN 和 signaling-first chooseNaN2。
- [NativeBinary32 Agreement.lean](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/ExecFloat/Backends/Word/Narrow/Agreement.lean#L51)：公开 word 字段桥、toDyadic_eq，以及后部 private 常量证明的可见性事实。
- [Native Base/Runtime.lean](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/ExecFloat/Backends/Word/Narrow/Base/Runtime.lean#L35)：UInt32 字段、原生 word/model 包装和特殊指数返回 none。
- [Native Packing.lean](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/ExecFloat/Backends/Word/Narrow/Packing.lean)：mkBits_fields 与 ofUInt32_or_quietBit，后者由既有 Dnan 使用。
- [Dyadic/Rounding.lean](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Dyadic/Rounding.lean#L80)：IEEE nativeOverflow 是指定符号的 Inf。
- [ExecFloat/Carrier.lean](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/ExecFloat/Carrier.lean#L137)：真实 ModelCodec 的 decode/encode/liftBinary。公开 R7-W01b/Codec、R7-W02/Raw 与 Step 的本地原件路径和 SHA 也保留在 JSON。

## 有限反例检查

只运行了 30 对人工定向 word、60 次操作，与既有 R integer oracle 的 AST 函数及手写预期 word 三方比较；没有执行该 oracle 的 main、随机枚举或写入其目录。依赖 SHA 为 3dfaeec2bde1364a4f06abd292f0ba265376da79e678d3827aa88bd33219ad72，前后未变。结果和可重放的轻量 checker 文本保存在 JSON；它是 Python 模型，不是 Lean 或实际机器 Float32。

覆盖双方 NaN signaling/quiet 优先级、负 NaN payload、Inf 与 NaN 的先后、±Inf 同/异号、Inf×±0 双顺序、乘积符号异或、最小负次正规 partner。另保留七种错误规则的具体反例及四对域外输入，避免普通有限输入误接此 helper。定向检查 trace SHA：

    cf5be09579eb5a1419e2d96ed2c7f28e242ed96f97ffa54926444cf0e41a04d4

## 成本、重叠与停放条件

40a special-model-proof1 已在处理相同的 generic dyadic 冷分支缺口；本设计进一步把分类及结果留在 UInt32。4a30 scalar-nan-select 的 NaN 命中与本设计完全重叠，新增空间主要是它的无 NaN exceptional miss。不能把两项收益相加，也不能因为 4a30 源中有 Option 就断言其 C 分配了 Option。

仅复用已公开发现样本 807：直接 scalar timed work 中，4a30 之外剩余无 NaN exceptional pair 为 add 3277、mul 2042；tensor 单次逻辑 raw replay 的剩余为 sum add 119、BMM add 2545、BMM mul 1173。这两种计数单位分列，未合成运行时频率。已有计数分别有 344/280 个实际历史 checksum 对照，但新草稿未执行。

R 的 quiet-suffix/prefix 与 nonNaN endpoint 会减少/替换标量 replay 调用；本设计只降低仍执行的冷调用成本，两者不是独立加速项。既有 tensor 受影响整 cell 总时间上限为 77685750 ns，覆盖 sum:specials、bmm:specials、bmm:extremes；其 26.37% 是整 cell 曝光上限，绝非本设计收益或 scalar 成本份额。

字段分类可能重复已有守卫/NaN 判据，分支、代码体积、carrier 构造仍有成本；编译器是否公共子表达式消除、inline 或 boxing 未测。既往普通 numeric-mul 变体的失败不在这里重试，普通路径维持原版。只有观察实际 C/asm 和完整同口径计时，才能决定是否值得移植；若省掉 dyadic 后仍无整体收益，应停放而非扩展到普通路径。

## 最小判别顺序

1. 先读取精确 Dnan probe 的实际 statement 结果；该依赖不通过时，不宣称本块可用。
2. 在临时固定环境追加本块，先看 rawInf_eq/rawZero_eq、两个常量、addNoNaN_model 和 carrier_model 的第一个真实目标。没有实际编译前不预判这些 tactic 已闭合。
3. 正确性闭合后，才旁路检查原始 statement C/asm 中实际 helper、generic dyadic 与分配；采集仅 discovery 使用，冻结独立确认关闭。
4. 未来运行接入沿用 4a30 已审过的 closed proof namespace 前移布局；本文件的全局追加 probe 不是运行候选。helper 的规格必须带这里的冷分支前提，调用端显式传递原守卫的否定；不能沿用 4a30 无条件 helper_spec，也不能把结果 NaN 守卫自动当作同一输入前提。
5. 先完成精确整包原版 gate，再对同一候选的完整 current public suite 作配对发现及冻结独立确认。全程不把有限检查、源码形状或曝光计数替代这些结果。

JSON 内的 local_checker_source 是保存的轻量重放文本，以 JSON 编码的 local_checker_fixtures 替换其中 FIXTURES_JSON 后运行；本次已在内存中重放并逐项核对结果、trace 和 19 个既有依赖 SHA。没有落盘额外脚本，也没有调用 oracle 的 main。
