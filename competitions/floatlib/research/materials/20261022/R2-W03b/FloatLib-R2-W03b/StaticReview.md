# R2-W03b 独立静态审查记录

状态：`NOT_RUN`。本记录只审查给定公开版本的源码、命题及证明文字；没有运行 Lean elaborator、Lean kernel、leanchecker 或官方 gate。

## 固定舍入桥的逐字适用条件

FloatLib 固定提交 `0d91825727839f597fd06b22fdd038ea21480f0c` 中：

```lean
FloatLib.Floats.Formats.BinaryInterchange.Model.
  roundWithAccuracy_exact_eq_round_of_le_targetExponent
  (spec : Float.Model.Format) (sign : Sign)
  (mantissa : Nat) (exponent : Int)
  (h : exponent ≤ spec.targetExponent
    (Float.Model.totalExponent mantissa exponent))
```

结论是 `.exact` 的 `roundWithAccuracy` 等于 `round`。条件方向为输入指数 **不大于** target；并非任意 `.exact` 输入都可替换。源码没有额外的 mantissa 非零条件。

本候选乘法中，输入尾数 `m <<< 23` 的 log2 是 46，输入指数为 `e - 23`，并有 `-149 ≤ e`。因此 target 恰为 `e`，桥条件成为 `e - 23 ≤ e`。这是证明显式提供的条件，不依赖乘法结果有限这一不够直接的事实。

来源：`FloatLib/Floats/Formats/BinaryInterchange/ModelRounding/Proof.lean`，行 839–848。

## 固定 pack/unpack 条件

`Model.unpack_pack_finite_normal` 公开可用，除了 `m ≠ 0`，要求：

- `m.log2 + 1 = spec.mantissaBits`；
- 偏置后的指数非负、严格正；
- 偏置指数的自然数值加一，严格小于 `2 ^ spec.exponentBits`。

binary32 下偏置表达式是 `e + 127 + 23`。候选通用引理采用 `-149 ≤ e ≤ 104`，对应偏置指数 `1..254`，完全满足上述严格不等式。整数 M 的 native 转换解包使用 `e = 0`。

`Model.unpack_pack_unpack` 则对任意原始 bits 无条件成立，可将 `(Float32.ofBits bits).toModel.unpack` 化为 raw `UnpackedFloat.unpack`，无需重新证明模型 canonicalization。

来源分别为 `BinaryInterchange/Model/Packing/Finite.lean` 行 85–153 与 `IEEE754/Native/Model/Representation.lean` 行 124–134。

## 可展开定义

Lean v4.34.0 的 `Float32`, `Float32.Model`, `Float32.ofBits`, `Float32.mul`, `UInt32.toFloat32`, Model 的 pack/unpack/ofBits/ofUInt32 位于公开 expose 区域。native UInt32 转换的逻辑定义经过 `UnpackedFloat.ofUInt32` 归到 `ofNat`；native 乘法的逻辑定义经过两个 model 的 unpack 再 `UnpackedFloat.mul`，后者 finite×finite 分支正好是上述 `.exact` 舍入。并未使用 Float32→Float→Float32。

## Array 查表

Lean v4.34.0 公开引理可直接证明常量表查找：

- `Array.getD_eq_getD_getElem?`；
- `Array.getElem?_ofFn`；
- `Array.size_ofFn`；
- `Array.getElem_ofFn`。

必须先证明 `(u >>> 23).toNat < 512`，再将该项化成 `Array.ofFn` 中同一 `Fin 512` 的值。不能把表值相等性替换为任意 table 的前提。这里的名字已从固定 tag 的 `Init/Data/Array/Lemmas.lean` 核对。

## 官方 policy 源码审查

固定官方 gate `978cc5b445edb9943fd9953b0a9037d97a9f33a8` 的 policy 检查直接读取整份源码。注释不会在禁止名字匹配前移除；包含独立 `import` 单词的任何一行都必须恰好是 `import ContractTensor`。因此候选注释中也不能写诊断命令及禁止词。属性白名单包含 `inline`、`noinline`、`always_inline`、`specialize`、`simp`、`reducible`、`irreducible`。

内部字符串检查最多能发现上述一部分问题，不能代替官方 policy、statement、kernel、依赖公理或性能阶段。候选片段还需接入用户实际 kernel 后才能接受官方 obligation 检查。

## 算术文件逐项审查

已静态审查 `arithmetic/ArithmeticCore.lean` 初版：

- `round_at_target` 与 `ofNat_eq_round` 的局部移植对应原公开文件中的私有辅助引理；保留 MIT 归属。
- `round_normalized24` 的 `max` 条件正确。
- `uint32_unpack_exact24` 与公开 native 构造定义一致。
- `mul_normal_scale_target` 采用 log2 46，未遗漏尾数位数。
- `mul_normal_scale_exact` 显式证明桥前提及符号乘法。
- 最终 native 桥的 `hscale`、`hraw` 是后续必须证明的结构命题；不是全输入主定理的新增用户假设。

尚未取得任何编译通过证据。具体 elaboration、simp 展开范围、类型推断与性能只能由固定环境编译解决。

## 字段、查表与主定理逐项审查

继续静态审查了 `bits/BitFields.lean`、根目录 `Definitions.fragment.lean`、`TableLookup.fragment.lean`、`FinalProof.fragment.lean`。

- UInt32 的 toNat 位运算与取模转换使用固定 tag 中真实公开的名字。
- M 的低 23 位与隐含位不相交，证明得到 `2^23 ≤ M < 2^24` 及 `M.log2 = 23`。
- scaleWord 的 toNat 展开保留原符号位；减 23 发生在已有 `E ≥ 24` 条件下，没有 UInt32 下溢。
- scaleWord 的 exponent 是 `E-23`，fraction 为零，unpack 后的有效指数是 `E-173`。
- 原始 normal unpack 与 scale unpack 的 dependent 正数证明参数可由 Lean 的 proof irrelevance 匹配。
- scaleWord 证明中交给 omega 的算式只有常数乘法、常数除法及常数取模；没有两个未知自然数相乘。
- 512 项表的索引上界由 UInt32 全域界和右移 23 位得到。lookup 只重写实际 signedScaleTable 的定义。
- `reconstruct_normal` 给算术桥提供的 `hscale`、`hraw` 已由具体字段引理证明。
- 全输入主定理按 raw+0、guard 成立、其余 fallback 三类穷尽，不向外保留 table 或 scale 假设。

此轮静态审查未发现能明确指出的剩余数学命题或错误声明，亦没有编译结果足以排除 elaboration 问题。

## 单文件集成复核

已再审查整合后的 `deliverable/ConversionCandidate.lean`：声明顺序满足依赖关系，没有重复的本地声明；本地 `unpackExponent_toNat` 与其他命名空间的同名引理不会混淆。全输入证明中 `beq_iff_eq` 用于 UInt32 的 lawful Boolean equality 和命题条件转换，适用类型正确。

为降低未编译条件下的名字解析风险，最终版本将 simp 参数列表中的 `ofNat`、`ofInt`、`normalize`、`round`、`unpack` 改为显式 `Float.Model.UnpackedFloat` 限定名。原因是同时打开 `Float.Model` 与 `Float.Model.UnpackedFloat` 时，native binary64 model 也提供部分同名定义；typed term 通常可由参数类型消歧，但显式名字不依赖这一点。

同时将可能被前一条 rewrite 自动完成的末尾 `rw; rfl` 合并为一次关闭目标的 simp；常数尾数位运算的 rewrite 显式指定 `n := 23` 与 `0 < 2^23`，减少后置类型推断的依赖。集成检查没有发现剩余的同类冗余目标风险。上述都是静态复核与文字修正，不构成任何编译通过证据。

## 为什么舍入桥的条件不能省略

在 binary32 模型中，给 `roundWithAccuracy` 输入正号、尾数 1、指数 0、精确标签，函数不能左移，因此返回尾数 1、指数 0 的 finite 构造；给 `round` 相同输入则先左移正规化，返回尾数 `2^23`、指数 `-23`。两者实数意义相同，但 UnpackedFloat 的结构不同。当前证明对 `m <<< 23` 明确满足桥条件，故不发生这一错误替换。
