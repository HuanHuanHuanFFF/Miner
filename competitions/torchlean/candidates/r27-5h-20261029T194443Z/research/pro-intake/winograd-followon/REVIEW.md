# 精确 Winograd：源码审计、数学边界与成本排除

状态：**NOT_COMPILED / native performance UNKNOWN**。这是有限可验证的研究增量，未形成可提交的 Kernel。全输入前提是快域之外继续调用已经正确的 retained 实现；未修改 Contract 的量词、bias、舍入或特殊值语义。

**范围修正：实际冻结600eaaa1／71667B已完成native finish接线；“未接线”仅指原先孤立Runtime片段，不是最终候选bug，也不计作本包新增效果。** 新附件两份builder与冻结请求已静态核查、声明哈希匹配；完整候选逐字节重构及调用数0/1是父控报告，本环境未重复重构。实际请求为source12／normalized_mlp batch8全部三个linear，非早期Mixer绑定；v2已有all-input-invalid整入口回退。详见 `SCOPE_CORRECTION.md`。以下public23成本分析和旧有限模型不自动成为600e的编译／计时证据；宽gap Int终端保持 **UNKNOWN**。

## 1. 证据与源码定位

仅读取本轮冻结附件及上一轮已提供的公开退任 23 / Contract。文件哈希见 `MANIFEST.json`。下述行号指独立提取的 public23 文件；新附件以定义名定位，避免 separator 行号歧义。

| 结论依据 | 源码位置 |
|---|---|
| bias 作为额外的 `oneW*b`，仅最终舍入，之后 ReLU | `ContractExact.lean`，`linearWith` / `linearSpec`，约 65–74 行 |
| limb 差值终端不是全部 dense 热路径 | public23 `YP` 50 行，`YaL` 125 行，`Yn` 143 行，`Yai` 595 行 |
| 原生三字 bias / finish 与 exact-zero sentinel | public23 `YL` 502 行，`YD` 519 行，`ZV` 证明 521 行 |
| 元数据与普通 word fallback | public23 `Yc` 583、`Yk` 590、`YaU` 648 行 |
| packed、稀疏、四行共享权重解码 | public23 `QY6G` 681、`QPI` 695、`QPS` 701、`QPa` 705、`QPa4` 758、`YaV` 865 行 |
| 原先孤立 Runtime 调用仍经 Int；不能外推最终候选 | 旧附件 `WinogradRuntime.lean.inc::linear/total/signed128` |
| 既有600e已接入 native finish，v2另加全输入cache无效回退 | 补充附件 `build_source12_nativefinish.py`、`build_source12_nativefinish_v2.py`、`CURRENT-COST-REQUEST.json` |
| 旧有限计数与旧 signed-product 反例 | 附件两个 JSON；不是本轮原生结果 |

用户新提供的 2.4052×、1.0906× 和六个旧 cell 的 linear/layer 比例，作为动机保留，未独立重测。87.8–93.2% 是三入口插桩时间中的 linear 比例，**不能代入全模型 Amdahl 份额**。43/23 的 0.9072362322 仍是官方链值，不是同机 native 对照。

### 真正被替换的工作

正常 packed dense 的主体已经是 immediate Nat 缓存取值、UInt64 乘法、两字累加，最后 `YL/YD`。四行路径共享 W 读取、mantissa / exponent 解码；稀疏路径只访问 X 非零索引。`YP` 只在 `Yai→Yn→YaL` 的通用 limb 路径出现，例如字路径 guard 不满足或 exact-zero 重放。没有分支计数，不能把 linear 总时间归给乘法或 `YP`。

配对每两项省下一次主体乘法和一次主体累加，却需要四个缓存读／decode、两次交叉相加；宽域还需要两个 abs 与独立符号处理。进入逐输出分支后的 scalar 调度未保留 `QPa4` 的 W 共享；v2的all-input-invalid整入口回退已经绕开该退化，不能将二者混为一谈。缓存 W 后节省解码可能有价值，但这是与 A/B 正在研究的无损缓存传输重叠的收益来源，不能宣称它独立证明了双线性机制。

既有builders已经让600e接受分支先调用 `totalWords→finishWords`，在native终端准入时避免 `hi.toNat<<64`、大Nat→Int与Int finish；这是600e原有机制，不是本包修复。宽gap仍可调用Int fallback，不能把“旧接受调用为0”误读为“整候选没有任何Int终端”。相对已检查public23源码，可绕开其 `YP` 的窄例子仍是：X/W全1，`productIndex=250`，bias的 `126+idx` 为373…377，即biasShift=123…127；public23 `YaU` 跨度大于122而该native finish可接受。此为源码域分析，不是600e/source12实测；发生率 **UNKNOWN**。`n≥2^20` 的public23尺寸快域差异也不构成source12的性能证据。

## 2. 精确数学归约

对每一非零有限 binary32，

\[
x_i=s_i m_i2^{e_i-149},\quad m_i<2^{24},\quad 0\le e_i\le253.
\]

快域 prepare 选自己的行基数 \(\ell_x\)，并验证所有非零项 \(0\le e_i-\ell_x\le8\)。定义整数 \(a_i=s_im_i2^{e_i-\ell_x}\)；权重独立取 \(\ell_w,b_i\)。零项整数值为 0，零的符号单独留给终端规则。

令 \(q=\lfloor n/2\rfloor,t=n\bmod2\)。

\[
C=\sum_{j<q}(a_{2j}+b_{2j+1})(a_{2j+1}+b_{2j}),\quad
S_a=\sum_{j<q}a_{2j}a_{2j+1},\quad S_b=\sum_{j<q}b_{2j}b_{2j+1}.
\]

环恒等式给出

\[
T=C-S_a-S_b+t\,a_{n-1}b_{n-1}=\sum_{i<n}a_ib_i.
\]

奇数尾必须只加一次。`n=0` 由 retained 整入口处理，不允许拿 `n-1` 的 Nat 截断来证明一般尾项。不同 row/weight base **不破坏恒等式**：这些是整数坐标上的 self 项；最终统一乘 \(2^{\ell_x+\ell_w-298}\)，不能把两个 self 项解释成原物理量的平方。

### 位宽：unsigned64 产品，signed128 累加

设 \(A=\max|a_i|,B=\max|b_i|\)，运行时验证 \(A+B<2^{32}\)，并已有 \(A,B<2^{32}\)。

* cross 因子的绝对值小于 \(2^{32}\)，可用 signed64 两补码加法表示。
* cross 产品绝对值小于 \(2^{64}\)，**未必小于 \(2^{63}\)**。当前 `magnitude*x + separate sign + addSigned` 形式是必要的宽域处理。
* self 产品同样只保证 unsigned64；不能未经新 guard 改成 signed63 sign extension。
* `n<2^30` 给出每个 cross/self 前缀绝对值小于 \(2^{93}\)。按实际计算顺序减去两项 self、再加 odd tail 的中间量绝对值小于 \(2^{95}\)，严格在 signed128 内。
* 最终量更小：\(4AB\le(A+B)^2<2^{64}\)，所以直接乘积 \(AB<2^{62}\)，\(|T|\le nAB<2^{92}\)。这也说明该准入域中的原 direct product 本来就很窄。

UInt64 的进位／借位给出模 \(2^{128}\) 的正确和；以上界才允许把模结果唯一还原为数学整数。只证明环恒等式或只核最终量都不够。

固定子域 \(A+B\le3037000499=\lfloor\sqrt{2^{63}-1}\rfloor\) 允许 cross 直接用两补码乘法并 sign extend。本包研究草案只在此 guard 下选择 `crossSigned63`，其他已准入输出保持 unsigned cross；它未接入600e冻结候选，不属于本次新增队列。这个子域覆盖率不能从旧 max-bit 摘要精确得出。

对于两条非零、正常完成 `Yc` 的有效行，metadata span 各不超过 8；若二者都为 8，各自 peak 至少为 \(2^{31}\)，与准入矛盾。因此两 span 和至多 15，通常已经落在原 packed 的乘法位宽范围。全局 `QPS`、bias、`wm≥1`、尺寸等额外条件仍可能使原 packed 未启用；此处不是逐输出 packed 命中的证明。

### 已知 signed63 反例的独立复现

附件原反例而非本轮新发现：

```
X = [36000000, 36000000, 32800000]
W = [35ffffff, 35ffffff, 32800000]
bias = 00000000
A+B = 4294967168 < 2^32
correct = 2d000100
unconditional signed-product = acfffe01
```

它被新阈值排除；当前 unsigned 方案通过。重复到八行不会修复错误版本。

## 3. native finish：bias、shift、zero 与 overflow

令 \(P=\ell_x+\ell_w\)。非零 bias 的正确物理量是 \(s_bm_b2^{idx_b-149}\)。当前 `YL oneW bias` 的系数为 \(2^{23}m_b\)，因此使用

\[
I_b=126+idx_b,\quad L=\min(P,I_b),\quad d=P-L,\quad h=I_b-L,
\]

\[
N=T2^d+s_b(2^{23}m_b)2^h,\quad output=RN_{32}(N2^{L-298}).
\]

接口文本中直接 bias 系数 \(m_b\) 配 `149+idx_b` 也正确。**不能只把代码 126 改为 149**，否则 bias 放大 \(2^{23}\)。模型同时验证了两个系数／index 约定的等价式。

`d≤63,h<128` 时：`top128` 必须先 sign extend；`d=0` 必须独立处理，因为 UInt64 shift 按 64 取模，不能执行 `hi >>> 64` 来代表数学零。当前分支处理正确。非零 d 使用三个 limb 的拼接。实际 \(|T|<2^{92}\)，故 body 项小于 \(2^{155}\)；bias 系数小于 \(2^{47}\)，移位至多 127，bias 项小于 \(2^{174}\)，合量小于 \(2^{175}\)，远小于 signed192 界 \(2^{191}\)。

`YL` 负数采用按位补加延迟 carry `c`；`YD` 必须加回这个 carry 后才能判断 exact zero 和舍入。模型翻译了这些 word 操作并核其 192 位整数等式。`Ybo` 的已公开正确舍入桥在此被视为已有依赖；没有宣称重证其 Lean 实现。

| 边界 | 必须保留的行为 |
|---|---|
| 任一输入／权重／bias 非有限 | v2先检查X；若需进入配对输出分支，再检查W与bias；失败回retained整入口。all-input-invalid先回原入口，由原入口处理W/b特殊值；非有限值不会进入已准入配对 |
| 次正规 | `idx=0,m=frac`；允许本快域，按精确整数一次舍入，无 flush-to-zero |
| bodyShift=63 / 64 | 63 可走 native，64 原补丁回 Int；不能去 guard 后让 shift wrap |
| biasShift=127 / 128 | 127 可走 `YL`，128 原补丁回 Int；这是 guard 边界，不是修改 Contract |
| overflow | 原 `YD/Ybo` 产生相应 ±infinity，再应用原 ReLU；不能饱和成最大有限值 |
| 非零极小总和舍入成 ±0 | `YD` 返回普通 32 位字；不是 sentinel，不能据此原样套 exact-zero 逻辑 |
| 完整精确总和为零 | `YD` 返回 `2^32` sentinel；非 ReLU 需保留符号回放，ReLU 可直接 +0 |
| 维度或 shape 不满足、新 n guard 失败 | retained 整入口；不能把证明限制成“输入一定形状正确” |

### 新反例：cache 不含零符号

`X=[-0,-0],W=[1,1],bias=-0` 的精确 dot 是 -0；把 X 改成 `[+0,+0]`，cache 完全相同，结果为 +0。即便两侧 peak 都非零也不够：`X=[1,+0]`、`W=[-0,-1]`、bias=-0 的所有原产品均为负零，改 W 首项为 +0 会改变终端零符号而不改变 cache。不能从“某个 cross/self 非零”推出原 dot 出现过非零产品。

当 `relu=true`，两种零均变 +0，故已证完整 exact-zero sentinel 可以直接返回 0。这里必须包括 bias；只看 cross 小计或 body 抵消不够。另一安全早出口是：signed128 body 确证为零且 bias 有限非零，则完整结果就是原 bias 字；不需要对齐、Int materialization 或 replay。

### 新反例：全零 metadata 与 Nat 截断

`Yc` 取 `absWord-1` 的 UInt32 最小值。全零行保留 `0xffffffff`，所以 `low=Yk(511)=510`，`high=0`；`high-low` 是 Nat 截断的 0，prepare 有效。故 `valid→low≤high` 是错误证明前提。与全 1 权重（low=125）和 bias=1（index=252）组合，bodyShift=383，原 native finish 回 Int，即便结果只是 bias。

本包未编译研究草案的 `finishZeroBodyOr` 可消除此类回退；尚未计入600e。非 ReLU的零bias留给旧replay。真实非零body的小次正规乘积加bias=1仍可能需要wide fallback，不能用零体规则误处理。若 `Yc` 因USize/数组端点guard返回 `0x01ff00ff`，非零有限元素在prepare的 `e<low` 处被拒绝，全零行仍可通过，证明应覆盖它。这是成本及证明边界，不是已验证的600e正确性bug。

### Int/Nat 与索引接口

prepare 的非零指数差必须先证明 `e≥low` 才能解释 Nat 减法；峰值相加小于 \(2^{33}\)，其 UInt64 guard 不会先溢出。payload 小于 \(2^{33}\)，在所述 64 位 Lean runtime 可为 immediate Nat，但每个 Array Nat 槽仍占一个 word，不能当作 33-bit 紧密打包。

有限正常 metadata 的 low 至多 510，P 至多 1020，转 Int 后的 `P-298` 可为负；不能先在 Nat 中减去 298。源代码采用 Int 减法正确。数组地址、rows*outW 保留 Nat；n<2^30 不自动证明 rows*n 或全部地址可窄化到 UInt32/USize。外部 shape 检查和 public23 自己的索引 fallback 不可删除。

## 4. 完整乘法账与真正 strong 反例

记 R 为行数，O 为输出宽，E 为配对准入输出数，q=K//2,t=K%2，V 为**成功完成 self preparation 的 X 与 W 行数之和**。失效 prepare 在 selfSum 前返回，不能给它们虚构 self 乘法。

在确实进入逐输出分支、每个miss执行K项dense YaU、排除额外exact-zero replay和共同bias项的模型中（不适用于v2已返回retained整入口的分支）：

\[
C_W=Vq+E(q+t)+(RO-E)K,
\quad C_D=ROK,
\quad C_D-C_W=q(E-V).
\]

附件 0.7213/0.6460 采用 V=R+O 的“所有行均付 self 项”保守计数。它们是源码乘法模型，不是实际 native 操作数，更不是 strong 稀疏／分块路径的时间比例。

| 旧 27-cell 汇总 | linear1 | linear2 |
|---|---:|---:|
| 原 dense K 项乘法模型 | 419814 | 419814 |
| 所有行 self preparation 模型 | 20046 | 24750 |
| 连 odd tail / miss 的计数模型 | 302827 | 271190 |
| 相对 dense 模型 | 0.7213361 | 0.6459766 |
| 输出准入比例 | 73.1660% | 84.4156% |
| 按 K 加权准入比例 | 67.0371% | 82.5956% |

以上数值仅从早期附件旧JSON重算，未重放原数组；不是600e/source12完整NMLP三个linear的覆盖统计。JSON不提供bias及exact-zero/native-finish命中率。不能把73.17%与84.42%当作时间覆盖。

如果实际 strong sparse 对每行只做 s 个非零输入产品，并且对应 QPa guard 成立，则均匀 s 的净主体乘法收益为

\[
ROs-C_W
=E(s-(q+t))-(RO-E)(K-s)-Vq.
\]

所以 `s≤ceil(K/2)` 时配对主体无正收益；miss 还会丢掉 sparse skipping。非均匀行把前两项按行求和即可。ReLU 后是否出现这种密度必须在允许的旧输入上计数，不能假设一半非零。

**精确新例：** R=8,K=20,O=40；X 每行 `[1,0,…,0]`，W 每行全 1，bias 全 1。`QPS` 成立、`QPI` 选择 s=1，bias 和 wm 也满足 `QPa`；四行 packed 要求不满足时调用标量 sparse，而非退成 full dense。每个输出为 2，无 exact-zero replay。strong 主体乘法 320，配对 480 次 self +3200 cross=3680，11.5×；连双方320次 bias 为6.25×。这不是“乘法减半”的轻微修正。

**小 batch：** R=1 即使全部准入也比 dense 多 q 次乘法；O=1 对称。K=1 没有成对收益。`RO≤R+O` 的小矩形没有全准入节省；R,O≥2 时只剩2×2，任意部分准入也无节省。因此可在准备前整入口旁路这些形状。此 guard 是成本选择，正确性仍由 retained 负责。

### 乘法以外必须计入的账

| 阶段 | 当前 Winograd 的额外／变化工作 |
|---|---|
| 扫描与元数据 | v2先X有限性、BX、A；若所有A无效则整入口回退，跳过W/b扫描与B准备；否则检查W/b，再构造BW/B。扫描和已构造对象的drop均计入 |
| prepare | 每条有效 X/W 行分配 payload，维护 peak，再遍历 selfSum；无效行可提前退出但已经付扫描／部分构造和 drop |
| 内层 | 600e每对四次decode、两个cross sum、unsigned更新；signed63仅为本包未接入草案。scalar输出循环含row/col Nat除法余数 |
| corrections | 每输出两次 signed128 减法，odd tail 额外产品；self cache 读与闭包／递归的编译效果未知 |
| finish | 非零 bias、宽对齐、existing YD；wide Int helper 与零回放有时再付完整 dot |
| miss | all-input-invalid已有retained整入口，保留原融合；仍进入逐输出分支的miss调用标量YaU，mixed-validity丢稀疏／多行融合风险保留。guard是 `¬A.any valid`，不是所有 `E=0` 情形 |
| 分配／drop | 两侧缓存、Cached 结构、输出数组均计入；约8(R+O)K字节payload槽，对比原 full packed X约16RK，忽略各自其他对象，前者未必更小 |

这些是源级工作账；没有汇编或 native profile，不能报周期，也不能从递归/乘法条数直接推出加速。

## 5. 10% 机会：只能给带前提的界

早期旧两个linear的dense计数合计比为0.6836563，减少31.6344%的“主体产品＋self/miss计数”；它不是600e完整NMLP测量。在 **V=R+O的旧计数模型内**，再额外假设全部走同成本dense产品、热段时间里与该计数成正比的份额为p，目标入口占全模型份额为f，其他变化合计增加全模型时间h，则模型预测为

\[
\Delta_{model}= f\,p\,(1-0.6836563)-h.
\]

这不是对 native 程序的无条件上界，因为实际 V 可能更小，decode、累加、缓存、branch、稀疏与 replay 均改变；它是揭穿“减半必快”的成本假设检查。在这个简化模型里，即使 f=1,h=0，10%降耗也要求 p≥31.61%。实际 f<1、准备或 miss 开销会提高门槛。仅相对 K 项 dense 产品数的一般界是节省至多50%；在“只节省等成本产品、无其他收益”的假设下，10%要求 fp≥0.2，仍不是原生程序的无条件时间界。

若要达到原目标“比 current43 再低10%”，只有在官方链值可用于同一评估链时，目标相对23才是 `0.9*0.9072362322=0.816512609`，即对23约降18.35%；同一理想模型 f=1,h=0 仍要求 p≥58.00%。这只是链值代数，**不是同机性能预测**。现有三入口比例不能给 f，故不能宣布10%已可达或已不可达。

可作明确排除的是：原 sparse 已将每行主体产品压至 ceil(K/2) 或更少；单行／单列；配对总完整时间没有改善；或真正全模型目标入口份额 f<目标降耗，即使删除该入口也不够。不存在这些证据时，把当前方案判死也超出证据。

## 6. 若首测否决，下一条不同路线

转向**有限 ReLU dense 的精确尾界提前结束**。已有整数前缀（必须已包含 bias）为 S，未访问尾和为 D，构造确证上界 U≥|D|。若 `S+U≤0`，则完整精确结果非正，正确舍入再 ReLU 必为+0，可不访问剩余产品，也不做其累加／终端重放。非有限或界不适用就留原实现；非 ReLU 不套此规则。

一个具体界为 `U=Amax * sum_remaining |b_i|`，使用与当前 packed 同一整数尺度；权重 suffix 绝对和的准备、界乘法和检查成本必须计入。不需要浮点近似和 FPsum，也不只是改 carry16 或 cache 格式。`WinogradBridges.lean::nonpositive_tail_certificate` 给出核心整数桥。

上限来源是跳过 dense 的剩余加载、乘法与累加，而非只省 layer 出口。**限制也明确：** 全正产品、尾部大抵消、接近零的前缀可能永不满足门槛；粗 L1 界对随机符号 dense 常很松。没有旧输入上的实际停止位置与完整成本，就没有10%承诺。本轮不为此开新实验窗口或做实现扩张。

## 7. 未闭合证明和工程接口

1. `prepare` 与 raw word、metadata、Array 索引、payload 符号／幅值的全称对应；包括全零 low=510 和 Yc sentinel。
2. `addSigned/subtract/crossSigned63` 的 UInt64 模运算细化、所有前缀 signed128 界，以及 Array getter / odd tail 索引证明。
3. `totalWords` continuation 与原 Int 归约的等价；cache self 项跨输出共享但每行尺度独立。
4. `finishWords` 与 public `YL/YD/ZV` 的桥，包含 bias 单位、三字 shift、范围，以及有限 overflow/subnormal 一次舍入。
5. 缺失的 `R27PackedLinear.finish/exactZero`、`Submission.retainedKernels` 的代码与等价；未因名字而假定它们已验证。
6. 600e native finish调用接线已由补充builder和父控重构报告确认，不再列为缺陷。仍未闭合的是完整caller证明、mixed-validity调度成本、原生编译／完整NMLP测量以及输出释放范围。
7. 原Contract全12核Obligation与允许公理门禁仍未由此研究关闭。冻结600e身份为71667B，低于256000B；此前把252639B public23直接拼片段的预算算术不适用于该source12 carrier，撤回其作为600e障碍的解读。本环境未独立重构整候选，也未核验未来加入完整证明后的最终字节数。

本轮 Python finite model 通过，不会关闭以上任何全称证明接口。Lean 文件无 `sorry`／新增公理，但全部 **NOT_COMPILED**，也不声称 elaboration 会无修改通过。
