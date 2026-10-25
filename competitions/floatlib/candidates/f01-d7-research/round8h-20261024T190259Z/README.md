# R14 八小时三方协作

窗口为北京时间2026-10-25 03:02:59—11:02:59，源码冻结目标10:02:59。[计划与分工](round-plan.json) · [当前开发状态](../../../coordination/development-status.json) · [恢复入口](development-NEXT.md)。

目标仍是新冠军。当前保留df5c，尚无新采用；01:19Z官方刷新仍为#309、官方协议4b7e。冠军模型保持8e68，四项耗时为冠军的add1.03／mul1.15／sum1.16／BMM2.73倍，整体1.25倍。[四运算看板](../../../../../dashboard.md)

|当前路线|精确候选|实际状态|
|---|---|---|
|纯UInt64乘法、偏置RNE及直接字段打包|integer-exponent4，2c7194cc|真实错误修复，statement40151550349在途|
|UInt32对齐／最高位与UInt64舍入加法|word-add-entry2，f958071e|已接真实public add，修复后statement在途|
|整数加法＋乘法＋薄列缓存／p8直算|allword-combined2，27cc5fc6|253329B，剩2671B；共用数学与依赖裁剪已接入，修复后statement在途|
|薄列B一次准备、跨m行复用|thin-bcache2，177b86c6|原版完整gate通过；首D whole0.97271未达0.97，BMM0.84473，停放|
|原生一次乘法与指数平移|native-exponent1，913d715b|真实编译未过，先停放附加桥，优先整数乘法|

[第一批真实编译反馈](development-compiler-error-map-40149766137.json)绑定source e5b2f2d3和原始72个成员，五项均失败。薄B仅去掉一条冗余dsimp；标量修复由研究与开发分别处理，旧候选及原始错误不变。[首批修复](development-first-real-compile-repair-build.json) · [开发字段修复](development-word-add-fields-repair3.json)。新源仍需实际编译、重放、公理检查和计时。

组合原稿277331B，逐片复用公共正常数舍入／字段证明，再删除无引用证明和静态局部名字图中的不可达helper岛。[完整派生](development-allword-combined-build1.json)保存父源、阶段哈希与每段删除坐标。静态图不替代Lean；真实首批编译没有新增missing-identifier错误，仍须修完后完整gate确认。

本方此前五项CI均终态且原件齐；第六项40149766137失败已全收，第七项40150334243成功全收，第八项40151550349三项修复statement在途。[终态收据](development-terminal-40149766137.json) · [当前CI](development-ci-job-40150334243.json)。前置NaN与行NaN方案的完整负结果保持停放。83a9只通过固定旧套件，当前public-v2收益未测。DeepSeek6990首个D未过，后来正输入组和复跑作为附加诊断，不能替换失败D。

01:12Z已收到本会话人类对本轮剩余公开推送与手动标准CI的直接授权，[范围收据](development-public-scope-authorization.json)已记录；不改写此前207旧指令误用的历史。最新公开a2cc9bf0包含三项数学修复与待派发plan1425015，已收D使用固定a05e80a6。私有研究聊天、上传副本、钱包及凭据不在公开范围。

本机不跑Lean或重型编译。研究负责astra-*数学片段，开发协调Git、CI、入口与word桥；自由侧在独立worktree探索。公共区短状态和逐议题文件交接；完整证据从本目录、ci-runs和双方状态读取。新双列共享输入机制仅发出源码探索请求，尚无交付／收益结论。
