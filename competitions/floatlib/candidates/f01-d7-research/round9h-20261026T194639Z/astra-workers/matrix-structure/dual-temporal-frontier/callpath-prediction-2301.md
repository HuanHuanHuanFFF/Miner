# d765完整调用的预测与反证入口

状态截至本阶段起点23:01:33 UTC：D最新404151是seed-isolation诊断，1927008计划是compact-scales首D；未发现d765的新goal/verdict。**d765仍未复编，本文是冻结前材料支持的条件预测，不是新C/ASM或性能验收。** 原9a5错误与proof2修复不再重复，见`proof2/REPAIR.md`。

关键边界：**相对c70c，Dual没有已知的堆分配可删除；它新增A缓存，换取重复A转换和读取的减少。** “没有跨行result tiles”只是避免R16的成本，不是相对c70c的新增节省。源中Nat控制也仍存在。

预期选中链是 MainFull的BMM闭包 → `Submission.bmm`原underflow判别 → `R19DualTemporal.dispatch`的p3..8/n>1/m≥4真支 → 新output → 一次flat packA与一次c70 packB → row/group → **R19DualTemporal.loop** → 原finish/replay与push → A/B缓存清理。p2和其余域仍进入c70；旧R19Temporal.loop在文件中存在并不说明新域用了它。

| 部分 | 必须在真正选中实现中看到 | 不能据此声称什么 |
| --- | --- | --- |
| 新native loop | 每完整4项借读一个A4和一个B8；A取原生字段，不再做4次raw-A getD/UInt32解包/ofBits。地址界由原证明参数擦除，不能退成hot默认值分支。 | ofBits不会从整个MainFull/二进制消失；准备、其他函数及原raw回放仍允许调用。 |
| 常规full block ASM | 沿实际small-Nat/范围内路径没有原4个decoder调用及其跨调用保存；要抓新loop或其实际redArg/专门化body。 | 没有调用仍可能因寄存器压力spill；源码中的lean_nat_*名也不等于每个正常块都外调。大小Nat冷路必须分开。 |
| A准备 | input valid元素各转换一次；一个预留总容量的A数组，R=batch*m*ceil(n/4)个16B Float32字段payload记录；没有每字段Float盒、每行临时数组或每group重复packA。 | 原raw UInt32输入本就用立即数槽，不存在可“去掉”的逐输入Float盒。新A记录/槽位、push、引用处理是正成本。 |
| B准备 | 仍一次c70 B8准备，原有效B转换、odd-column行为、尾字段和析构都在。 | 不把c70已取得的B打包节省再次记为Dual增量。 |
| 输出与回放 | 仍每pair一个F2终态、每实际输出一次finish；原nonNaN导入、NaN原字回放、全局A/B地址保持。 | 原codec与NaN回放不能计为本路线删除的工作；它们可能掩盖native loop的加速。 |
| 生命周期/普通miss | 新A在原完整调用边界内准备并释放，不留到测量之外；域外不能提前构造A。Araw/Braw为原回放保留。 | 不能只测准备后的dot，也不能把全局A的峰值当成R16流式单panel峰值。 |

最小生成代码判别先沿MainFull实际函数指针和条件真支追到新loop，再核packOutput专门化body。通用packRow/row包装器中的closure可能没有被选中；反过来，只有新loop的独立定义无ofBits也不够。若生成代码还重复准备、逐Float装箱或常规块仍有转换调用，先记录实现未达预期，不投完整计时。若代码实现条件成立，停止扩张静态审核，直接用原完整成本回答净效应。

令G=ceil(p/2)、T=ceil(n/4)、N=batch*m*n、R=batch*m*T。每新增A4记录对应删除的重复转换数是 **(G−1)n/T**，所选域范围2–12。由冻结的四组计划新推导如下（计数模型，不是周期）：

| 已见组 | 删除转换/新增A4记录 | padding占A4字段 | 新A请求/有效A值 |
| --- | ---: | ---: | ---: |
| 1526007 | 3.259 | 27.35% | 11.01 B |
| 1526101 | 3.659 | 17.41% | 9.69 B |
| 1526102 | 8.320 | 2.91% | 8.24 B |
| 1927003 | 7.092 | 12.66% | 9.16 B |

可见当前D1927003的摊销比两个旧组更有利，不能只据它判断泛化。n=2/G=2每个新增记录只换走2次转换，短尾风险最大；p2的零次数摊销因此已留给c70。全局A一调用峰值模型约0.35–0.71MB，原输入和B缓存同时存活；active row可能局部复用，但额外全局写入/重读/释放和缓存层次都要测。不能由峰值字节直接换算延迟。具体推导及冻结文件SHA在`callpath-prediction.json`。

R16已经证明“hot无转换”不是充分条件：当时实际wordLoop无Nat/ofBits/分配，但完整成本为负。Dual改变了复用方向、删除跨行result tiles并减少容器数量，同时新增全局A驻留、更多短尾A记录、从八链变成两链且保留Nat控制。其SIMD吞吐、延迟隐藏和缓存损失不能由R16未捕获的新ASM推断。本次不重审那份已验结果，按`decision.md`的原件入口引用。

净增量应按 **A准备＋A释放＋新旧native dot差＋缓存/布局/控制差** 判断；B准备和原输出/回放不免费。若整包没过门槛而BMM局部为正，按原发现角色保留，不进入确认；若改善来自未改动的标量漂移，不能把它归因于A缓存。原始25轮、source/reference哈希、CPU/绑核和完整控制数据都要保留；CPU型号未记录则UNKNOWN，不补猜。

下一次最小有用外部证据：精确d765 statement/两模块重放/18根 → 真选中C和新loop ASM → 原完整同run成本，含当前B2基线和必要parent/控制，D按槽位决定。不得把c70作为一个被“重置”的新发现或用局部microbench代替gate；所有新确认在最终源冻结后独立生成。当前不新增runtime版本或队列。
