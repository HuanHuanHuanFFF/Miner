# 第十四轮：两小时前沿优化

本轮从2026-10-09北京时间15:04至17:04；执行规则见 [AGENTS](../../AGENTS.md)。研究进行中，未取得本轮新正式上榜或分红证据。

起点为上一轮完整公开验证的 `r13-514-abs15`。它的历史速度信号小于波动，本轮保留为直接对照，另设正式#514与同源码shadow。当前完整官方 [快照29278](../../evidence/round14/official-start-2/receipt.json) 的快端门槛仍为#539；官方freshness为unknown。

首批真实编码检查 [37897361351](../../evidence/round14/37897361351/probe-a-native/diagnostics/r13-encoder/encoder.json) 已完成：

| 候选 | 新机制 | 公共大小变化 | 当前证据 |
|---|---|---:|---|
| chain-gain | 已进行的浅链搜索按现有位收益估算择优，不增加搜索 | −0.0061497pp／−1304B | 原版编码器28文件输出并独立解码；速度与完整gate待查 |
| head14 | 仅将浅链head表减半，保留U16链接窗口 | +0.0285406pp／+8355B | 真实编码代价已知；需检验总时间是否补偿 |
| dna-direct | 既有DNA路由复用直接发射引擎，六字节key与密集插入 | 待测 | 尚无实测结论；改变搜索、折叠与发射，需要完整版本验证 |

两项浅链候选在 [screen-b](../../evidence/round14/screen-b.json) 做两块配对发现；DNA是独立结构探测。确认条件已在读取计时结果前 [冻结](../../evidence/round14/confirmation-policy.json)，预留独立四块与完整gate时间。旧R13 rescue组合不因本轮续跑而恢复为有效成果。

官方#553源码已合法公开并保留原响应及作者。相对#542主要为参数与路由替换，本轮目前只阅读，不将其当作已验证的派生优化。

最新状态与预算：[研究状态](../../evidence/round14/research-state.md)、[预算](../../evidence/round14/budget.json)。
