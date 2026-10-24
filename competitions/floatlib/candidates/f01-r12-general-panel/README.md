# R12 GeneralPanel：完整候选冻结稿

Kernel 已于 2026-10-24 06:43:23 UTC 冻结：255559 B，SHA-256 `a1ab536c08d666f8b3f5d848d3fb9341410f37e3072f0d1ee17dba7672e48abe`，余量441 B。静态 policy、精确逆向、全部生成输入哈希及 LF 元数据已核验；新 Lean/full 尚未运行，性能 UNKNOWN。默认 builder 退出0确认生成结果与 Kernel 逐字节相同，其打印的 dryrun 标签是历史显示字段，冻结状态以 manifest 为准。

这次直接改共享RowStream的group/row及唯一一套Prefix证明：numericBase与原raw A/B回放基址分别传入，普通行numericBase=globalRow*n，局部尾行numericBase=rLocal*n。逐k读取等式只作Prop前提，不把Float32读取改成MAC中的函数回调。普通fallback的调用者与证明也同步改写。

完整四行块用已验Panel4.block在g外准备一次F4，再得到一次F40块缓存后按行输出。只有原packedB全局准备；每batch的0..3尾行只准备本地A片段，raw NaN回放继续读原A/B的global地址。原Underflow最外1039 B、Cross、DirectContinuous、原shape/machine guard与巨大Nat miss保持。原正常fallback仍可使用global A.map；不能因在整个bmm静态图中看到该函数就误判Panel分支重复准备，需沿实际Panel core检查。

为容纳真实整包，删除了WordFinite/FinalFinite共6个未标记定理正文：两个namespace的全部定理依赖家族一起删除：nativeFiniteOfExp依赖modelFiniteOfExp；add_finite_inputs/mul_finite_inputs依赖packNaN_notFinite和packInfinity_notFinite。namespace内部无剩余声明，名字在外部无引用，没有instance/attribute/notation/syntax/options。namespace、open及原FRO/Apache来源原文全部保留。删除仅为容量，不称性能收益；新Lean/full仍需验证闭包。若后续scalar整合需要这些定理，必须恢复对应依赖并重新算容量。

两段旧运行义务注释随实际数据流修改：原“同一全局nativeA”改为“一块一次局部panel/尾数组”，保留共享B、raw输入及一次计算/生命周期要求；其余旧注释按原字节、顺序保留。exact inverse已随冻结稿保存，所有R11原件不动。

有限字模型已经覆盖1280矩阵、63270输出，同时检查新普通row与Panel/localtail路径、各A输入恰好转换一次；这是共同source-derived oracle上的转写检查，不是Lean、硬件、独立oracle或性能证据。

完整验证需包括：原四spec与all-input gate、actualC真实producer/normal-fallback路径、无Panel分支globalA.map、panel一次求值与释放、无逐MAC/输出Float32回调装箱、完整调用准备/尾部/输出/析构成本。不得继承未接入Panel探针的计时。当前仅一个GeneralPanel配方，不做宽度/阈值网格。
