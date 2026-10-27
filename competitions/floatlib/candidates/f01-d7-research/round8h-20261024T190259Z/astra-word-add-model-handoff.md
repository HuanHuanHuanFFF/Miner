# R14：正常 finite add 已接到公开 Model.add 的证明草稿

时间：2026-10-25T00:17Z。新增 `astra-word-add-model-bridge1.lean`，连接：原输入顺序的 finite decode → exact addDyadic 结果 → Model.roundDyadic → ofFields。下界 h>=24、elo>=1，故前置指数已正常；后置 E<=254 显式包含 carry。桥的 Model.add 入口使用固定 FloatLib `Arithmetic/Proof.lean` 中 `Model.Proof.add_eq_spec`，该源已保存，Git blob `469ca2d5a6749c2dfa5093d8eeb8353e6e701bf6`。仍 **NOT_COMPILED**，不替代实际 Binary32 入口/字段桥/完整 gate。

新增轻量 `astra-word-add-boundary-screen.py/.json`：2秒/3000条上限，实际约0.004秒、1372个边界组合。N覆盖16777216..2164260735，h24..31，t1..8；2例carry，205例overflow回退；单比特log、偏置RNE、carry/fraction和完整指数判断未见反例。它只检查整数公式，不是实际 Lean/native/性能。

保留四个反面边界：opposite gap1 可得N=1、gap0可得N=0、gap8会使UInt32 N回卷、无上界的E257在8位字段中别名1。最后一项**不影响 runtime2 当前完整 e-1<=253 判断**。共享00:08/00:12片段及旧原件均保留。

没有新候选、CI队列、Git index或公开动作。若选择集成，建议先取实际引用的定理；现有通用片段不要求整套拼入256KB候选。我继续检查证明/字节预算和简化机会，所有运行体仍由开发协调。

基准目录：`D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z/`。
