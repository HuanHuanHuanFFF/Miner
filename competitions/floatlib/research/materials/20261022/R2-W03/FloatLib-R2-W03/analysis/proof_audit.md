# R2-W03：固定版本证明面审计

状态：**所有 Lean 片段 NOT_RUN**。研究环境没有 `lean` / `lake`；未安装工具链。`ProofBridges.lean` 包含真实定义上可核查的桥接引理、模型帮助引理和小型闭项 `decide` 诊断，但**没有宣称完成任意 raw 位的转换等价定理**，没有 sum/bmm obligation。

## 1. 关键结论

`UInt32.toFloat32` 并不是不透明的假设边界。Lean v4.34.0 的 `src/Init/Data/Float/Float32.lean` 第 303–304 行将它定义为 `Float32.ofModel (Float32.Model.ofUInt32 n)`；整个文件在第 13 行进入 `@[expose] public section`。`UInt64.toFloat32` 同理（315–316 行）。因此只要固定 ContractTensor 导入链保持实际公开版本，数值重构可以直接在逻辑模型中证明，不需要 Float64 往返，也不必增加公理。

完整桥链是：

- native UInt32 cast → `Float32.Model.ofUInt32` → `UnpackedFloat.ofUInt32` → `ofNat` → `ofInt` → `normalize` → `round`。
- native mul → `Float32.Model.mul` → unpack 两个操作数 → `UnpackedFloat.mul` → `roundWithAccuracy ... .exact` → pack。
- native neg → `Float32.Model.neg` → unpack / sign negation / pack。
- `Float32.ofBits` → `Float32.Model.ofBits` → unpack raw UInt32 / pack；NaN 在此规范化。

这里的“可证明”是定义已暴露、必要数学引理可以在普通 Lean 逻辑中建立；并不等于本轮已经提交了可通过 gate 的全域证明。

## 2. 固定源码事实与公开依赖

| 内容 | 固定版本文件与行 | 含义 |
|---|---|---|
| `Float32` 是结构，只有 `toModel` 字段 | Lean `src/Init/Data/Float/Float32.lean` 38–44 | 逻辑相等可由 packed model 相等证明；编译时仍特化为 C float。 |
| mul / neg 的模型 | 同文件 90–91 / 108–109 | 原生算术有透明定义。 |
| ofBits / toBits | 同文件 132–146 | ofBits 非保留 NaN payload 的 raw 通道。 |
| unsigned casts | 同文件 303–316 | UInt32 / UInt64 都可直接从定义建立模型桥。 |
| `Float32.Model.ofUInt32` | `src/Init/Data/Float/Model/Float32.lean` 223–224 | 经 pack 整数转换。 |
| 整数构造 | `src/Init/Data/Float/Model/Unpacked/Operations/OfNat.lean` 18–40 | ofUInt32/ofUInt64 都只取 `.toNat` 后 ofNat。 |
| 有限乘法 | `src/Init/Data/Float/Model/Unpacked/Operations/Mul.lean` 32–33 | 精确整数尾数乘积与指数加法后 RN-even。 |
| exact 尾零移位 | FloatLib `IEEE754/Native/Integer/Constructors.lean` 51–60 | 公共定理 `Model.round_shiftLeft`。 |
| exact roundWithAccuracy → round | FloatLib `BinaryInterchange/ModelRounding/Proof.lean` 839–848 | 公共定理 `roundWithAccuracy_exact_eq_round_of_le_targetExponent`。 |
| normal pack/unpack 恒等 | FloatLib `BinaryInterchange/Model/Packing/Finite.lean` 85–153 | 公共定理 `unpack_pack_finite_normal`。 |

只 import ContractTensor 的公开路径：
`ContractTensor → Contract → FloatLib → FloatLib.Floats → FloatLib.Floats.Formats → IEEE754 → Native.Integer → Native.Integer.Constructors`。上述核心 `round_shiftLeft` 在该 pin 已经存在，不必改变 FloatLib pin，更不必移植后续版本。

### 私有定理不能直接当公开 API 用

Constructors.lean 的 `round_eq_finite_of_targetExponent` 是 private。诊断文件按 MIT 许可在 candidate-local 命名空间局部改写了这一约 12 行的帮助引理，并保留来源说明；包中须同时包含 `FloatLib_LICENSE`。同文件 `float32_ofNat_eq_ofModel`、`ofNat_eq_round`、`mul_one_ofNat_small` 也都是 private，报告不把这些名字误列为可直接调用的公共定理。

## 3. 已给出的 Lean 片段实际证明了什么

`ProofBridges.lean` 中的五个 `rfl` 引理给出 UInt32 / UInt64 casts、UInt32 cast 后 mul、neg 的直接模型等式。它们没有引入“转换正确”的假设；左、右两端就是固定 Lean 定义的不同展开形式。

`round_at_target` 证明：若指定指数就是模型计算的目标指数，则 exact round 不改变尾数和指数。

`round_normalized24` 证明的目标：`m.log2 = 23` 且 `e ≥ -149` 时，unpacked round 将 `(m,e)` 保留为本身。这里明确只谈 **unpacked** 值；在 pack 阶段若 `e > 104` 仍可溢出为 Inf，因此不能把这个帮助引理当成“任意大指数有限”。

`round_shifted24` 用固定 FloatLib 的 `round_shiftLeft` 证明：

`round binary32 positive (m <<< k) 0 = finite positive m k`

其中 `m != 0`、`m.log2=23`。它解释根任务提出的更窄 shift 重构为何可行：整数绝对值可以超过 `2^24`，只要只有 24 个有效二进制位、其余都是精确尾零，转为 binary32 仍然精确。这里的移位发生在 `Nat`；实际 UInt32/UInt64 代码还必须证明移位不回卷，且 float pack 不溢出。

这些引理是证明组件，不是完整重构证明。文件中没有以一个未经证明的 `CorrectCast` 假设包装出表面完整的定理，也没有 `sorry`、新增 `axiom` 或 `native_decide`。

## 4. 尚须闭合的全域证明义务

1. 原始字段提取：`E=((u>>>23) &&&255)`，`F=(u &&&0x7fffff)`；normal 分支证明 `M=2^23+F`、`2^23≤M<2^24`，且提取 sign 与 pack 顺序一致。
2. 精确整数转换：由上述范围得到 `M.log2=23`，证明 UInt32 cast 的 unpack 是 positive finite M 0。shift 方案需要先建立 UInt shift 的 no-wrap 等式到 Nat。
3. 因子表：每个可索引槽确实为 `2^(E-150)`；数组界证据不进运行时，不允许把未命中默认槽误当 valid factor。可用具体有限常量计算证据，但不能把 23-bit mantissa 的所有情况靠计时样本替代。
4. 乘法归一化：E≥24 时因子 normal，乘积尾数 `M·2^23` 的低 23 位都是零，移位舍入 exact；E≤23 时因子 subnormal，需另一个 pack/unpack 分支（因子尾数 `2^(E-1)`、指数 -149），不能误套 normal-factor 引理。
5. 最终 pack：输出指数 E∈1..254，非零 finite normal。模型相等推出 Float32 结构相等，再结合既有 native/FloatLib 有限运算桥。
6. NaN / Inf / ±0 / subnormal：走已定义的外部分支契约；如果全输入合同要求 FloatLib 原始 NaN payload，**不能先经 Float32.ofBits 再试图恢复 payload**。

最先可收敛的证明域是 `24≤E≤254`（因子及结果都是 normal）或者本次数值分布域 `102≤E≤151`。后者只是快路 guard，所有其余值仍走精确回退。域有限不代表允许只证明 sampled mantissa。

## 5. signed integer 消除 sign 分支的可行性与新依赖

v4.34.0 `src/Init/Data/SInt/Float32.lean` 的 Int32/Int64 casts 也是 model-backed def，但是该文件只有 `public section`，没有 `@[expose]`；不要在只 import ContractTensor 下假设其 body 一定能被 `rfl` 或 `simp [Int32.toFloat32]` 展开。

固定 FloatLib `IEEE754/Native/Integer/FromInt.lean` 本身以 `import all Init.Data.SInt.Float32` 使用它们，并公开了：

- `FloatLib.Floats.ExecFloat.Binary.toModel_ofFloat32_int32ToFloat32`
- `FloatLib.Floats.ExecFloat.Binary.toModel_ofFloat32_int64ToFloat32`

结论连接到 `ExecDType.intToFloat ... .nearestEven`。所以 signed cast 候选有合法的已证桥，不必加 import，但其精确性证明比 unsigned 直接展开多一层。

若用无分支整数符号施加 `(N xor mask) - mask`，mask 为 `0 - sign`，必须证明 bit pattern 解释为 Int32/Int64 后就是 ±N，且正数幅值不跨 signed 边界。dense `N<2^30`、wide `N<2^55` 满足相应范围。原始负零不能走“signed integer 0”恢复路线，因为整数零没有符号；负零应回退或独立分支。

## 6. 有限闭项诊断及证据限制

文件给出 E=1、23、24、254、负最大 finite、最大 subnormal、负零以及 shift bucket 最高端的 `example ... := by decide`。这些运行在 Lean kernel 的透明逻辑模型，而非 native C 计算，不引入 `native_decide`。它们尚未编译，全部 NOT_RUN。运行成功也只证具体闭项，不证所有 mantissa。

开发者可在既有固定项目中运行：

```bash
lake env lean /absolute/path/to/ProofBridges.lean
```

并检查末尾 `#print axioms` 输出。该文件仅为独立证明诊断，不能作为已完成的 Kernel 提交，也没有改动 lakefile、toolchain、bench 或 gate。

## 7. 来源 URL

- Lean native definitions: https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Float/Float32.lean
- Lean packed model: https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Float/Model/Float32.lean
- Lean RN-even model: https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Float/Model/Unpacked/Round.lean
- Lean unsigned constructors: https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Float/Model/Unpacked/Operations/OfNat.lean
- Lean finite mul: https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Float/Model/Unpacked/Operations/Mul.lean
- Lean signed casts: https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/SInt/Float32.lean
- FloatLib exact shifts/constructors: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/IEEE754/Native/Integer/Constructors.lean
- FloatLib signed bridge: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/IEEE754/Native/Integer/FromInt.lean
- FloatLib rounding bridge: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/ModelRounding/Proof.lean
- FloatLib finite packing: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Model/Packing/Finite.lean
- ContractTensor: https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/contract/ContractTensor.lean
