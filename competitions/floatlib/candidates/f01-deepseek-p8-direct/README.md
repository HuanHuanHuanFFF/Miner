# f01-deepseek-p8-direct

DeepSeek 自由研究 agent 的第一条低成本分派实验。父本为当前保留候选
`f01-d12-scalar-combined`（`df5c61a0…`）。

## 机制

`bmmBeforeDirectRows` 的分派谓词由 `n ≤ 4 ∨ p ≤ 2` 改为 `n ≤ 4 ∨ p ≤ 8`。
`DirectSmall.core` 对任意形状都成立；此前 `n > 4` 且 `3 ≤ p ≤ 8` 的形状走 Packed10，
每行固定打包 10 列，`p=3` 时约 70% 的 lane 是填充。

## 证明

无新证明：`DirectSmall.core_eq_reference` 与 `bmmPackedBase_spec` 都是全形状无条件定理，
`bmmBeforeDirectRows_spec` 在谓词两支各自引用其中一条。改动只影响分派条件。

## 验收

本地仅做逐字节 diff（单行，248144 字节不变）。完整 gate、公共套件诊断与性能均为
NOT_RUN；需在临时 runner 上与 df5c 同 run 配对比较。
