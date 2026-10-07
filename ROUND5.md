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

## H16 gate 修复已验证

原版跨 runner 结果：small 为1次通过、2次900秒超时；smallC 为2次通过、1次900秒超时。失败均发生在 statement，官方重新提取已通过。三组原版结果分别为37580297956/37580365335、37581080647、37582138961。

纯证明修复保留每份 Rust 原字节，只利用冻结 CFG 首列仅0/2的事实排除不可达B分支，删除104个B证明声明。入口 LZ77.Obligation、A/C/H证明主体和900秒逐调用限额保持原样。

| 新候选 | 完整 gate | Proof/Parse | CPU | 结果 |
| --- | --- | ---: | --- | --- |
| r5-h16-small-proofopt | 37584216832 / h16-proofopt-gate | 591.5秒 | Intel Xeon Platinum 8370C | VERIFIED accepted |
| r5-h16-smallc-proofopt | 37584736974 / h16c-proofopt-gate | 646.3秒 | AMD EPYC 7763 | VERIFIED accepted |

两份新证明均通过实际重新提取、原入口义务、公理白名单检查和公共round trip；各自28个公共文件的input、token、压缩输出哈希与原候选逐份相同。精简候选目前各有一次完整通过；不能把不同runner的耗时差当作同机严格加速比，也不保证所有环境耗时。修复不改变算法性能，不使H16自动具备支付资格。

## 首批优化取舍

旧版本独立复测：37582344420，五个候选每个四块计时、同场fast3/#453及同字节shadow控制；36个公共配对进程。CPU顺逆序诊断发生符号翻转，尚无稳定提速证据。三个改变输出的旧候选在最新25803映射也非前沿。

新机制：37582348267，两新候选通过提取，383组实际Rust成本/官方encoder差分全部一致，公共及八个固定生成输入round trip通过；没有完整Lean证明。small-select压缩率与同场H3R smallC相同、时间+8.23%，停止。a-best299相对#299输出+0.010446945个百分点、时间+3.39%，当前版本停止；逐文件检查发现跨端点选择使编码块边界漂移。完整原始数据和判定在first-results.json及algorithm-notes.md。

唯一后续修正版r5-opt-a-sameend299固定被比较计划的字节终点及非末块token数，并保留原规划后续状态。Run37585987361。证明仍NOT_ADAPTED；完整块边界检查已通过，但收益不足，仍不能提交。

## 本轮最终结论

所有本轮CI已完成，状态清单为 `evidence/round5/ci-final-status.json`。两份proofopt当前通过记录分别在候选目录的 `VERIFICATION.json`；生成器manifest保留生成时的UNKNOWN陈述，不能将其误读为没有后续gate证据。

| 版本 | 公共时间轴 / 压缩率 | #299配对转移后的时间轴 / 压缩率 | snapshot25803 |
| --- | --- | --- | --- |
| H16-small（原版与纯proofopt，4runner/7块） | 7.214699 / 33.863214% | 6.988365 / 34.122912% | 非前沿 |
| H16-smallC（原版与纯proofopt，4runner/7块） | 6.768929 / 33.860879% | 6.630300 / 34.120559% | 非前沿 |
| a-sameend299（1runner/2块） | 9.505817 / 33.842789% | 9.199597 / 34.102331% | 非前沿 |

转移公式：时间逐块用`正式299时间 × 候选公共时间 / 同块public299时间`再求均值；体积乘`34.10237321953839 / 33.84283104811855 = 1.0076690443`。H/S混合尚无自身正式锚点，H16转移只是#299敏感性情景，不能当私有测试分数。四runner的时间转移范围small为6.70265–7.08365，smallC为6.43754–6.75909。不同runner不得仅选最快一次。

最后一个sameend修正版28文件块数/完整raw_end数组均与299一致，无文件变大，只节省6字节（yaml4/csv1/multibyte1），公共体积轴改善0.0000417083个百分点；时间+0.25022%。它修正了错误机制，但不足以达到前沿，停止，不投入完整证明。八个固定生成输入的两块检查通过，仍明确NO_FULL_GATE。审计在37585987361/sameend-mechanism/gate/selection-audit.json。

保留已正式提交的fast3/#453。官方25803快照（2026-10-07 15:09:58 +08:00）为0.4378734582 / 36.99972856%，rank52，公开评分份额约0.5017087%。weights/current为stale且chain_accepted=false；不代表已上链或已支付。新候选均未建立比它更可靠的收益证据。本轮没有新的正式提交或钱包交易。

机器可读总表：`evidence/round5/final-summary.json`；最新完整快照与复算说明：`evidence/round5/frontier-refresh/`、`frontier-refresh-notes.md`。
