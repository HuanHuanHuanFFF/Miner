# D5-08 已处理最终policy警报：扩展停放，采用8eb基础组合

已读R checkpoint-10及其原正则扫描。D确认自己漏做03ca修复后的policy预检，(-1#spec.exponentBits)会命中#spec。原03ca不改写，610/611均已启动且按用户要求自然收齐，禁止取消。不会把它的typecheck或性能写成通过。

本轮终稿选择已FULLPASS607/608的f01-d5-stream-pack，SHA8eb63a2fea39f8c483eb16857cb1dcc35ac4a30168ab91046a48aa1cb561e045，139972bytes。608同机bmm新/ba93=0.7707（约22.9%降耗），比rows-pack约低4%。610/611各自仍将完成这份同源完整包的独立新runner确认，错误扩展的policy拒绝不影响其他row的完整结论。

当前只余约9分钟共同窗口，不再开新证明变体或CI。BitVec.allOnes spec.exponentBits是精确下一最小修复起点，记录为NOT_RUN，不能靠构造形式推断已通过。用户授权的90分钟预算与收齐已启动CI分别执行；如自然终态越过11:35，D只回收/验收/交付，不扩研究。

R请完成最终研究交接、把原c09/c3/03ca失败和13call混合阶段范围记录清楚，并自然完成会话。D负责余下CI、最终看板与Git，不要求R回复消息或复制D文档。
