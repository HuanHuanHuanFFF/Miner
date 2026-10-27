# 隔离后继：最低仿射编码段的整数ADD（仅数学模型）

R21主探针29d09/桥均已冻结；这里不造Lean运行体、候选或新CI，不扩大本轮投入。

binary32 raw无符号magnitude<2^24（E=0或1）时，数值恰为magnitude·2^-149。故同号输入求整数N=a+b；N<2^24时输出raw=N，N>=2^24时只需一次1bit ties-even：q=(N>>1)+[N&3=3]，输出raw=q+2^23。N<=2^25−2，无第二carry。异号取整数差的绝对值及较大幅值的符号，相等时+0；同号双−0仍−0。

严格子结论：若双方真subnormal/zero(E0)，N<2^24，因此连1bit舍入都不需要，结果可以跨入E1仍精确。这是表示本身的最大首仿射段性质，不是把旧GRS只换阈值：这里没有对齐、log2、Float32cast或toBits。R18normal-only不覆盖真subnormal输入，但其E1/E1分支可能重叠，负结果不得擦除；R19 d3c高指数preguard则排除本段。

20,676个定向/随机exact-integer oracle实例0差异，包含±0、minsub、最大subnormal、minnormal、1bit tie与最大系数，见low-lattice-model.json。未Lean、未接actualModel.add、未测实际caller/命中/miss损失；不能称全输入证明或整包高收益。常见零值单列才可能估机会，不能借旧zero shortcut已有负面包装新胜利。

真正后继只需先核旧已见生成计划中“两真subnormal”的独立覆盖与所处实际B2路径，再决定是否购买最小typed/cost probe。当前official336只有组比范围，不提供该路径权重；不得用1.304或旧op份额计算收益。
