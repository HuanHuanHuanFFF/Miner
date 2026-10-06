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
| A | 37515419910 | be00e57 | 六种 CPU/内联消融、四种受限散文前瞻，三个对照；screen 已取得，refine 已取得，gate 待收集 |
| B | 37517466397 | 61d8f2e | 五种 CPU 源码变换、三种散文短远距成本拒绝；444 个有限等价用例，screen 已取得 |
| C | 37520076712 | ba1f8d5 | 精准前瞻两项、通用分块/成本规划两项；增加 fast3 同字节重复对照和 token/block 画像；待结果 |

各批输入与 SHA 在 `evidence/round4/batch-*.json`，阶段回执保存到 `evidence/round4/<run-id>/<phase>/`。artifact 的原始 state 不覆盖改写，派生分析另存。

## 已得到的观察

**VERIFIED（A 初筛）**：六种 CPU 候选在公共集的 token/DEFLATE 输出均与 fast3 一致。关闭 read-ahead 约慢 1.78%，强制主 `run1` 不内联约慢 4.32%。实际汇编表明后者丢失了 skip/lazy/key-mask 的常量特化：代码体积更小并不代表运行更快。

**VERIFIED（A 四块）**：`run1tai` 的时间轴约低 0.277%，`foldni` 的初筛微小收益在四块后约为零。`run1tai` 的小文本 parser 本身反而较慢；大路径的规范化指令序列相同而布局变化，不能把总轴小幅改善全部归因于小文本内联。

**VERIFIED（A 解析归因）**：四种 lazy 方案仅 prose.txt 改变 token。`lazy9-cost` 在唯一变化文件上的解析增量并不小于普通 lazy9，不能从其更好聚合均值断言 cost guard 已省查找。更多块之后它的大小轴约 36.554127%、总时间轴相对 fast3 约 +0.079%，仍需看独立 runner 和校准余量。

**VERIFIED（B 初筛）**：五种 CPU source 变换各通过 444 个有限 token/decode 等价用例；公共数据输出也一致，但初筛总时间轴均比 fast3 慢约 0.55%–1.14%。少做加载/写入可能增加依赖链或分支，不能只按源代码操作数判断。三个短远距成本拒绝方案尚未得到有用的两轴收益。

**INFERRED（后续假设）**：汇编显示 xlen16 在判断首组差异之前加载第二组字节，flush4 在待写长度零时仍可读写。基于这些观察生成了 lazy-second-load、zero-flush 和保持常量特化的 outline 变体；它们的收益和新证明仍待实测，不预填成功。

## 公开参照与规划方向

本轮从官方公开端点取得 #431、#415、#402，完整来源/时间/哈希/归属在 `references/round4-public-*/PROVENANCE.json`。#431/#415 属于 fastX/read-ahead 家族。#402 原始入口与部分子路由含精确输入长度分支，因此通用规划候选将入口直接接到 D 或 H 引擎，并用静态调用闭包排除原精确长度路由；这个检查仍需提取/gate 补充。

全域规划候选不能可靠地沿用 #402 混合入口的正式坐标作同族校准。其公共指标与参考曲线仅是探索筛选，私有集迁移仍 UNKNOWN。

## 当前未知

新候选完整 gate、跨 runner 的稳定增益、最终前沿余量与正式 admission/奖励。以各批新回执和最后选择记录为准；未作新的正式竞赛提交或钱包操作。
