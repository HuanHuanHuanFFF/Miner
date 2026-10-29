# 原生双精度结果的严格单精度舍入证书

状态：R数学推导与精确有限模型，尚未Lean验收、原生计时或整包采用。外部Pro正在独立反证；本条与A的实际fold误差证明并行，不以等待替代推进。

## 要消除的工作

前一方案对区间两端各调用一次完整binary32整数rounder，包含leading、GRS、subnormal/overflow和pack。此处改成：任意proposal的一对精确RNE32 midpoint word、两次binary64加减、两次word严格比较。proposal可由opaque cast产生，因为验证声明量化任意raw32，不需要证明cast正确。失败仍需原精确路径；不是免费转换或整个kernel的性能结论。

## 边界的直接word构造

设q的绝对raw word为a，指数1≤e≤254，fraction f。记w=((e+896)<<52)|(f<<29)，它是q绝对值的准确binary64编码；δ=2^28。正数q的上midpoint编码为w+δ；下midpoint为w−δ，**唯独a=0x00800000时减2δ**。负数q在两端OR sign64并交换顺序。零、subnormal、Inf、NaN proposal拒绝，由原路径处理。

普通binade内，raw64每步实值2^(e−179)，δ步即半个binary32 ULP。f=0跨binary64指数界时，低侧ULP自动减半，仍减同一δ就得到binary32的低侧半ULP。最小binary32 normal的低侧是subnormal，原spacing不减半，所以须额外乘2。最大有限值上侧与virtual next=2^128取中点，结果仍是有限binary64，正好是overflow midpoint。严格证书不需要处理中点归属和even parity。

`midpoint_word_model.py`以Fraction独立比较相邻数学值中点：254个指数场×7个fraction×双sign，共3556件，0不一致；不是遍历2^32个word或数学证明。统一δ在最小normal生成偏内边界，已留具体反例；最终构造包含特例。原始结果和脚本hash见`midpoint-word-model-results.json`。

## 为什么不必向外round

令s是有限实际binary64累加结果，精确目标S满足|s−S|≤B，B≥0且可准确表示。实际有限加减得rlo=RNE64(s−B)、rhi=RNE64(s+B)。若lower<rlo且rhi<upper，则由RNE64单调和RNE64(lower)=lower，反证可得lower<s−B；同理s+B<upper。因此S严格位于q的RNE32 cell内，RNE32(S)=q。两midpoint非零，故S≠0，并确定q的sign；精确零与ties全部拒绝，原路径保留其规范零／IEEE符号语义。

这不是rlo≤S≤rhi的声称，也没有把nearest rounding误当outward rounding。需要实际native加法语义、有限性、B界及准确midpoint分别连接，缺一不能采用。当前MUL桥、widen桥、fold误差和此checker是不同组件；组合新源另验。

## Word比较

对finite binary64 raw u，用key(u)=~u（负数）或u xor2^63（非负），在无signed-zero相等边界时严格保持实数序。−0和+0的key不同，但本证书两边界非零；若rlo或rhi是零，其与非零边界的严格关系仍准确。NaN不能经此key获得实数序，必须由已证finite或运行guard排除；不能仅以q normal替代rlo/rhi finite。

## 仍须购买的判别证据

输入产品精确时，原条件n≤2^L,L≤30,H≤506给B=2^(H+2L−303)，可正常binary64编码，s±B远未接近max64；实际fold证明由A负责。bias必须计入count和H。H若由行／列最大指数之和作上界可省额外scan，但会放大B；命中率损失UNKNOWN，不能悄悄换成精确H。

成本账应包括输入guard/widen或cache、H/count、累加、proposal、2个endpoint、word边界/比较、fallback的已损失前缀以及原精确处理。先比较同一输入上的完整“检查+可能重算”成本与原精确128路径；不要只比较末端2次rounder。短dot的固定成本可能占主导。当前正式新target仍待人类选择，本条不启动新12kernel或新target计时；D可决定是否在允许的旧环境做通用component诊断。

复核只针对最可能错的midpoint/strict反推/原生接口；Pro反馈若无反例不自动新增验收。无实测前，不写命中率、成功概率或整包提速。
