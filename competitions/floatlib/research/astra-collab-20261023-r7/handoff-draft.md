# R7研究交接草稿

窗口仍在进行，最终状态以[research-status.json](research-status.json)为准。共同窗口：2026-10-22 18:22:17—2026-10-23 04:22:17 UTC；02:45运行源码冻结，03:15最终独立确认目标。原目标“取代评测时现任冠军且达到约定优势”尚未达成。

R已于02:45:20 UTC完成7份精确运行源码冻结，见[runtime-source-freeze.json](runtime-source-freeze.json)。记录未改变文件或设文件锁；后续若有验证导致的修复，须新增精确回执，不能沿用旧冻结哈希。

## 开发端当前可取的材料

- [handoff-materials-preview.json](handoff-materials-preview.json)：7份当前待验源码的完整路径/SHA/字节、各manifest身份及25组网页原ZIP/报告。
- [web-deliveries.json](web-deliveries.json)：E:\Download的50个主文件与本地完整提取目录。原始失败、慢样本、超时及回收方式均保留；W11的110MB原始文本在本地忽略目录及同哈希E盘ZIP中，精选证据另在reviewed-evidence。
- [ready-policy-precheck-current.json](ready-policy-precheck-current.json)：7份精确源的单文件大小、导入、原禁词/options/attributes静态检查。不是Lean或完整gate。

## 已有完整验证与新接线分开

c760 nonNaN运行组件已有805/807完整公共验证及809回执；9a2 quiet-NaN后缀组件已有806/808完整公共验证。当前D保留60f direct+nonnan包，807和冻结新runner809完整通过。它们对公开shipped参照的结果不等于对现任冠军或私有scoring-v2的比较。

| 当前源 | 验证状态/用途 |
|---|---|
| 0e8bc05c combined-proof2 | 网页精确完整源码普通编译、原四spec及三公理通过；正式完整gate未运行 |
| 1f4d31aa self-nonnan-guard-proof2 | 终点自比较守卫；新精确组合未编译/未计时 |
| a9e546b6 native-repair-proof2 | dot第二native前缀与首NaN精确修复；未编译/未计时 |
| 0fe7884f sum-native-repair-proof2 | sum第二native前缀与quiet后缀；未编译/未计时，与单遍方案重叠 |
| ec36b4da canonical-bridge-probe-policy2 | 位宽表达式修复后的数学探针；精确候选未编译，无运行收益声明 |
| 3d9b1ea9 sum-singlepass-fused-proof1 | 原序USize单遍、首rawNaN一次精确add、后续只扫sNaN；新全候选未编译/未计时 |
| 353d9816 low-normal-sum-decode | 以c760为独立对照，仅替换sum decoder；新全候选未编译/未计时 |

完整哈希以manifest为准，旧失败/修复稿不覆盖。R无Git/CI操作权限，D统一选择队列、提交、推送与验证；公开push既有具体授权问题仍待人类回复。正式提交、签名、注册与资金不在本轮范围。

D另有唯一机械组合`f01-d7-direct-singlepass`，cc06a47faf9f982c324d265c90beb2b9cea953f33773eabed3ed6eab29260dfc，232363bytes。R只读核对实际字节等于3d9中原815bytes BMM尾段换成97f的2528bytes尾段，逆变换恢复3d9；sum/scalar整段保留。DirectSmall正文虽与60f相同，其NativeFinal.dot冷路继承0e8/97f，完整路径不继承60f接受/性能；新组合Lean/fullgate/C/计时均NOT_RUN。该稿由D拥有，不计入R的7份冻结列表。

## 最重要的数学与代码生成资产

W01—W03关闭真实乘法不产sNaN、dot quiet吸收、sum后续sNaN替换的原字语义。W05/W12关闭原生规范像的真实加乘/分类及完整原字闭包，允许中途invalid产生canonical NaN；原始任意NaN载荷不能从native值恢复。W12c给最小闭包在公开60f宿主中的实际编译和原四spec核对。

W13证明e=1..23低normal精确放大32指数再缩回，W13b证明全UInt32 wrapper等于原decoder。W14旧常量版本仍有once和acc spill；W14b复用原scaleTable[118]后，指定低normal原型路径的once状态检查和FP栈往返消失。W14c在官方maxRecDepth8192内实际复编译。W13c组合公共数学宿主通过；W13d对精确e8fb主源及4db诊断显式关闭autoImplicit/relaxedAutoImplicit，双exit0、80声明三公理通过。环境路径重新定位、旧olean缓存不能整体字节比对的边界见原回执。

这些公共宿主没有本地353d的USize接线或3d9新循环；不继承为本地候选接受。W14/W14b对象未计时，消除call/spill不等于净提速。D对低normal命中整cell的当前曝光上限为60f整包2.405%/c760整包2.081%，仍不是可回收时间，保持备选优先级。

W11确认实际MainFull scalar闭包/boxed调用边界；UInt32在ELF64中是立即数编码，不能说每输出堆分配。W15核实际随附库中of_bits/to_bits/isnan为31/16/7bytes叶函数；没有caller、缓存和替代算术的动态成本结论。807保存的诊断C/asm实际绑定8eb重放，不能当作60f已清理的计时对象。

## 组合与后续验证

3d9绕过旧NativeDecodeSum.decode，因此不能直接叠上353d旧hook期待低normal进入新sum。未来组合需在新循环中真实接线、证明并完整验证，收益不相加。源码上限的加法规划和词法依赖筛查见source-budget-inventory.json；D已有保留license和代码物理行的注释打包预检，新打包源仍需验证。R未生成新的组合或精简运行候选。

若公开授权到达，优先按D既有计划用原版4b7/public-v2跑精确源，保留原四spec、重放/公理、所有case及25配对轮。性能必须乘cell_work并保留控制项、慢样本和失败；冻结后用新runner/seed独立确认。若授权未到，保持NOT_RUN，按原窗口交付准备成果，不绕过审批。

03:16补充的[frozen-validation-triage.md](frozen-validation-triage.md)提供更小的可选验收顺序：60f控制与cc06完整gate，父组件按真实失败定位；d027/e139列为独立statement优先。该建议尚由D决定，不改冻结810或自动派发。03:15独立确认节点未见启动证据，不能标达成；完整期限04:22:17不变。

03:22:46 D已将上述MD/JSON逐字节接入其交接材料并记录采纳，R复核两份副本与原哈希一致。见candidates/f01-d7-research/validation-order-review-receipt.json；这是顺序建议的接收/采纳，不是公开发布或CI已运行，原810仍未改/未派发。
