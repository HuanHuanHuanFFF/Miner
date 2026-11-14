# 一手来源与当前精确合约的适用边界

- [Lavin、Gray，Fast Algorithms for Convolutional Neural Networks](https://arxiv.org/abs/1509.09308)：空间Winograd是已有路线；作者另公开[算法生成器](https://github.com/andravin/wincnn)。本轮不把F(2,3)变换本身称作原创发现，新增工作是与现有exact词内核的接线、字长边界和反例。没有复用作者完整源码。
- [Liu等，Efficient Sparse-Winograd Convolutional Neural Networks](https://arxiv.org/abs/1802.06367)：作者指出变换会填密；其方法移动ReLU并在变换域剪枝。**这些模型改动不能作为当前逐字等价合约的直接实现**。本轮仅借它核实“稀疏收益不能直接叠加”的研究背景；保留原权重和函数，按运行时guard回退，不能使用重训或精度损失换速度。
- [Lean官方Array说明](https://lean-lang.org/doc/reference/latest/Basic-Types/Arrays/)说明唯一引用关系影响原地更新。此latest文档只作一般机制背景，实际4.34编译行为仍须查固定源及生成C/ASM/完整成本；`@[inline]`不构成临时tuple已经消除的证据。

访问在本轮完成。CVF论文PDF端点返回403，保留失败事实，未绕过或改客户端伪装；改读同一作者公开arXiv摘要及作者仓库。没有将GPU论文速度迁移成这里CPU/Lean的预期成绩。

一个可检查的拒绝例：1D输入[1,0,2,0]、权重[1,0,0]，正常F(2,3)第一输出1；若先对B变换的[-1,2,2,0]做ReLU，再其余变换，第一输出2。两值都正，末端ReLU也不能消除差异。二维外积嵌入同样给1→2。因此“在变换域做ReLU”不是保持本合同的合法优化，见`relu-domain-counterexample.json`；这不否定不移动激活的整数Winograd。
