# C23 两 runner 原始确认审计

Snapshot `29954`，identity-check latest=`True`，freshness `unknown`。共 `36` 条原始流程（每 runner 18），独立 API 前沿 `105` 点；36 条 JSONL SHA 均与分析登记一致。
Runner 硬件：`38269106179`=AMD EPYC 7763 64-Core Processor, `38269130947`=AMD EPYC 9V74 80-Core Processor.
原始 36 流的 X/Y、路径和 SHA-256 在机器 JSON `raw_processes` 列表中；这里不复制逐流大表。

## 16 个候选主投影

每个候选、runner、block、primary/shadow 各一行；同源码副本全部另列为 control。

| Runner | Candidate | Block | Anchor | raw X | Projected X | Y (%) | Share (%) |
|---|---|---:|---|---:|---:|---:|---:|
| 38269106179 | C2 fold-tail | 1 | primary | 0.466580628 | 0.469720849879 | 35.603019030 | 0.864189305 |
| 38269106179 | C2 fold-tail | 1 | shadow | 0.466580628 | 0.469190832350 | 35.603019030 | 0.975842113 |
| 38269106179 | C2 fold-tail | 2 | primary | 0.467245095 | 0.470684895942 | 35.603019030 | 0.666867294 |
| 38269106179 | C2 fold-tail | 2 | shadow | 0.467245095 | 0.471057701721 | 35.603019030 | 0.592570488 |
| 38269130947 | C2 fold-tail | 1 | primary | 0.461227652 | 0.470118785078 | 35.603019030 | 0.781835110 |
| 38269130947 | C2 fold-tail | 1 | shadow | 0.461227652 | 0.470699343329 | 35.603019030 | 0.663967085 |
| 38269130947 | C2 fold-tail | 2 | primary | 0.464224222 | 0.474609200881 | 35.603019030 | 0.000000000 |
| 38269130947 | C2 fold-tail | 2 | shadow | 0.464224222 | 0.472683881600 | 35.603019030 | 0.000000000 |
| 38269106179 | C3 deferred-extension | 1 | primary | 0.467930380 | 0.471079686310 | 35.603019030 | 0.588224399 |
| 38269106179 | C3 deferred-extension | 1 | shadow | 0.467930380 | 0.470548135515 | 35.603019030 | 0.694404516 |
| 38269106179 | C3 deferred-extension | 2 | primary | 0.467730285 | 0.471173657572 | 35.603019030 | 0.000000000 |
| 38269106179 | C3 deferred-extension | 2 | shadow | 0.467730285 | 0.471546850474 | 35.603019030 | 0.000000000 |
| 38269130947 | C3 deferred-extension | 1 | primary | 0.461501616 | 0.470398031007 | 35.603019030 | 0.724802331 |
| 38269130947 | C3 deferred-extension | 1 | shadow | 0.461501616 | 0.470978934104 | 35.603019030 | 0.608174176 |
| 38269130947 | C3 deferred-extension | 2 | primary | 0.461695159 | 0.472023561018 | 35.603019030 | 0.000000000 |
| 38269130947 | C3 deferred-extension | 2 | shadow | 0.461695159 | 0.470108730749 | 35.603019030 | 0.783900272 |

## 主候选与同二进制副本统计

本批投影 Y 均为 `35.603019029780%`；真实时间零份额边界为 #562 的 X=`0.471162985455`。
关键分歧：C2 runner B block 2 两个主校准都越过该界；C3 runner A block 2 两个主校准都越界；C3 runner B block 2 主锚越界，但 shadow 锚仍在界内，份额 `0.783900%`。

零次数与份额范围分别统计；shadow/copy 是同二进制控制，绝不并入独立候选样本数。

| Runner | Candidate | 类别 | 份额行数 | 零次数 | 正份额范围 (%) |
|---|---|---|---:|---:|---:|
| 38269106179 | C2 fold-tail | candidate_main | 4 | 0 | 0.592570–0.975842 |
| 38269106179 | C2 fold-tail | same_binary_copy_control | 4 | 2 | 0.981750–1.095617 |
| 38269106179 | C3 deferred-extension | candidate_main | 4 | 2 | 0.588224–0.694405 |
| 38269106179 | C3 deferred-extension | same_binary_copy_control | 4 | 2 | 1.180476–1.297960 |
| 38269130947 | C2 fold-tail | candidate_main | 4 | 2 | 0.663967–0.781835 |
| 38269130947 | C2 fold-tail | same_binary_copy_control | 4 | 4 | — |
| 38269130947 | C3 deferred-extension | candidate_main | 4 | 1 | 0.608174–0.783900 |
| 38269130947 | C3 deferred-extension | same_binary_copy_control | 4 | 2 | 0.823925–1.232983 |
| ALL | C2 fold-tail | candidate_main | 8 | 2 | 0.592570–0.975842 |
| ALL | C2 fold-tail | same_binary_copy_control | 8 | 6 | 0.981750–1.095617 |
| ALL | C3 deferred-extension | candidate_main | 8 | 3 | 0.588224–0.783900 |
| ALL | C3 deferred-extension | same_binary_copy_control | 8 | 4 | 0.823925–1.297960 |

## 同源码过程控制与证明状态

两个 runner 的 raw JSONL 共 `12` 个已核验同二进制配对差；控制差全表在机器 JSON 中。
C2 proof1 exact gate 记录 `True`。C3 proof1 exact gate 记录 `False`；这批坐标只覆盖 proof1 源码，不能视作 proof2 后的最终确认（proof2 另一个 pair 仍在运行）。

所有份额是 29954 当前真实几何的单点重放。主候选每个算法仅有两个 runner、两个 block 的 discovery/confirmation 主测量；四种投影不作为四份相互独立证据。
