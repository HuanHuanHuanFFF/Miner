# 偶平移 jam 的加减桥

本件只做自然数数学桥。`JamTranslate.lean.inc` **3400 B**，SHA **c9e0cfb3b59f7eb45f8c5cdc281eb54b4598b080c2c43aae100e04df12237542**，依赖冻结 `JamVariable.lean` / a78a，原文件不改。新片段无新增运行定义、无占位证明；**Lean NOT_RUN**，不是公共ADD证明或候选。没有CI请求。

## 精确陈述与纸面闭合

对 D>0、X%2=0：

`jamDiv (X*D+m) D = X+jamDiv m D`。

若另有 m≤X*D，则：

`jamDiv (X*D-m) D = X-jamDiv m D`。

写m=Dq+r，0≤r<D。加法的商为X+q、余数r；X偶使商的奇偶与q相同，故sticky增量完全相同。

减法分两支。r=0时差为D(X−q)，jam精确保留。r>0时，由Dq+r≤DX得q<X，且

`X*D-m = D*(X-(q+1))+(D-r)`，`0<D-r<D`。

记s=X−q−1。X偶意味着s与q奇偶相反：

| q | 原m的jam | s | 正差的jam | X−jam(m,D) |
|---|---|---|---|---|
| 偶 | q+1 | 奇 | s=X−q−1 | X−q−1 |
| 奇 | q | 偶 | s+1=X−q | X−q |

这也保证右侧自然数减法没有被sticky额外推成错误借位：r>0时q+1≤X。m=X*D只在r=0分支，结果为0。

片段中只有独立的 `complement_sticky(X,q)` 使用omega，并显式拆q%2=0与非0。它的上下文没有D或D*q。乘积借位恒等式在 `borrow_decomp` 中由加法重排、乘法分配、两个 `Nat.sub_add_cancel` 证明；完整商块由 `jam_block` 的原div/mod API剥去。不会把p和D*q同时丢给算术自动化。

新增 `jam_scale` 对任意正整数s证明：

`jamDiv (s*p) (s*D) = jamDiv p D`。

商用 `Nat.mul_div_mul_left p D hs` 消去s；余数用 `Nat.mul_mod_mul_left` 化为s*(p%D)，其是否为零由s>0保持。D在该缩放引理中甚至可为0，但所有实际平移应用均明确D>0。

## GRS对原整数P的尺度

只处理本轮d≥4分支。记a=mBig、b=mSmall、X=8a、δ=d−3、D=2^δ。于是2^d=8D，且运行纸面的sticky数

`J = jamDiv (8*b) (2^d) = jamDiv b D`。

定义原共同指数下的整数 `P± = a*2^d ± b`。因为X*D=a*2^d，**P±同时就是X*D±b，不再含一个多余的8因子**。X偶；normal尾数与d≥4给b<X*D，所以减法前提成立。两个平移引理立即给

`T± = X±J = jamDiv P± D`。

因此对已选k∈{2,3,4}，前一轮变量jam引理给：

`roundShiftRightEven T± k = roundShiftRightEven P± ((d-3)+k)`。

这里必须是 **(d−3)+k**。P是原共同尾数整数，其实际二进制尺度是2^(eSmall−150)；P/D对应原纸面W，乘回2^(eBig−153)同值。后续连接Model.add时需保持这一尺度，不可把Jam17式的d+k机械搬到这个已消8的P上。

剩余桥没有被这些恒等式替代：真实UInt32的d≥32分支/掩码/移位、T/P的leading与k、数值Float32 primitive、normal/carry/overflow/字段/符号、原Model.add与公开spec。d≥4的W>2^25范围允许既有大leading论证；这里不声称在0<W<1时jam保leading。d≤3与合法小T=4仍属于精确对齐路径，须另接既有小整数primitive接口。

## 接口、检查与下一决定

八个新增 theorem 根：`jam_block`、`jam_mul`、`jam_add_even`、`complement_sticky`、`borrow_decomp`、`jam_sub_decomposed`、`jam_sub_even`、`jam_scale`，均在R19JamVariableProbe内。不是请求现在扩CI名单；如以后组合，需把依赖的a78精确版本一并验证。

用到的新增实际API已从保留Lean4.34源码核：`Nat.mul_add_mod'`（Nat/Lemmas:1578）、`Nat.mul_sub_left_distrib`（Div/Basic中实际调用）、`Nat.mul_div_mul_left`（Div/Basic:461）、`Nat.mul_mod_mul_left`（Div/Basic:405）、`Nat.lt_of_mul_lt_mul_left`、`Nat.sub_lt`、`Nat.sub_pos_of_lt`、`Nat.sub_add_cancel`。没有新增import；和先前ContractTensor环境共用。未编译风险仍是具体tactic/API接线，不能从纸面恒等式推出Lean通过。

`check_translation.py` 的有限检查：279873加法、219985有界减法、279873缩放、256个normal尾数边界GRS桥和768个舍入等式均无差异；这些是公式回归检查，不是全输入证明或计时。必要偶性反例D=2,X=1,m=1：加法两边1/2，减法两边1/0。完整范围与哈希见`translation-check.json`。冻结a78逐字未改，exact目录/本地Lean/Git/CI均未触碰。c598真实目标到达即抢占回Dual。
