# FloatLib R2-W03b：有符号常量表转换的全输入等式证明草稿

## 1. 结论与开发决策

本轮交付了完整的 `fromBitsTable` 全输入等式证明草稿。候选文件 `ConversionCandidate.lean` 中的最终声明是：

```lean
theorem fromBitsTable_all :
    ∀ u : UInt32, fromBitsTable u = Float32.ofBits u :=
  fromBitsTable_eq_ofBits
```

这次不再把目标定义为一个待满足的 proposition。单文件内已经写出位域展开、整数转换、scale 解码、精确乘法、实际 `Array.ofFn` 查找及三个控制流分支的全部证明体。最终定理没有 table、scale、输入分布或有限性等额外参数，也没有遗留待用户提供的数学前提。

**验证状态仍是 `NOT_RUN`。** 本环境没有 `lean`/`lake`，没有安装工具链，因而没有 Lean elaborator、kernel、依赖公理检查或官方 gate 的通过证据。这里的“完整”指声明与证明正文已经写齐、经固定公开源码和独立静态审查；不把它写成“已编译证明”。

这改变了下一步的优先级：可以把这一机制从“先找数学桥”推进到“在已有固定环境编译这一份具体草稿”。若编译及依赖检查成功，再把转换替换接入用户已通过 gate 的 finite 有序起点，运行原来的官方流程。暂时没有理由以未解决的数学命题否决它；也没有新的性能证据可以宣布它胜出。

现有 finite 路径已经通过官方 gate 这一基线状态，采自用户本次说明；本轮没有重新验证该 kernel。

| 项目 | 本轮状态 |
|---|---|
| 全输入主定理的证明正文 | 已写完整，`WRITTEN_NOT_RUN` |
| 尚未写出的数学子命题 | 当前草稿中无 |
| Lean 编译、名字解析、tactic 执行 | `NOT_RUN` |
| `#print axioms` 实际输出及允许集合检查 | `NOT_RUN` |
| 官方 policy / statement / kernel / bench | `NOT_RUN` |
| 有限文本检查 | 已运行；只检查文本、字节数、导入和选定禁用形式 |
| 新 C 或 Lean 性能实验 | 未运行 |
| 上一轮 ZIP | 保留原件，未改写 |

交付候选为 UTF-8，**18,558 bytes、464 行、34 个定理**，只含一行 `import ContractTensor`。它是可并入现有 `Kernel.lean` 的转换定义与证明片段，没有伪造当前完整 sum/bmm kernel 或它的 gate 结果。合并后的总文件仍须满足 256,000 bytes 限制。

## 2. 固定目标与边界

固定版本为 Lean `v4.34.0`、FloatLib `0d91825727839f597fd06b22fdd038ea21480f0c`、官方工程 `978cc5b445edb9943fd9953b0a9037d97a9f33a8`。导出链来自 `ContractTensor → Contract → FloatLib`；本候选没有新增直接导入，也没有改任何依赖、编译选项或官方文件。[S12] [S14]

可执行定义沿用原来的表布局和守卫，名称移入 `R2W03b` 以免与其他工作冲突：

```lean
def zero32 : Float32 := Float32.ofBits 0x00000000

@[inline] def exponent (u : UInt32) : UInt32 := (u >>> 23) &&& 255

@[inline] def mantissa (u : UInt32) : UInt32 :=
  (u &&& 0x007fffff) ||| 0x00800000

def signedScaleTable : Array Float32 :=
  Array.ofFn fun (i : Fin 512) =>
    let j := UInt32.ofNat i.val
    let e := j &&& 255
    let s := (j &&& 256) <<< 23
    let b := if 24 <= e ∧ e <= 254 then s ||| ((e - 23) <<< 23) else s
    Float32.ofBits b

@[inline] def fromBitsTableWith
    (table : @& Array Float32) (z : Float32) (u : UInt32) : Float32 :=
  if u == 0 then z
  else
    let e := exponent u
    if 24 <= e ∧ e <= 254 then
      (mantissa u).toFloat32 * table.getD (u >>> 23).toNat z
    else Float32.ofBits u

@[inline] def fromBitsTable (u : UInt32) : Float32 :=
  fromBitsTableWith signedScaleTable zero32 u
```

`fromBitsTableWith` 仍是便于调用方绑定表与零常量的实现辅助函数。**本报告不声称它对任意传入 table/z 正确。** 最终等式只针对具体 `signedScaleTable` 和精确 `zero32`。中间乘法引理中的 `hscale` 与 `hraw` 是明确的结构等式，并已在 `reconstruct_normal` 中用本文件的证明逐一满足。

两个反例说明这个区别是必要的。若将 `z` 换成 1.0，raw `u=0` 会直接返回 1.0；若将表换成全零数组而保持正确 z，`u=0x3f800000` 的 E=127 命中快路，却返回零而不是 1.0。这些反例仅用于划定定理范围，未作为全输入证明的替代品。

目标等式采用 Lean 的结构相等 `=`，没有用 IEEE 的浮点 `==`。对 NaN，右侧本来就是会规范化 NaN 的 native `Float32.ofBits`。我们证明的是替换旧 converter 保持其结果，**没有**声明 `(fromBitsTable u).toBits = u` 对 NaN payload 成立。用户现有 kernel 的 raw-FloatLib 回退与 finite admission 仍负责原始合同。[S1] [S2] [S8]

## 3. 位域、符号与整数 M 的闭合

令 `N=u.toNat`。证明首先把 UInt32 运算化为自然数中的常数除法、取模与加法：

\[
E=(N\mathbin{/}2^{23})\bmod 256,
\qquad F=N\bmod2^{23},
\qquad M=F+2^{23}.
\]

对应代码声明是 `exponent_toNat`、`mantissa_toNat`。所以对每一个 UInt32 word，都有

\[
2^{23}\le M<2^{24},\qquad M\ne0,\qquad \operatorname{log2}(M)=23.
\]

`mantissa_log2` 使用固定版本公开的 `Nat.log2_eq_iff`，其前提就是 `M≠0`，结论的两个范围条件由上述余数界给出。没有枚举 fraction、符号或输入集合。[S10] [S11]

符号定义采用模型原有的一位解码：

```lean
def rawSign (u : UInt32) : Sign :=
  Sign.ofBitVec (unpackSign (spec := f32Spec) u.toBitVec)
```

`unpackSign_toNat` 将这个一位向量解释为 `N / 2^31`，其值由 UInt32 范围限制为 0 或 1。这样正负号都沿同一个公开解码定义传递，无需额外假设，也无需通过浮点取负或 signed-integer cast 再建一条桥。[S3] [S10]

在守卫 `24≤E≤254` 下，`raw_unpack_normal` 排除模型 unpack 中的指数全零和全一分支，然后证明

\[
\operatorname{unpack}(u)
=\operatorname{finite}(s,M,e),\qquad e=\operatorname{Int}(E)-150.
\]

这里 `e∈[-126,104]`。`fullMantissa_toNat` 专门连接模型 normal 分支中的 `1#1 ++ fraction` 与候选构造的 UInt32 `mantissa`。有限构造携带的正性证明通过 proof irrelevance 匹配，未加入额外数据字段语义。[S3] [S4]

## 4. signed scale 的正规位展开

证明中使用一个辅助编码函数；可执行表本身没有改写为别的布局：

```lean
def scaleWord (u : UInt32) : UInt32 :=
  (((u >>> 23) &&& 256) <<< 23) ||| ((exponent u - 23) <<< 23)
```

守卫使 `E-23∈[1,231]`。因此 UInt32 减法不回绕，指数左移后低 23 位全零，指数部分不占符号位。`scaleWord_toNat` 的完整结果为：

\[
\operatorname{Nat}(\text{scaleWord}(u))
=\lfloor N/2^{31}\rfloor\,2^{31}
 +(E-23)2^{23}.
\]

`scale_unpack_fields` 分别证明 scale 保留原来的 sign、biased exponent 是 `E-23`、fraction 为零。结合模型 unpack 后得到

\[
\operatorname{unpack}(\text{scaleWord}(u))
=\operatorname{finite}(s,2^{23},e-23).
\]

也就是带原符号的精确数值 `2^e`。对整个快路，scale 的 unpacked exponent 是 `[-149,81]`，biased exponent 是 `[1,231]`，始终为 normal。E=24 对应最小正/负 normal scale `±2^-126`；E=254 对应 `±2^104`。

native `Float32.ofBits` 在逻辑层是先 unpack 再 pack。这里没有把它偷换成 raw bits 的恒等函数，而是调用固定 FloatLib 的公开定理

```lean
unpack spec (pack spec (unpack spec bits)) = unpack spec bits
```

本地封装为 `ofBits_unpack`，再导出 `scale_unpack_normal`。该公开定理对任意 bits 成立，因此也正确处理 canonicalization；在本轮正常 scale 上自然得到所需 finite 结构。[S2] [S8]

## 5. UInt32 整数转换为什么精确

Lean v4.34.0 的 `UInt32.toFloat32` 具有可展开的逻辑定义，经 `Float32.Model.ofUInt32`、`UnpackedFloat.ofUInt32` 归到 `UnpackedFloat.ofNat binary32 n.toNat`。候选直接沿这条链证明，没有使用 `Float32.toFloat` 或 `Float.toFloat32`。[S1] [S2]

局部 `ofNat_eq_round` 将非零自然数转换化为 `round spec .positive m 0`。`round_normalized24` 对任意符号证明：如果 `m.log2=23` 且 `-149≤e`，则目标指数已是 e，舍入结果精确为 `.finite s m e`。这条引理是 unpacked 层结论；不能仅凭它忽略后续 pack 的溢出条件。

整数 M 的场景取 e=0。`unpack_pack_normal24` 再用公开 `unpack_pack_finite_normal` 完成 pack/unpack 往返。它显式证明全部条件：

1. `m.log2+1=24`；
2. `0≤e+127+23`；
3. `0<e+127+23`；
4. `(e+127+23).toNat+1<256`。

该封装取 `-149≤e≤104`，正好覆盖 normal 的 biased exponent 1..254。整数转换使用的 e=0 严格落在范围中。因此得到完整结构等式：

```lean
theorem uint32_unpack_exact24 (n : UInt32)
    (hn : n.toNat ≠ 0) (hlog : n.toNat.log2 = 23) :
    n.toFloat32.toModel.unpack =
      .finite .positive n.toNat 0 (Nat.pos_of_ne_zero hn)
```

这里的两个条件在最终目标里分别由 `mantissa_ne_zero u` 和 `mantissa_log2 u` 满足。此处没有声称所有 UInt32 的数值转换都精确。[S5] [S7]

## 6. 乘法与舍入桥：前提已显式证明

两个 unpacked 操作数是

\[
(+,M,0),\qquad(s,2^{23},e-23).
\]

固定 Lean finite×finite 乘法先形成精确整数乘积和指数和，再调用 `roundWithAccuracy ... .exact`。[S15] 因此本例的原始乘积为

\[
P=M2^{23}=M\ll23,\qquad q=e-23.
\]

由 M 的 log2=23，`log2(P)=46`。固定模型的 `totalExponent` 是 `log2(P)+1+q`，所以

\[
\operatorname{totalExponent}(P,q)=47+(e-23)=e+24,
\]

\[
\operatorname{targetExponent}(P,q)
=\max((e+24)-24,-149)
=e.
\]

最后一步使用已证明的 `e≥-126≥-149`。[S4] [S6]

固定 FloatLib 定理 `roundWithAccuracy_exact_eq_round_of_le_targetExponent` 的前提，逐字是：

```lean
exponent ≤ spec.targetExponent (Float.Model.totalExponent mantissa exponent)
```

条件方向是输入指数不大于目标指数。本候选的 `mul_normal_scale_target` 先证明 target=e，随后显式构造

\[
q=e-23\le e=\operatorname{targetExponent}(P,q).
\]

代码把这个证明传入该定理，才将 `roundWithAccuracy ... .exact` 改写为 `round`。再用公开 `round_shiftLeft`：

\[
\operatorname{round}(s,M\ll23,e-23)
=\operatorname{round}(s,M,e)
=\operatorname{finite}(s,M,e).
\]

符号一步通过 `Sign.positive * s = s` 完成。两种符号均适用，且不会产生独立的额外取负舍入步骤。[S5] [S6]

### 为什么不能省略桥前提

取 binary32、正号、mantissa=1、exponent=0。此时目标指数为 −23，输入指数 0 不满足 `0≤−23`。固定定义中 `roundWithAccuracy ... .exact` 不做所需的左正规化，保持 unpacked `(1,0)`；`round` 则先左移得到 `(2^23,-23)`。它们实数值相同，但 `UnpackedFloat` 构造不同。`.exact` 只说明尾数精度信息，并不足以保证两种 round 接口结构相等。这是从固定定义得到的反例推导；没有把它包装成已经运行的 Lean 检查。[S4] [S4R] [S6]

本候选的乘积满足正确方向的不等式，因而没有落入这个反例。最终的 native bridge 对两侧相同 finite 结构应用 `Float32.Model.pack`，再由 `Float32.toModel` 的结构单射性得到 native `Float32` 相等。没有另设 pack 结果为原 word 的未证前提。

## 7. 真实常量表查找与全输入合成

索引是 `(u>>>23).toNat`，包含 sign 和 biased exponent 共九位。`table_index_lt` 从 `N<2^32` 证明

\[
\lfloor N/2^{23}\rfloor<512.
\]

因此 `getD` 在这一张具体表上不会取默认值。证明使用固定 Array API：先以 `Array.getD_eq_getD_getElem?` 转成 option 读取，再以 `Array.getElem?_ofFn` 展开 `Array.ofFn` 的对应项；在界内消掉 dependent if，用 `UInt32.ofNat_toNat` 还原 j，最后用输入守卫消掉表项自己的 guard。[S9]

得到的是下述完整定理，不是一个用户必须额外满足的 table 假设：

```lean
theorem signedScaleTable_lookup (u : UInt32)
    (hlo : (24 : UInt32) ≤ exponent u)
    (hhi : exponent u ≤ (254 : UInt32)) :
    signedScaleTable.getD (u >>> 23).toNat zero32 =
      Float32.ofBits (scaleWord u)
```

`reconstruct_normal` 随后一次性满足 native 乘法桥所需的非零、log2、指数下界、scale unpack 与 raw unpack。全输入主定理只有三条控制流分支：

```lean
theorem fromBitsTable_eq_ofBits (u : UInt32) :
    fromBitsTable u = Float32.ofBits u := by
  by_cases hz : u = 0
  · subst u
    rfl
  · by_cases hg : (24 : UInt32) ≤ exponent u ∧ exponent u ≤ (254 : UInt32)
    · simp only [fromBitsTable, fromBitsTableWith, beq_iff_eq, hz, if_false,
        hg, if_true]
      rw [signedScaleTable_lookup u hg.1 hg.2]
      exact reconstruct_normal u hg.1 hg.2
    · simp [fromBitsTable, fromBitsTableWith, hz, hg]
```

还有函数形式 `fromBitsTable_eq : fromBitsTable = Float32.ofBits`，可用于现有 proof 的上下文替换。独立诊断文件同时包含一个 `congrArg Float32.toBits` 的推论，右侧仍为 `ofBits u` 的 bits，没有错误地扩大为 raw payload 恒等式。

## 8. 全域覆盖与合同保持

| 原始输入类 | 行为 | 等式证明方式 |
|---|---|---|
| raw `0x00000000` | 返回精确 zero32 | 定义相等 |
| raw `0x80000000`，负零 | 原 `Float32.ofBits` | 非 +0，E=0 不满足守卫 |
| E=0、fraction 非零，任意符号 subnormal | 原 `Float32.ofBits` | E 下界不满足 |
| E=1..23 的 normal | 原 `Float32.ofBits` | E 下界不满足 |
| E=24..254 的 normal，任意符号、任意 fraction | M 的整数转换 × 带符号常量表项 | 全称重构证明 |
| E=255、fraction=0，正负 Inf | 原 `Float32.ofBits` | E 上界不满足 |
| E=255、fraction 非零，所有 NaN word | 原 `Float32.ofBits` | E 上界不满足，继承原规范化行为 |

这里“最小支持域”要分清：**定理域是所有 UInt32；数值重构域固定为 E=24..254。** 本轮没有扩大到 E=1..23，也没有在 subnormal 上错误添加隐含位。raw +0 快捷返回是独立的一条精确分支。负零从未被转换成正零。

最大有限 normal 对应 E=254、M=2^24−1、e=104。模型 pack 的偏置指数为 254，严格溢出条件检查是 `254+1<256`，成立；E=255 在进入重构前就被排除。不存在“上界差一位”让 Inf 混入快路的问题。[S7]

对 sum/bmm 的接入不要求重排任何运算。若每个旧转换 `Float32.ofBits u` 用本定理等值替换，则原来的从 +0 按索引 RN32 加法序列、以及每个 k 先 RN32 mul 再 RN32 add 的序列保持。既没有合并乘加，也没有改变求和顺序。此处只是上下文相等的应用，不是新的 ordered-sum 或 bmm 布局研究。正式合同仍是固定 `ContractTensor` 中的定义。[S12]

## 9. 许可、声明依赖与证明技术

只局部移植了 FloatLib `Native/Integer/Constructors.lean` 中两项 private 辅助证明：

| 本地声明 | 原源码声明 | 使用方式 |
|---|---|---|
| `round_at_target` | `round_eq_finite_of_targetExponent` | 复制证明并局部改名，使用当前参数名 |
| `ofNat_eq_round` | `ofNat_eq_round` | 复制非零整数归约证明 |

它们的原始归属为 Copyright (c) 2026 FloatLib，FloatLib Team，MIT。候选文件头部内嵌完整 MIT 文本，因此作为单文件合并时也保留许可；包中另附 `LICENSES/FloatLib-LICENSE`。没有把 private 名称伪装成可直接引用的公共 API。[S5]

其余关键调用是公开声明：`round_shiftLeft`、`unpack_pack_finite_normal`、`roundWithAccuracy_exact_eq_round_of_le_targetExponent`、`unpack_pack_unpack`，以及 UInt32/Nat/BitVec/Array 的公开引理。`sources/ProofDependencies.md` 给出分层依赖表，`sources/declarations.json` 列出全部 34 项本地定理，`sources/source_manifest.json` 给出所核对公开文件的固定 URL、字节数与 SHA256。

位运算通过 Nat 的常数除法、常数取模和线性等式完成；使用 `omega` 处理范围与线性整数算术，未使用遍历 2^32 输入的证明方法。少量 `by decide` 仅证明诸如 `0<2^23` 或固定指数界这样的闭合常数命题，未用有限样例替代全称结论。

最终实际依赖的公理集合需要固定环境中运行诊断后确认，本轮没有推断一个假的 `#print axioms` 输出。目标允许集仍只有 `propext`、`Classical.choice`、`Quot.sound`。候选没有新增公理、证明洞或 native-decide 形式。

## 10. 候选与诊断的分离、编译说明

`ConversionCandidate.lean` 是候选主体；`diagnostics/Diagnostics.lean` 仅存放追加式诊断命令。后者包含 `#check`、`#print axioms` 和从主定理导出的全称/上下文推论，**不可**并入提交文件。固定官方 policy 对整份文本匹配禁止名称，也检查注释中的独立 `import` 单词，因此候选注释没有讨论禁止词或放入诊断指令。[S13]

`tools/check_candidate_text.py` 是本次编写的有限文本检查器；其运行结果在 `text-check.json`。它不能验证 Lean elaboration、证明依赖、kernel、官方 statement 或性能阶段，也不代表已运行官方 policy。没有把该脚本输出命名为 gate PASS。

在已配置好的固定官方环境中，可从解压目录运行：

```bash
python3 tools/run_fixed_diagnostics.py /absolute/path/to/pinned-project/lean --output /absolute/path/to/new/w03b-logs
```

该脚本只使用已有工具，检查固定 toolchain；若检测到 elan，会先确认该工具链已安装。它在临时目录分别写出候选及“候选 + 诊断”的合并文件，调用现有 `lake env lean`，不改项目源码、编译选项或 bench。失败时保留第一份 Lean 日志，不改选项反复尝试。它不替用户证明现有 checkout 的 FloatLib/官方 commit 身份，也不执行官方 gate；这些仍使用已有固定环境的流程。

本地实际执行时，脚本在 `lake` 缺失处停止，`verification/compile-status.json` 记录的是 `NOT_RUN`，不是 Lean 编译失败。由于没有 Lean 错误日志，也就没有一个可诚实声称的“实测首个失败目标”。可能的 elaboration、simp、tactic 资源或可见性问题只能由这次固定编译确定。

静态审查已主动收紧几处常见风险：对 overloaded `ofNat/ofInt/round/unpack` 在 simp 列表中使用全限定名；在二次幂 OR 引理中显式指定位宽 23；对含正性证明的 finite 构造用 simp；去掉可能在 `rw` 已闭合后继续执行的多余 `rfl`。这些是源码级修正，不是虚构的编译修复记录。

## 11. 与 R2-W03 原包的变化

| 原版 | R2-W03b |
|---|---|
| 多种转换机制与有限诊断 | 仅保留 signedScaleTable 这一目标 |
| `ConversionObligation` 只是待证命题定义 | 写出 `fromBitsTable_eq_ofBits`、全称形式和函数相等 |
| `round_at_target/round_normalized24/round_shifted24` 等组件 | 保留适用思想，增加字段、cast、scale、mul、lookup 的整条连接 |
| 表 lookup 与全输入 wrapper 还未闭合 | 实际 Array.ofFn 值及默认分支已写出证明 |
| 诊断命令与候选定义混放 | 候选和诊断单独文件 |
| 候选注释触发官方禁止词 | 候选保留许可且避免这些词；检查结果单独保存 |
| C surrogate 性能 | 本轮不复测、不新增速度数字 |

上一 ZIP 仍为原来的 `FloatLib-R2-W03.zip`，其 SHA256 在 `CHANGELOG.md` 中保留用于身份核对。新 ZIP 使用独立 R2-W03b 名称。

## 12. 性能判断与下一步的最小决策

此次证明没有改变热路径的操作集合。仍包括 raw +0 检查、指数提取与上下界检查、九位索引形成、表读取、M 的整数转 Float32 和一次 native 乘法。表仍是合法纯 `Array.ofFn` 常量，表构造与 native 表项的初始化成本没有被证明文字消除。内联标记也仍然只是编译器请求，不能据此宣称一定生成某种机器码或一定向量化。

因此本轮的决策建议是：**推进一次固定环境编译；在编译与依赖检查通过后，接入真实起点作原样官方对照。** 在此之前保留原 ofBits converter 作为已通过 gate 的实现。若真实基准更慢，就拒绝这一转换替换，保留等价引理作为可复用资产；本轮没有另开 C 变体或修改数据布局来为它寻找胜利条件。

从证明角度，现在未发现需要改变数值合同、添加假设或引入 FFI 才能跨越的剩余命题。从性能角度，检查/查表/转换/乘法是否比原调用便宜，仍是实际 Lean 编译与既有官方 benchmark 才能回答的问题。

## 13. 主要一手来源

- [S1] Lean v4.34.0，`src/Init/Data/Float/Float32.lean`：native 类型与 UInt32 转换逻辑定义。
- [S2] 同 tag，`src/Init/Data/Float/Model/Float32.lean`：ofBits/ofUInt32/mul 的 pack/unpack 路径。
- [S3] 同 tag，`Model/Unpacked/Pack/Basic.lean`：normal 解码、隐含位和字段操作。
- [S4] 同 tag，`Model/Format/Basic.lean` 与 `Model/Unpacked/Round.lean`：total/target exponent 和两种 round 路径。
- [S5] 固定 FloatLib，`Native/Integer/Constructors.lean`：公开 shift 引理与两项 MIT 局部移植来源。
- [S6] 固定 FloatLib，`ModelRounding/Proof.lean`：精确舍入桥第 839–848 行。
- [S7] 固定 FloatLib，`Model/Packing/Finite.lean`：公开 normal pack/unpack 条件。
- [S8] 固定 FloatLib，`Native/Model/Representation.lean`：canonicalization 后 unpack 等式。
- [S9] Lean v4.34.0，`Init/Data/Array/Lemmas.lean`：Array.ofFn/getD lookup。
- [S10] 同 tag，`Init/Data/UInt/Bitwise.lean` 和 `UInt/Lemmas.lean`：位操作自然数语义与范围。
- [S11] 同 tag，`Init/Data/Nat/Lemmas.lean`：log2 区间刻画；相关 bitwise 声明见 source manifest。
- [S12] 固定官方工程，`lean/contract/ContractTensor.lean`：有序 sum/bmm 合同。
- [S13] 固定官方工程，`gate.py`：词法规则、导入限制和分阶段 gate。
- [S14] 固定官方工程，`lean/lakefile.lean`：环境与依赖配置。
- [S15] Lean v4.34.0，`Model/Unpacked/Operations/Mul.lean`：finite×finite 乘法的精确输入与舍入接口。

[S1]: https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Float/Float32.lean
[S2]: https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Float/Model/Float32.lean
[S3]: https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Float/Model/Unpacked/Pack/Basic.lean
[S4]: https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Float/Model/Format/Basic.lean
[S4R]: https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Float/Model/Unpacked/Round.lean
[S5]: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/IEEE754/Native/Integer/Constructors.lean
[S6]: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/ModelRounding/Proof.lean#L839-L848
[S7]: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Model/Packing/Finite.lean
[S8]: https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/IEEE754/Native/Model/Representation.lean
[S9]: https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Array/Lemmas.lean
[S10]: https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/UInt/Bitwise.lean
[S11]: https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Nat/Lemmas.lean#L1338
[S12]: https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/contract/ContractTensor.lean
[S13]: https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/gate.py
[S14]: https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/lakefile.lean
[S15]: https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Float/Model/Unpacked/Operations/Mul.lean
