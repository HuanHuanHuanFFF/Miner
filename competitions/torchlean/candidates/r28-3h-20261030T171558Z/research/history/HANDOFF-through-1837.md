# R28研究当前交接
共同UTC17:15:58—20:15:58；R实际首clock17:21:11，三Astra17:22:10/26/41接入，均不延长。R独占research/，D唯一Git/CI，初始化后全树files only；status/CI-REQUEST为当前索引。

**本轮尚无新冠军；新候选原gate/性能均待真实结果。** CI1只得到baseline11六cell/36checksum插桩：conv76—79%、BN12—13%、add4—6%（不是整模share），故主攻conv，add停止单独主投入。candidate49e5多余rfl失败无计时，D已修并收齐执行终态，平台旧状态另保留。

- 已完成一次关键组合审核：D ResNet zero+inplaceBN+mapIdx-v2 **70eed360/255847B**，intake/resnet-combined-independent-review.json；三处互不相交且用11精确算术，full12与真实成本UNKNOWN，153B空间风险已列。
- Mobile **dc610a60/255397B**已冻结CI2 run41103226283（D dispatch ff05aa6b）；父已重建/审核。新局部channel128 **662f2814/253201B**明确NativeOnly无correct，父关键producer/偏置/128carry复核在intake/local-channel128-independent-review.json。其它变体不盲目扩队列。
- Mixer norm26 **79615bd5/255514B**已父重建，D>0与ra/D<2^26关键界已核；原singleton578f因13/18旧模型span全miss降优先，不标native负。D统一有限吞吐与新确认预算。
- 数学：winograd-bounds/BLOCK-BOUND.md得到通用块14安全、15通道实际finite词反例4d86ffff→cd720002；A已独立复核（resnet-mechanism/parent-spatial-review.json），非Lean/native证明、非原11漏洞。A空间变换与支撑缓存、B局部尺度、C中心化继续隔离研究；parent sparse-input与A支撑编码属同族，不算独立证据。

source-budget/compact53.py仅证明拼写释放3422B，不能盲套11；RELU-COVERAGE-DECISION核近榜dot全false，直接ReLU证书停投。Pro当前工具无IAB，面板请求仅queued且无browser，quota UNKNOWN；三Astra持续推进。记录含失败/反例/未闭合项，整上游源码与聊天原文私有忽略。完整技术证据从各路线原件进入，私人授权锚点仅local-private/；资源RESOURCE-LEDGER（root-only非全树账单）。

最新补充：D draft support-v2 a498d9b7/252237B一次关键边界审核完成，intake/packed-support-v2-independent-review.json；odd尾channel有效context、encodedzero/sentinel分离、CHW位置、bias/zW及原fallback已源核，仍NativeOnly无新correct，无新增CI请求。

当前快照：champion64-reallocation.json已核18:15官方raw/publication，Res现任64，链式规划约19.015%（历史晋级config不同，属跨配置/环境INFERRED；本轮active policy未变），旧6.07%只历史。Mobile优先仍不变。父接受A稀疏成本纠正：原11无weight过滤、36对16不是18对16；winograd-bounds/SPARSE-BASELINE-CORRECTION.md留明历史修正，不新增CI。
