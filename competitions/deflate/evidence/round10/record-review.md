# R10 record-nonempty 独立源码审查

**结论：源码推理支持当前 `d_parse` 生成的记录流中省略 `cnt=0` 的 `[i,0]`，同时保留 `i=0` 哨兵；标记为 INFERRED。没有找到可由当前 `d_parse` 生成的反例。** 这不是完整 token 等价证明，也不是实际 parser 运行结果。

本审查针对 [scalar parse.rs](../../candidates/r9-block-scalar/parse.rs)、[record-nonempty parse.rs](../../candidates/r10-record-nonempty/parse.rs) 和 [build-round10-record.py](../../scripts/build-round10-record.py)。scalar parse SHA-256 为 `faf1d7281678d12c3243002121feecdd0ea139633dea197dbc77d86fb6319257`；候选 parse SHA-256 为 `7f1c661fd1ce29d12c69671f034ff5a713e284ed1fcba66ba404ff25479b55b7`；builder SHA-256 为 `6e511ae1ce726ca6da8d1cc6d540198d3725c6e24de476709340083265125214`。源码 diff 仅在 `d_record` 的 `[i,cnt]` 写入处增加 `cnt > 0 || i == 0` 条件。候选 manifest 标注 `Parse.lean` 的 `d_record_spec` 已适配，但尚未编译。

## 任意 `rs` 的反例形状，以及它为何不可直接反驳候选

任意手工构造的 `rs` 流确实会改变结果。比如 `[0,0, 6,10,1, 12,0]` 表示保留 0 哨兵、位置 10 有长度 6/距离 1 候选、位置 12 是空记录。节点 12 的 `d_top` 为 0，令 `end=12`；位置 12 只能走 literal/push。若删去 `[12,0]`，位置 10 的 gap 可用 `end=16`，在位置 12 派生长度 `16−12=4` 的同距后缀 match。一个简单的合成成本模型（literal 代价 10、长度 3/4 代价 1、端点 16 后缀代价 0）会把该位置的内部 choice 从 literal `0` 改为 match `516 = 512 + 4`。

这不是当前 `d_parse` 可生成的反例。它要求位置 12 的输入 continuation 仍有 4 字节，但记录计数为 0。当前 forward producer 在这种状态会跳过记录或把 continuation 一并记录，不会发出 `[12,0]`。

## `d_parse` producer 不变量

设前一个 recorded candidate 的结束位置为 `E`。在 `d_parse` 前向循环的 carry 中，`cl` 是 `E−i`；在对应 `rs` 记录里，`d_top` 取得的长度为 `E−p`。这两个值差一个当前位置偏移。

若 `cl >= ct && cl >= 3 && !lazy_here`，循环走 fast path，处理该位置并令 `cl -= 1`，不会调用 `d_record`。因此 continuation 仍长于 2 的这些位置不会生成空 header。

若进入搜索分支且 `cl >= 3`，`cl` 必在 `cap = min(258,n−i)` 以内：原始候选在其创建位置已受同一上限约束，之后每前进一步 `cl` 与剩余输入长度同步减小。`best` 初值为 2。若 `best < cl`，源码先执行 `drop_farther`，再将 `(cl,cd)` 追加到候选数组，并把 `best` 设为 `cl`。carry 的距离 `cd` 已由先前有效候选产生，且当前位置大于该候选起点，因此仍有效。该追加长度大于之前 `best`，`d_rec_cand` 会保留它。

若 `best >= cl >= 3`，则 `best` 必来自实际搜索候选。`probe` 只返回超过当前 `best` 的匹配，`d_walk` 也只追加 `l > best` 的候选；搜索候选长度因此大于 2、距离在窗口内、长度不超过 `cap`。`d_record` 从 `last=2` 开始，首个候选不会被长度过滤；dup 模式只把 backward extension `t` 设成 0，并不丢弃候选。

15 项候选上限也不会吞掉 continuation：`d_walk` 至多返回 15 项；若 `cl > best`，`drop_farther` 仅删去候选尾部，continuation 随后占第 16 个槽，`d_record` 的 `q < 16` 会处理它。候选长度由 `d_walk` 按 best 严格递增；continuation 只在更长时追加，所以 `rs` 最后一项仍是 `d_top` 所需的最大候选。

由此，当前 producer 写出 `cnt=0` 时，carry 至多为 2；从最近较低的有效 `rs` 节点看，`end−i <= 2`。`d_gap` 的 continuation 要至少 3 字节才会建立 match，因此被省略的位置不会失去一条长度至少 3 的后缀边。如果 greedy `skip` 生效，`i` 直接跳到所选匹配末端并清零 `cl`，匹配内部本来就不写 header；结束位置之后的空记录也没有延续可跨越。

## 反向 DP、块边界、push 与 sentinel

`rs` 中每条记录是若干候选词后接 `[position,count]`。`d_dp` 从后向前以 `a=e−2−k` 找上一条记录；删去 `[q,0]` 正好少两个 u32，不改变其余候选区间或 header 对齐。保留的节点仍按输入位置递增，`p >= hi` 检查不变。

被省略的 q 会作为合并 gap 中的普通位置处理。如果 `end−q <= 2`，`d_gap` 对 q 使用 literal/push 转移；这与空节点的 `st[0]` literal 和 `d_node_best` 相同。两者都在 `q >= lo` 时合并已有 ring push，`q < lo` 时都不读取它。空记录没有候选，不会调用 `d_back`，因此删除它不会改变 `st[1]` 或后续 push 的范围。gap 仍从高位到低位逐点处理，合并区间更长不会跳过字节。

encoder block 边界由 `bstart` 驱动 `d_block`/`d_stop`，不取决于 `rs` 记录数量。删掉空 header 后，较长 gap 仍逐个跨过相同 block starts 并加载对应表；当前源码的 `fuel` 上限按 `bstart.len()` 设置。这个控制流支持等价推断，但跨任意多 block 的全输入结论还需真实运行与进一步证明。

位置 0 必须保留。`d_dp` 消耗 `rs` 后没有独立的 prefix sweep；当 `i=0` 也是空记录时，`[0,0]` 让反向扫完整个剩余前缀。候选中的 `i==0` 分支保住这个终止哨兵。

性能收益仍未知：`d_parse` 仍会做同样的搜索并调用 `d_record`，`d_dp` 合并 gap 后仍逐位置计算 literal/push 递推。明确省下的是每个空节点的两个 u32 写入、反向记录解析和节点初始化开销；公共总压缩时间是否下降要由配对测量决定。

## 边界与证据级别

本结论只适用于当前 `d_parse`、`d_record`、`d_rec_cand`、`probe`、`d_walk` 和 `d_dp/d_gap` 源码关系。carry 编码、候选筛选、最大候选数、匹配最小长度或 gap 处理若有变化，必须重做可达性论证。`rs` 将位置转成 `u32`；位置大于 `u32::MAX` 时会截断，此行为在父子版本中相同，但本次没有分析这种理论输入的全流程影响。`d_push32` 在理论 `Vec::len()==usize::MAX` 时不追加；这个资源极限也未形式化。块切换和 ring/push 的全输入 token 等价尚未证明。

我没有运行 Rust、Lean、CI 或 parser 输出比较。主线程告知 444 个真实 Rust 输入和公共输出检查正在进行；这些是有限实测，应单独报告其结果。完整 correctness gate 通过也不能单独证明所有输入上的 token 等价。候选 manifest 当前将证明记作 `UNCOMPILED_ADAPTED_D_RECORD_SPEC`，官方重新提取、原始 obligation、公理审计和 round trip 仍是独立门槛。
