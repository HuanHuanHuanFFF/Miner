# R14研究交接：一次转换加法的边界支持与乘法入口绑定

时间：2026-10-24T21:36:38.778598+00:00
关联：R14；开发侧当前近指数整数加法研究；主线56773d4d指数平移证明待编译。
类型：数学支持／集成说明

摘要：不新增CI请求或运行候选。对开发侧正在研究的整数对齐加法做约10分钟纸面核对，取得固定源四份原件并核对Git blob。d≤7时精确对齐加减幅度N≤2164260735<2^32，一次UInt32.toFloat32可承担唯一RNE；若min指数≥24且max指数≤252、N=0另处理，则最终指数必在1..254，可用原字指数平移，避免第二浮点运算。a23抵消到subnormal、d8溢出UInt32、E254同号加法溢出均给出边界。已有uint32_model_eq_roundDyadic适用任意UInt32；当前乘法normal-form草稿只适用h≥23，异号小差不能直接套它。提供精确addDyadic与通用对齐引理入口，未宣称Lean/性能通过。

乘法：完整65536指数对模型验证guard恰好接受48259对，未发现回卷误放行；不是实际负载频率或收益。路线说明新增公开mul集成位置：绝对Submission.R14 namespace不能直接嵌进已有Submission scope，先闭合后重开；原mul保留改名作无环fallback，新入口须放在原mul_eq/referenceBmm之前。原参考BMM调用公开mul，实际成本影响仍以最终caller为准。proof1文件249900B及SHA56773d4d保持冻结。

需要对方：仅在下一自然检查点取用数学边界与入口说明，不改变已排队修复的执行顺序。所有运行集成、提交与CI仍由开发侧协调。

证据（均为未提交快照，采纳前核对）：
- D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z/astra-aligned-add-math-review.md；SHA-256 d3d6aefde72d40d0ef28b4d1f47c132a776e44062848a7ce72687c5a9c70db8f
- D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z/astra-add-upstream-index.json；SHA-256 34b550dba401ba0e479d08397be4a0e16c92ea83c78f253ab8516d3d0f107c34
- D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z/astra-exponent-guard-domain.json；SHA-256 0d3c5579741aad1be7759dafc143f4c13a29d56cae796c23e08d3dea854dcb58
- D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z/astra-exponent-shift-route.md；SHA-256 fa74d934c15b9f91572b06ede57c2f2b10fc1f0e17599bb14437b7a0f31dd54b

结论状态：纸面推导＋有限guard模型；无新增Lean验收、无性能结果。原始固定源FloatLib Team／MIT归属已保留。
