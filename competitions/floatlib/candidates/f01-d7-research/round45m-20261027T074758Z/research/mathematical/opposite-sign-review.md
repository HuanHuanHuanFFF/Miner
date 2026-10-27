# root异号纸面桥窄审核

已核research/next-round/opposite-sign-absorption.md：raw guard给normal g>=26 / subnormal g>=25、m<2^(g−2)正确；M>2^23和M=2^23两log2/drop分支正确。e>=26保证binade分支舍前无偏指数e−128>=−102，确实避开subnormal rounder；e254归一化后仍不溢出。负acc还必须通过实际dyadic magnitude比较证明选原sign，不能只写对称。

有一处**术语必须区分**：binade分支“加carry后编码指数e−127”中的e−127是归一化**无偏指数**，实际stored/encoded指数应再+127得到e。公式本身正常，但Lean目标mkBits必须取e。另“输入非零normal”应仅修饰acc；小项允许非零subnormal。

本方SubRound.lean补了不含原大乘积自动化的round_mul_sub和rne_shift_sub，以及实际binade drop=gap−1得到2^24的接口。均无占位，但Lean NOT_RUN；不是all-sign raw guard→ExecFloat.add桥，也不恢复已NO-GO的SUM运行体。用户域/原顺序不变。
