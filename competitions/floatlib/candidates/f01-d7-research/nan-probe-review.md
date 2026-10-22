# R7 NaN word bridge 与 scalar result guard 独立静态审查

审查快照：2026-10-22T21:10:34Z。范围仅为本目录两份构建脚本、`nan-choice-block.lean` 及其四份生成候选；只读检查已有候选，未运行构建脚本、修改候选、操作 Git、派发 CI 或上传源码。固定目标为 Lean 4.34.0 / FloatLib `0d91825727839f597fd06b22fdd038ea21480f0c`。

**结论：没有发现仅凭当前源码可以确定的错误。** 已确认文件身份、搬移范围、声明先后、固定库名称及关键改写方向。该结论是静态审查，不是 Lean 编译、内核重放、公理审计或完整 gate 通过；新候选仍为 **NOT_RUN**，性能为 **UNKNOWN**。

## 精确对象与本次实际检查

| 候选 | 字节 | 本次重算 SHA-256 |
|---|---:|---|
| `f01-d7-direct-nonnan` 父本 | 155103 | `60f74aa4af01a9b35ece66a7c310e6b05b5b84b9b7121a4cccd12a0a9c987e15` |
| `f01-d7-nan-choice-probe` | 162660 | `ad014e0b1cdc6e42d3a9bd9437e32762d840b8047be740dca8894b0108aa3cb9` |
| `f01-d7-result-guard-add` | 156619 | `fb365daa6ff957b34c9e6f4b5e339a2f9bb5f529526e5ce3ca571a2837a6747d` |
| `f01-d7-result-guard-mul` | 156614 | `9be05b601de849131d823a95f98dcc083aafb2d0c4679fabe089be205ae3e497` |
| `f01-d7-result-guard-both` | 156454 | `d0279229968ba66440efbfcf55abb64a29f313df68ba22d72df70a28aa0a855c` |

实际执行了不落盘的独立重构与字节比较：三份 scalar 候选均与脚本规则重构结果完全一致，SHA-256 与各自 manifest 一致；NaN probe 等于父本原字节加两个换行及新 block。新 block SHA-256 为 `584ace5443838454b3687f7a93cfca07be4f9cce2c889c7196b171b7cfd4c93c`。五份文件的显式 namespace/end 结构均配对，新 NaN block 未出现 `sorry`、`axiom`、`unsafe`、`native_decide`、`extern`、`implemented_by`。这些文本检查不能替代完整依赖公理审计。

## 已核实的高风险位置

以下行号以 `nan-choice-block.lean` 为准；生成 probe 的对应行号为 block 行号加 3652。

| 位置 | 静态结论及证据 |
|---|---|
| `rawNaN_eq` 14–31，尤其 25/30 | **未发现方向错误。** 固定 Lean 的 `UInt32.toNat_inj` 为 `a.toNat = b.toNat ↔ a = b`，此处目标为 word 等式在前、Nat 等式在后，因此 `.symm` 正确。`0xff : UInt32` 的 `toNat` 为 255，零同理。固定 NativeBinary32 的字段分别为 UInt32 shift/mask，Model 字段为相同 binary32 BitVec 字段的 `toNat`；没有把 IEEE 描述符推广到其他格式。 |
| `rawSNaN_eq` 33–44 | **未发现桥接名称或方向错误。** 固定 Model 的 IEEE signaling 判据为 NaN 且 quiet bit 为零。`UInt32.toBitVec_inj` 与 `UInt32.toBitVec_and` 均存在；逆向使用前者将 word 等式转成 BitVec 等式，再展开 and，方向与当前目标一致。`4194304#32` 对应 `0x00400000`。 |
| `quietWord_eq` 46–60 | **固定库定理确实可用。** 从 GitHub 连接器读取固定 `0d918` 的 Packing.lean，其 `ofUInt32_or_quietBit (x : Value)` 正是 `ofUInt32 (toUInt32 x ||| 0x00400000) = Model.ofBits (x.bits ||| quietBit binary32)`。代码实例化为 `ofUInt32 u`，再用已在父本使用的 `toUInt32_ofUInt32`，随后仅在已知 NaN 条件下展开 `quietNaN`。没有对非 NaN word 无条件置 quiet bit。 |
| `rawChoose`/`rawChoose_eq` 69–94 | **优先级与固定 Model 一致。** 顺序为 a signaling、b signaling、a NaN、b NaN，分支全部保留原符号及 payload，只 OR quiet bit。定理使用 `Option.map ofUInt32`，没有把 canonicalized native NaN 当成原始字表示。正、负 Bool 分支及 map 构造子简化仍需首次编译确认。 |
| `rawChoose_nonfinite`/`specialDecode` 96–123 | **没有缺失明显的选择前提。** 任一返回 some 的分支都推出至少一个输入指数全 1；该输入 dyadic decode 为 none，使 Spec 落入 exceptional 分支。`specialDecode` 的路线与父本 `WordFinite.modelFiniteOfExp` 已用过的 `toDyadic_eq`/roundtrip 名称一致。 |
| `selected_model_add`/`selected_model_mul` 125–153 | **与固定 Spec 的分支结构一致。** 固定 Spec 先匹配两个 dyadic decode；只有两个 some 才走有限计算，其余情况才选择 NaN。此处先证至少一个 none，再按另一个 decode 分情况，避免了直接假设 Spec 总是先 chooseNaN2 的错误。 |
| `selected_add`/`selected_mul` 157–173 | **未发现错误的规范层或字段投影。** 先由实际 ExecFloat 规范改写到实际 operation，再经 configured carrier 的注入性；调用的是父本已有 `Submission.R7Native.toModelExecAdd` 与 `Submission.NativeBridge.toModelExecMul`。父本 `FastMul.ofBits`/`dec_ofBits`（父本 1671/1691 附近；生成版本 1718/1738 附近）已将同一载体 decode 到原 word。最终 `change` 所需的 descriptor/codec 定义相等仍须由本次编译接受。 |

固定 UInt 引理证据来自仓库已有 `research/astra-collab-20261022/web/R2-W01c/original-extracted/FloatLib_R2-W01c/public_sources/lean4/src/Init/Data/UInt/Lemmas.lean` 第 101、168 行，以及相邻 `Bitwise.lean` 第 31 行；未将新 Lean 版本的 API 代入本轮。

## Scalar 搬移与成功分支

`build-scalar-result-guard.py` 第 16–20 行的起点明确位于首个 `namespace Submission` 之后。当前父本较早的同名块实际叫 **`R2W01c.NativeBridge`**（父本 474–645 行），不是 `R2W01b.NativeBridge`；它位于受保护的 R2 前缀中。本次逐字节比较确认该前缀完整保留。`Submission.NativeBridge`、`Submission.NotNaNProbe`、`Submission.R7Native` 的字节也分别保持不变：

| 块 | 字节 SHA-256 | 三份生成文件中的行号 |
|---|---|---|
| `Submission.NativeBridge` | `03b626fbaf4e5ac0cc3c9bd6a0009eeaa00eb4d508b0f9b64d867fee2682d3fc` | 2091–2281 |
| `Submission.NotNaNProbe` | `6440cc47ffac4bbfc9c5a42f48d3a4ef7b455d2f7f6792a341b2d0e2630061a1` | 2283–2338 |
| `Submission.R7Native` | `1f60d2bac8219bc597768fc77bd54a71ddf5a4c1bcadacb61ef56fa39856bf2b` | 2340–2563 |

已逐段核查新位置所需的候选内依赖：NativeBridge 只依赖之前的 imports/库证明；NotNaNProbe 不依赖 `Submission.add`、`nativeMul` 或后置 FinalFinite；R7Native 依赖前置 NotNaNProbe 与 NativeBridge，不依赖被跨越的 scalar 实现或 FinalFinite。未发现搬移造成的候选内前向引用。各块保留自己的 `open`，显式名称没有漂移到 R2 命名空间；原有已验数学不因本次未安装 Lean 而被否定。

以 `result-guard-both/Kernel.lean` 为准，新 scalar add 在 2566–2583 行、nativeMul 在 2586–2601 行：

- guard 的真值经 `R7W04.nonNaN_eq_true_iff` 转成**结果** `isNaN = false`，再经 NotNaNProbe 的 input inversion 得到两个**输入** `isNaN = false`，满足 R7Native 运算桥和原 word roundtrip 的前提。
- add 的数值 decoder 先通过 `R2W01c.convert_eq` 改写到 `Float32.ofBits`；后续 `change` 与父本 add 的同一 native conversion 定义相接。这个改写没有要求原始 NaN 能往返：成功分支已经排除了输入 NaN。
- 结果为 NaN 时仍调用原始 `TunedAdd.add` / `FastMul.mul`，因此未用 canonical NaN 替代 payload/priority 语义。低指数 `LowScale.mul` 仍在 nativeMul 之前（2603–2613 行），其原有证明不变。
- 新 R7W04 块完整取自固定 `3baa785e…` guard 父本，位于文件 3–48 行。它保留 self-BEq 的 Bool 规格，未把 `x == x` 当成普遍真；这份整包整合仍须本轮编译。

## 首次编译应优先观察的目标（不是已确认缺陷）

1. `nan-choice-block.lean` 第 23–30、37–44、56–60 行：这里依赖 UInt32/BitVec 和 binary32 descriptor 的定义相等，以及 Bool 判据的显式改写。若编译实际停在 `change`，先读取精确展开目标，补局部桥接引理或显式 `change`；不能因为数学等价便替换为抽象模型证明。
2. 同文件第 83–94 行：核对 `by_cases ... = true` 的负分支是否被当前 `simp only` 完整消去；如有剩余目标，按实际目标增加 Bool false 事实或精确分支化，保留 signaling-first 顺序。
3. 同文件第 135/138/150/153、162/171 行：分别确认 match reduction 与实际 configured carrier 的投影闭合。若 codec 的 `change` 不闭合，可参照本候选 FastMul.dec/dec_ofBits 的具体载体，而不是只证明 UInt32 层等价。
4. `result-guard-both/Kernel.lean` 第 2577–2581 行及第 2597–2599 行：确认 add 同时改写假设和目标后，结果 inversion 的实例及两个输入 roundtrip 能被 elaborator 正确推断。mul 路线的相同前提衔接也必须实际编译；不由原 bridge 的历史通过推定新整合通过。

这些目标当前没有编译错误回执，因此不按缺陷计数，也不建议预先改动能闭合的证明。完成 statement 编译后，任何 runtime 采用仍需精确候选的原版 obligation、kernel replay、公理审计、checksum 和完整配对计时。NaN probe 只新增 theorem，不能从它的存在推出已有运行时已采用 NaN 快路径。

## 固定公开来源

本次通过 GitHub 连接器只读获取下列固定版本文件，并核对正文；没有升级依赖：

- [NativeBinary32 Packing.lean](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/ExecFloat/Backends/Word/Narrow/Packing.lean)，Git blob `d2a05e54fbd16b7f008aa295b986764ca71bb91e`。
- [NativeBinary32 Base/Runtime.lean](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/ExecFloat/Backends/Word/Narrow/Base/Runtime.lean)，Git blob `dc080c68fa47df803354e28654c3973c6d2b48a2`。
- [Model/Carrier.lean](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Model/Carrier.lean)，Git blob `8849d6b29facd7ccff8d1f32e2b15626d0771023`。
- [Spec/Dyadic.lean](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Spec/Dyadic.lean)，Git blob `2204e7bd34af9f7d82469ecae247eb2942d78e73`。

未找到本机 Lean 工具链，本次没有安装或使用替代版本，所有新整合的编译及 gate 状态维持 NOT_RUN。
