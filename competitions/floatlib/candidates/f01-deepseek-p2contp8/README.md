# f01-deepseek-p2contp8

p=2 with batch*m>=4 skips R11CrossRows and the DirectContinuous guard is widened to `(n ≤ 4 ∧ 2 < p) ∨ p ≤ 8`, so both p=2 rows and 3<=p<=8 rows use the direct writer instead of DirectSmall or Packed10. No other runtime bytes change.

## 假设

One direct row writer for all p<=8 avoids both the Cross packing and the DirectSmall per-output decode; tests whether DirectContinuous generalises better than DirectSmall.

## 证明

分支条件改动，两支都有全形状定理；无新增证明义务。

## 验收

本地仅静态 diff；完整 gate、公共套件与性能 NOT_RUN。
