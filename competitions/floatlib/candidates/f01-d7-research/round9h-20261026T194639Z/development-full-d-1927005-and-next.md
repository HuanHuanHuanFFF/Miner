# 第二个完整发现组：收益不足，切换真实机制

40407333869／76b1e794／1927005已success终态、58份原件收齐。四源原完整gate/25轮均通过，无观察器。真正public Jam17 b271：whole/B2=0.998885，MUL1.017121，p05=-0.010815；索引内联f84：whole0.995855，BMM0.966865，p05=-0.006708。均不达门槛，不排A/B、不换seed重置。保留B2/622d与ab3b模型。

独立selected代码复核同时确认：f84接纳域消除了逐k转换call与spill，但新增判断/表读取/缩放抵消大部分完整成本；“目标代码出现”不能代替速度。该诊断对象与未来timed对象仍区分。b271真正MainFull确有Jam17核心，不能把本次结果归因于入口没接上。原输入/每项结果完整保留，不按有利cell选择。

下一单槽1927006先statement/完整模块回放/逐根审计：

| 机制 | 精确源 | 本批判别 |
|---|---|---|
| DirectBias固定23/24整数舍入 | 1180c82c… /235339B /14根 | 关闭旧seed编译UNKNOWN、postbias七数学根和完整诊断caller；public仍B2，尚无完整新MUL规格桥 |
| 双侧temporal缓存 | 9a5f19be… /240241B /18根 | 单一flat A4数组＋已验B8，检查A只准备一次、纯已准备字段hot loop、无重复每行数组，含新A生命周期 |
| 静态scale表布局 | 9c4e9505… /229293B /10根 | 一次checked FloatArray表、真实valid/size执行输出、实际ADD/MUL读表/窄化/额外flag成本；不自动排完整D |

前三条完整负/小收益源不混入新计时。v5只增加真实helper命名空间和固定两项#eval，诊断器只增加DirectBias/dualTemporal对象符号选择；官方contracts/gate/编译选项、采用门槛全不改。修改发生在当前两源首D失败且无确认cohort之后。此批只买接口/成本判别，不由proof通过推断收益。新的独立源码/不同成本条件才可能排下一次完整成本。

R请优先处理本批真实失败和完整public桥；peer scalar bits-conversion仍由DeepSeek负责，不重复。D继续唯一Git/CI/采用，普通交接用文件；研究窗口仍至04:46:39 UTC。
