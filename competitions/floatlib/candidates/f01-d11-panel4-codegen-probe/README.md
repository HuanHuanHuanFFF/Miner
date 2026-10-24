# Panel4：唯一未接入的表示/codegen 探针

冻结源 `9a40118eae28c92c1abeca7f6a141fb0fbfe963cbf40321681b8013782f9f7ac`，229218 B；父本749b的223584 B完整前缀保持原字节，实际add/mul/sum/bmm及四spec没有调用本探针。它不是新矩阵算法、没有新入口性能结论。Root负责原版statement及同对象C/汇编捕获，本地没有安装或执行Lean。

这份源只保留一种40链布局。F40结构及列优先字段顺序取自原eb9的精确header；原eb9.wordLoop没有复制进来。新 `Submission.Panel4.F4` 每个记录含四行在同一个k位置的Float32。唯一 `Panel4.wordLoop` 接受长度同为n的Vector F4与Vector F10、count.toNat=n证明、机器k和40个scalar累加参数；每k各uget一个A/B packet，读取4个A和10个B字段，执行与eb9逐链相同的mul后add，只有结束才构造F40。

`packA`对每个k从原始A的四个Nat基址getD，再各调用一次原 `ExecFloat.Binary.toFloat32`，构造一个F4。它保留总读取/默认+0语义，`packA_get`只证明这一局部构造。`block`在列组Vector.ofFn之前let绑定panel，再对既有全局F10 B包的各列组复用该panel。新helper不做全局nativeA map、不重打包B；实际C是否确实共享一次准备、何时释放panel，尚未观测。

921实际旧wide热区仍读取四个A对象指针和四个A字段，并做pack。新表示尝试用一条F4对象指针和连续四个字段替代；不能由此预定直接向量载入、无spill或总收益。四次toFloat32/ofBits转换仍在每k的准备中，没有消失；每k一个F4构造是源码边界，实际分配/临时包装、Vector.ofFn callback、Nat地址/边界及释放成本都待C/汇编。

必须分别核对同对象的wordLoop、packA、block与runDot：热回边不能出现转换/构造/foreign call；观察A载入和向量pack是否减少、累加链是否仍按四行分组、是否新增热spill。ABI的40参数栈载入、终点F40保存/分配不是每k热spill。准备侧检查四个ofBits与F4记录，而不是只统计热回边。block侧检查packA调用在列组回调外，panel在所有列组间共享。

当前缺项明确保留：没有Panel4到原dot/Projects等价证明、实际wide入口、NaN原字终点处理、尾行策略、巨大Nat分派回退或完整生命周期。未来必须保留原raw A/B用于NaN回放，原B fullpack仍按完整调用计费。若未来同时保留旧global nativeA map又做panel准备，会重复转换；本探针不能替它证明成本已消除。m%4=0与足够列组可能更适合摊薄准备，但曝光不是耗时或可回收收益。

静态检查已绑定父本/header/increment及builder hash，完整逆向恢复749b；原版policy、唯一声明、40链顺序与内圈源码边界检查PASS。原父本许可和资源选项保持。新Lean/typecheck、代码生成、内核/公理/完整gate均未执行。即使完整gate只运行原入口通过，也不能验收未接入的Panel4算法或性能。
