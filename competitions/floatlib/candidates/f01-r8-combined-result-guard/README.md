# a84 + bee6：标量结果守卫组合

SHA-256：`41bce4856c4c921dd67b6115928df16e5e8ed08a55b71f1296d28b77cf9ce9a7`；235169字节，距256000上限余20831字节。

运行父本是`f01-d7-direct-singlepass-proof2`（a84c1618…），标量来源是`f01-d7-result-guard-both-proof2`（bee6ccdf…），最小改动的基准为`f01-d7-direct-nonnan`（60f74aa4…）。完整父本SHA在manifest和构建脚本内固定。

仅搬移原有NativeBridge、NotNaNProbe、R7Native闭合证明/类型别名块，插入原R7W04，并把add/nativeMul及其证明换成精确bee6版本。包含bee6已修复的add_spec目标规范化change。a84的单遍sum、NaN后缀、Nat/USize、矩阵布局和其他声明保持原字节；这些函数调用的scalar实现发生变化，不能继承完整路径性能。

构建器先完整重现60f→bee6的全部字节，再将相同7次操作应用到a84；逆操作恢复精确a84。另一种最长公共前后缀方法独立得到同一完整产物。未压缩源码或删除许可证。

`python build.py`只核验现有产物；首次构建可使用`--write`，已有文件时拒绝覆盖。脚本不操作Git/CI或网络。

静态policy、唯一四导出/四spec及namespace检查通过；**本精确组合Lean、完整gate、C/对象和计时均NOT_RUN，净收益UNKNOWN**。两个父本各自收益不能相加。

[接入说明](../f01-d7-research/round1h-20261023T110107Z/astra-composition.md) · [完整字节映射](../f01-d7-research/round1h-20261023T110107Z/astra-composition.json)
