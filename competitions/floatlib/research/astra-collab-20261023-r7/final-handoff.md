# R7研究最终交接

本轮十小时窗口：2026-10-22 18:22:17—2026-10-23 04:22:17 UTC（北京时间02:22—12:22）。实际结束记录：2026-10-23T04:22:35.000Z。窗口已结束，冠军目标 **UNACHIEVED**；本地成果完成交接，不等于新候选已经通过完整验收。

## 交付入口

- [research-status.json](research-status.json)：R唯一当前状态，含实际结束时间、未测项和开发端接收回执。
- [final-handoff.json](final-handoff.json)：最终精确文件清单及冻结后完整性核对。
- [web-deliveries.json](web-deliveries.json)：**25组网页原始ZIP/报告，共50个主文件，均在E:\Download**；每份保留原SHA、回收时间和本地提取目录。
- [runtime-source-freeze.json](runtime-source-freeze.json)：02:45:20冻结的7份R候选。原Kernel、candidate manifest和原始失败回执未改写。
- [frozen-validation-triage.md](frozen-validation-triage.md)：恢复验证时的最小顺序，D已于03:22:46逐字节复制并记录采纳，原810未修改或派发。

网页工作使用两个并行GPT 6 Pro会话，本地数学、候选和证据核验同步推进。全部网页作业已完成并回收，没有留下待下载或未返回任务。W11大包经15个小分片还原原ZIP；W14c报告从原ZIP提取并核对页面原哈希，具体回收差异保留在原回执。不能把补充编译和重复回收计为新的独立数学成果。

## 得到的实质成果

1. **原字NaN与有序求和/点积数学。** W01—W03落实真实乘法quiet、dot后缀吸收及sum后续sNaN更新规则；W05/W12建立实际native规范像的加乘/分类桥和有序闭包，保留NaN sign/payload优先级。任意原始NaN不能从native值恢复，原始sNaN与qNaN的区别没有抹掉。
2. **单遍sum候选3d9。** 原序USize native前缀、首个原字NaN一次精确add、随后只扫描会改变结果的sNaN；大长度走Nat回退。它避免原方案再次重扫前缀。有限模型和公开checksum已筛查，精确新Kernel的编译、重放、完整gate和净收益仍未运行。
3. **低normal精确解码候选353d。** e=1..23的放大再缩回数学和全UInt32 wrapper等价已经有实际公共Lean证明。复用既有scaleTable[118]的公开原型在实际clang对象中消除了指定热路径的once检查与FP栈往返；不是整模块完全无once，也没有该对象计时。新候选的实际USize接线仍未完整验收。
4. **Lean设置和代码生成证据。** W13d对同一公共e8fb宿主及4db诊断显式关闭autoImplicit/relaxedAutoImplicit，真实双exit0、80项允许公理审查通过。它没有包含私有3d9/353d新循环接线。W11确认实际scalar闭包/boxed边界，UInt32是立即数而非每结果堆分配；W15核对固定库的三个实际转换/分类原语。静态代码字节和调用消除不自动等于提速。

## 已验组件与待验候选

R的c760 nonNaN组件已有805/807完整公共验证；9a2 quiet-NaN组件已有806/808完整公共验证。D当前保留60f direct+nonnan，807及冻结新runner809完整通过。公开shipped参照收益不能换算为当前私有scoring-v2冠军优势。

| 精确R源前缀 | 内容 | 当前边界 |
|---|---|---|
| 0e8bc05c | nonfinite-combined-proof2 | 网页精确完整源码普通编译、原四spec与三公理通过；原完整gate未跑 |
| 1f4d31aa | self-nonnan-guard-proof2 | 新组合未编译/未计时 |
| a9e546b6 | native-repair-proof2 | dot native前缀/NaN修复新集成未编译 |
| 0fe7884f | sum-native-repair-proof2 | 第二前缀方案未编译，与3d9重叠 |
| ec36b4da | canonical-bridge-probe-policy2 | 修复实际位宽表达式问题；精确探针未编译，无运行收益声明 |
| 3d9b1ea9 | sum-singlepass-fused-proof1 | 单遍sum新全候选未编译/未计时 |
| 353d9816 | low-normal-sum-decode | 独立c760 decoder候选；新全候选未编译/未计时 |

完整SHA/路径/字节见最终JSON。D另外准备cc06 direct-singlepass（232363B），只在3d9中换入97f完整BMM尾；R与D分别逆变换恢复3d9。DirectSmall正文与60f相同但其依赖冷路不同，新组合仍NOT_RUN，不能继承完整接受或相乘两条路线收益。

## 开发端下一步

D已采纳：同一runner先60f控制，再cc06，均按固定原gate完成四义务、重放、公理、checksum、所有case及25配对轮；关闭observer。发现有价值结果后，保持同一源码，换新runner/未用seed独立确认。父97f/3d9只按真实第一失败定位，不无条件重复预编译。

d027结果守卫与e139低指数零是独立statement第一/第二优先，可在授权、第二验证槽与剩余预算充足时另跑。939特殊值原字路线和353d低normal作为后续项。整op/cell曝光不等于可回收时间；不同gate对shipped的配对轮不能伪装成cc06对60f的直接配对试验。

3d9绕过旧NativeDecodeSum.decode，不能把353d旧hook直接拼上去就声称新sum用了低normal优化。D只读容量研究还发现宽namespace拼接会误删40743B实际证明依赖而仍满足大小上限；此反例已保留。没有写新组合源码，不能仅据sizePASS认定可用。

## 预算、等待与未完成事项

- 主要运行源码02:45:20冻结；之后做证据、原包核验和有边界的验收顺序复核。03:02:31—03:16:23的顺序复核耗时13.87分钟，计入原十小时。
- 公开push授权问题约从22:51 UTC起等待，到窗口截止约**5小时31分钟**。这段与数学证明、网页回收和本地研究重叠，**不是5小时31分钟纯空闲**。
- 冻结至截止约**1小时37分钟**用于收束、复核和待命；03:25:18起是最终交接及响应新输入阶段。纯空闲总时长未单独测量，保留UNKNOWN。
- 03:15独立确认启动节点已错过，实际记录为未达；未延长04:22:17原截止。9组既有CI已由D收齐；本地新候选没有新完整gate/性能结果。
- 自动审批拒绝了向具体公开仓库推送新材料，原因是缺少明确公开目的地和上传内容授权。D已经提出人类确认问题，最终仍以其实际授权/CI状态为准。R没有绕过该限制上传私有候选。
- 没有正式竞赛提交、注册、签名或资金动作。最终保留60f；冠军目标未达成。后续研究/新验证应从这些精确缺项接续，不能把本轮窗口完成写成项目达标。

