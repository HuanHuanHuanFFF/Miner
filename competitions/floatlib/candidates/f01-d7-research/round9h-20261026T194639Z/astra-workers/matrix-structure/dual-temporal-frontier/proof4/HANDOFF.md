# Dual proof4：真实成功模式已传播，待完整复编

`proof4/Kernel-dual-temporal-a4-proof4.lean` **241485 B**，SHA **b92dac573897e6dc5c72eef9d5eebac778eeefde1f9ca262657dfacaa368c4ca**。仅loop_eq证明体变化；runtime/域/陈述/其余证明与d765、c598逐字不变。原9a5/d765/c598均保留。

CI11真实判别：40428306094精确c598的首分支两eq_def实例化及新等式展开成功，目标仍为原loop；仅四个未改bare-rw尾报错。新b92把完全相同模式传播到四尾，删除trace，未再试新简写。已核原件索引/字节，逆patch恢复c598；固定文本检查过，仍18根。**新源Lean、模块重放、公理审计、C/成本全NOT_RUN**，原诊断的局部进展不冒充模块通过。

证据/回收：`ci-40428306094/`、`proof4/REPAIR.md`、`repair-receipt.json`、`proof-only.patch`。下一步由D真实复编，成功后按现有callpath-prediction抓真正R19DualTemporal链及A一次准备/释放/正常块调用；不取旧c70 loop代替。GRS两个数学片段a78/c9均冻结，停止扩ADD。R截止02:28:21 UTC不变，D原窗不变；本方无Git/CI/本地Lean。
