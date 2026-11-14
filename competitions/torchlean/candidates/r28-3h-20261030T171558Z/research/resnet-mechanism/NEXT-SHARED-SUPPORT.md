# 对 Root200700 的接口补充（不用 CI6 数据）

A 的 support00928141 是“一个输入patch、两个输出channel”，缓存一份输入factor和index即可。Root的新线性/空间pair路线是“两份输入、同一weight”；不能直接把前者的一个factor字段当成两行共有值。

设非零支撑S0、S1，拆成B=S0∩S1、L=S0\S1、R=S1\S0。B热loop读一次weight、两份不同input，更新两行；L/R各只更新一行。独立两行版本读weight共|S0|+|S1|次；分三类版本读|S0∪S1|次，少|B|次，但增加分类/分段分派。若B存两份packed factor，物理payload项数仍是2|B|+|L|+|R|=|S0|+|S1|，不是union大小；不要误报内存减半。

字节预算还必须看生产者域：A的56bit payload+7bitindex依赖K<128。直接搬到K<2^20会需要76bit，不能称smallNat。只有实际已验证的decoded factor满足|X|<2^39时，重偏置为X+2^39可用40bit payload，加20bitindex得到60bit；该范围不能从某个consumer倒灌到未守卫的全局prepare。实际零编码也要按源核对：source11为2^57，父已核的source36 MxA为2^62，不是raw0。

三段只在原精确整数/模128累加域重排；两个输入行的最终尺度和bias上下文各自保留，不能把它们合为一个数。若总和为零，仍用各自原始word的zero-sign provenance。最小schema负控：X0=[1,0]、X1=[0,1]、W=[1,2]应输出(1,2)；只保存一个union factor并让两行复用，已经不足以表达这两个结果。

先保留原dense/odd/非有限/fallback，实测完整构造、gather、三loop和析构。上述只是布局/计数与接口约束，不是native收益、全12证明或新CI请求；下一轮必须新精确source和新确认组。当前A候选源码未变。
