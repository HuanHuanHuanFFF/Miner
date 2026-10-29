# R24：七小时大幅优化探索

北京时间2026-10-29 **04:38:56—11:38:56**。目标仍为新冠军。D统一Git/CI，R主动并行Astra探索两条不同大路线，D两Sol承担标量组合与广覆盖真实成本。先取得整体机会/最小证伪，按证据连续投入；不重追旧失败体seed。

当前[计划](round-plan.json)、[作业](development-jobs.json)。保留B2/622d；R23数学资产沿原精确源验收，publicBMM仍未闭。正式竞赛上传/资金/reset不在本轮开发范围。到期停止新增，已启动CI完整收齐。

## 本轮发现的官方状态变化

FloatLib当前`submissions_open=false`，TorchLean为true；[原件与回执](competition-state-check/receipts.json)及[只读快照来源](source-snapshot/source-file-hashes.json)已保存。迁移范围已向用户异步确认，未获回答前不开发新参赛实现或运行新候选准入。团队继续通用数学及公开参照的原程序观察；原始官方源码、算法和计时程序不改。两个旧原型冻结NOT_RUN，不把目标关闭记为算法失败，7小时截止不变。[路线决定](development-route-decisions.json)。

## 当前决定与验证

公开前冠军2的原程序分层观察已完成：[精确回执与分析](development-reference-first-result.json)，[重算脚本](analyze-readonly-reference.py)。五个固定normal模型中，点积相关层占约66%—100%；归一化在nmlp只占6.2%、Mixer占26.1%。主攻原生双精度累加加精确证书，覆盖线性／矩阵／卷积共用路径；归一化作为补充。层计时包含hash/touch，当前冠军5源码未知；不据此生成新成绩。

| 大路线 | 当前证据 | 下一步 |
| --- | --- | --- |
| 原生双精度累加＋精确检查，消除逐项装箱 | [64进程完整对照](development-dot-cost/timeout-review/full-408048-findings.md)：Tail混合输入完整调用／自建整数参照为 **0.67–0.72×**；缓存已准备为 **0.60–0.69×**。普通指数缓存点积为 **0.36–0.41×**。实际C／汇编确认普通累加回边不再每项分配16字节Float | 多行、多列共用缓存，测完整调用；补齐运行时证明 |
| 原生64／128位整数精确多链 | 已有循环、编码和终端运输源码；先前标量直接转换无明显收益，不能替代点积测量 | [研究交接](research/HANDOFF.md)，仍需原输入到完整输出的闭合调用与实际成本 |
| 精确舍入与误差证明 | [精确core源](../../f01-r24-dev-core-certificate1/manifest.json)的 **9个新增helper＋4个原公开义务**已通过statement、kernel replay及13项公理审计；[35根组合第8版](development-math8-results.json)仍余两个转换问题 | 研究侧定点修复；父源不继承组合验收 |

以上点积成本的参照是本轮自建64／128位整数实现，**不是冠军**；混合输入为固定MAC样本之逐项中位数求和。新运行时仅通过有限原生检查，尚无全输入证明或新runner独立采用确认；旧FloatLib逐次舍入BMM未因此提速。新赛道选择仍待用户答复。全部已启动作业及原件见[作业索引](development-jobs.json)。
