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

## 后续并行批次与收集

- `old-speed-replication-a`：五个已通过 gate 的旧候选，与 fast3/#453 和同字节 shadow 对照，四个计时块；CPU 两项另做同进程顺逆序诊断。Run `37582344420`。
- `new-mechanisms-a`：小输入双 parser 按完整编码成本择优、299 A 迭代保留较佳完整路径。先提取和成本差分，再公共测量及有限输入 round trip；复制证明明确为 NOT_ADAPTED，不执行完整 gate，不具有提交资格。Run `37582348267`。
- 两批源提交均为 `b94837db0ccb2ae5a8a4c3d36cd9a718b8fb50aa`。所有已知 run 对应关系保存在 `evidence/round5/run-ledger.json`。
- 矩阵回执用 `python scripts/collect-round4.py pull RUN_ID PHASE --round 5 --batch BATCH`。新算法可先取 `extraction` 阶段；旧的两个手动 H16 run 不带 `--batch`。
- 远端并发增加的 push 自动 H16 矩阵已合并保留；与本地重复的 token profile 配置修复统一调用相同白名单路径函数。本次合并多触发的一组冗余 H16（37582343768）已请求取消，原始 gate、远端复测及新旧候选批次继续。
- 首两个 H16 run 使用早期提交，辅助 profile/interleaved 尚未读到 round5 目录；这两项诊断的失败不影响通过独立配置入口运行的官方公共 benchmark 与 gate。后续批次已修复。

## 首轮完整 gate 结果（2026-10-07 UTC）

- VERIFIED：H16-smallC，run 37580365335，官方提取、statement、公理检查、公共 round trip 全通过；Parse 调用557.5s，保持900s官方限时。八个固定生成输入的两块检查通过。公共正式两轴由10个配对进程重算，候选为6.690710 / 33.8608788%。
- VERIFIED：H16-small，run 37580297956，提取通过，statement在900s超时；没有官方评分JSON，回执明确为拒绝。公共性能两轴7.268855 / 33.8632138%不代表gate通过。
- 两个候选的#299校准均未进入25678快照前沿；#427转移的有利结果仅为另一种敏感性情景，不足以宣称可领奖。下一步在独立候选中仅优化small的证明开销。
