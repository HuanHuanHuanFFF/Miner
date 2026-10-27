# Dual temporal：9a5证明失败，proof2副本待复编

当前 `proof2/Kernel-dual-temporal-a4-proof2.lean`，**240398 B**，SHA **d765bd41234a26640eaa6df6c7134e0d4d8dca760e50eaef3aa82eff1fac0847**。原9a5/240241B保留；只改loop_eq/group_eq证明体，运行体、域、所有声明逐字不动。父源c70c；`3≤p≤8,n>1,m≥4`之外仍c70c，原underflow最外层。扁平A4一次准备＋B8同步读取、两条原序链、无跨行结果tiles的机制不变；全部准备/析构继续计时。

**真实反馈：** run40410895344原9a5 statement失败，五处旧loop方程展开失败＋group_eq未闭合，18根/重放/C/ASM未运行。`ci-40410895344/`保存已按原artifact索引核验的原件。proof2只规范化blocks别名、定向展开RHS、补定义相等；**新副本仍NOT_RUN**。`proof2/REPAIR.md`、`repair-receipt.json`、`proof-only.patch`说明范围并核反向精确恢复9a5。旧静态检查/有限模型的历史状态保留，不能当证明通过。

裁剪只去旧R15PackedB2未用部分（保留tileIndex）和未用旧公开entry；原add/mul/sum整个前缀不动，c70c全namespace保留。`pruning.patch`与三个removed原块可回查，不继承原包验收。不要在helper名单继续引用已删的R15PackedB2.loop；使用本次18根。

第一真实检查：完整statement＋Submission/VerifyFull重放＋18根公理审计；重点 `packRow_prefix`、`packA_get`、`loop_eq` 和 `runDot_eq`。实际C/ASM明确抓 **Submission_R19DualTemporal_loop**（及可能redArg）、新packOutput专门化循环、新output选中调用链；旧R19Temporal_loop只是不选新域时的后备，不能替代。核A只prep一次、无逐Float box/每行Array/每group重复prep/结果tiles；正常hot block是否无ofBits及跨调用spill。保留Nat控制，未自动拼失败9f7，普通路径是否无call由实际ASM判定。

成本不是单向改进：R19已见D上 A转换666448→219954，但加62956个A记录、31870个padding字段、约2.015MB请求；与同shape R16 A相关2.012MB相近，峰值全局A增加。详细对照、旧R16完整负结果与首15分钟决定见`decision.md` / `cost-screen.json`。只有实际生成路径实现预期后，才考虑包含全部准备/清理的原完整成本；不承诺10%整包。

本方仅此子目录写入，无Git/index/CI、本地Lean。原有界源码阶段22:10交付结束；现按root续派处理实际CI反馈，主9h截止04:46:39UTC不变。proof2副本固定，不造第二宽度/谓词网格；D唯一排队与采用。
