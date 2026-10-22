# FloatLib R2-W01：固定 binade 顺序和的公开源码桥接

## 结论与验证状态

**已找到一条实际存在、可由 `import ContractTensor` 访问的桥接链：**

`ExecFloat.add` → configured codec 的 `Model.Spec.add` → `Model.add` → `Model.toReal_add_eq_roundAt` → 固定格点的 nearest-even 数学引理 → `Model.eq_of_toReal_eq_of_nonzero` → configured codec 单射 → 完整 binary32 字等式。

关键好消息是：**“双方有限、实值相等且非零推出全字相等”已经有公开定理，不用从字段重新证明。** 主要缺口是把候选整数前缀区间证书转换为 `roundAt` 的固定格点舍入等式，以及验证双 parity 块摘要、机器整数运算和数组/向量遍历。

本文只使用给定消息、以下固定公开提交及自行构造的数学例。没有读取旧会话、旧项目附件或私有资料，没有安装工具链或执行下载的代码。已下载的 6 个比赛文件、73 个 FloatLib 文件均逐个计算 Git blob SHA 并与固定提交的 GitHub tree 比较，零差异。`command -v lean` 无结果。

**所有新增 Lean 草稿均未编译。未做 `#print axioms` 检查。本文不声称已有完整、可提交或有性能收益的 Kernel。** `BridgeDraft.lean` 为 5,155 bytes，只含 `import ContractTensor` 一个 import；它显式把尚未证明的固定 binade 性质作为参数，不使用占位证明。

固定版本：

- 比赛仓库：`978cc5b445edb9943fd9953b0a9037d97a9f33a8`。
- FloatLib：`0d91825727839f597fd06b22fdd038ea21480f0c`。
- 比赛的 `lean-toolchain` 明确为 `leanprover/lean4:v4.34.0`：[lean/lean-toolchain:1](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/lean-toolchain#L1)。

后文为缩短公式用 `M` 指 `FloatLib.Floats.Formats.BinaryInterchange.Model`，`Flocq` 指 `FloatLib.Floats.Formats.Flocq`，`N` 指 `FloatLib.Numerics`。表中列的是源码中的命名，不把推导目标冒充已有定理。

## 1. 合同和基准的精确边界

| 项目 | 固定源码事实 | 对快路的含义 |
|---|---|---|
| binary32 | `Competition.Binary32 := ExecFloat.Binary (exponentBits := 8) (fractionBits := 23)` | 不是宿主 double 的求和合同。 |
| 起始状态 | `Competition.posZero := ExecFloat.Binary.zero false` | 空和与第一次加法从 `+0` 开始。 |
| 顺序和 | `sumSpec x := (List.finRange n).foldl (fun acc i => ExecFloat.add acc (x i)) posZero` | 每个中间前缀都属于合同；总和一次舍入不能一般替代。 |
| 全域义务 | `SumObligation kernel := ∀ n x, kernel x = sumSpec x.get` | 基准输入分布只能用于性能选路，不能缩小证明量词。 |
| bmm | 对每个输出按 `k` 左折叠 `ExecFloat.add acc (ExecFloat.mul a b)` | 乘积先舍入，之后每次加法再舍入；不能换成 FMA。 |
| sum 长度 | `Bench.sumLen = 1000` | 仅基准定长；合同仍任意 `n`。 |
| sum dense | 指数字段 `124 + (...) % 7`，随机符号 | 非零有限，绝对值在 `[2^-3, 2^4)`。 |
| sum relu | 约半数 `+0`，其余同上且正号 | 便于正 binade 块；仍不自动保证固定格点无舍入。 |
| sum wide | 指数字段 `102 + (...) % 50`，随机符号 | 绝对值在 `[2^-25, 2^25)`，吸收和抵消都可能出现。 |
| bmm 形状 | `50 × 100` 乘 `100 × 50` | 每个输出 100 次乘加步骤。 |
| bmm relu | **A 使用 `bmmRelu`，B 使用 `bmmDense`** | **B 有混合符号，乘积和输出前缀都不保证非负。** |
| raw | 包含任意字；sum 与 bmm 中 `timed = false` | 仍检查结果，且合同完全覆盖 NaN、Inf、subnormal、signed zero。 |

来源：[lean/contract/Contract.lean:14-17](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/contract/Contract.lean#L14-L17)；[lean/contract/ContractTensor.lean:18-30](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/contract/ContractTensor.lean#L18-L30)；[lean/contract/ContractTensor.lean:53-72](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/contract/ContractTensor.lean#L53-L72)；[lean/bench/BenchTensor.lean:18-36](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/bench/BenchTensor.lean#L18-L36)；[lean/bench/BenchBmm.lean:18-36](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/bench/BenchBmm.lean#L18-L36)。

`M.toReal` 对 NaN 和 Inf 都返回 0，且实数无法区分 `+0` 和 `-0`。因此不能把裸 `toReal` 相等当成全域位等价：[FloatLib/Floats/Formats/BinaryInterchange/Model/RealSemantics.lean:75-86](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Model/RealSemantics.lean#L75-L86)。

## 2. 单 import 可达性已经从源文件追踪

合同只要求最终文件 `import ContractTensor`。已检查的公开导入路径是：

1. `ContractTensor` → `Contract` → `FloatLib` → `FloatLib.Floats` → `FloatLib.Floats.Formats` → `BinaryInterchange`。
2. `BinaryInterchange` 的公共 import 含 `Semantics`、`Configured`、`Reduction`。
3. `Semantics` 公共 import `Arithmetic.Semantics`、`DirectedSemantics.Exact` 等。
4. `Configured` 公共 import `Conversion.Text.Roundtrip`；后者公共 import `Conversion.Text.Representation`，其中包含关键 `eq_of_toReal_eq_of_nonzero`。
5. `Configured` 也公共 import `Configured.Instances` 和 `Configured.Value.CoreProof`，提供 codec 单射及互逆。

源码入口：[FloatLib/Floats.lean:9-13](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats.lean#L9-L13)；[FloatLib/Floats/Formats.lean:9-16](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats.lean#L9-L16)；[FloatLib/Floats/Formats/BinaryInterchange.lean:28-43](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange.lean#L28-L43)；[FloatLib/Floats/Formats/BinaryInterchange/Semantics.lean:9-33](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Semantics.lean#L9-L33)；[FloatLib/Floats/Formats/BinaryInterchange/Configured.lean:9-26](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Configured.lean#L9-L26)；[FloatLib/Floats/Formats/BinaryInterchange/Conversion/Text/Roundtrip.lean:8-12](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Conversion/Text/Roundtrip.lean#L8-L12)。

这是源码层面的可达性检查；由于没有 Lean，尚未通过单 import 的 elaboration 实测。尤其不能把 `private theorem` 当成可调用 API。下表只选 public 声明。

## 3. 实际存在的桥接定理

### 3.1 合同执行值 → descriptor model

| 精确名称 | 作用和必要条件 | 来源 |
|---|---|---|
| `FloatLib.Floats.ExecFloat.Proof.add_eq_spec` | 对任意两个配置值，把 `ExecFloat.add` 改写成 `ExecFloat.Spec.add`，含全部位信息。 | [FloatLib/Floats/ExecFloat/Proof/Arithmetic.lean:35-39](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/ExecFloat/Proof/Arithmetic.lean#L35-L39) |
| `FloatLib.Floats.ExecFloat.Spec.add` | 定义为该 capability 的 `Add.spec`。binary32 固定 capability 的 `spec := Configured.Spec.add`。 | [FloatLib/Floats/ExecFloat/Spec/Arithmetic.lean:36-45](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/ExecFloat/Spec/Arithmetic.lean#L36-L45)；[FloatLib/Floats/Formats/BinaryInterchange/Configured/NativeDispatch.lean:46-54](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Configured/NativeDispatch.lean#L46-L54) |
| `FloatLib.Floats.Formats.BinaryInterchange.Configured.Spec.add` | 不是重新定义舍入；它是 `ModelCodec.liftBinary ... Model.Spec.add`。 | [FloatLib/Floats/Formats/BinaryInterchange/Configured/Core/Runtime.lean:38-44](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Configured/Core/Runtime.lean#L38-L44) |
| `FloatLib.Floats.ExecFloat.ModelCodec.decode_liftBinary` | decode 一个 liftBinary 结果，得到 descriptor operation 作用于两个 decode。 | [FloatLib/Floats/ExecFloat/Carrier.lean:195-202](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/ExecFloat/Carrier.lean#L195-L202) |
| `FloatLib.Floats.Formats.BinaryInterchange.Model.Proof.add_eq_spec` | `M.add x y = M.Spec.add x y`。 | [FloatLib/Floats/Formats/BinaryInterchange/Arithmetic/Proof.lean:30-37](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Arithmetic/Proof.lean#L30-L37) |
| `FloatLib.Floats.Formats.BinaryInterchange.Model.Spec.add` | 两个 `toDyadic?` 都成功时，定义就是 `roundDyadic fmt (addDyadic dx dy)`；否则按原 NaN/Inf 分支。 | [FloatLib/Floats/Formats/BinaryInterchange/Spec/Dyadic.lean:36-52](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Spec/Dyadic.lean#L36-L52) |

**命名陷阱：** `FloatLib.Floats.ExecFloat.Binary.toModel_add` 确实存在，但它证明的是有显式 `rounding` 参数的 `ExecFloat.Binary.add`，不是合同里的 `ExecFloat.add`。它不能不经定义核对就拿来直接改写合同。[FloatLib/Floats/Formats/BinaryInterchange/Configured/Rounding/Proof.lean:43-47](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Configured/Rounding/Proof.lean#L43-L47)

### 3.2 descriptor addition → 实数逐步舍入

| 精确名称 | 可用结论 | 来源 |
|---|---|---|
| `FloatLib.Floats.Formats.BinaryInterchange.Model.toReal_add_eq_roundAt` | 在 IEEE、两个输入有限、结果有限的条件下，`toReal (add x y) = roundAt fmt (toReal x + toReal y)`。 | [FloatLib/Floats/Formats/BinaryInterchange/Arithmetic/Semantics.lean:72-88](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Arithmetic/Semantics.lean#L72-L88) |
| `FloatLib.Floats.Formats.BinaryInterchange.Model.isFinite_add_of_abs_toReal_add_le_posMaxFinite` | 输入有限、精确实数和绝对值 ≤ 最大有限数，推出加法结果有限。无需先执行参考加法再检查结果。 | [FloatLib/Floats/Formats/BinaryInterchange/Arithmetic/Semantics.lean:37-50](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Arithmetic/Semantics.lean#L37-L50) |
| `FloatLib.Floats.Formats.BinaryInterchange.Model.isFinite_add_of_abs_add_le_posMaxFinite` | 更保守的三角不等式条件：`abs x + abs y ≤ maxFinite`。有较强抵消时优先上一条。 | [FloatLib/Floats/Formats/BinaryInterchange/Arithmetic/Semantics.lean:56-63](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Arithmetic/Semantics.lean#L56-L63) |
| `FloatLib.Floats.Formats.BinaryInterchange.Model.Dyadic.toReal_addDyadic` | `addDyadic` 的实值是精确实数加法。 | [FloatLib/Floats/Formats/BinaryInterchange/Model/RealSemantics.lean:56-62](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Model/RealSemantics.lean#L56-L62) |
| `FloatLib.Floats.Formats.BinaryInterchange.Model.roundAt_neg` | `roundAt fmt (-x) = -roundAt fmt x`，可用于负 binade 镜像。 | [FloatLib/Floats/Formats/BinaryInterchange/Rounding/Proof.lean:71-82](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Rounding/Proof.lean#L71-L82) |

`M.roundAt` 是本文该用的实际 API。它是 Flocq `round ... nearestEven`，采用 gradual-underflow grid，但实数格点没有最大指数限制，因此 `toReal_add_eq_roundAt` 的 finiteness 不能省略。[FloatLib/Floats/Formats/BinaryInterchange/Rounding/Proof.lean:49-64](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Rounding/Proof.lean#L49-L64)

在已检查的固定 FloatLib 文件中没有找到 `roundNearestReal` 这个声明；不要把这个叙述性名称当成可调用的已存在定理。

### 3.3 实数舍入 → dyadic / 商余数 / parity

| 精确名称 | 对固定 binade 的用途 | 来源 |
|---|---|---|
| `FloatLib.Floats.Formats.BinaryInterchange.Model.roundAt_dyadic_eq` | 非零 dyadic 的 `roundAt` 等于带符号的整数 `roundMantissaAtExponentEven` 乘目标 2 的幂。IEEE 前提显式。 | [FloatLib/Floats/Formats/BinaryInterchange/Rounding/Proof.lean:276-305](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Rounding/Proof.lean#L276-L305) |
| `FloatLib.Floats.Formats.BinaryInterchange.Model.cexp_toReal_eq_targetExponent` | Flocq 的 `cexp` 与 Lean logical float 的 `targetExponent` 一致。 | [FloatLib/Floats/Formats/BinaryInterchange/Rounding/Proof.lean:176-187](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Rounding/Proof.lean#L176-L187) |
| `FloatLib.Floats.Formats.BinaryInterchange.Model.targetExponent_eq_normal` | 若 dyadic 最高位指数在 normal 范围，目标指数是 `log2(mantissa) + exponent - fracWidth`。 | [FloatLib/Floats/Formats/BinaryInterchange/ModelRounding/Proof.lean:469-481](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/ModelRounding/Proof.lean#L469-L481) |
| `FloatLib.Floats.Formats.BinaryInterchange.Model.targetExponent_eq_minSubnormal_of_lt_minNormal` | 对 subnormal 区域使用恒定最小指数。 | [FloatLib/Floats/Formats/BinaryInterchange/ModelRounding/Proof.lean:454-466](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/ModelRounding/Proof.lean#L454-L466) |
| `FloatLib.Floats.Formats.BinaryInterchange.Model.nearestEven_scaledMagnitude` | 非负 dyadic 的实数 nearest-even 与 `roundMantissaAtExponentEven` 一致。 | [FloatLib/Floats/Formats/BinaryInterchange/Rounding/Proof.lean:212-249](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Rounding/Proof.lean#L212-L249) |
| `FloatLib.Floats.Formats.BinaryInterchange.Model.nearestEven_scaledDyadic` | 上一条的有符号版本。 | [FloatLib/Floats/Formats/BinaryInterchange/Rounding/Proof.lean:252-263](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Rounding/Proof.lean#L252-L263) |
| `FloatLib.Floats.Formats.BinaryInterchange.Model.nearestEven_div_pow2_eq_roundShiftRightEven` | `nearestEven (num / 2^shift)` 等于自然数 `roundShiftRightEven`。 | [FloatLib/Floats/Formats/BinaryInterchange/Rounding/NearestEven.lean:192-198](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Rounding/NearestEven.lean#L192-L198) |
| `FloatLib.Numerics.roundShiftRightEven_eq_roundQuotientEven` | shift 舍入等于除以 2 的幂后的商余数舍入。 | [FloatLib/Numerics/Quantization/Deterministic/ShiftRight.lean:111-126](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Numerics/Quantization/Deterministic/ShiftRight.lean#L111-L126) |
| `FloatLib.Numerics.roundQuotientEven_eq_quotient_add` | 商 + 0/1，进位只由 remainder 和商 parity 决定。 | [FloatLib/Numerics/Quantization/Deterministic/Quotient.lean:66-76](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Numerics/Quantization/Deterministic/Quotient.lean#L66-L76) |
| `FloatLib.Numerics.nearestEvenRoundsUp` | 可执行 Bool 判据：`denominator < 2*remainder || (denominator == 2*remainder && quotientOdd)`。 | [FloatLib/Numerics/Quantization/Deterministic/Quotient.lean:30-34](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Numerics/Quantization/Deterministic/Quotient.lean#L30-L34) |

四个最直接的实数分支也确实存在：

- `FloatLib.Floats.Formats.Flocq.nearestEven_eq_floor_of_frac_lt_half`。
- `FloatLib.Floats.Formats.Flocq.nearestEven_eq_ceil_of_frac_gt_half`。
- `FloatLib.Floats.Formats.Flocq.nearestEven_eq_floor_of_frac_half_even`。
- `FloatLib.Floats.Formats.Flocq.nearestEven_eq_ceil_of_frac_half_odd`。

源码和完整前提：[FloatLib/Floats/Formats/Flocq/Theory/Rounding/Core.lean:166-199](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/Flocq/Theory/Rounding/Core.lean#L166-L199)。此外 `nearestEven_abs_sub_le_half` 可将候选整数结果的区间转成精确实数和的半格点区间，见 [FloatLib/Floats/Formats/Flocq/Theory/Rounding/Core.lean:288-296](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/Flocq/Theory/Rounding/Core.lean#L288-L296)。

### 3.4 有限非零实值等式 → 全位等式

最有用的现成结论在文件名不直观的 `Conversion/Text/Representation.lean`：

```lean
FloatLib.Floats.Formats.BinaryInterchange.Model.eq_of_toReal_eq_of_nonzero
  {fmt : FloatFormat} {x y : Model fmt}
  (hx : isFinite x = true) (hy : isFinite y = true)
  (hvalue : toReal x = toReal y) (hzero : toReal x ≠ 0) : x = y
```

源码：[FloatLib/Floats/Formats/BinaryInterchange/Conversion/Text/Representation.lean:78-108](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Conversion/Text/Representation.lean#L78-L108)。

随后用 `FloatLib.Floats.ExecFloat.Binary.toModel_inj` 或 `Configured.Family.toModel_injective` 即回到配置载体相等。前者为 `toModel left = toModel right ↔ left = right`；后者为 codec 单射。[FloatLib/Floats/Formats/BinaryInterchange/Configured/Instances.lean:67-70](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Configured/Instances.lean#L67-L70)；[FloatLib/Floats/Formats/BinaryInterchange/Configured/Storage/Family/Proof.lean:42-48](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Configured/Storage/Family/Proof.lean#L42-L48)

`ExecFloat.Binary.ofModel_toModel`、`toModel_ofModel` 与 `ofNatBits_toNatBits` 保留完整 interchange 字。[FloatLib/Floats/Formats/BinaryInterchange/Configured/Value/CoreProof.lean:29-52](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Configured/Value/CoreProof.lean#L29-L52)

**限制不可移除：** 相同实数 0 可能是正零或负零；NaN payload、NaN sign、Inf 无法靠此实值接口恢复。快路若承诺非零输出，现有定理恰好够用；其他情况继续原顺序实现。

## 4. 建议新增的单步 binade 引理：真实缺口

令 binary32 字段指数 `E ∈ {1,...,253}`，定义：

- `q = 2^(E - 150)`，即本 binade 的 ULP。
- `L = 2^23`，`U = 2^24`。
- 初始正累加器 `a = K*q`，`K ∈ [L, U-1]`。
- 对当前精确实数和 `v = a + x`，设 `r = nearestEven(v/q)`。

要证明的核心性质是：

> **若 `L + 1 ≤ r ≤ U`，则 `roundAt binary32 v = r*q`。**

这是应新增的定理，不是本次检索找到的已有 FloatLib 定理。它不要求加数 `x` 是 normal，只要求其实际值可正确解码且原加法有限。有限 subnormal 和 signed zero 输入都可以在不改变非零输出的情况下使用这一桥。

为什么这个保护带够用：

1. nearest-even 的半格点误差给出 `L + 1/2 ≤ v/q ≤ U + 1/2`，因此精确和位于正 normal 区域。
2. `v < U*q` 时，目标 exponent 正好是 `E-150`，可用 `roundAt_dyadic_eq`、`targetExponent_eq_normal` 和整数舍入一致性收尾。
3. `v ≥ U*q` 时，目标 exponent 切换到 `E-149`。这时原候选区间和舍入单调性迫使 `r=U`；`v/(2*q)` 位于 `[U/2, U/2+1/4]`，该较粗网格也舍入到 `U/2`，所以结果仍是 `U*q`。
4. `E≤253` 保证 `U*q` 仍是有限 normal。进一步由同一精确和上界证明 `abs v ≤ maxFinite`，调用 `isFinite_add_of_abs_toReal_add_le_posMaxFinite`，避免依赖先执行参考加法的结果守卫。
5. 镜像负 binade 可令 `a = -K*q`，对 `-v` 使用同一引理，再用 `roundAt_neg`。最终值非零，所以 `eq_of_toReal_eq_of_nonzero` 恢复符号和全部位。

**上边界 `r=U` 不能用“target exponent 一直不变”的错误前提来证明。** 允许它意味着必须独立处理上面第 3 个分支。

**下边界排除 `r=L` 是实质条件。** 自行合成反例：取 `a=1`、`q=2^-23`、`x=-3*2^-26`。统一 q 网格的舍入结果为 1；但 1 左侧的 binary32 间距是 `q/2`，正确结果为 `1-2^-24`，即字 `0x3f7fffff`。仅验证候选前缀落 `[L,U]` 会接受这个错误结果。`[L+1,U]` 排除了它。`E=1` 下界两侧间距相同，但保留统一保护条件会更便于实现和证明。

## 5. 双 parity 块摘要的精确数学接口

下面是从现成 nearest-even 定义推导的目标数学模型，不是库内现成块处理器。

固定 q 后，写每个（已按需要镜像符号的）输入为：

`x_i/q = a_i + f_i`，其中 `a_i = floor(x_i/q)`、`0 ≤ f_i < 1`。

若当前整数累加器为 K，则更新是：

`K' = K + a_i + u_i(K mod 2)`，其中：

- `f_i < 1/2`：`u_i = 0`。
- `f_i > 1/2`：`u_i = 1`。
- `f_i = 1/2`：`u_i = 0` 当 `K + a_i` 偶；否则为 1。

因此输入项在固定 q 上诱导一个二状态转移：从 parity `p ∈ {0,1}` 进入，产出整数增量 `d_i(p)` 和 parity `(p+d_i(p)) mod 2`。tie 后的总整数是偶数，但增量本身可能是奇数。**不能把 `nearestEven(K+t)` 无条件改写成 `K+nearestEven(t)`；奇整数平移会翻转 tie 选择。**

长度为 b 的块为两个入口 parity 各保存：

- `D_p`：整个块的最终整数增量。
- `m_p, M_p`：所有非空前缀的最小、最大累计整数增量。

运行时只需按实际 K 的 parity 选一个分支，验证：

`L+1 ≤ K+m_p` 且 `K+M_p ≤ U`。

这两个不等式同时覆盖本块每一步实际候选整数前缀。单步 binade 引理加 list induction 就能证明整个块与原顺序加法相同，且包含所有中间前缀的舍入。

两个摘要 A、B 的组合（`p_A=(p+D_A(p)) mod 2`）为：

- `D_AB(p) = D_A(p) + D_B(p_A)`。
- `m_AB(p) = min(m_A(p), D_A(p)+m_B(p_A))`。
- `M_AB(p) = max(M_A(p), D_A(p)+M_B(p_A))`。

这保持原顺序，只把“顺序状态机的作用”汇总，不重排浮点加法。非空前缀定义需给空块独立身份元素；若把前缀 0 也纳入 min/max，正确性仍可保留，但会更保守，特别是起点 `K=L` 时。

**仍需自证的实现部分：**

- 从 `toDyadic?` 结果构造 `a_i`、fraction 分类及商 parity 的整数算法，与实数分解一致。
- 负输入必须用向下取整和非负余数；“对绝对值截断再补符号”不能直接当 floor。
- 原始输入解码、移位、UInt 加法减法无溢出；若使用固定宽度整数，要把 checked arithmetic 的 guard 纳入证书。
- 摘要组合、min/max 更新、分块和尾块确实覆盖原序列。
- fast guard 失败时从同一个原累加器、同一原输入块继续参考语义，不能保留未验证中间状态。
- 从 `+0` 到可用 normal binade 的启动段；初始 K 不存在时应继续既有顺序累加器，直到合法入口或直接完成。

## 6. exact-prefix 格点路线：可作局部子快路，但不是原问题的替代

存在两个相关 exactness 定理：

- `M.roundDyadic_of_representable`：若 dyadic significand 是 `m*2^k`，`m<2^(fracWidth+1)`，底层 exponent 不小于最小 subnormal exponent，且 magnitude ≤ maxFinite，则舍入结果有限、实值完全不变。[FloatLib/Floats/Formats/BinaryInterchange/DirectedSemantics/Exact.lean:245-256](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/DirectedSemantics/Exact.lean#L245-L256)
- `M.roundDyadicWithRounding_of_representable`：所有四个 IEEE rounding direction 的可表示 dyadic 版。[FloatLib/Floats/Formats/BinaryInterchange/DirectedSemantics/Exact.lean:402-412](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/DirectedSemantics/Exact.lean#L402-L412)

如果能够对**每一个精确数学前缀**证明这些格点和范围条件，就能逐步证明当前顺序和等于精确前缀。因此“先以整数聚合，再编码”的路径在这类受守卫约束的块上可行。

但只证明最终总和可表示远远不够。自行合成例 `[2^24, 1, -2^24]`：顺序 binary32 从 `+0` 得 `+0`，精确总和为 1。每个输入有限且正常，最终 1 也可表示；中间的 `2^24+1` 却先 tie 到 `2^24`。

若某精确前缀等于 0，要单独追踪零符号。上述实数 exactness 定理不能独自恢复该前缀的完整字。`Conversion/Text/Representation` 另有 `roundDyadicWithRounding_zero` 和 decoded finite round-trip 定理，可用于单步编码；顺序加法产生哪个 zero sign 仍必须由 addDyadic / 原加法语义证明。[FloatLib/Floats/Formats/BinaryInterchange/Conversion/Text/Representation.lean:125-147](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Conversion/Text/Representation.lean#L125-L147)

## 7. 看似相关但不能直接完成合同的已有 API

### 7.1 `Reduction.sum` / `dot` 是一次舍入的精确累加

`M.Reduction.sumWithStatus_eq_round_of_finite_nonzero` 和 `sumWithStatus_value_toReal_eq_roundAt_of_finite_nonzero` 都明确描述 exact accumulator 的**最终一次**舍入；这不等于合同的逐次舍入。其排列不变性定理也不是顺序和的排列不变性。[FloatLib/Floats/Formats/BinaryInterchange/Reduction/Proof.lean:535-591](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Reduction/Proof.lean#L535-L591)

### 7.2 `ReductionTree` 保留逐节点舍入，但主要给误差界

`M.ReductionTree.toReal_eval` 确实把选定树的逐节点 `Model.add` 连接到逐节点 `roundAt`，条件是所有叶子与中间结果有限。`abs_toReal_eval_sub_eval_le` 给两种调度的差异上界，**没有证明换树后相等**。把左链表示为树可以使用，但不会自动获得任何块重排等价。[FloatLib/Floats/Formats/BinaryInterchange/Reduction/Tree.lean:13-18](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Reduction/Tree.lean#L13-L18)；[FloatLib/Floats/Formats/BinaryInterchange/Reduction/Tree.lean:45-78](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Reduction/Tree.lean#L45-L78)

### 7.3 NativeFPU 模块名称不能当作 native add 证明

固定提交的 `Configured.NativeFPU.Runtime` 只提供 `ofBinary32Bits`/`ofBinary64Bits` 包装、软件 FMA 等；它明确说 host Float32/Float 实验在独立的 `NativeFPU.Unchecked`。`NativeFPU.Proof` 里只有 `softwareFma32_eq_spec`、`softwareFma64_eq_spec` 两个定理。[FloatLib/Floats/Formats/BinaryInterchange/Configured/NativeFPU/Runtime.lean:13-21](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Configured/NativeFPU/Runtime.lean#L13-L21)；[FloatLib/Floats/Formats/BinaryInterchange/Configured/NativeFPU/Proof.lean:27-41](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Configured/NativeFPU/Proof.lean#L27-L41)

本任务已知的 native finite add/mul 到 ExecFloat 及顺序累加器是既有基线，直接复用，不应重包装为本研究新发现。本文没有建议导入 Unchecked、加入 unchecked host 运算或改变编译设置。

## 8. 草稿内容与还没完成的验收

`BridgeDraft.lean` 包含：

- `toModel_exec_add`：合同执行 add → descriptor add 的短 codec 证明。
- `eq_of_nonzero_model_real`：有限非零实值等式 → 配置值字相等。
- `model_add_eq_from_roundAt`：以固定-grid roundAt 等式为入口的 scalar step。
- `model_add_eq_from_bound_and_roundAt`：用符号范围证明不溢出。
- `nearestEven_eq_floor_plus_increment`：明确 floor parity 的 0/1 增量公式。
- `foldl_simulation`：保持每一步顺序的状态机到 List.foldl 归纳。
- `guarded_sum_obligation`：guard soundness + 原实现回退提升为全域 SumObligation。

这些只是可审阅的胶水草稿。**未编译**；第一条需要在实际 v4.34.0 环境确认 fixed binary32 plan 的 definitional reduction，其他条也没有 elaboration/axiom 证据。没有把任何 theorem 参数当作已获得的证明。

仍必须交付：

1. 固定 binade 单步 `roundAt` 引理，特别是上边界候选 U。
2. 输入量化与双 parity 摘要 checker 的正确性。
3. 每个前缀范围 guard、固定宽度整数溢出 guard 和失败回退的整体证明。
4. 与 Vector/Array 索引及 sumSpec/bmmSpec 的衔接；bmm 输入项必须是原 `ExecFloat.mul` 的结果。
5. 在原依赖、原编译选项下编译；检查 `SumObligation` / `BmmObligation` 最终定理只依赖允许的 axioms；检查最终 `Kernel.lean ≤ 256000 bytes`。
6. 完整验证 NaN payload、Inf、signed zero 和 raw；给出目标机器上的真实性能测量。本文没有这些测量。

数值实值桥、非零编码单射及基准结构已由固定一手源码确认；核心 binade 和块证书工作仍是明确的开发缺口。


## 9. 补充：Lean v4.34.0 的 Float32 版本接口

本节直接读取 Lean 官方 `v4.34.0` 标签下的公开源文件；没有安装或执行这些文件。实际 wrapper 路径是 **`src/Init/Data/Float/Float32.lean`**。`src/Init/Data/Float32.lean` 在该标签返回 404，不能用这个不存在的路径作为来源。

| 精确声明 | v4.34.0 语义 | 官方固定版本来源 |
|---|---|---|
| `Float32.ofModel` / `Float32.toModel` | `Float32` structure 的构造器与投影；逻辑上包装 `Float32.Model`。源码没有为这里另写一个名为 `toModel_ofModel` 的 wrapper theorem；该结构互逆可由定义/结构消去证明。 | [Float32.lean:37–44](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Float/Float32.lean#L37-L44) |
| `Float32.ofBits` | `fun a => .ofModel <| Float32.Model.ofBits a`。 | [Float32.lean:132–133](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Float/Float32.lean#L132-L133) |
| `Float32.toBits` | `fun a => a.toModel.toBits`，结果 UInt32。 | [Float32.lean:145–146](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Float/Float32.lean#L145-L146) |
| `Float32.isFinite` | 定义为 `a.toModel.isFinite`；注释明确 normal、subnormal、zero 都为 true。 | [Float32.lean:260–266](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Float/Float32.lean#L260-L266) |
| `Float32.Model.isFinite` | 定义为 `a.unpack.isFinite`。 | [Model/Float32.lean:181–185](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Float/Model/Float32.lean#L181-L185) |
| `Float.Model.UnpackedFloat.isFinite` | `.notANumber` / `.infinity` 为 false；`.zero` / `.finite` 为 true。 | [Operations/Status.lean:20–24](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Float/Model/Unpacked/Operations/Status.lean#L20-L24) |
| `Float32.Model.ofBits` | `pack (UnpackedFloat.unpack Format.binary32 a.toBitVec)`；**源码明确：所有 NaN 输入规范化成 canonical NaN**。 | [Model/Float32.lean:198–204](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Float/Model/Float32.lean#L198-L204) |
| `Float.Model.Format.Valid` | 对 NaN 编码要求等于 `packedNaN spec`；不是“任意 UInt32 都保留原 NaN payload”。 | [Format/Valid.lean:19–25](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Float/Model/Format/Valid.lean#L19-L25) |
| `Float.Model.UnpackedFloat.valid_pack` | `spec.Valid (pack spec f)`。这是明确存在的 pack 有效性定理，不是任意 raw 字 round-trip。 | [Pack/Lemmas.lean:37–52](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Float/Model/Unpacked/Pack/Lemmas.lean#L37-L52) |

因此不能无前提声称 `Float32.toBits (Float32.ofBits w) = w` 覆盖任意 NaN payload。有限路径可使用已知基线的 native bridge；异常路径应保留原 FloatLib 值及原顺序语义。这里仅核对类型、分类和字转换，不重新展开或宣称发现基线 native add/mul 等式。

### 9.1 odd significand 排除 tie 的附加草稿

新增 `OddNoTieDraft.lean`（2,272 bytes，仅 `import ContractTensor`，**未编译**），给出完整证明草稿的纯自然数命题：

```lean
-- shift 是右移位数，即分母为 2^shift。
(n % 2 = 1) → (2 ≤ shift) →
  n % 2^shift ≠ 2^(shift-1)
```

同时给出等价的商余数判据形式：

```lean
(n % 2 = 1) → (2 ≤ shift) →
  2 * (n % 2^shift) ≠ 2^shift
```

证明核心：对任意 k，若 `n % (4*k) = 2*k`，由 `Nat.mod_add_div` 得 n 是 2 的倍数，矛盾；之后代入 `k=2^(shift-2)`。这避免依赖未核对的 mod-of-divisibility 定理名字，也没有 FloatLib 舍入假设。

`shift≥2` 是必要限制：`shift=1` 时任意 odd significand 的余数都为 1，恰等于分母 2 的一半。因此此引理只能消除至少右移两位的 tie 分支；one-bit tie 必须继续保留 parity 转移。它本身没有证明完整固定 binade 快路。
