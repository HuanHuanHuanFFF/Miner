# 27/28位GRS加法：广normal域与一次数值舍入

状态：纸面推导/有限整数模型；Lean、真实C/ASM及性能均NOT_RUN。R窗口至UTC2026-10-27 02:28:21。先20min判别，不抢DirectBias/Dual证明槽。

## 与历史的实际差异

旧f01-grs-normal-add-prototype/6bef4c4b（35105B）外层只接同号，使用UInt64 GRS、手写RNE和未可达异号UInt64.log2；39575344774为bench-only/旧参照1.096087，含显式sorry，非可采用源码。R16 f7f的UInt32数值舍入接线仅限gap≤7且拒绝部分异号低N，ADD/B2负1.87392；R18真正ADD也已负，保留原结果。

本提案不新称GRS/RTO机制：接纳两个normal有限输入的全部符号/指数差，先把精确对齐和压为不足28位，再一次UInt32.toFloat32.toBits同时给RNE、leading和carry，取消UInt64.log2/手写round/reverse numeric cast。仅运行差异值得最小代码成本判别；不能由更广覆盖直接推断收益。

历史成本收紧：runtime worker随后核R16 f7f的实际selected ADD已是一次UInt32.toFloat32和一次toBits、没有table/FP加乘；因此本提案相对f7f并未减少cast数量，去UInt64/log2/手写RNE只对应更老GRS或其他运行稿。相对f7f的实质差异是sticky允许广指数差及真实异号低T覆盖、共享一次raw排序/字段；重复排序目前仅C层观察，无ASM或退化因果结论。

参考一手源：John R. Hauser/UC Regents，SoftFloat3固定497c81c1f5016dc6ef5b3219ece2f3c261d4d8f1，[addMags](https://github.com/ucb-bar/berkeley-softfloat-3/blob/497c81c1f5016dc6ef5b3219ece2f3c261d4d8f1/source/s_addMagsF32.c)、[subMags](https://github.com/ucb-bar/berkeley-softfloat-3/blob/497c81c1f5016dc6ef5b3219ece2f3c261d4d8f1/source/s_subMagsF32.c)、[shiftRightJam32](https://github.com/ucb-bar/berkeley-softfloat-3/blob/497c81c1f5016dc6ef5b3219ece2f3c261d4d8f1/source/s_shiftRightJam32.c)。原BSD3版权及原NaN/flags语义不移植；本项目保留自己的全输入回退。

## 精确对象与运行草式

双方输入字段e∈1..254，m∈[2^23,2^24)。只在此域按绝对raw字排序大/小输入；相同指数也比较尾数。令e=eBig，d=eBig−eSmall≥0，X=8mBig，Z=8mSmall/2^d。

令J=jam(8mSmall,d)：d=0原样，0<d<32用商OR非零余数，d≥32返回1。不能依赖UInt32对≥32移位的模32语义。同号T=X+J，异号T=X−J；0≤T<2^28。T=0只可能精确异号相消，直接+0。T>0时：

```
r = T.toFloat32.toBits
E = (r >>> 23) + eBig - 153     -- UInt32运算
if E - 1 <= 253 then
  signBig | (E << 23) | (r & 0x7fffff)
else 原B2 fallback
```

E测试必须在无符号回卷后做上述区间检测，不能只把E遮成8bit后判断normal；负E会回卷为很大UInt32而被拒绝。该范围E数学值位于[-25,256]，不会回卷为小的合法正指数。公开入口仍须normal guard，所有miss保持原NaN payload/Inf/±0/次正规/overflow语义。

## 纸面舍入归约与关键边界

1. d≤3时8mSmall被2^d整除，J=Z，T即精确缩放的绝对和；相消低N无需clz，硬件数值舍入处理所有T。
2. d≥4时，Z<2^23，X≥2^26，故异号精确X−Z>7·2^23>2^25；同号也≥2^26。设floor(Z)=q、余数非零，J=q或q+1且为奇数。X是偶数；所以X+J以及X−J分别是精确X±Z的round-to-odd整数：余数为零时精确；非零时取相邻奇整数。此处必须验证减法方向，不能把加法jam定理无条件替换成减法。
3. 正round-to-odd不会跨过2的幂边界：边界前floor=2^k−1已为奇数，无向上跨界。T与精确正绝对和具有同一leading指数；d≥4已保留至少2个目标RNE舍入位。经典RTO→RNE归约因此给RN24(T)=RN24(精确X±Z)。这是待形式化的一般变量d归约，现Jam17仅固定drop17/k6或7，不能直接称其已覆盖。
4. 实际绝对和为精确(X±Z)·2^(eBig−153)。只在原rounder normal分支及含carry的finite上界闭合后才允许raw指数平移。**postE normal不能无条件推出原normal分支**；已有R14反例必须保留。
5. 此域可补normal前提：d≥4⇒eBig≥5且leading≥25，故精确原指数≥−123，安全。d≤3的T精确；无carry由postE下界直接推出原normal，carry时leading≥24，eBig≥3也安全。剩余eBig1/2需整除性：d≤eBig−1，T可被2^(4−eBig)整除；在可能pre-subnormal的leading+eBig≤26处，该整除性排除RN24进位。不能省略这一小指数桥。
6. T.toFloat32的primitive语义、typed UInt32移位/加减不回卷、signed raw packing、从Model.add回原四spec的桥仍需固定Lean4.34真实验收。没有Float64算术或opaque跨宽假设。

## 最小证伪与成本

astra-grs-add-model.py用了独立精确整数IEEE加法oracle（按共同指数求和、原RNE、次正规量子及overflow处理），不是宿主Double近似。95,664例中93,817个提案命中、312个+0、1847回退，零差异；含E1/2、gap0/1/3/4/25/26/31/32/33/253与尾数边界。范围仅这些定向/随机例，不是全输入证明，也不作基准命中率或速度估计。

下一最小动作：先独立查上述RTO减法/低E桥的反例，再由runtime worker对旧精确调用核是否实际省Uint64 conversion/log2/RNE分支、是否新增排序/jam/postguard成本抵消。若值得一次诊断，可附原B2后仅定义新诊断函数，不用sorry、不改公开算法/spec；真实完整public版本另作证明/完整gate。若其成本与既有负源实质相同则停，禁止换名或改seed。

影响上界未知；潜在对象是约36%整包ADD主路径，但不是36%可消除。需原始调用成本及实际广覆盖证据后才给整包预测；新证明/字节预算和首完整反馈时间均UNKNOWN。

补充核验：astra-grs-add-oracle-review.py另用统一2^-149整数单位、按IEEE正字顺序二分寻找最近两邻居及ties-even/overflow阈值，独立核2056例，与原整数oracle及提案命中均一致；不复用原RNE商余辅助函数。该核验只提高有限检查器的可信度，不提升为全输入证明。4份固定SoftFloat加法原件/许可证共14000B已先E:/Download/FloatLib/20261027-R19/softfloat-add-497c81c1，再逐字节整理至astra-source-intake/softfloat-add-497c81c1；原URL/时间/SHA保留，无ZIP。
