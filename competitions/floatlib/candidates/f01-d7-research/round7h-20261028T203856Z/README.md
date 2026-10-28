# R24：七小时大幅优化探索

北京时间2026-10-29 **04:38:56—11:38:56**。目标仍为新冠军。D统一Git/CI，R主动并行Astra探索两条不同大路线，D两Sol承担标量组合与广覆盖真实成本。先取得整体机会/最小证伪，按证据连续投入；不重追旧失败体seed。

当前[计划](round-plan.json)、[作业](development-jobs.json)。保留B2/622d；R23数学资产沿原精确源验收，publicBMM仍未闭。正式竞赛上传/资金/reset不在本轮开发范围。到期停止新增，已启动CI完整收齐。

## 本轮发现的官方状态变化

FloatLib当前`submissions_open=false`，TorchLean为true；[原件与回执](competition-state-check/receipts.json)及[只读快照来源](source-snapshot/source-file-hashes.json)已保存。迁移范围已向用户异步确认，未获回答前不开发新参赛实现或运行新候选准入。团队继续通用数学及公开参照的原程序观察；原始官方源码、算法和计时程序不改。两个旧原型冻结NOT_RUN，不把目标关闭记为算法失败，7小时截止不变。[路线决定](development-route-decisions.json)。

## 当前决定与验证

公开前冠军2的原程序分层观察已完成：[精确回执与分析](development-reference-first-result.json)，[重算脚本](analyze-readonly-reference.py)。五个固定normal模型中，点积相关层占约66%—100%；归一化在nmlp只占6.2%、Mixer占26.1%。主攻原生双精度累加加精确证书，覆盖线性／矩阵／卷积共用路径；归一化作为补充。层计时包含hash/touch，当前冠军5源码未知；不据此生成新成绩。

[95KB自包含数学包](../../f01-r24-dev-portable-island2/manifest.json)含36个明确审计根，验证实际位扩展、精确乘法、累计误差及舍入边界；CI `40788628582` 运行中。旧六份父Kernel保留各自未运行状态，只给精确组合源记验收。新增[直接读取循环](development-read-fold/ReadFold.lean.inc)连接实际尾递归与已审的List数学接口，原生代码和成本待验。所有新增数学目前尚无整包提速／采用结论。
