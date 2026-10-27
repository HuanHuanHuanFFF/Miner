# R19外部数学与源码判别

六份原件先保存到`E:/Download/FloatLib/20261027-R19/mpfx-8bd80452`，再按原Git blob SHA及字节数核对、整理至本目录。共30470B，无压缩包；不存在待删除ZIP。原MIT许可证保留。精确版本`bksaiki/mpfx-lean@8bd80452927ae9234fc378c07a00f2962e1e5b6f`，下载映射及SHA-256见[intake-receipt.json](intake-receipt.json)。本地未构建，源文件存在不等于在本赛道通过。

[Boldo／Melquiond原论文](https://guillaume.melquiond.fr/doc/05-imacs17_1-article.pdf)的round-to-odd再RNE机制要求足够中间精度并处理指数边界；[SoftFloat原实现](https://github.com/ucb-bar/berkeley-softfloat-3/blob/master/source/s_shortShiftRightJam64.c)提供右移并保留sticky的成熟实现思路。这里没有引入C实现、外部调用或库二进制。Jam17不是新发明，待验证的新工作是把该机制接到固定Lean primitive与本赛道精确public MUL。

[MPFX论文](https://arxiv.org/html/2610.09005v2)与[作者证明库](https://github.com/bksaiki/mpfx-lean/tree/8bd80452927ae9234fc378c07a00f2962e1e5b6f)提供抽象格式的包含及双重舍入结论。亲读现版本：`Nearest.lean`的`roundsRTO_RN_finite`保留格式扩张/有界性等假设；`Mul.lean`用精确可表示的中间乘积消除一次舍入，要求中间精度至少两倍输入精度。源库固定Lean／Mathlib4.29，而赛道4.34只导入ContractTensor；其Dyadic/Real关系也未连接FloatLib编码、符号零、NaN和四项原义务。因此本轮只借鉴证明分解，不做整库迁移，不将论文速度或Lean声明转记为本赛道收益/闭合。

根主控独立检查Jam17的关键整数关系：写`P = 2^17 V + r`，再写`V = 2^s q + v`；`J = V OR [r≠0]`，实际`s=6或7`。最低位置sticky不改变`q`；当`v`恰等于half且`r≠0`，half为偶数，所以sticky使其严格大于half，保留原数的tie方向。其它below/above情形不跨越half，exact tie仍由q奇偶决定。不能把这条证明随意推广到`s=1`：丢1位、P=5时，jam=3，RNE(3/2)=2而RNE(5/4)=1。完整Jam17源码仍须真实Lean、重放、公理和完整gate验收，文献与纸面检查不替代它们。

决定：继续Jam17最小接口和真实caller成本；暂不投入高迁移成本的Mathlib/Real大证明。原件/作者/许可已可定位，速度、工具链迁移与正式采用均UNKNOWN。

本3.5h增量：[SoftFloat加法4原件](softfloat-add-497c81c1/README.md)，14000B，先E盘后逐字节整理，BSD3保留，无ZIP；机制边界见本轮astra-grs-add-paper.md。
