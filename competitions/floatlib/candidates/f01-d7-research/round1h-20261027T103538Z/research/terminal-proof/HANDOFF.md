# R21 A当前交接：终端原public证明已闭合，后继writer仍未验

实际开始 **10:38:49 UTC**，持续至共同 **11:35:38**，晚接入不延长。共同截止已到，11:36:34之后仅处理D释放摘要及状态收尾，无新研究/源码/CI。D唯一Git/CI；本方只写terminal-proof，无本机Lean/子agent，末段不增新大源或长CI。

**实际采用验证源是7de，不是b66。** `count-two-repair/Kernel-terminal-count2-repair.lean`，238168 B，SHA **7de57a414bce7ba3e8541d90c89acb9b505dbf930c5635efd9b3825889bda512**。D候选dc4，CI40492989029/a9a4053f已声明、Submission/VerifyFull原回放、9根三允许公理PASS；绑定见accepted.json及root原件回执。它在独立count=2下subst后以Fin.foldl_succ两次/zero闭合依赖writer，全部运行/域/原陈述不改。完整publicD **40493865047**已由D释放：原完整gate与25轮PASS，whole/B2 **0.99151657**、BMM/B2 **0.94317027**、收益p05 **−0.02486428**，未达采用门槛；精确runtime PARK，不A/B或换seed。后继源不变；冻结期间未读取其输入/结果，释放摘要见released-fullD.json。#336只绑定622d原B2，不继承给新源。

**未采用替代稿** `fin-two-repair/Kernel-terminal-fin2-repair.lean`，237770 B，SHA **b66aea4529988c35f4d6b2bba8752a241a06482f66a8da7c1ebab960a4ad3741**，仍NOT_RUN。CI1 ifFalse、CI2 dependent count、CI3 List.finRange残余原件/逆patch均保留；batch4-source-identity.json明确版本身份。冻结D源没有原地改写。

**隔离后继接口**：writer/WriterTransport.lean.inc（fb9e9abe/2873 B，6根）给整行finish、双row-major emit、同batch/相邻基址；ConcretePairPrefix.lean.inc（c3e4fb0c/2095 B）把B现有streamedRows运输到原RowStream.point。批内floor(m/2)对＋独立奇尾再到整batch的证明尝试已汇成 `writer/full-matrix-proof-reproduction.lean`，250211 B，SHA **c3c3d6cb7fca720beebcf270036f076508abbe62ab40e722e37c8a3a7ffe2705**，34根清单/各部件hash在full-matrix-manifest.json，固定文本检查过，**全部新组合Lean NOT_RUN、公开入口仍B2、无新性能结论/CI请求**。复用B冻结v2/4e36及driver/ba2d，不改它们；显式β/out的BatchPairTransport变体单列，旧613ac保留。

**必要边界**：全局flatten行数每2行配对在奇数m时跨batch共B错误；本方writer/odd-batch-counterexample.json与root反例均保留，非B当前同batch raw两行或B2的bug。后继要求i+1<m、batch内配对、奇尾用原单行；m/n/p0仍覆盖。所有proof接口的hstep/point义务都必须由具体实现关闭，不能冒充实际CtorReuse/COWfree或完整新public接入。
