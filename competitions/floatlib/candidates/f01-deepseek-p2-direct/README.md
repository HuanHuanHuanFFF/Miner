# f01-deepseek-p2-direct

Only the p=2 Cross guard changes: `4≤batch*m` becomes `batch*m < 4`, so p=2 shapes with batch*m>=4 fall through to the proven DirectSmall scalar-dot core instead of R11CrossRows. No other runtime bytes change.

## 假设

R11CrossRows packs four rows and two columns (8 outputs) through the p=2 Cross machinery; direct scalar dots may avoid its fixed packing/output overhead at the cost of reading A twice per row. Public-v2 dense, sparse and extremes groups hold most p=2 scored work.

## 证明

分支条件改动，两支都有全形状定理；无新增证明义务。

## 验收

本地仅静态 diff；完整 gate、公共套件与性能 NOT_RUN。
