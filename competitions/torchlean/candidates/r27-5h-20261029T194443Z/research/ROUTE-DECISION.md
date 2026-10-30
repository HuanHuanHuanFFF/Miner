# R27首次选路决定

20:30检查点；共同截止00:44:43不变，等待/修复都计时。目标任意现任分榜冠军，overall不优先，公开原版不是性能目标。

1. 主攻normalized_mlp：强起点12，当前冠军23身份/hash已核。C norm-guard26完整候选5fcb3b89正由batch2原all12 gate验证；D的min/square统计准备与D07精确reciprocal另作可组合候选，需各自真实成本和组合版本完整验收。C模型中3875/18063旧fallback可移至精确fast path只是有限覆盖，不是部署比例/成功概率。优先闭合这个完整候选，再扩充队列。
2. 独立高上限机制保留packed-output整数表示。3085B实运行源包含实际准备/因子/提取/bias/finish/zero，父代数界已复核；先一个真实Mixer完整调用成本，包含classifier及未修改norm/GEMM。不能从Python收益推Lean速度，也不能在成本未知时建大矩阵证明。记录实际接入覆盖：只替dense.linear不自动替换前任Ya3Q内部直接调用YaV，若要影响GEMM必须显式绑定实际调用图。
3. FP保留独立数学路线：key4根已接受，prepare已见4个真实Id.run目标且有定点修复；Real/checker/guarded endpoints按最小共享前缀诊断。旧生成C排除直接Float逐MAC装箱解释，确见eager双缓存准备；完整producer投入前买到认证hit/miss或FP-only+惰性strong fallback成本证据，不只理论FMA次数。
4. Word方向复用27已有192bit终端与四路word loops，block16/Nat替代只按新机制与实际guard覆盖留存；B独立数学审查D07 reciprocal，避免重复派发。模/进位根收到实际goals再定点修，未验大41KB闭包不占主队列。
5. Mixer inline-only来源a74687f8首批已有完整探索，D判定信号不足；不扩展同类属性变体。它不反驳packed/FP/归一化等不同机制。

冠军报告与live board配置哈希不同、所有current源码private。现任ID可验证，实际比较需要功能政策归约或复制明确报告配置并标INFERRED；否则当前冠军倍数UNKNOWN。父target-chain review和COMPARISON-POLICY已记录，不往新quick数据贴旧配置hash。内部前任桥可辅助选路，不能改称现任或宣称晋升。

资源投入调整依据：约7%的报告链规划改善可能跨过归一化近邻目标，而从旧慢起点重建需倍数改善；因此先给完整候选闭环和独立表示成本。原60/20/15/5为初配计划，实际token/cache/CPU没有读数，全部UNKNOWN；不把源文件字节或未编译引理数量当成果。Droot唯一Git/公共CI，1在途；R3Astra+ D2达到5子agent，无Pro/嵌套agent。

后续22:15完整证明/模型里程碑，23:20冻结，00:00停新长实验；开发冻结时研究侧隔离后续、不拿确认数据选新源，持续实质研究至共同截止。初始spawn后全树严格文件，阻塞/结束亦禁止直接消息/followup/interrupt。
