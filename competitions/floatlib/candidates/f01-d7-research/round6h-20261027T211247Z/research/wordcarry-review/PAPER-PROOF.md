# 初始 leading bit 与隐式位加法打包：独立纸面核验

R22 A；本阶段首个恢复时钟2026-10-28 00:47:32 UTC，15分钟上限01:02:32，共同截止03:12:47不变。只读D运行体和历史，不读取root的独立验算论证，不改D源/公共证明/CI。本文是全域代数论证，**不是Lean验收**。

核验精确D `development-wordcarry/Runtime.lean.inc`，SHA **5806bb2591dccff00d59b6720360f4c74a1082d4899bf73e4180dfff418e4b2b**，1166B。旧参照fa652的`R19BiasBase.R19DirectBias.normalCore`；两个biased分支完全相同，变化只有leading bit与最终pack。成本UNKNOWN。

令B=2^23、H=2^47=2B^2，a,b∈[B,2B−1]，P=a*b。故

`B^2 ≤ P ≤ (2B−1)^2 = 2^48−2^25+1 = 281474943156225`。

令h=P div H∈{0,1}、k=23+h、ε=(P div 2^k) mod2∈{0,1}，T=P+(2^(k−1)−1)+ε，Q=T div2^k。旧实现h'=T divH、q'=T div2^(23+h')、E'=S−127+h'，旧无符号幅值为`(E'<<23) OR(q'−B)`。新幅值为`((S−128+h)<<23)+Q`。以下固定128≤S≤380。

## 三个穷尽情形

1. **h=0且T<H。** B^2≤T<H，故h'=0且B≤Q≤2B−1，q'=Q。旧fraction Q−B<B，与E'的指数位不相交。因此旧OR等于加法，幅值是`(S−127)*B+(Q−B)=(S−128)*B+Q`，即新式。

2. **h=0且T≥H。** P≤H−1且偏置≤B/2，故`H≤T≤H+B/2−1<H+B`。所以h'=1，`Q=T divB=2B`恰好，而`q'=T div(2B)=B`。旧fraction为0，幅值`(S−126)*B`；新式`(S−128)*B+2B`相同。这里**不能截断或掩掉Q的隐式位，也不能把最后的加法换为OR**；该额外一位就是指数carry。

3. **h=1。** H≤P且偏置≤B，故`H≤T≤2^48−3B+1<2^48=2H`，从而h'=1、q'=Q，且`B≤Q≤2B−2`。最后这个整数上界来自`(2^48−3B+1) div(2B)=2B−2`；真实乘积上界确实排除Q=2^24。旧幅值`(S−126)*B+(Q−B)=(S−127)*B+Q`，等于新式。

这三个情形覆盖所有24位normal significand乘积，不依赖有限枚举，也不另证RNE：两式共享同一个T，证明是对旧normalCore的精确改写。

实际可把等式接口做得更小：对任意UInt32 u/v，mask再OR隐式位已无条件给出a,b的上述范围。因此`new.normalCore S u v = old.normalCore S u v`本身只需S.toNat∈[128,380]，无需另外传原u/v normal前提；原输入normal条件留在已有guard正确性。这个结论尚未写成Lean源。

## 机器字与符号边界

- a,b≤2^24−1，乘积<2^48<2^64；T≤2^48−3B+1<2^48。UInt64乘法和两次偏置相加没有回卷；shift均23或24，旧shift也23或24，不触发64位模shift异常。
- Q≤2B，q'≤2B−1且q'≥B；转UInt32和旧q'−B均精确无回卷。
- 新e=S−128+h∈[0,253]，所以减法、加h、左移23位均精确。新幅值小于2^31：h0最大 `(252B)+2B=254B`；h1最大`253B+(2B−2)=255B−2<256B=2^31`。最后32位加法不会回卷，也不会进入符号位。
- 旧E'=S−127+h'∈[1,254]，fraction∈[0,B−1]，OR=不相交字段相加，幅值同样<2^31。`(u XOR v) AND 0x80000000`只为0或2^31，与两边相等幅值不相交。保留原最终OR即可逐bit相等。
- 实际guard的eu/ev和S范围、原fallback保持原样。这里不扩大S128..380，不外推到subnormal/overflow/special原输入；这些仍走旧fallback。要变成公共正确性，仍需精确旧源的真实gate与新word等式的typing/replay/公理验收。

## 旧接口与历史范围

旧fa652已经写有`R19PostBias.biased_bounds`、`normalized_quotient`、`R19DirectBiasWord.biased_sum_nat`、`R19BiasShape.high_nat`和`normalCore_eq_roundP`等尝试，可在D真实typing通过后复用；**fa652旧public未通过**，不能称已验根。R19 quotient-only014acd曾独立typecheck，不覆盖完整公共端点。当前88cdf fullgate由D Sol负责，不重复实现。

本次限定Kernel.lean/lean.inc/Markdown文本检索未找到另一个既有MUL运行体同时使用初始P>>>47及`((S−128+h)<<23)+Q`；命中的是本轮5806。不是穷尽新颖性证明。旧DirectBias7489四block成本未见稳定收益、Jam b271 whole.998885/p05−.010815以及本轮inline控制波动均保留；它们不等于这个精确pack改写已测失败。成本仍由D完整caller决定，不把少一步依赖自动当加速。

最小判别：真实输出先含低分支跨位P=H−2（a=B+1,b=2B−2）、两个tie parity、Pmax以及S128/380、双符号；随后检查actual caller是否确实以P的leading bit而非biased T决定shift，最后依赖链使用加法而无额外normalize/fraction mask。完整成本包括原guard和cold fallback。未要求新大证明或CI。
