# 矩阵乘法重构：文献、现有证据与实验顺序

调研日期：2026-10-24（北京时间）。本次按用户要求查阅论文、作者博客及官方实现文档，阅读相关章节并对照项目源码；没有复现文献基准，没有新候选或新 CI。当前状态仍以 [development-status.json](../../../coordination/development-status.json) 为准。

结论：重构主线应同时覆盖「按形状选择输入准备方式」和「把多个独立点积组织成向量计算」。连续输出缓冲作为共同底座。最值得新增的机制是跨 batch／独立行的计算组织；已有 2×4、2×8 微块的负结果不能替代它的实验。

## 1. 资料具体支持什么

| 资料 | 可借鉴的机制 | 在本项目的适用边界 |
|---|---|---|
| [Goto & van de Geijn，Anatomy of High-Performance Matrix Multiplication，2008][S1] | 从数据移动、复用及打包摊销推导执行结构，再选择内核 | 文中也讨论窄矩阵无法摊销打包；不能只照搬大方阵的块尺寸 |
| [Van Zee & van de Geijn，BLIS，2015][S2] | 分离输入布局、外层调度和小内核，减少整套实现反复改写 | 借鉴分层与证明模块化；不能直接调用外部 BLAS |
| [Frison 等，The BLAS API of BLASFEO，2020][S3] | 对比全打包、单侧打包和完全不打包，并按规模切换 | 这是与固定输入格式最贴近的论文；原 BLASFEO API 把预打包格式暴露给调用方的收益不能移来 |
| [Kim 等，Designing vector-friendly compact BLAS and LAPACK kernels，SC17][S4] | 按 SIMD 宽度交错存放多个小矩阵，使每个 lane 对应不同矩阵 | 可保留各自累加顺序，但需要承担本次调用内的数据重排和恢复输出成本 |
| [Dongarra 等，The Design and Performance of Batched BLAS，2017][S5] | 比较连续、交错、分块交错布局；分析转换开销 | 论文明确报告转换成本会显著影响完整调用，不能只测准备好的内核 |
| [Chris Armstrong，Arm PL 工程博客，2021][S6] | 将同形状的小问题跨 batch 向量化，减少大量细小调用的成本 | 借鉴机制；Arm 指令、FP64 数据及原文加速数值不用于预测我们的 FP32 x86 性能 |
| LIBXSMM：[SC16 论文][S15]与[官方文档][S7] | 面向小矩阵做尺寸特化，控制调度及代码体积 | 可做少数源码级形状族；本项目不能引入 JIT、外部库或新增指令注入 |
| [Amanzhol Salykov，CPU matmul 工程博客，2025][S8] | 寄存器内保留独立输出、数据复用、尾块和完整打包流程 | AVX2/FMA、16×6 尺寸和多线程配置不能直接迁移 |
| [Nadav Rotem，High-Performance Matrix Multiplication][S9] | 用寄存器块减少每次算术对应的加载量，并检查生成的汇编 | 原文含 FMA；必须检查我们实际生成的独立 mul/add，而非照抄指令 |
| [Simon Boehm，Fast Multidimensional Matrix Multiplication on CPU，2022][S10] | 用连续访存和循环组织解释阶段性收益，保留可重复的比较 | 原文使用 fast-math，不能将其倍率作为逐位一致版本的预期 |
| [Ullrich & de Moura，Counting Immutable Beans，IFL19/2020][S11]；[Lean 数组说明][S14] | 独占数组的原地更新、借用、引用计数与对象复用 | 连续输出缓冲有实现依据；是否消除复制必须在固定 v4.34.0 的实际 C 中核查 |
| [LLVM 向量化与浮点语义文档][S12] | SLP 合并独立标量链；重排单条浮点归约与独立输出并行是不同变换 | 可以组织独立输出供自动向量化；不能开启 contraction 或 reassociation |
| [Deshmukh 等，Cache Optimization and Performance Modeling…，2023][S13] | 把打包、加载和计算分别建模，并用完整调用校验模型 | 其低秩算法、FP64/FMA 环境与本合同不同；只借鉴成本分析和缓存组织 |

以上是相关章节的机制分析，未把文献中的高倍率认作当前候选收益。合法源码复用还须逐份核对作者、许可、精确版本及证明依赖；本次没有复制外部实现代码。

## 2. 现有实现与机会

当前保留源码为 `f01-r8-combined-result-guard/Kernel.lean`，SHA-256 `41bce4856c4c921dd67b6115928df16e5e8ed08a55b71f1296d28b77cf9ce9a7`。

- `n≤4` 或 `p≤2` 走 DirectSmall：逐输出点积，原始 A/B 在内层转 Float32，各输出独立处理 NaN 回放。
- 其余走 RowStream：先准备 nativeA 与 F10 打包 B，再逐行算结果、建立行输出并拼接。输入准备、所有中间分配及最终输出均在计时边界内。
- 本次重查 CI 40005234741 的精确捕获 C，SHA-256 `fb421a595ceced1cf8994f19ccb32704ac20a02a0430eda6c4134bf042d075db`：nativeA 的 map 循环在第 39639—39665 行，每次转换后执行 `lean_box_float32`；第 40809 行由 RowStream 调用。F10 打包在第 38488 行函数中构造一个含 40 字节标量的对象，不能把它误报成十个 Float32 堆对象。
- 固定诊断编译使用 Clang 22.1.4，实际参数包括 `-O3 -ffp-contract=off`，没有 `-march=native`。原文 AVX2/AVX512 的寄存器及 lane 数不能直接假定为我们可用的目标。
- 现有容量余量：保留41为 20831 字节，研究首选 a066 为 18858 字节。新运行代码、证明和接线须一起满足 256000 字节，不能只计算内核函数大小。

以下由 [inspect-opportunity.py](inspect-opportunity.py) 从已有原件重新计算，原始路径、SHA 和全部命中项见 [opportunity.json](opportunity.json)。分母是 seed852 未插桩诊断 control 的 34 个计时 BMM case 的 best_ns 合计 35992011；这是选路线用的单组范围，不是官方权重或可直接回收的阶段时间。

| 形状／路径范围 | case 数 | 占该组 BMM control 耗时 | 对选择的影响 |
|---|---:|---:|---|
| DirectSmall 全部 | 13 | 48.23% | 只修打包路径不足以覆盖大半机会 |
| Packed 全部 | 21 | 51.77% | 只修直接路径同样不够 |
| batch≥4、n>4、p≤2 | 11 | 30.36% | 值得验证跨独立行／batch 的点积内核 |
| 上一行中 p=2 | 8 | 24.16% | 第一份完整原型优先覆盖 p=2；只做 p=1 会错过主要范围 |
| 上一行族中 p=1 | 3 | 6.20% | 可作更小的编译探针，不能将其结果代替 p=2 验收 |
| 已打包且 3≤p≤8 | 10 | 37.66% | F10 尾列和准备方式值得重新组织 |
| 已打包且 m≤2 | 5 | 18.00% | B 跨行复用少，需要核算打包能否摊销 |

前两行互斥且覆盖全部；p=1/p=2 互斥并分解跨 batch 筛查范围；其余部分重叠，不能求和。跨 batch 筛查与「已打包且 3≤p≤8」互斥，合计范围为 68.02%，但不是可消除成本。

另三组已执行输入 850/842/843 中，跨 batch 长细形状分别出现 6/9/8 个 case，窄列打包形状分别为 10/11/13 个。这里只有已见输入的形状计数，没有把它们推算成时间份额；这些输入也不再属于下一候选的独立留出组。

## 3. 三条具体重构路线

### A. 按复用程度选择零／单侧／局部打包

**变化**：将当前固定 F10 准备流程拆成可复用组件，增加原始布局计算与局部打包的完整实现，再用形状及复用成本决定路径。重点不是再次扫描块宽4/8/10。

- 对 m 小、p 窄的情况，比较不建立整份 packedB、按当前块准备、只准备一侧的完整调用。
- 对只有一个列组的情况，调查取消 nativeA 装箱数组是否值得；它会把原始字转换移入计算区，可能破坏向量化或增加寄存器保存，不能只凭少了分配就采用。
- 对可摊销准备成本的规模保留当前已验打包路径。当前公开输入的 p≤8 只是机会筛查条件，不预先指定为最终分派阈值。

**首个有效检查点**：一个包含准备、计算、NaN 处理、输出的精确候选；同 runner 比较41、a066和新候选，逐形状保留收益与回归。诊断对象须核实转换调用、堆对象和向量指令的实际变化。

**证明连接**：布局读取引理 → 每个输出仍是原始地址的同序点积 → 既有终点非 NaN 桥／逐输出精确回放 → 原 bmm_spec。空维度、n=0、大 Nat 及尾块用完整定义或已验回退覆盖。

**换路条件**：若打包节省被内层转换或回退成本抵消，保留实际边界；再研究能同时保持解码外提和紧凑存储的表示，不能只重复替换 Array 为另一种容器。

### B. 跨 batch／独立行并行的四条点积链

**变化**：目前 p≤2 时没有足够列供 F10 计算，退回逐输出循环。新布局把四个独立行实例（允许来自不同 batch）的同一 k 位置放到同一块，让各条点积同时前进。它与 R4 的「同一矩阵两行×多列」不同。

一个可检验的 p=2 原型：

1. 每个小块准备四行的原始地址；循环内无需反复还原 batch／行坐标。
2. 每个 k 准备一个含 12 个原生 Float32 标量字段的结构：4 个 A、第一列的4个 B、第二列的4个 B。布局转换、结构分配和遍历均计时。保留原始 A/B 供每个输出的 NaN 回放。
3. 内核维持8个独立累加器；对每条链严格从 k=0 到 n−1，分别执行一次 Float32 乘法和一次加法，从 +0 开始。让固定编译器判断能否自动生成两组向量运算，不添加 AVX/C、编译参数或新 extern。
4. 末尾不足四行使用正确的尾部路径；不同 batch 的 B 起点分开证明。输出逐个套用现有终点守卫／精确回放。

这个表示有机会共享同一 A 的两列转换，并减少循环／地址控制；也新增块准备与对象成本。因此须同时比较直接读取组织和局部预打包组织，不能先认定某一种必胜。第一份完整收益测试必须覆盖 p=2；p=1 在 seed852 仅占约6.2%。

**首个有效检查点**：冻结一个实际触发的 p=2 完整入口，检查生成代码是否产生独立向量 mul/add、热循环是否出现新增转换调用／寄存器落栈，随后检查完整成本。没有形成目标机器码时，先诊断表示或调用边界，不直接增加 lane 数。

**证明连接**：每个 lane 的 Float32 递推与 NativeFinal.dotLoop 对应 → 原地址映射 → 各 lane 终点处理 → 输出位置与长度。可借鉴 R4 的低／高投影证明和 R10 的地址界限组件，但新增表示与接线仍须重新验收。

### C. 连续结果缓冲与执行流程融合

**变化**：用一次分配的结果数组承接最终输出，逐行／逐块递增地址，不建立行号数组、行结果 Vector 再 flatMap 拼接；在写出时完成终点处理。

先证明「已写前缀等于参考输出」的不变式，后续 A/B 两种计算方式共用它。只改变容器与遍历，不改变点积次序，便于隔离性能归因。

**首个有效检查点**：实际 C 中确认数组更新未因共享退化成复制、闭包及行数组是否减少，再比较完整调用。仅有源码里的单个 Array 变量不能证明运行时只有一次分配。

**换路条件**：若这些分配本已被编译器消除，或实际成本很小，就降低单独投入，将证明及输出组件用于 A/B，而非继续微调写出顺序。

## 4. 已试方向如何影响选择

- [R4 2×4／2×8](../../../research/astra-collab-20261022-r4/checkpoint-04-final.md) 完整 gate 通过，分别比对应父本矩阵慢约9%／0.6%；捕获诊断对象中已形成向量 mul/add、B 复用且热循环无调用／落栈。它排除的是当时两份完整实现，不能解释成 SIMD 没生成，也不能据此否定跨 batch 布局。
- R10 短 n 手动展开、低指数桥接、long-thin USize 内层替换未得到采用优势。新路线必须改变共享、布局、准备和输出中的实质部分；不能将这些试验改名重跑。
- [旧存储调查](../storage-cost-screening.json) 已查过 FloatArray／字节存储。固定核心没有已核实可直接替用的 Float32Array；现有 FloatArray 存 Float64，转换与逐位证明不能省略。F10 的10个标量也没有逐个装箱。
- [853缓存曝光记录](../round2h-20261023T170031Z/cache-853-exposure.json) 中 m=1，新增 B 缓存 guard 没触发；它不是缓存机制的反例。下一次发现实验先核查 guard 覆盖。
- 逐位合同限制：不引入 FMA、fast-math、改变单条累加顺序的分段归约、近似低秩或直接移植 Strassen。可重排独立输出的执行与存储；每个输出内部的乘法／加法及 NaN、±0 等语义仍分别保持。LLVM 的 contraction／reassociation 含义另见[官方浮点语义](https://llvm.org/docs/LangRef.html#fast-math-flags)。

## 5. 投入、顺序及验收

建议沿用65%重构／10%廉价局部优化／25%验证的总比例：重构部分约25%投入 A、25%投入 B、15%投入 C。它是下轮预算建议；本次文献调研不自动开启新的计时研究窗口。

实施顺序是：先用已有证据与最低成本编译探针确定 A/B 的关键瓶颈；完成可复用的输出不变式及必要底座；给最有支持的一条路线足够预算做到首次完整原型，再决定扩展或换路。不要把三条都做到半成品就花完验证预算。

比较目标仍用「受影响耗时占比×可信降耗幅度，再考虑开发、证明和验证成本」。例如覆盖 f 的路径局部加速 s 倍，总体只能达到 `1 / (1 - f + f/s)`；68.02%的范围即便都局部2×，该组矩阵也仅约1.52×。冲矩阵完整调用2×还需要更大局部降耗，或同时消掉其它共有成本。覆盖比例不是降耗比例，文献高倍率不代入这个式子。

发现组可选择能触发目标分支的输入，但须记录筛查条件及全部结果。最终冻结精确源码后，再使用至少两组未参与选路的不同输入／新 runner 确认，原版 gate、公理审计、逐项 checksum、25轮配对计时与完整回执全部保留。分派成本、打包、尾部、NaN 回放、输出分配及销毁按原计时入口计算。正式上传仍是单独操作。

本次结果状态：文献机制和上述历史输入统计已核查；A/B/C 新候选均为 PROPOSED，新增性能、证明和能否替代冠军仍未取得实验结果。没有改动看板数字或原始 CI 原件。

[S1]: https://www.cs.utexas.edu/~flame/pubs/GotoTOMS_final.pdf
[S2]: https://www.cs.utexas.edu/~flame/pubs/blis1_toms_rev3.pdf
[S3]: https://cdn.syscop.de/publications/Frison2020.pdf
[S4]: https://www.sandia.gov/research/publications/details/designing-vector-friendly-compact-blas-and-lapack-kernels-2017-11-12/
[S5]: https://icl.utk.edu/files/publications/2017/icl-utk-1376-2017.pdf
[S6]: https://developer.arm.com/community/arm-community-blogs/b/tools-software-ides-blog/posts/new-interleave-batched-linear-algebra-functions-in-arm-pl
[S7]: https://libxsmm.readthedocs.io/en/latest/
[S8]: https://salykova.github.io/matmul-cpu
[S9]: https://gist.github.com/nadavrot/5b35d44e8ba3dd718e595e40184d03f0
[S10]: https://siboehm.com/articles/22/Fast-MMM-on-CPU
[S11]: https://arxiv.org/abs/1908.05647
[S12]: https://llvm.org/docs/Vectorizers.html
[S13]: https://arxiv.org/html/2311.07602v1
[S14]: https://lean-lang.org/doc/reference/latest/Basic-Types/Arrays/
[S15]: https://ieeexplore.ieee.org/abstract/document/7877162/
