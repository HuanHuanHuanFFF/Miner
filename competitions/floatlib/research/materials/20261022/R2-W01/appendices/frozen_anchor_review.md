# Fixed native anchor 量化：独立快审

## 结论

**在给定 guard 下，量化恒等式成立；它确实把原来串行依赖于 accumulator 的浮点加法，换成对同一个固定 H 的独立加法。** 这比单纯改写整数代码有新的性能机制：各项 `RN32(H+x)` 可以并行发射或 SIMD，再归约整数增量。是否胜过 native 原序链仍需全成本测量；本快审没有任何性能测量或 Lean 编译结果。

首试可保持已有窄 guard：正 normal accumulator 的 exponent field `132≤Es≤148`；输入为 +0，或正 normal、odd mantissa、`Ex≤Es−2`；块长 `B≤64`。若希望支持 subnormal，要求 `Es≥3` 即可沿用下面论证；不能不加条件把 exponent field 0 当作正常数的有效指数。

## 1. 证明锚点量化等于需要的 δ

设 `E=Es−127`、`q=2^(E−23)`、`L=2^23`，固定锚点 `H=Lq=2^E`，即原始 bits `A=Es<<23`。

对于非零正 normal 输入，设 `x=m·2^(Ex−150)`，`m∈[2^23,2^24)` 为奇数，`d=Es−Ex≥2`。于是

`x/q=m/2^d`。

halfway 的充要条件是 `m mod 2^d=2^(d−1)`。前者奇、后者偶，所以不可能 halfway。令

`δ=RN_integer(m/2^d)`。

由于 `Ex≤Es−2`，有 `0≤x<H/2`。因此

`H≤H+x<3H/2`，且 `H≤RN32(H+x)≤3H/2<2H`。

整个 anchor 加法的结果保持在同一正常 binade 内，无下边界、上边界或 overflow 问题。该 binade 的可表示值依次相差 q、编码依次加 1，故

`RN32(H+x)=(L+δ)q`

`rawBits(RN32(H+x))−A=δ`。

H 的 significand 为偶数，但没有 midpoint，因此其 parity 不会造成入口信息丢失。对于 +0，上述等式直接给 δ=0。

对真正 accumulator `s=kq`，只要该块候选保持在有效 binade 区域，同样无 midpoint 的每步增量就是这个 δ，与 k 无关。非负性加上 `k+Σδ≤2^24` 的端点证书保证全体候选前缀安全；这一步仍不可省略。锚点加法本身安全，并不意味着实际 accumulator 加完整个块也不跨 binade。

## 2. 两个必须保留的反例

### 去掉 odd/no-midpoint 条件会失败

取 H=8，q=`2^-20`，输入 `x=1+2^-21`，bits `0x3f800004`。该 x 的 Ex=127，满足 `Ex≤Es−2=128`，但 mantissa 为偶数，`x/q=2^20+1/2`。

- `RN(H+x)=9`，anchor 提取 `δ=2^20`。
- 真正 accumulator 若是 `8+q`，bits `0x41000001`，其加 x 应得到 `9+2q`，bits `0x41100002`。
- anchor 增量给出的却是 `9+q`，bits `0x41100001`。

因此“加一个固定大常数再取 bits 差”不能在存在 tie 时自动保持任意入口 parity。

### Subnormal 在 Es=2 产生真正反例

令 H 的 bits 为 `0x01000000`，即最小正常 binade 的下一 binade，`Es=2`，q=`2^-148`。输入最小正 subnormal `x=0x00000001=2^-149=q/2`。

它满足正数、raw odd、`Ex=0≤Es−2=0`，却是 midpoint：

- `RN(H+x)` 的 bits 仍是 `0x01000000`，anchor δ=0。
- 真正入口 `s=0x01000001` 加 x，应到 `0x01000002`。
- 候选却留在 `0x01000001`。

所以仅有 encoded exponent 差的 guard 对 subnormal 不充分。其正确有效表示是 `x=f·2^-149`，故 `x/q=f/2^(Es−1)`。当 Es≥3 且 f odd，分母指数至少 2，才与正常数一样严格排除 midpoint。对于原计划 Es≥132 的大锚点，全部 subnormal 都远小于半 q，不会影响结果；允许它们在数学上安全，但第一版 normal-only 可降低证明分支数。

## 3. raw 上界与位运算细节

当 `Es≥3` 且 `Es≤253`，正 raw 编码满足

`w≤((Es−1)<<23)−1`

等价于 exponent field `Ex≤Es−2`，同时排除了负数、Inf 和 NaN，因为这个上界低于 sign bit。再要求 `w=0` 或 mantissa odd；如果暂不支持 subnormal，非零时再要求 `w≥0x00800000`。

应先保证 Es 的范围，再构建上述 unsigned 上界。Es=1 时 `(Es−1)<<23` 为 0，减 1 会回绕成 `0xffffffff`，把错误输入全部放进来。Es=0 也不能被当作正常锚点。Es=254 的 anchor 自身仍安全，但块出口可能触碰 overflow；第一版沿用 `Es≤253`，避免把该分支混进本证书。

H 必须由原始 bits 构造，不是把整数 A 数值转换成 Float32。RN32 必须是 binary32 round-to-nearest-even；保持冻结锚点、禁用会重结合成实数总和的 fast-math。这里不需要 FMA。

## 4. 模 2^32 归约合法，但需要事先上界

因为 `0≤x<H/2`，有 `0≤δ≤2^22`，上界允许取等号：例如 x 极接近 H/2 时，会舍到恰 H/2 的整数增量。

对 B≤64，数学总增量 `D=Σδ≤2^28<2^32`。每项 `w_i=A+δ_i`，故在 `Z/(2^32)` 中

`(Σw_i−B·A) mod 2^32 = D mod 2^32 = D`。

因此先对 raw bits 做 unsigned 归约、再减 `B·A` 是合法的。中间回绕可以存在，证明方式是先建立模等式，再用 D 的先验范围恢复自然数等式。C 需使用 `uint32_t` 或定义了回绕的 SIMD 整数指令；不能让 signed integer overflow 参与。部分尾块必须用实际处理的项数 B；若跳过零项，就不能仍减去包含那些项的 B·A。逐项先减 A 则没有这一计数陷阱。

**不能仅凭最终 residue 很小就相信没有回绕。** 反例取 B=1024，每项 x 是 Ex=Es−2 的最大有限数，mantissa `2^24−1` 为奇数，各项 δ 恰为 `2^22`。则真实 D=`2^32`，模归约给 0，端点检查会误以为 accumulator 没变。B≤64 的先验界正是在排除这个问题。

## 5. 性能解释的边界

这个变体省掉每项的变量整数移位，把 `RN32(H+x)` 的输入依赖限制在固定 H 与 x；多个加法互不等待前一项结果。其数学目标仍是逐次 RN 的各次整数增量，整数归约并未把原输入的浮点求和重结合。因此它有值得单独验证的 ILP/SIMD 机制。

全成本仍包含 raw guard、odd/zero 判定、bits 转换、整数归约、端点证书、块边界锚点更新和失败块重放。不能用无 guard 的 `addps` 吞吐率替代这些成本，也不能把 C 向量化结果直接换算成 Lean 性能。通过本快审只表示等价性路径成立；要声称胜出，仍须同路径完整 guard 的比特校验和实际计时。

本文件只依据本轮新任务中的方案和自造算例推导；未读取旧资料，未提交或安装任何内容。
