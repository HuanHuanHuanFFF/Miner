# 输出融合的生成代码判别

候选 `f01-d11-bmm-fused-output`，精确 SHA 以其 manifest 为准。新候选的 C 尚未取得；以下是确认清单，不是实现已经产生目标机器码的结论。

历史可核查起点：run 40005234741、seed852 的 `diagnostics/f01-d7-public-suite/retained-stage-profile/profile-retained-original.c`，SHA-256 `fb421a595ceced1cf8994f19ccb32704ac20a02a0430eda6c4134bf042d075db`。该源属于保留41，其 Packed RowStream 与 a066 对应段相同。

- 第40711行起的 `RowStream_core_spec__0___redArg` 每行分配捕获 nativeA/packedB 等六值的闭包（40728），以 `l_Array_ofFn___redArg` 建 rowTiles（40740），调用 `RowOutput_row` 建行输出（40744），再 `l_Array_append___redArg`（40747）。
- 第40781行起的 `RowStream_core` 用 `l_Array_ofFn___redArg` 建行号 Array（40787）。nativeA 与 packedB 仍整批准备。
- 旧源已经可见上述构造；没有将源码层中间值的消失误认为编译器已消掉这些分配。

取得新候选的实际捕获 C 后，沿 `RowStream_core → RowStream_output → Fin.foldl.loop` 特化路径检查：

1. 行号、rowTiles、`RowOutput_row` 与逐行 `Array_append` 是否退出热调用图。
2. 输出 `Array.mkEmpty(total)` 是否传成一份结果数组；push 前是否增加输出引用或出现 `lean_copy_expand_array`，从而触发额外复制。只看到源码变量 `out` 不足以回答这一点。
3. 每行每组只调用一次 `Packed10Index.runDot`／其特化版本；lane emit 仅执行 finish，不重复点积。
4. 新 emit/group/row 的 Fin.foldl 是否成为直接循环；若有每组／每lane闭包分配，记录数量及捕获，不凭 inline 标记假定已消除。
5. 内层 MAC 与原 Packed10Index 保持独立 mul/add；终点仍使用原始 A/B 字的逐输出 NaN 回放。完整计时包含 nativeA、packedB、尾块、输出及销毁。

地址诊断 `layout-precheck.json` 仅覆盖有限 Python 整数布局，不证明 Lean、数组唯一引用、浮点或性能。
