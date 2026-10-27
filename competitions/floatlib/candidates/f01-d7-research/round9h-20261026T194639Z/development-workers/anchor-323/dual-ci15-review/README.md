# CI15结论：值得一次干净原完整D，收益仍UNKNOWN

**135原件SHA、精确c36bc250/241509B、statement、Submission/VerifyFull完整重放及18根审计已独立核过。** row_bound是零公理根，其余报告均在三允许公理内。未读取此新源的计时、未Git/CI/本机Lean或修改候选/全局。

真实C链为MainFull public BMM→Dual dispatcher（p3..8、n>1、m≥4）→output→专化row/pair→`R19DualTemporal.loop___redArg`。plain `loop`只是8字节转接包装，分析采用CI15同时采到的redArg本体，未拿包装器冒充热循环。selected pair C直接调redArg，无动态apply/closure；最终pair caller的native、relocation及ELF未保留，机器调用边/潜在inline仍不能独立闭合，未称整条机器链已验证。

| 相对c70 | 本次实际实现 |
|---|---|
| 删除 | 同A跨列组的重复raw读取/UInt32解包/getD及转换；常规full4块从4个名义codec call变为0，相关跨call临时保存消失。 |
| 新增 | 一次flat preparedA数组、每行ceil(n/4)个A4记录、padding、写入/重读、引用处理、驻留和析构。flat不是FloatArray：每A4仍是独立16B原生字段payload的ctor。 |
| 保留 | 原c70 B8准备/有效B转换/析构、两条原顺序MAC、每pair一个终态F2、每输出finish/UInt32 box/push及NaN原字回放。原raw A/B同时保留；c70本无结果tiles可删。 |

实际准备只建一个预留总容量A数组，按行直接追加；有效A元素每调用转换一次。无每行临时A数组、每字段Float32装箱、每pair重复准备或逐k动态A4选择。常规循环每4k借读一个A4及一个B8，A4固定offset四字段；短尾只做有效MAC。group的row/m及回放地址仍每group计算，未声称已移到每行。

同次对象里的旧c70 loop也已采：常规小Nat/范围内full4路径有4个call及16个向量栈保存/重载动作，新redArg无call但仍有2个（每块一次16B累加器reload/store），指针栈读取也在。新栈框架0xb8、旧0xc8；冷大Nat、尾、终态仍有call和更多spill。两边原有mulps/addps顺序相同，不能把“新向量化”或这些计数换算成速度。

相对B2，还包含已有c70的B8布局及4k展开；不能把c70已测过的节省重复计为Dual增量，也不能假设B2原输入存在逐Float32盒可删除。旧R19Temporal namespace9816原字节与c70完全相同（33eeb29a…），不是重新拟造旧对照。

建议以精确c36进行一次干净原完整D，完整计入A/B准备、缓存驻留、输出与析构，原whole≤.97、正p05、完整gate和controls保持。C与成对callee ASM已支持新的复用机制，剩余关键问题是新增A生命周期的净取舍，静态审核不能回答；这不是过门槛、采用或跨runner稳定性预告。

绑定：Submission C `ed2ffb74…`，MainFull C `94f69ed1…`，statement对象 `2a8342c4…`；均为statement产物而非已清理的timed对象。完整精确hash、18根、调用边与原编译参数见`review.json`/`all-originals.json`，常规路径逐条证据见`native-paths.json`，完整选中C摘录见`selected-chain.c.txt`，输出hash见`receipt.json`。
