# 组合体积：先做局部依赖选择

当前 ebfb v2 为 254601 B，只剩 1399 B。以下是源码层面的备选削减，不更改已交付候选，也不声称删减后编译或计时已通过。

1. 最小进一步删除集是 `R21StreamingPair.controlPair`、`streamedPair`、`streamedPair_eq_control`：这些只服务两行诊断端点，实际公共调用从 `streamedRows` 开始；`controlRows`、两种 rows_size、emit_size 必须保留，D cost 的尺寸证明仍使用它们。若删除，audit 清单也删除该独立等式端点，不能再报原 19 根不变。
2. `R21StreamingMatrix.controlOutput` 没有调用点，可以作为单独小项；不要连带删 `DirectContinuous`，B2 fallback 仍会走它。
3. 若 MUL 仍放不下，优先替换新 writer 证明链：直接证明 D 的 pairs / rows / output 的 Prefix，不再通过 c3c3 的另一份 matrix 运行定义运输。D 的 `R22StreamingCost` 运行体可完整保留。这只涉及新增 BMM 证明，不整理原 B2 历史算术链；需要新源的实际声明、回放和公理审计，不能靠 grep 猜依赖已安全。

已经完成的四个无调用 theorem 削减原件、每段字节数和 SHA 在 v2 manifest，未抹掉超限原稿。没有看到正向完整成本前，不批量裁剪或重编译这些备选。
