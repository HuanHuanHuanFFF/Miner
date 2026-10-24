# FloatLib 数学结论

资料整理截至 2026-10-25，保留 R1–R6 归档、R11 三份网页交付与后续精确源码验收。四项性能与冠军见[看板](../../../dashboard.md)，当前保留版本及研究候选见[开发状态](../coordination/development-status.json)。

**已建立原生算术、精确解码、有序累加、机器字索引、连续矩阵输出和独立点积链的证明链；按“耗时占比 × 可实现降耗”，结合开发和完整验证成本选路。** 当前保留[R12 df5c 完整包](../candidates/f01-d12-scalar-combined/Kernel.lean)，SHA `df5c61a0ca24a8ef18c0c42d83bdd23466872d3fe8f39dd912e9c347b27fb172`。D/40074431355、A/40083425886、B/40083571000 均通过完整原版 gate 和冻结三组门槛，见[R12 精确验收](../candidates/f01-d7-research/round6h-20261024T051445Z/three-group-verification.json)。冠军相对模型按[原冻结回执](../candidates/f01-d7-research/round6h-20261024T051445Z/retained-estimate-freeze.json)保持；新增同源码控制只扩充原始证据。R13 的四个新候选正确性均通过，但收益未达采用门槛，见[R13 研究记录](../candidates/f01-d7-research/round3h-20261024T112622Z/README.md)。R11/6c、旧41与R10保留为历史对照；下表 K 仍固定指8eb原件。尚未取代冠军，旧份额不跨 suite 继承。

| 运算 | 已可复用的结论 | 当前使用方式 |
|---|---|---|
| 加法 | raw 指数字段可证明输入有限；精确数值解码等于原转换；有限原生加法连接正式规格 | 指数守卫＋内联转换＋特殊值软件回退 |
| 乘法 | 原生乘法的模型桥成立；低尺度舍入可等价省略最高位搜索 | 原生路径与低尺度软件路径组合 |
| 求和 | 最终结果有限可反推各步所需有限性；原序累加与软件 fold 相等；机器字循环与 Nat 循环等价 | 原生累加器＋精确转换＋USize 索引 |
| 矩阵乘法 | 多 lane 投影等于各自原序点积；合法地址与机器字边界可证明；行序展平与原平坦输出相等 | 十列打包＋有界读取＋逐行计算和输出 |

资料入口：[R1–R6 十二包原文与源码](materials/20261022/README.md) · [R11 三份网页交付与提炼](materials/20261024-r11/README.md) · [全部候选及实际回执](results/CANDIDATES.md) · [逐定理行号与哈希](results/candidate-catalog.json)。原包中的历史 NOT_RUN、失败和作者判断保持原文；以下状态依据后续回执归并。

## 1. 已通过完整候选验证的证明组件

以下 K 固定指历史完整包，SHA-256 为 `8eb63a2fea39f8c483eb16857cb1dcc35ac4a30168ab91046a48aa1cb561e045`。其R5四次完整回执为 39766391628、39767698381、39769247640、39770153343，后者为冻结后的独立确认。固定 Lean、FloatLib、官方源及审计入口见[本轮汇总][R5]。R6新增实际验证见[R6汇总](../candidates/f01-d6-research/summary.json)；旧回执保持原版。

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

### R10：精确组合源码的完整验收

| 编号 | 数学结论与范围 | 精确源与验收 |
|---|---|---|
| M25 | 乘积不会是sNaN；仅将精确乘积原字−0改成+0即可恢复原+0种子加法。不能把此等式推广到任意原始sNaN。非NaN原生乘积导入与NaN原字回退可组成n=1内积 | [ff34单项内积](../candidates/f01-r10-bmm-singleton-native/Kernel.lean)，39994377803完整PASS；[复用已优化标量乘法995d](../candidates/f01-d10-bmm-singleton-tuned/Kernel.lean)，39998179051完整PASS。旧53d/47d原件不追认通过 |
| M26 | n=0…4的固定有序乘加链逐项等于原Nat dotLoop，保留初始+0、每次舍入及NaN回放；n≥5直接回原循环 | [d70展开](../candidates/f01-d10-bmm-small-unroll/Kernel.lean)，39994942866完整PASS；该组BMM慢约0.7%，保留证明、停放运行替换 |
| M27 | 按行共享商余数与基地址后，Vector.flatMap的完整输出等于原平坦DirectSmall；包括空输出、n=0和任意Nat维度 | [a066按行寻址](../candidates/f01-d10-bmm-direct-rows/Kernel.lean)，39996680317、40003013355、40003240475三组完整PASS。矩阵快约7.4%/6.5%/10.8%，未据此更换保留版本 |
| M28 | 实际矩阵坐标可构造两数组的strided地址界；机器加乘不回卷与uget=getD连接原Nat循环。入口一次检查可表示范围，超范围回41，因此不删巨大Nat域 | [f278长薄机器索引](../candidates/f01-r10-bmm-longthin-usize/Kernel.lean)，40000561390完整PASS；该组未见净收益，数学组件保留 |
| M29 | 行内外提A的原生转换、预转换B并经total map/getD等式读取，仍等于原n=1乘积、负零归一化及NaN原字回退 | [f448行缓存](../candidates/f01-d10-bmm-singleton-row-cache/Kernel.lean)与[ce683双侧缓存](../candidates/f01-d10-bmm-singleton-double-cache/Kernel.lean)，40000065474均完整PASS。853仅3600个n=1输出且m=1，B缓存分支未触发，不能据该组否定其性能机制 |

本轮经验：发现组先核对目标路径是否实际覆盖；确认组仍须冻结后保持未查看。三组a066的每对输入均改变35个BMM形状，完整生成字段均有变化。新增同源慢控制不能重新校准冠军估值；当前看板以冻结基准和同组参照归一化增量更新。原始失败、慢组及未触发分支的限制均见[R10结果](../candidates/f01-d7-research/round2h-20261023T170031Z/round-results.json)。

### R11：完整调用重构与逐位等价

当前轮证据及最终选择统一从[R11记录](../candidates/f01-d7-research/round7h-20261023T193125Z/README.md)进入；下列验收只绑定所列精确源，不由组件成绩相加推断组合性能。

| 编号 | 数学结论与范围 | 精确源与验收 |
|---|---|---|
| M30 | 数组前缀同时维持长度及所有已写元素等于原平坦输出；逐组只计算一次F10并emit有效尾列，可连续写出而不改变舍入及NaN回放 | [连续writer5b7d926c](../candidates/f01-d11-bmm-fused-output-proof3/Kernel.lean)，40027315361、40032766690完整PASS；精确回执见[R11实现交接](../candidates/f01-d7-research/round7h-20261023T193125Z/review-output-final-math-handoff.md) |
| M31 | 全部原字满足指定小幅值强界时，每个实际binary32乘积均为带符号零；原+0种子的逐步加法因此全为+0。须扫描完整输入，miss仍用原路径 | [下溢证书6a69d6ed](../candidates/f01-d11-bmm-underflow-zero-proof2/Kernel.lean)，40030638967完整PASS；有限尾数、scale及原舍入引理前提均保留，不推广为必要条件 |
| M32 | 四个独立行实例的p=2双列可组织为P12输入与八条独立点积链，各lane仍逐k先乘后加；跨batch地址及尾行按各自原字回放 | [Cross5c5e7071](../candidates/f01-r11-crossrow-p2-pack12-proof2/Kernel.lean)，40030638967、40037152933完整PASS；不是单条浮点归约重排 |
| M33 | 四行十列的40条独立链可逐行投影为原Packed10点积，块内row-major writer及旧尾部拼成原矩阵；每条链保留+0、k顺序和终点精确回退 | [actualWide28b81912](../candidates/f01-r11-wide4-inline-proof3/Kernel.lean)，40043628421 statement、40044330511完整PASS；该源使用原Array Float32四基址，不能据此认定F4面板版本已闭合 |
| M34 | 先按batch再按row遍历，与原flattened-row输出逐项相等，可用batch基址与行偏移替代逐行商余数；空维度与巨大Nat域仍由总定义覆盖 | [batch-row ad323bf0](../candidates/f01-d11-bmm-direct-batch-rows-proof2/Kernel.lean)，40042916169完整PASS；原1c54仅证明失败，不改写为已通过 |

[931真实机器码](../candidates/f01-d7-research/round7h-20261023T193125Z/review-panel-codegen-931.md)另确认未接入的Panel4 helper以一个F4读取四行、十组SIMD乘加，热回边无调用、栈访问或分配；准备阶段仍有四次转换与一次24B对象请求。它没有证明新Panel矩阵入口等价或完整调用提速。

局部尾行的[6e99f707数学资产](../candidates/f01-d11-panel4-tail-proof2/Kernel.lean)在40048163768通过statement：`prepare_read → dot10_shift → runDot_prepared → Prefix`连接局部数值基址与原始回放基址。该新namespace仍未接入实际Panel入口，完整内核重放、公理验收与性能不由此替代。原f767在40047532920的两处失败及旧draft均保留。

真实F4的[0feec56a行投影](../candidates/f01-d11-panel4-projection-proof2/Kernel.lean)在40050615221通过statement：实际packA读取支撑任意40个初始累加器的wordLoop逐行等式，再连接runDot和block；原ec112在40049985877的冗余证明步骤失败保留。[2dc2546f边界桥](../candidates/f01-r11-wide4-guard-proof/Kernel.lean)在40051011135通过statement，给出具体四行块地址界、机器范围及direct-within的Projects。二者均未连接新矩阵入口，不能升级为完整Panel算法或运行收益。

[1b472298尾行因式分解](../candidates/f01-d11-panel4-tail-factored-proof/Kernel.lean)在40051933922通过statement：通过group/row/tail函数等式复用原emitTail_prefix，避免重复Prefix归纳。新资产6165B，仍须保留原2031B tail依赖；相对9283B资产的3118B差额不等于完整组合净节省。实际Panel入口、完整gate及收益仍缺，[依赖与容量交接](../candidates/f01-d7-research/round7h-20261023T193125Z/research-agent-technical-handoff.md)保留缺项。

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

### R12–R13：原字选择、逐块输出和单步行共享

| 编号 | 证明结论与范围 | 精确证据及性能边界 |
|---|---|---|
| M33 | 原字 NaN 选择保持 signaling 优先级、payload 和符号；冷分支复用既有选择证明，普通路径仍由认证的结果守卫连接规格。`nativeMul` 的数值 converter 由全输入 `convert_eq` 接回原转换 | df5c 的 `DWordNaN.selected_add/selected_mul`、`ScalarNaN.add_spec/mul_spec`、`nativeMul_spec`、`mul_spec`；[R12 证明归属与验收](../candidates/f01-d7-research/round6h-20261024T051445Z/astra-r12-conclusions.json)。复用资产不作为新发明 |
| M34 | 对原 p=2 Cross 分支，每组原 `blockRows` 只算一次，八个原字按有效尾行直接推入最终数组；`Prefix` 证明长度和逐元素原序等价，不需要保存全部 W8 后二次遍历 | [3c5e 源码](../candidates/f01-r13-cross-fused-output/Kernel.lean)：`R13CrossFused.emitRow_prefix/emitBlock_prefix/output_prefix/core_eq_reference`。完整 gate PASS，但[发现组](../candidates/f01-d7-research/round3h-20261024T112622Z/result-1324007-f01-r13-cross-fused-output-vs-f01-d12-scalar-combined.json)整包/df5c=1.001426、BMM=1.008952，停放；W8 本身仍存在，不能宣称省去额外 W8 分配 |
| M35 | n=1 时，每行中、列循环外解码一次的 A 值可作为列回调的 unboxed Float32 参数；展开原 `dotLoop 1`，保留原 `+0 + fa*fb`、结果守卫和 raw replay。行等式可运输到原连续输出前缀及完整规格 | [8661 源码](../candidates/f01-r13-n1-prepared-row-output/Kernel.lean)：`R13N1Prepared.onePreparedDot_eq/row_eq/output_eq/output_prefix/core_eq_reference`。完整 gate PASS；[发现组](../candidates/f01-d7-research/round3h-20261024T112622Z/result-1324009-f01-r13-n1-prepared-row-output-vs-f01-d12-scalar-combined.json)整包=0.997634、BMM=0.993289，未达0.97门槛；statement-build 生成 C 的审查观察到实际共享参数，最终机器成本与该 C 构建的边界仍分开 |

R13 另两条已证明正确的运行接线也没有净收益：[708 一次性 A/B 转换](../candidates/f01-r13-preparation-convert/Kernel.lean)整包=1.003435、BMM=1.005952；[252b 短点积改用既有 RowStream](../candidates/f01-d13-short-packed/Kernel.lean)整包=1.001618、BMM=1.006563。四条发现组均未达到整包≤0.97，因发现门槛未通过而未进入独立确认，也没有采用或正式提交。3c 的 bootstrap p05 为正0.001656，不能误写为负；其 headline 仍不达标。各结果及原件统一从 R13 入口访问。

运行范围须分开：8661 新路由仅限 `n=1,p>2`；3c 的数学与 dispatch 域为 p=2、包含n=1，但其发现组只有 n=80/91/393/99 的四个 Cross case，没有 n=1 高输出热点。后述三组同源码诊断的高输出 n=1,p=2 只出现在一个输入组，不是3c性能确认，也不能用作替代失败发现组。

**测量经验。** 逐元素探针曾把 RowStream/Cross 示例放大约8.0/4.69倍，排他计时只能避免嵌套重复计数，不能消除探针成本。低频外层探针在 RowStream、DirectContinuous 的整路径约1.009/1.003倍，但 Cross 仍约1.181倍、sum 高 batch 仍显著扰动；阶段比例不能当作可移除收益。多组同源码未插桩 whole 诊断与原版25轮成绩、冻结新输入确认分别保存，不相互替代。

**模型储备，尚未闭合。** [Float64 跨宽审计](../candidates/f01-d7-research/round3h-20261024T112622Z/profile-scalar-wide-summary.md)仍受 `Float.toFloat32` opaque 语义桥阻断，同宽表示桥不足以支持原生跨宽 RNE；不为此自增公理。另有[同宽 Float32 缩放合并调查](../candidates/f01-d7-research/round3h-20261024T112622Z/astra-scale-fusion-feasibility.json)：24×24 整数乘积先做 RN24、再乘合并二次幂，限定两输入均为正规数（原始指数1..254），且指数和174..380；复用表索引 `(s−150)+256*sign`。380的最大结果为0x7f7ffffe，h=46向h=47进位须保留；误扩到173会把非零结果变成零。8852个整数模型检查和纸面归约仅为 INFERRED 储备，缺通用 `roundP` 指数平移及第二乘精确性 Lean 证明，未造新候选、未实测性能。复用 R2 `normal_eq` 时还须约束原输入 E≥24，或补 E1..23 的表示桥。

## 4. 下一次可直接承接的缺口

2026-10-22 用户确认：**耗时占比 × 可实现的降耗幅度，再考虑开发和验证成本。** 四个运算之间没有固定优先顺序；落后冠军的倍数、当前占比都不能单独决定选路。

对实际受影响的计分类，整包降耗估计为 `Σ(该类耗时占比 × 可实现降耗)`；局部快 s 倍，对应降耗 `1−1/s`。只覆盖部分输入时计入真实命中范围，不重复计算命中率。每条路线先列机制、预期降耗范围及依据、开发／证明／完整验收成本和最小证伪实验；未知收益先做有上限的诊断，不编造成功概率。

R13 已补[同一未插桩 df5c binary 的三组已见输入诊断](../candidates/f01-d7-research/round3h-20261024T112622Z/profile-whole-multi-analysis-summary.md)：乘法占34.57%–36.58%，BMM占18.00%–20.69%；这是诊断完整调用的份额，不是官方计分份额。n=1、p>2目标在每组仅一个 case，占 whole 1.223%–1.768%；p=2 Cross 的范围也随输入明显变化。1224091 的一个 add 进程慢37%，已保留，不能把全部变化归因于形状。后续优先评估覆盖较广的乘法缩放合并证明，以及多组 whole 结果支持的 BMM 路线；不靠单个热点或 MAC 数量判断整包收益。

**旧 suite 历史份额（不作当前排序依据）：**

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

R1–R6 归档保留 12 个原包的 376 个普通文件、364 条包内 SHA-256 校验、12 份报告及一份附加校验清单的映射。来源、成员长度、SHA-256、CRC 与对应磁盘位置见 [manifest.json](materials/20261022/manifest.json)。原始许可证及作者归属随源码保存。压缩包清理结果见[清理回执](materials/20261022/cleanup-receipt.json)。

R11 补充归档将 W01 证明审查、W02 稀疏数学、W03 Lean／编译性能三份交付的97份原件（3,119,501字节）纳入当前分支，另附2份项目数学／曝光补充及3份固定版本许可证。[逐文件清单](materials/20261024-r11/manifest.json)保留来源、原包哈希、清理记录与E盘原件映射；[开发承接说明](materials/20261024-r11/RESEARCH_NOTES.md)分开记录网页原始 NOT_RUN、后续精确候选验收及负结果，原件字节不改写。私人会话索引与界面截图未纳入。

R11 资料完整性可复跑：`python competitions/floatlib/research/materials/20261024-r11/verify.py --git --sources`；没有E盘时去掉 `--sources`，仍可验证分支内副本。该核验不执行原件代码、Lean、CI或性能实验。

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

### R9：矩阵证明已闭合、运行替换无收益

- 直接点积可复用全输入数值decoder，同时需要将共享Packed10.dot10_lane沿decoder等式运输；[d5e3512f源码](../candidates/f01-d9-bmm-direct-decode-proof2/Kernel.lean)在834原版完整gate通过，但矩阵慢17.3%、整包慢4.0%，保留证明、停放运行替换。
- 矩阵NaN重放可维持原生前缀，首次NaN事件仅做一次精确原字修复，再利用实际quiet-NaN吸收证明结束；[9244e334源码](../candidates/f01-r9-bmm-native-event-replay-proof2/Kernel.lean)在836原版完整gate通过，但矩阵慢2.2%、整包慢0.8%，不能把证明成立提升为性能收益。
- [R9完整证据及后续缺项](../candidates/f01-d7-research/round1h-20261023T125752Z/README.md)保存原始失败、仅proof修复、原版验收及低指数word乘积的编译诊断边界。
