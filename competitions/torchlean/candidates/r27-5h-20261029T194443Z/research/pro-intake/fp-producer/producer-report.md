# LazyFPOnly 精确 binary32 dot：producer 数学研究

日期：2026-10-30（Asia/Shanghai）。范围：只研究附件末尾原创 helper 的 producer；不重证已接受的 orderKey / strict-midpoint consumer、getter 一致性或 UInt64 模块。

## 0. 可执行结论与证据等级

**现有 `+720` 半径正确，可以同表达式成本收紧为 `+719`；再缩为 `+718` 不正确。**

设 `1 ≤ n ≤ 2^30`，输入为任意有限 binary32，实际 widening 精确，乘法和原顺序左折使用 IEEE binary64 RN-even。令 `H` 为两侧 `maxIndex` 相加，`L=ceil(log2 n)`，则：

\[
|s_n-S_n|
\le 2^{H-303}\frac{n(n-1)}2
<2^{H+2L-304}
<2^{H+2L-303}.
\]

这包含次正规输入、任意符号、抵消、±0、`n=1` 和极端指数。每个乘积精确；累加及其精确加法输入均不发生 binary64 overflow，非零值也不进入 binary64 subnormal 区域。

建议首先证明现有执行顺序的 producer，半径处只做：

```lean
let r := Float.ofBits ((H + (L + L) + 719) <<< 52)
```

这是源级操作数量相同的常数修改，不是已经测得 native 指令数、耗时或整模型收益。无需新增 per-term 累加操作、补偿数组、分块或重排。

| 产物 / 结论 | 本次证据 | 不表示什么 |
|---|---|---|
| 全 finite 的 720 / 719 数学界 | 下文完整量词推导，两条交叉路线 | 未完成实际 native Float 定理实例化 |
| 718 不成立 | 原始 bit、精确整数 RN-even 脚本、独立尺度复核 | 未声称 consumer 在该输入错误接受 |
| 原创 Lean 小核心 | `LazyProducerCore.lean`；逐段静态复核 | **NOT_COMPILED** |
| FloatLib 接口 | 固定源码读取、真实声明与前提记录 | 仍需固定环境 `#check`、elaboration 与前提证明 |
| 有限数值检查 | 纯整数 / Fraction 模型已运行 | 不是全域证明、不是 native 测试 |
| 全 12 kernel / 性能 | 未开展 | **NOT_PROVED / NOT_RUN** |

附件中实际名字为 `Submission.R24PortableF64` 和 `R27FPOnly`，没有字面名为 `LazyFPOnly` 的 namespace。本报告用 LazyFPOnly 指用户指定的这条路线，不把名称差异当成另一份实现。

## 1. 被检查的实际材料

输入文件：`research-materials-r28(1).txt`，278657 bytes，SHA256：

`932da02eec02644a6e0b1fcfe56579143936eec3fcce38b8d8caa1c7eb74374c`

本次 producer 目标是末尾 `OWN_FP_COST_HELPER_NOT_PROVED`：6739 bytes，SHA256：

`1762a473178d3a45b431c94b995a2616fd4b939dd5b98d65f40ada71dfc2c892`

这两个长度 / hash 已核对。每段 END marker 前额外有一个容器分隔换行；按声明长度取内容后匹配段 hash。没有修改附件，也未在 zip 中重分发上游 Kernel。

`ContractExact` 的 dot 是精确乘积之和只舍入一次。`linear` 的 bias 是追加的 `(1,bias)` 项。helper 的 `linear` 确实对两侧使用 `prepareFn (k+1)`，因此这里的 `n` 必须是 `k+1`，两个 peak 也必须包括这最后一项。偏置不能在 producer 的计数或指数上界之外另加。

## 2. 量词、解码和乘积精确性

任取自然数 `n` 满足 `1≤n≤2^30`，以及两列原始 binary32 words `a_i,b_i`（`0≤i<n`），要求每个 word 的 raw exponent `e` 都不为 255。这个条件由现有 preparation 的真实 `valid` guard 建立；它不是加到最终 Kernel contract 上的新假设。

对一个有限 word，令符号为 `σ∈{−1,+1}`、fraction 为 `f`，定义：

\[
(m,I)=
\begin{cases}
(f,0), & e=0,\\
(2^{23}+f,e-1), & 1\le e\le254.
\end{cases}
\]

于是：

\[
x=\sigma m2^{I-149},\qquad
0\le m<2^{24},\quad 0\le I\le253.
\]

零的两个符号都对应实数 0；`widenBits` 保留其原始 sign bit。实数误差界本身不声称给出最终零的符号。

### 2.1 实际 widening 配方

对 normal32，helper 生成 binary64 的 biased exponent `e+896`，fraction `f<<29`，故值为：

\[
\left(1+\frac f{2^{23}}\right)2^{e-127}
=(2^{23}+f)2^{e-150}.
\]

对非零 subnormal32，令 `ell=floor(log2 f)`，则 `0≤ell≤22`。helper 的 biased exponent 是 `ell+874`，fraction 是 `(f−2^ell)<<(52−ell)`，故值恰好：

\[
\left(1+\frac{f-2^\ell}{2^\ell}\right)2^{\ell-149}
=f2^{-149}.
\]

因此包括最小 subnormal32 在内的所有非零有限输入，widen 后都是 **normal64**。最小值 `0x00000001` 对应 `0x36a0000000000000=2^-149`。零单独保留符号。exponent255 的分支必须使 `valid=false`，其临时缓存中 push 的 0 只是无效占位，不能拿来替代原 NaN/Inf 的语义。

### 2.2 每个 binary64 乘积精确

每个精确实数乘积可写为：

\[
t_i=a_ib_i=\sigma_i p_i2^{J_i-298},\qquad
p_i=m_{a_i}m_{b_i}<2^{48},\quad
J_i=I_{a_i}+I_{b_i}.
\]

设两侧 metadata 分别为 `A,B`，满足所有 `I_a≤A≤253`、`I_b≤B≤253`，令 `H=A+B`。则 `0≤J_i≤H≤506`。非零乘积满足：

\[
2^{-298}\le |t_i|<2^{256}.
\]

它只有至多 48 个有效二进制位，少于 binary64 的 53 位精度；其非零值域又完全处于 binary64 normal 范围。因此一次正确 RN64 乘法精确得到该乘积，既无 overflow，也无 underflow。零乘积保持实数值 0；零符号不是本误差结论的输出。

这个论证需要对应 native 乘法的正式连接，不能只靠一句“double 精度更高”替代。第 8 节明确列出了已有入口和剩余前提。

## 3. 关键不变量：可精确表示的 kM 上界

定义：

\[
u=2^{-53},\quad M=2^{H-250},\quad
L=\lceil\log_2 n\rceil,\quad N=2^L.
\]

于是 `0≤L≤30`、`n≤N≤2^30`，且每个乘积严格满足 `|t_i|<M`。令：

\[
s_0=0,\quad s_k=\operatorname{RN}_{64}(s_{k-1}+t_k),
\qquad S_k=\sum_{i=1}^{k}t_i.
\]

这里只把下标改成一基以便写公式；执行顺序仍是附件 `sumRemaining` 的左折，首项是 `+0+t_1`。

对每个整数 `0≤k≤N`，`kM` 是有限 binary64 可精确表示数：`k` 至多 31 位，而 `M` 是 2 的幂；非零端点范围从 `2^-250` 到 `2^286`，远离 double 的指数边界。

由 RN 的单调性及其固定可表示数，归纳得到：

\[
\boxed{|s_k|\le kM.}
\]

归纳步完整地是：

\[
|s_{k-1}+t_k|
\le |s_{k-1}|+|t_k|
<(k-1)M+M=kM;
\]

对两端 `±kM` 舍入不改变值，所以舍入后的 `s_k` 仍在这个闭区间内。舍入后的界允许等号；下一步利用 `|t|<M` 重新得到严格的 pre-round 界。

**这一步真正消除了误差导致的幅度增长。** 不能把常规 `(1+u)^k` 硬改成 1；这里是另一个经过证明的不变量。前缀和以及精确 pre-round 加法输入均不超过 `2^286`，所以无 double overflow。

## 4. 严格半径：两个短证明

### 4.1 最适合连接小 Lean 核心的统一网格证明

令 `U=NM=2^(H+L-250)`。在区间 `[−U,U]` 中，所有网格点：

\[
j\delta,\quad |j|\le2^{53},\qquad \delta=U2^{-53}
\]

都可用 binary64 精确表示。`|j|<2^53` 时有效位数不超过 53；端点 `|j|=2^53` 也是 2 的幂。最小网格步长至少 `2^-303`，最大端点至多 `2^286`，所以没有格式指数例外。

每个实数 `z∈[−U,U]` 距某个网格点至多 `δ/2`。真正的 RN64 选择整个可表示集合中的最近值，故：

\[
|\operatorname{RN}_{64}(z)-z|\le U2^{-54}=:C.
\]

该结论连 `z=0`、任意抵消后的小值都包含在内，不需要先建立相对误差前提。第一步 `RN64(0+t_1)=t_1` 精确，所以有且只有至多 `n−1` 个非零局部舍入误差：

\[
\begin{aligned}
|s_n-S_n|
&\le(n-1)C\\
&<NC\\
&=N^2M2^{-54}\\
&=\boxed{2^{H+2L-304}}.
\end{aligned}
\]

`n=1` 时第一行是 0，而 radius 为正，严格包含同样成立。

### 4.2 明确保留 n(n−1)/2 的逐步证明

对第 `k≥2` 步，令 `j=ceil(log2 k)`。由 `|z_k|<kM≤2^jM`，把上一节网格界用于更小的区间，得到：

\[
|\epsilon_k|\le M2^{j-54}=uM2^{j-1}.
\]

因为 `k` 是整数且 `2^(j−1)<k`，所以 `2^(j−1)≤k−1`。第一步误差为零。因此：

\[
\begin{aligned}
|s_n-S_n|
&\le\sum_{k=2}^{n}|\epsilon_k|\\
&\le uM\sum_{k=2}^{n}(k-1)\\
&=\boxed{uM\frac{n(n-1)}2}\\
&<uM\frac{N^2}{2}=r_{719}.
\end{aligned}
\]

这不是用错了标准相对误差公式；此处纯三角系数由精确端点不变量和绝对网格误差得到。下节的常规展开会多出 `n−1`，二者的来路不同。

若 `n=N=2^L`，保留每个 binade 的界还能得 `uM(N²−1)/3`，因为第 `j` 段有 `2^(j−1)` 项，每项系数 `2^(j−1)`。这不允许直接再除以 2；事实上 718 已有反例。

## 5. 不省略增长因子的独立交叉核对

先由第 6 节的格点闭包保证每个非零加法输入是 normal64，故可使用精确的标准局部关系 `|RN(z)−z|≤u|z|`；`z=0` 的误差为零。

以下取 `n≥2`；`n=1` 已单独处理。记 `E_k=|s_k−S_k|`。由于 `|S_k|≤kM`，第 `k≥2` 步有：

\[
E_k\le(1+u)E_{k-1}+ukM,\qquad E_1=0.
\]

展开而不近似：

\[
\begin{aligned}
E_n
&\le uM\sum_{k=2}^{n}k(1+u)^{n-k}\\
&\le uM\left[\frac{n(n-1)}2+(n-1)\right](1+u)^{n-2}.
\end{aligned}
\]

这里不能遗漏额外的 `n−1`：`Σ(k=2..n) k=(n−1)(n+2)/2`。等价地看相对误差因子，第一项和第二项都会经历第二次加法所引入的那次舍入。

对 `m≥0`、`u≥0`、`mu<1`，精确不等式为：

\[
(1+u)^m\le\frac1{1-mu}.
\]

一个短归纳是：

\[
(1+u)^{m+1}(1-(m+1)u)
=(1+u)^m\bigl(1-mu-(m+1)u^2\bigr)
\le(1+u)^m(1-mu)\le1.
\]

本题 `(n−2)u<2^-23`；再用恒等式：

\[
\frac{9n^2}{16}-\left[\frac{n(n-1)}2+(n-1)\right]
=\frac{(n-4)^2}{16}\ge0,
\]

得到：

\[
E_n
\le uMn^2\frac{9/16}{1-2^{-23}}
<uMn^2
\le uMN^2=r_{720}.
\]

最后一个常数比较是精确的整数 / 有理数不等式。没有把 `gamma_n` 近似成 `nu`，也没有忽略增长因子。这条路线足以独立验证原 720；证明 719 应选第 4 节更强、更短的端点 / 网格路线。

## 6. 抵消、次正规、零与极端输入

### 6.1 抵消不会导致 double underflow

所有精确 products 都在格点 `gℤ` 上，其中 `g=2^-298`。binary64 RN 在本题范围保持此格点：若系数绝对值不超过 53 位，该格点值本来可表示；否则舍入量子本身是 `g` 的整数倍，结果仍在同一格点上。跨 binade 的进位也保持这一性质。

归纳可得每个 `s_k` 和 `s_(k−1)+t_k` 都在 `gℤ` 上。故它们非零时绝对值至少 `2^-298`，远大于 double 最小 normal `2^-1022`。精确抵消为零，不是 underflow。

这个格点结论用于完整回答 underflow 问题及第 5 节的相对误差交叉验证。第 4.1 节的绝对网格核心本身不依赖先证明低格不变量，正式证明可以避免让两条归纳互相循环。

### 6.2 normal32 输入仍能抵消到 2^-298

原始输入：

```text
a = [0x00800001, 0x00800000]
b = [0x00800001, 0x80800002]
```

令 `m=2^23`，两个精确 product 的 `2^-298` 整数系数为 `(m+1)^2` 和 `−m(m+2)`，和恰为 1。四个输入都是 nonzero normal32；两次乘法和这次抵消均精确。因此 **normal-only guard 不能把可达最小非零格点提升到 2^-252**。

### 6.3 normal32 也不意味着左折精确

例如：

```text
a = [0x3f800000, 0x32000000, 0xbf800000]
b = [0x3f800000, 0x32000000, 0x3f800000]
```

精确 products 是 `1,2^-54,−1`，精确和 `2^-54`，而 RN64 左折结果是 0。该例只反证“全 normal 即精确累加”，不反证 719 / 720。

### 6.4 必须包括 bias 的具体理由

把 `minNormal32²` 之后追加 bias `1`：两侧都是 `[0x00800000,0x3f800000]`。精确和为 `1+2^-252`，double 结果为 `1`，误差 `2^-252`。若错误地只对原始乘积统计 `H=0`，取 `n=2` 的旧半径只有 `2^-301`，就小了 `2^49` 倍。正确包含 bias 后 `H=252`，现有 helper 正是这样准备的。

### 6.5 边界汇总

| 情形 | producer 处理 | wrapper 的 bitwise 语义 |
|---|---|---|
| `n=0` / 长度失配 / `n>2^30` | attempt 返回 miss，不调用本正长度定理 | 原 exact fallback |
| `n=1` | 乘积和首步加法实数值精确，误差 0 | 是否可接受输出仍由原 consumer 判断 |
| `+0/-0` | widening 保留 sign；数值误差 0 | producer 不冒充零符号定理，零候选 / 未命中走原 fallback |
| finite32 subnormal | widen 后 normal64；乘积最小 `2^-298` | 全 finite 路线涵盖；窄域路线以真实 guard 回退 |
| 精确抵消 | 可能为 0 或 `2^-298` 等很小值，误差界有效 | 正常非零 proposal 不能替代零的原规范 |
| 最大 finite32 | product `<2^256`，任何前缀 `≤2^286` | 最终 binary32 overflow / 边界输出仍交给 consumer 或 fallback |
| NaN / Inf，包括 `0·Inf` | preparation 无效，禁止用其缓存占位零进入已证明 fast 域 | 保留原 dot 的 NaN / Inf / payload 处理 |

## 7. 718 的最小可复核反例

**它同时满足 normal32 输入限制和 E2..253、fraction≠0 的 proposal 限制。** 所以这两项窄域 guard 不能挽救 718 的统一 producer 半径。

原始 word 序列只需三段描述：

| 连续项数 | a word | b word |
|---:|---|---|
| 128 | `0x3fffffff` | `0x3fffffff` |
| 128 | `0x3fffffff` | `0x3ffffffb` |
| 256 | `0x3fffffff` | `0x3ffffff7` |

全部 raw exponent 为 127，所以 `H=126+126=252`。`n=512`、`L=9`。每个 product 都是整数 `p<2^48` 乘 `2^-46`；因此可只对整数系数做 RN-even 53-bit 左折。

| 量 | 以 2^-46 为单位的精确整数 |
|---|---:|
| 精确和 S | 144115127946316800 |
| double 左折 s | 144115127946318880 |
| 绝对误差 | **2080** |
| r718 | **2048** |
| r719 | 4096 |
| r720 | 8192 |

因此 `|s−S|=65·2^-41 > 64·2^-41 = 2^-35 = r718`。

最终 double bits 是 `0x409fffff20000142`。helper 的 raw proposal 为 `0x44fffff9`，确实满足 `2≤e≤253` 且 fraction 非零。三个分段末尾的有符号误差依次为 `−96,288,2080` 个单位。

`counterexample718.py` 是独立最小脚本，只用整数算术。`verify_producer.py` 另以统一 `2^-298` 格点重新计算这一序列，核对相同的 sum、bits 和误差。**反例的目标仅是 718 producer 的包围半径；没有执行或声称反证已接受 consumer。**

由 719 的全域数学证明和 718 的反例，在同一公式 `2^(H+2L+C−1023)` 的固定整数偏移家族中，**719 是可普遍成立的最小常数**。这不声称当前半径对每一条具体输入都最紧。

## 8. 最便宜的正式证明接口

### 8.1 原创 Lean 核心究竟做了什么

`LazyProducerCore.lean` 仅 `import ContractExact`，以 `ℝ` 对接 FloatLib 的 `toReal` / `roundAt`，包含：

- 原顺序 `roundedPrefix` 和精确 `exactPrefix`；
- `rounded_envelope`：端点保持接口推出 `|s_k|≤kM`；
- `pre_round_lt_cap`：每次精确加法输入严格小于公共 cap；
- `uniform_error_le` / `uniform_error_strict`：首步精确，后续误差相加，得到严格 `NC`；
- `triangular_error_le` / `triangular_strict_radius`：精确的 `n(n−1)/2` telescope；
- `half_radius_identity`：常数 719 对应的纯代数恒等式。

它把 `R`、局部端点保持、首项精确与局部舍入界作为**显式定理参数**。这些参数尚未实例化成实际 Float 运算；它们不是新 axiom，也不是已经完成 producer 的声明。正式应用时选 `R = Model.roundAt binary64` 的实数数学模型，并另外证明 native fold 的值等于这个 fold。

核心使用实际 `n` 项，不补齐运行到 `N`，不改变顺序，也不新增数组。文件标记 **NOT_COMPILED**。当前环境没有可用 Lean / lake，未安装工具链；静态审阅不等于 elaboration 通过。

本文件是约 9.5 KB 的独立研究稿，包含说明和两条替代数学路线，不是可直接拼接的已验收候选。附件 public23 已有 252639 bytes；把整个研究稿追加进去会超过 256000-byte 限制。正式合并应只保留选用的统一 cap 路线、复用已有引理，并按最终完整单文件重新计算 UTF8 字节数；本次不声称该集成预算已经闭合。

### 8.2 核查过的真实固定源码入口

参考固定版本为 Lean `293d5d0c0c3f3dded4688b3ccd6a33939ac5102b` / 4.34.0、FloatLib `0d91825727839f597fd06b22fdd038ea21480f0c`。未在本地编译环境验证依赖锁；下一步需在团队现成固定环境做 probe。

下面用 `BI = FloatLib.Floats.Formats.BinaryInterchange` 简写 namespace。名称均从固定源码读取，完整 `#check` 在 `NativeBridgeProbe.lean` 中。

| 真实已有声明 | 用途 | 不能省略的前提 / 缺口 |
|---|---|---|
| `FloatLib.Floats.ExecFloat.Binary.toModel_ofFloat_add_of_isFinite` | native double 加法接到 BI model 加法 | 两输入有限；不保证输出有限 |
| `BI.Model.toReal_ofModel_mul_finite_eq_roundAt` | 非零 finite unpack 的 native mul 实数语义 | 两 mantissa>0；native targetExponent 条件；**输出有限** |
| `BI.Model.abs_toReal_add_sub_le` | model 有限加法的绝对误差 | 输入、输出都有限；还要控制 `epsilonAt` |
| `BI.Model.abs_roundAt_sub_le` | 数学 RN 的半 ULP 界 | 还要证明 `epsilonAt≤U/2^54` |
| `Flocq.round_preserves_generic` | 可表示值被 round 固定 | 真实证明 compact product / kM 的可表示性 |
| `Flocq.round_toReal_exists_same_exponent` | round 保持输入原指数表示 | 用 `FloatRep` 表示 `2^-298` 格点；连接 native 值 |
| `BI.Model.isFinite_roundDyadic_of_isIEEE_of_abs_toReal_le_posMaxFinite` | 有界 dyadic round 有限 | 仍是软件 roundDyadic，需经过 native/model 等式 |
| `BI.Model.roundWithAccuracy_exact_eq_round_of_le_targetExponent` | 将 `UnpackedFloat.roundWithAccuracy .exact` 改写为 `UnpackedFloat.round` | 明确 targetExponent 不等式；该声明本身不是 `roundAt` 实数语义定理 |

固定 Lean 的 `Float.add/mul/ofBits/toBits` 均有 `Float.Model` 逻辑定义。不能把它们说成完全 opaque；也不能把源码层逻辑模型等同于已验证所有机器指令实现。官方 native 边界保持原样，本产物没有新增 extern 或替换执行实现。[S1][S2]

固定 FloatLib 有已存在的有限输入 native 加法桥；它允许结果 overflow，所以不能用这个定理直接填上 `hout`。[S3] 乘法本次找到的是带条件的 unpack 入口；没有凭空使用一个无条件 `ofFloat_mul`。[S4]

sole-import 的源级导入链已检查：`ContractExact → Values → Decode → Congr → Round → FloatLib → Floats → Formats → IEEE754 → Native.AddSub`。这只说明源码可见性有依据，不代替固定环境下的 `#check`。[S7]

### 8.3 推荐连接顺序与明确未闭合项

1. **widen 专用引理。** 对实际 word 配方证明 finite 和值一致。全 finite 多一个 subnormal `log2 / shift` 分支；窄域把该分支以实际 guard 排除。零保留 bits，误差投影只用数值零。
2. **只证明 widened-binary32 的 native mul。** 非零 widened 值均为 normal64，unpack mantissa 至少 `2^52`；可据此处理 targetExponent 条件。再利用原始 compact product 的 48-bit 形状证明 round 固定。零因子单独分支。**输出有限性必须真正证明**，不能在 `hfinite` 中填入待证精确性结论。
3. **native add 接已有桥。** 从实际 finite 输入进入 model；用 dyadic 精确加法及 `|z|≤2^286` 先关闭结果有限性，然后用实数 RN 语义。勿循环使用“假设输出 finite，得到误差，再由误差证明输出 finite”。
4. **有限端点 / half-ulp 引理。** 证明 `±kM` exact，得到局部 `hgrid`；证明 power cap 下 `epsilonAt≤U/2^54`，或直接使用最近值与可表示网格竞争点。后者避免相对误差、低格前提和大 gamma 定理。
5. **接入实际递归。** 使用团队已接受的 getter 一致性，将 `sumRemaining` 的每步对应到上述实数 recurrence，再应用当前核心。radius bit 解码和 UInt64 范围复用团队模块，不另造一套。

其中 1–4 的 native 实例、具体 finite / generic 表示证明，以及第 5 步的桥接实例，本次均未写成已验证 Lean 定理。交付的小核心覆盖它们之后的归纳与严格半径代数。

## 9. 全 finite 与窄域：把限制落到真实 guard

| 方案 | 真实 runtime 改动 | 证明省下的部分 | 仍需证明 |
|---|---|---|---|
| 全 finite | 原 `e==255` 无效 guard；radius 720→719 | 不损失 finite32 fast 域 | 全 widening，精确 mul，prefix finite，端点与 half-ulp |
| normal32 + ±0 | 把非零 subnormal 标为无效 | 非零 subnormal 的 widening / log2 分支 | 同样的 product / cancellation / prefix 误差主体 |
| 再限 proposal `E2..253 && fraction!=0` | 在调用 consumer 前增加该判定 | 可配合团队的较窄 consumer 实例 | **不减少** producer 的任一前缀义务；718 反例仍满足 |

窄域的可执行 preparation 判定应位于 `prepareFn` 现有无效分支：

```lean
-- 原本: if e == 255 then
if e == 255 || (e == 0 && (word &&& 0x7fffff) != 0) then
  valid := false
  values := values.push (Float.ofBits 0)
else
  -- 保留原本 peak 更新与 widenBits 路径
```

proposal 限制可以在 `attempt` 里作为已有 `certify` 之前的额外 gate，不修改已接受 consumer：

```lean
let e := (q >>> 23) &&& 255
let f := q &&& 0x7fffff
if !(decide (2 ≤ e) && decide (e ≤ 253) && f != 0) then
  return 0
-- 然后走原 certify；若不接受仍返回 0
```

这些是 **NOT_COMPILED 的插入片段**。宽域方案不需要它们；不是把它们预设成输入假设。若采用窄域，必须真正接入运行时，并对 invalid / miss 分支调用原正确 `slow row col`。

原 helper 的最后一步 `act relu (if guess == 0 then slow row col else guess)` 提供所需回退形状。正确性证明的全输入分支应是：无效或 miss → 原正确 dot；hit → producer 界 + 团队已接受 consumer → 同一个精确一次舍入 dot。`slow` 必须是含 bias、未提前 activation 的精确 dot，这个约束不能略去。

normal+±0 适合缩短**第一版正式连线**，尤其当 subnormal widening lemma 目前最慢；全 finite 的误差数学已经成立，后续扩大 fast 域不必重做核心。两种方案均不改变最终 Kernel 的全输入量词。

在当前 row / column preparation 结构里，一个非零 subnormal 会使整个相应缓存的 `valid=false`，继而让使用它的 dot 退出 fast 路径；不能只统计单个元素检查的成本而忽略这种回退范围。`ThinPrepared.valid=true` 这个可构造字段本身也不是 metadata 正确性的证明；只对已由团队 preparation / getter 定理认证的对象应用本 producer。

## 10. 精确累加或分块：可达域与额外成本

本次不建议把路线改成补偿或分块。其代价应先按实际域说明：

对长度 `m≥1` 且至少有一个非零 product 的块，若所有非零 products 写成 `σ_i p_i 2^(J_i−298)`，`p_i<2^48`，且 `D=J_max−J_min`，则每个 exact prefix 在共同指数下的整数系数**绝对值**小于 `m·2^(48+D)`。全零块单独按数值精确处理，不对空的非零项集合取 `min/max`。充分条件：

\[
D+\lceil\log_2 m\rceil\le5
\]

保证每个 prefix 都至多 53 位有效数字，块内 native 左折完全精确。这是充分条件，不是必要条件。它最多允许同 product 指数下 `m≤32`；`D=1` 时最多 16 项。任意 normal32 输入并不满足它。

把条件做成真实 guard 至少需要排除零后的最小 / 最大 product 指数。当前 preparation 只有每侧 max，没有 min；可以额外缓存两侧 min，用跨度和给出保守界，也可以每个 dot 逐项看实际 product 指数。前者增加准备统计与 metadata，后者增加 per-term 整数操作，且独立两侧跨度可能很松。不能把“做个 guard”记为零成本。

分块还增加每块重置、块结果存储或寄存器状态、块间 reduction；块间求和仍需误差定理。重新结合加法改变了当前原顺序 helper 的执行模型，需要新证明。TwoSum / 多分量补偿增加每项加减、依赖链与额外累加状态；也不能无条件保证有限长度两个 double 装得下所有 exact sums。本题从最小 product 位到最大前缀幅度的保守窗口可跨约 585 个二进制位置，远超单一 53-bit accumulator 的全域精确容量。

因此当前优先级应是：保留已有一乘一加的左折，证明 719 producer，再观察真实 fallback 比例。没有 native 整调用测量前，不对“更精确”或“更窄 radius”赋予性能收益数字。

## 11. 与实际 helper 的逐项映射

下面行号均是附件原始容器中的位置，只用于定位。代码完整原件不在本 zip。

| 实际位置 | 对应数学对象 / 义务 | 本次处理 |
|---|---|---|
| `index32`（3357 起） | `I=0` 或 `e−1` | 解码定义，未重做 UInt32 模块 |
| `widenBits`（3362 起） | exact widening、finite64 | 全分支数值推导；native word 桥仍待实例化 |
| `prepareFn`（3469 起） | 实际 `n`、有效性、每侧 peak | 假设来自已接受准备 / getter 模块；可在 invalid 分支加窄域 guard |
| `sumRemaining`（3428 起） | `s_0=+0`、原顺序 `RN64(acc+t)` | 不改 runtime，新的端点 / 误差数学核心 |
| `ceilLog2`（3391 起） | `n≤N=2^L≤2^30` | 使用 guard 建立的长度前提；复用整数模块 |
| `attempt`（3487 起） | length / valid guard、`H=A+B` | 只在真实有效 fast 域应用 producer |
| radius（3495；另一路 3445） | `r_C=2^(H+2L+C−1023)` | 证明 720、719；反证 718；两个入口如均采用应同步 |
| `proposal` / `certify` | 任意 proposal + 已接受 strict consumer | 不重证；可外加窄 proposal gate |
| `linear`（3500 起） | `n=k+1`、bias 入两侧统计、原 slow fallback | 保留 bias 与回退；不声称全12连线完成 |

720 的 biased exponent 位于 `[720,1286]`，719 位于 `[719,1285]`，均为合法正 normal64 power-of-two 编码。`0≤H≤506`、`0≤L≤30` 下，不会指数字段溢出或碰到特殊值。这里没有发明新的 UInt64 引理。

## 12. 已完成验证与下一最小实验

### 已运行的有限整数模型

命令：

```bash
python3 verify_producer.py --output verification.json
python3 counterexample718.py > counterexample718.json
```

`verify_producer.py` 只用 Python 标准库整数和 Fraction，不调用 host float。此次结果：

- 4080 个 widening words：两种符号、全部 255 个 finite raw exponent、8 个代表 fraction；
- 4321 个 product pairs：边界组合和固定种子样本；
- 525 个 dot 序列，共 40264 项，最长实际循环 512 项；
- 15717 组 `(H,L)` 的 radius 字段数值核对；
- `n=2^30` 只做符号整数 / 有理数上界核对，没有执行十亿次循环；
- 完整记录当前 / 半径收紧检查、bias 遗漏反例、normal 细格抵消以及 718 的独立尺度复核。

没有从这些有限样本推断全域成立；全域结论来自第 2–6 节推导。没有运行 native benchmark、CI、全12 gate，也没有修改生产 Kernel。

### 下一最小实验，按价值排序

1. **现成固定工具链的 source probe。** 用 sole `import ContractExact` 编译 `NativeBridgeProbe.lean` 和 `LazyProducerCore.lean`；记录 Lean 版本、FloatLib commit、命令、退出码。再对自有核心做 `#print axioms`，检查仅允许的逻辑公理。当前都为 NOT_COMPILED。
2. **只闭合一个 widened multiply lemma 与一个 add-prefix step。** 若先走 normal+±0，必须同步接入真实 guard。第一关是非零 normal widened operands 的 native mul 输出 finite 与精确值；第二关是 prefix finite + `roundAt` 等式 + cap。不要先集成全12，也不要为 probe 运行代价修改 gate。
3. **小型原生值核对。** 在相同工具链运行最小 subnormal 平方、最大 finite 平方、normal 细格抵消、n=1、±0、以及本 512 项反例，输出 raw bits 与整数参考比较。这是检查接线，不能替代定理。本次未运行。
4. **闭合 producer 后才做整调用成本实验。** 同一原始输入、相同编译参数下比较 720 与719，记录 accepted / fallback 数量、准备成本、drop 成本、慢路调用与整调用耗时。原始 peak 相加可能很松，特别是两侧最大指数不在同一项时；严重抵消也可能继续回退。半径减半不会自动带来显著模型收益。

## 13. 固定源码来源

以上 native 接口名称来自这些公开固定源码。交付包只含本次原创分析 / 代码，不含这些源文件副本。

- [S1：Lean Float definitions](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Data/Float/Float.lean)
- [S2：Lean Float.Model](https://github.com/leanprover/lean4/blob/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/Init/Data/Float/Model/Float.lean)
- [S3：FloatLib native AddSub](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/IEEE754/Native/AddSub.lean)
- [S4：FloatLib Arithmetic LeanModel](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Arithmetic/LeanModel.lean)
- [S5：FloatLib Analysis Error](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Analysis/Error.lean)
- [S6：FloatLib Flocq Exactness](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/Flocq/Theory/Error/Exactness.lean)
- [S7：Contract ExactToolkit Round import](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/accb82b6e2adeda1b41a57a260d68fb3879c427e/lean/contract/ExactToolkit/Round.lean)
- [S8：FloatLib Finiteness](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Arithmetic/Finiteness.lean)
- [S9：FloatLib ModelRounding Proof](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/ModelRounding/Proof.lean)

源码读取不构成编译结果；所有未知连接和未运行项目已在上文分开标识。
