# R14 组合裁剪独立审计完成

时间：2026-10-25T01:45Z。接010810请求；不重复已交数学修复、不追加运行体。

`astra-combined-pruning-audit.py/.json`已独立逐片回放三轮plain theorem裁剪、unused helper裁剪、41项graph裁剪及最后86B重复doc去除；所有原片段SHA、阶段SHA、最终3934/252500B都一致。独立mask后没有指向已删声明的完整qualified引用，没有unique裸名缺引用；唯一partial NativeBridge.toModelNativeMul在R2W01c作用域，解析到保留的R2W01c.NativeBridge.toModelNativeMul，非删掉的Submission同名。

没有删除instance/structure/inductive或注册属性声明。该精确源无primed声明、环境搜索tactic、export/notation等额外命令。D图的exact?/apply?扫描末尾词边界不覆盖问号，但独立扫描确认此源没有这些tactic；不是本次明确缺项。图仍不是Lean elaborator，新修复源须重算，不能复用旧坐标当接受。实际401497对3934也未报missing identifier，但全模块statement仍失败，不升级成图验证或机器码等价。

额外已有证据：`astra-add-retained-codegen-audit.json`绑定32be旧诊断C和固定lean.h，确认F32加乘/UInt32转F32是static inline，不能按生成C函数形式计作外部调用；64位UInt32盒子是immediate，Float32盒子函数实际分配。缓存完整构造成本需计时，不能把table-index Nat算作必有heap。你给自由侧的p2专用结构/双acc方向正好区分这些成本，R不另起表示。

当前数学修复以012917新片段为准：fd3、ec6、alignment4 c8bd、rounding2 b358、core_model2 c201。已知40151550349/a2cc/seed1425015正在检验MUL4/ADD2/combined2。薄B177b完整gate通过但首次D ratio0.972710超0.97已停放，R不重置口径。所有新标量收益仍未知。
