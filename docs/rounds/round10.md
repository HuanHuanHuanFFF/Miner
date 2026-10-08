# 第十轮：同字节优化、完整验证与前沿边界

执行规则见 [AGENTS.md](../../AGENTS.md)。会话 ID：`01a117eb-0257-7f51-a1b9-a7621bdf16dc`。本轮北京时间 2026-10-08 **03:50:52** 开始，五小时截止 **08:50:52**；当前 [预算回执](../../evidence/round10/budget.json) 与逐次决策 [research-state.md](../../evidence/round10/research-state.md) 保留阶段状态。本报告的最终快照与归档校验尚在收尾。

## 结果

**尚未取得新的均衡可支付前沿点。** 全部 13 个 CI 已自然结束，测试了 **21 份不同 Rust 源码、246 个公共配对测量进程**，得到两份通过完整公共 gate 的新源码／证明对。其余独有负面结果、提取拒绝和未验证草稿均保留。完整复算见 [pre-final-summary.json](../../evidence/round10/pre-final-summary.json)。

当前最好的已验证包是 [r10-finder-pipeline-proof](../../candidates/r10-finder-pipeline-proof)：空记录消除加原 DP 插入预读流程。两个独立 runner、四个公共计时块平均比本轮起点 scalar 快 **1.7122%**，压缩输出逐字相同；相对同场 record 父版，平均再快 **0.6522%**。幅度在 runner 间变化，不能把均值解释成保证值或统计置信界。

备选 [r10-record-nonempty](../../candidates/r10-record-nonempty) 只省去空候选记录，改动与证明更小。七个 runner、十四块平均比 scalar 快 **0.9795%**，输出相同，也有完整公共 gate。后续需要较小证明迁移成本时可复用此包。

证据口径：**VERIFIED** 为精确源码／证明的公共 gate、公共输出和配对测量；**INFERRED** 为同族迁移、压力场景和候选几何份额；**UNKNOWN** 为私有 stage2、正式 admission 与这些新候选的实际奖励。本轮没有正式竞赛上传、链交易、新注册、签名或付款。

## 精确交付与验证

| 包 | Rust SHA-256 | Lean SHA-256 | 完整 gate |
|---|---|---|---|
| pipeline-proof | `b74ae5fd9575101b6b34b9f2718d8835adca770c6765c30b33bb895878ba1adf` | `e0ded4248a894e8c53bc1ce644c7c3f5c6681fe3c06eaab597caf10a5bf472db` | [37700280634](https://github.com/HuanHuanHuanFFF/Miner/actions/runs/37700280634)，通过 |
| record-nonempty | `7f1c661fd1ce29d12c69671f034ff5a713e284ed1fcba66ba404ff25479b55b7` | `86cfc36adb009970bccbb5a9c543c5f559148d729e8c0f041934aab44e95592d` | [37684506856](https://github.com/HuanHuanHuanFFF/Miner/actions/runs/37684506856)，通过 |

证书分别为 [pipeline VERIFICATION](../../candidates/r10-finder-pipeline-proof/VERIFICATION.json) 和 [record VERIFICATION](../../candidates/r10-record-nonempty/VERIFICATION.json)。旧试验目录中的复制父证明仍保留当时的未适配状态，接受结论只属于上表精确 pair。

pipeline 的官方检查重新运行 Charon/Aeneas，核对原始 `LZ77.Obligation slot.parse`，公理恰为 `Classical.choice`、`Quot.sound`、`propext`，并完成 28 文件公共往返／评分；原输入 15,930,000 字节、输出合计 4,882,102 字节。日志中的 542.4 秒是阶段 0–5 的验证耗时，其中 Parse 调用 374.9 秒。完整公共 gate 随后完成阶段 6 的公共往返与评分；542.4 秒不含该阶段及额外生成语料检查。公开原作者及来源继续见 [#361 PROVENANCE](../../references/round7-public-361/PROVENANCE.json)。

这不是对“与父版在所有输入上 token 相同”的 Lean 证明。原生 444 用例、公共同 token／输出、代码机制论证与完整原始正确性 gate 分别记录，不互相替代。

## 配对性能与波动

正式时间轴按每文件候选／配对 incumbent 总压缩时间中位数之比，再等权平均；包含 parser 和公共 encoder。每文件 1 次预热、11 次正式重复。相对父版先比较同 runner、同 block 的轴，runner 内等权汇总后再对 runner 等权。没有用不同机器绝对秒数相除。

pipeline 公共四块相对同场 record 的变化：

| runner | block 1 | block 2 |
|---|---:|---:|
| restore-h | −0.22296% | −0.41239% |
| confirm-j | −1.27203% | −0.70140% |

第一台 runner 的小信号低于当场同源码 clone 的最大观察波动 0.6472%；第二台的平均变化 −0.9867% 大于其 clone 最大观察变化 0.4710%。clone 只是描述性对照，不能据此宣称统计显著性。

[稳定性复核](../../evidence/round10/stability-confirmed.md) 按相同输入 SHA 将 18 个 D 路由与 10 个未改非 D 路由分开。confirm-j 的 pipeline 改善主要来自 D：贡献 −1.1112 pp，非 D 贡献 +0.1245 pp；二者合为 −0.9867%。未改路由贡献也是测量结果，不能自动视为纯噪声。

公共压缩大小轴固定为 **33.934365747942536%**。八个脚本生成输入也有独立诊断；它们公开、固定且不是私有 stage2。早期生成语料没有同场 scalar，不能据此推断相对 scalar 的反转；后期 pack/confirm/mask 加入同场 scalar 与 record。见 [早期审计](../../evidence/round10/synthetic-transfer-audit.md)、[pack 同场审计](../../evidence/round10/pack-transfer-audit.md)。

## 所有实测版本

以下全部相对同场 scalar；跨 runner 按上述方式汇总。“大小”单位为百分点 pp。表中 0 表示完全相同的公共输出大小，具体 token／输出身份以原始回执为准。

| Rust 版本后缀 | 总时间变化 | 大小变化 pp | 结论 |
|---|---:|---:|---|
| finder-pipeline | −1.7122% | 0 | 最佳已验证包；两个 runner 复现 |
| record-nonempty | −0.9795% | 0 | 完整 gate；较小改动备选 |
| forward-seed | −5.5527% | +0.1351735 | 质量损失复现；证明另有四处终止错误 |
| forward-lazyseed | −5.0739% | +0.0926915 | 质量损失过大 |
| forward-seed2 | +9.6347% | +0.0583781 | 追加 pass 仍更慢、更大 |
| forward-costseed | −3.0988% | +0.0656117 | 追回部分质量却增加成本，停止 |
| finder-tag4 | +6.0713% | −0.0013716 | 新增表没有形成有用两轴收益 |
| finder-hash5 | +4.4842% | −0.0053775 | 发现新增匹配，未形成有用两轴收益 |
| finder-key5 | +4.7821% | −0.0005412 | 停止长键替换扫参 |
| finder-key6 | +2.2458% | −0.0031119 | 收益不足 |
| forward-delta16 | +1.2501% | 0 | 同字节但变慢 |
| forward-rebase16 | +2.9653% | 0 | 空间变小，但同字节总时间增加 |
| rmq8 | +5.1328% | 0 | 同字节总时间增加，具体时间归因未测 |
| finder-row16 | +11.3824% | +0.0079558 | 两 runner 均慢且大 |
| finder-row16-mask | +7.0641% | +0.0079558 | 对 row16 恢复 4.2889%，仍无用 |
| forward-endprobe | +0.0734% | −0.0017765 | 16 文件共省 319 字节；保留小质量研究材料，未完整证明 |
| forward-costcache | −0.5420% | 0 | 相对 record 仅 −0.0583%，无可辨新增收益 |
| finder-linkearly | −0.2394% | 0 | 相对 record 慢 0.2458%，停止 |
| forward-routecfg | −1.4047% | +0.0001288 | 相对 record 小变化，不足前沿目标 |
| record-packed | +0.2475% | 0 | 相对 record 慢 1.4456%，停止 |
| backward-prefixmask | +7.1519% | 0 | 相对 record 慢 7.8532%；官方提取拒绝，停止 |

所有 21 份源码在当前同族与声明的压力场景中都没有前沿份额。source 相同的 proof 包没有重复计作新 Rust。

## 从反馈得到的机制结论

- **统计种子不能只看搜索覆盖。** seed/costseed 的原匹配流在 18 个公共 D 输入和 66 个生成输入上保持一致，但后续种子／成本规划仍损失质量。成本筛选追回约 29% 的 lazyseed 大小损失，剩余差距仍过大，停止继续调同类种子与 pass。
- **少做局部工作不等于总压缩提速。** costcache 少重建了 1,523/6,208 次成本表，整体对 record 仅 −0.0583%，两块变号。linkearly 的实际完整机器码确认下一指针读取部分提前，同时观察到额外栈存储；实际总时间无收益。见 [机器码审计](../../candidates/r10-finder-linkearly/codegen-result.md)。
- **记录更紧凑也可能更慢。** packed 在 18 个公共 D 路由累计少存 17,238,988 字节，节点流和首遍计划不变，444 等价及公共输出检查通过；但公共对 record 慢 1.4456%，生成语料仅有 −0.1438% 小反向信号。所省是多个记录流的存储合计，不是峰值 RSS。
- **端点区间实际很短。** prefixmask 有 6,967,033 次选择，原长度扫描合计 28,038,648，平均约 4.02；维护 12,812,018 次逐字节发布后，`pm_cost+d_bcost` 合计约 51.02M 次逻辑调用，约为原区间长度总数的 1.82 倍。计数不是硬件 load 或时间占比。该版本 444 与公共输出一致，但官方 Aeneas 第 3 阶段退出 1，未产出完整提取；工具丢弃了 stdout，具体原因仍 UNKNOWN，不能称为 Lean 失败或 Miri 缺失所致。
- **加入节点需要分析旧边是否保留。** 末尾补查确有小质量收益，但更早插普通节点有一个 [89 字节反例](../../candidates/r10-forward-overlay-study/counterexamples.json)，会删除原 gap continuation 选择；即便补上 gap owner，动态最佳端点回推仍可能改变原边集。原 rs 候选保留不等于整个规划图边集保留。
- **迁移附带改变也要拆开核查。** 原 DP 转 D 时同时改变了部分 key/update/half 及长度枚举。routecfg 只恢复模型配置，仍保留 flen16，未声称恢复原 DP 计划；实际变化仅在预期五文件，仍不足目标。

## 前沿与支付边界

当前复算使用完整快照 **27641，2026-10-08 06:26:41 +08:00**，494 行、76 个前沿点，API freshness 标为 unknown。原始响应、请求时间与 SHA 见 [receipt](../../evidence/round10/official-late-research/receipt.json)。公开 scorer 重放误差为 `6.94e-18`。

| pipeline 条件模型 | 时间轴 | 大小轴 | 几何份额 |
|---|---:|---:|---:|
| 同族 #361 迁移 | 1.40378031 | 34.18551719% | 0 |
| 声明的压力场景 | 1.43836924 | 34.20584067% | 0 |

同族模型仍被 #360/#418/#422 支配。固定此大小时，时间还需再改善约 5.02% 才可能跨过现有几何门槛。压力场景取最慢观察配对比值再加 2%，大小取同族值加 0.01 pp 与公共大小×1.008 的较大者；它不是置信区间或私有集保证。

官方只为同 hotkey 最早的存活前沿提交分配 Pareto 支付。本次快照中该点仍为 #453；即使未来均衡点有正几何份额，只要新点加入后仍有更早的同 hotkey 前沿点，新点本身的可支付份额仍为 0。见 [规则与源代码核对](../../evidence/round10/payability-notes.md) 和 [支付重放](../../evidence/round10/payability-late-research.json)。weights/current 与固定分页不是同一快照，不据此推断本次分数已被链接受。

邻近 #375/#418/#422/#443/#489 的公开源码接口均返回 `SOURCE_WITHHELD`，不能由其坐标猜测内部优化。见 [原始响应审计](../../evidence/round10/public-neighbor-audit.md)。本轮没有触及未开放源码。

## CI 与复现

| 批次 | Run ID | 结果 | 公共配对进程 |
|---|---|---|---:|
| explore-a | 37679261323 | success，筛选／提取／有限诊断 | 24 |
| rmq-a | 37680712729 | success，有限等价；无完整 gate | 16 |
| prove-a | 37682364860 | failure，seed 四处 omega 终止义务未关闭 | 18 |
| struct-b | 37684506856 | success，record 完整 gate | 22 |
| row-c | 37688325585 | success，独立复测 record | 18 |
| rebase-d | 37689247460 | success，有限等价；无完整 gate | 16 |
| selective-e | 37693029351 | success，末尾补查／行掩码 | 20 |
| cost-f | 37693861172 | success，成本种子 | 18 |
| cpu-g | 37695105461 | success，缓存与加载顺序 | 20 |
| restore-h | 37695964878 | success，流水与模型配置 | 20 |
| pack-i | 37698560245 | success，节点压缩／生成对照 | 18 |
| confirm-j | 37700280634 | success，pipeline 独立复测与完整 gate | 18 |
| mask-k | 37702101006 | success，但研究提取被拒绝、未执行完整 gate | 18 |

246 包含对照进程，不是 246 个独立 runner；每个进程覆盖 28 文件。只有表中两份新 pair 完整 gate 接受。失败 seed 的另一个修复草稿、delta16/row/其他接口草稿仍属于未验证材料。

每批保存原始 reps、输入／token／输出 SHA、编译器与 runner、官方日志、提取和 `raw-artifact-files.json`。目录为 `evidence/round10/<run>/<batch>/gate/`；没有改写原始回执的字节与哈希。可用 `scripts/summarize-round10.py` 对报告列出的 gate 目录重新计算；`scripts/analyze-round10-stability.py` 复核分组贡献，`scripts/write-round10-verification.py` 核对接受 pair。另有 [独立结论审计](../../evidence/round10/final-claims-review.md) 复核数值、基线、证明与下一步假设边界。

[归档校验](../../evidence/round10/archive-check.json) 检查 621 份原始实验文件、246 项源码／证明与 6 项 gate 输入检查，全部一致；706 个 Git 路径的归档字节也匹配。另对 [13 次冻结提交](../../evidence/round10/frozen-run-input-check.json) 的 220 个不同输入路径分别核对，确认每次实际 run 的提交保留了对应源码／证明。检查结果绑定各自记录的提交，不把之后的报告提交冒充被验证对象。新增的明确基线字段及策略校验也经过 [旧汇总数值回归](../../evidence/round10/summary-generator-check.json)，1,804 个原有标量字段保持一致。

开发分支为 `codex/round10-balanced`；原 `main` 的 `4ce98ccfe48ced871a501a016518076baf8a81d9` 保留，未合并。官方 sources/contract/encoder/gate/pins 阅读副本未改，工作流仍只手动启动，私有开关默认 false。本地未新增编译工具链或已编译二进制。

## 下一次最有价值的最小实验

**建议先计数，不直接继续添加缓存。** 现有端点范围平均只有约四项；下一问题是 `d_gap` 无 pending-push 部分中，有多少字节处于“续接匹配已胜出、长度成本保持相同”的区间，区间宽度是否足够批量填充。先保存覆盖率、宽度分布和候选 token 一致性，再决定是否实现。

这个想法尚未实现、未测性能、未完成证明。必须处理打包成本的 u32 回绕、字面量价格、choice tie、块边界和数组界；发现反例或覆盖率不足就停止。当前能够交付的是已验证的约 1.7% 同字节收益及完整负面证据，不能将下一步假设写成已有前沿成果。
