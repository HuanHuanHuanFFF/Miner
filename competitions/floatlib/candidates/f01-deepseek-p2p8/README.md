# f01-deepseek-p2p8

Combines the p=2 Cross guard change (`batch*m < 4`) with the bmmBeforeDirectRows predicate change (`n ≤ 4 ∨ p ≤ 8`). Both edits only choose between branches whose unconditional correctness theorems already exist.

## 假设

Tests whether the two direct-routing changes compose: p=2 work plus 3<=p<=8 work leave the packed/Cross paths.

## 证明

分支条件改动，两支都有全形状定理；无新增证明义务。

## 验收

本地仅静态 diff；完整 gate、公共套件与性能 NOT_RUN。
