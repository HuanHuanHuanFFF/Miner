# f01-deepseek-directallfull

Unbounded routing probe: p=2 leaves Cross and the DirectContinuous guard becomes `(n ≤ 4 ∧ 2 < p) ∨ p ≤ 1000000`, so in practice every shape uses the direct row writer. DirectSmall/Packed10 remain in the kernel with their proofs but are unreachable for scored sizes. No other runtime bytes change.

## 假设

If the direct row writer is competitive at every p on the public suite, the packed preparation and lane padding can be dropped as dead cost.

## 证明

分支条件改动，两支都有全形状定理；无新增证明义务。

## 验收

本地仅静态 diff；完整 gate、公共套件与性能 NOT_RUN。
