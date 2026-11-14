# R20：45分钟协作冲冠

窗口：北京时间2026-10-27 15:47:58—16:32:58；[计划与授权](round-plan.json)。D开发验证、R研究主控及3名Astra通过留言板推进；DeepSeek没有本轮接入回执，不计实际参与。

| 路线 | 新证据 | 下一步 |
| --- | --- | --- |
| 八列行内广播 | ec40e88e，CI40471664006声明、两模块、9根通过；8个原生累加参数，无A缓存，仍有F8终态和row writer closure | 任意p完整入口与输出生命周期，另测完整成本 |
| 点积终态直接写出 | b6b77553，CI40472418849声明、两模块、8根通过；实际C和对象删除F2构造/allocator调用 | 优先下一行整合源，不把静态消分配当提速 |
| 完整终端DC整合 | **39626da4，237637B**，已接原public BMM/奇数尾/回退；完整证明尝试NOT_RUN | 下一轮先跑statement＋模块＋9根，核实际public caller，再做完整D+A+B |
| SUM块吸收 | 31056个精确整数oracle命中对和1000块无差异，保留binade/合块反例；旧输入8块仅跳6.74%，多20.85%raw扫描读 | 暂不投入完整候选，保留数学接口；Lean原SUM桥未闭 |
| 行列重复复用／hot-index尺度缓存 | 两份有界旧输入模型显示覆盖不足，新增扫描／分支成本无支持 | 不造候选、不重跑旧负源 |

**结果：保留B2，尚无可取代冠军#323的新整包。** 冠军digest、suite及上游4b7e8384已补核；冻结ab3b耗时模型未变。两批CI均为证明诊断，未新增性能或正式准入结论。

- [开发结果及作业索引](development-jobs.json)、[八列回执](development-row8-proof-result.json)、[终端回执](development-terminal-proof-result.json)。全部77份原附件及日志在本轮ci-runs，逐文件hash已核。
- [终端实际代码审查](development-terminal-codegen/audit.json)、[八列代码审查](development-row8-codegen/audit.json)。原公共Main仍选B2；新诊断函数与真正public caller分列。
- [下一轮完整整合入口](development-next-entry.md)、[可复现生成脚本](development-build-terminal-integration.py)及[候选](../../f01-r20-dev-terminal-dc1/manifest.json)。原spec不减、原gate不改。
- [研究当前交接](research/HANDOFF.md)和[后半程结论](research/validated-and-next.md)：独占Array修改、逐列状态载体、RNE减法接口等后继方向。
- [整包成本反事实](development-cost-frontier.json)：仅BMM提速2倍，冻结模型whole仍约1.123×冠军；不是可实现速度预测。

完整原始大证据以原路径/源提交/SHA索引保留；以后按项目merge流程处理。私人网页会话观察原文只留本地，不随公开推送。
