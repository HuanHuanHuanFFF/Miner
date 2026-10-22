# FloatLib R2-W01：严格 ordered binary32 求和的可组合结构与成本否决

日期：2026-10-22（北京时间）  
合同版本：比赛仓库 `978cc5b445edb9943fd9953b0a9037d97a9f33a8`；FloatLib `0d91825727839f597fd06b22fdd038ea21480f0c`；Lean `v4.34.0`。

## 1. 决策结论

**本轮找到了真实的数学结构，但没有得到可推荐直接投入完整 Kernel 开发的性能突破。**

最值得保留的结构是：

1. **固定浮点间距上的 ordered RN-even 转移，可以用两个入口奇偶状态精确表示和结合。** 对混合符号块，还能把所有候选前缀的最小、最大位移放进同一个可组合摘要。这里结合的是转移函数，原来的浮点加法顺序没有改变。
2. **对同向、奇尾数、足够小的输入，入口奇偶依赖消失。** 每项变为独立整数增量；因前缀单调，块末端不越界这一项检查就能证明所有前缀安全。
3. **整数增量可以由固定锚点的独立 Float32 加法得到。** 不一定要每项拆尾数、做变量移位。令锚点为当前 binade 的正下端 H，则 `bits(RN32(H+|x|))−bits(H)` 正是所需增量。浮点加法相互独立，随后允许结合的是有界整数归约。
4. 指定 `sum/relu` 生成器恰好提供了一个可达机会：非零项的尾数最低位必为 1。在累加器指数至少高 2 时，所有这些项都严格避开 midpoint。这是确定性质，不是概率猜测；正式快路仍须运行时验证条件。

然而，**三个包含域检查、端点检查及失败块重放的本地 C 实现都未胜过原生顺序累加**。最好的固定锚点版本在本轮 ReLU CPU 探针中，耗时比为 **2.279×**；其余两个版本更慢。五轮固定锚点比值在 **2.095×～2.438×**。这支持暂停当前标量实现的大规模形式化，不能据此声称所有等价算法都不可能加速。

**建议：数学结论保留；当前标量实现 PARK。最多再做一次固定 Lean 环境中的小型编译与全成本诊断，以排除 C 代理和实际 Lean 表示成本的差别；没有稳定净收益就停止，不扩展到通用转移分区或 bmm。**

### 证据分层

| 层级 | 本轮实际完成 | 结论边界 |
|---|---|---|
| 纸面数学 | 两状态半群、前缀证书、odd 无中点、单调端点证书、固定锚点量化、整数容量与特殊值分流推导 | 有完整推导；不是 Lean kernel 已检查的证明 |
| 公开源码 | 6 个比赛文件、73 个 FloatLib 文件逐一核对固定 commit 的 Git blob SHA；另读取 Lean v4.34.0 相关源文件 | 可以给出真实定理名、定义和导入路径 |
| 有限诊断 | 任意精度整数 binary32 参考、合成反例、摘要结合律、20,000 个随机块、三类各 100 条长度 1000 的向量；独立第二套反例和锚点检查 | 已接受候选未观察到位差；不能替代全域证明 |
| 本地 CPU 成本 | GCC 13.3.0、x86_64，三种候选与原生顺序 C 循环，5 轮交替顺序测量 | 是 CPU 代理负结果；不是正式 Lean 或比赛成绩 |
| Lean 编译 / 公理审计 | **未执行**；环境无 `lean`、`lake`，未安装工具链 | 草稿可能有 elaboration 问题；`#print axioms` 结果 UNKNOWN |
| 目标性能 / gate / 提交 | **未执行** | 不声称可提交、通过 gate 或有目标加速 |

## 2. 研究边界与固定合同

本轮仅使用本次任务文本、指定固定版本的公开一手源码、相关作者/官方资料及自造合成数据。没有读取旧会话、旧项目附件、私有代码；没有参赛提交、修改账户、改动官方 bench/gate/依赖/编译选项，亦未安装工具链。C 的编译参数只作用于独立诊断文件。

既有 native finite add/mul 与 ExecFloat 的逐位等式、原生 Float32 顺序累加器，以及另一开发者正在推进的末尾 finite 守卫，全部作为给定基线。本文不把这些工作重新算作发现，也没有读取它们的私有实现。

公开合同确认为：

- `sumSpec` 从 `Competition.posZero` 即 +0 开始，对 `List.finRange n` 左折叠 `ExecFloat.add`。
- `SumObligation` 对**任意长度和任意输入位型**成立，不只是 n=1000。
- `bmmSpec` 每个输出按 k 递增，先 `ExecFloat.mul`，再 `ExecFloat.add`。不能换 FMA，不能把未舍入乘积放进精确点积。
- raw 虽不计时，仍在正确性范围内。

来源：[ContractTensor.lean](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/contract/ContractTensor.lean)。

必须更正一个会影响选路的细节：固定版本的 **bmm/relu 是 A 用 ReLU，B 用 dense**，所以乘积仍有混合符号。sum/relu 的单调性不能搬到该 bmm 类。来源：[BenchBmm.lean](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/bench/BenchBmm.lean#L23-L36)。

## 3. 先找反例：哪些“更快求和”算错了目标

本节的有限加法步骤与主要反例均由整数精确参考复核。参考用整数表示值除以 `2^-149`，每步独立执行 binary32 RN-even；没有用 double 累加冒充 ordered binary32。溢出例中的第一次 overflow 已计算，后续 `+Inf + 有限数` 的结果按 IEEE/合同分支推导；未据此声称实现了完整非有限 payload oracle。

### 3.1 最强反例：正数、奇尾数、实际 ReLU 指数域仍不能重排或末轮一次舍入

令 `q=2^-20`：

| 数量 | 精确值 | binary32 bits |
|---|---|---|
| s | `8+q` | `0x41000001` |
| a | `1+3·2^-23 = 1+3q/8` | `0x3f800003` |
| ordered `[s,a,a]` | `10+q` | `0x41200001` |
| ordered `[a,a,s]` | `10+2q` | `0x41200002` |
| `RN32(s+2a)`，只末轮一次 | `10+2q` | `0x41200002` |

三项都为正 normal，biased exponent 在 124..130，尾数均为奇数。补 997 个 +0 就是长度 1000 的反例。

第一条路径一直留在 `[8,16)`。每次 `a/q=2^20+3/8`，所以每次只增加整数 `2^20`，各自丢掉 `3q/8`；而实数总和把两次丢掉的部分合成 `3q/4`，跨过末轮 midpoint。**本报告快路要保留这些逐次丢失，不能把它们补回来。**

这也否定任何只保留 multiset、精确总和、绝对值和、指数直方图等无序信息的通用修正器。它不否定保存顺序的转移摘要。

### 3.2 midpoint 使独立增量依赖入口 parity

取 `s=0x3f800001=1+2^-23`，`x=0x33800000=2^-24`。入口最低有效位为奇数：

- 真正 `RN32(s+x)=0x3f800002`。
- 若独立算 `RN_integer(x/2^-23)=RN_integer(1/2)=0`，再把 0 加到 s，得到错误的 `0x3f800001`。

因此不能不加条件地把每项独立舍入到入口 ULP，再进行整数求和。

### 3.3 混合符号只查最后位置会误放

以 q=`2^-23`、`L=2^23` 为统一格点，入口 `s=0x3f800001`，块为：

```text
0xb4400000   = -3·2^-24
0x34000000   =  2^-23
```

统一 q 网格预测整数轨迹 `[L+1,L,L+1]`，末端仍在原 binade；预测输出 `0x3f800001`。真实轨迹为：

```text
0x3f800001 -> 0x3f7fffff -> 0x3f800000
```

原因是 1 以下的间距为 q/2。**候选落在 L 本身，也不能保证舍入模型仍然正确。** 更强的“越过上界再返回”反例见诊断和数学附录。

### 3.4 其他不可省略的边界

| 反例 | ordered 结果 | 否定的简化 |
|---|---|---|
| `[2^24,1,-2^24]` | +0；精确总和末轮为 1 | 精确总和等于 ordered 输出 |
| `[maxFinite,maxFinite,-maxFinite]` | +Inf；精确总和为 maxFinite | 只证最终精确总和有限 |
| `[0x00800000,0x807fffff]` | `0x00000001`，最小正 subnormal | FTZ 或忽略取消后的次正规数 |
| 从 +0 开始输入 `[-0]` | +0 | 返回原输入、把实值相等当位相等 |
| `s=0x01000001,x=0x00000001` | `0x01000002` | 对 subnormal 错用指数差 `Es−Ex`；此时固定偶锚预测不变 |

最后一行解释为什么锚点快路要拒绝 `Es=2`：subnormal 有效指数是 1，不能把原始 exponent field 0 直接套进 normal 的公式。

## 4. 少量本质不同路线的比较

| 路线 | 数学可行性 | 完整成本与关键障碍 | 本轮选择 |
|---|---|---|---|
| 全域转移函数 / 分段扫描 | 有限状态当然可表示；固定间距还有很小摘要 | 原始全 32 位转移表约 16 GiB/函数，远超单文件；全域压缩的区间数、构建成本没有已证上界 | 不做全域实现，深入固定间距子问题 |
| 所有前缀精确的块证书 | 可证明充分 | 对任意 fraction，廉价格点幅度条件很严格；逐个验证精确性仍有依赖和位操作成本 | 不作主线 |
| EFT / 预测后修正 | 原序 EFT 可以恢复每步误差 | 已执行原串行加法；重组轨迹的误差不等于原序轨迹误差，midpoint 和消去会改变后续路径 | 没有新的便宜证书，不继续 |
| 固定间距两 parity 转移 + 全前缀摘要 | **可精确组合** | 维护双状态、两份 min/max、位量化和失败重放；在标量代码里未必减少依赖 | 保留一般理论与有限诊断 |
| 同向 odd 无中点块 + 单端点证书 | **可合法重组整数增量** | 域检查、量化、整数归约、端点及跨界回退仍有成本 | 最有希望，深入并实测 |

“所有前缀精确”的一个简单充分条件是：入口和各项都是 q0 的整数倍，所有精确前缀的整数系数绝对值不超过 `2^24`，且 exponent 范围合法。其整数和都可表示，可以合法移除每步 RN。对 dense 的最细可能共同格点 q0=`2^-26`，该粗证书容许的幅度只有 1/4，而输入绝对值和远大于此；细化成每个前缀有足够 trailing zeros 又恢复逐项检查。不能从“每个输入自己可表示”推导“所有精确前缀可表示”。

TwoSum/FastTwoSum 的精确残差性质是有用工具，但其目标和本合同不同；标准算法分别需要多次浮点运算，原序执行不会消掉已经发生的 add 依赖。这里没有证明任何“所有预测修正都不可能”的下界，只指出当前候选没有比原序 add 更廉价的正确性证书。参考：[Ogita–Rump–Oishi, Accurate Sum and Dot Product](https://www.tuhh.de/ti3/paper/rump/OgRuOi05.pdf)。

## 5. 命题 A：固定间距上存在两个状态的可组合转移

设统一格距 q>0，整数状态 K 表示 `s=Kq`。暂不把这个无限格当成真实 binary32；后面另给使二者一致的证书。

把任一输入写成 `x/q=a+r`，`a=floor(x/q)`、`0≤r<1`。即使 x<0，仍用向下取整的 a 和非负余数 r。令 R 为 RN-even 的整数舍入，则：

```text
F_x(K) = R(K+x/q) = K + δ_(K mod 2)

r<1/2: δ_0=δ_1=a
r>1/2: δ_0=δ_1=a+1
r=1/2: δ_p=a+((p+a) mod 2)
```

证明直接来自最近整数及 midpoint 选偶数。特别有 `F_x(K+2)=F_x(K)+2`。

一块的复合 F 也满足该平移关系，因而可表示成：

`F(K)=K+D[K mod 2]`。

先执行 A 再执行 B 时：

```text
r = (p + D_A[p]) mod 2
D_AB[p] = D_A[p] + D_B[r]
```

这个结合律来自函数复合，不是来自实数或浮点加法的结合律。没有 midpoint 时两个 D 相同；一旦发生 midpoint，状态差仍可由两个整数完整表示。

### 5.1 所有前缀也能摘要，而不是运行时重算所有 RN

每个入口 parity 再保存候选前缀位移最小、最大值 `lo[p],hi[p]`，包括空前缀的 0。复合为：

```text
lo_AB[p] = min(lo_A[p], D_A[p]+lo_B[r])
hi_AB[p] = max(hi_A[p], D_A[p]+hi_B[r])
```

摘要为 6 个有符号整数；组合 O(1)。构建一块仍是 O(B) 工作，平衡归约可使深度为 O(log B)，但本合同没有自动提供并行硬件或高效 Lean 归约实现。

### 5.2 与真实 binary32 的充分区间

令正 normal 入口 exponent field 为 Es，`1≤Es≤253`，

```text
q = 2^(Es−150)
L = 2^23
U = 2^24
L≤K<U
```

一个简单充分条件是所有候选输出前缀都在 **`[L+1,U]`**。此时真实 RN32 与统一 q 网格选择一致：

- 严格内部的候选格点具有相同左右相邻数和 midpoint parity。
- 候选 U 的统一网格舍入 cell 包含在真实 binary32 的 U 舍入 cell 中；真实 U 右边的间距更大，所以允许恰 U。
- 排除 L 避免较低 binade 的 q/2 间距。最小 normal binade 的下方是同间距 subnormal，本可放宽；为保持首版简单没有采用这个例外。
- Es≤253 保证 Uq 仍有限，不接触 overflow 门槛。

用摘要只需检查：

`K+lo[p]≥L+1` 且 `K+hi[p]≤U`。

诊断实现把空前缀也纳入 bounds，所以还会保守拒绝入口恰 L 的块；这只损失通过率，不损失正确性。负 normal 区间可以先按入口符号镜像，再使用同样证明。

**不能宣称任何跨 binade 函数都需要指数数量状态。** 本轮还观察到，对预先固定的各步 q 序列，可以利用最大 q 的周期性得到更紧压缩；但真正的 IEEE q 序列依赖未知前缀。确定这些区间、构建证书及其全成本仍没有解决。本轮不沿这个分支扩展。

## 6. 命题 B：odd 同向块把逐步舍入变为合法整数归约

这是选择深入的主命题。

### 6.1 精确充分条件

设块入口 s 为非零 normal，符号为 σ，biased exponent 为 Es。取：

```text
3≤Es≤253
q=2^(Es−150)
L=2^23, U=2^24
|s|=Kq，L≤K<U
B≤64
```

每个输入满足以下之一：

1. `+0` 或 `-0`；
2. 非零且符号为 σ，绝对值的 significand M 为奇数，有效指数 Eeff 满足 `Eeff≤Es−2`。

其中 normal 的 `Eeff=rawExponent`、`M=2^23+fraction`；subnormal 的 **`Eeff=1`、`M=fraction`**。

设 `d=Es−Eeff≥2`，则：

`|x|/q=M/2^d`。

定义整数增量：

```text
δ = RN_integer(|x|/q)
D = Σ δ
```

最后的接受条件为：

**`K+D≤U`。**

### 6.2 无中点引理

若 M 为奇数、d≥2，`M/2^d` 不可能是半整数。

反证：midpoint 要求 `M mod 2^d=2^(d−1)`。左边为奇数，因为模数为偶数；右边为偶数，因为 d≥2，矛盾。

因此对任意整数 K，

`RN_integer(K+M/2^d)=K+RN_integer(M/2^d)`。

这是整数增量与当前 accumulator parity 脱钩的关键。不是近似，也不需要概率假设。

直接量化时：

- `2≤d≤24`：`δ=(M+2^(d−1)) >> d`。
- `d≥25`：`M<2^24`，所以 `δ=0`。

不能直接对机器整数做任意大的位移；有些机器/语言语义会对位数取模。必须在 d≥25 时分流，或使用后述锚点量化。

### 6.3 单端点为什么包含所有前缀

所有 δ≥0，因此每个候选前缀

`K_j=K+Σ_(i<j) δ_i`

都在 `[K,K+D]⊆[L,U]`。而每步舍入前的精确实数和也不会低于 Lq，因此不会碰到第 3.3 节的下方密网格漏洞。

逐步归纳：假设第 j 步真实状态就是 `σK_jq`。由无 midpoint 平移引理，统一 q 格的下一候选是 `σK_(j+1)q`。若 `K_(j+1)<U`，它落在本 binade 的有效均匀格；若等于 U，统一 q 的舍入 cell 仍包含于真实 U 的 cell，所以结果相同。两种情况都有限且非零。于是最终输出严格等于原序逐次 RN 的结果。

这里每个前缀都在证明中出现；运行时利用单调性，把这组证明义务压缩成了一次端点检查。**没有在运行时偷偷重做全部原序 RN 来验证。**

允许恰 U 很重要：此时出口已经进入下一 binade，下一块重新选择 Es/q。若一个块越界，就从保存的原块入口对原输入顺序重放，不能沿用被拒绝的候选值。

### 6.4 命题 C：固定锚点量化

令正锚点：

```text
H = Lq = 2^(Es−127)
A = Es << 23       -- H 的正 binary32 raw bits
```

对上述每个输入，记 `y=|x|`。由指数条件，`0≤y<H/2`。所以：

`H≤RN32(H+y)≤1.5H<2H`。

锚点量化结果始终留在 H 的同一 binade；raw bits 按一个 q 对应增加 1。又因 `H/q=L` 为整数，得到：

**`δ = bits(RN32(H+y)) − A`。**

每项的 `H+y` 都使用同一个固定 H，彼此没有 accumulator 依赖。其浮点加法不能被改成 FMA，也不需要重结合；可结合的是后续整数 δ 的和。

这提供了真实的并行机会：把原来 B 次串行 FP add，改成 B 个独立 FP add + 一个整数 reduction + 一次块出口更新。它不减少输入读取次数，也不必减少 FP add 数量，收益只能来自依赖深度/执行吞吐的变化。

**subnormal 边界：** Es≥3 是必须的通用简化条件。若 Es=2，最小 subnormal 是 q/2，odd 不再排除 midpoint，反例见第 3.4 节。对 Es≥3，subnormal 的有效指数 1 给出 d≥2，证明正常成立。零值单独放行；非零 accumulator 加 ±0 都保持该非零位型。

### 6.5 一种可实现的纯 word 域判定

在已检查 `3≤Es≤253` 后，令：

```text
mag = xBits & 0x7fffffff
limit = ((Es−1) << 23) − 1
```

接受一项，当且仅当：

```text
mag==0
或
(x 与入口同号，mag 的最低位为1，mag≤limit)
```

`mag≤limit` 确保 normal exponent≤Es−2，亦包含 subnormal；它也排除 Inf/NaN。不能在 Es 未检查时解释该 limit，特别是 Es=1 时 unsigned 减法会回绕。

对负入口只把同向输入转成正 magnitude 做 H+y，再给块结果恢复入口符号。异向输入绝不可通过这个 monotone 快路。

### 6.6 机器整数容量、raw 编码与防回绕

由 `y<H/2`：

`0≤δ≤2^22`。

当 B≤64：

```text
D≤2^28
K+D<2^29
```

所以用 UInt32 累加各个 δ 不会溢出。端点检查可写成：

`D≤0x800000−fraction(s)`。

接受后，正 magnitude raw bits 直接增加 D；恰好到 U 时会自动进位到下一 exponent 的 fraction=0。Es≤253 保证新 exponent≤254，仍为有限 normal。

若使用 `Σ bits(quantized) − B*A` 的模归约，应先在模 `2^32` 环里证明它等于 `Σδ`，再利用 D<2^32 恢复自然数值。不能从最后 residue 很小反推没有回绕。反例：B=1024、每项 δ=`2^22`，总和 `2^32` 会回绕到 0，错误通过端点检查。实际 Kernel 必须固定块容量上限，并对尾块用实际长度。

## 7. 对全输入逐位合同的覆盖

主快路的域是充分条件，不是改写合同的量词。任意长度、任意位型都仍需返回原 `sumSpec`。

| 情况 | 快路如何处理 | 正确性理由 |
|---|---|---|
| 起点 +0、空输入、首个非零之前 | 原基线；空输入直接 +0 | 不凭实数 0 决定 signed zero |
| 同向 odd normal 或合格 odd subnormal | 尝试独立量化和端点证书 | 命题 B/C 覆盖全部前缀 |
| 输入 ±0，块入口非零 | 增量 0 | 对非零有限值，加 ±0 保持原位型 |
| 异向输入、可能消去 | 拒绝块，保存入口后原序重放 | 不把单调性偷用于混合符号 |
| 偶尾数、指数差 0/1 | 拒绝块 | 防 midpoint/parity 漏洞 |
| 超过 binade 的块 | 拒绝并原序重放 | 不把候选终值跨指数解释为真实轨迹 |
| 入口 subnormal 或 Es=1/2 | 本锚点版本拒绝 | 避免模型边界；gradual subnormal 留给基线 |
| 入口 Es=254 | 拒绝 | 排除 U 对应 overflow 的特殊上界 |
| Inf、任意 NaN payload/signaling 位型 | 项域拒绝；最终走原非有限回退 | 不用宿主 NaN 规则替代 FloatLib payload 策略 |
| 任意形状 bmm | 本轮不替换其乘加核心 | 不混淆独立 mul 舍入和 sum 定理 |

建议接入方式是保留既有 native 顺序路径和最终 finite 守卫：已接受块用新证明替换同一段 `ExecFloat.add`；未接受块仍用原生顺序循环；若最终非有限，则对**原始整向量**调用原实现。native 临时 NaN 的 payload 不参与返回合同。末尾守卫的逆向归纳证明由另一开发者负责，本轮不声称完成。

如果不依赖正在完成的末尾守卫引理，也可先构造“成功块有证书、其他块直接调用 ExecFloat.add”的纯正确性版本；它适合证明，不是相对于 native 基线的公平性能候选。

## 8. 实际生成域：机会在哪里、在哪里不存在

### 8.1 ReLU 的 odd 性质是源码事实

`sumRelu` 在 `w & 1 == 0` 时生成 +0，否则保留低 23 位 fraction。因而每个非零 significand 都是奇数。

其 raw exponent 为 124..130。只要入口 Es≥132，便有 `d=Es−Ex≥2`，所有非零项都确定无 midpoint。后期并不是“碰到 midpoint 概率很低”，而是该结构下不可能碰到。来源：[BenchTensor.lean](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/bench/BenchTensor.lean#L21-L31)。

这只用于评估机会。Kernel 不得信任类别名、种子或样本身份；每一块都按第 6.5 节检查 word 条件。任意用户输入只要满足条件都能进入快路，其他输入都精确回退。

### 8.2 有限覆盖实验

诊断用独立 Python PRNG 新生成 32 位词，然后应用同样的三类 word 变换；没有使用官方 LCG 或官方固定种子。每类 100 条向量，每条 1000 项。候选从第 1 项之后的参考前缀开始，按固定 B 切块；拒绝等价于原序走完该块，下一入口仍是正确参考状态。

表中是**被接受块覆盖的元素数 / 全部 100,000 个元素**；不是通过块比例，不是官方测试集成功率，更不是加速比。

| 块长 B | ReLU：odd/锚点主路线覆盖 | dense：一般双 parity + prefix 证书覆盖 | wide：一般双 parity + prefix 证书覆盖 |
|---:|---:|---:|---:|
| 8 | 93.660% | 51.697% | 76.332% |
| 16 | 89.132% | 38.641% | 61.268% |
| 32 | 81.788% | 25.841% | 43.012% |
| 64 | 69.372% | 15.793% | 25.839% |

主 odd/锚点路线在这组 dense/wide 数据里没有接受完整块，符合其同向和 odd 条件较窄的预期。一般摘要覆盖更宽，但处理成本也更高，不能用其通过率推导收益。

这 100 条 ReLU 向量首次达到 s≥32 的前缀位置：最小 6、最大 58、平均 24.11。它只是这批合成数据的观察，不是任意输入上的概率或保证。B 越大覆盖下降，主要因为一个跨 binade 事件会使整个较长块重放。

Python 与 C 探针采用不同的独立 PRNG，块对齐也不同：Python 先处理一项；C 从开头按 B=32 处理。因此不能把上表的比例直接代入 C 的时间作为实测分项。

### 8.3 bmm 不晋升

即使把每个已舍入乘积当作 sum 的输入，仍有三项阻碍：

1. 固定 bmm/relu 的 B 是 dense，乘积不是单调正数流。
2. binary32 乘法舍入后的尾数不保留输入的 odd 性质，不能复用 ReLU 生成器的无 midpoint 推导。
3. 每输出只有 n=100，热身和跨界块占比可能更高；输入读取、mul、输出编码都不能省略。

因此不推荐把本轮结构直接推广成 bmm 的新算法。本轮没有运行 bmm 全形状性能实验，也没有构造 `BmmObligation` 证明。

## 9. 完整成本核算与已执行的负面探针

### 9.1 必须计算的成本

令 a 为接受元素比例。候选的总时间至少要包含：

```text
入口字段提取 / 分派
+ 每个尝试块的输入读取、域检查、量化、整数归约
+ 端点检查、编码回写
+ 每个失败块从原入口开始的完整原序重放
+ 与基线相同的最终 finite 判断和必要全域回退
```

忽略共同部分后，一个必要的收益条件是：

`尝试块与提交证书的成本 < 被替换的原序部分成本`。

对于固定锚点实现，每个尝试项还要做一次 FP add；失败块又再做原序 add。因此收益不是少算 FP 操作，而是希望独立 FP add 和可结合整数 sum 的吞吐足以抵消额外检查、编码和重放。若编译器仍生成逐项标量取位/判断，结构正确并不会自动带来速度。

一般两 parity 路线更难：若摘要仍以标量 fold 构建，原来的浮点依赖被更长的整数依赖替换。形式上 O(log B) 的树深度不等于 Lean 实际并行执行。

### 9.2 CPU 代理设置

文件：`diagnostics/native_cost_probe.c`。

- 本轮宿主：x86_64，GCC 13.3.0。
- 独立命令：`cc -O3 -std=c11 -fno-fast-math -ffp-contract=off ...`。
- 未改变官方 Lean 编译参数；没有 `-ffast-math`、FMA 或浮点归约重结合。
- 每类 100 条 fresh synthetic 向量、n=1000；B=32；每轮 400 次重复；5 轮交替测量顺序。
- 数据创建在计时外；**候选域检查、量化、证书、失败块重放都在计时内**。不缓存量化结果或答案。
- 每个候选先逐位核对这 300 条向量与 C 原生顺序循环，零差异。
- 代理没有 Lean 对象表示/分配开销，也没有执行 FloatLib 的非有限 payload 回退；原生和候选均未另外计入共同的终端 finite 守卫。所测三类均保持有限。因此它不能被称为完整目标 Kernel 时间。
- 没有固定 CPU 频率/亲和性。小幅差异不作结论，ReLU 的倍数退化则五轮方向一致。

### 9.3 最终同轮结果

下表时间为每元素 ns 的中位数；耗时倍数为**逐轮候选/原生比值的中位数**，不是两列中位数的商。

| ReLU 实现 | ns/元素，中位数 | 对原生耗时比，中位数 |
|---|---:|---:|
| 原生 ordered Float32 C 循环 | 0.877974 | 1.000 |
| odd 条件 + 有分支整数移位量化 | 4.819023 | 5.393543 |
| 去掉逐项零值分支的整数移位量化 | 3.783197 | 4.546651 |
| **固定锚点独立 FP add 量化** | **1.995628** | **2.279020** |

作为诊断对照，原序 skip-zero 版本中位数为 3.550827 ns/元素；这里跳零的随机分支也不划算。它不是正式候选或新的优化结论。

固定锚点相对于原生的五轮 ReLU 比值分别为：

`2.279020, 2.265433, 2.094887, 2.326716, 2.437765`。

dense 和 wide 中主要走拒绝/回退，波动较大，不把偶然接近 1 或略低于 1 解释成加速。最终 CSV 和机器码均随包提供；当前 GCC 产物在锚点快路里观察到的是标量 `addss`，没有 `addps`。这解释了为什么“有并行空间”还没有兑现，但不能保证换成 Lean 会自动产生向量化。

**研究判断：停止扩展这三种标量 C 版本。** 不能把 2.279× 换算成 Lean 的速度；也不能拿已经排除某一实现开销的次数，冒充整个数学路线被证明不可能。

## 10. 与固定 Lean / FloatLib 定理的真实桥接

以下条目都来自指定提交，完整路径、行号和导入图见 `appendices/source_bridge.md`。不是依据当前主分支猜名称。

| 桥接层 | 固定版本中真实存在的名称 | 本轮用途 |
|---|---|---|
| 合同执行到规格 | `FloatLib.Floats.ExecFloat.Proof.add_eq_spec` | 将合同 `ExecFloat.add` 改写到其 spec |
| configured codec | `FloatLib.Floats.ExecFloat.ModelCodec.decode_liftBinary` | 从 configured 值进入 descriptor model |
| model 执行到规格 | `FloatLib.Floats.Formats.BinaryInterchange.Model.Proof.add_eq_spec` | 接 `Model.Spec.add` |
| 有限加法到实数舍入 | `Model.toReal_add_eq_roundAt` | 得到精确实数加法后一次 `roundAt` |
| 符号范围推出有限性 | `Model.isFinite_add_of_abs_toReal_add_le_posMaxFinite` | 不执行一遍参考 add 就证明不会 overflow |
| dyadic 舍入 | `Model.roundAt_dyadic_eq` | 把 `roundAt` 化到目标 exponent 上的整数 RN |
| normal 格距 | `Model.targetExponent_eq_normal` | 确定当前 binade 的 q |
| 商余数舍入 | `Model.nearestEven_div_pow2_eq_roundShiftRightEven`、`Numerics.roundQuotientEven_eq_quotient_add` | 对接无 midpoint 与整数增量 |
| 负值镜像 | `Model.roundAt_neg` | 同向负数块的对称性 |
| **非零有限实值相等恢复全位等式** | **`Model.eq_of_toReal_eq_of_nonzero`** | 关键：不是只证明数值近似或实值相等 |
| 返回 configured 值 | `FloatLib.Floats.ExecFloat.Binary.toModel_inj` | 恢复 `Binary32` 本身的等式 |

其中最重要的源码入口：

- [Arithmetic/Semantics.lean](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Arithmetic/Semantics.lean#L37-L88)。
- [Rounding/Proof.lean](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Rounding/Proof.lean#L252-L305)。
- [Conversion/Text/Representation.lean](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Conversion/Text/Representation.lean#L78-L108)。
- [Configured/Instances.lean](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Configured/Instances.lean#L67-L70)。

这些模块沿 `ContractTensor→Contract→FloatLib` 的公开 import 可达；这已经从源码导入图核对，但还没有实际 elaboration。

### 10.1 两个容易误用的接口

1. `ExecFloat.Binary.toModel_add` 虽存在，但针对显式 rounding 参数的 `ExecFloat.Binary.add`；不能直接当成合同 `ExecFloat.add` 的同名桥。
2. Lean v4.34.0 的 `Float32.ofBits` 逻辑模型会经过 pack/unpack，NaN 会规范化。不能假定它对任意 NaN payload 与 `toBits` 无条件互逆。快路只使用已证明有限的值；非有限 payload 由原实现负责。

Lean 版本源码：[src/Init/Data/Float/Float32.lean](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Float/Float32.lean)；[src/Init/Data/Float/Model/Float32.lean](https://github.com/leanprover/lean4/blob/v4.34.0/src/Init/Data/Float/Model/Float32.lean)。

### 10.2 真正尚缺的 Lean 工作

核心未完成项明确为：

1. 证明固定 q 网格舍入与 `Model.roundAt` 一致；**候选恰 U** 的 exponent 切换必须独立处理。
2. 从 word guard 推出有效指数、odd、同号和范围条件，特别是 subnormal 的 Eeff=1。
3. 锚点 `H+y` 的 raw bits 差等于 δ；需要 normal 编码的有序格点关系。
4. UInt32 归约无回绕、raw bits 加 D 的正确性、端点 guard soundness。
5. 块级模拟到任意长度 Vector 的原索引 fold；保留原始入口供失败重放。
6. 接入既有 native finite 等式/末尾守卫，完成真正的 `SumObligation`。
7. 在固定环境运行编译和 `#print axioms`，只允许 `propext`、`Classical.choice`、`Quot.sound`；最终仅 `import ContractTensor` 且 `Kernel.lean≤256000` 字节。

最后一项的完整 Kernel 大小、证明耗时和允许公理集合都是 **UNKNOWN**。两份小草稿本身很小，不等于完整 Kernel 已满足限制。

## 11. 已交付的第一个可运行诊断与 Lean 草稿

### 11.1 零依赖 Python 诊断

从 ZIP 解压后的根目录运行：

```bash
python3 diagnostics/ordered_sum_diag.py --vectors 100 --length 1000 --seed 927401 --output results/diagnostics.json
```

仅 Python 标准库。种子是本次合成实验的复现参数，候选函数不读取种子、类别名或缓存答案；不是官方 benchmark seed。

它包含：

- 精确 finite binary32 编解码与 RN-even add，处理 gradual subnormal 和 signed zero。
- 所有主反例。
- 两 parity/前缀摘要、一般块 guard、odd 单调块、固定锚点块。
- 5,000 次三摘要结合律试验，每次对 6 个整数入口比较结果及所有前缀界。
- 20,000 个自造浮点块：一般摘要接受 11,541 块；单调无 midpoint 接受 2,225 块；odd 直接量化接受 689 块；锚点接受 727 块；所有接受结果零位差。
- 三类各 100,000 项的覆盖实验和输入词 SHA256。
- 另一套宿主加法 sanity check；它不参与参考定义，只用于检查整数 oracle 是否有明显实现错误。

NaN payload 的参考运算未在 Python 中重写。诊断对若干 Inf/NaN 位型检查的是**快路拒绝**，不声称执行了全 payload 的 FloatLib 回退验证。

独立数学检查另有 `verify_transition.py` 与 `verify_anchor_quantization.py`：后者执行 5,000 块、160,140 项，其中 2,988 项为 subnormal；3,692 个块通过终点证书，已接受块零位差。这些是人为构造的数学覆盖数据，不是目标分布成功率。

### 11.2 本地成本诊断

```bash
cc -O3 -std=c11 -fno-fast-math -ffp-contract=off diagnostics/native_cost_probe.c -o /tmp/r2w01_cost_probe
/tmp/r2w01_cost_probe 400
```

该命令不会编译或修改比赛仓库；只运行自造 C 探针。本轮产物的最终 CSV、汇总 JSON、初始负结果 CSV 和机器码均附在 `results/`。不同机器复跑可能得到不同时间。

### 11.3 Lean 草稿

- `lean/OddNoTieDraft.lean`：纯自然数 odd/mod/2 的幂无 midpoint 证明草稿。
- `lean/BridgeDraft.lean`：真实公开定理的 codec 桥、有限非零位等式、fold simulation、guard+fallback 的 obligation 胶水。

两者都只 `import ContractTensor`，没有新增 `unsafe`、`extern`、`axiom`、`native_decide` 或占位证明。**但两者均未真实编译**；BridgeDraft 把未完成的格点/证书事实显式作为参数，不能把这些参数视为已证结果，也不能拿它冒充可提交的 Kernel。

在已有固定环境中，第一项检查应是：

```bash
lake env lean path/to/OddNoTieDraft.lean
lake env lean path/to/BridgeDraft.lean
```

不更改 `lean-toolchain`、lake 依赖或官方 bench。当前会话未执行这两个命令，因为没有相应工具链。

## 12. 一个可证伪的最小后续实验与停止条件

本轮已经完成首轮有限诊断及 CPU 筛选；不建议直接开始整个形式化 Kernel。若开发者仍要检验实际 Lean 是否有不同成本结构，只做下面这个有边界的小实验。

**唯一实验：** 在现有 Lean 4.34.0 工具链和固定依赖里，用单 import 的独立诊断文件实现 **B=16 和 B=32 的固定锚点块**；比较同一表示路径上的 native 原序循环。输入仍为多个独立合成向量，所有 guard、量化、编码和失败块重放放进候选调用；保留同一个末尾 finite 条件。无需正式提交，也不修改官方 bench/gate。先比较结果，再计时。

记录可直接作决策的内容：

1. 全部输出 bits，包含最强 ReLU 反例、midpoint、Es=2 subnormal、恰 U、U 两侧、NaN/Inf/±0 和任意尾长。
2. 总调用时间与接受/拒绝/重放项数；不得只报接受块内核时间。
3. 生成 C/机器码中的量化循环是否仍为标量、是否出现临时对象分配；不能通过添加 extern/SIMD 内建或改变选项来绕开合同。
4. 对 dense/wide 的分派退化。不能只看 ReLU 胜出的子集。

**停止条件：**

- 任意被接受块与参考位差不为 0，立即停止该 guard；先修正命题，不靠扩充测试掩盖。
- 若必须依赖不允许的公理、unsafe、extern、额外 import、改变编译选项/固定依赖，停止该实现。
- 如果量化/证书全成本在真实 Lean ReLU 路径仍不能稳定胜 native，就不启动剩余大证明。
- 可以把“重复测量至少约 5% 的净优势，且总体未被 dense/wide 退化抵消”作为**本项目投入筛选阈值**；这不是官方验收标准。边际变化落在噪声内时按没有建立收益处理。
- 即便小诊断通过，也必须完成 `SumObligation`、公理审计和原 bench 的真实测量，才能宣称目标性能突破。

对一般双 parity、跨 binade 分区、预测修正和 bmm，本轮没有新的投入证据，保持停止。缺少的是可兑现的低成本执行，不是再列一批源码微优化。

## 13. 最终状态与可复用产出

本轮留下三项可复用的技术资产：

1. **一个否定“严格逐位就完全不能重组”的具体构造**：转移摘要的结合律，以及 odd 同向域上的合法整数 reduction。
2. **一个不偷换目标的证明路线**：保留逐次舍入丢弃量；用所有前缀/单调证书维持真实 binary32；有限非零实值等式通过现成公开定理恢复完整位型。
3. **一个会阻止继续盲目投入的成本负结果**：直接移位、去零分支、固定锚点三个完整候选代理都没胜出，最好的也比原生慢约 2.28 倍。

状态：**数学结构可行；有限实验通过；当前 CPU 实现不值得晋升；Lean 编译、公理集合、全域 gate、目标速度均未建立。**

## 14. 来源与随包文件

固定版本源文件清单及内容哈希见 `sources_manifest.json`；主要链接见 `SOURCES.md`；逐个定理的长表与源码导入图见 `appendices/source_bridge.md`。核心路线推导、反例、统计与停止条件已完整写在本报告，不需要打开附录才能理解结论。

ZIP 包含本报告、两份 Lean 草稿、所有自造诊断源码、有限实验 JSON、CPU CSV 与汇总、相关审查附录、来源清单和 `SHA256SUMS.txt`。没有可执行二进制、下载的大工具链、私有输入或正式参赛提交。
