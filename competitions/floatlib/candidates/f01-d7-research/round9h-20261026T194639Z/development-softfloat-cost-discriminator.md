# Jam17后续成本判别参考（不抢当前证明修复）

一手源固定ucb-bar/berkeley-softfloat-3／497c81c1f5016dc6ef5b3219ece2f3c261d4d8f1，作者John R. Hauser／UC Regents，BSD3-clause及源码头完整保留在development-source-intake/softfloat/。f32_mul.c使用有效位扩展、乘积右移jam及31位规格化，roundPackToF32使用固定7位整数RNE；这不是未知原创机制。未把C加入候选或链接库，未继承其NaN payload策略或其性能。

与本轮路线的可证伪差异：现Jam17用UInt32→Float32→UInt32承担RNE；公开软件实现说明，可另比较**规范化jam31＋固定宽UInt32偏置/最低位清除**，从热路彻底去掉这两个cast。它仍须保留normal域/范围/进位与溢出及原fallback。旧9038/r14-mul-cache-rse2明确调用泛型FastMul.rseAny，64位可变shift=23+high；因此不能拿它的1.2908×直接证明固定32位/固定7位实现无机会，也不能反过来声称新法一定更快。

请R在当前f784的真实目标修复后再比较：是否能复用rne_jam，先构造最小完整guard/caller并检查真实选中C/ASM的转换、可变移位、调用与live寄存器，确认新的成本前提，再投入完整规格。新基于SoftFloat的Lean实现若复制或实质改编源码，保留版权/许可证和准确归属；只借机制也记录来源。当前预期whole收益与新Lean/fullgate均UNKNOWN；不要求同时排两个近似变体，不修改原gate或编译选项。

资料：固定版本source/f32_mul.c、source/s_roundPackToF32.c、source/s_shortShiftRightJam64.c和COPYING.txt，原URL／时间／字节／SHA见同目录receipts.json。BSD数值代码只是机制参考；IEEE逐位等价仍由本赛道完整原义务验收。
