# FloatLib R5-W02：用一次 toBits 完成 finish 的有限性判断与原始字构造

日期：2026-10-22  
固定环境：Lean v4.34.0；FloatLib `0d91825727839f597fd06b22fdd038ea21480f0c`；官方项目 `978cc5b445edb9943fd9953b0a9037d97a9f33a8`。

## 1. 决策与状态

**值得接入现有父本，先编译这个很小的桥。全域 guard 等价和任意 raw fallback 的整体等价已经写出完整证明体，静态源码核对没有留下新的数学命题缺口。全部 Lean 编译、依赖公理审计、官方 policy/gate、候选 C 生成和性能计时均为 NOT_RUN。**

本机 PATH 中没有 Lean/lake，本轮没有安装工具链。本文交付的是可送固定环境编译的完整证明草稿，不能把它标成“已通过 Lean”或“已通过 gate”。父本通过三次完整 gate、原实际 C 的调用情况，来自本轮用户陈述；本轮独立验证的是公开父本的字节与 SHA256、固定源码定义、证明结构和集成文本。

这个变更只处理 `Submission.Packed10.finish` 的最终结果分类与构造。它不改变乘法、累加、点积次序、decode、布局或输出行序；sum 的其他 result guard 也未改动。已有数值合同继续由原父本与 `finish_eq_dot` 桥连接。

| 项目 | 本轮状态 |
|---|---|
| 父本公开文件与给定 SHA256 | VERIFIED |
| 全域 guard、构造与 finish 等价证明体 | WRITTEN；NOT_RUN |
| 独立静态源码/集成审阅 | 完成；未发现未修复的具体问题 |
| 补丁生成、父本哈希锁定、单文件 UTF-8/大小/单 import | 已做机械核对 |
| 禁用文本预筛 | 已做；不是官方 policy 执行 |
| Lean elaboration/kernel 检查 | NOT_RUN |
| `#print axioms` 依赖审计 | NOT_RUN |
| 官方 gate、候选生成 C、实际计时 | NOT_RUN |
| 新 C surrogate 或性能数字 | 没有 |

## 2. 固定父本与实际改动位置

父本：[Miner / e5b144bf… / f01-d4-final-lowmul/Kernel.lean][P]。

- 原文件：132,965 bytes。
- 原 SHA256：`ba93c233f87935aaadb9ec697487b316d4538d014831ee8d6e00127d6c34f630`，与用户给定一致。
- 新完整候选：136,051 bytes，只有 `import ContractTensor`。
- 新 SHA256：`c09eb599cebddb59acd2a5fad1e6d8ce4eba1ca27f8469e03e6592b40d944b7a`。
- 新桥模块：`candidate/FiniteBits.lean`，2,693 bytes。
- 新完整候选：`candidate/Kernel.lean`，保留原父本许可证头。

原父本第 2671 行附近的 fallback 并非一个叫 `NativeFinal.dotFallback` 的函数，而是直接内嵌的 `Fin.foldl`。本交付逐字保留这段运行时 else 表达式，包括原 raw A/B、getD、索引、Submission.mul/add 和 posZero。[P]

父本 `finish_eq_dot` 原本只需 `rw [hs] <;> rfl`。改变 guard 后不再是纯定义相等，必须补上 `finish_eq_original` 再改写。后续 `finish_eq_fold`、lane 和 bmm 证明接口保持原样。

## 3. 全域证明为何能够闭合

定义 UInt32 分类器：

```lean
@[inline] def finiteBits (u : UInt32) : Bool :=
  ((u >>> 23) &&& 255) != 255
```

目标是 Bool 本身的相等，强于仅证明某一类输入的测试：

```lean
theorem isFinite_eq_finiteBits (v : Float32) :
    v.isFinite = finiteBits v.toBits
```

### 3.1 native 两个操作有公开逻辑定义

Lean v4.34.0 的 `Float32.isFinite` 定义为 `v.toModel.isFinite`；`Float32.toBits` 定义为 `v.toModel.toBits`。模型的 isFinite 再定义为 `unpack.isFinite`。因此证明可以直接 `change` 到 unpack 分类，不依赖新的 cast 语义前提。[L1][L2]

### 3.2 任意 raw BitVec 的分类

对任意 Format 与任意该宽度的 bits：

```lean
(unpack spec bits).isFinite =
  if unpackExponent bits = (-1 : BitVec spec.exponentBits)
  then false else true
```

展开固定 unpack：

- 指数全一：fraction 为零得到 infinity，否则得到 notANumber；两者 isFinite 都为 false。
- 指数为零但不进入上述分支：fraction 为零得到有符号 zero，否则得到 subnormal 对应的 finite；两者 isFinite 都为 true。
- 其他指数：得到 normal 对应的 finite，isFinite 为 true。

所以 `unfold ...; split_ifs <;> rfl` 就是完整按定义的证明。这里对 bits 没有 canonical-NaN validity 前提。[L3][L4]

### 3.3 指数字段与 UInt32 运算的桥

公开引理把 extract 的自然数值变成：

```text
(unpackExponent u.toBitVec).toNat
= (u.toNat >>> 23) % 256
= (u.toNat >>> 23) &&& (2^8 - 1)
= (((u >>> 23) &&& 255) : UInt32).toNat
```

使用 `BitVec.extractLsb'_toNat`、UInt32 的 `toNat_toBitVec/toNat_and/toNat_shiftRight` 以及 `Nat.and_two_pow_sub_one_eq_mod`。UInt32 位移确实把位移量对 32 取模；这里常量 23 的取模可由定义规约。两个 `toNat_inj.mp` 则把自然数值相等送回 BitVec/UInt32 相等。[L5][L6][L7]

没有枚举 2^32 个 word，没有用有限 decide 例子替代量词证明。

### 3.4 同一个 toBits 的构造是 rfl

固定 FloatLib 的公开定义：

```lean
ofFloat32 v := ofBits32 v.toBits
```

`ofBits32` 只把 UInt32 装入配置好的 raw carrier，不调用 native `Float32.ofBits`。所以：

```lean
ofBits32 v.toBits = ofFloat32 v
```

对所有 v 都由 `rfl` 成立，包括 NaN。这不是任意 raw NaN word 的 native 往返定理。[F1]

### 3.5 任意 raw fallback 的整体等式

交付的最终小定理是：

```lean
theorem finish_expr_eq (v : Float32) (fallback : Competition.Binary32) :
    (let u := v.toBits
     if hf : finiteBits u = true then
       FloatLib.Floats.ExecFloat.Binary.ofBits32 u
     else fallback) =
    (if hf : v.isFinite = true then
       FloatLib.Floats.ExecFloat.Binary.ofFloat32 v
     else fallback)
```

它没有有限性假设，也不要求 fallback 的任何数值性质。fallback 可以是任意 raw Binary32，包括带任意 payload 的 NaN 或负零。证明仅展开 let 与 ofFloat32，再改写 guard。

## 4. 完整最小桥模块

以下与 ZIP 内 `candidate/FiniteBits.lean` 完全相同。**所有证明体已写完，尚未编译。**

```lean
import ContractTensor

namespace R5W02

open Float.Model
open Float.Model.UnpackedFloat

@[inline] def finiteBits (u : UInt32) : Bool :=
  ((u >>> 23) &&& 255) != 255

theorem unpack_isFinite_eq (spec : Format) (bits : BitVec spec.numBits) :
    (Float.Model.UnpackedFloat.unpack spec bits).isFinite =
      if unpackExponent bits = (-1 : BitVec spec.exponentBits) then false else true := by
  unfold Float.Model.UnpackedFloat.unpack
  split_ifs <;> rfl

theorem exponent_toNat (u : UInt32) :
    (unpackExponent (spec := Format.binary32) u.toBitVec).toNat =
      (((u >>> 23) &&& 255) : UInt32).toNat := by
  simp only [unpackExponent, BitVec.extractLsb'_toNat, UInt32.toNat_toBitVec,
    UInt32.toNat_and, UInt32.toNat_shiftRight]
  change (u.toNat >>> 23) % 256 = (u.toNat >>> 23) &&& (2 ^ 8 - 1)
  rw [Nat.and_two_pow_sub_one_eq_mod]

theorem exponent_allOnes_iff (u : UInt32) :
    unpackExponent (spec := Format.binary32) u.toBitVec = -1#8 ↔
      (((u >>> 23) &&& 255) : UInt32) = 255 := by
  constructor
  · intro h
    apply UInt32.toNat_inj.mp
    have hh := congrArg BitVec.toNat h
    rw [exponent_toNat] at hh
    exact hh
  · intro h
    apply BitVec.toNat_inj.mp
    rw [exponent_toNat]
    exact congrArg UInt32.toNat h

theorem isFinite_eq_finiteBits (v : Float32) :
    v.isFinite = finiteBits v.toBits := by
  change (Float.Model.UnpackedFloat.unpack Format.binary32 v.toBits.toBitVec).isFinite = _
  rw [unpack_isFinite_eq]
  by_cases h : (((v.toBits >>> 23) &&& 255) : UInt32) = 255
  · have he := (exponent_allOnes_iff v.toBits).2 h
    simp [he, finiteBits, h]
  · have he : unpackExponent (spec := Format.binary32) v.toBits.toBitVec ≠ -1#8 := by
      intro he
      exact h ((exponent_allOnes_iff v.toBits).1 he)
    simp [he, finiteBits, h]

theorem isFinite_true_iff (v : Float32) :
    v.isFinite = true ↔ finiteBits v.toBits = true := by
  rw [isFinite_eq_finiteBits]


theorem ofBits32_toBits_eq_ofFloat32 (v : Float32) :
    FloatLib.Floats.ExecFloat.Binary.ofBits32 v.toBits =
      FloatLib.Floats.ExecFloat.Binary.ofFloat32 v :=
  rfl

theorem finish_expr_eq (v : Float32) (fallback : Competition.Binary32) :
    (let u := v.toBits
     if hf : finiteBits u = true then
       FloatLib.Floats.ExecFloat.Binary.ofBits32 u
     else fallback) =
    (if hf : v.isFinite = true then
       FloatLib.Floats.ExecFloat.Binary.ofFloat32 v
     else fallback) := by
  change
    (if hf : finiteBits v.toBits = true then
       FloatLib.Floats.ExecFloat.Binary.ofBits32 v.toBits
     else fallback) =
    (if hf : v.isFinite = true then
       FloatLib.Floats.ExecFloat.Binary.ofBits32 v.toBits
     else fallback)
  rw [isFinite_eq_finiteBits v]

end R5W02
```

这是本轮新写的小桥，没有复制任何 FloatLib private helper，也没有新增未证假设。核心证明只用已公开定义和公开整数/BitVec 引理。声明依赖与来源详见 `sources/Dependencies.md`；实际递归公理列表必须在目标 Lean 环境由独立诊断命令打印后确认。

## 5. 最短集成方法

有三种使用方式，选择一种即可：

1. 直接取 `candidate/Kernel.lean`，作为针对给定父本的新独立候选送原固定环境编译。
2. 对仍为同一 SHA 的父本应用 `integration/Kernel.patch`。
3. 已有父本另作开发时，把 `FiniteBits.lean` 中 import 后的整个 R5W02 namespace 放入自己的单文件，再用 `Packed10Replacement.lean.inc` 替换父本的 finish 与 finish_eq_dot 小段。合并时按语义检查，不能把 SHA 锁定脚本强行用于不同父本。

提供的标准库 Python 脚本只读取父本并创建新输出，不覆盖输入、不联网：

```bash
python3 integration/apply_to_parent.py /path/to/parent/Kernel.lean /path/to/new/Kernel.lean
```

脚本要求父本 SHA 精确一致并拒绝覆盖已存在的输出；其生成结果已与包内 `candidate/Kernel.lean` 逐字比较一致。

实际替换片段如下。**该片段需要处在父本现有 `Submission.Packed10` namespace 和 open 环境中；它不是独立模块。**

```lean
def finish (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
    (result : Float32) : Binary32 :=
  let u := result.toBits
  if hf : R5W02.finiteBits u = true then ExecFloat.Binary.ofBits32 u
  else Fin.foldl n
    (fun a i => Submission.add a
      (Submission.mul (Araw.getD (baseA + i.val) posZero)
        (Braw.getD (baseB + i.val * p) posZero))) posZero

theorem finish_eq_original (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
    (result : Float32) :
    finish n baseA baseB p Araw Braw result =
      (if hf : result.isFinite = true then ExecFloat.Binary.ofFloat32 result
       else Fin.foldl n
         (fun a i => Submission.add a
           (Submission.mul (Araw.getD (baseA + i.val) posZero)
             (Braw.getD (baseB + i.val * p) posZero))) posZero) := by
  exact R5W02.finish_expr_eq result _

theorem finish_eq_dot (n baseA baseB p : Nat) (Araw Braw : Array Binary32)
    (result : Float32)
    (hs : result = NativeFinal.dotLoop n baseA baseB p Araw Braw 0 zero32) :
    finish n baseA baseB p Araw Braw result =
      NativeFinal.dot n baseA baseB p Araw Braw := by
  rw [finish_eq_original, hs] <;> rfl
```

### fallback 的执行位置必须保留

`finish_expr_eq` 是量化 fallback 值的**定理**；其证明会被擦除。不要据此把运行时实现改成 `helper v (expensiveFallback ...)`：Lean 的普通值实参会先求值，可能令有限路径也执行原 fold。

本候选让原 fold 留在 else 内；有限分支才构造 raw Binary32。只把 UInt32 的 toBits 移到 guard 之前。

## 6. NaN / Inf / ±0 / subnormal 边界

| native v 类别 | v.toBits 的指数字段 | 新 guard | 行为与原实现 |
|---|---:|---|---|
| +0 | 0 | true | 同一 toBits 字构造，得到原 +0 |
| −0 | 0 | true | 同一 toBits 字构造，保留 sign bit |
| 正/负 subnormal | 0 | true | 完整原 word；不做数值重构或归一化 |
| 正/负 normal，含最大有限值 | 1..254 | true | 完整原 word |
| +Inf / −Inf | 255 | false | 原 raw A/B fold |
| NaN | 255 | false | 原 raw A/B fold；canonical word 不作为 fallback 的输入 |

固定运行时 `lean_float32_to_bits` 对 NaN 返回 `0x7fc00000`，其余值做 bit_cast。因此新增的前置 toBits 确实会在 NaN 路径执行原先不会执行的规范化操作，但这个结果只用于分类，随后仍执行完全相同的原 raw fallback。[C1]

整个证明没有使用 `(Float32.ofBits raw).toBits = raw` 这一对任意 NaN payload 不成立的断言。对 v 的逻辑分类由公开模型定义完成；对 fallback 的 raw payload 则完全不加限制。

## 7. 现有 Binary32.isFinite 的取舍

FloatLib 公开的 `ExecFloat.isFinite` 路径是：

```text
ExecFloat.isFinite → Model.isFinite → Model.IEEE.isFinite → expField != expAllOnesNat
```

这在 binary32 上语义正是 exponent != 255，可以作为规格接口。然而固定源码中的 expField 经过 BitVec/Nat；`Model/Fields/Optimized.lean` 的编译器替换 `expFieldImpl` 仍以 `x.toNatBits` 做 Nat 位运算。仅凭 inline 标记不能保证最后生成裸 UInt32 指令。[F2][F3][F4]

本候选直接使用 UInt32 shift/and/compare；这样代码生成目标明确，且证明只需三个短整数桥。没有额外运行一个“先构造 Binary32 再调用其 isFinite”的版本。

## 8. 调用数与真实性能的边界

设执行 finish 的输出数为 R，其中 native result 有限的数量为 F。只统计 finish 这一层的 isFinite/toBits 边界调用，不统计未改变的 fallback 内部工作：

| 路径 | 原 finish | 新 finish 的预期形态 |
|---|---|---|
| 有限 result | isFinite + toBits | toBits + UInt32 位运算 |
| 非有限 result | isFinite + 原 fallback | toBits + UInt32 位运算 + 原 fallback |
| R 次 finish 合计 | R + F 次相关调用 | R 次相关调用 |

所以减少 F 次调用。若 R=5000 且 F=5000，相关调用数从 10000 变为 5000。用户所说的“5000 个有效输出”本身不等价于“5000 个 native result 都有限”，这里保留该条件。

预期 C 形态如下，仅为源码推导，**不是本轮实际编译输出**：

```c
uint32_t u = lean_float32_to_bits(v);
if (((u >> 23) & 255u) != 255u) {
    return raw_binary32_from_u(u);
} else {
    return original_raw_fallback(...);
}
```

其中 `raw_binary32_from_u` 只是解释用占位名，不是新增函数/API。实际 raw 包装成本与原有限分支是同一个定义。

固定 lean.h 中 UInt32 shift、and、比较是内联整数运算；isFinite/toBits 由 runtime 提供边界函数。[C1][C2] 但 toBits 内部仍做 isnan 检查并规范化，不能把它称作无条件 bitcast。新实现也增加显式整数分类，非有限路径把 isFinite 换成 toBits 而非减少调用。

**当前没有加速比结论。** 这个变动每个输出只作用一次，不作用于每个 k。整个 bmm 的收益还受点积工作量、fallback 比例、编译器是否共享 u、包装和调用成本影响；相关调用数减半绝不等于整个 kernel 加速两倍。

最小后续决策是：在既有固定环境编译本桥与完整候选，确认 finish 的可达代码为一次 toBits 且没有额外 isFinite，再走原不变 gate 的配对计时。若生成代码仍重复 toBits，或者原 gate 实测无收益/有回退，就保留父本。这些检查本轮均未执行，也未调整任何编译参数。

## 9. 诊断与文本扫描

`diagnostics/Commands.lean.inc` 只放 `#check` 与 `#print axioms`。它不属于提交候选。可在固定环境把它追加到一个临时的完整候选副本，再用原有 Lean 环境检查；不要把诊断尾部一起送 policy。

需观察的公理集合为 `propext`、`Classical.choice`、`Quot.sound` 的子集。此处是验收要求，**不是已取得的打印结果**。候选文件没有新声明此类前提；也没有用有限算例代替任意 v 的分类证明。

本轮内部禁用文本预筛读取了固定 gate.py 的 BANNED 正则，但没有执行官方 policy：其他准入、声明、导入、属性、公理及 gate 阶段并不由这一文本检查覆盖。预筛发现 `-1#_` 的 `#_` 会命中命令式正则，已改成定义等价的 `(-1 : BitVec spec.exponentBits)`。诊断命令仅保留在独立文件，候选注释也未引入禁用词。

`diagnostics/Validation.json` 记录本轮机械检查与 NOT_RUN 项目；`diagnostics/StaticReview.md` 是独立静态审阅，不是编译日志。

## 10. 许可、来源和交付清单

Lean 源按 Apache 2.0 发布；FloatLib 按 MIT 发布；父本保留了 Conjectures.io 与 FloatLib 等原版权/许可说明。完整副本置于 `LICENSES/`。本轮没有 private 辅助证明移植。原父本许可证头在新 Kernel 中完整保留；片段随附相同第三方说明。

`sources/source_manifest.json` 记录本轮实际核对的固定公开源 URL、文件 SHA256 与字节数，不混入私有附件或会话内容。源码哈希标识读取的字节，不代表编译环境已构建。新包不修改此前交付。

| 文件 | 用途 |
|---|---|
| `candidate/FiniteBits.lean` | 独立最小全域桥，单 import |
| `candidate/Kernel.lean` | 对给定父本集成后的完整单文件候选 |
| `integration/Packed10Replacement.lean.inc` | 最短局部替换 |
| `integration/Kernel.patch` | 精确父本 diff |
| `integration/apply_to_parent.py` | SHA 锁定、仅创建新文件的集成脚本 |
| `integration/ParentFinish.lean.txt` | patch 对照的原小段 |
| `diagnostics/Commands.lean.inc` | 独立声明/公理诊断命令 |
| `diagnostics/Validation.json` | 本轮检查状态 |
| `diagnostics/StaticReview.md` | 独立静态审阅 |
| `sources/Dependencies.md` | 声明依赖与来源定位 |
| `sources/source_manifest.json` | 固定源 URL/SHA256 |
| `LICENSES/` | 许可原文及父本通知 |
| `SHA256SUMS` | ZIP 中各有效载荷文件的校验和 |

### 一手来源

[P]: https://github.com/HuanHuanHuanFFF/Miner/blob/e5b144bf77d477919f4787e36311cf65d2a23c15/competitions/floatlib/candidates/f01-d4-final-lowmul/Kernel.lean#L2671-L2694
[L1]: https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Float/Float32.lean#L145-L146
[L2]: https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Float/Model/Float32.lean#L184-L185
[L3]: https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Float/Model/Unpacked/Pack/Basic.lean#L74-L109
[L4]: https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Float/Model/Unpacked/Operations/Status.lean#L20-L24
[L5]: https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/BitVec/Lemmas.lean#L1109-L1110
[L6]: https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/UInt/Bitwise.lean#L37-L41
[L7]: https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Nat/Bitwise/Lemmas.lean#L537
[F1]: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/IEEE754/Native.lean#L62-L122
[F2]: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Configured/Value/Core.lean#L119-L121
[F3]: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Model/Carrier.lean#L128-L166
[F4]: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Model/Fields/Optimized.lean
[C1]: https://github.com/leanprover/lean4/blob/v4.34.0/src/runtime/object.cpp#L1976-L2004
[C2]: https://github.com/leanprover/lean4/blob/v4.34.0/src/include/lean/lean.h#L2098-L2115

固定官方合同：[ContractTensor.lean](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/contract/ContractTensor.lean)。固定依赖配置：[lakefile.lean](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/lakefile.lean)。原 bench 与 gate 未修改。

