# FloatLib 数学结论

截至 2026-10-22，统一整理 R1–R5 已有结论及 E 盘 12 份研究交付。四项性能与冠军见[看板](../../../dashboard.md)，当前候选选择见[开发状态](../coordination/development-status.json)。

**已建立原生算术、精确解码、有序累加、机器字索引及矩阵按行输出的证明链；矩阵仍是主要优化方向。** 当前完整包为 [f01-d5-stream-pack][K]，四次完整验收通过；仍未取代冠军。

| 运算 | 已可复用的结论 | 当前使用方式 |
|---|---|---|
| 加法 | raw 指数字段可证明输入有限；精确数值解码等于原转换；有限原生加法连接正式规格 | 指数守卫＋内联转换＋特殊值软件回退 |
| 乘法 | 原生乘法的模型桥成立；低尺度舍入可等价省略最高位搜索 | 原生路径与低尺度软件路径组合 |
| 求和 | 最终结果有限可反推各步所需有限性；原序累加与软件 fold 相等；机器字循环与 Nat 循环等价 | 原生累加器＋精确转换＋USize 索引 |
| 矩阵乘法 | 多 lane 投影等于各自原序点积；合法地址与机器字边界可证明；行序展平与原平坦输出相等 | 十列打包＋有界读取＋逐行计算和输出 |

资料入口：[12 包原文与源码](materials/20261022/README.md) · [118 份候选及实际回执](results/CANDIDATES.md) · [逐定理行号与哈希](results/candidate-catalog.json)。原包中的历史 NOT_RUN、失败和作者判断保持原文；以下状态依据后续回执归并。

## 1. 已通过完整候选验证的证明组件

以下 K 指当前完整包，SHA-256 为 `8eb63a2fea39f8c483eb16857cb1dcc35ac4a30168ab91046a48aa1cb561e045`。其四次完整回执为 39766391628、39767698381、39769247640、39770153343，后者为冻结后的独立确认。固定 Lean、FloatLib、官方源及审计入口见[本轮汇总][R5]。这里只整理已有证据，本次未重跑 Lean。

| 编号 | 数学结论与必要条件 | 可复用声明／精确源码 |
|---|---|---|
| M01 | 原始指数字段不是 255 ⇒ 转换后的原生值有限；有限性排除了非规范 NaN 往返问题 | K：`WordFinite.nativeFiniteOfExp`、`GuardBridge.finiteRoundtrip` |
| M02 | 对有限输入，原生 Float32 加法连接 ExecFloat 规格；非有限输入用原软件运算 | K：`Submission.add_spec`；公开 FloatLib 加法桥的归属保留于源码 |
| M03 | 原生乘法通过目标指数、精确模型及表示桥连接规格，涵盖有符号零与舍入分支 | K：`NativeBridge.modelMulFinite`、`toModelNativeMul`、`ofFloat32Mul`、`nativeMul_spec` |
| M04 | `product < 2^48 ∧ scale ≤ 123` 时，低尺度 rounder 与通用 `roundP` 相等；带守卫选择器对所有输入等价 | K：`LowScale.roundLow_eq`、`roundSelect_eq`、`mul_spec`；不能删掉乘积和尺度前提 |
| M05 | 令 `a=u & 0x7fffffff`，UInt32 回卷条件 `(a−1 ≥ 0x0bffffff) ∧ a<0x7f800000` 恰好接纳 ±0 或指数 24..254 的 normal | K：`R2W01b.wrap_gate_iff`、`fastOK_iff`、`magnitude_zero_iff` |
| M06 | 在上述 normal 域，整数尾数乘精确二次幂恢复原位型；零分支保留符号，域外回到原 `ofBits`，因此组合转换对全部 UInt32 相等 | K：`R2W01c.normal_eq`、`normal_bits`、`convert_eq`、`foldl_convert_eq`；R2-W01c 原稿经集成修复后进入此包 |
| M07 | 原生加法或乘法的结果有限 ⇒ 两个操作数有限，包括零；Inf×0、NaN 和溢出结果不能通过终点守卫 | K：`FinalFinite.add_finite_inputs`、`mul_finite_inputs` |
| M08 | 对从 +0 开始、原顺序逐项舍入的 sum，以及每步先 mul 后 add 的 dot，最终有限性可支撑回溯归纳；否则由原始 Binary32 输入重算 | K：`NativeFinal.sumLoop_eq`、`dotLoop_eq`、`dot_eq`、`originalSum_spec` |
| M09 | 机器字循环在不回卷与数组界条件下等于 Nat 循环；不满足准入时保留 Nat 路径，因此支持任意自然数维度 | K：`Packed10Index.stepNat`、`loop_eq`、`within_eq`、`runDot_eq`；sum 的 `NativeDecodeSumWord.run_eq` |
| M10 | 从矩阵 shape、合法 batch/row 与 `nativeA.size < USize.size` 可推出每行的长度、基址和末地址界；空输出、n=0 分支另处理 | [f01-d4-global8](../candidates/f01-d4-global8/Kernel.lean)，精确 SHA `f139bc8c…c6ef`；[501 完整结果](../candidates/f01-d4-global8/window2h-20261022/summary.json)。旧 manifest 的 NOT_RUN 不代表最后结果；当前 K 未采用这一整体守卫版本 |
| M11 | 打包后任意有效 lane 的 B 读取等于原 B 地址，尾块填充不影响有效 lane；十条累加链各自投影等于原序点积 | K：`Packed10.packB_lane`、`lane_update`、`dot10_lane`、`finish_dot10_lane_fold` |
| M12 | `q` 的商余数解码及 packB 的直接索引均有真实边界证明；可外提地址运算、去除重复运行时边界分支 | K：`Packed10.decode_bounds`、`packB_get`；不得把 Vector 长度等式直接当成元素等式 |
| M13 | 给定任意 tiles，按 batch/row 生成并展平的整个输出向量等于原 flat-q 构造；再把行号展平成 `b*m+i`，逐行计算与消费 tiles 仍等价 | K：`RowOutput.output_eq`、`core_eq`、`RowStream.core_eq`、最终 `bmm_spec`；包括零维及一般形状 |
| M14 | 两行四列／两行八列的低高投影、地址映射及各 lane 回退可分别连接原点积，不改变每条链的舍入顺序 | [2×4 源码](../candidates/f01-r4-tile2x4/Kernel.lean)、[2×8 源码](../candidates/f01-r4-tile2x8/Kernel.lean)，[完整验证与负结果][R4] |
| M15 | Float32→Float→Float32 可用逐元素 raw-word 运行时比较建立本次存储读取等式，无须假设 opaque 转换的一般数值往返定理 | [checked FloatArray](../candidates/f01-d2-checked-floatarray/Kernel.lean)、[39663131701 验收索引](../candidates/f01-d2-checked-floatarray/manifest.json)。单遍 prepare 是另一个尚未完成验收的版本 |

全输入义务仍包括 NaN payload、Inf、次正规数、±0 与指定舍入顺序。**FMA、重排浮点求和、忽略零符号、仅比较实数值均不能替代这些等式。** 原生解码等于 `Float32.ofBits`，也不等于保留所有原始 NaN payload；精确回退须保留原始字。

## 2. 已提取、尚未形成正式验证组件的数学储备

| 编号 | 结论／适用条件 | 当前证据及决定 |
|---|---|---|
| T01 | 固定 ULP 的 RN-even 单步映射 `f_r(k)=R(k+r)` 的任意有序组合可表示为 `F(k)=k+d[k mod 2]` | [R2-W01 数学审查][W01M]：纸面推导＋有限整数模型，Lean 未运行；PARK |
| T02 | 前块 A 后块 B，令 `t=(p+dA[p]) mod 2`，则 `dBA[p]=dA[p]+dB[t]`；这是函数复合，结合但不可交换 | 同上；不允许把浮点部分和重新相加 |
| T03 | 两个出口位移及两组前缀 min/max 共六个整数即可组合整块安全证书；内部 normal binade 的简单充分界为 `k+min≥L+1`、`k+max≤U`，其中 L=2^23、U=2^24 | 同上；普通内部 binade 为 −125≤e≤126，端部与符号另处理；只查最终值不足够 |
| T04 | 同向非负块可用单调性把前缀检查缩为终点；奇尾数且指数差≥2 排除 midpoint，此时各项独立整数增量可结合 | 同上；累计的是 `ΣR(x_j/q)`，一般不是 `R(Σx_j/q)` |
| T05 | 在正 binade 下端 H、非负足够小输入及无中点条件下，`bits(RN32(H+x))−bits(H)` 可给出独立整数增量 | 同上；包含守卫、回退和重放的 C 代理仍慢，最佳所报比值 2.279×；保留数学，不继续该标量实现 |
| T06 | normal 精确值为 `(-1)^s (2^23+f)·2^(E−150)`；E=1..23 的因子虽为次正规数，乘积也可精确恢复 normal | [R2-W03 报告][W03]是更广数学推导；当前已验转换只对 24..254 走快路，其余回退；不能把扩大域当成已验优化 |
| T07 | 单遍 checked prepare 的 `out.size=k`、已处理内容等价、终止长度与越界正零不变量可支持去除重复 encode | [R2-W04][W04]有完整证明尝试；原包 Lean 未运行，后续不能继承双遍父本通过状态 |
| T08 | 奇数 m 的最后 batch 第二行起点恰为 A.size；两行完整 span 准入必须拒绝该 tile。跨到下一 batch 的未观察 lane 仅在独立链、有效输出映射和独立回退条件下不污染有效值 | [R4-W01][W4]的地址引理／17 个解析见证；网页辅助稿自身 NOT_RUN，与 M14 的实际候选验收分开 |
| T09 | 可用一次 `toBits` 同时判断 finite 并构造结果，目标为 `v.isFinite = finiteBits(v.toBits)` | [R5-W02][W52]原稿及首次修复实际 statement 失败；组合修复又被 `#spec` 策略拒绝。尚无通过的该桥 |

R2-W03b 另有 34 条定理组成的 [unpacked-rounding 替代证明草稿][W03b]，保持 `WRITTEN_NOT_RUN`；已有 M06 的 Model 见证路线完成集成，不重复把两稿算成两项已验证成果。

## 3. 反例与不再重复的路线

| 路线／假设 | 已知结果 | 复用时的限制 |
|---|---|---|
| 只看块终点仍在 binade 就可合并 | [W01 反例][W01M]否定：混合符号可先越界再返回 | 必须保留前缀安全证书；下边界 L 的较密浮点格也要处理 |
| 固定锚点能自动消除 midpoint | W01 反例否定 | 需要奇尾数／指数差条件或双 parity 摘要 |
| 官方 ReLU 的零随机分布 | [W01b][W01b]确认固定 LCG 最低位交替，+0 与正 normal 严格交替 | 随机 50% 零的代理收益不能直接转用 |
| 无表转换必然更快 | W03 的 wide 两常量变体在扩大输入后明显退化 | 保留表方案及完整调用验证；C 代理不等于 Lean 性能 |
| 更宽微块／更多行一定更快 | 2×4 完整通过但约慢 9%；2×8 约慢 0.6%；显式双步展开约慢 4% | 实际诊断已出现 SIMD，不能把退化解释为“没有向量化” |
| 矩阵统一采用数值解码 | R5 完整通过，同批约慢 2.3% | 标量有效组件不自动适合矩阵准备路径 |
| UInt8 lane／延迟回退地址 | 各自完整通过，约 0.13%／0.38% 差异，不采用 | 静态操作数减少不等于稳定速度收益 |
| 矩阵改善等于整包改善 | stream-pack 同批 BMM 少 22.9%，该批整包反而约慢 2% | 保留分项与整包结果，组件收益不相加 |
| 阶段诊断 output 占比≈99% | 609 混合 13 次调用，含不计分 raw 软件回退 | 正式计分类的阶段占比仍 UNKNOWN；607 零工作量诊断无效 |

反例、失败源、慢样本和原始回执都保留在来源包及 [R4][R4]、[R5][R5]；没有用后来的修复覆盖早期失败。

## 4. 下一次可直接承接的缺口

1. **矩阵优先**：从当前已通过的 stream-pack 出发，先把正式计分类与 raw 回退的准备、点积、输出成本分开测清。
2. **单次位转换桥**：最小未运行修复是使用 `BitVec.allOnes spec.exponentBits`，先验证小引理及固定 policy，再接入真正被调用的 finish 并验收整个新包。[精确失败与修复线索](astra-collab-20261022-r5/checkpoint-10-policy-alert.md)。
3. **复用而非重新寻找**：需要转换、机器字循环或行布局证明时直接使用 M05–M13；全局边界与 checked prepare 保留为不同实现的可选组件，采用前重新比较完整调用成本。

## 5. 资料完整性

本次归档保留 12 个原包的 376 个普通文件、364 条包内 SHA-256 校验、12 份报告及一份附加校验清单的映射。来源、成员长度、SHA-256、CRC 与对应磁盘位置见 [manifest.json](materials/20261022/manifest.json)。原始许可证及作者归属随源码保存。压缩包清理结果见[清理回执](materials/20261022/cleanup-receipt.json)。

归档校验可复跑：`python competitions/floatlib/scripts/archive_research.py verify --git`。候选索引按冻结源码 SHA 匹配 CI 中保存的 candidate manifest 与 verdict；保留完整通过、仅编译、失败、未找到匹配回执四类，历史原文不改写。

[K]: ../candidates/f01-d5-stream-pack/Kernel.lean
[R4]: astra-collab-20261022-r4/checkpoint-04-final.md
[R5]: ../candidates/f01-d5-costsplit/window90m-20261022/README.md
[W01M]: materials/20261022/R2-W01/appendices/math_findings.md
[W01b]: materials/20261022/R2-W01b/FloatLib_R2-W01b_report.md
[W03]: materials/20261022/R2-W03/FloatLib-R2-W03/R2-W03-report.md
[W03b]: materials/20261022/R2-W03b/FloatLib-R2-W03b/R2-W03b-report.md
[W04]: materials/20261022/R2-W04/R2-W04/R2-W04.md
[W4]: materials/20261022/R4-W01/FloatLib_R4-W01/FloatLib_R4-W01_Report_zh.md
[W52]: materials/20261022/R5-W02/FloatLib_R5-W02_FiniteBits/FloatLib_R5-W02_Report_zh.md
