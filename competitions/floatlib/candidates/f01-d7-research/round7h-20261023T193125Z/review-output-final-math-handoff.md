# R11 输出与数学实现交接

本交接只覆盖Sol实现/维护的连续writer、Direct/batch-row、整矩阵下溢零、BMM classifier、容量构建器和Panel资产。最终采纳、三组确认、正式提交及奖励仍由Root的统一状态与回执决定。下列结论按精确source区分，完整SHA、路径、原summary/verdict hash及数学前提见同名JSON；冻结manifest中的初始NOT_RUN不回写为当时已知。

## 精确实现与真实验收

| 源/字节 | 已回收的最强精确证据 | 数学与运行边界 |
|---|---|---|
| fused writer **5b7d926c**,245841 | 907 statement；**911、916 fullPASS** | packed行/组逐次产生F10，再连续emit有效lane到同一Array |
| compact **f2fa8d10**,236400 | **913 statementPASS** | 机械删除旧P链；不能直接继承5b的独立full计时 |
| DirectContinuous **2aaa5d9e**,248566 | 915 statement；**916、922 fullPASS** | 只替n≤4且p>2，raw dot直接连续写出，无nativeA/packedB |
| batch-row首稿 **1c544655**,251809 | **922 statementFAIL** | Nat.add_mul与succ*m形状不匹配；不是运行反例 |
| batch-row proof2 **ad323bf0**,251810 | **927 fullPASS** | Root仅改succ_mul证明；batch→row双fold消除flattened-row/m |
| whole-array underflow **6a69d6ed**,244896 | 912 statement；**914 fullPASS** | 双Array.all强充分条件，命中直接全+0，否则完整旧路径 |
| terminal classifier **6457ed8f**,237208 | 917 statement；**919 fullPASS** | 仅NativeFinal.dot/Packed10.finish及dot_eq前提转换 |
| official-add fallback **73177f57**,221629 | **919 fullPASS** | 只改native-NaN结果回退/证明，删无引用TunedAdd；净省15513 B |
| combined0655 **0655b266**,254588 | **918 fullPASS** | fused+Direct+Cross+underflow，尚无本轮classifier |
| combined-classifier **6c2d394d**,254654 | **922、929、930 fullPASS** | 0655上精确三处classifier变化；930为首个无observer干净D |
| no-Cross backbone **749bc933**,223584 | **923 statementPASS** | 容量/隔离基座，含official fallback；并非移除Cross提速结论 |
| writer/projection诊断 **ea102356**,244990 | **925 statementPASS** | 泛型writer与投影typecheck；没有把Panel4接进实际BMM |
| Panel4 probe **9a40118e**,229218 | **927、931 fullPASS** | 原749b实际入口不变；新helper定义/终止/packA_get接受，Panel算法未接入 |
| Tail首稿 **f7676313**,238494 | **934 statementFAIL** | 多余dsimp与基址展开证明方向；原9276 B draft没有Lean接受 |
| Tail proof2 **6e99f707**,238501 | **935 statementPASS** | 只修上述两处证明；原9a运行prefix及12个Tail声明不改，kernel replay/axiom/checksum/full/性能仍未验 |

原writer失败稿1b71/2c73、20a与f767等均保留；没有用占位证明或提高资源绕过失败。20a的924失败与ea102的925通过是不同精确源，不能合并。

所有已核public-v2回执绑定官方commit4b7e83841cc0c32c6529f533923c73d33b5ecf97、suite a16494e97c6a073bfd8accf72480c34534c87808092c56074fdcfa42cd34868a；JSON保存各自contract与verifier fingerprint。原gate policy源SHA1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194。931编译trace为Lean4.34.0 commit293d5d0c0c3f3dded4688b3ccd6a33939ac5102b、自带clang/x86_64，原-O3及-ffp-contract=off。没有本地Lean编译或环境选项变化。

## 必须保持的数学前提

**连续writer。** Prefix同时要求当前长度和所有已写元素等于reference point。prefix_push→foldl_inv→emit_prefix→group/row/output前缀，再用抽象prefix_vector_eq_ofFn和独立points_eq_reference闭合原规格；不能重新通过展开整份output做类型转换。每行每g只计算一次F10；尾组emit min10有效lane，不能逐输出重算tile。输入转换、B准备、输出和释放仍在原调用内，终点F10/最终Array也仍有成本。

**Direct与batch-row。** 适用guard仍是n≤4、p>2，n=0/空维度/任意Nat的core证明完整，其他分派保留。当前6c2d实际采用2aaa，ad323尚未并入。ad323以b*m*n和b*n*p为batch基址，行i用baseA0+i*n；没有每行tuple状态。旧row保留为证明目标，使用mul_add_div与add_mul证明同地址，再用内外fold不变式。旧每row只有一次动态除法，64/32位分支二择一，不算两次。没有同场ad323对2aaa的净成本数据，不能把去div直接称为提速。

**Underflow。** raw magnitude<0x16000000等价于这里使用的expField≤43强界，覆盖±0/subnormal/小normal并排除NaN/Inf。finiteScale≤42，双scale和≤84；UInt64有限字界使149-scale≥65的rseAny为0。经FastMul原规格连接实际ExecFloat.mul带符号零，+0加任意带符号零仍+0，归纳原序fold得到全+0。此条件是强充分域，不是所有下溢的必要条件。必须扫描全部原字，不能用类别标签/局部前缀代替；n=0、空shape和hugeNat均接原证明。**组合最外Underflow guard优先，wide只允许替换miss。**

**Classifier。** nonNaN_eq_true_iff作用于有效native Float32结果，不能改成任意raw Binary32字的自等判别。非NaN仍ofFloat32，NaN仍按正确raw A/B基址回放。输入packing、MAC顺序、±0与原字payload路径均未动。旧R7四终点方案未有保留full回执；6457是其当前父本接线。W06中beq本来已static inline，不存在“额外去掉foreign beq”的收益声明。

**容量回退。** 7317有限热路不变，但共享add的NaN回退会影响sum/repair等调用上下文。TunedAdd闭namespace只有两处外部引用、没有global instance/simp泄漏；删除后保留全部来源/许可。它是容量选择，冷分支也须计时。

## 性能证据的适用范围

以下是同一实际CI内各自对reference归一化后的候选/基线比，不是跨source直接配对。除930外都有observer或仅discovery性质，不能叠加组件收益：

| 对照 | whole | BMM | 备注 |
|---|---:|---:|---|
| 911 5b/a066 | .984804 | .921393 | whole收益p05<0，未达到单独晋升口径 |
| 914 6a69/a066 | .949602 | .810615 | 强信号来自该批subnormal整块命中；不是未来分布保证 |
| 916 2aaa/a066 | .963488 | .815550 | 未改sum也约.9207，不能把全部whole差异归给Direct |
| 919 6457/a066 | .997660 | .990885 | 小幅变化，未改sum约1.0326，不能过度解释 |
| 919 7317/a066 | 1.003288 | 1.006013 | mixed小幅代价；不是免费容量或速度提升 |
| 930 6c2d/41 | .916224 | .718057 | 干净D，p05=.064674；仍由Root收齐确认组 |

901/902/904原字重建的underflow hits为1/3/2，MAC份额约3.21%/12.20%/8.30%；原Lean raw数组/实际guard trace未留，状态是deterministic reconstruction INFERRED。每case实际时间缺失，不能把MAC当耗时。固定43、maxScaleSum84及100三域没有新增hit/MAC，所以dynamic max证书保持PARK，避免增加完整扫描和证明。

当前Root新组合e5b279b3在932仅statementPASS，933 full结果与最终三组选择不由本交接提前判断。完整旧wide28b在929通过，属于Array Float32四基址实现；它不证明Panel4.Vector F4的等价。不同组合/种子差异也不能直接归因给classifier或宽内核。

## Panel数学与实际931机器码的边界

依据Luna的review-panel-codegen-931.md/json，9a精确对象4380cf302c94965f44a622f9bba1c11fdc9a6baefea1ebe0897e7af083458613的回边0x1b0–0x262：一个F4指针+一次movups读取四行，十个mulps和十个addps；热call/rsp/分配/新装箱均0。实际出现15个XMM名字，无hot spill，不能复述此前理想12寄存器猜测。

prepare每k仍有4次ofBits和一次24 B F4分配，没有四个临时Float32 box；准备期间确实有栈暂存、Nat/getD、callback及冷路。block先在g外完成panel，之后构造捕获panel的列闭包；64 B准备闭包+48 B列闭包仍有成本。最终panel释放在下块前发生尚UNKNOWN，未捕获Array.ofFn完整销毁/实际连续BMM调用者。931是带observer的unused helper证据，整包Panel降耗UNKNOWN。

Tail数学资产的目标是只准备每batch最后≤3行的rows*n局部Float32数组，numeric base=rTail*n，raw finish base=(b*m+firstTail+rTail)*n。prepare_read→dot10_shift任意10acc→runDot_eq→group/row/tail Prefix均已有源码；f767首次statement失败，修复6e99已在935/run40048163768 statementPASS；这不包含kernel replay、axiom audit、checksum、full gate或新算法/性能接受。**它与已通过的旧global-nativeA emitTail不是同一实现，不能继承925/929。**

F4字段读取与实际packA的连接已在独立ec112投影诊断源补齐源码，但**Lean NOT_RUN**，不能视为证明接受。仍缺：该真实Panel4.wordLoop_row编译接受、具体Projects实例、无global map的buildTiles/output、实际tail入口、hugeNat guard/fallback、source容量闭包、原fullgate和干净whole成本。global map可保留在证明参照或旧fallback，但不能在新Panel快速路径继续执行，否则panel/tail会重复准备。保留F40/projectRow/lane40与原Packed10Index；未来只替旧R11WideRows4机器家族及旧tail/flow，不盲加整份14KB generic writer，精确计划在panel4-tail报告。

## 下一轮试验顺序

按“预期受影响路径降耗×真实时间份额÷工程成本”做定性排序；时间份额和完整降耗尚缺，不能计算收益分数。这里只给两个有当前证据支持的最小方向：

1. **主预算：全m≥4的generalPanel4+localTail真实入口。** 931已确认A聚集载入被移除，完整四行块MAC曝光32.65%–52.23%；仅m%4=0且m≥8的窄guard只有1.13%–16.18%，不足以替代尾部处理。潜在受影响路径较大，优先主预算；工程代价高：先最小statement关闭F4投影与接通已过935 statement的tail，再一份具体入口保持原Underflow/direct/Cross分派，重新查实际caller/生命周期及干净完整调用。若旧global map仍执行、重复prepare、成本抵消收益或需未审核删链，立即PARK。

2. **低成本辅线：ad323对2aaa的同场干净因果对照。** 两源已fullPASS，无新数值定理；潜在改变量是一条每row除法，额外batch层也可能抵消。旧完成样本的short-direct MAC份额4.14%–22.62%，并非时间份额。只测这一对冻结源；若完整成本中性/负面就PARK，不再做地址网格。通过后再考虑接最终确认基线及重新完整gate。 不让一条除法的局部试验挤占GeneralPanel结构主线。

不优先扩大underflow max域、复做numeric decode/tiny-unroll或无瓶颈证据的宽度网格。所有建议只扩展下一轮研究计划，不改变本轮冻结source或采纳结论。


935新证据快照：source6e99f707a6dff0d4656731a38851d426198dd8244bacc139ba133750e45c4d6e/238501 B；verdict90157372422f0be1876ec5f246cefb51dc38d312a36b26d9df5fea68acd836dc，原始路径与summary哈希见JSON。初始manifest的NOT_RUN保持原字节，934失败源和原draft保留。


后续独立投影资产ec11262306db740f79a51af22a13230963fdc9ac9e77a99e45fcb9a07dfe7d4e/235266 B，仅把9a真实Vector F4循环的packA_read→wordLoop_row→runDot_row/block_row及projectRow依赖打包；asset851736a0/6048 B。全部Lean/full仍NOT_RUN；Astra两份donor、唯一proof语法变化和exact9a逆向在独立manifest/builder中记录。不会追写9a/6e99或本轮final cohort。
