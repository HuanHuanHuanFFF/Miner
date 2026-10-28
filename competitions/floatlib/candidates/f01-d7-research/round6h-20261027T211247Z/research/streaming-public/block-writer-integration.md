# 四行状态的最小公共运输接口

`BlockWriter.lean.inc` 为 **b6f6149f / 5932 B / 8 根 / NOT_RUN**，仅依赖原 4e36 已有的 RowStream、NativeFinal 和标准 Fin / Nat 接口，不依赖 c3c3 重复 matrix driver。未组装新大候选，未请求 CI。

若 D 的实际状态分别提供 s0/s1/s2/s3 四个 finish 定理，可直接选 `FourWriterDirect.lean.inc`（**dfd9d0c0 / 1720 B / 1 根 / NOT_RUN**）的 `emit_four_rows_prefix`，无需先构造 `Fin 4 → ...` 的 lane 选择函数。它与通用 `emitRows_point_prefix` 是两种接法，不必一并加入最终源码。

给 D 的实际四行状态，最小义务是：对每个 lane : Fin 4 和 j : Fin p，最终 `read lane j` 精确等于原 `NativeFinal.dot n ((bi*m+4*g+lane)*n) (bi*n*p+j) p A B`。这里必须来自实际 k loop 的 lane 投影及原 finish / NaN replay，不能以抽象假设当具体实现已证。

接法如下：

1. `emitRows_four` 把四次原 row-major `RowStream.emit` 与一般 `emitRows 4` 等同，因此 D 可以保持手写四行 writer 的运行体，而在证明中反向改写。
2. `emitRows_point_prefix` 取 offset=4*g、rows=4，将四个具体 lane 的精确 dot 等式转为矩阵 Prefix。块内行有效性由 `block_row_valid 4 m g lane` 给出；hrows 可由 g<m/4 和 div/mod 关系推出。
3. `blocks_tail_prefix` 取 width=4，先折叠 m/4 个 block，再折叠 m%4 个原始单行。第 t 个尾行是 `4*(m/4)+t`。`tail_row_valid` 给合法行，`four_tail_bound` 给尾行数量最多 3。
4. `batch_fold_prefix` 把每批前缀推进接到整个 batch，最后仍用原 `RowStream.prefix_vector_eq_ofFn`、`points_eq_reference` 和 `referenceBmm_spec`。所有配对/分块必须在 bi 内重新开始。

**四行尾部不能直接把旧双行的 `emit ((m%2)*p)` 改成 `emit ((m%4)*p)` 而仍固定最后一行 A 基址**：余 2 或 3 行时必须逐行改变 A。若实际 writer 使用一个扁平尾部循环 q < (m%4)*p，需使用尾行 `4*(m/4)+q/p`、列 `q%p`；若使用逐行 fold，则 t、j 天然分开。p=0 没有元素，不运行除法或 dot。

有限符号检查涵盖 widths=1,2,3,4,5,8，batch0..3、m0..12、n0..4、p0..5，共9360个形状/width组合全部地址与每输出k序一致。global4跨批变异在 batch2,m5,n2,p3 的输出15..23被拦截。它不是Lean证明、Float32值模型或性能结果。

这是一份接口储备。四有效SIMD lane、两个floatbox或closure的静态发现不等于完整速度；本方未查看或调整四行计时分派，实际运行体与成本由 D 验收。
