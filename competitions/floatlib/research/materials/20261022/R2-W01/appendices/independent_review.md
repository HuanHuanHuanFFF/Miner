# FloatLib R2-W01：独立路线反驳与可证伪建议

## 判断

**最值得做一次全成本实验的是：正数 ReLU 的固定 binade、无 midpoint、整数增量块；当前只能判定数学上可行，不能判定能胜过既有 native Float32 原序基线。** 一般两状态奇偶摘要有真正的结构，不应被“浮点不结合”一句否定；但它比 ReLU 特化多维护前缀界和状态，性能机会更差。精确总和后末轮、通用 compensated/EFT 后廉价修正，均没有解决目标是逐次原序 RN 这一核心问题。

本审查只使用任务消息、指定公开 pinned 仓库和自造例。未读取旧会话、旧项目或私有附件，未安装工具链，未构造参赛提交。正式目标以 `ContractTensor.sumSpec` 为准：从 +0，按索引顺序做 `ExecFloat.add`，所有长度和所有 bit pattern 都必须一致。[S1] 已知 native Float32 原序路径与末尾 finite guard 是比较基线，本报告不把它作为发现。

## 1. 先给反例

以下均由本目录 `check_examples.py` 独立复核。它用任意精度整数表示精确值乘以 `2^149`，每次加法后自行做 ties-to-even，不调用项目实现。它是有限数算术检查器，不是 FloatLib 全 NaN oracle，也不是 Lean 证明。

### 1.1 连实际 ReLU 非零位型都满足的反例

取 `h = 2^-20`，`s = 8 + h`，`a = 1 + 3·2^-23 = 1 + 3h/8`。

| 数量 | 原值 | bits |
|---|---|---|
| s | `8 + 2^-20` | `0x41000001` |
| a，两次 | `1 + 3·2^-23` | `0x3f800003` |
| 原序 `[s,a,a]` 的结果 | `10 + h` | `0x41200001` |
| 原序 `[a,a,s]` 的结果 | `10 + 2h` | `0x41200002` |
| 实数总和末轮 RN | `RN(10 + 7h/4) = 10 + 2h` | `0x41200002` |

原序第一条路径始终在 `[8,16)`。两次 `a/h = q + 3/8`，且同一个 `q = 2^20`，均严格低于 midpoint。因此各次整数增量恰为 `δ=q`，每次都丢弃 `3h/8`；起始多出的 `h` 保留下来。末轮实数和却把两次丢失的部分合成 `3h/4`，跨过最终 midpoint。另一排列先算 `a+a = 2+3·2^-22`，这一步恰好可表示，再加 `s` 得到后一个结果。

三个输入都是正 normal、biased exponent 在 124..130、mantissa 为奇数，符合 pinned ReLU 生成器的非零结构。[S2] 加 997 个 +0 即得到长度 1000 的反例。相同 multiset、精确总和、绝对值和、指数直方图都相同，却目标不同。故任何只保存这些无序摘要的修正器都不充分。这不排除保留顺序信息的紧凑状态摘要。

### 1.2 midpoint 的增量不能独立于入口奇偶

仍取 `h=2^-20`，`x=1+2^-21`，bits `0x3f800004`，则 `x/h=2^20+1/2`。

| 入口 | 真正 RN 结果 | 把 x 独立舍入为整数增量后的错误结果 |
|---|---|---|
| `8`，bits `0x41000000`，k 偶 | `9`，`0x41100000` | 此行碰巧相同 |
| `8+h`，bits `0x41000001`，k 奇 | `9+2h`，`0x41100002` | `9+h`，`0x41100001` |

入口只差 1 ulp，出口可差 2 ulp。预测器不能把初始 1 ulp 不确定性当作永远不扩大的误差，也不能以小的实数误差替代正确的 tie parity。这个 x 的 mantissa 为偶数，因此会被下文 odd-mantissa guard 拒绝。

### 1.3 signed 数据的端点界不够

固定入口 binade 的整数区间记为 `L=2^23`、`U=2^24`。下表中的“候选”把所有舍入都强行放在入口的均匀 h 网格上。

| 场景 | 入口 bits；后续输入 bits | 候选 k 轨迹 | 真正结果 / 候选结果 |
|---|---|---|---|
| 在下边界错误使用均匀网格 | `0x3f800000`; `[0xb3400000]` | `[L,L]` | `0x3f7fffff` / `0x3f800000` |
| 下方离开再回来 | `0x3f800001`; `[0xb4300000,0x34c00000]` | `[L+1,L,L+3]` | `0x3f800002` / `0x3f800003` |
| 上方离开再回来 | `0x3fffffff`; `[0x34800000,0xb5000000]` | `[U-1,U+1,U-3]` | `0x3ffffffc` / `0x3ffffffd` |

这些值均在任务 wide 指数域内。第一行是 `1 + (-3·2^-26)`：1 以下的间距是 h/2，真实舍入为 `1-h/2`，均匀 h 网格却舍到 1。后二行的最终候选都回到安全区间；只检最终值仍会误放。对 signed 路线，前缀 min/max 或充分保守的幅度界有实质必要。

### 1.4 边界条件不是装饰

| 输入 bits | 逐次原序结果 | 排除的错误简化 |
|---|---|---|
| `[0x00800000,0x807fffff]` | `0x00000001`，最小正 subnormal | flush-to-zero、忽略 normal/subnormal 接缝 |
| `[0x7f7fffff,0x7f7fffff,0xff7fffff]` | `0x7f800000`，+Inf | 先实数求和再末轮会得到最大有限数 |
| `[0x80000000,0x80000000]`，仍从规定 +0 开始 | `0x00000000`，+0 | 返回末项、随意保留 -0 符号 |

NaN 不在本有限数检查器内。公开 FloatLib 说明其 NaN 策略保留并 quiet payload，而 Lean unpacked model 只有单一 NaN；因此只证明实数语义或普通 `Float32 ==` 不足以证明位级一致。[S3] 本文候选用运行时正有限域 guard 排除这类输入，失败走已经正确的原序实现。

## 2. 固定 binade 的确存在小状态模型

令正常正累加器 `s=k·h`，其中 `h=2^(E-23)`、`L≤k<U`。把非负输入写成 `x/h=q+r`，`q` 为整数、`0≤r<1`。在候选舍入值处于当前均匀网格有效区域的条件下：

`k' = k + q + [r>1/2] + [r=1/2 且 (k+q) 为奇数]`。

非 tie 时，增量完全独立于 k。tie 时，只依赖 k 的一个 parity bit，且输出 k' 必为偶数。

### 2.1 一般两状态摘要

对一块记录 `D[0],D[1]`，表示入口奇偶为 p 时的总增量。若先执行 A 再执行 B：

`pA=(p+D_A[p]) mod 2`

`D_AB[p]=D_A[p]+D_B[pA]`。

这就是函数复合，因此可以结合。它保存原来的舍入顺序，允许重组的是摘要计算，不是原浮点加法。不能据“不结合”证明不存在这种加速。

对 signed 块再存每条入口 parity 路径的前缀偏移 `lo[p],hi[p]`（包含空前缀 0）。组合为：

`lo_AB[p]=min(lo_A[p],D_A[p]+lo_B[pA])`

`hi_AB[p]=max(hi_A[p],D_A[p]+hi_B[pA])`。

在入口 exponent field 1..253 且所有候选 prefix 在 `[L+1,U]` 时，均匀网格的 RN 选择与真实浮点 RN 一致。拒绝 L 是为了避开下一较低 binade 的半间距；允许恰 U 是安全的，因为均匀网格舍到 U 的区间包含在真实 U 的舍入 cell 里。exponent 254 需要单独处理 overflow，第一版直接拒绝最清楚。首个正常 binade 下方其实同为 subnormal 间距，可放宽，但这不改善目标数据的主成本。

成本障碍在于每块须计算两份增量和两份前缀界；如果只是按每项顺序更新这些状态，形式上更复杂而依赖链仍在。要赢应明确展示独立 lane、树形复合或可优化的分段结果，而非只给一个半群公式。

### 2.2 纯非负数据只需要端点证书

非负 x 对均匀网格的舍入增量 `δ≥0`。若候选端点 `k+D≤U`，则所有候选 prefix 自动落在 `[k,U]⊆[L,U]`。因为真实每步舍入前的精确和也不低于 L，不会遭遇下边界较密网格。可以逐步归纳候选等于原 RN，但运行时只检查一次端点。

因此 **ReLU 不需要运行时维护 lo/hi，也不需要重新算一遍所有 RN 才确认安全**。等于 U 可接受，下一块重新选择 h。跨 binade 的块回退原序计算，然后从新 accumulator 继续。

tie 稀疏时还存在中间方案：非 tie runs 可以独立汇总整数增量；遇到 tie 才使用当前 parity，tie 后 parity 重置为 0。第一版可以直接拒绝含 tie 块。下面实际生成器提供了更强的充分条件。

## 3. 实际 ReLU 输入的 odd mantissa 消掉全部晚段 tie

Pinned `BenchTensor.sumRelu` 的分支是 `w & 1 == 0` 时输出 +0，否则保留 fraction。[S2] 所以非零输入的 mantissa `m=2^23+fraction` 必为奇数。

令块入口 exponent field 为 `es`，输入 exponent field 为 `ex`，`d=es-ex`。则 `x/h=m/2^d`。当 `d≥2`，midpoint 要求 `m mod 2^d=2^(d-1)`；右侧为偶数，左侧因 m 奇必为奇数，矛盾。这个结论是确定性的，不是“小概率碰不到 tie”。

可把首试限制到以下完全可运行时验证的域：

- 块长 `B≤64`。
- 每项是 +0，或正 normal 且 `ex∈[124,130]`、fraction 奇数。
- 入口为正 normal 且 `es∈[132,148]`。

于是每个非零项 `2≤d≤24`，直接计算

`δ = (m + 2^(d-1)) >> d`。

不需要 remainder 比较，不需要 tie parity。由于 m 的低位为 1，sticky 恒为真，half-up 与 ties-even 在该域相同。`δ≤2^22`，所以 `D≤64·2^22=2^28`；`k+D<2^29`，UInt32 不会 wrap，`m+2^(d-1)<2^25` 同样安全。

运行时接受条件可以写成 `D≤0x800000−fraction(acc)`，出口原始 bits 直接是 `accBits+D`。即使恰好到 U，这个整数加法也自动编码到下一指数的 0 fraction，不需重新做 normalization。拒绝则从原块入口对相同输入原序重放。

此 guard 比“实际 benchmark 应该怎样”强：它覆盖任何满足条件的输入，未假定 seed 或样本身份；任意别的长度、NaN、Inf、-0、负数、偶 mantissa、其他指数都由 fallback 保持合同。只有 +0 被作为零项接受，避免第一版引入 signed-zero 支线。

若以后扩域，`d≥25` 的正输入必小于半 ulp，可直接令 δ=0。机器 shift 可能对位数取模，不能未经区分直接执行 `1 << d` 或右移 d。先保留上述小范围，证明与生成代码都更简单。

自造随机检查用了 5000 个长度 32 的块、入口 es 132..140、符合 guard 的正 odd 输入：3551 块通过端点界，1449 块拒绝，0 midpoint，0 位级不一致。这是故意随机选择入口 mantissa 的数学诊断；**不是官方轨迹覆盖率，也不是速度证据**。

## 4. 与两条大路线的比较

| 路线 | 正确性机会 | 主要成本或障碍 | 本次建议 |
|---|---|---|---|
| 证明块内每步精确，然后直接整数总和 | 充分条件可证，但范围窄 | 所有前缀都精确通常失败；逐项检查等于重做工作 | 不作主线 |
| 精确总和 / 更准确总和后末轮 | 算错目标 | §1.1 已在正 odd 域击穿 | 停止 |
| 一般固定 binade 两 parity + 前缀界 | 数学可行，保留原序语义 | 双状态、min/max、移位、转换、边界重放，Lean 优化未知 | 理论备选 |
| ReLU 正 odd、无 tie、端点证书 | 数学可行且验证成本明显更低 | 位提取和 variable shift 仍多于一个 FP add；必须实际计时 | 最有价值的一次实验 |
| 按原序 TwoSum/FastTwoSum 算每次误差 | 可得到真实逐次误差 | 已经执行原 add 依赖链，再加误差提取 | 无直接胜出机制 |
| 对重组/预测轨迹算 EFT，再廉价修正 | 缺少充分证书 | 误差属于另一轨迹；midpoint、跨 binade、取消可改后续决策 | 除非给出具体 correction invariant，否则停止 |

关于“全部精确”证书：若所有 x 和入口都是某格点 `2^q` 的整数倍，且每个精确前缀的整数系数绝对值不超过 `2^24`，则可直接保证可表示。这种整数幅度界可以由总绝对值上界一次验证，不需要每次 RN。然而 dense/ReLU 的最细共同格点可到 `2^-26`，单项范围已有 7 个 binade，1000 项和更大；任意 fraction 不提供大量尾零。“每项本身都是 binary32”绝不意味着这个共同格点上的前缀全部可表示。可放宽为各前缀有足够尾零，但检查成本和通过率都不乐观，且没有提供性能优势的证据。

关于 EFT：TwoSum 通过 6 次浮点运算把一对输入变成舍入和与精确残差；FastTwoSum 在适当输入排序条件下为 3 次。该性质包含渐进下溢情形，但需要遵守相关算法的算术假设，不能扩展到 overflow/NaN。[S4] 对真实顺序每次做 EFT，残差当然属于正确轨迹，原加法已经做完。对改变过的顺序做 EFT，保留的是实数和，§1.1 表明它与本合同仍不同。需要的“廉价修正”应明确给出可检查的不变量，而不是以更准确代替同一位型。

信息论上只可得有限结论：n 个输入一般都要读取；无序摘要不足；不等于必须有 n 次串行硬件 FP add。浮点状态有限，而固定 binade 的 transition 具有二状态压缩，这是反对过强不可能论的具体构造。另一方面，全 binary32 域的 transition 不能直接假定仍具有二状态形式，binade 转换和特殊值都要处理。

## 5. 最小全成本实验与停止条件

不先做完整 Lean 证明。只写一个明确标为诊断的实现，与既有 native 原序基线比较，输入读取和所有 guard 都在被测函数内：

1. 数据用 pinned 生成器按多个 seed 产生长度 1000 的 dense、relu、wide；零分配留在计时外，候选本身不得预缓存已验证的转换结果。
2. native 先行直到入口 es≥132；然后试 B=16、32、64 的上述正 odd 块。失败块完整原序重放；不从错误候选状态恢复。非 ReLU 类必须计入检查后拒绝的成本。
3. 记录总时间、通过项比例、拒绝块数、重放项数、进入快路径前原序项数。包含 flag/domain/odd 检查、位拆装、构建 D、端点判断、转换、fallback。已有 baseline 的末尾 finite guard 保持相同位置与语义。
4. 对每个向量比对完整结果 bits；加入本节反例和结构边界：全零、首项非零、恰 U、U 两侧、偶 mantissa midpoint、负值、subnormal、Inf、NaN、任意长度，后几种确认走 fallback。
5. 如果使用 C 诊断，只把它当作 CPU 成本筛选。最终性能结论必须来自同一 Lean 4.34.0 编译路径、同一容器/硬件和允许依赖；阅读生成 C/机器码确认整数 lane 没被回串行、没有分配意外。C 快不等于 Lean 快。

**停止条件：** 全成本候选在 ReLU 本身未稳定胜 native，就不继续花数周形式化此版本；若只在 ReLU 胜而 dense/wide 检查回退抵消收益，以正式聚合总时间判负；若优势完全来自跳过 +0，单独测试合法的原序跳零诊断基线，区分收益来源。官方 benchmark 是计时类时间之和的比值，并含 harness/checksum 成本，不是三个类简单等权平均。[S5]

仍为 **UNKNOWN** 的事项：Lean 产物能否利用整数 lane 的短依赖链；真实路径中不同块长的总拒绝/重放率；全成本相对 native 的净收益；正式证明是否能在单文件 256000 字节内紧凑接通已有 RN/bit 桥。本独立审查未做 native/C/Lean 性能测量，也没有提交可编译的定理。数学可行性不能升级为性能突破。

### 同轮协作补充：已有一个负面成本探针

主代理在本轮工作中报告了一个 C complete-cost 诊断：朴素含分支的 odd 块版本在 ReLU 上约为 native 的 5.28 倍时间；native 约 0.85 ns/元素、候选约 4.45 ns/元素，原序 skip-zero 诊断约 3.04 ns/元素。主代理观察到的具体风险是约 50% 零值带来的分支成本，并计划仅追加一个 branchless 量化版本来排除这个实现因素。这些数值由主代理提供，本审查未重跑，也不属于 Lean 或正式 benchmark 的性能证据。

这个失败已足以反对“短整数依赖链必然更快”的乐观论断，但不构成数学不可能性，也不能按倍数换算 Lean 性能。一次完整 branchless 变体能分辨可避免的随机分支成本与整数拆位、移位、证书和重放的剩余成本；之后若仍无净收益，就按上述停止条件收束。

## 6. 证据与复现

运行：`python3 check_examples.py`。已运行成功。反例输出保存在 `examples.json`。

- [S1：ContractTensor.lean，指定 commit](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/contract/ContractTensor.lean)：`sumSpec`、`SumObligation`。
- [S2：BenchTensor.lean，同 commit](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/bench/BenchTensor.lean)：三类生成器、sumLen=1000、ReLU 的 LSB 分支。
- [S3：FloatLib AddSub.lean，指定 FloatLib commit](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Arithmetic/LeanModel/AddSub.lean)：有限加法的模型桥、NaN payload 区别；[Spec/Dyadic.lean](https://github.com/lean-dojo/FloatLib/blob/0d91825727839f597fd06b22fdd038ea21480f0c/FloatLib/Floats/Formats/BinaryInterchange/Spec/Dyadic.lean)：精确 dyadic 后 RN 及 exceptional 分支。
- [S4：Rump、Ogita、Oishi，Accurate Floating-Point Summation Part II，作者公开 PDF](https://www.tuhh.de/ti3/paper/rump/RuOgOi08.pdf)：§2，TwoSum、FastTwoSum 及误差自由变换条件。仅引用性质和操作数，不把该论文的高精度求和目标当成本合同。
- [S5：BENCHMARKING.md，指定 commit](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/docs/BENCHMARKING.md)：计时类、headline 聚合、校验与计时边界。

公式、反例、固定 binade 证书和成本判断是本次推导；未声称已由 Lean 验证。
