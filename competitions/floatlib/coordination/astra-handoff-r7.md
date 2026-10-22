# R7：十小时协作冲冠

用户明确要求继续协作10h，中间不停、跑满窗口。共同墙钟为2026-10-22 18:22:17—2026-10-23 04:22:17 UTC（北京时间10月23日02:22—12:22）。准备、研究、修复、等待与交付均计时；窗口内持续选择有价值的下一动作。02:45 UTC冻结主要运行源码、03:15前启动最后独立确认，剩余窗口用于验证、反方检查和证据回收；已启动CI自然完成，必要回收可越过截止，不再开启研究。

继续既有Astra研究会话与设置；D负责协调、Git、推送、CI和采用。R只写research/astra-collab-20261023-r7/及candidates/f01-r7-*/，D只写f01-d7-*及公共状态/看板。原有dirty草稿均保留，不切分支、暂存、提交、推送、派发CI或覆盖对方文件。普通交接落盘，在阶段检查点读取。最多2个公开标准runner并行，不用付费/private runner；正式提交、注册、签名和资金不在范围。

目标仍为取代评测时现任冠军，按“耗时占比×可实现降耗，再考虑完整开发/证明/验证成本”选择具体路线。当前完整包f01-d5-stream-pack/Kernel.lean，SHA256为8eb63a2fea39f8c483eb16857cb1dcc35ac4a30168ab91046a48aa1cb561e045，139972字节。新public-v2完整通过719/720，当前份额中位数add18.7%、mul20.7%、sum10.9%、bmm49.6%；seed719的bmm:specials占整包17.1%，ml12.2%，extremes7.3%。旧12类份额和冠军推算不跨suite使用。

先读本赛道README、track-rules、pins、docs/suite-transition-20261022.md、research/RESULTS.md、R6 final-handoff.md、nan-bridge-remaining.md，以及candidates/f01-d6-research/public-suite-results.json。实际当前官方源以D新查询为准。完整验收要求四项原spec、原obligation、重放、仅三允许公理、原版suite所有case和25配对轮；没有正式冠军对照不宣称夺冠。

R优先独立研究并实现精确非有限值路径：矩阵NaN/Inf的回退或原生桥接、dot中乘法先quiet后相加的后缀吸收、以及sum溢出/Inf桥；自行按收益与证明成本选分支。D独立推进多shape矩阵布局/宽度/准备成本，避免重复。不要只提交抽象前提或旧证明重放：尽早关闭实际Model/Configured/ExecFloat桥接，给出能被D编译的完整候选及精确manifest。R6 dfef非NaN探针、W03条件证明、公开FloatLib分类可复用；普通sum的qNaN不是对后续sNaN吸收，保留sign/payload和有序舍入，不用FMA/重排。

按可复核阶段交付，第一份研究状态/路线检查点在30分钟内，第一份关键引理或最小候选目标90分钟内；每阶段依据D的真实CI反馈继续，不因单个候选完成提前结束整个窗口。持续阶段预计每30—60分钟自然检查点读取development-status和coordination/r7-feedback.md。未知收益保持UNKNOWN，工具故障与算法反例分开。若用网页研究，遵守原授权和审批、只携带可公开材料，控制活动数量并在窗口内回收全部原件，不阻塞直接研究。

首次写research-status.json确认进入执行，列活动路线、精确源与下一检查点。每个候选标NOT_RUN直到真实结果，并交代相对旧路线的实质变化、成立条件、全输入义务、运行路径、最小证伪与预期完整成本。D核验后决定采用。统一状态入口仍为coordination/development-status.json，本轮原始报告在candidates/f01-d7-research/。
