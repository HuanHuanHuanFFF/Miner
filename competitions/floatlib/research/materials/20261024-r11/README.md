# R11 网页研究：分支内提取与承接

[研究提炼](RESEARCH_NOTES.md) · [逐文件来源与哈希](manifest.json) · [作者及许可证](NOTICES.md) · [数学结论总入口](../../RESULTS.md)

这里将2026-10-24通过Codex内置浏览器取得的三份网页6 Pro交付整理到 `codex/multi-track-floatlib`。按用户2026-10-25澄清，“提取”包括把原件、可复用结论、反例、验证边界和开发承接说明纳入当前分支。E盘解压目录保留作为下载原件；本目录提供脱离E盘可读、可核验的副本。

## 原件与提炼

97份交付文件共3,119,501字节，复制时保留原路径层次和全部字节。未改写报告、失败日志、许可证头或历史NOT_RUN；没有执行交付包中的代码。压缩包此前已删除，原包大小、SHA-256和清理时间仍在manifest中。

| 交付 | 原件 | 份数 | 本次整理后如何接续 |
|---|---|---:|---|
| W01 完整证明审查 | [报告](originals/W01/original-extracted/R11-W01/R11-W01-report.md) | 20 | 复用实际读取、逐lane点积、尾行和输出连接的证明义务；保留地址反例。网页条件termination补丁未采用，实际修复及验收以项目精确候选回执为准 |
| W02 稀疏数学 | [报告](originals/W02/R11-W02-report.md) | 6 | 区分零列与单非零列，保留最早两个非有限位置摘要及反例；分类脚本不构成FloatLib独立执行验证，Lean与性能仍未闭合 |
| W03 Lean与编译性能 | [报告](originals/W03/original-extracted/R11-W03/R11-W03-report.md) | 71 | 两种short-n lowering、38份固定版本公共源码及原反例完整保留；已试过的7cad集成版本通过正确性但无采用收益，不能把网页A/B视为独立成功路线 |

[RESEARCH_NOTES.md](RESEARCH_NOTES.md)按三条路线给出前提、结论、失败、原始/后续验收状态及最小承接动作，并连接R13的负结果。另逐字节收录两份项目自身的[稀疏数学补充](project-evidence/astra-sparse-math.md)和[曝光筛查](project-evidence/astra-sparse-screen.json)，避免引用仅存在于未跟踪工作区的证据。

## 上下文更正与验收边界

原上传上下文曾写错合成限制选项；实际门槛使用 `synthInstance.maxHeartbeats≤400000`。保留原上下文字节，将此更正作为整理说明，不能把原稿中的选项名直接迁入候选。

W01/W03基线源码SHA-256为 `4bdd1e7db35cd85e17d06511721d5dbf7f654ec12e58633264b08a086ec54fa0`；它们的网页原件、后续修复候选和当前df5c保留版本各自绑定不同证据。归档完整性不等于Lean证明、完整gate、收益或正式准入。源码引用及作者归属见NOTICES；私人会话、截图、凭据不在这97份文件中。

## 核验与Git交接

工作区完整性：`python competitions/floatlib/research/materials/20261024-r11/verify.py`。

对照E盘原件：同一命令加 `--sources`。核对当前分支提交内的原字节：加 `--git`。后两项可合用；没有E盘时默认核验及Git核验仍可执行。manifest自身也纳入Git字节核对；核验器不编译、不计时、不运行原件脚本。

原件使用已有 `.gitattributes` 的 `research/materials/** -text` 规则保留行尾。Git仍由开发协调者处理；本次要求纳入当前分支，不自动推送、开启CI或采用候选。
