# 逐 batch 准备 B、计算并释放的连续输出草稿

状态：DESIGN / NOT_COMPILED / NOT_BENCHMARKED。对应完整草稿是 `review-output-batch-local.lean`；未生成新 Kernel，也未修改冻结5b7d。草稿依赖 proof3 的两个新参考桥，须先取得其真实语句结果。

## 准备与运行组织

`BatchLocalPacked.packBatch` 新建 `Vector.ofFn g → Vector.ofFn k → packet`，直接从原 B 的 `(b*n+k)*p+j` 位置转换，不构造外层 batch Vector。其运行定义不调用 `Packed10.packB`，也没有从完整 packedB 中取 b 的伪局部化。`packBatch_eq` 仅在擦除的证明中连接 `(Packed10.packB ...).get b`，供复用既有逐 lane 语义。

运行链为：全局 nativeA map → output Array.mkEmpty(total) → Fin.foldl batch → 本次 batchStep 内 packBatch → Fin.foldl m → Fin.foldl groups → 一次 runDot 后 emit 有效 lane → 返回结果 Array → 下一 batch。batchStep 的返回值只有输出数组，外层累加器没有 packedB 字段；旧 batch 的 packed 也没有写入输出。

原始 B 仍整份保留供逐输出精确 NaN 回放，nativeA 也按本次约定全局保留。减少的是新建 F10 打包对象的同时存活量。源级数量由 batch*groups*n 变为每批 groups*n；两者总打包工作量相同，没有把暂存量减少解释为同等运行时间减少。新的外 batch/内行遍历还直接使用已知 b 计算 B 基址；这属于本次结构调整伴随的地址组织变化，应在性能解释中保留。

## 可复用证明块

- `packBatch_eq`：新两层构造与旧 packB 外层 get b 的等式；通过原 `vector_get_ofFn`，不引入新的浮点结论。
- `rowIndex` 与 `rowIndex_batch`：r=b*m+i 的全域界限与 r/m=b。需要 m 正时从当前 Fin m 元素获得；空 m 不制造索引。
- `group_eq`：局部 packed 参数和已知 batch b 复现旧 RowStream.group 的精确输出。旧完整 packB 只出现在定理中。
- `row_eq`、`row_prefix`：重用 RowStream.group/row 的既有 Prefix 链，省去复制逐 lane 终点和 NaN 证明。
- `batch_prefix`：内行折叠不变式是 `Prefix(point,(b*m+i)*p,out)`，把入口 b*m*p 接到出口 (b+1)*m*p。
- `output_prefix`：外 batch 折叠不变式是 `Prefix(point,b*m*p,out)`，末尾得到 total=batch*m*p。包装 Vector 后复用 proof3 的抽象 Prefix→Vector 桥和 scalar points_eq_reference。

空 batch/m/p、n=0、尾组与巨大 Nat 均保持同一全域定义，不需要把常用形状当作前提。实际原 dispatcher 已对 total=0 与 n=0 走参考回退；不能因此省略新 core 等式的全域证明。Packed10Index.runDot 的机器字界限检查和 Nat 回退原样复用。

## 最小集成与判别

先等冻结5b7d语句通过，再选择一份候选做集成。按精确剪枝计划删旧物化输出链、将 bmmPackedBase_spec 直接接 referenceBmm 后，可只把 packed 分支换成 BatchLocalPacked.core；DirectSmall、DirectRows 和 p2跨batch路线由协调者分别保留。每份最终组合重新计字节并跑完整四spec gate，不继承旧包通过状态。

只有实际捕获 C 才能确认生命周期缩短。沿新 output 的外 Fin.foldl 特化函数检查：

1. packBatch 的调用／内联构造位于 batch 迭代体，未出现返回完整 batch Vector 的 packB 调用。
2. 当前 packed 的引用仅被本批 row/group closure使用，离开 batchStep或其内联区域时有对应 `lean_dec_ref`，下一批没有保留旧 packed 的引用；逐分支检查，不能只搜到一次 dec 就宣布全部释放。
3. 输出 Array 继续独占，未因新闭包捕获而复制；每组仍仅一次 runDot，每 lane 只 finish/emit。
4. 保留全部准备、销毁、尾组和 NaN 回放成本；完整同 runner 对比5b基座、批局部版本及控制源。新批循环控制／闭包开销可能抵消暂存收益，尤其batch很多而m很小时。

草稿的文本与有限布局诊断仅支持结构设计。Lean依赖、输出证明、精确checksum、公理审计、实际生成代码和性能目前全部 NOT_RUN。
