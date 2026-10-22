# Dot 原输入非 NaN 冷扫描准备

已写 [dot-nonnan-scan-block.lean](dot-nonnan-scan-block.lean)，**3526 字节、107 行，6 个新声明全部 NOT_RUN**。该片段只给实际读取范围的扫描与证明接口；未生成候选、未接入运行路径、未修改 R/sum，也未操作 Git/CI/上传。详细用例、依赖字节哈希和静态回执见 [JSON](dot-nonnan-scan-design.json)。

工作从 2026-10-22 22:54:38 UTC 开始，预算 40 分钟，截止 23:34:38 UTC。基底是精确 [ad014 全局上下文](../f01-d7-nan-choice-probe/Kernel.lean)：`ad014e0b1cdc6e42d3a9bd9437e32762d840b8047be740dca8894b0108aa3cb9` / 162660 字节。既有 `DWordNaN` 片段哈希 `584ace54…fd4c93c` 与其末尾字节完全相符，依赖本身仍 NOT_RUN。新模块应放在这个全局块之后、任何 Submission 命名空间之外；片段不含独立加载命令。

## 实现与接口

`DDotNonNaNScan.loop n baseA baseB p A B k` 先检查 `k<n`。若不成立返回 true；否则检查 `A.getD (baseA+k) posZero` 的 `raw.1`，命中 raw NaN 立即 false；A 通过后，再检查 `B.getD (baseB+k*p) posZero`，命中立即 false；两者通过才递归到 k+1。只使用实际 `DWordNaN.rawNaN`，不是抽象判据参数。`whole` 从 k=0 开始。

| 声明 | 行 | 精确用途 | 状态 |
|---|---:|---|---|
| `loop` | 8 | 上述 Nat 短路扫描，`termination_by n-k` | NOT_RUN |
| `loop_true_iff` | 18 | loop=true 当且仅当所有 `k≤i<n` 的两项原始 word 判据均 false | NOT_RUN |
| `whole` | 69 | k=0 的入口 | NOT_RUN |
| `whole_true_iff` | 73 | whole=true 当且仅当所有 `k:Fin n` 的两项判据均 false | NOT_RUN |
| `whole_raw_nonNaN` | 87 | 上一等价式的正向，供 D 接语义桥 | NOT_RUN |
| `whole_model_nonNaN` | 95 | 逐项用 `DWordNaN.rawNaN_eq`，得到实际 `Model.NativeBinary32.ofUInt32` 的 isNaN=false | NOT_RUN |

`loop_true_iff` 在 A/B 失败分支，用 i=k 与区间后件矛盾；通过分支递归到 k+1，并将 i=k 与 i>k 分开。k≥n 时区间为空。定义及证明的严格递减目标均是 n-(k+1)<n-k，递归前提为 k<n，交由既有上下文的 omega 处理。新 Lean 未执行，不能把这份证明文本当作通过回执。

## 必须保留的范围

- 地址与 [60f NativeFinal.dotLoop](../f01-d7-direct-nonnan/Kernel.lean) L2690–2697 一致：A 为 `baseA+k`，B 为 `baseB+k*p`；B 的 stride 没有改成连续区间。
- 全部参数为 Nat。n/base/stride 无字长约束；p=0、n=0、k≥n、任意大 Nat 地址及越界 +0 默认均保留。没有引入 USize。
- n=0 或 k≥n 时返回 true，不读数组。任意起点 k 的定理只覆盖 [k,n)，`whole` 才覆盖从零开始的完整 dot 输入。
- Inf、±0、次正规数均可通过；未读 storage、另一 B 列里的 NaN 不影响结果。原始输入通过不代表乘积／accumulator 非 NaN，例如默认 +0 与 Inf 可形成 invalid。
- 模块没有 accumulator、输出值或 canonical 结论；不引用尚未存在的 R 新引理。`whole_model_nonNaN` 只到请求的 word→NativeBinary32 Model 分类层，最终 carrier/原规格语义闭合由 D 与 R 后续组合。

D 后续只在实际 native 终点 NaN 冷路调用 `whole`；false 保留原精确 fallback，true 分支须等待真实语义桥再接返回。可能的 D 接入位置为 60f `NativeFinal.dot` L2735–2745 与 `Packed10.finish` L2984–3006，仍须核各输出 lane 的原始地址；本任务没有实现这些改动。普通非 NaN 路径未加入扫描。

## 已做的有限检查与未做项

20 个定向 Python 地址模型用例全部符合预期和独立区间全称检查，未随机枚举。覆盖 n=0、k=n/k>n、A 先失败不读 B、B 失败不读下一项、B stride 2/3、p=0、非零 base、未读 NaN、越界默认、短缓冲、超过 64 位的 Nat 地址、Inf/±0/次正规数。该模型只转录字段分类及读取地址，不执行 Lean、不执行 Model 桥、不做浮点运算，也不能证明新声明。

新块按保存的原版 gate `1eb74ef7…4d27194` 的原正则检查：包括注释在内无禁用 token；每个 def/theorem 前均有 NOT_RUN 标记，片段没有独立加载命令。这里只是片段静态检查，**不等同整个候选 policy、编译、原义务或完整 gate**。

静态未找到确定的 API 阻塞：所有外部接口都来自现有 ad014、ContractTensor 及其现用库；本机没有 Lean 可执行文件。第一次外部检查应先编译精确上下文和片段，重点核递归定理的分支化、两个终止义务及 `rawNaN_eq` 的依赖；再由 D 组合 R 的独立语义桥。生成 C/asm、真实调用的扫描成本、完整配对计时和独立确认均 NOT_RUN / UNKNOWN。

