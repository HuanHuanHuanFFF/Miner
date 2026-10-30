# R28 研究报告：绕过 LayerNorm 的完整整数商余链

## 1. 研究结论与证据边界

选定的机制是：**先构造完整、含 bias 的精确 affine 分子，再认证一个任意 binary32 候选属于其正确舍入区间。** 它把“精确求出若干商与余数后舍入”变为“只判定最终结果位于哪个舍入区间”。保留全部精确行统计与已经正确舍入的平方根分母，不重排 Contract 的舍入位置。

这是相对附件 public23 的不同路线，不是对整个研究领域的原创性声明，也不能证明源码不可见的冠军43没有使用相同思路。它不重复团队的 exact reciprocal 行缓存、RMS rrsG/rrsGe native finish 或 Mixer 调度；前者与本路线竞争同一个 LN 商余成本，不能相加预计收益。

本轮交付的最小成果是完整数学归约、可执行的两 limb 精确模型、包含实际 imported roundQuotientEven 的 Lean 小引理脚本，以及一个未接入 kernels 的 native 草稿。**不是可提交的 `Submission.correct` 实现。** 无可用 Lean/lake/elan；没有安装环境、运行 Lean、生成 native 程序或计时。本文使用“推导成立”表示书面数学论证；Lean 文件均 `NOT_COMPILED`。

已核验附件中三个区段的原始字节与 SHA256。具体行号和源身份见 `03_SOURCES.md`。Contract 文本引用 StableNorm/Values/SqrtProof；附件并未展开所有传递依赖。正式推导依据附件中的入口定义与 `U8/U9/V0/V1/Ya7Ge/Zdt` 语义桥；本轮没有把传递依赖的完整 pin 当作已复核证据。

## 2. public23 真实剩余成本

最终 `kernels.norm` 绑定为 `⟨Ybb2,MYbc⟩`。LN 的调用链是：

`MYbc → Y8f → Y2L + rsV → FF → FTk/FNk → FW/FX/FY`，随后每元素 `Ya7G`，必要时 `MYa7/MYa7b`。

| 部分 | 已有优化与仍存在的工作 | 频率 |
|---|---|---|
| 域检查 | stable domain、形状、finite、positive eps；LN 再查 b | 每次调用 |
| Y2L | 尾递归最低非零指数扫描；不是待消除的 list fold | 每行一遍 |
| rsV | 六个 UInt64 维护正和、负和、平方和；逐元素 decode、shift、m²、carry、guard | 每行一遍 |
| FF / FTk | `nQ−S²`，已有固定宽乘法、减法与检查 | 每行一次 |
| FNk | 精确 epsilon 对齐与相加 | 每行一次 |
| FW / FX | log2/scale；`dv128` 仍有三组商余 | 每行一次 |
| FY | `Nat.sqrt q`、root²/余项分类、终端 sqrt 舍入 | 每行一次 |
| Ya7G | `cv/D, cv%D`；`r0/D, r0%D`；`ra/D, ra%D` | 每元素三组 |
| rrsG→rqU | 最后缩放后的 quotient/remainder 舍入 | 每元素再一组 |

这里的“四组商余”是源码级事实。`/` 与 `%` 是否合并成单条机器除法、常量分支是否被消除，必须看 native codegen；不能把八个源表达式说成八条硬件除法。

`rsV` 已覆盖 n<256 且非零输入相对 b0 指数差≤36 的固定宽域。失败时 LN 还可能重新跑 Y7/Y6 的18-limb 统计与 YaD fallback。RMS 的 `YaEf` 也调用 rsV，但 continuation 忽略正负和：编译器是否消掉其维护不能从源码断言。

本轮优先选元素出口，因为它随 n 重复，而 sqrt 每行只做一次。这只是工作量判断，不是占时结论。没有 profiler，也没有当前冻结模型输入和 native 环境，所以不能声称 sqrt 一定轻、LN 出口一定占到20%以上。

## 3. 完整数学归约：mean、gamma、bias 都在同一有理式内

对有限 binary32 原始字 w，采用附件已有解码：

\[
v(w)=\sigma_w m_w2^{i_w-149},\quad 0\le m_w<2^{24},\quad\sigma_w\in\{-1,+1\}.
\]

令 b0 是行中非零项的最小 index；全零时保持旧实现的约定。定义

\[
X_j=\sigma_jm_j2^{i_j-b_0},\quad S=\sum_jX_j,\quad
\mu=\frac{S}{n}2^{b_0-149}.
\]

只在非零项上要求 b0≤i_j；零项直接取 X_j=0，避免对负的指数差做 Nat 截断或 UInt64 wrap。行长必须 n>0。

继续使用原 Y8f 给出的分母字 dw。快速认证域要求 dw 为**正的有限正规值**，写作

\[
d=m_d2^{i_d-149},\qquad m_d>0.
\]

该 d 已经包含 Contract 要求的一次 sqrt 舍入。用精确实数 sqrt 或另一个近似 d 替代它，通常会改变最终输出；本路线没有这样做。

对一个元素，令

\[
C=nX_j-S,\quad A=C\sigma_gm_g,\quad B=n\sigma_bm_bm_d,\quad
\alpha=b_0+i_g,\quad\beta=i_b+i_d.
\]

设 c≤α 对 A≠0 成立、c≤β 对 B≠0 成立；对零项没有这个要求。令非零项的 shift 为相应差，零项的 shift 为0：

\[
k_s=\begin{cases}\alpha-c&A\ne0\\0&A=0\end{cases},\quad
b_s=\begin{cases}\beta-c&B\ne0\\0&B=0\end{cases}.
\]

那么

\[
P=A2^{k_s}+B2^{b_s},\quad D=nm_d,\quad E=c-149-i_d
\]

满足精确恒等式

\[
\boxed{\frac{P}{D}2^E=\frac{(v(w)-\mu)v(g)}{d}+v(b).}
\]

推导可以逐项检查：第一项消去 D 后等于 `(nX−S)σg mg/n/md ·2^(b0+ig−149−id)`，第二项消去 n、md 后等于 `σb mb·2^(ib−149)`。这正是附件 U8/elL 的完整表达式。没有提前舍入 mean、中心化项、乘积或 bias。

### 3.1 为什么必须忽略零项选择锚点

原 `c2=min(b0+ig,ib+id)` 会让 b=±0 的 raw index=0 参与对齐。例如普通1附近的数据可能使 ks≈124，尽管 bias 项实际为0。最小新原型采用

\[
c=\begin{cases}
\beta&A=0,\\
\alpha&A\ne0\land B=0,\\
\min(\alpha,\beta)&A\ne0\land B\ne0.
\end{cases}
\]

两个系数都零或最终 P 抵消为零，均回退。这项处理保持精确式不变；它是完整机制的必要覆盖率修补，不能单独包装成“零 bias 就能赢板”。Lean 片段给出 `activeBase`、`activeShift` 和 `zero_aware_alignment`，显式保留非零项的真实指数差前提。

## 4. 原快速域为什么只需要98位；原型如何扩域

原 Ya7G 的主要守卫给出：n<2^12，|S|<2^60，非零 w 的 index spread≤24。

| 量 | 严格上界 |
|---|---:|
| `n·(mw<<spread)` | 2^60 |
| C 的绝对值 | 2^61 |
| D=n·md | 2^36 |
| `abs(C)·mg` | 2^85 |
| `D·mb` | 2^60 |
| `abs(C)·mg<<ks`，ks≤8 | 2^93 |
| `D·mb<<bs`，bs≤37 | 2^97 |
| P 的绝对值 | 2^98 |

因此完整含 bias 的分子**不需要普遍大整数**。D·mb 是普通64位乘法；只有 |C|·mg 需要宽乘。新草稿利用 mg<2^24，将其分成两个32×24乘积并显式处理carry；这只是支撑原语，不是另一个主机制。

实际原型没有把 ks≤8、bs≤37 设为最终限制。它计算两个未移位项后，分别检查：shift<128、移位不丢位；移位后每项 `<2^127`。于是同号相加 `<2^128`，异号按幅值先比较再减，不依赖溢出环回。这样允许小 C 与大指数差并存，覆盖后面的完整 bias 抵消反例。

这是保守充分条件：个别两个大项互相抵消后本来可装入128位的情况仍会拒绝，保持回退即可。动态检查的成本必须计入实验；98位上界不能被挪用为所有扩域输入的上界。

### 4.1 机器边界义务

- U64移位按实际计数语义执行，必须区分0、1..63、64、65..127；128以上拒绝。不能拿 `x<<<64` 当作无界整数左移64。
- Nat差只在对应非零项具有 c≤index 的分支取值。零项shift显式设0。
- `n.toUInt64`、Sabs、b0 的转换必须继承旧 aux guard，不接受任意截断后的数。
- P 使用 sign+magnitude；精确零回退，不能沿用 proposal 的零符号。
- 端点乘积与对齐移位有自己的边界证明，不能因为 P 能装下便省掉。
- 非有限输入、畸形数组、空尺寸保留原 stable/legacy 分流。本文没有缩小原 Contract 的量词。

## 5. 候选为什么可以完全不可信

先得到精确 P，再用

`((Float(phi)·2^64 + Float(plo))/Float(D))·2^E`

产生 proposal。此处 phi/plo 是 |P| 的两个 limb；符号最后按精确 P 加回。候选既可以来自 `Float.toFloat32`，也可以来自其他任何返回 raw32 的函数。**正确性定理必须对任意 q 成立，不能假设候选转换正确。**

Lean 官方参考说明 Float32 转换可损失精度且 `Float.toFloat32` 为 opaque；本路线不需要将其精度纳入信任链。文档只用于核对标准 API，不替代固定4.34编译验证：<https://lean-lang.org/doc/reference/latest/Basic-Types/Floating-Point-Numbers/>；U64转换参考 <https://lean-lang.org/doc/api/Init/Data/Float/Float.html>。

这里仍有一次 native binary64 除法。准确描述是“完整精确整数形成链和认证器无除法”，不是“整条 attempt 没有除法”。当前草稿还含3次 U64→Float、2次 double乘、1次double加、Float32转换与bit读取。元组是否分配、调用是否内联，均需看生成代码。

在当前守卫下 c≤508、id≤253，构造2^E用的 biased exponent `c+874−id` 在[621,1382]，没有负数转Nat或UInt64下溢。即便 proposal 被任意污染，后面的整数判定仍应拒绝错误q；尚待正式证明这一 word-level 定理。

## 6. 精确舍入区间与不需要商余的判定

仅尝试 magnitude 为正规数的候选：e∈[1,254]、f∈[0,2^23)，M=2^23+f。

\[
h=e-152,\qquad U=4M+2,
\]

\[
L=\begin{cases}4M-1&f=0\land e>1,\\4M-2&\text{其他}.
\end{cases}
\]

候选的下、上 midpoint 分别是 L·2^h、U·2^h。检查 P≠0、D>0、q符号=sign(P)，再检查

\[
\boxed{L2^h<\frac{|P|}{D}2^E<U2^h.}
\]

严格区间内候选比前驱与后继都近；更远的有限值不会成为最近者。负数用 magnitude 对称性。最大有限值单独用无界精度网格的虚拟后继2^128定义 overflow midpoint；没有把 +Inf 解码成有限 rational。

若 k=E−h=c+3−id−e≥0，整数判定为

`D·L < |P|<<k < D·U`。

若 k<0，改为

`D·L<<(-k) < |P| < D·U<<(-k)`。

两边系数均 `<2^26`，D<2^36，所以 D·L 与 D·U **小于2^62**，可以用普通 UInt64乘法。仅对齐阶段使用128位移位。`fits` 必须在实际移位之前成功；上端点可装下时下端点也可装下，但该单调性也属于正式证明义务。

### 6.1 为什么采用严格区间

ties-to-even 下偶 mantissa 可以接受两个中点，奇 mantissa不能。最小原型统一拒绝所有中点，交给旧实现决定，这简化证明且保持全输入语义。它不是把中点从Contract中排除。

对最小正规值 e=1,f=0，其前驱是最大次正规值，必须用 L=4M−2。普通 binade 起点用4M−1。对最大有限值，上 midpoint 为2^128−2^103；原型严格拒绝这个点，旧RNE路径返回overflow结果。

## 7. 必要反例与回退

| 错误做法 | 精确反例 | 正确处理 |
|---|---|---|
| 对2的幂套对称半ULP | q=1，y=1−3·2^-26 | 应为0x3f7fffff；错误的宽下界会接受1 |
| 所有midpoint均闭区间 | q=0x3f800001，y=1+3·2^-24 | q是奇mantissa，应选0x3f800002 |
| minnormal套普通binade下界 | y=2^-126−3·2^-152 | 应舍入0x00800000；错误较窄下界会误拒绝 |
| 精确零继承native符号 | row=[1,1],eps=1,g=−1,b=−0 | stable rational为0；native可为−0，必须回原规范 |
| 宽乘只保留低64位 | C=2^59,mg=D=mb=2^23,ks=bs=0,E=−23 | 真值2^36+1；截断P能错误“认证”1 |
| 128位项可装下就省略shift检查 | 1在U64上shift64 | 机器环回计数与整数乘2^64不同 |
| maxfinite用Inf作为有限邻居 | y=2^128−2^103 | tie应overflow；用虚拟2^128构造阈值 |

第五行是机器算术反例，不冒称它来自一条完整合法统计行。模型特别用独立有理式验证P，防止“错误构造的P验证自己”。

### 7.1 一个完整 stable row 的 bias 抵消反例

取 row `[1,1,1+2^-23]`，eps=1；关注w=1，g=3，b=2^-23+2^-46。精确 mean=1+2^-23/3，variance=2·2^-46/9，sqrt分母正确舍入为dw=1。因此

\[
((1-\mu)3)/1+b=2^{-46}.
\]

本轮 Python 实验中，直接用 host double 做中心化与bias相加，proposal为 **0x287c0000**；真实结果为 **0x28800000**。从已经精确抵消后的 P 生成 proposal，整数检查接受 **0x28800000**。这解释了为什么草稿先构造P，而不是直接照搬浮点 affine 表达式。

### 7.2 全输入回退表

| 情况 | 行为 |
|---|---|
| 原stable domain失败，包括非有限、形状、n=0等 | 保持原legacy分支 |
| n≥4096、Sabs≥2^60、输入指数spread过大 | 回旧元素出口 |
| dw不是正有限正规值 | 回旧元素出口；尤其不把dw overflow擅自改成硬件除Inf语义 |
| g/b/w为次正规或零 | 按真实decode构造；若guard不满足则回退 |
| 两项皆零或最终P=0 | 回退，保留canonical zero语义 |
| 候选为±0、次正规、Inf、NaN | 回退 |
| 候选符号错误、恰好midpoint、检查失败 | 回退 |
| 移位、乘加或转换前提不成立 | 回退 |

正的有限epsilon意味着精确variance+eps有正下界，但本原型没有依赖这个事实删除denominator guard。即使某些denominator情况数学上不可达，出口的零、次正规和overflow依然可能发生，不能省略回退。

## 8. 最小成果与实际执行结果

`R28CellLemmas.lean` 给出以下小规模脚本，均未编译：完整 affine 恒等式；实际 imported `FloatLib.Numerics.roundQuotientEven` 的 strict-cell 定理；ordinary网格、power-boundary lower网格；midpoint系数；minnormal与maxfinite；正分母交叉乘；零项感知对齐。核心 quotient 定理是

\[
D>0,\quad 2MD<2N+D,\quad2N<2MD+D
\Rightarrow\operatorname{roundQuotientEven}(N,D)=M.
\]

证明中可以使用商余分解；拟议运行时只判断两个整数不等式。不要把证明脚本存在误当作Lean内核已经验收。

`R28NativeCell.lean` 是独立 native 成本草稿，仅 import ContractExact，不定义 kernels、不改Contract、不声明correct。它包括完整 bounded-word形成、动态128guard、proposal和strict checker，方便首个成本实验有具体对象。

### 8.1 已执行的有限模型

| 验证组 | 实际规模 / 结果 |
|---|---|
| 64×24宽乘 | 3,000组，对无界整数积 |
| 128位加减 | 6,000项检查 |
| shift / 无溢出guard | 33,650项，含0/64/128边界 |
| toy format局部midpoint网格 | p=2..5，41,020项；不是所有有理数穷举 |
| binary32边界网格 | 254个正规指数，6类fraction，正负符号；33,528项 |
| 其中严格拒绝的精确midpoint | 6,096项 |
| 正确/相邻/反号/随机proposal | 24,000项；接受2,801，0错误接受 |
| 真实合成行元素 | 11,888项，详见下表 |
| 独立压力检查的局部一致metadata | 12,000组；4,994构造，4,421接受，最大P127位，0错误接受 |

这里“不同算法oracle”表示：checker使用limb交叉乘，round32使用商余RNE，另一个reference使用实际前驱/后继。它们共享fields/finite_value基础，不能声称完全独立实现，更不能声称已等价于固定FloatLib。Python函数中的Fraction除法只用于独立语义核对，并不是拟议生产路径的费用模型。

合成行覆盖结果：

| 合成组 | 元素数 | 接受 | 回退 |
|---|---:|---:|---:|
| 普通范围、完整非零bias | 2,972 | 2,972 | 0 |
| 零bias | 2,972 | 2,972 | 0 |
| 混合次正规 | 2,972 | 0 | 2,972，对齐guard |
| 广指数范围 | 2,972 | 0 | 2,972，row guard |

保留两个raw指数取min而不忽略零项时，零bias组2,972项全部因对齐guard回退。这个差异支持零项感知对齐的必要性，不是对官方输入分布的估计。

额外metadata检查只约束单个 affine 元素与其mean记录相容，没有声称每条记录来自完整stable row。脚本、固定seed与JSON结果全部交付，可按README命令复现。所有这些结果都是有限算术证据，没有Python耗时、native耗时或冠军复现数据。

### 8.2 正式证明仍缺什么

1. UInt64/128 helper在各guard下精确等于无界Nat/Int操作，包括无丢位、carry/borrow、下端点shift安全。
2. 实际 Y8f/aux 和数组索引连接到P的完整有理表达式；检查Ssign极性。
3. 动态整数比较等价于数学strict-cell条件。
4. raw32邻居映射及 `roundRatScaled` 的floorLog2、packing、跨binade carry、overflow桥接。
5. `attempt ≠0 → attempt = MYa7 ...` 的最终word定理，以及fallback wrapper与整个`Submission.correct`。

所以本轮成果**没有完成全输入Lean验收**。全输入安全结构是在快域证书成立时接受、其余使用原函数；正式接入仍须证明快域接受定理，不能仅靠这些测试发布。

## 9. 10%机会：可被推翻的成本条件

定义f=旧目标元素出口占整模时间比例，p=按旧执行成本加权后能跳过的比例，a=所有attempt（成功和失败）总费用/旧目标出口总费用，h=目标区外新增费用/原整模费用。忽略缓存干扰时：

\[
\frac{T_{new}}{T_{23}}=1-f(p-a)+h,\qquad
\Delta=f(p-a)-h.
\]

这是规划模型，实际验收取完整native调用。p不能简单拿合成样本的元素命中率代入，因为慢fallback元素可能占大量成本。

若p=1、h=0：

| 新attempt/旧出口费用a | 达到整模10%至少需要f |
|---:|---:|
| 0.25 | 13.33% |
| 0.40 | 16.67% |
| 0.50 | 20.00% |
| 0.60 | 25.00% |
| 0.70 | 33.33% |

若f≤0.10，即使出口被免费消除也最多省10%；任何正的新费用都使此路线严格达不到10%。若p≤a且h≥0，本路线连净收益也没有。没有f/a/h实测，就没有无条件10%承诺。

当前attempt付出一轮解码、精确P形成、动态guard、FP proposal、cell检查，miss后还重新进入原Ya7G。st/aux准备、输出构建和drop仍在。尤其tuple未被内联消除或频繁失配时，源码少了商余也可能更慢。

官方链值仅作为条件目标算术：

\[
T_{43}/T_{23}=0.9072362322,
\]

若可直接同基比较，要比43再减时10%，需 `Tnew/T23≤0.81651260898`，即比23省18.3487%。比23省10%在该条件下仅比43省约0.7976%。当前没有直接同机证据，不将链值当作性能校准。

## 10. 首个否证实验与停止条件

实验前提是已有固定Lean4.34/FloatLib环境、冻结模型输入与原编译/计时配置。本轮没有这些环境，所以没有执行。

1. 在相同模型、参数、输入、线程和编译配置上建立A=原public23；C仅在LN出口前加本attempt，miss调用整个原Ya7G。保持原行统计和外层检查。不要更改Contract、gate或benchmark参数。
2. 在不计入正式耗时的差分阶段逐位比较A/C完整输出；记录各guard、midpoint、normal/non-normal和fallback原因。包含完整bias、零、次正规、最大值、不同n和shape边界。
3. 使用原计时边界交替测完整A/C调用。proposal、UInt64→Float、dynamic fits、分子形成、所有失败回退、准备和回收都在C内。计数和profiling另跑，不能给C单独排除开销。
4. 若团队exact reciprocal版本B已经可用，加同机A/B/C。它与C的收益不能求和；应选完整模型结果更好的实现。
5. 检查生成C/汇编：pairs是否分配，商余是否已经被合并，三个转换是否helper call，inline是否生效。这些检查解释实测，不替代实测。

**否证/停止：** f的可信上界≤10%；完整C相对A不能净省10%；或C只在删掉proposal/fallback费用后达标。此时不要继续为“10%”扩大证明范围。若只有一个明确可修复的allocation/转换热点，可修一次再用同一判据复测。

**推进：** 完整模型C/A≤0.90且重复测量差异稳定、逐位差分通过，再投入word-level证明。此仍不证明比未知43更快；那个结论需要可比较的官方/同机结果。

## 11. 字节上限与下一条不同路线

public23为252,639B，距256,000B仅3,361B。本轮研究稿不能整体append后当成合法候选。原Ya7G定义约1,680B，Ya7Ge证明区约14,329B；理论上生产版可替换这一实现/证明并保留MYa7作为fallback，腾出空间。但这会改变miss成本，必须重新测量，且新证明有自己的尺寸。现阶段不删除上游任何内容，也不声称已满足最终单文件限额。

若本路线因成本份额不足被否证，下一条不同路线是**每行 sqrt 的平方阈值认证**：保留精确variance+eps=N/D·2^e，用任意候选d，对其正的midpoint L/U直接检查 `L² < N/D·2^e < U²`，把原Nat.sqrt及准备除法替换为精确乘法比较；失败回FW/YaD。这仍保留“先舍入sqrt分母，再终端舍入”的Contract顺序。大数对齐和256位乘法可能比现有FW更贵，必须先看行统计/sqrt份额；若该份额也≤10%，它单独也达不到整模10%。

若两个热区的可消除上限均不足，就应明确放弃“仅改归一化出口或sqrt就保证10%”的目标，转向实际更大份额的dense或数据流成本；附件中已有的FP dot cost helper只是未证明候选，不能把它重新命名成此次新突破。
