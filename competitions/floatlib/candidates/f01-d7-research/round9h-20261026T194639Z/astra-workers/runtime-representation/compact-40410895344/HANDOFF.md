# Compact404108 当前交接

22:40 UTC：**已有compact接口关闭，无需proof修复，源9c4e不改。** run40410895344/d6b76/1927006中VerifyFull+benchFull编译、Submission/VerifyFull重放及10根allowed-only均PASS；亲读helper raw最后两行true/512，未由batchfailure或脚本exit猜测。audit.json保存全部精确绑定。

Actual BENCH_PLAN仍ADD lambda0/MUL lambda3：连续表movsd+cvtsd2ss真实存在；额外globalvalid读/分支保留，MUL低指数臂先绕过valid。选中体无.data materialize、逐调用map/check或initializer；原decoder分类、native算术、postguard/toBits、冷回退和frame均保留。四个有.data的私有splitter仅声明/定义，无调用，不能据grep误报热物化。

**初始化成本不能缩写为4KiB buffer**：原Float32表、中间Array Float及512个boxed Float64、packed512-double buffer都保留。实际C先构造packed再valid；once冷路径将中间Array标persistent，所以mk后lean_dec不释放它。初始化在Module init/Bench调用前，不在每scalar；全部构造/校验/once/持有成本保留，未改原计时协议。

REVIEW.md详地址/作用域；源9c4e9505702231fdb93f47f8d767ba0b2b0c2ad7ec48d8894b5a53ba87657645仍229293B。完整gate/checksum/计时收益NOT_RUN/UNKNOWN，不把少指针追踪当提速。是否占完整D由主D决策，不自动排CI，不造新变体；1d15/b271未改。本阶段结束可交回根，主窗04:46:39不变。
