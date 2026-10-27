# CI21成本前提：GO一次干净原完整D

**精确broad2 bb058c75/255724B值得一次完整D测净成本，原whole≤.97＋正p05及完整gate/controls不变。** 不预测过门槛或采用。core4 c7e7/249694B的13根、broad2的20根及两模块replay成功回执已绑定；本次不扩大数学复核。130原件SHA均核过。

实际C链：MainFull public BMM闭包→Column4 dispatcher真guard→output→Fin row(spec2)→真实group(spec1___redArg)→Column4 loop___redArg。group native call `0x1f6`的relocation `0x1f7`直接指向所检查redArg，未拿孤立loop、8字节包装器或旧R12四lane替代实际体。四个guard miss均回保留PackedB2，外层UnderflowZero仍先判。

output只准备一次flat A4与一次B16，随后row/group共用；selected路径无B8 low/high/join临时重建、每group重复pack或result tile。PB实际准备链为packB→ofFn回调→pack→实际pack___lam__0，后者直接16个原codec站点并构造一条64B原生字段B16记录；不是根据独立导出packet作推断。准备期仍有outer/inner ofFn捕获闭包及记录/数组成本，无逐Float32盒，不能记零。

正常small-Nat、范围内full4k机器路径：无codec/call/动态apply/heap，每块借读A4/B16固定字段，四lane保留原k顺序。仍有**一次16B累加器reload/store、指针栈读、184B栈框架和6个push**，不是无spill；冷大Nat、短尾及终态另有call。SIMD/no-codec只确认机制实现，不是相对旧R12的新收益。

每group终态F4真实`mi_malloc_small(24)`＋heartbeat，emit后decref；group还保留ix函数call。emit C每输出lane仍呈现3个Nat乘法地址站点，四个结果按各自finish/NaN原字回放、UInt32输出与push处理，不假定这些被免费消除。DC odd p仍多一条不emit的phantom lane；新低行/宽路的A4/B16准备、驻留、原raw输入、析构，以及原完整pass中的finish/checksum/cleanup全部计入完整D。

净生命周期能否抵消收益仍UNKNOWN，因此此阶段停止继续扩大静态审核，用一次干净完整pass回答。captured对象为statement重放对象而非已清理的timed对象；最终ELF和上层完整native入口链未导出，已明确边界。没有读取后续D/确认输入或计时，没有Git/CI/本机Lean或源码修改。

精确hash与路径：`review.json`、`all-originals.json`、`native-full4.json`、`selected-C.txt`、七段实际ASM摘录及`receipt.json`。
