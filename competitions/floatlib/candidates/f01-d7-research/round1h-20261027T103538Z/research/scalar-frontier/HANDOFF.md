# R21 C当前交接：scaled-U32诊断冻结，其余廉价止损

实际10:39:17接入，共同11:35:38截止不延；首判别10:45:33晚33s，诊断10:56:44冻结早于11:00。只本方目录/授权r21-r候选，无Git/index/CI/本机Lean/总状态/子agent；继续窄核至截止。

- **正式依据**：#336只绑定B2/622d：whole1.628700，ADD各组1.345390–1.532804、MUL1.524899–1.649603。旧1.2487为历史预测，1.304不是通用校准，没有推导op聚合权重；新源不继承official_submission。
- **唯一诊断源**：f01-r21-r-scaled-u32-probe1/Kernel.lean，228050B，29d09f90c3116932461df2cc64e773e59873922dfe0a8714e4880214a1de7f2b。B2前缀逐字保持，4public仍B2；新增P.toFloat32×2^-23→UInt32/high/q的完整guarded caller，normal双输入/S128..380/原fallback不变。8根是4原spec＋4定义，不是新mul_spec；原静态gate通过，实际Lean/C/成本暂无回执，NOT_RUN。
- **小桥**：ScaledBridge.lean.inc5568B/a4432cb159c0980df0f3bab8435440b385af762c0d9e832bc3e935b2ecda2762；Helper-scaled-bridge.lean5587B/f41bfa397df0f74cd7f514647ec6d9bcef0fe9e6ad3ddb0719cb3c93433f9fa7，须import精确29d。7新根含真实same-width Model.mul→native、精确缩放、原已验UInt32cast体、high/q恢复，均NOT_RUN；缺P→decode接线及public字段/guard规格组合。root23,431对独立host检查只是有限模型。
- **历史/成本差异**：此式是R18未测储备续接；相对U64reverse删2^63补偿却新增FPmul和constant once/load；相对已负Jam17删sticky但新增FP依赖和较宽forward，U32clamp仍需实看。7489/d3c/9c4与R18负面全保留。COST-PREMISES.md明确实际完整caller、常量冷/热、call/frame/clamp检查，不由指令数宣称速度。
- **廉价NO-GO**：Float64最终native缩窄仍旧opaque无新桥。幂次因子整类消除早期转录1/10794不能作当前覆盖；D当前生成器/另一已见R15 plan为143/10752，仍不足投入，不相减作改动收益。65536项完整值LUT旧转录命中主要是零；B2零已走tableProduct，非ofBits冷call，重表/miss成本无支持，不造候选。
- **隔离后继**：LOW-LATTICE-NEXT.md保留raw magnitude<2^24首仿射段的整数ADD式；20676精确整数模型例0差异。双方真subnormal时连舍入都不需；E1/E1可能与旧R18域重叠，负面不可擦除。仅数学/有限模型，无实现/Lean/覆盖/性能，不恢复GRS或零捷径。

manifest.json列全文件哈希和缺项；源已冻结，实际反馈优先。未采用、无新正式提交，token/CI分摊UNKNOWN。截止前仅窄核和交接，不新增长任务。

末段在途：40496659327/02aa966d于11:30:29启动，D分行runtime29d(8根)与combined 56cdb076b82fb8212dfa7fcd535928cc96f5fa384c62c6647975ac9587fc1e35（233619B/15根=4old+4defs+7math）。两者仍无新publicMUL规格，尚未回收结果；11:35:38后仅收已启动证据、不修源/开新任务。
