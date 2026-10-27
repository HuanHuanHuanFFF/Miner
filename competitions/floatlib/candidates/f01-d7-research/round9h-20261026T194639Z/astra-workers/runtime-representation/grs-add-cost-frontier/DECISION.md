# GRS ADD：有可区分的运行机制，尚不支持大proof或性能结论

本20min阶段23:30—23:50UTC；R总续窗至02:28:21，D原窗不变。只交最短运行片段和成本边界，无大Kernel、无CI、无本机Lean。

**历史并未覆盖完全相同的机制，但负结果必须保留。** 精确6bef4c4b旧原型外层把异号全部送回参考，故源码中的异号UInt64.log2死分支没有被那个快路径执行。39575344774是旧参照bench-only，ratio1.096087，含显式证明占位，不能复制为可采用Kernel。R16 f7f实际BENCH_PLAN ADD是lambda2，其accepted C已是一cast＋一toBits、无table/FPadd/mul；全gate后ADD/B2=1.87392仍是实测负面。旧八处重复顺序选择在C层可见，Scalar ASM未采，不能推断实际重复指令或把回归唯一归因于它。

**本次实质差异**是全normal符号/指数差的UInt32 GRS，使T<2^28，接纳旧gap≤7/highN之外的实际输入，并显式一次raw magnitude排序后携带eBig/sign字段；不是新发现数值转换。`Runtime-grs32-add.lean.inc` **1867B，SHA e4833e4e8b41c7fe50cb8dfa91dbd639fc4cc6aa926fb7b5498e4dda1a2be45a**。3个数据定义，原序B2 fallback；无tuple、UInt64、log2、手写RNE、额外FP加乘或表读取。所有新Lean/C/性能仍NOT_RUN。

alignNonzero的唯一调用者给v=8·normalMantissa>0；d<32时mask公式在d0恰为0，保留原v，d≥32明确返回sticky1，未走UInt32模32移位。typed实现模型28,452例与根整数proposal一致，含合法T4/postE1的±minNormal四个顺序/符号见证。它只检查实现边界，不代替根RTO数学或Lean。旧R15已完成draw的来源模型样本中新hit9754/10752，旧R16hit6056；dense1536vs746、ML2048vs1671、paired1989vs1353。新增覆盖是真正判别信息，但这些是未加权频数，不是时间或成功概率。

**完整成本风险仍大：** 新法删B2两次表读/两scale mul/FPadd和一次numeric cast，却增加排序、variable shift/mask/sticky、符号选择、T0与postE判断。toBits仍是固定runtime外部边界；B2 C把它放在返回位置，新法必须在其后计算E/pack并可能fallback，原x/y和eBig/sign可能跨调用存活。这与R16的非尾codec风险同类，不能假定无save/spill。广覆盖不保证抵消这些成本；整包10%按冻结ADD36.56%分配需要ADD耗时约降27.35%，尚无实测依据。

最低代码生成判别：仅在更高优先级证明批次允许时，编译这份具体diagnosticEntry，核一次排序/字段提取、无重复T求值、1cast/1toBits、无Nat/heap/apply热工作、d32保护、非尾codec的真实save/spill和miss ABI。若编译器仍出现f7f式重复选择或相似成本，停，不扩参数网格。若将来只是append到B2，public MainFull仍B2，绝不能把其gate或比值当作新GRS证明/速度。

关键证明缺项由根/数学线持有：排序无借位、一般d的RTO加减归约、T界、低e1/2整除排carry、原Model.add正常分支及字段平移。小T不能继承旧n≥2^23接口；已实际读B2L1452的`R2W01c.uint32_model_eq_roundDyadic`对任意UInt32成立，可作为小T语义起点，但小T字段恢复和postE桥尚未闭合。`history-and-cost.json`绑定原bench、f7f实际选中C及根纸面/模型hash。
