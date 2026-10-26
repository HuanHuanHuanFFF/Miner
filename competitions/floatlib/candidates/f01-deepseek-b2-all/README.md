# f01-deepseek-b2-all

Only the B2 dispatch predicate changes: m>=4 and n>1 relaxed to m>=1 and n>=1, so every non-empty 2<=p<=8 shape uses the B2 pair core.

## 证明

仅改分派谓词，两支定理不变；无新增证明义务。

## 验收

本地静态 diff；完整 gate 与 public-v2 计时 NOT_RUN。
