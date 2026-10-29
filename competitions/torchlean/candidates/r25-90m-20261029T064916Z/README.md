# R25：TorchLean overall 首轮

北京时间2026-10-29 **14:49:16—16:19:16**，共1.5h。主目标overall冠军；[计划](round-plan.json)、[当前状态](development-status.json)。

| 路线 | 已核结果 | 当前决定 |
| --- | --- | --- |
| 新赛道完整验证 | 固定accb82，原baseline在两runner通过原intake/policy/statement/Submission与VerifyExact重放/AX | 原官方工具、源码保持原版，后续复用公共标准runner缓存 |
| 原生FP64证书 | Widen7/a88c原gate及6helperAX通过；29项key与17项finite组合仍有实际类型错误 | 只接受精确已验源；FP完整模型原型已成但UNPROVED/NOT_COMPILED |
| 共享解码／卷积窗口／Rat缓存 | 第一组policy拒绝，第二组通过policy但停类型检查，均未测速 | norm-proof1已通过原完整12证明、两seed/1800配对cell检查；overall对公开shipped为0.9280847×，耗时下降7.2%，guard通过 |

已收原件：[批1](evidence/40834710293/ci-run.json)、[批2](evidence/40837681089/ci-run.json)。批3仅收尾既有实验，精确计划见[修复批](ci-plan-batch3-repair.json)。[批3](evidence/40840742077/ci-run.json)已成功；全部3CI终态收齐。研究窗口按原08:19:16结束，最后CI至08:22:42后按授权回收。

所有性能都使用原官方完整模型生成器；公开shipped参照与冠军分开。新候选的完整12原gate已通过。原quick配置5轮/inner3/2ms、两rootseed，overall为0.9280847×公开shipped，lower gain=6.5296%、回退guard通过；未跑11轮/50ms独立确认，也没有现任冠军对照，不能替换看板冠军乘数。原始1800配对记录/3600个报告ns及checksum全部匹配，见[完整复算](verification/analysis-batch3.json)与[独立验收](verification/analysis-batch3-acceptance.json)。[看板](../../../../dashboard.md)以最新有效冠军快照为基准。

保留结果见[候选记录](../../retained.json)；窗口与全部原始证据见[收尾回执](closeout.json)。下一主线仍为能删掉整数累加主循环的原生FP64证书，源码已准备但完整证明与真实模型成本未闭；先修已有key/finite桥明确错误，不继续缓存小变体扫点。
