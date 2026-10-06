# ROUND4 — 五小时优化窗口

用户授权继续尝试 CPU、匹配成本、局部预算与有限规划等方向，目标是找到可上榜候选。
开始 `2026-10-06 18:44:59 UTC`，研究截止 `23:44:59 UTC`，即北京时间 10 月 7 日 02:44:59–07:44:59。环境仍为标准临时 GitHub runner；仓库已实时核对为私有，沿用用户的私有 CI 授权。注册、钱包、资金和正式提交另按具体授权处理。

基线是上一轮已通过完整公共 gate 的 `r3-432-fast3`，源 SHA256 `bae8014121e4710f4a34ce63452578b4bf69121b4f695e1b1356780a019108ef`，proof `e2c200cf084eca95eb70d26c0efb04e70d88f015315610d2a54d20b6adb7cf04`。之前仅一台 runner 四块、有窄的校准前沿余量，不是正式 admission 或奖励证据。

## 本轮入口和证据边界

`scripts/round4.py` 分为 preflight / screen / refine / gate。每个 source/proof pair 在安装工具链前检查哈希，官方源码与 pins 保持原样。公共测量仍为 paired incumbent、28 文件、1 warmup + 11 measured，并按文件等权的中位总压缩时间比计算。

每个阶段完成后上传短期研究回执（保留一天），只含 JSON/JSONL、候选两文件、日志与汇编文本，不含工具链或编译二进制。这样主线程能在 gate 继续运行时分析 screen/refine 结果。`collect-round4.py` 下载后从每条原始 repetition 独立重算，已用上一轮 16 个进程回放检查。

CPU 候选另做有限 token/decode 等价检查；它不是全输入等价证明。源码上的少读、少分支或少内联不等于 CPU 收益。第一台 runner 的 `perf` 被 `perf_event_paranoid=4` 拒绝，目前只有汇编与配对时间证据，不能声称已测 cache miss 或 branch miss。

官方前沿起点为 snapshot 24227，完整分页在 `evidence/round4/initial-frontier/`。439 项、71 个前沿点；快端 #436 为 `(0.436193913, 37.0704342%)`，#433 为 `(0.440208895, 36.6039562%)`。这些是冻结时点，完成前须重新核对。

## 实验批次

| 批次 | CI | 固定提交 | 范围 |
|---|---|---|---|
| A | 37515419910 | be00e57 | success；40 个公共测量进程；run1tai、foldni 两个新完整 gate 通过；附加生成输入通过 |
| B | 37517466397 | 61d8f2e | 实验 job failure；36 个公共测量进程有效，两个短远距成本拒绝候选在 Lean 被拒绝；其性能无优势，不修复该路线 |
| C | 37520076712 | ba1f8d5 | success；28 个公共测量进程；lazy4far 新 gate 与附加生成输入通过；最初 token 画像编译失败，不作为数据 |
| D | 37522012041 | 44a655c | success；32 个公共测量进程；flushzero 与 run1tai gate 通过；CPU 小收益没有独立复现 |
| E | 37523141792 | 33c57dd | failure；32 个公共测量进程有效；完整 H 旧证明 statement 达 900 秒上限，symbol-block512 旧证明未适配新条件 |
| F | 37524045017 | 71c874c | failure；34 个公共测量进程；halfpass gate 通过，directemit 两处算术证明未通过；测量未发现稳定 CPU 增益 |
| G | 37526862387 | c9f3545 | 保存全部 34 个测量后取消重复的完整 H 验证；livehuff 更差，后由 I 验证精简 H 核心 |
| H | 37529887857 | 11429ab | 保存全部 44 个测量及同进程正反序诊断后取消；wrap 证明失败，CPU 小收益随顺序反转 |
| I | 37532140321 | 232a978 | success；12 个测量；H8 核心对完整父版本 444 个有限用例 token/decode 一致；完整 gate 与生成输入通过 |
| J | 37535056448 | 7ca68c0 | success；42 个测量；H16d64 与 tinydepth32 gate 通过，大小收益已接近饱和 |
| K | 37537479001 | 91c8136 | success；44 个测量；sampleguard 和 mode1/i8 的完整 gate 与附加生成输入通过 |
| L | 37539732787 | edf8897 | failure；20 个测量有效；EOB 修正输出略差，statement 在新增数组写回后的状态展开处失败；停止该支线 |
| M | 37541614789 | 0f157bd | success；16 个测量；mode3/i8 大小最优且完整 gate、生成输入通过；校准后仍差 0.004603 pp |
| N | 37542714311 | 4e22f24 | research workflow success；10 个测量，RMQ 444 个用例等价，但时间轴恶化约 133.55%；旧证明 NOT_ADAPTED，没有候选 gate，通过 job 不代表 proof 通过 |
| O | 37544346810 | 5d8fa14 | 最后三个通用 S/H 组合；小输入阈值与原 #299 内容分类复用，等待性能和选中的完整 gate |

各批输入与 SHA 在 `evidence/round4/batch-*.json`，阶段回执保存到 `evidence/round4/<run-id>/<phase>/`。artifact 的原始 state 不覆盖改写，派生分析另存。

## 已得到的观察

**VERIFIED（A 初筛）**：六种 CPU 候选在公共集的 token/DEFLATE 输出均与 fast3 一致。关闭 read-ahead 约慢 1.78%，强制主 `run1` 不内联约慢 4.32%。实际汇编表明后者丢失了 skip/lazy/key-mask 的常量特化：代码体积更小并不代表运行更快。

**VERIFIED（A 四块）**：`run1tai` 的时间轴约低 0.277%，`foldni` 的初筛微小收益在四块后约为零。`run1tai` 的小文本 parser 本身反而较慢；大路径的规范化指令序列相同而布局变化，不能把总轴小幅改善全部归因于小文本内联。

**VERIFIED（A 解析归因）**：四种 lazy 方案仅 prose.txt 改变 token。`lazy9-cost` 在唯一变化文件上的解析增量并不小于普通 lazy9，不能从其更好聚合均值断言 cost guard 已省查找。更多块之后它的大小轴约 36.554127%、总时间轴相对 fast3 约 +0.079%，仍需看独立 runner 和校准余量。

**VERIFIED（B 初筛）**：五种 CPU source 变换各通过 444 个有限 token/decode 等价用例；公共数据输出也一致，但初筛总时间轴均比 fast3 慢约 0.55%–1.14%。少做加载/写入可能增加依赖链或分支，不能只按源代码操作数判断。三个短远距成本拒绝方案尚未得到有用的两轴收益。

**VERIFIED（独立复测 D 初筛）**：同源码且同编译库 SHA 的 fast3-shadow 对照约 +0.019%；A 的 run1tai 在这台 runner 变为 +0.461%，不能宣称已复现其小幅优势。flushzero +0.331%，classoutline +3.204%，lazy9-cost +0.766%。classoutline 的汇编仍保留常量 skip/key-mask，parser 依然退化，故“丢失常量特化”不能作为所有 outline 退化的唯一解释。当前不采用这些变体。

**VERIFIED（C 四块）**：lazy4far 时间相对 fast3 +0.179%、大小轴 36.577230%；公共 gate 通过，但多加 1% 时间压力后无前沿余量。同源码 shadow 均值 -0.131%，提醒千分之几的改善需要独立复现。

**VERIFIED（压缩端探索）**：C 的统一 H2 入口公共坐标约 `(4.324145, 34.065520%)`；E 初筛 H2-deep16 为 `(4.674739, 33.974638%)`，H4 为 `(4.811351, 33.998955%)`。搜索深度和成本重估轮数分别产生可观察的大小收益。继续检查组合后的边际收益及耗时上限。它们尚无可靠同族正式校准，不能把这些公共大小直接与正式榜比较。

**VERIFIED（画像修复）**：C/D 的旧 token-profile 格式字符串少一个 JSON 转义闭括号，Rust 编译拒绝，`files=[]`。E 使用修复后脚本，`DIAGNOSTIC_OK`，84 个候选/公共文件的独立 token 解码检查完成、零失败。画像不计时，正式性能仍来自未改动的官方引擎。

**VERIFIED（B Lean 拒绝原因）**：复杂主匹配接受条件令提取器复制内层 lazy 循环为 `run1_loop0_loop1/2/3`；旧证明只注册原循环的 spec，`step*` 因而停在新调用上。日志中的 tuple 构造错误不是有效的正确性证明，也不是已找到错误输出的反例。候选未通过 gate；性能不足，停止该支线。

**INFERRED（后续假设）**：汇编显示 xlen16 在判断首组差异之前加载第二组字节，flush4 在待写长度零时仍可读写。基于这些观察生成了 lazy-second-load、zero-flush 和保持常量特化的 outline 变体；它们的收益和新证明仍待实测，不预填成功。

## 公开参照与规划方向

本轮从官方公开端点取得 #431、#415、#402，完整来源/时间/哈希/归属在 `references/round4-public-*/PROVENANCE.json`。#431/#415 属于 fastX/read-ahead 家族。#402 原始入口与部分子路由含精确输入长度分支，因此通用规划候选将入口直接接到 D 或 H 引擎，并用静态调用闭包排除原精确长度路由；这个检查仍需提取/gate 补充。

全域规划候选不能可靠地沿用 #402 混合入口的正式坐标作同族校准。其公共指标与参考曲线仅是探索筛选，私有集迁移仍 UNKNOWN。

另从官方取得 #299、#304、#398、#413 并保留来源；审计在 `evidence/round4/family-notes.md`。#299 使用通用内容采样分类、三个规划引擎与检查后发射器，本轮新增其原版对照和仅改 A 引擎预算的两个候选。#299 的 Huffman 成本模型仍区别于官方 package-merge：全部符号加一平滑、树长近似修补且忽略树头和 block 类型选择；不能称为准确编码成本。另准备仅去除 Huffman 阶段伪计数的 livehuff 假设，尚待实测。

`scripts/summarize-round4.py` 汇总每台 runner 的最新完整阶段，避免重复计算 screen/refine/gate 上传；各 runner 等权报告配对变化和范围，不将其当作官方 admission 的 bootstrap。

## 已证实的取舍

**VERIFIED（CPU）**：run1tai 在 A 平均快约 0.277%，D 反而慢 0.077%；flushzero 在 D 平均快约 0.621%，H 慢 0.211%。D 的 flushzero 最大单块改善主要来自 incumbent 变慢。同进程诊断也显示 shadow、wrap、flushzero 的小幅变化随正反运行顺序翻转。保留全部数据，不通过删除慢块制造收益。当前保留 fast3，不采用这些 CPU 变体。

**VERIFIED（H 证明）**：仅保留 H8/depth32 的可达实现和证明后，源码从 271232 字节降至 71184 字节，证明从 405932 降至 95901 字节。I 的重新提取、Lean obligation、公理检查和公共 round trip 全部通过；statement 94.9 秒、至公理检查结束约 150.2 秒。444 个有限 token/decode 用例和公共输出均与完整父版本相同。这解决的是证明验证成本，没有声称运行算法提速。

**VERIFIED（压缩收益饱和）**：H8/depth32 公共大小轴为 33.875400%；H16/depth64 为 33.874353%，只少 0.001047 pp。H16/depth32 未改善大小；PM 128→256 仅改善约 0.000090 pp。增加成本重估、树深和候选宽度已经不足以自然跨过当前前沿门槛。

**VERIFIED（#299 路线）**：原版公共大小 33.842831%；halfpass 约 33.871225%，samplemore 约 33.846773%，sampleguard 约 33.843555%。sampleguard 四块比同 runner 原版时间轴低约 13.4%，但仍增加大小。tinydepth32 输出大小与原版相同；tinypass8、livehuff 和 EOB 归一化都没有大小优势。

**VERIFIED（结构性 DP 实验）**：N 的 RMQ Rust 通过 444 个有限 token/decode 用例，公共 28 文件两个块的 token 与压缩输出均与 #299 一致。但两个块时间轴分别为 22.1193 / 22.0671，原版 9.4742 / 9.4454，相对慢 133.47% / 133.63%。停止该实现，不再投入新证明。维护 min/max 层的开销超过本次省下的逐长度扫描收益是源码与计时支持的解释，未测硬件计数器，不能声称已定位具体 cache miss 原因。

**INFERRED（最后组合假设）**：逐文件权重使小文件影响不可忽略。H16d64 相对 #299 多出的大小轴中，小于 64 KiB 的三个公共输入贡献约 0.011139 pp。O 的第一种组合只增加通用 `n < 65536` 分支；第二种再复用 #299 已有 DNA、零稀疏和高字节二进制分类，第三种把其余路径换为 M 已通过 gate 的 mode3/i8。所有原引擎函数与常量逐字保留，未加入文件名、哈希或精确输入长度查表。父版本数据组合推算保存在 `hybrid-parent-prediction.json`，不能替代新二进制实测及新组合证明。

**INFERRED（校准限制）**：#299 原版正式大小 34.102373%，用它自身的公共/正式比例校准后，上述已测衍生仍被前沿支配。只乘 #427 系数，会连已被支配的原版 #299 都误判成有几何位置，因此不能据此选择。H 没有正式同族锚点；#427 是筛选假设，#299 只能用于敏感性比较。`own_anchor` 字段对 H 使用的 #432 转移同样只是跨家族假设，不是同族证据。

## 复核入口和当前未知

`scripts/summarize-round4.py` 每台 runner 只取最新完整回执，核对原始测量、源码和 gate 输入哈希，记录上传阶段与实际完成阶段、CI 结论及 CPU 型号。`scripts/select-round4.py --snapshot <pareto-pages.json>` 用同一份官方快照复算两种校准、余量和条件几何权重；详细结果在 `evidence/round4/selection.json`。原始数据保留在各 run 的最终回执目录，未用重复的 screen/refine 把样本数放大。

完整结果以精确哈希对应的回执为准；候选 manifest 的状态是生成时快照。RMQ 仍需要实际 Rust 结果及全新证明；所有候选的私有 stage2、正式 admission、实际排名与奖励均 **UNKNOWN**。本轮未进行新的正式竞赛提交、钱包或付款操作。

回执下载中有一次可恢复超时，最终 gate 回执已覆盖同一批完整测量。早期 Python 临时目录在两个旧回执上建立了受保护 ACL；递归恢复继承的请求被自动审批拒绝，因此没有改动权限。后续下载改为继承工作区权限的新目录，旧回执通过获准的只读访问核验。该问题没有改变 CI 或测量数据。
