# F64 ADD診断：允许公理路径与严格数学前提

UTC2026-10-28T21:39:37Z；源08a0208e…已冻结，本文不改运行体。所有新增Lean义务仍NOT_RUN。

## 二元ADD的double-round充分条件

一手论文Pierre Roux，*Innocuous Double Rounding of Basic Arithmetic Operations*，JFR7(1),2014,131–142，DOI10.6092/issn.1972-5787/4359：[文章](https://jfr.unibo.it/article/view/4359)、[PDF](https://jfr.unibo.it/article/download/4359/4017/12373)。定理20（纸页137）、FLT扩展（138页）及表II（141页）给二元加/减的充分条件：中间精度`p2≥2*p1+1`，渐进下溢还需`emin2≤emin1`。binary32/64满足`53≥49`和`−1074≤−149`。论文是Coq/Flocq外部数学证据，**不自动成为当前Lean证明**。此结论只用于两个F32数的加法；不扩到FMA或任意fold。

原PDF字节未落盘：普通终端下载被当前网络权限阻断（WinError10013），因此PDF原始SHA/字节UNKNOWN；web已读原PDF正文和精确公式，未把本地未保存当作原件回收。原文无大段复制；页面标CC BY3.0。后续可由D按其可用下载入口回收，非本次cost前置。

独立、保守的binary32特例证明分解如下（纸面推导，非Lean闭合）：

1. 非零有限F32可精确写为`±m*2^(L−23)`，`2^23≤m<2^24`，即使原字次正规也能通过左移m正规化表示；真最高指数`−149≤L≤127`。0另外按IEEE符号处理。
2. 设`Lx≥Ly`，差`d≤26`。共同最低单位`2^(Ly−23)`上的精确有符号整数为`±mx*2^d±my`，绝对值小于`2^(24+d+1)≤2^51`；因此整个和在binary64中精确。共同单位最低为`2^-172`，值上界小于`2^129`，都在binary64正常范围内（非零和至少为F32最小次正规单位）。
3. 若`d≥27`，较大x必为F32正规数（较大者仍次正规则差至多22）。`|y|<2^(Lx−26)`。从F32正规x到任何相邻舍入中点的最小距离至少`2^(Lx−25)`；在2的幂、最大有限和反号方向同样取这个保守界。binary64 RNE误差可取上界`2^(Lx−52)`，故总扰动严格小于该F32中点距离。精确和与64舍入后的和都仍回到原x。
4. 零、精确抵消、−0＋−0等通过同宽native ADD与原Model.add的符号零规则单列，不由实数等式代替原字身份。有限输入导致F64和绝对值小于`2^129`，所以中间不会溢出；最终F32溢出由word converter显式处理。

## 运行体中需要逐项连接的义务

- **UInt32→F64数值cast**：`UInt32.toFloat`在固定Lean4.34中有`Float.Model.ofUInt32`逻辑模型；24位mantissa可精确表示，不使用opaque Float32.toFloat。当前B2的通用native integer/mul模型与固定FloatLib Native/Integer接口可复用，实际实例化和完整依赖须重验。
- **512 signed scales**：E0取`2^-149`，E>0取`2^(E−150)`。binary64 biased exponent为874或E+873（874..1127），全为正常数。global FloatArray通过公开push构造，不用其内部结构冒充native存储。需要size/get!值身份、word sign/exponent字段和numeric乘法精确性；源与成本包括getter实际检查/调用。
- **F64 ADD**：固定FloatLib `Native/AddSub.lean`有`toModel_ofFloat_add_of_isFinite`、`ofFloat_add_of_isFinite`；它是同宽binary64桥，不能充当Float.toFloat32 narrowing桥。
- **纯word缩窄**：源`narrowWord`只用Float.toBits后的UInt64字段。令biased exponent为E，53位M带隐位。E≤872给signed0；873..896用`RNE(M/2^(926−E))`得到F32次正规格点整数，允许进位到min-normal；897..1150用`RNE(M/2^29)`并与`(E−897)<<23`相加，让24→25bit carry进入指数；E≥1151给signed∞。此义务只对有限F64 word，NaN不是该转换器的payload合同。
- **fallback**：任一原F32 exponent255则原B2 ADD；保持NaN选择/信号优先/Inf和invalid规则。有限输入经过已证明的decoder/nativeADD/word缩窄，再用二元double-round特例连接原ADD。

`f64native/f64boxed`仅使用有逻辑模型的原语，尚缺上述新证明；`f64cast`调用opaque Float.toFloat32，永远只作工程对照。后者没有机器时间下界定理，也不能代替legal路径实测。

若两条legal完整成本均无实质收益，停止该body而不投入这些证明。若legal有明确收益，第一层只编decoder/size、finite64 word→RN32、同宽ADD和二元rounding四个小接口；此后才接公开函数/完整gate。

## 两个最小、可复用的精确命题

1. Word缩窄可直接以纯bits为义务：对任意UInt64 w及dyadic d，若`Model.toDyadic? (Model.ofUInt64 w : Model binary64)=some d`，则`Model.ofUInt32 (narrowWord w : UInt32) = Model.roundDyadic binary32 d`。这包含64位有限word的−0、正常/次正规目标和溢出；不需要opaque native narrowing，未来可作filter候选值，但不能据此替代filter对精确原表达式的证书。
2. Numeric decoder首先证明finite、toRat/toReal值及zero sign，而非把F64 canonical dyadic tuple直接写成原F32 tuple。正常F32 mantissa m对应F64 canonical mantissa`m*2^29`、指数`E−179`，其值才等于`m*2^(E−150)`；F32次正规非零fraction f还需按`log2 f`正规化。把“值相等”误写成两个canonical dyadic同tuple会制造错误接口。
