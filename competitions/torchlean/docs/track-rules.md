# TorchLean 技术规则

固定版本见[pins](../pins.json)，官方contracts/gate/bench保持原样。候选仅含UTF-8 Kernel.lean，≤256000B，仅import ContractExact，提供全12算子Submission.kernels及Submission.correct。全输入逐字匹配，线性/卷积bias包含在同一精确dot最后一次舍入内；不能先round dot再加bias。允许公理propext/Classical.choice/Quot.sound，原verification依次intake/policy/statement/kernel/axioms。

用户当前目标为任意一榜冠军，只与各榜现任冠军比较。overall按五模型配置权重聚合，分榜只用对应模型；原配置每seed6workload（typical/scale/boundary各2，50/30/20），overall为30cells、单模型分榜为6cells，按原权重几何均值、每workload跨轮中位数、stratified bootstrap与逐cell guard验收。生产参数/冠军取新鲜官方响应并保存原件；请求失败时保留旧值与时间，最新UNKNOWN，不绕过。历史原版对照不再作为新性能目标。

原官方quick配置5轮/inner3/2ms用于探索，标准开发配置11轮/inner3/50ms用于确认；报告各自配置，不冒充生产。准备模型和outputhash在计时外，但kernel内部缓存/输出/回退成本均在计时内。只读参考、source hash、CPU、种子、序列及原始逐项结果全部保留。正式提交/签名/资金另核当次授权。
