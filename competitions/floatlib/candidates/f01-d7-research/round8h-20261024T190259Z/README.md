# R14 八小时三方协作

北京时间2026-10-25 03:02:59—11:02:59。目标仍是新冠军；[窗口与分工](round-plan.json)，当前总状态见[开发状态](../../../coordination/development-status.json)。

研究侧由GPT-6.1 Sol负责数学与Lean桥接，开发侧负责实现、集成和CI，自由侧DeepSeek在独立工作区探索。本机不运行Lean或重型编译。公共区只放短状态与逐议题留言，完整结论、源码和证据在所属工作区。

保留起点df5c；R13的四个增量候选均未采用。优先研究能够改变主要成本的机制，按实测耗时份额、可降耗幅度和实现验证成本分配投入。普通交接通过文件，启动消息仅一次；阶段检查点读取并单独记录处理结果。

- [新冠军换锚](development-reanchor-applied.json)：冠军更新为#309，只替换冠军投影成本，我方冻结计时、输入和配对样本不变；[元数据换行核对](development-reanchor-metadata-correction.json)记录精确当前模型哈希。整包约1.25×、矩阵约2.73×。
- [标量前置NaN选择与行NaN分流完整负结果](development-terminal-40129155932.json)：两条均停放，原件及失败保留。
- [已公开缓存组合的固定旧套件完整预检](development-legacy-correctness-preflight-result.json)：83a9通过；新公开套件收益待测。
- [一次原生乘法与原字平移](development-native-exponent-build.json)、[纯整数RNE乘法](development-integer-exponent-build.json)、[薄列B复用](development-thin-bcache-build.json)：完整源码证明尝试已准备，尚未编译。
- [整包组合](development-combined-slim-build.json)及[证明源码余量](development-combined-headroom-build.json)：为实际加法重构留出空间，完整gate待跑；不按新文件名重置旧失败来源的统计。
- [纯整数加法域检查](development-word-add-screen.json)及[独立编译底座](development-word-add-probe-build.json)：避免深抵消，实际新add规格仍待闭合。
- 研究侧状态与关键引理探针从本轮`astra-status.json`读取；请求、单项源码与回执分别成文件。

本方已启动的五个CI均已收齐终态。新批公开范围等待本会话人类回复，`round-plan.json`最初的推送布尔值不构成新增公开授权。研究侧已追加更正其旧推送指令误用；后续按当前开发状态及直接人类回复执行。私有研究网页链接、提示词与上传副本留本地。

恢复工作读[当前开发检查点](development-NEXT.md)，完整四项看板保持既有冻结口径。
