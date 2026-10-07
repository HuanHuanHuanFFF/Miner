# ROUND5 — H16 完整 gate、旧候选复测与新优化并行

用户要求优先补齐两个 H16 组合的完整 gate，同时继续新优化，并用 CI 复测仍可能获奖的旧候选。沿用已授权的标准私有 GitHub Actions；仓库当前仍私有。新正式提交、钱包及资金操作不属于本轮优化工作。

## 已确认的起点

- fast3 已正式提交为 #453，完整 gate 与 admission 通过。它为同族速度候选提供实际正式锚点；最新数值以本轮冻结官方快照为准。
- `r4-hybrid-h16-small299` 和 `r4-hybrid-h16-smallc299` 上轮仅做了公共性能与 round trip，没有单独执行完整 gate。本轮先跑冻结原字节，若失败再按真实日志修复。
- 已通过的 H3R 组合的 statement 调用为 725.4 秒；889.7 秒是到公理检查结束的总验证时间。官方 900 秒逐调用限额不变。
- H/S 组合尚无正式同族锚点。#427、#299 转移只用于敏感性比较，不能套用 #453 并称为可靠预测。

## 执行与证据

分支 `codex/deflate-round5`，入口 `.github/workflows/deflate-round5.yml`。复用 `scripts/round4.py` 的原始计时和官方 gate 调用，设置 `ROUND4_SPEC_DIR=evidence/round5`；工具链、encoder、gate、pins 与超时不变。

首批为 `h16-small-gate.json`、`h16-smallc-gate.json`，分别运行在独立 runner：两个公共计时块、完整 gate、通过后的八个生成输入检查。额外保存实际提取出的 Lean 源文件，方便依据真实签名修复证明，不保存编译二进制或工具链。

收集命令：`python scripts/collect-round4.py pull RUN_ID gate --round 5`。第五轮回执与旧轮次分开，旧分析不覆写。测量仍为 28 个公共文件、每文件一次预热和 11 次正式计时，并配对官方 incumbent。

新算法线和旧候选筛选线独立推进，记录分别为 `evidence/round5/algorithm-notes.md`、`old-candidate-shortlist.json`。H16 证明审计在 `h16-proof-notes.md`。所有未返回的编译、证明、性能和正式获奖结果均为 UNKNOWN。
