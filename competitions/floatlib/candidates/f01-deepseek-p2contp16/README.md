# f01-deepseek-p2contp16

Same as p2contp8 but the DirectContinuous guard is widened to `p ≤ 16` instead of `p ≤ 8`; p=2 leaves Cross. Tests whether the sparsely occurring p=9..16 cases also prefer the direct writer. No other runtime bytes change.

## 假设

p=9..16 cases carry 4-8% of scored BMM work by seed; if direct wins there too the threshold can move without touching larger packed shapes.

## 证明

分支条件改动，两支都有全形状定理；无新增证明义务。

## 验收

本地仅静态 diff；完整 gate、公共套件与性能 NOT_RUN。
