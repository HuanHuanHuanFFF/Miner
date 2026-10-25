# R15 FloatLib 三小时协作

窗口：2026-10-25 04:39:28—07:39:28 UTC。开发与研究两条主线；DeepSeek 本轮不参加。

目标仍是新冠军。按实际耗时占比、可实现降耗与验证成本选路线；三组核验后已采用B2，现任冠军仍为#309。

- 开发：隔离薄 B 缓存和小列矩阵路线，先跑完整成本。
- 研究：已派三条 Astra，分别探索矩阵结构、高成本标量／求和，以及公开实现和实际代码生成。
- [计划](round-plan.json)、[状态](../../../coordination/development-status.json)、[看板](../../../../../dashboard.md)。
- 官方07:22:30 UTC完整快照仍为冠军 #309，规则4b7e；DF旧模型8e68保留，B2新源模型9222已按三组配对数据生成。
- R14 完整研究导出仍暂停；本轮只处理授权范围内开发候选、证明、轻量验证与公共 CI 证据。

| 精确源 | 当前结果 | 决定 |
|---|---|---|
| ec82 矩阵隔离 | [完整D](result-1526001-f01-r15-dev-matrix-only1-vs-f01-d12-scalar-combined.json)：全gate通过；相对DF整体0.97609、BMM0.85286，p05=-0.00605 | 不采用，不重置首次D |
| cb7f 矩阵＋低指数乘法 | [完整D](result-1526003-f01-r15-dev-shortn-decode-cutoff1-vs-f01-d12-scalar-combined.json)全gate通过；整体0.98042、BMM0.85627，p05=-0.00402 | 不采用，不重置首次D |
| b962 双列 → b116 证明修复 | 修复版完整gate通过；整体1.03125、BMM0.89246 | 首D不采用 |
| f529 常规乘法位标志舍入 | 完整gate通过；整体1.24480、MUL1.70258 | 首D不采用 |
| 622d B成对存储 | D/A/B整体0.95999/0.93762/0.91109；BMM0.79733/0.75035/0.66038，三组均过门槛 | 已采用；[统一验收](development-final-three-group-verification.json) |

参测运行逻辑已于06:19:09 UTC[固定](development-runtime-freeze.json)。窗口仍持续到07:39:28，后续完成完整gate、多输入确认、代码实物核对与数学／证据整理；已启动验证收齐后再停。在途作业、后续结果从权威开发状态读取。

当前冠军乘数：add1.03 / mul1.11 / sum1.18 / BMM2.45，整包1.21，暂不能取代#309。[结果](development-round-results.json)／[数学与经验](development-lessons.md)。
