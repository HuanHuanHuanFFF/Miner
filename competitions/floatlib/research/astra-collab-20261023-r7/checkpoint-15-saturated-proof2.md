# R7检查点15：实际复编译定位部分应用，统一proof2交接

2026-10-22 21:41 UTC。**请将未派发810中的39a/3baa以及0de/cff旧proof1换成下列proof2；旧源和本地冻结提交保留，不再请求验证旧proof1。** 公开推送仍须D已提出的用户确认，R没有推送、派发或向网页上传任何未公开候选。

## W09给出了真实失败原因及已编译完整修复

网页只读取匿名可得的8fc6a7ea公开b169源和公开808错误，精确原SHA匹配并实际复现第3262行`simp made no progress`。原因是`replayStep n baseA baseB p A B`缺acc/i参数；固定Lean4.34默认simp不会展开这种部分应用。

独立的首次两行simpa修复也实际失败。其SHA `3b7b874414716b237e19f56479f6c005bd9ac87c30e9b56168a0c4450a02cb56`与本地39a只差`using`的换行位置，空白分隔token串完全相同；**不冒称exact39a字节已被编译**，但旧策略的具体缺口已经复现。

最终使用原`replayEarly_eq`作等式传递，`congrArg`把fold等式转为步函数等式，再`funext acc i`补齐参数，最后改写已证add_eq/mul_eq。完整修复源**0e8bc05c**实际plain Lean退出0，四项原始add/mul/sum/bmm_spec以精确原类型独立检查，五项声明传递公理均恰为允许三项。原b169之外只改dot_eq证明两行到四行；所有运行定义/属性/接口/常量字节不变。**原版fullgate、C/机器码身份、性能仍NOT_RUN/UNKNOWN。**

W09原ZIP 1679256字节，SHA `6b3ea0b4e14ed5890835025fbc14f66e3a1e58755e8ae735fa3fb61d9700a632`；报告SHA `9f266252b8c3a9aad633da8138ff2f6fff00c8ec0a4d0d3e244647ed8d1cc26c`，CRC/96条manifest通过。原始失败、失败修复、成功完整快照和SpecAudit均在web/R7-W09。`web-proof2-identity.json`完成本地精确字节核对。

## 当前待验精确源

|候选|SHA256|字节|真实状态|
|---|---|---:|---|
|f01-r7-nonfinite-combined-proof2|0e8bc05ce954e3e8213fbef05ac6041f8f882673c88c1071a3c9d4254a3064cd|173212|与网页成功完整源逐字节同一；plainLean/原四spec/公理PASS，fullgate待验|
|f01-r7-self-nonnan-guard-proof2|1f4d31aadf4c4fd239b311a5776cdecca4ae2693e33ee4e0ccdd129db6e3bee2|175176|新整合NOT_RUN，四个终点守卫机制不变|
|f01-r7-native-repair-proof2|a9e546b68bf334c7d8d0d4a918a12b4c01dd153980ad8c372359424d2c7f3525|176460|新整合NOT_RUN，矩阵prefix机制不变|
|f01-r7-sum-native-repair-proof2|0fe7884f568c5bb9748bc36b11c731c846ffa596ebd94d254134d53f4a6a9f4f|188629|新整合NOT_RUN，sum prefix机制不变；另显式证明step函数等式后再重写fold，避开同类部分应用问题|
|f01-r7-canonical-bridge-probe-policy1|a4f26514082e3d35738d253207db9f3127ca16de20e55fc6ac54d075710297a9|193261|原statement-only数学探针不变，NOT_RUN|

`ready-policy-precheck-proof2.json`对应以上五份源静态全部PASS。sum额外变化仅在run_spec证明体，旧片段保留为sum-native-repair-block.before-partial-fix.lean；它没有继承W09的完整编译结论。新源进入当前ready清单，原proof1从队列退休且文件完整保留。

## W08b增量数学已闭合

W08b原ZIP SHA `7b1b340b70902297c490bf0a821568c67d56c174a075172bc0822936abff80a2`（55237字节），报告SHA `90c20a8bc147b6e78bc6495fffc1538622acbc021bbb0ffc1277bf4dc163c80a`，CRC/99条manifest通过。用真实Float32.Model/UnpackedFloat.add的NaN后缀吸收闭合flat=natBlocked及flat=usizeBlocked，全域所有数组/初值/raw fallback，空数组与NaN seed均覆盖。原W08定义字节不变，最终六个依赖模块和两新增证明模块重编译退出0；早期没捕获Lean退出码的尝试明标NOT_CAPTURED，不冒作成功。无新运行性能结论，原W08历史缺口记录未回写。

全部当前网页在途任务已回收；入口web-deliveries.json继续给出E盘原件与源/失败日志。分块路线仍按headroom证据降为储备，不新增运行变体。D11已读，保留标量特殊值与sum raw后缀收益重叠的警戒，不相加组件收益。下一步先补齐以上实际候选验收，数学资产与源码边界复核仍在授权范围内继续至原窗口终点。
