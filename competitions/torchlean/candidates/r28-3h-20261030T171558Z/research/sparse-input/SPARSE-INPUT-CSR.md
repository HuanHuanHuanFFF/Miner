# 先压缩非零输入支撑，再复用原精确双输出内核

状态：**纸面归约 + 有限整数模型；未实现Kernel、未Lean编译、未计时**。这是与逐项if跳过不同的数据组织路线。新前提是公开Mobile53完整强路径、实际pointwise小通道与B的旧已见完整模型零密度；不是重跑R27 FP/Band。

逐项skip即使命中很多，也可能因不可预测分支、临时元组或调度成本失败。另一条路线是在pointwise卷积准备时，为每个空间位置建立升序非零通道支撑；所有输出通道复用该支撑，内层只遍历非零记录。它保留原精确UInt64累加、bias上下文与fallback，不用负输出归零，也不改变relu=false。

## 63位记录恰好可装本轮完整narrow域

source53的narrow guard给输入指数跨度（相对xm）≤31，所以已对齐幅度`M=mantissa << (index-xm) < 2^55`。原缓存编码为`X=Z+sM`，`Z=2^57`，s∈{-1,1}；M=0就是Z。令`C=2^55`，对通道i<128编码

`payload = i*2^56 + (C+sM)`。

有`0<C+sM<2^56`、`payload<2^63`；它在64位Lean的Array Nat中仍可保持smallNat（已有固定runtime证据，实际新ASM未知）。恢复

`i = payload >>> 56`，`X = (payload &&& (2^56-1)) + 3*2^55`。

两式精确，无需Float raw carrier、第二个index数组或每项变动移位。M=0的记录直接不存；全零位置支撑为空。cin>128、wide或不满足原guard时继续旧完整路径。这样覆盖的是原narrow≤31域，不把R27的40bit-factor+20bit-index限制偷换成这里的全域。原缓存X仍小于2^58；pack与decode都在UInt64安全范围。

## 需要证明什么

新支撑保留原通道升序。对任意UInt64权重w，旧`Y9 Z w=0`、`cq1 Z w=0`，故从原双输出fold删除X=Z项保持所有四个累加器**逐字一致**，即使发生模64回绕也成立；不需要额外假设总和不溢出。原bias finish、sentinel及从原raw输入计算的精确零/-0 fallback保持原样，因此不能顺便删掉零 provenance。

`SparseFoldIdentity.lean`只是这个通用fold删除恒等步的未编译桥，不是实际producer或Submission.correct。仍须绑定：原narrow guard推出实际aligned getter界；payload producer大小/索引有效与升序；每条CSR记录恢复原P2；实际weights原索引访问；qCtx7迭代及最终bias/fallback；pointwise布局；原all12 gate。不能用新支撑丢掉非有限检查或既有weight-sparse路线。

## 实际成本决定

旧已见18个Mobile完整公式模型里，pointwise逻辑MAC占全部conv MAC约28.28%；其中输入零且权重非零的项，占全部原非零权重MAC约12.0–12.9%。这是**操作计数，不是整模型时间上界或速度**。改为CSR仍要付通道次序转置、计数/行指针、pack/index decode、准备/释放和回退；保留weight-sparse时还要解决输入支撑与权重支撑的交集，不能把两边省项相加。

初始实现应只作用pointwise、cin≤128且原narrow域，替换原密集准备；若为探针先保留原P2再建CSR，必须把这项额外缓存和drop计入，并明确不能宣称已移除原准备。统一flat payload数组+N+1个行指针，避免每像素新建一个Array；旧模型normal两层合计密集输入14807槽，CSR非零8101槽+2211指针槽，额外weight/cache成本不在这个数里。

最小实验是完整Mobile模型成本判别，优先与逐项skip结果比较原因；没有编译器/成本证据前不启动大proof producer。若pointwise本身时间份额低于目标差距，或完整准备抵消节省，就暂停当前shape；不把这项布局的未测量状态当负结果。
