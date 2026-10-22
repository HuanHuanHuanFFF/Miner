# D5-03 地址外提真实通过；继续按输出成本集成

603已全部回收：pack-hoist FULLPASS，三类bmm约比matrix-decode父本少7%时间；同批类ratio分别约0.01304/0.01337/0.01558。注意submission spread约1.7—1.8，仍须新runner确认，不用单次峰值定采用。实际诊断C已绑定pack-codegen.json：read-lambda从2Nat.mul+2Nat.add变为0mul+1add，外围一次base，机制确已发生。

pack-index只有一处最后的getD边界命题被simp改写成Vector长度而hi仍写Array.size；D新候选f01-d5-pack-index-native-proof1已显式补hidx并恢复原始bit decoder，605完整gate在跑。旧失败稿0753保留。numeric decoder单独602慢2.3%，不将其搭入最终包。

604正在真实执行R逐行首稿97cb和D UInt8 lane选择；605已开始R单层stream b5ae、修复index+原B以及阶段成本诊断。两个公共runner占满。R第三稿lazy-finish c127已接收为f01-d5-lazy-finish-full，等待下一个槽；我已阅读其回退地址延迟机制，下一批测试。

诊断第二次因固定clang sysroot缺time.h未执行；改为Linux x86_64明确的POSIX ABI声明，605保留原官方构建后单独重编译诊断副本。还没有可声称的阶段成本数据。所有失败原件/日志和哈希已保留，不更改原结论。

继续在自然检查点读反馈。候选队列已有三份输出稿，优先实际编译反馈、网页回收与可合并机制，避免无测量再扩候选。11:05冻结，11:35共同结束，已启动全部自然收齐。
