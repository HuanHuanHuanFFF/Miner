# R14研究：旧mul实际生成C与并行网页Pro资源

时间：2026-10-24T23:27:23.830873+00:00
关联：R14；主线913d/6f88/ef5仍按开发固定顺序，等待新公开授权。
类型：性能机制核对／资源进展

已从run40135440097中精确32be Native2的Submission.c原件（SHA31e14092）核对旧DF运行：Kernel前248144B恰是DF，新增部分只有定理。正常公共mul路径确有2次UInt32→Float32、2次scaleTable读取/乘法缩放、一次结果乘法、自比较NaN guard及最终return to_bits；编译trace含O3和ffp-contract=off，没有flto。保留C及trace原件未改。

补查固定Lean object.cpp：of_bits和to_bits本体是bit_cast加NaN规范化/判断，不能称为昂贵软件浮点解码。旧最后return to_bits可能尾调用；一次FP方案在mid.toBits后还做指数/符号，可能有非尾调用、寄存器保存成本。纯整数源式不调用Float32，但重复P/R能否CSE仍要看新真实caller。表索引C虽有Nat/lean_dec，<=511属于x64小整数，不计作必然堆分配。所有这些不替代实际计时；现有asm只选Packed10Index循环，未据此假报scalar汇编或新候选收益。

沿用此前明确持续授权，已在Codex内置浏览器以UI Pro模式并行发出两个只读数学/源码咨询：共享整数舍入13KB新增模块及纯整数6f88字段审查。输入只含Kernel/证明源与约束，无钱包、密钥或会话日志；均UI显示正在回应。我继续本地研究，不阻塞等待。没有新建Codex子agent/工作区/CI，三方所有权与新Git发布hold不变。

权限来源已另从原始人类消息核实：2026-10-21T18:39:22.544Z msg_01a15fc2-c5b0-78d3-9e97-1866ec4dc7f3允许不限次数/并行网页Pro；2026-10-23T20:46:51.237Z msg_01a16a84-3365-7c01-bea6-5c6a4e755461明确完整候选源码上传研究“后续不要问我,授权”；21:01:48.106Z msg_01a16a91-e2c9-7331-adb4-11010e34c041指定内置浏览器。这是既有私有研究资源授权，**不是**新的Git公开范围，也不授权Pro代跑CI或推送。

网页结论只算未核验建议；返回后按用户要求下载E:/Download/FloatLib/20261025-R14并逐字整理进当前分支研究材料，保留原NOT_RUN状态/负结果。有ZIP则核验提取后只删ZIP，无ZIP不扩清理。UI截图另放本地visualizations，不进Git。B提示词旧父本gate措辞按原DF fullgate／精确compact only statement区分，整份新源不会被提升为已验收。

证据入口（本轮目录下，未提交快照）：
- astra-retained-scalar-codegen-review.json；SHA-256 09019797edd94831c4f36b0e408307edcdb069fa55f9ed80875667f6b44b0747
- astra-lean-float-bits-source.json；SHA-256 5d3d406faaf8a7c02981eb26bc5c83d66b75a35767f538586d80d7eac84f71ad
- astra-web-pro-dispatch.json；SHA-256 26e205a689f5d75ea22c3838f758dc49991eeadb79515c42a3145ca84dbd4b02

需要开发：仅在自然检查点参考真实C成本点；继续自己的冻结/CI安排。待网页有可核验关键修复，再交精确文件/哈希。不增加第三种乘法运行候选。
