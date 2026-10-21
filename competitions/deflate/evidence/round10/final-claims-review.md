# R10 最终独立主张审计

审计时间：2026-10-08 08:00 北京时间。只读候选、原始回执、官方源码和汇总；本审计仅写本文件及同名 JSON，没有运行新候选、CI、正式提交或资金操作。复核对象为 SHA-256 `1ca2f7636ede256f795fcd218c4cf0c2e90af22ddd592481616d75ee51be7353` 的 `pre-final-summary.json`，其中官方快照仍为 27641（06:26:41 北京时间，`freshness=unknown`）。后续最终快照须另行记录，不能用本审计把它称为最新状态。

**结论：已报告的核心性能数字和两个已接受的源码／证明配对没有发现阻断性错误。** 原汇总字段的基线名称有歧义，主线程已补明确字段，最终重算待完成；公共验证、私有准入及收入仍须分开表述。下面的 VERIFIED 只覆盖列出的直接证据，下一研究问题是建议，不代表已实现或已获授权继续运行。

**已独立复算的范围。** 从 13 个完成运行的原始 JSONL 重算 246 个公共配对进程，并核验 621 个原始 artifact 文件的 SHA-256。每个配对包含同一公共语料的 28 个文件、每文件 11 次有效计时；输入合计 15,930,000 字节。21 个新增 Rust 哈希计数一致。13 次运行中 12 次 CI success、1 次 failure；失败的 prove-a 是 seed 证明错误，不能写成所有运行都成功。246 是配对进程数，不是独立机器数；重复公共测试也不是新增独立语料。

时间轴按官方形式先逐文件取总压缩时间中位数之比，再对文件等权平均，得到每个候选／区块的 normalized time。候选相对对照取同 run、同 block 的轴值之比；先对块平均，再对运行等权平均。不能直接相除不同 runner 的绝对时间均值，也不能用 LZ77 单阶段计时替代总压缩时间。

| 比较 | 独立 CI jobs / blocks | 重算时间变化 | 公共输出 |
|---|---:|---:|---|
| pipeline / scalar | 2 / 4 | -1.712193382% | tokens、bytes 相同 |
| pipeline / record | 2 / 4 | -0.652193783% | tokens、bytes 相同 |
| record / scalar | 7 / 14 | -0.979486256% | tokens、bytes 相同 |
| prefixmask / record | 1 / 2 | +7.853160757% | tokens、bytes 相同 |

这些是所测固定公共语料的配对结果，不是私有集保证或跨所有 CPU 的速度保证。pipeline 四块相对 record 均为负值，支持保留小收益结果；数值规模仍远小于取得当前前沿位置所需的改进。这里的 jobs 是不同 CI 运行实例，未据此推断不同物理机器或 CPU 型号。

pipeline、record 和 scalar 的公共 mean-file size 均为 **33.934365747942536%**；相对 public361 为 **-0.02426100803957354 个百分点**。这是平均文件压缩率的百分点差，不是总字节加权压缩率的相对变化；这部分大小收益也不是 pipeline 新增的。原 gate 日志中的“4.848% smaller”是另一种字节统计，不能混为该 pp 数字。

**精确证明配对。** 核对当前候选、gate 原始 input 副本、日志和 VERIFICATION，以下两对相符：

- record：Rust `7f1c661fd1ce29d12c69671f034ff5a713e284ed1fcba66ba404ff25479b55b7`，Lean `86cfc36adb009970bccbb5a9c543c5f559148d729e8c0f041934aab44e95592d`；run 37684506856 / struct-b。
- pipeline-proof：Rust `b74ae5fd9575101b6b34b9f2718d8835adca770c6765c30b33bb895878ba1adf`，Lean `e0ded4248a894e8c53bc1ce644c7c3f5c6681fe3c06eaab597caf10a5bf472db`；run 37700280634 / confirm-j。

两份原始完整 gate 都重新提取并检查 `LZ77.Obligation slot.parse`，公理为 `propext`、`Classical.choice`、`Quot.sound`，最终 accepted，并完成公共 corpus-stage1 round trip。pipeline core verification 日志为 542.4 秒。restore-h 里的 pipeline 使用相同 Rust，却借用了旧 Lean `86cf…`；它可提供该 Rust 的性能证据，不能被标为接受过的源码／证明配对。只有上述 `b74… / e0ded…` 获得对应完整 gate 证据。CI success 本身也不等于所有 extraction 或 proof 成功，例如 mask-k CI success 同时包含 extraction rejected。

**汇总名称的具体问题。** `scripts/summarize-round10.py:123` 中 `relative_to_parent_times` 固定除以 `r9-block-scalar`；第 144 行据此写出 `relative_time_change_pct_vs_parent`。数字算术正确，但 parent 不是候选 manifest 的实际父版本。prefixmask 的该字段 +7.151876711% 是相对 scalar，实际相对 record 是 +7.853160757%。最终报告应直接写 scalar／record 名称；本审计未改共享脚本。

08:02 的跟进检查已确认主线程在脚本中加入 `*_vs_scalar`、`*_vs_public361`、`legacy_parent_comparison_baseline=r9-block-scalar` 和顶层字段定义。旧 `pre-final-summary.json` 仍是本次复核的冻结对象；等待最终重算，不能将新增字段说成已经出现在该旧回执中。当前 `round10.md` 已明确表中全部 21 个版本相对 scalar；其基线、接受 pair、CI 与 gate 区分及下一研究边界一致。两个低风险措辞建议已反馈：将“#453 仍存活”明确为“仍是该 hotkey 最早的前沿点”；压链／RMQ 的维护成本解释保留为推断，不写成已隔离的时间归因。

**准入与支付边界。** 本轮两份完整公共 gate 不能替代 corpus-stage2、正式 admission、注册资格、bounty cap 或链上支付。快照 27641 所含 policy 要求 stage1 与 stage2，`pareto_share=1`、`improvement_share=0`。基于 public361 的同族投影仍属 INFERRED：pipeline 约为 `1.403780310 / 34.185517190%`，被 #360、#418、#422 支配；其条件几何份额为零。压力投影也不是私有集置信区间。当前正式排名与收入须由最后一次官方刷新决定。

本地官方 `validator/scoring/combine.py:128–155` 先按 `(submitted_at, submission_id)` 排序，再选每个 hotkey 留在前沿的最早提交；较新的重复 hotkey 点仅保留 improvement 部分。因本快照 improvement 为零，**若 #453 仍是该 hotkey 最早的前沿点，新点即便有几何份额，其自身新增 Pareto payable weight 仍为零**。这不是该 hotkey 整体份额永远不变的结论：新几何可以改变旧点权重，且新点若支配并移除 #453，条件会改变。27641 中 #453 的 payable weight 为 `0.0034807359791970568`（竞争 Pareto 池内约 0.3480736%），只是当次评分记录，不是本轮新增收入或同快照链上到账证明。

**prefixmask 的停止依据。** run 37702101006 的原始 extract-only 日志显示 source intake 和 static 成功；Charon compile exit 0（1.8 秒），translate exit 1（98.8 秒），因此第 3 阶段拒绝。`002-extract.sh.log` 为空，未产生 Types/Funs。官方 `extract.sh:37–38` 将 Aeneas stdout 重定向到 `/dev/null`；具体报错原因仍是 UNKNOWN。编译阶段虽出现 miri fallback 提示，但该阶段成功，不能当作本次拒绝原因；也没有进入 Lean 证明失败。extract-only intake 的空 Lean 是提取模式行为，不是候选完整证明已受检。

该 Rust `5a4b534b9966d21f06f8cde90fe0c5c6f5d6c4429c2c19c57a2a1e300c9993c1` 的 native 444 例均与 record tokens/decode 相同，公共输出也相同；这些有限证据不补齐提取或全输入证明。两个公共时间块相对 record 为 +7.471809285%、+8.234512230%，足以否决本轮继续为它修复提取或投入完整证明。

独立重加 28 文件计数：publish 12,812,018；best-length 有效调用 6,967,033；其区间长度和 28,038,648，平均 **4.024474694**；singleton 3,258,508；prefix query 4,044,072；fallback/disabled 为零。`pm_cost + d_bcost` 为 **51,023,656** 次逻辑 getter 调用，约为旧候选区间长度和的 **1.819761638 倍**。插桩副本与 frozen 在这 28 文件 tokens/decode 相同。这里没有硬件 load 计数、微函数时间或性能百分比归因；调用总数只支持“缓存维护可能抵消短区间查询收益”的机制解释。

**下一研究问题的来源级判定：合理，但先计数，当前不实现。** `d_gap` 第三个循环已越过 pending-push 范围，仅在 continuation 和 literal 中取较小的打包值。一次调用内 endpoint/distance 成本固定；如果 continuation 已赢、后续 length-cost 平台相同、literal 成本严格为正且加法不会在打包的 32 位成本中回绕，则 continuation 在该平台内持续赢。它可能允许批量写入相同高 32 位成本和递增的低位 choice，减少逐字节 literal 查表与依赖比较；每字节 ring/out 写入仍然存在，当前没有向量化或总时间收益证据。

最低保持条件和反例不能省略：

- 处理 **32 位打包回绕**，不能只检查 u64 加法溢出。若 continuation 高位成本为 `0xfffffffe`，下一字节 literal cost 为 3，则 literal 打包后的高位变为 1，原逐字节算法会选 literal，盲填 continuation 错误。
- literal cost 为 0 时必须保留 choice tie。`dlit=0` 下等成本 literal choice 通常小于 match choice；`dlit=D_LIT` 下合法 match choice 则通常较小。不能未经检查假定所有 helper 输入价格都严格为正。
- 保持实际 `lc[rem % 512]` 平台、合法 choice 低位界，以及 `kc/chd/end` 不变；遇到块表切换、gap 所属节点切换、pending-push 边界、长度平台边界或 ring 的物理分段须截断／重建条件。新的批量循环还需要清晰的终止和数组界证明。
- 先计第三循环覆盖字节、continuation 赢后的连续平台宽度分布、零 literal 价格和到 u32 回绕的余量，并记录块／ring 截断损耗。只有足够机会量才值得实现；平均 range=4.02 与 51M getter 不能回答这些问题。

因此建议仅保留为下轮可证伪研究问题。本轮没有新增该算法，没有新实验或后续执行授权；prefixmask 实现与修复保持停止。

具体逐块值、原 gate 日志 SHA、公式复算数量和审计边界见 [final-claims-review.json](final-claims-review.json)。
