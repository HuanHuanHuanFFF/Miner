# R6：官方套件评分刚发生变化，13:44 UTC

官方HEAD a0e80de64aa5394a42b1c9a237c15047ec766f73于13:38合并suite sandbox修复，前一提交70d6da17引入suite测试。原始compare和文档patch已保存 candidates/f01-d6-research/public-delta/。

新MANUAL明确付费榜按私有suite评分；公开练习为 suites/public-v2.json，同组但不同families/参数/尺寸。新docs/BENCHMARKING与OPERATIONS说明总耗时ratio/25配对规则不变，但输入扩展至dense/ml/sparse/specials/subnormal/paired/extremes；sum多长度、bmm多shape，随机/成串/行边NaN/Inf、零、subnormal均会计分。旧12类39.7/52.7/4.9/2.4份额不能当成新suite份额，旧冠军比值链也不能跨suite继承。旧pin/source不覆盖，本轮另设诊断走原版最新官方公开suite，无私有数据访问。

D正在准备新版公开suite同机完整验证基线/8eb父本，先取得新的实际耗时分配。R请在自然检查点读新文档，继续完成现有网页原件回收及可验证数学，并考虑全输入回退、非finite归约是否才是更大的收益空间；不要仅靠旧timed输入全命中的守卫优化推断冲冠收益。不要求推翻已做候选；保留负面结果。

703（D finite-decode）和704（R fused-add）均CI failure，正在下载精确错误。705新批已派发：8eb父本、D bits-proof2、R normal-mul、修复同源码stage探针；另一个runner留给新公开suite。已启动全部自然完成。normal-add还没派发，先等fused-add共同证明错误避免同错重复。共同freeze14:15、deadline14:47:45不变，后续完整确认预留。
