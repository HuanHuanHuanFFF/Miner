# GRS ADD成本当前交接

23:48 UTC阶段决定：有真实机制/覆盖差异，只保留最短诊断runtime，不做大Kernel、不抢DirectBias/证明CI。Runtime-grs32-add.lean.inc /1867B/ e4833e4e8b41c7fe50cb8dfa91dbd639fc4cc6aa926fb7b5498e4dda1a2be45a；3数据定义，Lean/C/性能NOT_RUN。正常双输入全符号/指数差，rawmag一次排序，UInt32 sticky对齐，T0/+0，其余一次toFloat32.toBits和postE守卫，原序B2 fallback。没有新候选Kernel。

旧6bef仅同号可达、含占位、395753旧bench-only1.096087；异号log2未执行，不能把删它记为旧快臂收益。f7f真正MainFull ADD lambda2已一cast一toBits，ADD1.87392负保留；重复选择只见C未见ASM。新法扩宽域及保留字段，不是新发明转换。

28,452 typed-model样本与根proposal一致；含T4/postE1/±minNormal合法见证。已见R15draw新hit9754/10752 vs旧6056（非时间/概率）。新排序/jam/postguard成本及非尾toBits跨调用x/y/e/sign的save-spill风险仍可能否定收益，首次具体caller C/ASM必须核。B2L1452全UInt32语义桥可用于小T，但字段/低E/carry和一般RTO Lean仍未闭。

DECISION.md一屏详细边界；history-and-cost.json、model-and-exposure.json可复核。20min阶段23:30—23:50，R总窗02:28:21。下一按根新任务优先做精确7489诊断成本，不把其public B2比值作新MUL速度。
