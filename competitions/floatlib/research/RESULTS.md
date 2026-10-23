# FloatLib 数学结论

截至 2026-10-22，统一整理 R1–R6 已有结论、12份历史归档与R6新增4份研究交付。四项性能与冠军见[看板](../../../dashboard.md)，当前候选选择见[开发状态](../coordination/development-status.json)。

**已建立原生算术、精确解码、有序累加、机器字索引及矩阵按行输出的证明链；后续按“耗时占比 × 可实现降耗”，结合开发和验证成本选择具体路线。** R7当前保留[直接点积＋非NaN完整包](../candidates/f01-d7-direct-nonnan/Kernel.lean)，冻结后独立确认通过；Inf、NaN及组合成果见[R7](../candidates/f01-d7-research/README.md)。下表K仍固定指8eb原件，历史证明与失败保持原版。尚未取代冠军，旧份额与冠军倍数不跨suite继承；适用范围见[套件变更](../docs/suite-transition-20261022.md)。

| 运算 | 已可复用的结论 | 当前使用方式 |
|---|---|---|
| 加法 | raw 指数字段可证明输入有限；精确数值解码等于原转换；有限原生加法连接正式规格 | 指数守卫＋内联转换＋特殊值软件回退 |
| 乘法 | 原生乘法的模型桥成立；低尺度舍入可等价省略最高位搜索 | 原生路径与低尺度软件路径组合 |
| 求和 | 最终结果有限可反推各步所需有限性；原序累加与软件 fold 相等；机器字循环与 Nat 循环等价 | 原生累加器＋精确转换＋USize 索引 |
| 矩阵乘法 | 多 lane 投影等于各自原序点积；合法地址与机器字边界可证明；行序展平与原平坦输出相等 | 十列打包＋有界读取＋逐行计算和输出 |

资料入口：[12 包原文与源码](materials/20261022/README.md) · [全部候选及实际回执](results/CANDIDATES.md) · [逐定理行号与哈希](results/candidate-catalog.json)。原包中的历史 NOT_RUN、失败和作者判断保持原文；以下状态依据后续回执归并。

## 1. 已通过完整候选验证的证明组件

以下 K 指当前完整包，SHA-256 为 `8eb63a2fea39f8c483eb16857cb1dcc35ac4a30168ab91046a48aa1cb561e045`。其R5四次完整回执为 39766391628、39767698381、39769247640、39770153343，后者为冻结后的独立确认。固定 Lean、FloatLib、官方源及审计入口见[本轮汇总][R5]。R6新增实际验证见[R6汇总](../candidates/f01-d6-research/summary.json)；旧回执保持原版。

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


| M16 | 对binary32闭宽指数，`v.isFinite = finiteBits(v.toBits)`；一次toBits可同时判断finite和构造返回字，等于原finish | [bits-proof2](../candidates/f01-d6-bits-proof2/Kernel.lean)，fbf2d0c7；705/39789494626完整PASS。通用allOnes及早期policy/statement失败保留；同机BMM约慢0.6%，数学桥保留、运行候选停放 |
| M17 | 单次UInt32回卷区间判断恰好识别指数24..254域，蕴含finite和旧fastOK，可把数值解码与finite守卫融合 | [normal-add-proof1](../candidates/f01-r6-normal-add-proof1/Kernel.lean)，8a0e40fb；706/39791810276完整PASS。旧版完整调用未建立稳定整包优势，新suite待验 |
| M18 | 从原finiteMantissa定义可证乘积<2^48；外层ex+ey<128排除特殊输入，因此可证明删去两处重复运行时守卫 | [web-lowguards](../candidates/f01-r6-web-lowguards/Kernel.lean)，75ddbcff；706完整PASS。逻辑上的乘积/尺度条件仍需证明，不能无条件删除；旧版整包未见稳定收益 |

| M19 | 对product∈[2^46,2^48)，log2只可能为46或47，可按2^47阈值选择；域外回到原搜索，故新整数roundP/core与原规格相等 | [normal-mul-proof1](../candidates/f01-r6-normal-mul-proof1/Kernel.lean)，96865cba；707完整PASS，但整包约慢14%，停放该运行替换 |

| M20 | 对有限normal操作数，指数差≥26可精确返回较大操作数；保留异号二次幂边界和原fallback，TunedAdd规格桥连接原obligation | [absorption26-proof2](../candidates/f01-r6-web-absorption26-proof2/Kernel.lean)，65cd1338；720新版public-v2完整PASS；该样本add约慢7.7%、整包约慢0.4%，保留证明、停放运行路径 |

全输入义务仍包括 NaN payload、Inf、次正规数、±0 与指定舍入顺序。**FMA、重排浮点求和、忽略零符号、仅比较实数值均不能替代这些等式。** 原生解码等于 `Float32.ofBits`，也不等于保留所有原始 NaN payload；精确回退须保留原始字。

### R7：当前原版公开套件实际验证的新增组件

| 编号 | 数学结论与范围 | 精确源与验收 |
|---|---|---|
| M21 | 非NaN原生add/mul连接实际Model/ExecFloat规格，包含Inf；终点非NaN反推各步所需条件，原顺序sum/dot可接受Inf终点而不重算，NaN仍回到原始字 | [nonnan-runtime](../candidates/f01-r7-nonnan-runtime/Kernel.lean)，c7605688；805、807完整PASS；首次运算桥bb199701仅编译阶段，集成接受另计 |
| M22 | binary32乘法结果不会是signaling NaN；quiet NaN可吸收后续所有先乘后加项。因此实际Nat点积回放在quiet NaN时停止，仍逐位等于原fold，涵盖sign/payload及任意长度/地址默认值 | [nan-replay-fullpath](../candidates/f01-r7-nan-replay-fullpath/Kernel.lean)，9a2a05cd；806/808原版public-v2完整PASS；不能套用于含后续原始sNaN的一般sum |
| M23 | 按一般shape n≤4或p≤2选择直接有序点积，旁路全矩阵准备/打包；其余采用原逐行路径。两分支均对全部输入与维度满足同一bmmSpec | [direct-small](../candidates/f01-d7-direct-small/Kernel.lean)，d9a80847；802发现、804冻结新seed新runner确认，806/807再次完整PASS |
| M24 | M21实际终点实现与M23直接点积接口可精确组合；直接分支同样接受Inf，原生/软件顺序与NaN回退均由该组合源码的原obligation重新验收 | [direct-nonnan](../candidates/f01-d7-direct-nonnan/Kernel.lean)，60f74aa4；807发现、809冻结新seed新runner完整确认PASS；性能不由组件成绩相加 |

原始逐项数据与精确verdict从[R7结果](../candidates/f01-d7-research/public-suite-results.json)定位；仅statement或网页自述的后续稿未列作完整组件。R7阶段诊断137次BMM调用已逐一核对，计时/校验/raw分离；[诊断范围与投入决定](../candidates/f01-d7-research/profile-summary.json)保留探针开销异常，不能将finish/回退时间写成纯输出分配或官方阶段份额。

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
| T09 | 一次toBits判断finite并构造结果 | R5历史失败保持原版；R6闭宽修复已完整通过，现归入M16 |
| T10 | 非NaN原始字包含Inf，可精确往返；native add/mul结果非NaN可推出两个输入非NaN | [notnan-probe](../candidates/f01-d6-notnan-probe/Kernel.lean)，dfef26d5；706 statement PASS。该R6探针自身仅数学桥；当时缺的允许Inf操作规格桥已由R7 M21实际完整闭合，不回写R6原件 |
| T11 | quiet NaN并非一般sum的吸收元；后续signaling NaN可优先替换它。dot各乘积已quiet时才有潜在后缀吸收 | [R6原文交接](astra-collab-20261022-r6/checkpoint-09-web-complete.md)：四个原件包已校验。R6当时NaN decode、quiet幂等及mul无signaling桥未闭合；R7 M22已由真实完整gate闭合，R6原始记录仍保留 |

R7数学与代码生成部分已逐项审查17份交付，按实际源码/成功快照/退出码及公理日志整理为[数学储备索引](../candidates/f01-d7-research/math-reserve-index.md)，精确路径及哈希在同名JSON；原包完整性已覆盖19份，低指数缩放专项审查继续。原件均标LOCAL_ONLY，不因网页编译而晋升为本候选完整gate。主要新增承接点如下：

| 编号 | 数学储备及条件 | 现行验收边界 |
|---|---|---|
| T12 | 已有quiet NaN的原始sum前缀之后，只需按原序扫描后续sNaN并取最后quieted word | MR02/W02精确源编译及公理日志闭合；新Nat适配0fe仍NOT_RUN |
| T13 | +0起点的一般sum只要含原始sNaN，完整结果等于最后原始sNaN quiet后的word | MR03/W03；none分支只排除原始sNaN，不能由此决定求和值 |
| T14 | 实际Float32 IEEE BEq中x==x恰好识别非NaN，含Inf/±0/次正规数 | MR04/W04；1f4实际整合尚未完整gate，叶函数codegen不代表整包收益 |
| T15 | add/mul到native的全输入canonical同态及首次NaN事件的实际raw修复 | MR05/W05；不能由投影相等直接恢复原NaN符号/payload，a4映射探针NOT_RUN |
| T16 | 对任意正K，保存真实块起点与前态的失败块完整raw后缀重放满足原sumSpec | MR07/W07源码/日志闭合；不是块和重关联，当前无运行候选或完整成本结果 |
| T17 | 固定K=32的Array Float32 flat/Nat/USize wrappers，对相同任意UInt32 fallback等价 | MR08/W08b后续闭合原gap；仍缺与原raw sumSpec的组合桥，给定fallback值也未证明惰性冷路计算 |
| T18 | 实际逐步mul结果永非sNaN，初项add(+0,product)等于仅把product的raw负零改成正零；其他符号/payload原样保留 | MR10/W10/W10b精确普通编译及218/26项原公理日志已核；完整原单位有policy/依赖体积问题，最小允许适配与n=1整合仍NOT_RUN，性能UNKNOWN |
| T19 | 对任意native参数，ofFloat32无条件保持实际add/mul；exact native image对原序运算闭合，故原始+0及各非NaN读入字允许sum/dot/BMM直接导入native结果，途中和终点可NaN | MR11/W12精确普通编译与269项原公理报告已核；W12c公共宿主另实际验原四spec及41项公理。任意raw初值须保留image条件，4792实际矩阵扫描和3d9单遍sum不继承公共宿主的新Lean或完整gate/收益 |
| T20 | 旧decoder低分支拒绝考虑UInt32幅值减1回绕后仍蕴含finite；任意native前态可与原始非NaN逐步精确相加，首次原始NaN的实际修复必quiet | MR12/W12b成功快照及369项原公理报告已核；3d9的9条新循环/映射/spec定理仍未编译，右quiet与右signaling的原始优先级反例保留 |
| T21 | 原始binary32指数1..23的表乘法解码逐位精确；保留原零/次正规/非有限分支后wrapper对全部UInt32等于旧convert；固定table[118]常量可消除已查局部暖循环once/外部调用/spill | MR14/W13/W13b数学、W14b/c原始代码及W13d同公共源严格前端参数编译/80公理回执已核；指数0排除、NaN不能raw roundtrip。新353d实际USize解码接线Lean/fullgate/C/收益均NOT_RUN；T06既有数学想法不重复当发现 |

MR09另保存了部分应用step在funext补齐参数后再simp的具体修复：精确0e8已普通编译/四原spec/公理PASS，原版fullgate仍待验证。上述数学储备的性能均不由证明存在推出。

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
| C函数大就表示普通热路径也大 | W11实际MainFull mul虽含LowScale，普通路只经过89字节/26指令位置 | 无完整成本依据继续做noinline；对象/机器码形状也不是计时收益 |
| UInt32 boxed wrapper意味着每次堆分配 | W11的ELF64 wrapper实际为tagged immediate，未调用allocator | 官方apply2、候选内部cold backend及准备/IO分配分别审查，不能据此推广整次调用无分配 |

反例、失败源、慢样本和原始回执都保留在来源包及 [R4][R4]、[R5][R5]；没有用后来的修复覆盖早期失败。

## 4. 下一次可直接承接的缺口

2026-10-22 用户确认：**耗时占比 × 可实现的降耗幅度，再考虑开发和验证成本。** 四个运算之间没有固定优先顺序；落后冠军的倍数、当前占比都不能单独决定选路。

对实际受影响的计分类，整包降耗估计为 `Σ(该类耗时占比 × 可实现降耗)`；局部快 s 倍，对应降耗 `1−1/s`。只覆盖部分输入时计入真实命中范围，不重复计算命中率。每条路线先列机制、预期降耗范围及依据、开发／证明／完整验收成本和最小证伪实验；未知收益先做有上限的诊断，不编造成功概率。

以下仅为旧十二类的同源码四次完整结果；新版public-v2须按cell_work加权重测，不沿用此份额。各运算占官方十二类最小耗时之和的中位份额如下；每批都已复算并匹配原 headline ratio。[原始回执及计算](results/optimization-priority.json)。

| 运算 | 当前整包计分耗时占比 | 假设该项单独减少 10% 耗时，对整包的影响 |
|---|---:|---:|
| 乘法 | 52.7% | 约减少 5.3% |
| 加法 | 39.7% | 约减少 4.0% |
| 求和 | 4.9% | 约减少 0.5% |
| 矩阵 | 2.4% | 约减少 0.24% |

右列仅展示相同局部降耗下的敏感性，前提为其他分项不变；不能直接作为路线排名。矩阵若能快 2 倍，整包约减少 1.2%；乘法若只能少 1%，整包约减少 0.53%，此时矩阵收益更大。两种可实现幅度都尚未由新实验建立。四次份额分别取中位数，表中份额之和可能略偏离 100%。

1. **先比较具体路线**：同时允许乘法／加法的算术与转换、求和的有序结构及矩阵的准备／点积／输出方案参与比较；用已有成本、机制和小实验建立可实现降耗，再分配主要预算。当前不预设“乘法→加法”顺序。
2. **收益和成本共同决定投入**：较低占比但可大幅优化的路线可以优先；完整开发、证明、排队、回收与独立确认均计入成本，并考虑可复用成果。0.13%／0.38% 等既有微调继续停放，除非新条件改变收益判断。
3. **新suite成本优先**：M16单转换桥已完整通过但未提速，不再无证据重试。先从新版public-v2真实计分工作量、特殊值/溢出回退及多shape结果选路；T10/T11提供后续精确桥接入口，缺项保持显式。
4. **直接复用既有证明**：转换、机器字循环及行布局使用 M05–M13；全局边界与 checked prepare 按实际收益选择。没有新条件不重复已否定路线；完整 gate 与独立确认保留足够时间。

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
