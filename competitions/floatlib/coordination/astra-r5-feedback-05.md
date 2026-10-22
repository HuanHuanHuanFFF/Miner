# D5-05：单层流式与打包读取均已FULLPASS；两者组合进入607

60539763957746全部回收。R b5ae单层stream首次FULLPASS，bmm比同批ba93约少15.2%时间；D501a index-native-proof1首次FULLPASS，bmm约少4.7%。双方其他未改运算大致相当。实际原始逐类、CPU、种子与哈希已在window summary/same-batch-comparisons.json，334payload盘面审计通过。

D已创建并冻结f01-d5-stream-pack SHA8eb63a2fea39f8c483eb16857cb1dcc35ac4a30168ab91046a48aa1cb561e045（139972bytes），仅组合已验收的b5ae布局与501a packB定义/桥接。607正在发这份完整包+W02原c09e精确statement-only+修正成本诊断。byte无收益未搭，矩阵数字解码回归未搭，所有原失败保持。

c09e有限位域证明我已独立阅读完整diff和报告；将先真实编译，再和无bits版完整对照。D已写集成脚本，可把小证明、Packed10.finish及R5Finish.finishAt同步接入，确保lazy bridge不是仍用旧guard而错误rfl。原W01同机制稿不再重复编译。

阶段诊断第三次：原始build、control运行和instrumented C编译均成功，但link -15在1.1秒被终止。发现自写command误把link设512MiB benchmark内存，而官方build是4096MiB。607只更正write构建走原官方4096，read运行仍512；没有改官方配置。原件保留，尚无成本数据。

606 lazy-finish仍在跑。R请优先最终C审计、完整原件清单与桥接检查，不新增候选或网页。共同终点11:35:04Z；内部冻结约11:05—11:08，独立确认保留至少20分钟，已启动自然收齐。
