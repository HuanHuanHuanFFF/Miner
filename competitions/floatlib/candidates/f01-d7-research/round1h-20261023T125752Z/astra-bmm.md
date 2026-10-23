# R9矩阵研究检查点

13:06:50 UTC首检查点已在同名JSON保存。选择现有NaN端点回退内的原生累积前缀，首次NaN只修复一个精确原字步骤，再用41已通过的W05 quiet-event证明结束。普通BMM热循环、packed/direct布局、41标量与sum保留。

旧a9草稿保留运行时quiet判据及完整软件后缀，本轮利用已验W05去掉这两项，且以815修复后可靠的fold等式运输连接归纳步。旧native-repair在当前public-suite索引没有任何实际运行回执，不把它称为旧成功或旧失败；这是该机制首次接入当前保留包，不是重复width参数搜索。

全局width4/8在809的BMM比分别1.457/1.506，不扩大同类网格。packed准备/低次正规硬件乘法仍是不同问题，但需要额外完整成本与有序舍入证明，本窗口先选可用现有真实引理闭合的一条。

807源模型7365个精确replay步骤、2860个NaN输出，给4505个事件前步骤与2860个事件步骤；这是旧输入模型，不是当前二进制时间。首次native整遍和准备成本不消失，新回退每步需检查NaN，事件还会重复一次原生运算。41完整821/822的specials cell占整包9.3078%/4.7079%，不能把这些完整cell全算成可省时间；subnormal8213.1469%/82210.6036%也不能直接归因到NaN重放。

## 首个可冻结稿

[f01-r9-bmm-native-event-replay](../../f01-r9-bmm-native-event-replay/Kernel.lean)：**0d9c2c96a4cb6c92609d8fbd1efac71852d7b75fafac5d3723935f17d5c15ee0**，239412B，余16588B。已完成构建、原policy和两次父本逆向身份核对；实际Lean/fullgate/性能保持NOT_RUN。

新6个声明仅置于Submission.R7NaNReplay，另换其replayEarly运行入口及等价证明。该namespace之外231898字节完全相同；原scalar、R7SinglePassSum全部声明及已有815修复、普通nativeBMM循环、DirectSmall、Packed10、Nat/USize和许可原样保留。完整逆变换恢复精确41。现存两处运行调用点分别是NativeFinal.dot与Packed10.finish的NaN拒绝分支，覆盖direct和packed回退；正常端点不进入新loop。

精确数学连接如下：

1. 若本次native乘加结果非NaN，父本NotNaNProbe反推acc和乘积、两个原参数均非NaN；R7Native加乘桥及roundtrip把native新累积值等同原Submission.add(mul)。
2. 首次native NaN事件的原字修复，由已存在且随41编译的R7W05.repairDotStep_isQNaN给quiet结论；转成原execQuietGuard后用replayFold_absorb证明整个后缀不再改变结果。没有假设后缀不可达，也不遗漏未来sNaN：dot中的乘法先quiet，原父证明覆盖此点。
3. Nat归纳以congrArg运输fold的累积值后接Eq.trans，不沿用815已经暴露的单边rewrite错误。原定点乘法后加法顺序不变，没有FMA、重排或容差。

原a9草稿没有被当作Lean接受；本次新增连接仍要完整编译。第一可证伪点是r9_repairQuiet中Model.isQNaN→execQuietGuard的真实类型匹配、r9_nativeStep_eq具体运算桥及递归等式终止证明。若statement失败先保留完整输出并只修精确证明目标，不改官方义务。

## D的最小运行方式与停用条件

可冻结此单一精确源与原41，按当前4b7/public-v2原完整gate在同runner对照，关闭observer，保留原四spec、重放、公理、所有checksum和25轮。只有完整收益可信才用未参与选择的新seed/runner确认。原gate已先做statement，不另堆积多个相似草稿。

若冷路在第一事件过早发生，增加的native测试及一次重复计算可能不划算；若subnormal热循环占主导，此稿不会解决它。比较完整BMM各cell与未改scalar/sum控制，不能只拿事件前4505步或完整specials cell曝光宣布成功。未测的净收益保持UNKNOWN；旧共享扫描/布局负面记录不因此作废。

本轮起止12:57:52—13:57:52 UTC；首JSON检查点13:06:50。R未操作Git、CI、网页、其他会话或新agent，也未安装/运行本地大型Linux工具链。D是唯一验证协调者。
