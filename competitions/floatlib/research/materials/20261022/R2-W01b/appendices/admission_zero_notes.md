# R2-W01b：准入与零分支候选

## 状态

**NOT_RUN**。当前环境的 PATH 中没有 `lean` 或 `lake`。`AdmissionZero.lean` 是源码核对后的候选，不是已经编译通过的证明；未执行 elaboration、内核检查或依赖审计。`AuditAdmissionZero.lean` 单独放置诊断命令，不是提交候选。

只使用本轮消息、固定公共源码和新造边界例子。源码位于本轮新建的 `../sources`；未读任何旧项目目录、旧附件或旧会话。

固定版本：

- Lean `v4.34.0`，解析到 commit `293d5d0c0c3f3dded4688b3ccd6a33939ac5102b`。
- FloatLib `0d91825727839f597fd06b22fdd038ea21480f0c`。
- 官方 kernels `978cc5b445edb9943fd9953b0a9037d97a9f33a8`。

## 结论与边界

令 `a = u & 0x7fffffff`。32 位无符号回卷下，

`(a - 1 >= 0x0bffffff) && (a < 0x7f800000)`

精确对应 `a = 0` 或 `0x0c000000 <= a < 0x7f800000`。零时减一得到 `0xffffffff`；非零时减一不回卷，故不等式下界变成 `0x0c000000`。`0x0bffffff` 被拒绝，`0x0c000000` 被接受；`0x7f7fffff` 被接受，`0x7f800000` 被拒绝。

候选先证明任意 `UInt32 a` 的一般回卷等价式，再代入 `magnitude u`。证明把 `UInt32.toNat_sub` 展开成 `% 2^32`，用 `a.toNat < 2^32` 和 `omega` 完成。它没有把机器减法换成饱和自然数减法。

两个零的路径保持一致：

| `u` | `a` | `j = u >>> 23` | `M` | scale 位 | 结果位 |
|---|---:|---:|---:|---|---|
| `0x00000000` | 0 | 0 | `0x00800000 = 2^23` | `0x00000000` | `0x00000000` |
| `0x80000000` | 0 | 256 | `0x00800000 = 2^23` | `0x80000000` | `0x80000000` |

`scaleTable` 是闭合的 `Array Float32`，用 `Array.ofFn` 建立 512 项。`scaleTable_size` 与 `scaleTable_entry` 给出长度和每项公式；`tableIndex_toNat_lt` 证明全部输入都访问范围内的项。`scaleAt_eq` 将实际数组读取关联到公式。它没有把查表改成每次调用公式重算。

`convert_zero_path` 明确说明零也走 `tableProduct`，其定义仍是 `M.toFloat32 * scaleAt u`。`foldl_convert_eq` 对同一完整列表、同一左折叠顺序逐元素替换转换，不过滤零、不跳过零、不重排元素。

## 本候选覆盖的证明接口

1. `wrap_gate_iff` / `fastOK_iff`：完整精确准入条件。
2. `magnitude_zero_iff`：掩去符号后为零，当且仅当 `u` 是正零或负零编码。
3. `zero_fields`：两个零各自的 `j`、`M` 和 scale 位。
4. `zero_mantissa_conversion`：`UInt32 2^23` 转成 `Float32.ofBits 0x4b000000`。
5. `tableProduct_positive_zero` / `tableProduct_negative_zero`：首先陈述 `Float32` 的命题相等；随后通过 `congrArg Float32.toBits` 得到位等价。
6. `tableProduct_zero_bits`：零输入的原始编码精确保留。
7. `convert_fallback`：未准入输入沿用 `Float32.ofBits u`，不要求 normal 前提。
8. `convert_eq` / `convert_bits_eq` / `foldl_convert_eq`：在下述**明确未证明的 normal 前提**下组合得到完整转换及逐元素左折叠等价。
9. `float32_eq_of_toBits_eq`：展开 `Float32` 与 `Float32.Model` 两层结构，由位相等恢复命题相等。这里不使用浮点 `BEq`。
10. `normal_value_of_bits` / `convert_eq_of_normal_bits`：可直接接收 normal 证明提供的 `(tableProduct u).toBits = (Float32.ofBits u).toBits`。
11. `normal_value_of_raw_bits` / `convert_eq_of_normal_raw_bits`：可直接接收 `(tableProduct u).toBits = u`。候选用已核实的 `toFloat32_ofFloat32` 推出所有 native 值的 `Float32.ofBits x.toBits = x`，再用给定的原始位等式重写。这个前提本身保证 `u` 来自合法 native 值，因此不需再假设一般原始编码的往返性质。
12. `replace_decoder`：通过 `funext` 和 `congrArg` 将转换相等搬到任意纯上下文 `core : (UInt32 → Float32) → α`，可用来保留外层结构与 payload 回退。

```lean
hNormal : ∀ u, NormalBand u → tableProduct u = Float32.ofBits u
```

本轮不重复证明 normal 乘法数学。上述三个组合定理的结论仍依赖 `hNormal`；它们不能被写成无前提完成态。

`convert_bits_eq` 的右边特意是 `(Float32.ofBits u).toBits`，不是任意 `u`。Lean 对 NaN 的逻辑模型会规范化编码；不能据此宣称所有原始 NaN payload 被 native 转换保留。算法级 payload 回退是独立层，必须保留。这个候选只给转换替换定理，没有实现或替代那一层，也没有完成 `Competition.SumObligation`。

## 公开源码核对

以下均使用固定源码；行号指对应 commit 下的文件。

| API / 事实 | 固定公开来源 |
|---|---|
| 仅依赖 `ContractTensor`；它导入 `Contract`，后者导入 `FloatLib` | [ContractTensor.lean](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/contract/ContractTensor.lean#L1)、[Contract.lean](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/contract/Contract.lean#L1) |
| `UInt32.toNat_sub`、`toNat_lt_size`、`toNat_inj`、`ofNat_toNat` | [UInt/Lemmas.lean](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Data/UInt/Lemmas.lean#L139)：139、149、168、194 行模板，250 行为 UInt32 生成 |
| `UInt32.toNat_and`、`UInt32.toNat_shiftRight` | [UInt/Bitwise.lean](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Data/UInt/Bitwise.lean#L37)：37、41 行模板，53 行为 UInt32 生成 |
| 掩码 `(2^n)-1` 等价于 `% 2^n` | [Nat/Bitwise/Lemmas.lean](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Data/Nat/Bitwise/Lemmas.lean#L537)：`Nat.and_two_pow_sub_one_eq_mod` |
| 移位除以二次幂 | [BitVec/Lemmas.lean](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Data/BitVec/Lemmas.lean#L2119) 直接使用 `Nat.shiftRight_eq_div_pow` |
| `Array.ofFn`、长度和逐项读取 | [Array/Basic.lean](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Data/Array/Basic.lean#L331)；[Array/Lemmas.lean](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Data/Array/Lemmas.lean#L4254)：4254 行 `size_ofFn`，4282 行 `getElem_ofFn` |
| `Float32` 是包装逻辑模型的结构，具有命题相等的决定过程 | [Float32.lean](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Data/Float/Float32.lean#L37)：37–47 行 |
| `Float32.mul`、`ofBits`、`toBits`、`UInt32.toFloat32` 有透明逻辑定义 | [Float32.lean](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Data/Float/Float32.lean#L90)：90、132、145、303 行；[Model/Float32.lean](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Data/Float/Model/Float32.lean#L86) |
| `ofBits` 的逻辑模型规范化 NaN | [Model/Float32.lean](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Data/Float/Model/Float32.lean#L199) |
| 每个已经构造的 native 值可以精确往返，供 raw 位接口适配 | [Native/Representation.lean](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/IEEE754/Native/Representation.lean#L48) 的 `ExecFloat.Binary.toFloat32_ofFloat32`；[Native.lean](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/IEEE754/Native.lean#L131) 的 `toFloat32` 与 `toBits32_ofFloat32` |
| 默认 `decide` 生成可由内核复查的证明项，默认没有启用 native 分支 | [Init/Tactics.lean](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Tactics.lean#L1384)；[Lean/Elab/Tactic/Decide.lean](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Lean/Elab/Tactic/Decide.lean#L81) 的默认 `doElab` 分支使用 `mkDecideProof`、`whnf` 并返回证明项 |
| `omega` 返回证明项并交给内核检查 | [Omega/Frontend.lean](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Lean/Elab/Tactic/Omega/Frontend.lean#L649)：649–675 行取得 `proveFalse?` 的证明并赋值，694–696 行保存辅助定理 |
| 普通 `bv_decide` 不可直接当作本任务允许的纯内核路线 | [Lean/Elab/Tactic/BVDecide.lean](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Lean/Elab/Tactic/BVDecide.lean#L65)：65–67 行说明其编译反射信任增加；候选已完全移除它 |
| 依赖白名单和文件全文词法过滤 | [gate.py](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/gate.py#L191)：191 行白名单，205–210 行禁词，492–518 行 policy |

`UInt`、`Nat.Bitwise`、`Array.Lemmas` 均由默认 `Init` 的公开导入链可达；`omega` 还由 `FloatLib.Numerics.Automation.Numerics` 的公开 meta 导入到达。这里的“可达”是源文件导入链核对，不是实际 elaboration 验证。

raw 位接口的适配不使用 `∀ u, (Float32.ofBits u).toBits = u`。它只使用 `∀ x : Float32, Float32.ofBits x.toBits = x`：前者对带非规范 NaN payload 的原始编码错误，后者由模型有效性与已有公开往返定理成立。候选仍保留 `hNormalRawBits` 作为未完成 normal 证明的明确前提。

## 已做与未做的验证

- 已做：固定官方 `BANNED` 正则对候选全文的词法扫描，未发现匹配；候选只出现一条 `import ContractTensor`。
- 已做：自造 Python 边界诊断，两种符号下检查零、最小非零、subnormal/normal 分界、下界相邻点、最大有限值、无穷及 NaN 区间相邻点，均与目标准入集合一致。
- 已做：Python 格式化后的两个闭合零乘法诊断均得到对应符号的零位模式。这只验证自造例子，不能替代 Lean 证明，也不是 Lean native 运行结果。
- 未做：Lean 编译、内核检查、依赖清单、normal 引理、完整 sum kernel 义务、native codegen、运行时每次查表/闭合值获取成本测量。

顶层闭合数组是否被具体 C 输出提升，以及读取它时是否仍有一次性初始化检查，应由实际 Lean codegen 确认；不能仅从 `Array.ofFn` 的源码形式宣称运行时开销为零。

## 有工具链时的诊断顺序

在固定官方 Lean 项目与依赖完整可用、模块目录已正确加入搜索路径后，先生成 `AdmissionZero.olean`，再运行 `AuditAdmissionZero.lean`。例如在候选所在目录、且固定项目环境已配置时：

```sh
lake env lean -o AdmissionZero.olean AdmissionZero.lean
lake env lean AuditAdmissionZero.lean
```

第一步未成功前不应运行第二步并把旧 `.olean` 当成本轮结果。最后逐项核对实际输出依赖属于 `propext`、`Classical.choice`、`Quot.sound`；当前没有这份实际输出。
