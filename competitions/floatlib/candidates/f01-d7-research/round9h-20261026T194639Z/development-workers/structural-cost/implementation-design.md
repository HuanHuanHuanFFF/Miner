# 可实现结构路线：B2原始A机器字循环，范围检查在output一次完成

状态：UNCOMPILED_DRAFT。本文件只支持实现/投入决定，不能作为正确性、MainFull成本或提速回执。正式集成仍由D在候选目录进行，编译和完整gate只用标准公共runner。

## 决定与完整成本边界

推荐先筛`Kernel-hoisted-b2.draft.lean`，SHA `9f7f96d71c153681c6a2500fd229e0627cd2ea38a3ad375afdeee25a1657eee1`，234277B，距256000B上限21723B。它与精确保留622d的差异都在`Submission.R15PackedB2`内；加/乘/求和、原B2准备、原group/row、分派、finish和raw replay保持原文。来源和构建方式见`build_hoisted_b2_draft.py`、`hoisted-draft-manifest.json`。备用的最少改动版本`Kernel-indexed-b2.draft.lean`/bae4a96d需要每组四项范围检查，只有诊断价值，不建议与hoisted版本并排占完整发现预算。

保留B2三组完整计时中，BMM占整包16.142%/20.023%/19.058%；仅BMM加速2倍最多给8.071%/10.011%/9.529%。整包10%要求BMM降低61.950%/49.943%/52.472%。新方案实际阶段占比、机器级降耗和可达收益均UNKNOWN；没有可支持10%的强预测。它值得低成本筛选，是因为能消除已核实的热索引/默认分支且不引入A面板、tiles或新的数据准备分配。

完整路径为`bmm`原underflow扫描 → `R15PackedB2.dispatch`原shape guard → output原packB一次 → row/group → 新wordLoop → 原F2 → 原emit每个有效列调用`Packed10.finish` → 非NaN转换或`R7NaNReplay.replayEarly`。准备B、原始A转换、数值乘加、终态F2、输出push、raw finish和NaN回放全部计时。当前源5848行已包含p≤8连续输出分派；不能再以旧DeepSeek guard改动声称本轮新机制。

## 精确改动与证明复用

| 范围 | 运行改动 | 接回旧义务的方法 |
|---|---|---|
| `Indexed.wordLoop` | A和B2用安全uget；k与baseA用USize；每步仍先mul再add，两条独立相同顺序链 | `wordLoop_eq`对任意初始s0/s1回到旧`R15PackedB2.loop`；直接照已有`Packed10Index.loop_eq`模式 |
| `Indexed.within` | 把n/baseA转机器字并从+0启动；没有运行分支 | `within_eq`复用wordLoop_eq和已有USize往返/步进定理 |
| `Indexed.rowDot` | 接受已知有效行，运行体只调用within；边界和n范围全部是擦除证明 | `row_last_lt`由`(r+1)*n ≤ batch*m*n`推出；`rowDot_eq`回到原行baseA的旧loop |
| `groupWithin`/`rowWithin` | 与旧group/row相同准备、地址、尾列和输出，只替换数值loop入口 | 两条等式回到**任意packedB**的旧group/row；不新增IEEE引理 |
| `output` | 在原packB后只检查一次`0<n ∧ A.size<USize.size`；不满足就走旧row | output_eq先用rowWithin_eq，再旧row_eq；output_prefix/core_eq_reference/dispatch_spec/bmm_spec继续接原链 |

新增8条显式helper根见manifest；需要普通Lean检查、逐根重放和完整允许公理检查。具体为`Indexed.ugetA_getD`、`Indexed.ugetB_get`、`Indexed.wordLoop_eq`、`Indexed.within_eq`、`Indexed.row_last_lt`、`Indexed.rowDot_eq`、`groupWithin_eq`、`rowWithin_eq`。旧四公开spec即使通过，也不冒充新增未被收集helper的显式审计。原证明可信度不转移给这份草稿；本机未运行Lean。

## 为什么提升guard

完整旧计划按shape路由的条件事件（假设underflow未命中）为：

| 组 | B2组数 | k步数 | 平均n | 新全局guard次数上界 |
|---|---:|---:|---:|---:|
| D40168687803 |144332|682982|4.732|9次输出入口 |
| A40169957447 |117264|808548|6.895|12次输出入口 |
| B40171180249 |94416|1108785|11.744|14次输出入口 |

这些是一次计划逻辑执行的源级事件，非25轮动态计数、非CPU时间。若用通用runDot每组做4项guard，旧短n入口的额外成本风险很大。因此推荐版本把两项guard提升到output一次，而不是依靠编译器自动外提。zero维、n=0、超机器范围以及A.size恰等于USize.size都有保留路径；ASize为0但n>0时可进入空fast fold，行函数没有可调用索引。

## 精确代码生成判别

1. 先绑定内层精确Kernel SHA与原始C索引；核MainFull闭包仍指向`Submission_bmm`并送入两原bench入口。外层carrier、未选中的helper、诊断caller以及诊断ASM均不能替代这条路径。
2. 从bmm→B2 dispatch→output的fast分支跟到`Indexed.wordLoop`实际C。预期热分支只有两次borrowed uget、原始A的一个UInt32取值及`Float32.ofBits`、两个B2字段、两组原mul/add、机器字比较/加法；无Nat运算、A.size/getD/default分支、每步RC/分配/apply。F2仍应只在终态分配8B payload。
3. global guard只在output，不能在group/wordLoop重新做；原packB仅一次，不能出现全局/逐行A.map、面板、tile数组或按输出重建B。无新增数据容器是源码事实；编译器是否新增闭包/装箱仍待实际C确认。
4. 原packB和原finish/emitter的选中C应与旧版按SSA规范化后一致；正确原字基址、奇p尾列、每个有效输出的finish都保留。旧B2 loop作为fallback仍会出现在模块，不能仅按全模块grep判断是否错误选路。
5. 若实际C未消除目标工作，停止完整计时并记录具体反证；若C符合，才由D决定原完整发现组。真实首次D不达标后不换seed重置；达标再冻结两组新runner确认，原验收不降。

`lean_nat_add`在旧C的站点不等于每k两个外部函数调用；小Nat可能内联，机器码实际节省UNKNOWN。原`Float32.ofBits`转换和潜在调用/累加器保存也完全保留，本方案不能声称移除了转换或spill。已有B2 ASM是诊断对象，未用其推导MainFull周期。

## 覆盖与另一具体选择

`route-coverage.json`按精确622d的所有旧shape分派复算：B2之外仍有B1 raw-A Nat循环（D/A/B为3/1/2个shape，条件平均n=74/132/399）和Direct raw-AB Nat循环（12/10/12个shape，条件平均n=5.89/2.25/3.05）。将同一个**全局范围守卫＋合法地址证明＋安全uget**应用到现有DirectContinuous/NativeFinal.dotLoop或p1 B缓存，不改变其guard，是具体可检验的扩展，而非重开p≤8分派。B1触及class的整包上界仅4.218%/3.923%/1.613%，单独不能支持10%，在旧B组甚至不能支持3%；Direct目标时间仍UNKNOWN。

宽p>8/n>4的F10路径本来已有`Packed10Index`机器字循环，不能把本方案收益套给它。旧R18保留的TemporalCore四k打包是另一数据布局原型，减少B记录而保留每k A转换；此前没有阶段占比或完整性能证据。本轮不把它包装成新发现。R16 A4B2已测负结果、R9原生NaN事件回放完整负结果及R18数值MUL/ADD负结果均继续有效。

## 本次验证边界

`validation.json`核对精确源delta、字节帽、单导入与信任关键字，并在人工16/256字长上检查536个fast shape、264个fallback shape、12647行地址步骤及12371通用guard步骤。它只排除这些有限地址模型中的明显错误。Lean/typecheck/重放/公理/原完整gate/MainFull新C/新ASM/新计时全部NOT_RUN。此次没有CI或本地编译，没有修改主候选或他人文件。
