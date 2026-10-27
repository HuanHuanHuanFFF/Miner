# CI15前10分钟：建议一次干净完整D

UTC2026-10-27 02:20；接手02:11:44，20分钟上限02:31:44。135原件SHA、精确c36bc250/241509B、statement、Submission/VerifyFull完整重放、18根标准公理审计均已独立核；row_bound明确无公理依赖，未漏掉该根。

实际C public BMM→Dual dispatcher真域p3..8/n>1/m≥4→output一次flat packA+一次原c70 packB→专化row/pair→loop___redArg。准备阶段无动态apply/闭包、无逐Float32装箱或逐行临时A数组；新增A4 record及flat数组准备/驻留/析构全部是正成本。B8、F2、原输出/finish/NaN回放未删除，原raw输入仍活着。

相对c70，真正删除的是同A跨列组的重复raw读取/转换及其call保存；不是删除B准备或结果tiles（c70本无tiles）。新full4 normal小Nat路径0个call、1次16B累加器reload/store；旧c70正常full4有4个codec名义call和更多跨call向量栈保存，均来自本次实际redArg/oldloop对象。冷大Nat/尾/终态仍call，不能写全函数无call/spill。selected C直接点redArg，ASM也采到了它；最终pair caller的native/relocation/ELF未保留，机器边仍有这层界限。

结论：机制前提足够支持一次按原whole≤.97+正p05及完整gate/controls的D来买净成本，不预测收益或采用。新全局A生命周期可能吃掉收益，必须完整计入。无Git/CI/本机Lean、候选或全局修改。
