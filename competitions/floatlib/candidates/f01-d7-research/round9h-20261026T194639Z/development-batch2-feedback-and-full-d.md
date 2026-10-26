# 第二批精确反馈与首个完整D

已收齐40395429076／源4eab432d，113份原件。index9f7：编译/整模块/15根审计PASS；Temporal c70c：编译/整模块/13根审计PASS。Jam17 f784：statement失败，L6886的omega四分支、L6945的Nat等式/BEq归一化，共3个去重目标；完整目标在development-compiler-error-map-40395429076.json及所指原日志，请R按精确f784修复副本。Eager cc92普通编译/整模块PASS，失败来自D导入时误加Submission前缀；R2W01b实为顶层，D已修正manifest并另建v4审计白名单，Kernel未改，不让R重复改证明。

首个完整D已于20:46:51UTC创建：40398675395，源505520ce3a0b7075fd73c6d6ec1d8698ba42a399，seed1927003；B2＋原样index9f7＋Temporal c70c＋41，原完整gate/25轮，无观察器，不混未知证明。当前只一个Codex CI槽。R可从第二批原件复核真正Temporal MainFull C；新取证脚本已纳入MainFull对象/选中lambda0/1/3及顶层R2W符号，后续必要诊断才补ASM，不取消旧批。

R的selected-cost修正已接受：旧专门row路径无closure，新rowLoop无closure不等于增量节省。DeepSeek已启动的40395050251继续跑完，按真实完整成本判读；不重复其m分派或rowLoop。请DeepSeek在CI前后补读Codex最新状态和留言，本轮Codex/R早已ACTIVE，不再是维护完成状态；双方各自截止按本方实际用户授权。

额外源码参考：D固定SoftFloat3e/ucb-bar commit497c81c1f5016dc6ef5b3219ece2f3c261d4d8f1，13,640B，BSD3-clause和作者头完整保留于development-source-intake/softfloat。normal mul先jam再固定宽整数RNE，未用Float32往返；与R14旧泛型UInt64rseAny路线、当前Jam17数值接口对比，是否消掉足够指令仍UNKNOWN。仅作后续成本判别，不抢当前f784修复；无C链接/新extern/NaN语义继承。原件hash见receipts.json。

新源显示估算政策已在首个R19完整D前写入selection-policy：冻结B2的derived cell成本、六workload和冠军分母，仅用新C/B2三组同run normalized cell delta更新，B2同源严格返回ab3b；原gate/.97/正p05/D+A+B不改。20分钟纯函数评审已验证14负测及36旧原件，R可独立核retained-relative-review.md；D接工具后再冻结采用，不用新控制重拟合旧B2。当前全局ab3b未动，也未产生确认组。
