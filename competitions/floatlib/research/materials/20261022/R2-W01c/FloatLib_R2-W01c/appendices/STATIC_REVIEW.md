# R2-W01c 片段交叉静态复核

复核对象为 `IntegerDyadic.lean`、`NativeProductBridge.lean` 和 `ModelExactProduct.lean`。这是公开定义和证明脚本的静态检查；没有 Lean 运行环境，所有新声明 **NOT_RUN**。以下结论不把复核者一致当成机器证明。

## IntegerDyadic

- `UInt32.toFloat32 n` 的 Lean 定义是 `Float32.ofModel (Float32.Model.ofUInt32 n)`。
- `Float32.Model.ofUInt32` 是 pack 一个 `UnpackedFloat.ofUInt32`。
- Lean v4.34.0 的 `UnpackedFloat.ofUInt32` 定义为 `ofNat spec n.toNat`，`ofNat` 再定义为 `ofInt spec (n : Int)`；因此 `uint32_model_eq_roundDyadic` 中两次 `change` 有真实定义链支持。
- 固定 `Model.ofFloat32Model_pack` 是 `rfl`，而 `Model.ofModel_ofInt_eq_roundDyadic` 的确接受所有 `n : Int`，唯一格式前提为 `fmt.isIEEE = true`。
- 固定 `roundDyadicWithRounding_toDyadic?` 包括 zero，整数桥不需要先证明 n 非零。normal specialization 后由范围证明正数。
- `fields32_toDyadic` 使用 `toDyadic?_ofFields_normal` 的四个域前提对应正确：指数非零、指数 `< 255`、fraction `< 2^23`，binary32 格式固定。`e − 127 − 23 = e − 150` 的 Int 算术无截断风险。
- `uint32_mantissa_model_eq_fields` 把 native 整数词指定为 sign=false、biased exponent=150、fraction=n−2^23。两个 n 边界恰保证 fraction 范围及加回 M，`omega` 仅需线性自然数算术。
- `simpa only [hsum]` 还要由定义等价化简闭常量指数 `(150:Int)−150` 和 Nat/Int numeral coercion。按固定定义这应是归约，而非未证数值事实；真正 elaboration 待执行。

## ModelExactProduct

- `toReal_eq` 的完整 RHS 是 `match toDyadic? x with | some d => d.toReal | none => 0`。`simp only [toReal_eq,hx,hy,hz]` 对已替换的 `some` match 进行 iota 归约，正是固定 Text/Representation 中同类证明已有使用的写法。
- `dyadic_scale_value` 展开到 `(↑M) · ((±↑(2^k)) · 2^e) = (±↑M) · 2^(e+(k:Int))`。
- `zpow_add₀ (by norm_num : (2:Real) ≠ 0)` 的命名和用法与固定 `Model.Dyadic.toReal_mul` 相同。simp 的标准 Nat→Int→Real cast、`zpow_natCast` 简化后，剩余为乘法交换结合及负号的环等式，`ring` 能承接该形式；未在本机检查实际 tactic elaboration。
- generic product 的 finite 输入、finite 目标、目标非零全部显式；结果 finite 是用目标幅值界推出来的，不是一个循环假设。
- 输出是 `Model.mul x y = z`，未在本文件声称 native value 或 raw UInt32 相等。

## NativeProductBridge

- `nativeModel_ofBits_of_decode` 通过 decoded finite→unpacked finite→canonical invariant→canonicalizeModel identity，显式关闭 ofBits 的 NaN 规范化差异；没有使用错误的全输入原始位 roundtrip。
- `change nativeModel (toFloat32 (ofBits32 u)) = rawModel u` 有定义级支持：固定 `toBits32_ofBits32` 证明为 `rfl`，`toFloat32` 定义为 `Float32.ofBits ∘ toBits32`。
- `nativeFinite_of_decode` 先用 `toDyadic?_ieee_eq_model`，再把 `Model.toModel (nativeModel x)` 化成 `x.toModel.unpack`，按 unpacked constructors 排除 NaN/Inf，桥接到 `x.isFinite`；这不依赖目标 word 位关系。
- 最终乘法提升先取得 `B.ofFloat32 (x*y) = B.ofBits32 u`，依据是 B.toModel 的注入性和已证明有限输入 native mul桥；再用 `congrArg B.toFloat32` 恢复 native value，或 `congrArg B.toBits32` 恢复 raw word。两条最终关系均具有明确完整表示证据。
- 提出一个防脆弱建议：`simpa only [toFloat32_ofFloat32,toFloat32,toBits32_ofBits32]` 同时给了 roundtrip rewrite 和展开 rewrite，可换三段显式 calc，先用 roundtrip 的对称，再 `congrArg`，最后 `rfl`，避免依赖相交 simp 规则选择顺序。这是稳健性建议，未确认该原写法会失败。已通知原作者处理，没有修改他人文件。

## 可见性与信任边界

- 固定 `IEEE754.lean` 公开导入 `Native.Integer`；后者公开导入 `Constructors`、`FromInt`、`ToInt`；这些均公开导入 `Integer.Rounding`。结合 ContractTensor 的既有 umbrella 导入，整数桥源码级可见。
- 固定 Text/Representation 的公开可见路径见 `ROUNDTRIP_AUDIT.md`。
- `norm_num`、`omega`、`ring`、常量格式的 `by decide` 在片段中没有引入新的声明级公理。实际声明公理集仍要在可运行 Lean 环境分别检查，不能从词法扫描推断。

## 当前复核结论

未发现上述三片段有数学上的反例、漏掉 finite/nonzero 前提，或把实数等式直接当 raw 相等的步骤。未声称它们已通过 Lean。本次缩短路径仍有实际价值：固定 pin 已含所需整数和表示桥，新代码集中于通用数学组合及具体字段 decode，不必移植较新证明文件。
