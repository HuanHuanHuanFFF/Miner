# R2-W01c：native／raw Model 关闭桥审计

## 状态

本分支只负责复用公开有限乘法桥和关闭最终 native／packed 字节关系。没有执行 Lean 编译：`command -v lean` 无结果，状态 **NOT_RUN**。没有安装工具链，没有执行 C 实验，没有访问 CI。

`NativeProductBridge.lean` 是只导入 `ContractTensor` 的独立草稿；原样摘录父源所需的五个乘法桥事实，再加入 decode、canonical-word 和 raw-product 提升引理。它不是完整 `normal_eq`，也没有将尚未证明的 normal 条件包装成所谓无条件转换定理。所有新引理的数学前提均出现在显式参数中；不存在新公理或未填证明占位。

文件 18,643 bytes，SHA256 `ce7c23d7cf5d6dfc8b9d5cf196d1244d1ccdb833d4c030f802e8c62091fe1b07`。按固定 gate 的完整文本正则扫描，禁止词匹配为空，唯一导入行为 `import ContractTensor`。这只是文本检查，不代替 elaboration 或公理审计。

## 1. 已验证父源

公开父文件：

<https://github.com/HuanHuanHuanFFF/Miner/blob/46a9f085db7634a22324d25623f715829f7074f9/competitions/floatlib/candidates/f01-d2-final-finite/Kernel.lean>

实际读取后计算：58,079 bytes，SHA256 `86312a3759286cb207f946af9db95546777fdb16f1bd147f7892c0f9e1d79217`，与用户给定完全相同。归档为 `ParentKernel.lean`。两次完整 gate 通过是用户给定反馈，本轮没有重新执行，也没有访问 CI。

父源内置完整 MIT 通知，包括 Conjectures.io、FloatLib、TorchLean 三份通知；提取文件保留了这些完整通知。尝试读取仓库根 `LICENSE` 和 `competitions/floatlib/LICENSE` 均返回 404，因此不声称读取了独立仓库许可文件。代码自身完整许可通知提供了本次摘录的许可依据。

父源 `Submission.NativeBridge` 中前三个 target-exponent 引理已标明来自 FloatLib 较新 commit `1f5771b3e36a98f17fcac2c6d76aaa024b36aa37`，`Arithmetic/LeanModel/MulDiv.lean`，MIT。这里保留父源既有移植；没有升级固定依赖，也没有为 normal 转换重新发展 target-exponent 路线。

## 2. 父桥每个前提

| 定理 | 显式数学前提 | 实际结论 | 本分支使用 |
|---|---|---|---|
| `GuardBridge.modelCanonicalOfFinite` | 任意格式 model `x` 的 `Model.toModel x` 是 unpacked finite | `Model.IsModelCanonical x` | 复制短证明，用 decode 排除非有限后使用 |
| `GuardBridge.finiteRoundtrip` | `(B.toFloat32 x).isFinite = true` | `B.ofFloat32 (B.toFloat32 x) = x`，raw 相等 | 审计但最终 product 提升不依赖它 |
| `NativeBridge.modelMulFinite` | `fmt.isIEEE = true`；两个 operand 的 unpacked `isFinite = true` | `Model.mul x y` 等于 Lean unpacked mul 后 `ofModel`，完整 Model 相等 | 原样摘录 |
| `NativeBridge.toModelNativeMul` | 两个 native operand 的 `isFinite = true` | native `x*y` 读回的 raw Model 等于 `Model.mul` | 最后提升直接使用 |
| `NativeBridge.ofFloat32Mul` | 两个 native operand 的 `isFinite = true` | `B.ofFloat32 (x*y)=ExecFloat.mul (B.ofFloat32 x) (B.ofFloat32 y)` | 审计；不必摘录到最小桥 |

这里 `B` 表示 `FloatLib.Floats.ExecFloat.Binary`。两个 finite 输入前提没有额外要求乘法结果 finite；因此父桥本身包括乘法溢出为 infinity 的结果。normal 重构的结果有限与非零仍由上游 exact-dyadic 证明承担，不能从这个父桥自动得到。

`modelMulFinite` 使用的是 `(Model.toModel x).isFinite`，不是可任意替换的 `Model.isFinite x`。新 `nativeFinite_of_decode` 通过固定 `toDyadic?_ieee_eq_model` 转到真正 unpacked 类型并做 case 分析，避免混淆两个分类接口。

## 3. 两种 raw wrapper 的关系

草稿定义：

```lean
abbrev nativeModel (x : Float32) : Model FloatFormat.binary32 :=
  B.toModel (B.ofFloat32 x)

abbrev rawModel (u : UInt32) : Model FloatFormat.binary32 :=
  B.toModel (B.ofBits32 u)
```

固定 `Configured.Storage.Code.Runtime.toModel` 在 word32 分支用 `BitVec.ofNatLT`，不是取模编码；这使 `rawModel u` 和 `Model.NativeBinary32.ofUInt32 u` 的表示定义相同。草稿提供：

```lean
theorem rawModel_eq_native32 (u : UInt32) :
    rawModel u = Model.NativeBinary32.ofUInt32 u := rfl
```

泛型 `Model.ofUInt32` 使用 `Model.ofNatBits u.toNat`，定义中有取模；不要默认把它当作同一个声明。对应短桥为：

```lean
theorem rawModel_eq_ofUInt32 (u : UInt32) :
    rawModel u = Model.ofUInt32 (fmt := FloatFormat.binary32) u := by
  change Model.ofBits u.toBitVec =
    Model.ofBits (BitVec.ofNat 32 u.toBitVec.toNat)
  rw [BitVec.ofNat_toNat]
```

这一段也属于 **NOT_RUN** 的 Lean 草稿，证明依据是 fixed word32 decoder、UInt32 的 BitVec32 存储和 `BitVec.ofNat_toNat`，不是有限抽样。

## 4. 原 ofBits 的 canonical 边界

固定 native 边界明确区分：

1. `B.ofBits32`／`B.toBits32` 对任意 raw word 无损。
2. `Float32.ofBits` 对 NaN 执行 canonicalization。
3. `B.toFloat32 (B.ofFloat32 x)=x` 对任意 native `Float32` 成立。
4. raw→native→raw 一般等于 `canonicalizeModel`，不是无前提 raw identity。

新桥接受 raw decode 事实：

```lean
hd : Model.toDyadic? (rawModel u) = some d
```

随后用 `toDyadic?_ieee_eq_model` 将其改写成 `unpackedToDyadic? (Model.toModel ...) = some d`。unpacked NaN 与 infinity 分支都返回 none，因此被排除；其余 signed zero 和 finite 分支都是 finite。这提供 canonical-word 条件，固定 `canonicalizeModel_eq_self` 才能恢复 raw word。

完成后的接口：

```lean
nativeModel_ofBits_of_decode :
  Model.toDyadic? (rawModel u) = some d →
  nativeModel (Float32.ofBits u) = rawModel u

nativeModel_ofBits_decode :
  Model.toDyadic? (rawModel u) = some d →
  Model.toDyadic? (nativeModel (Float32.ofBits u)) = some d
```

这两个桥包含两种 signed zero，但本轮不新增零路径方案。它们的用途是让表项的纯 raw 字段证明原样送入 native 乘法桥。

## 5. 最终 native 与字节关闭

上游只需交付真正的 raw Model 等式：

```lean
hm : Model.mul (nativeModel x) (nativeModel y) = rawModel u
```

加上 `hx : x.isFinite=true` 和 `hy : y.isFinite=true`，草稿先用父桥得到：

```lean
B.toModel (B.ofFloat32 (x * y)) = B.toModel (B.ofBits32 u)
```

固定 `B.toModel_inj` 是存储模型的单射性，所以推出完整的 `B.ofFloat32 (x*y)=B.ofBits32 u`。此时再分别取：

- `congrArg B.toFloat32`：得到 `x*y = Float32.ofBits u`；native→raw→native 固定 roundtrip 关闭。
- `congrArg B.toBits32`：得到 `(x*y).toBits = u`，直接关闭最终 32-bit 字节关系。

第二条更强，避免把 native 相等误说成任意 raw roundtrip。若 `u` 是非规范 NaN，`hm` 在这里本来就无法成立，因为左侧 native model 是 canonical；没有将 canonicalization 偷渡为 identity。

新接口 `native_mul_eq_of_decoded_raw_model_mul_eq` 还接受两个 operand 的 decode-some 事实，自动导出两个 native finite 前提，再调用相同提升。

这段提升不需要对结果再加 `finiteRoundtrip` 前提。原因是上游已提供完整 raw Model 相等，而不是只有 `toReal` 相等；真正使用 numerical equality 的步骤必须先在上游通过 finite、nonzero 和 representation uniqueness 关闭为 raw Model equality。

## 6. 与 normal_eq 的精确接点

令 `x=(mantissa u).toFloat32`，`y=scaleAt u`。上游的三类工作是：

1. 用 native integer constructor 的 fixed bridge 和 `2^23≤M<2^24`，证明 `nativeModel x` 解码为 `⟨false,M,0⟩`。
2. 由 `scaleAt_eq` 与 raw table fields 解码，证明 `rawModel (scaleBits (tableIndex u))` 解码为 `⟨sign,2^23,E−173⟩`。用本文件 `nativeModel_ofBits_decode` 搬到 `nativeModel y`。
3. 用乘积 `⟨sign,M*2^23,E−173⟩` 的精确性及目标 raw word 的 finite nonzero 唯一表示，证明上面的 `hm`。`roundDyadic_of_representable` 的 `m=M,k=23` 分解允许大 significand；不能错误地要求乘积 significand 自身小于 `2^24`。

三项齐全后调用本文件的解码版 product 提升，结论正是 `tableProduct u=Float32.ofBits u`。该结构不是重复 `hNormal`，每个中间前提都降到了独立的 decoder 或 raw Model arithmetic 事实。

## 7. 来源

- 父源及完整 MIT notices：<https://github.com/HuanHuanHuanFFF/Miner/blob/46a9f085db7634a22324d25623f715829f7074f9/competitions/floatlib/candidates/f01-d2-final-finite/Kernel.lean>
- 固定 native runtime boundary：<https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/IEEE754/Native.lean>
- 固定 native representation roundtrip：<https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/IEEE754/Native/Representation.lean>
- 固定 native model representation：<https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/IEEE754/Native/Model.lean>
- 固定 canonical packed proof：<https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/IEEE754/Native/Model/Representation.lean>
- 固定 raw wrapper definition：<https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/ExecFloat/Backends/Word/Narrow/Base/Runtime.lean>
- 固定 word32 storage decoder：<https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Configured/Storage/Code/Runtime.lean>
- 固定 storage injectivity wrapper：<https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Configured/Instances.lean>
- 固定 generic UInt32 wrapper：<https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Model/Carrier.lean>
- 固定 dyadic/model bridge：<https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Dyadic/Classification.lean>

FloatLib 源均标记 Copyright (c) 2026 FloatLib、MIT、FloatLib Team。没有新引入大规模 proof dependency，仍使用固定 `ContractTensor` 已导入的声明；摘录父桥仅为补齐固定 pin 缺少的 native finite multiplication refinement。
