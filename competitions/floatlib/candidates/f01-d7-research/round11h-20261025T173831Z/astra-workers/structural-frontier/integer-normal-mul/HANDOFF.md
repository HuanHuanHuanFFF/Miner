# 整数性能支线停放；主B数值MUL公共规格桥就绪待编译

**主控决定已执行：停止扩大新的纯整数性能变体，不开计时队列。** 鲜核9038原源=40155753018原始输入，原verdict完整25轮PASS；相对当时df5c，整包1.0471437、MUL1.2908011。它已是同normal/S128..380域的完整专用整数核；R6的约14%整包负结果范围更弱，不能只援引R6重开。9038实际标量C/ASM未保存，重复表达式是否被CSE消掉UNKNOWN。精确原件绑定见prior-negative-binding.json。

改为复用9038的已验模型与规格骨架，而不复制其7864B R14DIntegerNormal整数rounder证明段。Old-model-support-v1.lean.inc只取原normal decode、generic Model乘法、raw指数/守卫等5941B支持；Public-numeric-mul-bridge-v1.lean.inc补固定BitVec.and_twoPow/msb_xor原字sign证明，并将已有Fields的精确E/fraction接到core_model、core_spec和完整guardedMul_spec。最后theorem对原B2 fallback闭合，没有留下sign或primitive假设。**这是完整证明尝试，尚未Lean验收。**

两个精确新输入：

- **先编数值接口** Probe-b2-u64-roundtrip-repair2.lean，240189B，SHA9be1162e920ccf2ca79ca066c72c5c645cb24b7aa6e0233080321ece63e84955。B2前缀不变，13直接根＋15支持根；已核与D的f01-r17-dev-u64-roundtrip-repair1逐字哈希相同，不重复排队。仅复用numeric worker共享的simpa only [Int.toNat_natCast]修复，9f9/v3原件未改。
- **依赖的公共数学桥** Probe-numeric-mul-public-bridge-v2.lean，255561B，SHA365f49b1180bae24f217e83089e7a70e71bea6e22696f0b2197a11dac6e7871e。63个显式根见HelperAudit-public-bridge-v2.lean.inc；原四运行入口不变，新公共规格在独立命名空间。它不具备新的性能入口，不应计时。

原固定intake/policy/options（含注释）及LF检查均PASS。公共数学初稿260395B，删除全源只出现一次、无属性的12个普通证明叶回收4949B；未删public *_spec、运行定义或命名空间。删除仅发生于新副本，逆向逐字节恢复通过。规范化修复与后续数学section选项计入后余439B。完整删除计划/源范围及两输入身份在public-probe-v2-manifest.json、byte-budget-preview.json；未来修改后须重查，不借旧裁剪状态。

与直接B2 FastMul.roundP路线比较：roundP_eq已验，但尚无一个现成定理同时关闭native-R整数值、finiteScale=S−2、position正常界、RSE/carry和无overflow全部机器字分支；新桥字节与编译代价UNKNOWN。本次选已有model_mul_normal_fields，因为其目标字段与当前数值字段完全相同，可避免另一轮正常域roundP分支证明。整段9038 mul_spec复用会额外带入已不需要的7864B整数证明；已选择更小的模型/spec骨架。

新输入编译、完整模块重放、显式根公理审计和性能均NOT_RUN。先用数值接口真实反馈，不将依赖公共桥当独立确认。无模型重跑、Git、CI、本机Lean或新性能队列；原始负结果和冻结文件保留。09:03现场看到主控线程因模型capacity处于systemError，D仍活跃；为避免交接堵住，将按用户已明确授权的本任务协作向D发一次必要通知，权限与截止11:45:28UTC不变。
