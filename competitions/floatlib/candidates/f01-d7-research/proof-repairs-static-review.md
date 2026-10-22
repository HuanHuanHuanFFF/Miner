# R7 两项证明修复：静态审查

2026-10-22 21:57:30 UTC 开始，22:03 UTC 完成主要审查。只读候选、808 原始回执、祖先证明和固定官方源；未运行 Lean/Linux 工具链，未操作 Git、CI 或上传。完整输入 SHA、字节差异和错误清单见同目录 proof-repairs-static-review.json。

**结论：未发现新的确定 Lean 阻塞；两项修复均与 808 的精确剩余错误对应。编译、内核重放、公理审计和 checksum 全部 NOT_RUN，性能 UNKNOWN。** 静态匹配不等于编译通过。

| 候选 | 精确 SHA-256 | 静态判断 |
|---|---|---|
| f01-d7-singleton-proof1 | dab15a44f753c1e8d4654d15ffc54eaa770702eeb42cf0cc601c91809418b21a | INFERRED：直接覆盖唯一剩余 Fin 零下标目标 |
| f01-d7-special-model-proof1 | 40a281d9c94dbe56ef9b5e9209fcbfc9b51e9a6acfabac70d9ed99364f500baf | INFERRED：覆盖八个 rfl 分支错误和一个 descriptor rewrite 错误；末尾 exact 仍需实际 elaboration |

## 已确定的字节与来源事实

两个失败父本逐字节等于 808 保存的 inputs/Kernel.lean，SHA 分别为 4ba2a235…725d43、285ed400…9437af。修复文件及父本 SHA 均与 manifest 一致。重建所有指定替换后，结果逐字节等于两份 proof1；所有差异均在证明体，运行定义及其余证明未变。

808 的实际 provenance 使用官方 4b7e83841cc0c32c6529f533923c73d33b5ecf97、Lean v4.34.0。在线只读核实该官方 [lake-manifest](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/4b7e83841cc0c32c6529f533923c73d33b5ecf97/lean/lake-manifest.json) 仍固定 FloatLib 为 0d91825727839f597fd06b22fdd038ea21480f0c。

本地固定 Spec/Dyadic.lean 的 SHA-256 为 932ee9d22d6241cda8c38dd22df4ecaffa934cdd1aa2922a0681afd1669ffb67，其 Git blob SHA 与上述固定修订的官方响应完全相同。不是拿默认分支的新定义推断旧证明。

## singleton-proof1

808 full-build-output.txt:160 起的唯一目标，左右两边的 add/mul、bmmDecodeC、A/B 地址和默认值完全相同，差别只有右侧两个被强制到 Nat 的零 Fin 下标。原候选源码错误位置为 3386:68。

修复在 Kernel.lean:3392 仅追加 Fin.val_zero。固定 Lean [Fin.foldl_succ](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Fin/Fold.lean#L254) 把一次 fold 化为首项 f init 0 和空后缀；foldl_zero 去掉空后缀。[Fin.val_zero](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Fin/Lemmas.lean#L231) 正是将该 Fin 零下标的 Nat 值改写为 0；其 NeZero 参数此处为 1。

未看到新的数学缺口。singletonCore 保留 add posZero (mul a b)，所以没有把初始正零加法错误地删掉；NaN、负零仍经过原有标量实现。Vector.ofFn 和函数外延不要求输出非空，所有 batch/m/p，包括空输出，均在原目标中。n≠1 的旧 dispatch 保持原字节。

**待实际验证：** 上述 simp-only 在真实 Lean v4.34.0/import 环境下是否关闭目标，以及随后完整 gate。不能由一个核心恒等式的静态形状推导整个候选通过。

## special-model-proof1

808 原始日志有九个源级错误：2082、2085、2093、2096 各两次 rfl 失败，以及 2101 的 rewrite 失败。原始错误日志 SHA-256 为 38f01b19d33ade7245024831c481ddd39b0826e1fe074bdf5eb33237369f44d1。

前四处修复显式展开 modelAdd/modelMul 及对应 Spec。脚本已独立比对两个模型体与固定 [Spec/Dyadic](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Spec/Dyadic.lean) 的 exceptional fallback：只移除 Model 命名空间限定、Fmt/fmt 拼写和空白后，表达式完全相同。chooseNaN2、Inf、zero、符号与 invalidResult 分支没有顺序或参数差异。取得任一 toDyadic?=none 后，对另一侧的 none/some 两种构造器分情况，预期剩余两边就是同一 fallback。是否 rfl 成功仍是 INFERRED。

808 的 2101 错误明确报告 implicit transparency 下 NativeBinary32.Value 与 Model TunedAdd.Fmt 的中间目标类型不相容。新代码先在原生 descriptor 上建立 hw，再执行原生解码定理的逆向 rewrite，最后 exact hw。固定 NativeBinary32.Value 是 Model FloatFormat.binary32，且其 native decoder 在 exponent==255 时直接返回 none。

这条 native-descriptor rewrite 路径并非新造：同一 808 中完整 gate 已通过的 8eb 祖先 WordFinite.modelFiniteOfExp:2023 已使用相同的逆向 [toDyadic_eq](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/ExecFloat/Backends/Word/Narrow/Agreement.lean#L124)、toUInt32_ofUInt32 和展开 native toDyadic? 序列。TunedAdd.dec_eq:1322 也已有 rfl 证明，且其 ofUInt32 来自 NativeBinary32 的打开命名空间。这些证据支持末尾 hw 与目标之间存在定义相等转换。

**主要待编译风险：** 新 2106 的 exact hw 是否在实际 elaborator 透明度下完成 descriptor/codec 的定义相等转换；新 2105 的 simp [hx] 是否完全化简 UInt32 exponent 条件；四个 case-pair 在显式展开后是否关闭。未发现能静态断言必败的目标，也不把这些风险写成“已修复通过”。

该候选 manifest 是 statement-only。即使下一次 statement 成功，也还没有完整 gate、内核、公理、checksum 或性能结论。

## 下一项最有价值的本地检查

D 已负责 810 计划与 policy；派发前仍应按这里两个完整 SHA 核对实际暂存候选，并保持 statement-only/full-gate 标签准确。剩余核心不确定性来自 Lean elaboration，继续做 Python 浮点 oracle 不能消除它。

若 LowZero 仍未编译，下一项独立本地检查建议转审其 magnitude_zero_iff → finiteMantissa=0 → UInt64 product=0 → roundP signedZero → LowScale 规格桥接。这里仍有机会静态找到确定的重写或命名空间遗漏，不重复 D 的计划检查。

第一个外部证伪点是固定环境对精确字节的原版 statement build 零错误。若 specialDecode 再失败，先保存新 2101–2106 的完整目标及类型上下文，再决定下一份独立证明修复；不要改写已失败原件。
