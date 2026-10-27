# R14研究：原roundProduct形状引理已交付

时间：2026-10-24T19:15:07.035360+00:00
关联：R14-20261024T190259Z；回复20261024T190623507Z-r14-development-startup.md；已读DeepSeek p8/p2路由计划，不重复该方向。
类型：协作请求
摘要：已冻结仅追加证明的shape1：252569B，Kernel SHA-256 4c523fa6534e5c69ebda55b0c337e5d76be8cd7e88173545588a36007dacd792，保留df5c运行定义逐字节不变。新声明覆盖24位尾数乘积界、log2∈46..47、原UInt64 roundProduct在174≤指数和≤379时的同一舍入尾数/指数正常式，以及首个整数尾数乘法scale298的特例。该探针还没有证明两次native乘法等于原mul，也没有性能结论。
需要对方：你当前完整CI终态回收后，请按精确请求安排原pinned statement/rounds0验证；如方便同时审计5个新定理的公理。不要打断已启动运行，不需对此纯证明探针做25轮计时。
证据：D:\CodingProject\Bitget\competitions\floatlib\candidates\f01-d7-research\round8h-20261024T190259Z\astra-ci-request-scale-shape1.json；请求文件SHA-256 0c367563e66f871589c2ab946a2072f9e5bb56c26e36d3b3ff04daae24b3a6a6。候选D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-r14-math-scale-shape1/Kernel.lean，未提交冻结快照。上游固定FloatLib0d918源码/许可证及哈希在本轮astra-upstream-receipt.json。原pins仍记旧978，但本请求按current_protocol的4b7/public-v2与Lean293d5d0c执行。
结论状态：NOT_RUN（全部新Lean定理），静态append-only及字节/体积核对VERIFIED；native融合、380边界强化及实际收益尚未闭合。
下一步：研究侧继续构造首个native乘积decode及精确第二次缩放桥，保留379上界先降低证明复杂度；再补380的真实24×24乘积无h47 carry界。
