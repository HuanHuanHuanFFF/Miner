# R25 两个保留配对的独立收尾审计

**VERIFIED：两个当前 Rust／Lean 配对均与各自原始 gate 输入、VERIFICATION 和新确认 spec 一致；未发现身份绑定错误。** 已核验两次确认的全部44份 JSONL，并从逐次测量重算公共 time/size 指标，与 state 一致。**快照29697的条件投影中，两候选各4个主确认块全部为0份额。** 这不影响已通过的正确性结论，也不构成稳定竞赛收益。

本审计只读候选、原始回执和源码；没有运行工具链、CI、Git 或重新抓取官方榜单。完整字段、文件 SHA 和逐 JSONL 身份见 `final-pair-audit.json`。

## 精确配对和原始 gate

| 候选 | 当前 Rust SHA-256 | 当前 Lean SHA-256 | 原始 gate |
|---|---|---|---|
| r25-astra-end4 | `03ec0aa4e617d622755e85324a9d4fbc77ef74e6572485b3170e2790681ed8e6` | `4ff09d168269ae8d9c93e602496b01078d2d0ec80f27d6cd16041d91a76c70a6` | 38125243582 |
| r25-astra-tiny-pc8-proof1 | `5c20b99cf52ac8e2f047b4e2e83be974b1f9b1f21b23d54ccccb25c58b891f00` | `3bd53694534c0114453a95c2f120d743fde3af233de88c00e1d5c30fe05ccdb8` | 38130996700 |

当前大小分别为361083／404060B与365360／410352B，均低于524288B。逐字哈希核对覆盖当前文件、VERIFICATION、gate spec以及归档 `exact-gate/input` 两文件。

两个原始 `gate.log` 均明确记录：Charon+Aeneas重新提取；原 `LZ77.Obligation slot.parse`；bwrap、原900秒 Lean 限制和16384MB；允许公理仅 `Classical.choice`、`Quot.sound`、`propext`。原始006/007公理日志一致，Lean为4.31.0，commit `68218e876d2a38b1985b8590fff244a83c321783`。验证分别用556.1秒、540.2秒通过，公共输出5325224B、5332289B；公共原始输入均15930000B。这些 gate 的 paired_performance_blocks 为0，gate smoke时间不参与性能结论。

两次 gate 的CI原日志记录上游固定commit `a356bbff18b60c4527fbcc85d5a28ef9c20214e0`、70/70 pinned source匹配及 `pins.py --check` 成功；gate后的官方树diff日志为空，回执对应检查为true。固定encoder为 `172c240014f65d5e2762c1287e4982dd1cd426f2999f74e17011e05f2dc5fdec`，token为 `8bf5d962324b3a0890f3c75f713198be086c4b0659797c24b8b976978cea4917`。原measure的首轮 `check_round_trip` 会把失败写入errors；确认JSONL所有errors为空、deterministic为true。另两次确认各有每候选540个有限native decode case，均0失败。

原依赖构建日志含Aeneas库的sorry警告；没有把它们隐去，也没有据此声称候选含admit。接受定理的实际公理查询只列上述三项。原gate没有保存其score阶段的逐文件JSONL；原verdict/log、输出总字节及后续完整逐文件确认构成现存证据范围。

## 新确认的运行环境分别列示

两次均为独立workflow_dispatch/job，同一仓库commit `3bd8e378c0f15419982cc994bda24b474cfe717e`，每次2个主测块，反向顺序相互交叉；没有在确认作业重新跑full gate。

| 项目 | 38135739022 / confirm-components-a2 | 38135751559 / confirm-components-b2 |
|---|---|---|
| Job ID | 114459107670 | 114459146911 |
| 开始UTC | 2026-10-11 11:29:25 | 2026-10-11 11:29:38 |
| 完成UTC | 2026-10-11 11:43:30 | 2026-10-11 11:43:35 |
| CPU | AMD EPYC 7763 64-Core Processor | Intel Xeon 6973P-C |
| Governor | null，未报告 | performance |
| OS / arch | linux / x86_64 | linux / x86_64 |
| Rust | 1.100.0-nightly，8fa1c96cf，2026-08-17 | 相同 |
| 预热／测量 | 每文件1／11次 | 每文件1／11次 |
| 构建／沙箱／内存 | release / true / 2048MB | 相同 |
| 请求CPU / host affinity | `0` / `[0,1,2,3]` | 相同 |

这里同时保留请求cpus与host进程affinity，不把它们混称为实测sandbox子进程亲和性。该子进程实际mask在本回执中未独立核验。perf不可用（paranoid4）是能力探测记录，不是候选性能证据。

所有44份JSONL的engine/template/host provenance分别一致为 `ab202460…` / `584b0179…` / `2b32344a…`，完整值在JSON审计中。每文件28输入／15930000B、11个measured rep、`total_s=parse_s+encode_s`、零错误与确定性都检查通过。按逐文件measured total中位数和incumbent配对重算的公共指标与state相符。

end4所有主测／副本／两run记录的lib SHA一致为 `e898d414a4a732dafd012942b6d1c8934d6e85d4a1ca81d7a5bef2f58c4fc642`；tinyPC为 `276316d0937f14509bdd8bc9c5fef0fa34d47c7a35bc7ef783e9d3b5608e5f9e`。所有Rust source SHA与spec相同，Lean通过spec和单独原gate绑定。编译二进制没有归档到本机，因此这里只核验记录的一致性，没有冒称重哈希了二进制实物。

两对候选在主测／副本／两run的所有逐文件token SHA及output SHA一致，并与原gate总输出字节相同。四个artifact的归档文件清单SHA全部复核：两个gate各17文件，两个确认各31文件。GitHub ZIP digest保留，但本审计没有重新下载或独立重算ZIP摘要。

## 性能与份额边界

按已保存快照29697（评分时间2026-10-11 11:45:35.330581 UTC、policy `compression-policy-c255effb7d5afeef`），analysis及rank相互引用的SHA一致。tinyPC聚合项沿用原canonical名称 `r25-root-tiny-pc8`，本审计按完整Rust哈希定位，并确认4个新主确认的entry_name均为 `r25-astra-tiny-pc8-proof1`、proof SHA均为已gate的 `3bd53694…`，没有把先前DRAFT证明计为已验证。

| 候选 | 主确认块／独立run | 公共time相对combo范围 | 主份额最低／中位／最高 | 零份额／严格第一 |
|---|---:|---:|---:|---:|
| end4 | 4／2 | +0.9950%至+1.2935% | 0／0／0% | 4／0 |
| tinyPC proof1 | 4／2 | +1.6382%至+2.8451% | 0／0／0% | 4／0 |

public595-shadow校准复用同4个主观察，不是4个额外独立确认。候选同源码shadow测量也只作为控制，不能增加主确认计数。公开输出改善分别为7397B和332B，但当前证据支持保留为已证明的质量组件，不支持宣称稳定份额或榜首成果。

**UNKNOWN／剩余边界：** 私有stage2在gate安装日志中不可用；没有正式admission、提交或奖励结果。快照29697是本次审计采用的已保存评分回执，不代表之后实时榜单。未发现阻断当前精确配对正确性绑定的材料缺口；未归档二进制、gate score逐文件原JSONL和子进程实际affinity的边界已如上明确保留。
