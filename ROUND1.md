# ROUND1 — 公开首轮优化参照实验

日期：2026-10-06（北京时间）。用户已授权开始优化，并明确选择公开首轮参照实验。

目标是进入可支付的 Pareto 前沿并争取较大持续份额。正确性通过、公共 corpus 有改进、线上进入前沿及实际领奖是不同结果，分别记录。

## 官方目标：VERIFIED

官方 API snapshot **22580**，计算时间 **2026-10-06 14:19:03 +08:00**，policy `compression-policy-c255effb7d5afeef`，freshness=`unknown`。已保存同一快照的规则、榜单与全部 399 个点（4 页）；61 点在前沿。

| 参照 | 官方时间轴 | 官方大小轴 | 快照状态 |
|---|---:|---:|---|
| 原版模板 #9 | 0.545345× | 38.957803% | 非前沿，不能领奖 |
| 公开快速参照 #261 | 0.458999× | 36.595691% | 非前沿，不能领奖 |
| 奖励份额第一 #385 | 0.450505× | 36.527956% | 可支付份额 11.6215%（比赛份额内部） |
| 最快前沿 #382 | 0.448004× | 37.285647% | 可支付份额 0.0467%（比赛份额内部） |

依据：[官方规则 API](https://conjectures.io/v1/competitions/deflate)、[官方榜单](https://conjectures.io/v1/competitions/deflate/leaderboard)、[官方 Pareto API](https://conjectures.io/v1/competitions/deflate/pareto)。本表为保留的评分时点，不能当作后续实时排名。最小时间坐标也不等于奖励排名第一。

## 两个候选

使用官方已公开的被超越提交 #261 作为控制，保留原始两文件与 [来源说明](references/submission-261/PROVENANCE.md)。这是他人已公开成果，不能计作我们的独立优化收益。

| 候选 | 相对 #261 的改动 | 待验证假设 |
|---|---|---|
| `hash-wide` | HB 15→16，HN 32768→65536，HS 4096→8192 | 较大 hash head table 能否减少碰撞，并抵偿更多清零与缓存成本 |
| `probe2` | T_DEPTH、P_DEPTH、S_DEPTH 1→2 | 文本/散文/结构化文本多一次探测，能否以可接受耗时换取较小输出 |

两者都只改三项常量，复用原参照证明。官方模板、trusted contract、gate、encoder 和 pins 保持原样。

## 验证与结果

**VERIFIED**：[CI 37423606370](https://github.com/HuanHuanHuanFFF/Miner/actions/runs/37423606370) 全部步骤成功，14 分 53 秒。实测代码提交 `c9e4c3b186551d5ffb86713570827a2202cee039`。两个修改版均完成重新提取、`LZ77.Obligation` 类型检查、公理检查与公共 corpus 完整 gate，`accepted=true`，只依赖 `Classical.choice`、`Quot.sound`、`propext`。

测量：原版模板、#261、两候选；同一临时 Linux runner、同一可用 CPU；每文件 1 warmup + 11 次 measured，正反顺序各一轮。每个 parser 都由未修改的官方测量器配对 incumbent，留存每文件输出/token 哈希与全部 timing repetitions。两轮必须输出一致。

指标按当前评分公式计算公共 stage1 代理坐标：非空文件等权平均的候选/incumbent **总时间中位数比**，以及压缩/原始字节百分比。总时间包括 parser + encoder。不能用比总时间或比总字节替代。

| Parser | 公共时间轴（两轮范围） | 公共大小轴 | 输出总字节（telemetry） |
|---|---:|---:|---:|
| 原版模板 | 0.540859–0.548879× | 38.668848% | 5,885,981 |
| 公开参照 #261 | 0.452866–0.455844× | 36.336009% | 5,389,889 |
| `hash-wide` | 0.454116–0.454626× | 36.314655% | 5,384,838 |
| `probe2` | 0.458369–0.459774× | 36.035722% | 5,315,736 |

**VERIFIED**：相对同轮 #261，`hash-wide` 的大小轴降低 **0.021354 个百分点**；时间轴一轮增加 0.2760%，另一轮降低 0.2670%。16 文件变小、3 变大、9 同大小。`probe2` 大小轴降低 **0.300287 个百分点**；时间轴两轮增加 **1.2152% / 0.8623%**。15 文件变小、2 变大、11 同大小，大小收益较大的文件包括 prose、multibyte、Lean 与 C source。每候选两轮的输出/token 哈希一致，完整 gate 的输出字节亦与独立测量一致。

**INFERRED（开发决策）**：`probe2` 提供了明确的压缩/速度交换，比扩表更值得作为下一轮开发参照；`hash-wide` 的大小收益很小，当前数据没有可靠的速度收益证据。两轮不足以建立正式 admission 的置信结论，CI 时间亦不能消除机器差异。配对 incumbent 自身的总时间在这 8 个进程间约有 1.8% 漂移；部分单文件 repetition 的 max/min 达 1.67，细小速度差不能计作稳健优势。

证据：[运行元数据](evidence/round1/ci-run.json)、[完整日志](evidence/round1/ci.log)、[两轮测量](evidence/round1/comparison.json)、[原始数据复算/逐文件差异](evidence/round1/analysis.json)、[hash-wide gate](evidence/round1/hash-wide-gate.json)、[probe2 gate](evidence/round1/probe2-gate.json)。每进程原始记录另保存为 `evidence/round1/round*-*.jsonl`，可用 `python scripts/analyze-round1.py evidence/round1/ci.log` 无工具链复算。日志仅清理 ANSI 与行尾空白，保留时间戳；JSON timing 内容未改变。

**UNKNOWN**：私有 stage2、线上机器/实际 admission、该候选线上排名、是否可领奖。公共 stage1 与官网两 corpus 的坐标不能直接比较；bootstrap 的正式 admission 由线上对特定历史参照完成。

本轮结论：已取得两个正确且有可复算测量的实验候选，**尚未取得“排名靠前或能领奖”的证据**。下一步优先从 `probe2` 的逐文件结果中定位额外搜索成本，保留压缩收益并减少新增耗时，再与可复现的公开参照比较；当前不将任一候选提升为正式提交。

本轮不注册、不操作钱包、不付款、不签名、不进行正式 submission。工具链仅在临时 CI，本地不重新安装。
