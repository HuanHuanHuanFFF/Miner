# f01-deepseek-p2cont

p=2 with batch*m>=4 skips R11CrossRows; DirectContinuous's guard is widened from `n ≤ 4 ∧ 2 < p` to `(n ≤ 4 ∧ 2 < p) ∨ p ≤ 2`. DirectContinuous.core is proven equal to the reference for all shapes and writes each row directly with an Array.mkEmpty output, avoiding per-output decode div/mod.

## 假设

For p=2 rows, two direct dots with one shared row base may beat Cross's four-row P12 packing and its fixed preparation/output machinery.

## 证明

分支条件改动，两支都有全形状定理；无新增证明义务。

## 验收

本地仅静态 diff；完整 gate、公共套件与性能 NOT_RUN。
