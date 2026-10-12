# PC 相邻 token 向前合并：无需另开实验的域排除

等待 A12 计时时，检查了另一种跨token设想：当前match已查到后，若它紧邻上一输出match，尝试沿上一距离延长上一token，把两者合成一个≤258的match。这与A2向后移动边界并不相同，但对当前PC core存在更直接的可行性阻断。

原PC `probe_m`、`probe_lazy` 和 `f_try` 的实际长度都来自 xlen/common 的最大相等前缀，最多258或输入尾界。若上一输出match长度a<258且其后仍有输入，则在它的结束位置E，字节 `s[E]` 必然不同于 `s[E−d_previous]`；否则原比较本应继续。backward fold只改变开始位置和长度，保持结束E及距离d，故不消除这个结束处失配。若原匹配因258截断，fold没有继续后移/增大它的空间，输出仍是258，不能再和下一token并成≤258。

因此，对这些未经拆分/截断的PC匹配，紧邻的当前match不能沿上一距离覆盖哪怕第一个字节；对“合成一个token”的前向合并，非尾端域为空。无需添加一次字节尝试，更不应在真实匹配主循环上付重复验证成本。

边界：这不是全仓库所有引擎的定理。ET长度符号分片、BFRAW固定len3、其他主动截断匹配可能不满足最大性；也不排除**跨一个真实literal gap之后**再尝试以前距离（R11 gaprepeat / R25 gap1），或max258之后产生另一个token（R11 continuation），这些已有不同的历史负例。它也不排除A2通过不同的当前距离吸收上一match后缀。

VERIFIED源码依据：PC xlen/xlen16/common 1553–1612、probe_lazy 1623、probe_m 1759、f_try 1901；fold保持结束的原Lean BackInv及fold_w规格2101、2172。INFERRED：上述基于源码最大性的非形式化数学排除；未新增Lean或全输入机器证明。决定：不实现这条相邻forward-fold变体，不消费CI。
