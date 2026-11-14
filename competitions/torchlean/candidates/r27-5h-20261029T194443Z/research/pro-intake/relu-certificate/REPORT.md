# R27：纯整数粗精度 ReLU 符号证书

## 结论与最先判停的实验

**数学候选成立；当前不进入大 producer 证明。** 三个 8-bit 无符号积可以由一次 UInt64 低乘准确提取。对实际通过“输入行非负、所有参与字有限”的 guard 的输出，u8×s8 量化还可把符号修正减少到一次行和修正，并仅为正权重支付上界误差。完整 bias 必须单独向上对齐。其余输入原样走 public23 正确路径，Kernel 全输入量词不改变。

**收益 UNKNOWN，首轮只值得做很小的 native 成本判别。** 本包没有 native 测量，没有安装工具链，没有写 Git/CI，没有读取当前冻结确认输入/结果，没有派子代理。Python 用自有 raw-word 有限输入；时间不作为性能数据。旧 FP-only 测量由用户提供，本包不重测，也不据此推断此新候选的收益。

最早可证伪的顺序：

1. **最佳情形仍失败即停止该 shape 的变体**：自造 dense 非负 X、全负 W、零 bias，保证全部证书成功；将完整额外 prep、缓存、drop、bias 检查计入，与原 public23 比较。若即使全命中仍不快，停止该 shape，无须扩展证明。
2. **全 miss 税**：自造全正 X/W，执行完整证书后调用原强路径。测量额外成本，不得先算原 dot 再统计可跳过比例。
3. **调度税**：四输出组内混合命中，分别测“只有整组全中才跳过”和“标量运行 miss”两种方案；不可把单输出命中率直接当作省下的四路内核比例。
4. **稀疏先 gate**：k=96、X 仅一个非零时，本包证书要 32 次打包乘法，原稀疏路径只要 1 次 exact 项乘法。这个乘法数差不是 native 时间定理，但足以停止把当前 dense 打包方案直接套在极稀疏行上；要继续须先证明收益来自其他实际成本。
5. **覆盖门槛**：只用自造输入，记录 finite/nonnegative/bias-range/shape guard 失败率、证书 margin、单输出命中、整组全命中、原支持长度。近抵消和宽指数小尾项样本已显示负值也会全 miss。没有生产覆盖证据，不扩为通用 producer。

计费恒等式应按实际被移除的旧工作建立：

`Tnew - Told = Pextra + Ccertificate + Δschedule + Δallocation/drop - SavedOriginalWork`。

Pextra 包含未证明可复用的所有行/列扫描、量化、打包、正余数统计和缓存；miss 仍需原准备。均匀输出的粗略必要条件为 `h > (c+p+g)/d`，d 是实际省掉的原输出 dot/finish 成本，h 是成本加权命中比例。保持四路原调度时，须改用整组全命中实际省下的工作，不能假设独立再用 h⁴。若要总模型快 10%，还需 `SavedOriginalWork - Extra > 0.1*ToldModel`；本包没有能代入的 native 数据。

## 1. 真实 Contract 的 activation 语义

来源是附件原 `CONTRACT_EXACT_OLD_PIN_UNCHANGED_PROOF_ID`，`ExactRuntime.reluW`、`act`、`linearWith`，以及原 `ExactToolkit.Values`。实际定义：

```lean
def reluW (w : Word) : Word :=
  if w &&& 0x80000000 != 0 && !(expOf w = 255 && fracOf w != 0)
  then 0 else w
def act (relu : Bool) (w : Word) : Word := if relu then reluW w else w
```

| 输入 word | `act true` |
|---|---|
| 负 normal、负 subnormal、`0x80000000` (-0) | `0x00000000` (+0) |
| `0xff800000` (-Inf) | +0 |
| +0、正数、+Inf | 原 word |
| 任意 NaN，包括 `0xffc00001` | 原 NaN word，不清零 |

`linearWith` 调用长度 `inW+1` 的单次精确 dot，最后一项是 `oneW * b[j]!`；**bias 与所有乘积一起求精确和，最后只舍入一次**。不能把 staged FP add 或“dot 负”代替“含 bias 的精确总和负”。

若所有实际参与因子和 bias 有限，精确总和 S<0，则正确 binary32 舍入只会产生负 finite、-0 或 -Inf，均经真实 ReLU 变成 +0。负下溢无需额外排除。非有限输入的规则不同：例如零乘 Inf 不能跳过检查。本候选遇任何非有限即走原 fallback。relu=false 在新增 prep 前退出。虽然 S=0 也可以研究，本首版只接受严格上界 U<0。

形式化缺口：上段的数学结论已明确，但从 `finiteDotSlice_eq`/`finishWord`/`Model.roundDyadic` 到 raw-word ReLU 的桥**尚未在 Lean 编译证明**。本包不把该桥写成不存在的库 API。

## 2. 全量词整数模型与一般上下界

对任意 k∈Nat，0≤k≤2³⁰；任意有限 binary32 因子字及有限 bias；令一个有限字的 sign、significand、index 为 σ、m、I，其中 m<2²⁴，I=e=0 时为0、否则 e−1，I≤253。其精确值是 `(-1)^σ m 2^(I−149)`，包括 ±0 和 subnormal。

使用整数单位 2⁻¹⁴⁹：a、b 是有符号整数。取正整数幂 Ta=2^sa、Tb=2^sb，向零截断：

`a=Ta*qa+ra`, `b=Tb*qb+rb`, `|ra|≤Ta−1`, `|rb|≤Tb−1`。

余数与原值同号（或为零）。逐项恒等式：

`ab-Ta*Tb*qa*qb = Ta*qa*rb + Tb*qb*ra + ra*rb`。

所以令 Q=Σqa*qb，τ=Ta*Tb，D=Σab，有：

`|D−τQ| ≤ Ta(Tb−1)Σ|qa| + Tb(Ta−1)Σ|qb| + k(Ta−1)(Tb−1)`。

这含完整的交叉项。除以 τ 后可用更便宜的 R=Σ|qa|+Σ|qb|+k 保守包住两侧。物理尺度 Δ=τ·2⁻²⁹⁸。若 βlo≤bias/Δ≤βhi，则完整 S 满足：

`Q−R+βlo ≤ S/Δ ≤ Q+R+βhi`。

只有右端严格小于0才认证。整数模型使用 Fraction 只作 exact oracle；候选 probe 仅做整数操作。

## 3. 建议首试域：实际非负输入 guard，u8×s8

这是一项新增的 **运行时 fast-domain 检查**，不是偷偷修改原 Kernel 假设。对 X 中每个字检查有限且 `(sign=0 or m=0)`；允许 -0。W 和 bias 可为任意有限值。所有 miss 回原强 YaV。实际模型的 `certificate_probe` 已执行这些检查；生产 YaV 接入尚未做。

令 A=max I(X)，B=max I(W)，空行峰值取0。采用 sa=A+16、sb=B+17：

`qX = mX >> (A+16−IX)`，`qW = signW * (mW >> (B+17−IW))`。

得 qX∈[0,255]、qW∈[−127,127]，Δ=2^(A+B−265)。每侧余数是否为零可由移位和低位检测得到。**shift≥24 必须分支直接给 q=0、rem=(m≠0)**；不能把大移位直接交 UInt64 的掩码移位语义。小移位分别在16..23、17..23，安全。此实现无需构建几百位整数；大整数仅用于精确验证。

行缓存：A、打包 qX、A1=ΣqX、Amax=max qX、ηA=(至少一个 X 量化余数非零)。列缓存：B、打包(qW+128)、P=所有原正权重的 qW 之和、K=所有原正权重中余数非零的项数。正权重 qW=0 但余数非零仍必须计入 K；padding、±0 不计。

对正权重，用归一化余数 δX,δW∈[0,1)，误差是 `qX δW + qW δX + δX δW`。三部分之和分别不超过：

- `min(A1,Amax*K)`：δW 非零只发生于 K 个位置；也不超过整行 qX 和。
- `ηA*P`。
- `ηA*K`。

对负权重，qW≤0、δW≤0，而 qX、δX≥0，三个误差项均≤0；无需给上界增加正误差。于是：

**`Eplus = min(A1,Amax*K) + ηA*(P+K)`**，

**`U = Q + Eplus + βhi`，`U<0 ⇒ S<0 ⇒ act true (exact dot+bias)=0`**。

Eplus 每输出只需一次小整数乘法 Amax*K、min、少量加法/分支；它的准备扫描和缓存成本仍必须支付。首版不扫描额外逐项 residual dot。通用 signed×signed 仍用上一节 R；比较模型已实现，但不是首选生产域。

## 4. 三项低乘：精确范围、证明、偏移陷阱

取 Bpack=2²⁰。六个数字均在0..255，

`Apack=a0+a1*Bpack+a2*Bpack²`，
`Cpack=b2+b1*Bpack+b0*Bpack²`。

完整乘积的 Bpack 进制系数依次是：

| 系数 | 表达式 | 上界 |
|---|---|---:|
| c0 | a0b2 | 65025 |
| c1 | a0b1+a1b2 | 130050 |
| c2 | a0b0+a1b1+a2b2 | 195075 |
| c3 | a1b0+a2b1 | 130050 |
| c4 | a2b0 | 65025 |

都小于 Bpack，故不存在基数进位。c2 占 bit40..59。c3 从 bit60 开始；模2⁶⁴丢掉的高位不影响 bit40..59。Apack、Cpack 各自<2⁴⁸。因此对所有六元组：

`((Apack*Cpack mod 2^64) >> 40) & (2^20−1) = c2`。

这里需要低乘；不要求完整乘积<2⁶⁴，也不允许错误地用这条不等式证明。Bpack=2¹⁷ 则失败：六字节全255，提取64003，真实195075。原 Bpack=2²⁰ 没有这个问题。

固定 Bpack=2²⁰ 时，可保证所有六数字∈[0,M] 的最大统一范围实际是 M=591：3·591²=1,047,843<Bpack，其他系数更小；六个数字全592则中间系数1,051,392溢出字段，提取得2816。故0..255不贴近此范围边界。这个扩大范围的事实只作精确范围说明，不新增量化方案或运行成本主张。

通用 signed×signed，u=qA+128、v=qB+128，补齐后项数 N=3ceil(k/3)：

`Q = Dpacked −128Σu −128Σv +16384N`。

**常数项必须用 N，不是原 k**；补齐零编码为128。最小原始 word 反例：x=w=`0x3f800000`，qA=qB=64，补齐 u=v=[192,128,128]，Dpacked=69632。正确 Q=4096；错用 k=1 得−28672，再加 R=129 仍为负，将真实 +1 错清零。

非负输入 u8×s8 只偏移右侧：

`Q = Dpacked −128*A1`。

这省掉两个符号偏移统计/修正项；补齐 qX=0、qW=0（右编码128），贡献仍0，不存在 k/N 常数修正陷阱。

## 5. Bias 对齐与本机范围 guard

对 u8×s8，H=A+B，bias字段 mβ、Iβ、σβ：

`bias/Δ = (−1)^σβ mβ 2^t`，`t=Iβ+116−H`。

signed×signed 的对应常数为115。bias 对齐依赖当前行 A 与列 B，不能无条件只按列缓存一次。

- mβ=0：βlo=βhi=0，±0 一致。
- t≥0：仅当 `bit_length(mβ)+t≤60` 才执行左移；否则回退。此 guard 使 shift 自身也合法。
- t<0：令 d=−t，q=floor(mβ/2^d)，r 为余数非零标志；d≥24 直接 q=0、r=(mβ≠0)。正 bias 区间[q,q+r]，负 bias 区间[−q−r,−q]。

这是 exact floor/ceil，无浮点误差。即使极大 bias 自身可能主导符号，首版也不额外开分支，先回退。

在 k≤2³⁰、N≤k+2 下，Dpacked≤65025N<2⁴⁷；正确 Q 绝对值<2⁴⁷；Eplus<2⁴⁰；|βlo|、|βhi|≤2⁶⁰；所有顺序执行的修正及最终 score 均在 signed64 安全范围，保守可用绝对值<2⁶¹。A1≤255k，P≤127k，Amax*K≤255k，各自可用 UInt64。不应用 UInt64 环绕减法的无符号比较判断负数：必须先证明可转换范围，再用 Int64 或已证明的有符号表示比较。

`certificate_probe` 对 relu、长度一致、k上界、raw UInt32 范围、finite、非负输入、bias尺度范围均执行 guard。数组 shape/index 与 metadata 一致性需在实际 YaV 接入前再建立；遇不满足者必须走原函数，不能改变原 `get!`/默认值行为。无 native 集成意味着这些跨缓存 guard 目前不是已验证的生产代码。

## 6. 与真实 public23 helper 的映射及费用

| 实际名称 | 当前作用 | 新证书可用的接口 / 尚须计费 |
|---|---|---|
| Yc / Yah；YaV 的 BX、BV | 行列指数范围与 finite 信息 | maxIndex 可候选复用；必须证明 metadata 来自同一逻辑字，非负 guard 仍新增 |
| QPS | 决定共享输入准备路径；inW≥16、有限、跨度条件 | 不是新证书的隐含前提；广域原路径差别须保留 |
| QPI | 原始 nonzero significand 支持集 | q=0 不代表原 x=0；不得用量化零改变原 fallback 稀疏支持 |
| QPD | 输入双 lane 准备 | coarse pack 是另一份准备；不能假设免费，也不研究团队 A/B 的无损字缓存 |
| QPa / QY6G / QhiS | 窄跨度 finite 条件下的 signed128 精确积累 | baseline 已强；每项乘法和共享加载是实际比较对象 |
| QPa2、QPa4、QPa4w、QPac4；Yak4、YT4l | 多输出/多行调度及共享 | 混合命中需要实测，fallback 到标量会损失共享 |
| YaU / Yai / YaL；YP | 更宽域/后备精确路径；YP 是 limb 减借位 | 不能把每个 YaV 输出都按昂贵 YP 路径计费 |
| Z5、O2、ZcC | 现有 dot、含bias helper、linear 正确性 | 复用已有正确 fallback，不重证原模块 |

原 YaV 先构造 BX/BV，并有条件构造行准备 P；QPI 的稀疏判定为非空且4*z≤3*inW。新方案若每个 miss 调用完整 YaV，会重复准备并破坏调度；若先运行全部 YaV，则没有省掉 dot。正确接入点应在保留共享准备与组调度的局部输出分支，完整 fallback 仍调用原对应 helper。

额外空间至少约 `(rows+outW)*ceil(k/3)` 个打包64位单元，加元数据；Lean 容器装箱、引用计数、drop 的实际代价 UNKNOWN。复用 BX/BV 也仍需一次行列量化/打包 pass，且正权重 residual 统计必须在列准备完成。除非全部输出能跳过，否则不得假定原 P 不再构造。

稀疏支持不免费：按每行原 support 重排 W，会让列 pack 依赖行、增加 gather/repack，并改变 P/K 统计的索引域。因此首轮明确只考虑 dense 非负输入域；稀疏和负输入回原强路径是一种可实现 guard 策略，不能由未测的命中率替代成本分析。

## 7. 可重放结果与最小反例

运行 `python3 integer_model.py --output results.json`。只依赖标准库；所有输入 raw words 来自脚本内常数或固定种子0x523237，无 FP arithmetic。候选 `certificate_probe` 不调用 exact oracle；`certify` 是测试 wrapper，才计算精确整数总和和 binary32 最近偶数舍入。`certified_or_fallback` 展示 hit返回0、miss调用 supplied fallback 的总路由；它尚未链接 YaV。

已运行：14,096 个打包检查（4⁶边界组合+10,000固定种子），1,000 个 finite 候选调用（其中可含真实guard miss），边界 case 和192个自造覆盖 case。有限测试不能替代全称证明。Python 的 RN32 oracle 是本包原创模型，并非已证明等于 FloatLib。

每个 family 都32输出、k=96、8组四输出：

| 自造 family | 真实总和负 | 证书成功 | 四输出整组成功 |
|---|---:|---:|---:|
| 全负对齐权重 | 32 | 32 | 8/8 |
| 全正对齐权重 | 0 | 0 | 0/8 |
| 成对近抵消 | 32 | 0 | 0/8 |
| ±1抵消后极小负尾项 | 32 | 0 | 0/8 |
| 仅一个非零 X | 32 | 32 | 8/8 |
| 固定种子混合符号 | 16 | 14 | 1/8 |

最后一行14/32单输出命中，却只省得1/8个完整四路组，说明不能遗漏调度。表格是可证伪构造，不是生产准确率预测。

其他 exact 验证：minsub×negative-minsub 舍入−0，certificate miss但fallback正确；maxfinite×negative-maxfinite 舍入−Inf且证书成功；maxsub×negative-maxsub 舍入−0且证书成功；NaN bias、zero×Inf guard miss；empty+bias 的巨大相对尺度可直接bias-range miss。负 dot 加正 bias 的反例 x=+1,w=−1,b=+2，最终+1，遗漏 bias 会错误清零。

## 8. 最小 Lean 接口与 UNKNOWN

`IntegerBridge.lean` **NOT_COMPILED**：有真实 proof draft，无 sorry、axiom、admit、native_decide，不声称 Lean 已接受。依赖附件原 `ContractExact`；本包不拷贝整个上游。包括：

- 六字节打包提取的 Nat 模2⁶⁴定理；各中间系数范围明确。
- 三项 signed偏移、unsigned-left偏移恒等式。
- 残差展开、正权重误差、负权重误差非正。
- prefix sum、显式 metadata 上界假设的聚合桥、含 bias 严格负闭合。
- 对真实 `ExactRuntime.act` 的 −0、−Inf、负NaN、relu=false 小例子。

最便宜的正式证明路径：先编译纯代数文件；随后只连接下列边界，保持已接受原 proof 不动：

| 接口 | 需建立的事实 | 状态 |
|---|---|---|
| raw word→quant/remainder | 用现有 mantOf、idxOf、decodeD_toRat、mantOf_lt_24、idxOf_le 证明移位分支给真正向零商余数 | OPEN |
| Nat低乘→UInt64 | toNat mul 的模语义、右移/and等于常数div/mod、转换范围 | OPEN；未捏造组合API |
| prep→metadata | 同一row/column与原索引；A1/Amax/P/K/ηA、pad正确；支持集不丢真实非零 | OPEN |
| metadata→Eplus | 正/负权重分区求和，termA≤A1且≤Amax*K，其他两项上界 | 数学已给；Lean文件保留明确hA/hAK/hP/hK接口，未冒充已闭合 |
| bias | bitlength guard、floor/ceil与scale对应，Int64无溢出 | OPEN |
| finite exact total→activation0 | finiteDotSlice_eq、dotStateLoop_flags、finishWord_of_ne 与roundDyadic sign；NaN不可能；−0/−Inf均relu0 | OPEN |
| dispatch→original obligation | 接在YaV实际分组分支；miss原helper；ZcC复用 | OPEN |
| native成本、模型收益 | prep、hit/miss、分组、sparse、drop全计费 | NOT_RUN / UNKNOWN |

上述接口只包含实际找到的原始定义/定理名，未知 FloatLib 连接没有写成假定现成 API。原公开文件约252,639 bytes；若原256,000-byte约束仍适用，仅约3,361 bytes追加空间。把本研究文件直接append必然不合适；精简集成大小未做，另列 gate，不能因数学简单忽略提交预算。

**停止理由（当前）**：数学没有排除一个很窄的 dense/非负/负margin足够大的 fast 分支，但没有 native 证据能抵消额外准备、每次miss税与多输出调度损失；近抵消覆盖已经构造性失败，极稀疏乘法数明显不利。因此交付此最小可回收成果后，不继续大producer；下一最小实验仅是前三种自有输入的计费native探针。没有该结果，不承诺10%。

## 9. 来源、范围与复现状态

- 附件 `research-materials-r28(1).txt` SHA256：932da02eec02644a6e0b1fcfe56579143936eec3fcce38b8d8caa1c7eb74374c。
- 原 public23 section SHA256：1010c0744f0506974c64601e8ce7335bea56d0cb21b655543d390794df0665fe。
- 原 Contract section SHA256：bddd6bd9caa19f9419e0e38cd553b109a7675fc710fdf82a6d6f7d0f2a4c8b1b。
- 只读原 public23/Contract 及其已获取的 pinned ExactToolkit 定义；未读任何冻结确认输入或结果。
- 本包未重写 YaV，未打包上游 Kernel，未复做 orderKey、strict midpoint、getter、UInt64通用模块、FloatArray无损字缓存或 Winograd。
- 执行状态：Python exact checks PASS；Lean NOT_COMPILED；native NOT_RUN；完整 Kernel obligation NOT_PROVED。
