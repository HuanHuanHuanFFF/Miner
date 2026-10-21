# R26 新增 public source 静态审计

范围：离线比较 snapshot `29870` 新捕获的 public #652、#658。两份原始 JSON response 与 `source-receipt.json` 的作者、指标记录、`parse.rs`／`Parse.lean` 字节和 SHA-256 均交叉核对通过；不据提交号或指标推断源码新颖性。扫描全部 **58** 份 reference；对 **408** 份已有 candidate 核对完整 `parse.rs` 哈希，并对 #652 的11个活跃变化函数做精确函数体哈希检索。

## 结论

**VERIFIED — #652 最接近的整源及 parse 函数祖先是 #611，#614 几乎并列。** #652 Rust 为 `20992b6048110ad2837e8e0006936e1539a20d223031b838a7815517e2859d71`；#611 Rust 为 `ee8b309c75f03853e7f18e2f99e9c8103647484b82b049c5e64a7a3c3ddfaa38`。#652 的387个函数定义中，381个名称与#611相同，376个函数体 token 哈希相同，5个同名函数体改变，另有6个函数加入、没有函数移除。全源 token 多重集保留率98.377%；#614的函数计数相同、全源保留率98.365%。#628虽排第三，但仅62个函数体相同、目标函数体 token 覆盖11.54%；#552覆盖83.34%，仍明显低于#611/#614。#609、#595、#601、#641及其余全部 reference 均纳入排序。

**VERIFIED — #652 不是纯参数／路由复用。** `parse` 的直接调用集合与#611相同（`SFshape`、`emit_pos`、`r18_base`、`route_class`）；静态可能闭包比#611多6个 helper。5个变化的同名函数是 `a_dp_pass`、`a_find_all`、`a_tree_insert`、`d_best_len`、`d_walk`；新增 `a_word4_at`、`a_fill`、`a_dp_fill`、`a_dp_min`、`a_dp_recs`、`d_filt`。A 路径用8项分段填充记录长度区间，再对区间最低代价做选择，异常记录回退逐项扫描；A 查找／树插入把原64位读取改为有界四字节前缀比较。D 路径新增必要字节前缀过滤，随当前最佳长度更新过滤条件，并改为上限259的打包代价扫描。D_KNOBS、CFG、CLASS_TAB 等配置也有变化。

**VERIFIED — #652 的上述11个可能可达变化函数，在全部58份 public reference 和408份 candidate 源码中均没有精确函数体 token 哈希命中；两份目标也都没有 candidate 的整文件字节级重复。** 因而它包含区别于扫描历史的源码机制；这不等于算法概念首创，也不证明相关分支在竞赛语料运行。

**VERIFIED — #658 的整源最近参考是#506/#507；按 parse 可达函数体重排后，#507 最近。** 整源排名#506略高于#507（目标 token 保留97.364%／97.361%，两者均有178个相同函数体）；可达闭包排名则#507为86.384%目标函数体 token 覆盖、119个同体函数，#506为74.465%、107个。#658 与#507的 `parse`→`bulk_parse`→`route` 主干保留，主要改动是 `bulk_parse` 将 route ID 指向另一组 `p125_row*` 包装器和模板参数。新增可达的 `ef32_*`、`et_*`、`q4_*` 核心函数体均能在其他 public reference 找到精确同体；对#507新增／改体的44个可达函数中35个有这些同体命中，其余9个都是 `bulk_parse`／`p125_row*` 路由包装器。因此，#658呈现已知 kernel 的路由／参数组合，不是新活动 kernel 的证据。泛型调用断言验证了 `p125_row8→pc_run1c`、`p125_row9→u118_run`、`p125_row10→o_a_main_part`。

**INFERRED — 投入判断：** 若要继续做小范围机制审查，#652的区间填充 DP 与 D 前缀过滤是应单独看待的差异；#658现有证据支持把它作为 route／预算组合，而非独立 kernel 方向。这里没有性能或收益结论。

**UNKNOWN：** 这些分支对比赛语料的实际触发范围、压缩质量、运行时间、证明迁移和正式准入效果。调用闭包是静态可能路径，不证明运行时分支；报告没有计算或解释回执中的性能指标。

## 可复核材料

- 重跑：`python scripts/r26-extension-new-source-audit.py`
- 机器报告：[`audit.json`](audit.json)
- 完整 top-source diffs：[`#652–#611`](public-652-vs-611.diff)、[`#652–#614`](public-652-vs-614.diff)、[`#652–#628`](public-652-vs-628.diff)、[`#658–#506`](public-658-vs-round12-public-506.diff)、[`#658–#507`](public-658-vs-round12-public-507.diff)、[`#658–#628`](public-658-vs-628.diff)
- #652 Rust／Lean SHA-256：`20992b6048110ad2837e8e0006936e1539a20d223031b838a7815517e2859d71` / `c61cd363e99de08fcef7549e4d31c0db805eaffa326dd287fed431b6ea88f215`
- #658 Rust／Lean SHA-256：`1185749453a5abe100106f2e15082eca84521292b7233784a9c2f4562367f3ad` / `354d56aa9f58536efdb410f3d5ecdf1945bded607965fe8a48161f96b035c494`

勘误：首版闭包扫描漏掉 Rust turbofish `::<...>` 直接调用；修正后按闭包重新排名并重生成报告。函数／整源哈希排名不受影响。扫描器仍是轻量词法分析，不解析宏展开、方法分派或类型语义。
