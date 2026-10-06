# ROUND2 — 吸收研究与浅层搜索优化

日期：2026-10-06（北京时间）。用户要求吸收研究文档并继续尝试更好的版本；延续首轮参照实验，工具链仍只在临时 GitHub runner。正式竞赛提交、钱包和资金操作不在本轮执行范围。第二轮开始时实时核对仓库已私有，CI 运行须另确认额度授权，见 ENVIRONMENT。

## 研究吸收

输入为用户提供的《Conjectures.io / Bittensor SN66 DEFLATE 压缩竞赛深度研究：从 probe2 到可支付 Pareto 前沿》。原文是研究材料，不是新的操作授权；原文件保持本地，不公开上传。哈希和对照记录见 `evidence/round2/research-receipt.json`。

- **VERIFIED**：仓库首轮原始测量支持 `probe2` 大小改善 −0.300287 个百分点；约 1% 额外时间属于历史公共 stage1 观察。细小时间变化需要更多顺序块，不能从比总秒数替代官方 equal-file 指标。
- **VERIFIED（源码机制）**：libdeflate 的 [ht_matchfinder](https://github.com/ebiggers/libdeflate/blob/master/lib/ht_matchfinder.h) 使用两槽 inline bucket；其原生 unaligned load、指针与 SIMD 实现没有直接移植。本轮只借用数据结构思想，保留比赛所需安全 Rust。
- **VERIFIED（本项目源码）**：#261/probe2 的大输入文本路径使用 32768-position 环形链；小输入可以使用 16384-position 表。小表会在完整 DEFLATE 窗口内覆盖链，所以改桶未必能复现 token。首版只在 `input.len() > SMALL` 且 `cls ∈ {1,5,6}` 接管，其他路径保留 `probe2`。
- **INFERRED**：完整窗口的大输入路径，在单调插入和相同 lazy/skip/tail 时机下，两槽捕获的最近候选可能与原链的前两节点一致。距离恰为 32768 时的环形覆盖会改变链尾，但更早节点已超窗口；这是机制解释，不是全输入等价性证明。
- **UNKNOWN**：文档的 opaque citation ID 不能在本仓库重放；文中 snapshot 22742、排名和奖励份额属于报告中的历史断言，本轮没有据此判断实时状态。仍保留线上部署对应、私有 stage2、许可条款和外部泛化缺口。

采用顺序：有限等价性 → 官方提取/Lean/axioms/gate → 未插桩 paired benchmark → 对照分析。先研究浅层候选价值，再决定是否扩大 cost-aware planner。完整 DP、继续扩表、额外内容分类暂缓。

## 候选及证伪条件

所有修改位于 `candidates/`；参照来源见 [PROVENANCE](references/submission-261/PROVENANCE.md)。官方 gate、encoder、contract、pins 和阅读用源码副本不改。

| 候选 | 相对 probe2 | 本轮假设 |
|---|---|---|
| `bucket2` | 大文本两张 hash-keyed recent-position 表；捕获两候选后旋转，使用单元素虚拟链复用 verified `find/walk` | token/DEFLATE 输出保持一致，减少 position-indexed pointer chase |
| `probe3` | T/P/S 搜索深度 2→3 | 第三候选仍可能有压缩收益；额外时间是否值得待测 |
| `probe2-nice16` | NICE 32→16 | 达到较短好匹配就停止，可能保留大部分压缩收益并节省时间 |
| `probe2-nice64` | NICE 32→64 | 32–63 字节匹配后继续搜索是否仍有价值 |

NICE 两变体会影响所有 regular engine 类别，tiny planner 的 TF_NICE 保持原样；它们是全局停止门槛消融，不能误称为仅文本的 adaptive gate。未根据 stage1 调参选择门槛；这两个预先指定值用于归因与边界对照。候选由 `python scripts/make-round2.py` 重建。

bucket2 新证明复用原 `find/walk`、字节匹配及 decode 层，另为 bucket insertion 和复制的 engine loops 提供证明。保存的 Parse.lean 在官方重新提取和检查前仅是候选源码。

## 验证入口与证据边界

[DEFLATE round 2](https://github.com/HuanHuanHuanFFF/Miner/actions/workflows/deflate-round2.yml) 在 `codex/deflate-round2` 分支运行，复用 [ENVIRONMENT](ENVIRONMENT.md) 的固定官方 revision 和临时 Linux 环境。

1. `scripts/research-round2.py` 对全部 stage1 和预定合成输入逐 token 比较；合成输入覆盖小/大路由边界、16/32 KB 相邻距离、零、binary、重复文本、扰动文本、数字结构，并另强制 structured engine 测试。有限 token decode 检查不是 Lean 或完整 DEFLATE round trip。
2. 同脚本生成仅 runner 存在的诊断版，按第一候选长度记录第二访问和第二候选被选中的次数。诊断版 token 必须与 probe2 一致。它不参与官方 gate 或 timing；“被选中”不等于最终 emitted token 改变，backward/lazy 归因及 oracle 上界仍未知。
3. `scripts/ci-round2.sh` 对四候选执行官方完整 gate，保存重新提取、Lean obligation、公理和公共 round trip 结果。一个候选拒绝不会丢弃其他结果，但最终 job 要求全部接受。
4. `scripts/round2.py` 只测 gate 接受的候选，保留 template/#261/probe2；每文件 1 warmup + 11 measured，共四个交错顺序块。同一 CPU、官方 paired incumbent，保留每 repetition 原始结果和输出/token hashes。bucket2 要求与 probe2 的两种 hashes 都一致。

这些是公共 stage1 结果；外部 source-held-out、私有 stage2、线上 admission/排名及实际奖励分别保持 UNKNOWN。四块也不足以自动消除 CI 主机漂移；报告每块和文件分布，不凭一个平均数宣称可靠速度优势。

## 当前状态

**VERIFIED**：[CI 37447673754](https://github.com/HuanHuanHuanFFF/Miner/actions/runs/37447673754)，提交 `ce3e5be14710d95dea42d178782697a55e7915ba`：bucket2 完成 496 个有限 token-equivalence/decode 用例（含全部公共 28 文件）；诊断版保持 probe2 token 流。bucket2 重新提取成功，但 `Bucket2.find_spec` 在 tuple 参数展开处存在一个未解决目标，未通过 Lean statement。其余三个常量变体完成完整 gate，`accepted=true`，公理仍仅三项白名单。

**VERIFIED**：regular walk 的第二候选访问 1,332,720 次、被选中 171,566 次（约 12.87%）；这是查找层的选择，不能推断最终 emitted-token 的 oracle 价值。原始 trace 已保存。

首轮第二轮运行的测量入口因拒绝候选没有评分 JSON 而中止，因此没有四块性能结论。已修正 tuple 展开和失败回执处理。修复后的复测只重新验证 bucket2；三个未改变的候选使用 [hash-bound proof receipts](evidence/round2/accepted-control-proofs.json)，CI 必须核对 parse.rs/Parse.lean SHA256 和固定官方 revision，然后在新 runner 重新测全部版本。这样复用已验证证明而不复用旧计时。原始失败和成功证据保存于 `evidence/round2/37447673754/`。

初次自动 push 因仓库私有而跳过；用户随后明确授权运行私有 CI、继续实测。仍不把未完成验证和性能测量的桶版写成优化成功。
