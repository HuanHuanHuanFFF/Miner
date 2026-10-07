# R10 RMQ8 源码审查

审查对象是生成器 [build-round10-rmq.py](../../scripts/build-round10-rmq.py)、候选 [parse.rs](../../candidates/r10-rmq8/parse.rs) 和父版本 [scalar parse.rs](../../candidates/r9-block-scalar/parse.rs)。本次未发现标量端点最小值与八元素 summary 查询之间的有限反例；这支持继续做组合型实验筛选，不构成完整正确性结论。

可复跑轻量模型：

```powershell
python scripts/check-round10-rmq-model.py
```

默认写入 [rmq-review.json](rmq-review.json)。它只实现候选 helper 的整数与环形索引模型，没有编译 Rust、改候选、运行 Lean 或模拟整个 parser。

## 关键不变量

长度价格表将 `lc[0..512]` 划成半开常值段。反向扫描得到每个长度的下一个不同价格索引；查询只访问 `l < e <= 259`，因此实际 LZ77 长度 3..258 的索引留在价格表范围内。每次 `d_load` 后都重建 512 个 `ends` 元素，初始加载和 `d_block` 切块路径都覆盖。

在一段价格不变的区间内，最小化 `ring[p+l]` 的高 32 位即可。summary 保存 `(cost << 3) | offset`，低 3 位选相同成本下最早的长度。查询只在 `p+l` 八对齐且同价段至少还剩八个长度时使用整组；左边不足八个的位置和段尾回到标量扫描。跨价格段仍比较完整打包值，因而相同总成本保留更短长度。

summary 与 `ring` 都覆盖 1024 个位置；128 个 summary 槽各含 8 个 ring 单元。查询最多向前 258 个字节，候选 push 最多向后 255 个字节，最远可能关联的区间仍小于 1024。`d_push` 只写 `p-x`，严格早于当前节点；这些单元尚未最终确定。进入下一个低位节点前，`d_gap` 从高到低最终确定这些位置，并在写入后更新对齐 summary。当前节点之后的 push 不会改动其已完成的未来组。模型包含跨 1024 环回的 push 和查询序列。

当 `lo >= e` 或 `e > 259`，新 helper 退回父版本 `d_best_len`。有效区间的内层循环每次增加 1 或 8；`stop` 总是大于 `l` 且不超过 `e`，所以至多处理 259 个长度。价格及 summary 槽分别通过 `% 512`、`% 128` 索引；ring 单元通过 `% 1024` 索引。高成本及价格均为 32 位值，最大和小于 `2^33`，summary 左移 3 位小于 `2^35`，最终查询打包小于 `2^42`，不会触及 u64 上限。`usize` 环回也不改变这些模数，因为 1024 整除 32/64 位 usize 的模数。

## 模型覆盖

脚本比较与父版 scalar 同一半开区间最小值，并复用 `ends` 缓冲区模拟块切换。它检查了 769 组价格表的 393,728 个 run-end 元素、493,440 个穷举区间、17,305 个随机区间、7 个无效区间回退，以及先前 push 后由 gap 逐点 finalize 的 32,896 个区间。穷举覆盖长度 3..258、常值 tie、跨多个短价格段的 tie、长段和极端价格；绝对起点包括 1000/1020/2044 和 64 位环回位置。模型累计执行 4,497,146 次 summary 查询及 6,458,672 次标量尾部查询，没有差异。

历史节点 #2058 产生 255 个 backward pushes 后，模型检查 gap finalize 将这些值纳入 summary；随后低位节点 #1800 的查询覆盖绝对端点 #1803..#2058，对应 ring 槽 779..10，确实跨过 1024 单元环回。之后 #1800 的 255 个 push 都写在已完成未来组以下，未来 ring 单元和 summary 未变，当前查询结果保持相同。完整计数、随机种子和 SHA-256 见 [rmq-review.json](rmq-review.json)。

## 尚未关闭的审查边界

`candidates/r10-rmq8/manifest.json` 记录候选复用了 scalar 的 `Parse.lean`，但新增 `r10_price_ends`、`r10_min8_commit`、`r10_best_len`，并改变了 D 路径接口。上述 helper 的终止性、数组界限、取模环回和“只 push 未完成单元”的 sweep 事实还没有绑定到官方重新提取结果或 Lean 原始 obligation；候选清单也将 proof 标成 `UNADAPTED_PARENT_DRAFT`。因此只能报告源码审查和有限 Python 模型结果，不能称作 equivalence、official gate 或认证通过。

本次不在本地安装或运行 Rust 工具链，没有运行完整 parser、round trip、CI 或配对性能测量。若要扩大长度上界、改变 `D_RING`、summary 分组宽度、push 距离或 block 更新顺序，必须重新检查小于 1024 的活跃窗论证并运行新的差分覆盖。
