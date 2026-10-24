# f01-deepseek-directall

Extreme routing probe: p=2 leaves Cross and DirectContinuous's guard becomes `(n ≤ 4 ∧ 2 < p) ∨ p ≤ 64`, so every scored p<=64 shape uses the direct row writer; only p>64 can still reach DirectSmall/Packed10. No other runtime bytes change.

## 假设

Brackets the packed path's value: if direct wins even at p=32/59, the Packed10 preparation and lane padding are pure overhead on this suite.

## 证明

分支条件改动，两支都有全形状定理；无新增证明义务。

## 验收

本地仅静态 diff；完整 gate、公共套件与性能 NOT_RUN。
