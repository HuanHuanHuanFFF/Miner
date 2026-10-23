# R10两小时矩阵探索

北京时间2026-10-24 01:00:31—03:00:31。目标仍是新冠军；根看板统一使用现任冠军乘数。

截至 2026-10-23T18:15:49.796115+00:00，已完成 7 个CI，运行中 2 个。

| 候选 | 矩阵变化 | 整体变化 | 验收状态 |
|---|---:|---:|---|
| f01-d10-bmm-low-word-typed | 慢9.35% | 慢3.29% | 完整gate通过；未达采纳门槛 |
| f01-r10-bmm-singleton-native | 快3.79% | 快0.95% | 完整gate通过；未达采纳门槛 |
| f01-d10-bmm-small-unroll | 慢0.70% | 快0.77% | 完整gate通过；未达采纳门槛 |
| f01-d10-bmm-inline-address | 待结果 | 待结果 | statement失败，无性能结论 |
| f01-d10-bmm-direct-rows | 快7.39% | 快2.39% | 完整gate通过；未达采纳门槛 |
| f01-d10-bmm-singleton-tuned | 快3.20% | 慢0.36% | 完整gate通过；未达采纳门槛 |
| f01-d10-bmm-inline-address-proof2 | 快9.50% | 快2.34% | 完整gate通过；未达采纳门槛 |
| f01-d10-bmm-singleton-row-cache | 待结果 | 待结果 | 待完整结果 |
| f01-d10-bmm-singleton-double-cache | 待结果 | 待结果 | 待完整结果 |
| f01-r10-bmm-longthin-usize | 待结果 | 待结果 | 待完整结果 |

变化量是相对本轮已保留41的同组参照归一化完整入口成本；冠军差距只见根看板。

同一候选的最终确认要求冻结源码、两个未参与选择的新输入组，与发现组共同逐组通过。负面结果与慢组全部保留；一轮三份候选的853只计一个输入组。

[精确结果索引](round-results.json) · [事前计划](round-plan.json) · [三组验收规则](three-group-design.md) · [固定冠军基准](anchor-design.md) · [阶段诊断](profile-integration.md)

正式参赛提交未授权、未执行；公开Git推送只用于开发与标准runner验证。
