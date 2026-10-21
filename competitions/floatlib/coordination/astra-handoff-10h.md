# FloatLib 十小时协作续跑

用户本轮明确要求：继续协作推进优化10h，目标是拿下新的冠军。共同窗口2026-10-21 18:16:11—2026-10-22 04:16:11 UTC（北京时间10月22日02:16:11—12:16:11）。准备、协调、排队、失败、验证、复测与交付都计入。03:15 UTC前开始最终冻结／确认，03:40后不再启动长实验；已启动CI自然收齐。

本轮沿用huan-collaborate、huan-open-research。总体状态唯一入口为development-status.json。目标以真实当前冠军与官方晋升为准；旧参考提速是研发证据，不能当作新冠军。

## 分工

D（01a15ce7-bf54-74b2-8a2b-4a1e2f3828d7）负责candidates/f01-d2-*、开发状态、看板、集成、完整gate和计时，是唯一Git／推送／CI协调者。当前共享分支codex/multi-track-floatlib，不切换、reset、stash。D首条路线：保留精确守卫和原始异常回退，将已通过sum的Float32原生累加器推广到每个bmm点积，再按反馈削减转换与守卫开销。

R（01a15e06-b75c-7811-b0a0-194d8877365d，GPT-6 Astra／xhigh）只写research/astra-collab-20261022/和candidates/f01-r2-*/；不修改D文件、旧原始证据、pins、官方源、contracts、gate、bench、共享Git／CI。保留你上一轮新增网页6 Pro交接约定。可按已获用户授权使用网页6 Pro研究适合的问题，使用实际可用浏览器与实际模型；原下载件留E:/Download并附原件路径、来源、时间和SHA，遵守本机写入权限。不要因网页不可用而停下可直接开展的研究。

首个交付重点：先核对、完善旧native-roundtrip-bridge-draft.lean与native-finite-bit-bridge-draft.lean，让finite转换后的逐位往返可由证明消掉运行时raw guard；交付独立源码或候选与关键疑点，D用临时Linux CI编译。然后研究bmm与冠军的剩余量级差距：原生Float32数组、保持k顺序的多输出累加、跨输出向量化、合法编译展开等。先核查公开实现／现有定理与实际bench，不能把旧的inline微调换名重做。冠军源码尚未获取；当前机制UNKNOWN，不据历史乘数猜其源码。

## 可访问起点与验收

先读根AGENTS.md、FloatLib README、docs/track-rules.md、pins.json以及本交接。上轮结果在candidates/f01-d1-inline-all/window1h/README.md与summary.json；三份冻结原生候选各有两次完整gate。native-both-proof1 SHA707d22fe...，native-sum-acc SHA75524a31...。R-01—R-07及公开源码／许可在research/astra-collab-20261021/。D会刷新官方冠军快照。

Lean4.34、FloatLib和官方commit沿用pins；单文件Kernel仅import ContractTensor，四函数四全域精确义务，含NaN／Inf／次正规数／正负零。bmm每输出按k逐步mul再add，不FMA、不重排。只允许propext、Classical.choice、Quot.sound。所有重型工具链仅公共临时GitHub标准runner；本地轻量源码／模型／证据。只D派发实际验证。已有窗口失败与性能证据保留，不把草稿或有限模型称为正式通过。

R每一可执行交付完整写入后，更新research/astra-collab-20261022/research-status.json：事件ID、确切路径与SHA、变化、前提、反例、证明状态、最小验证请求和下一步。普通交接走文件，在下一候选／CI前后读取对方状态。D在总体状态写采用或失败反馈。减少待测积压，先修能改变方向的关键缺口。R不额外创建会话或子agent，不给其他会话发消息，不正式提交或进行钱包／注册／签名／付款。

预算到期与目标达成分别记录。窗口内只要存在有价值的授权动作，就继续；若阶段结束先落盘具体下一动作，D可在自然检查点按本次用户续跑授权接续现有研究会话。最终保持所有冻结源码和公开来源归属，预留同版完整gate及新runner独立确认。
