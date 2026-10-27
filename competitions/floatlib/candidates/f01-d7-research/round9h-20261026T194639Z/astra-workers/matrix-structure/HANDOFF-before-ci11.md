# R19 矩阵结构当前交接

**当前工作入口：`dual-temporal-frontier/status.json`。** DualA4原9a5 statement失败；仅两证明体修复的d765/240398B已由D导入`f01-r19-dev-dual-temporal-a4-2`，1927009诊断批准备中，尚无新goal/C。保持冻结。完整调用预测见`dual-temporal-frontier/callpath-prediction-2301.md`；行内t/g调度仅为`next-proposal-row-interleaving.md`条件提案，未造源码/排队。R最新窗口22:58:21—02:28:21，D窗口不变。以下c70c已验结论作为组件历史保留。

**主源完整gate通过，首D未达整包采用门槛，不确认。** `Kernel-temporal-b2.lean`，237897 B，SHA **c70cf9479ca48b4690990ebbd0b3781139cbeb94e46b28bbe61563e3eeaced1c**，D候选 `f01-r19-dev-temporal-b2-1`。run40398675395/seed1927003，c70c与B2原full gate均通过、各25轮；whole **0.990205**、BMM **0.922129**、p05 **+0.007791**，ratio>0.97。保留局部单样本观察，不称跨输入稳定提升；原件复算见`first-discovery-review.json`，决定见`first-discovery-decision.md`。不重置seed。

证明/实现资产：run40395429076的statement、Submission/VerifyFull重放及13根允许公理通过。已核17原件、16个实际C函数及ASM：新loop确实选中，packet单32Bpayload、无额外数值遍历；inner closure每tile+16B、outer整次−8B。frame72→200B，但核定正常full4路径均8次XMM存/读，不能据frame判慢。证据：`temporal-codegen-review.md/json`；历史诊断当时NOT_RUN字段保留原状。

成本边界：n=2的packet+槽位字节不减；三个旧已完成B2组的条件请求减少约35%/44%/47%，A解码、valid B解码及output finish不减。`cost-ledger.md` / `cost-snapshot.json`保留精确输入与计数；动态可回收成本和10%整包收益UNKNOWN，不改冻结谓词。

**备选不排队：** `Kernel-fused-output-b2.lean`，234407 B，SHA **764615ad5348dc0032fda9aa956685b2bd2124bf0bd7951db455231c079b1000**。原B2准备/MAC不变，loop终态直接finish/push，源级去掉结果F2和动态lane fold；新增live参数可能反噬。`output-fusion.md` / `fused-build.json`；Lean/C/性能NOT_RUN。未组合或造第三稿。

**新判别已交主控：** 旧精确622d的实际B2/DC output专门化调用链已无逐行closure；通用row中的closure不在该选中链，不能以它估算新rowLoop的可回收时间。`closure-hypothesis-review.md`、`closure-evidence.json`含原件SHA、11函数、调用和行号。DeepSeek已认领并在测外层循环，本方不重复；已启动CI照常收齐。

权限与下一步：仅本目录写入，D唯一Git/index/CI。等主控下一阶段，不组合备选或改谓词；新组合必须新精确源/完整发现，收益不可相加。token/cache UNKNOWN，诊断子段64.1秒、首次完整gate子段178.9秒，不含批次准备/排队/回收；本方派发CI=0。当前入口`status.json`，旧机制依据`direction.md`。
