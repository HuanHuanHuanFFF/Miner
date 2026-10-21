# R10 已验证空记录消除包

只省去无候选节点的两字记录，保留位置零节点，让原后向 gap 处理其余文字位置。来源及执行规则分别见 [#361 PROVENANCE](../../references/round7-public-361/PROVENANCE.json) 与 [AGENTS.md](../../AGENTS.md)。

- Rust：`7f1c661fd1ce29d12c69671f034ff5a713e284ed1fcba66ba404ff25479b55b7`
- Lean：`86cfc36adb009970bccbb5a9c543c5f559148d729e8c0f041934aab44e95592d`
- 完整公共 gate：[37684506856](https://github.com/HuanHuanHuanFFF/Miner/actions/runs/37684506856)。最新接受证书：[VERIFICATION.json](VERIFICATION.json)。生成时 manifest 的未验证状态保留为历史观察。

七个 runner、十四块公共配对计时平均比 scalar 快 **0.9795%**，公共输出逐字相同。此包改动与证明较小，可作为后续研究的简单父版；更快的已验证包见 [pipeline-proof](../r10-finder-pipeline-proof)。有限等价与原始完整 gate 是不同证据，不把它们写成全输入 token 等价证明。

当前未进入预测前沿，没有新正式提交。全部口径与限制见 [第十轮报告](../../docs/rounds/round10.md)。
