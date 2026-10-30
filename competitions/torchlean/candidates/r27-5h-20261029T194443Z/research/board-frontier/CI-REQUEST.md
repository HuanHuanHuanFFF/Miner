# C 当前成本请求 — 21:49 UTC

当前唯一活动请求见 `CURRENT-COST-REQUEST.json`：若D/R选择容量，使用同一source12/normalized_mlp完整模型，区分两条机制。C不派发CI。

| 候选 | SHA前缀 / 字节 | 构造器 |
|---|---|---|
| packed12-native-v1 | 1b0ac553 / 65227 | build_source12_probes.py，variant=packed12 |
| winograd12-nativefinish-v2 | 600eaaa1 / 71667 | build_source12_nativefinish_v2.py，variant同名 |

两者只依赖精确source12，构造器无网络/无27取回；D接口均为 `transform(raw_bytes, 12, variant)`。依赖hash、完整sourcehash、成本边界、最低验收、原始正反例均在JSON/对应receipt。固定原MainExact与flags，计入全部准备、失败回退、输出和释放；所有小形状/慢样本保留。

两者静态intake/policy已核，**尚未Lean编译，且没有Submission.correct**。必须覆盖D runner按fetch自动标成DeclaredCorrect的错误标签。只进行native诊断，不能宣称新内核all12证明。当前23报告政策已核，但跨环境倍率仍INFERRED；最终现任由D刷新。

**已完成的请求：** guard26-v2 dced7848/218583B在run40952423982通过完整原12gate，360pair完成；详 `guard26-v2-verified-result.json` 与政策追加。不因旧标题重复派发。小收益冻结保留；当前估计未达目标。

旧Mixer27构造、Winograd普通终端、动态moment与小helper均属控制/后续记录，不加入活动队列。下一次变更须由真实编译/完整成本或新的关键反例触发。
