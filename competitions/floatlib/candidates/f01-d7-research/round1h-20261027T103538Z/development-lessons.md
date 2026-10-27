# 本轮可复用经验

- 依赖count的writer证明，先用独立forall count=2桥、subst count和固定Fin.foldl_succ/zero；不要把List.finRange/Array.append化简误当rfl。该桥已在7de完整公共BMM通过，不必从失败dc1/dc2重猜。
- 条件先化成False时显式ite_false；size invariant明确Array类型、原emit展开和初始out。流式4e36的真实两行/任意p规格及19根已验。
- 减少F2分配已经进入实际public caller并产生完整D矩阵耗时−5.68%，但整包只有−0.85%且p05负。指令、分配或单算子收益不能直接当整包晋升。
- 同宽缩放7条实质桥接引理已验，仍缺实际U64product与原MUL原义务连接；单独定义的公理报告不替代新MULspec。
- 两行共享B必须在同一batch内，m奇数需每batch保留尾行，不能把扁平总行数直接两两配对。
- 历史重算先选与该run绑定的原adapter。本轮拒绝早期不匹配adapter，匹配末R19原件重算与记录逐值相同；未修改冻结验证器。
