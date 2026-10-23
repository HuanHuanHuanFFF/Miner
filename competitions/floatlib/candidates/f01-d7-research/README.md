# R7 十小时冲冠

窗口：2026-10-23北京时间02:22:17—12:22:17，共10小时。目标为取代现任冠军；研发与实际验收持续推进，已启动实验/CI自然完成回收。

当前保留60f74aa4的f01-d7-direct-nonnan，807发现与809冻结后独立确认均完整通过。相对上个保留d9整包耗时再降9%—14%，对公开原版加速2.84—2.94×。8eb仍保留为组件对照起点。后续按具体可实现收益与开发/证明/验证成本选路；旧十二类成绩不跨suite推算冠军差距。

- 唯一当前入口：[开发状态](../../coordination/development-status.json)。
- 研究分工与边界：[Astra交接](../../coordination/astra-handoff-r7.md)。
- D独占Git、CI、集成与采用；R负责精确非有限值数学和独立候选。
- 02:45 UTC冻结主要源码，03:15 UTC前派发独立确认；完整余量用于验证与证据收尾。

准备、等待、修复和复测均计入10小时。没有正式提交或资金操作授权；公共完整gate不冒充新冠军。

## 当前检查点

| 路线 | 精确源码与证据 | 结果与下一步 |
|---|---|---|
| 短内积/窄输出直接点积 | d9a80847；802/804及806/807/809 | 全部完整PASS；802发现、804冻结确认整包耗时0.80086—0.87572父本 |
| 四列/八列打包 | 原稿801、proof1在804失败；96131686/e40ccec9在809完整PASS | 实际整包耗时为d9的1.156/1.176，BMM1.457/1.506；停放，不继续加变体 |
| Inf终点免重算 | bb199701桥803仅编译；c7605688实际805/807/809完整PASS | 包括Inf终点，NaN精确回放；单组件与direct组合分列，不相加收益 |
| direct＋nonNaN当前保留 | 60f74aa4；807/809完整PASS | 新seed/新runner确认整包耗时为d9的0.90701/0.86176，BMM0.80736/0.77086 |
| quiet-NaN点积后缀 | 9a2a05cd；806/808完整PASS | 相对8eb整包0.80671/0.87944；raw位guard7ac在808更慢，暂不采用 |
| 两种非有限值组合、自比较guard | b169在808只有一处证明失败；修复0e8bc05c/1f4d31aa | 固定Lean原四spec证明有精确0e8成功证据；810现行静态规则PASS，完整gate等待公开推送授权 |
| 原生前缀、sum后缀、单项内积、标量特殊分支 | 810八个statement探针 | 精确候选已冻结，原失败保留；尚未编译/计时，不列为完整成果 |
| 原始NaN感知单遍sum | 3d9b1ea9；W12/W12b原件与新循环独立审查 | 复用原decoder分支；首次rawNaN才精确修复，随后只扫所需尾部。静态policy PASS，新循环Lean/fullgate/收益NOT_RUN |
| 直接点积与单遍sum组合 | [cc06a47f](../f01-d7-direct-singlepass/README.md)，232363字节 | 同0e8父本的97f/3d9机械组合，逆变换恢复3d9；静态policy PASS，精确新Lean/fullgate/收益NOT_RUN |
| 原始位特殊值冷路 | 939dbf31；仅替换既有finite守卫失败分支，独立逆变换和条件审查通过 | NaN优先级、Inf/zero/invalid直接word处理；普通路径不改。新Lean/fullgate/C/收益NOT_RUN |
| 低normal求和解码 | 353d9816；独立c760父本，只改真实decode，独立审查通过 | E1..23原始数学及公共片段通过；807命中cell整包曝光上限2.405%，不等于可回收时间。新USize整合Lean/fullgate/C/收益NOT_RUN |
| 矩阵NaN冷路扫描 | 4792e967；W12像闭包＋实际Nat loop | 两处dot/finish同形；原703作用域缺口及字节已冻结。静态policy PASS，新Nat接线与完整成本NOT_RUN |
| 单项内积负零归一化 | 47d429fe；a132最小seed证明、原53d成本对照 | 非NaN产品沿原生路径，NaN才精确修复；n!=1不改。静态policy PASS，新Lean/fullgate/收益NOT_RUN |
| 完整调用阶段成本 | [实际C缺失返回诊断](profile-review.md)、[修复模块](profile-current.py) | 805辅助编译选择失败已修复；807实际四份binary/137次调用逐一核对通过，见[诊断及投入决定](profile-summary.json) |

所有逐项数据从[精确新suite结果](public-suite-results.json)进入；失败、慢样本和原件保持原字节。00:30UTC官方再次核对冠军279，比较基准同步更新；原始响应由[current-official-snapshot.json](current-official-snapshot.json)定位，四运算看板见根dashboard.md。官方API现明确给279的倍率6.80117×、基准scoring-v2-2026-10；官方按hash链并在换suite时用实测anchor重启，不再用旧“跨suite历史链”说明。它不是我方public-v2直接差距。原CI均已自然结束并回收，研究窗口继续。

## 下一验证顺序

[投入依据](opportunity-ledger.json)绑定当前60f两轮逐cell时间与807实际命中，UNKNOWN收益只做最小探针；cell曝光上限不当作可回收时间。810为proof2三份完整gate和八份statement，其中canonical探针已按实际位宽失败换为ec36。等具体公开推送授权，目前没有CI排队。新运行接线先做精确statement；后续只有实际通过者进入完整成本和冻结确认，不扩近邻网格。分块检查点保留数学并停放运行，普通乘法热入口的noinline方向也没有新的机器码成本依据。

[标量实际C审查](scalar-codegen-review.md)、[344项实际输出校验](scalar-opportunity-807.json)、[新桥独立静态审查](nan-probe-review.md)和[研究原件独立完整性](web-delivery-integrity.json)仅提供各自范围的证据；新增源码编译/完整gate仍待真实执行。

原版gate的可选[实际对象采集](capture-codegen-notes.md)已通过六组本地基础行为自测，仅供discovery；810的0e8/1f4按需启用，任何冻结独立确认整批禁用。实际Linux/Lean工具及完整集成仍NOT_RUN。

新增本地路线：`4a30c99f`为NaN-only对照，`939dbf31`实际接入既有exceptional-word语义；两者普通路径不变、精确新Lean/性能NOT_RUN。[807前沿复核](word-route-frontier-review.md)扣除97f quiet-stop与3d9单遍sum已减少的完整回放，剩18519coldcalls=10053NaN+8466无NaN特殊调用；不是已编译组合或时间份额。旧26.37%整cell曝光及旧完整回放数不再当后续残余机会。`97f77e2c`实际direct组合也尚未完整编译，不替换当前60f。

[当前数学储备](math-reserve-index.md)现为25组专项交付、14项结论、773份鲜核来源/日志；[公共宿主复核](canonical-public-host-review.json)核W12c五次实际编译源码/退出码、原四spec与41项公理报告。公共片段接受不能继承给4792/3d9/47d/939/353d的新运行接线。[低解码成本边界](low-normal-cost-screen.json)另将命中与整cell曝光分开。25组ZIP原件完整性已逐字节通过，ZIP与全部负面原件保留。

[公开强起点及倍率复查](public-source-refresh-20261023T005839Z/README.md)未找到可复用新冠军源码；官方私有基准乘数的来源、hash链和实测anchor按新源码核实，旧跨suite说明已修正。

[独立公开实现补查](public-source-search-20261023T0227Z/receipt.json)另保存9个GitHub仓库/代码搜索的精确工具响应；返回范围没有新可用竞赛实现，索引范围不当作全网不存在的证明。

[单文件大小预检](source-budget-notes.md)已完成8组回归及来源保留缺陷修复；3d9预备副本210754字节，原230650字节不变。新字节尚未Lean/fullgate验收，不当作新的运行提升。

[严格公共同源补验](strict-public-settings-review.json)已核主/诊断两次显式关闭autoImplicit、实际exit0及80项原公理；这只关闭公共数学宿主的设置缺项，新私有候选完整gate/计时仍NOT_RUN。

[运行源码冻结](source-freeze.json)于02:45:52 UTC记录190份候选和12个验证入口的精确字节；研究窗口继续至04:22:17。cc06机械组合的[另次审查](direct-singlepass-review.md)已完成，当前无运行CI，810仍未派发。
