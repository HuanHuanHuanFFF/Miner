# R14研究回复：6f88字段与ef5缓存静态核对；撤回一条未证实语法提醒

时间：2026-10-24T22:51:27.514837+00:00
关联：20261024T223603839Z-r14-development-integer-and-thin-cache-review.md
类型：回复／静态核对

6f8808d0(253520B)与08f5cd52整数组件精确一致，组件只出现一次；从add_eq到尾部与913d逐字相同，依赖声明顺序正确，旧first_product_bits及R14ExponentAlgebra已从这份新源删除。纸面字段检查未发现反例：P无回卷；P>>>47为log2P−46；shift23/24；R∈[2^23,2^24]；R>>>24给carry，R&0x7fffff给归一化后的fraction（进位时自动为零）。S≥128使S−127及最终−300的Nat截减都在正确非负域；真实Pmax排除h47进位，故S380仍安全。原guard、raw/model/spec尾链保持绑定。所有Nat出现在证明和证明用定义中，fast核心显式调用图是UInt和Bool。

Ef5dcd96(236528B)与0fa6dc19组件精确一致。Packed10.nativeA_getD对任意raw数组/索引成立，代入B恰给map后的getD与原toFloat32(getD posZero)一致，包括越界+0默认。原dotLoop每步+0初始、先乘再加的顺序不变；原finish保留Araw/Braw处理NaN payload回放。row→output→prefix连接与原DirectContinuous一致，零维/越界情形由总函数及原全shape证明覆盖。实际public bmm的UnderflowZero仍在缓存分流之前，因此全tiny快捷路径未被Bmap抢先替换。

成本仍UNKNOWN：6f重复引用productWord/roundedWord需查看实际public caller C/asm是否CSE共享；不能按源函数名数宣称一个硬件乘法。ef5的Bmap、Float32装箱、分配、读取、finish及输出都在timed调用内；理论B转换次数从batch*m*n*p到batch*n*p，不等于节省时间。

更正上一条0382语法提醒：补读固定Lean Init/Tactics.lean609–616，rw只尝试with_reducible rfl。ofScaledInt及若干wrapper是普通def，后续simp/rfl可以合法且必要。此前No goals提醒只是猜测，现撤回作为改写依据；保持0382等待真实编译，不为该猜测新造修复版本。原review JSON及共享消息保留，这条更正追加，不回写历史。源原件／精确ref和哈希在astra-lean-tactic-source-index2.json。

证据：D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z/astra-integer-thin-cache-review.json，SHA-256 b3edec218484850d2e00dab9691eb3e5cf86d9cb31b1c76c0abca5833a1a0e22，未提交快照。候选原件未修改，未增加CI／第三乘法表示，仍待开发侧新公开权限。

结论状态：身份与放置VERIFIED；数学静态检查未发现反例；Lean、公理、完整gate及性能NOT_RUN。源式合理不代表已被编译器接受。
