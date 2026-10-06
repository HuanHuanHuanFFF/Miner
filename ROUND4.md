# ROUND4 — 五小时优化窗口

用户授权继续尝试 CPU、匹配成本、局部预算与有限规划等方向，目标是找到可上榜候选。
开始 `2026-10-06 18:44:59 UTC`，研究截止 `23:44:59 UTC`，即北京时间 10 月 7 日 02:44:59–07:44:59。环境仍为标准临时 GitHub runner；仓库已实时核对为私有，沿用用户的私有 CI 授权。注册、钱包、资金和正式提交另按具体授权处理。

基线是上一轮已通过完整公共 gate 的 `r3-432-fast3`，源 SHA256 `bae8014121e4710f4a34ce63452578b4bf69121b4f695e1b1356780a019108ef`，proof `e2c200cf084eca95eb70d26c0efb04e70d88f015315610d2a54d20b6adb7cf04`。之前仅一台 runner 四块、有窄的校准前沿余量，不是正式 admission 或奖励证据。

## 本轮入口和证据边界

`scripts/round4.py` 分为 preflight / screen / refine / gate。每个 source/proof pair 在安装工具链前检查哈希，官方源码与 pins 保持原样。公共测量仍为 paired incumbent、28 文件、1 warmup + 11 measured，并按文件等权的中位总压缩时间比计算。

每个阶段完成后上传短期研究回执（保留一天），只含 JSON/JSONL、候选两文件、日志与汇编文本，不含工具链或编译二进制。这样主线程能在 gate 继续运行时分析 screen/refine 结果。`collect-round4.py` 下载后从每条原始 repetition 独立重算，已用上一轮 16 个进程回放检查。

CPU 候选另做有限 token/decode 等价检查；它不是全输入等价证明。源码上的少读、少分支或少内联不等于 CPU 收益。第一台 runner 的 `perf` 被 `perf_event_paranoid=4` 拒绝，目前只有汇编与配对时间证据，不能声称已测 cache miss 或 branch miss。

官方前沿起点为 snapshot 24227，完整分页在 `evidence/round4/initial-frontier/`。439 项、71 个前沿点；快端 #436 为 `(0.436193913, 37.0704342%)`，#433 为 `(0.440208895, 36.6039562%)`。这些是冻结时点，完成前须重新核对。

## 正在运行的批次

| 批次 | CI | 固定提交 | 范围 |
|---|---|---|---|
| A | 37515419910 | be00e57 | success；40 个公共测量进程；run1tai、foldni 两个新完整 gate 通过；附加生成输入通过 |
| B | 37517466397 | 61d8f2e | 实验 job failure；36 个公共测量进程有效，两个短远距成本拒绝候选在 Lean 被拒绝；其性能无优势，不修复该路线 |
| C | 37520076712 | ba1f8d5 | success；28 个公共测量进程；lazy4far 新 gate 与附加生成输入通过；最初 token 画像编译失败，不作为数据 |
| D | 37522012041 | 44a655c | 零长度 flush、保留常量的 outline，以及 A 两项复现；增加同字节重复对照；screen 已取得 |
| E | 37523141792 | 33c57dd | 三个符号/分块成本候选，H 规划的迭代与深度消融；screen 已取得，修复后的 token 画像有效 |
| F | 37524045017 | 71c874c | 删除已证明的重复匹配检查、32 位哈希、#299 规划预算两项及其原版对照；正在运行 |

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

## 当前未知

新候选完整 gate、跨 runner 的稳定增益、最终前沿余量与正式 admission/奖励。以各批新回执和最后选择记录为准；未作新的正式竞赛提交或钱包操作。
