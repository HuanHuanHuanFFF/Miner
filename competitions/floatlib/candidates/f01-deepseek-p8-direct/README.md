# f01-deepseek-p8-direct

Only the bmmBeforeDirectRows predicate changes from `n ≤ 4 ∨ p ≤ 2` to `n ≤ 4 ∨ p ≤ 8`; shapes with n>4 and 3<=p<=8 use DirectSmall instead of Packed10. No other runtime bytes change.

## 假设

Packed10 pads every row to 10 lanes, so p=3 wastes about 70% of its lane work; the direct scalar core may win for short p even though it re-reads A.

## 证明

分支条件改动，两支都有全形状定理；无新增证明义务。

## 验收

本地仅静态 diff；完整 gate、公共套件与性能 NOT_RUN。
