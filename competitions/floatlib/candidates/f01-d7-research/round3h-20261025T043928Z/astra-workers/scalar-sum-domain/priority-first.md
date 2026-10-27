# R15 首批：标量极低指数和短路优先

2026-10-25 04:51 UTC；当前入口 `status.json`，本稿为首批筛选。

## P1：只在现有低尺度乘法分支内加 `ex+ey≤84` 带符号零短路

旧缺口：df5c 先按 `ex+ey<128` 进入 LowScale，仍读取尾数、构造乘积、计算舍入。R14 全整数 ADD/MUL 已完整正确但回退，本路线不替换原生主路径，不重访失败 D。

本次变化：复用 df5c 内已完整验过的 `UnderflowZero.finiteScale_toNat / rseAny_zero / roundP_zero`，把双侧各自≤43的 BMM 条件改成标量已提取的指数和≤84。指数和不回卷且≤84保证双方 finite、实际 scale和≤84，已有 roundP_zero 对任意 UInt64 product 都成立，因此无新 RNE/偏置/正常乘法证明。返回符号必须为原 `Bool.xor(signBit a)(signBit b)`，不把负零归一化。

真实机会：`domain-screen.json` 对三个已见完整 D 计划每个 mul case 取256个确定性分层样本，共32,256个 scalar 对；共43,703个显式读取，0.422秒，外部5秒上限已执行。源为 Conjectures.io MIT、固定4b7e838的真实 BenchSuite及R14已保存源翻译。当前3组中 cutoff84 与 cutoff100 在 sparse / specials / subnormal 完全相同；区别只在少量随机 dense/extremes，故本窗先买最便宜的84证明。

- mul:sparse：该计分 cell 占 whole 5.89%–6.80%，样本命中29.95%–43.29%。
- mul:subnormal：cell占3.35%–4.18%，样本命中2.25%–76.07%，明显依赖 draw。
- ml/paired未命中，保留现有高分支；新增判断放在 `ex+ey<128` 内，避免给这些主路径加一次动态判断。

这些频率不是可移除时间；不将频率乘整 cell 时间当作测得收益。相关 cell 的全部成本只是宽松上界，单靠本路线能否whole≤.97仍 UNKNOWN。值得先做精确编译与一次完整 D，因为只增几十行新算术证明，主体复用已验 roundP_zero。源草稿与接线预计05:05前完成，首 D 失败即停，不换seed重试。

## P2：sum quiet后缀逆向找最后原始sNaN（暂缓实现）

这不是新发现：MR03已有完整普通编译/公理证据；R7原诊断已说明逆扫描只是后备，原List.reverse版本没有实际性能验收。df5c 当前是首次rawNaN后线性扫描；逆向第一个sNaN可决定后缀结果，找不到必须保留当前quiet累加器，不能全局NaN早停或取第一个sNaN。

本次真实成本筛查：三组计分 `sum:specials` whole占比只有0.178%–0.273%。这不足以单独争取3%，现有前缀/后缀之外输入不保证受益，额外全向量预扫会伤所有非NaN输入。因此本窗不抢占完整runner证明这个小收益路线。保留后续可与矩阵候选组合的严格cold替换机会，不能叠加组件百分比。

## 来源与边界

- `f01-d12-scalar-combined/Kernel.lean`，df5c61a0…，当前精确父源；已有 UnderflowZero 证明与 Native scalar路径。
- FloatLib Team/MIT固定 `0d918257…`，实际 `FixedWord/Core/Runtime.lean` 与 `Arithmetic/Runtime.lean` 已读，不能从通用软件实现存在推出更快。
- Conjectures.io/MIT固定 `4b7e838…`，实际 BenchSuite 源SHA256 `2f167273…`、许可证已读；原始引用在R14 astra-official-bench-index.json。
- 新增所有Lean/完整gate/性能状态均NOT_RUN。只写本子目录，不操作Git/CI/其他会话。
