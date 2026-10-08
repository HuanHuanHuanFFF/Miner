# R10 已验证插入预读包

本目录是精确交付包：在空记录消除的基础上，复用公开 #361 原 DP 已有的插入预读流程。长跳后重新读取链头，其余查找、价格与输出检查保持原逻辑。原作者来源见 [PROVENANCE](../../references/round7-public-361/PROVENANCE.json)。执行规则见 [AGENTS.md](../../AGENTS.md)。

- Rust：`b74ae5fd9575101b6b34b9f2718d8835adca770c6765c30b33bb895878ba1adf`
- Lean：`e0ded4248a894e8c53bc1ce644c7c3f5c6681fe3c06eaab597caf10a5bf472db`
- 完整公共 gate：[37700280634](https://github.com/HuanHuanHuanFFF/Miner/actions/runs/37700280634)，验证时提交 `cac77a5bff21ba0ca6a94e174817aca882322ead`。
- 最新接受证书：[VERIFICATION.json](VERIFICATION.json)。生成时的 `manifest.json` 保留当时 UNCOMPILED 状态；新证书记录后续实际接受结果。

官方重新提取、原始 `LZ77.Obligation slot.parse`、三项公理白名单和 28 文件公共往返／评分通过。日志中的 542.4 秒是阶段 0–5 的验证耗时，其中 Parse 调用 374.9 秒。完整公共 gate 随后完成阶段 6 的公共往返与评分；542.4 秒不含该阶段及额外生成语料检查。八个固定生成输入另有同场 scalar／record 对照；它们不是私有语料。

两个 runner、四块公共配对计时平均比本轮 scalar 起点快 **1.7122%**，比同场 record 父版快 **0.6522%**。公共 token／压缩输出相同，大小轴 **33.934365747942536%**；已有 444 个原生有限等价用例。均值和观察波动不是保证值；gate 也没有证明与父版对所有输入的 token 等价。

仍未取得新的可支付前沿位置，没有正式提交。当前前沿、支付身份限制及全部负结果统一见 [第十轮报告](../../docs/rounds/round10.md)。
