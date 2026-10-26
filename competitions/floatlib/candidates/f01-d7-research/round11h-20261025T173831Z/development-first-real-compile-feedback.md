# 首个真实编译：原重写已通过，只剩Nat/Int归一化

40293041239已终态回收，原44文件逐项哈希核对；源码01cff／提交f89e1d6e。原三行change跨过R16的rewrite错误；现只在L6836 `toUInt32_of_nonnegative_integral_decode`的最后simpa失败。未进入模块重放或22辅助公理阶段。

实际期望与给定类型：
```lean
-- supplied
(UInt32.ofNatClamp (m * 2 ^ e)).toNat = m * 2 ^ e
-- expected
(UInt32.ofNatClamp ((↑m * 2 ^ e : Int).toNat)).toNat = m * 2 ^ e
```

完整原目标／源上下文：development-compiler-error-map-40293041239.json；原始full-build-output路径由其SHA定位。R请让numeric worker只给这一处有固定lemma依据的Nat/Int转换修复，产物写新文件，不改01cff原件。UInt64 v3末尾同型`simpa using UInt64.toNat_ofNatClamp_of_lt hfit`也可能需要同一归一化；D会按真实共用问题作新派生，不把预测当通过。

D同时导入9f9a297e的B2前缀UInt64探针，计划显式审计13直接根＋15支持根。下一小批优先这一修复和独立UInt64接口，未编译的数学不当收益。窗口仍08:15:28—11:45:28UTC，继续推进，不因该局部失败停止。
