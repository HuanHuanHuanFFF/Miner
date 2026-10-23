# 低 normal 解码：历史机制与负面边界核对

审查始于2026-10-23 00:04:36 UTC，上限30分钟。只读既有原件、实际源码和公开固定版本；未运行模型、编译器、微基准、Git、CI或上传，未修改R或候选。产物为本文件及同名JSON。另按D追加要求，仅修正先前singlepass审查JSON的同名lemma定位：R7SinglePassSum.loop_eq由误中的5555改为6170；源码和结论不变。

**结论：新式属于T06已有的数值重构/两次精确缩放思想，但不是旧wide64退化实现的重复，也未被R4/R5旧计时直接否定。等待一个最小codegen结果合理；W13/W14现已收齐，不再记为pending。目前仍不自动晋升运行集成，gain UNKNOWN。**

W14确认去掉目标输入的of_bits调用，却否定了“调用消失就连accumulator spill也消失”的强解释。这个混合结果既不能证明提速，也不能证明必慢。已启动研究不应因此取消；保留完整数学、C、汇编和慢样本。后续若继续，判别对象应是同一个公式在实际有序调用上下文的完整成本，而非再做一次旧wide64代理。

## 1. 具体机制：哪些已知，哪些确有变化

| 对照 | 实际机制与域 | 与新式的关系 |
| --- | --- | --- |
| T06 / R2-W03数学 | normal值为sign·M·2^(E−150)，E1–23也成立；原报告第4节还提出两次精确乘法、均用normal因子避免subnormal因子 | 一般数学思想已有，不能称全新发现 |
| R2-W03 wide64 | E102–151；UInt64 M按E−102或E−134可变移位；选2^-48或2^-16；数值转换后一次乘法，再按sign分支取负 | 与新式不是同一域、同一整数宽度、同一分派或同一符号实现 |
| R2-W03 signed wide64 | 同样两桶和UInt64移位，改为Int64符号构造 | 仅单向量计时，64向量pool未测；不能借unsigned慢样本给它补结论 |
| 当前唯一式 | 仅旧低guard拒绝且magnitude≥minnormal时，tableProduct(u+0x10000000)乘Float32.ofBits0x2f800000 | 只扩E1–23；复用原signed table及UInt32 mantissa转换，无UInt64可变移位、两桶选择或单独随机sign分支；新增第二次乘法及closed constant |

新式把biased exponent1–23提升到33–55，然后乘2^-32还原。其具体接线利用已证tableProduct正常域，保持sign/fraction；这与旧报告“先M乘2^-23，再乘normal的2^(E−127)”也是不同的实现分解。当前实质新增是这条确切word偏移/真实rounder/codec桥的完整形式化证明及窄域接入设计，不是新发现binary32值公式。

e=0不能混入。W13保留了±0进入独立helper后的真实反例：分别变0x00400000/0x80400000。实际wrapper的下界只在旧低guard假支生效；±0本来因UInt32减1回绕而走旧table路径，非零subnormal仍走ofBits。E24–254、Inf/NaN保留原源码机制。

## 2. R2-W03慢样本确实存在，但属于哪一个实验

实际ConversionCandidates.lean、variants.c、diagnostic.c与原始diagnostic.log已读取并绑定哈希。原Lean交付自身是NOT_RUN，旧计时是GCC13.3/x86-64手写C surrogate，并非Lean或官方完整gate。

| C surrogate域 | call中位ns/item | boxed表 | unsigned wide64 |
| --- | ---: | ---: | ---: |
| dense，64向量pool | 3.4661 | 0.8446 | 4.2111 |
| relu，64向量pool | 3.6075 | 2.0746 | 3.2224 |
| wide，64向量pool | 3.6984 | 1.0031 | 7.2452 |

同一个unsigned wide64在单个1000项wide向量上曾报1.2671ns/item；扩大到64向量pool后明显退化。不能只引用前一个好样本。实际汇编保留两桶分支、可变64位移位及sign的js/jns分支；没有硬件计数器，不能把具体退化归因写成已测的branch-miss因果。

计时在表初始化后开始。单向量为11轮、每轮4000次完整原序sum；pool为64个不同1000项向量、5轮、每轮128次pool sweep，输入准备不计入。输出确实保留。旧C代理还测过单向量raw，但wide64在这些raw字上仍只放行E102–151；E1–23继续fallback。pool没有raw。官方gate的raw另为未计时检查，不能混同。

boxed代理只模拟静态预分配表的依赖load，不具备真实Lean Array/RC/once/完整API成本。该负例拒绝“无表/少常量必更快”和“单向量结果足够”，没有测到当前E1–23的提升表再缩放实现。

## 3. R4 numeric-mul：3.75%不是四项整包headline

39746211363、seed504，记录CPU为Xeon Platinum8370C。实际输入Kernel与当前冻结a7dca716…文件逐字节相同；父本6744be2b…、两份原始verdict和25轮数据均已核对，均完整gate通过。

替换的是标量add/mul的两个输入解码点，使用既有convert：E24–254及zero走numeric，E1–23仍走旧ofBits。原始mul计分类及candidate/parent结果为：

| 类 | 输入指数 | 原始耗时比 | 参照归一化比 |
| --- | --- | ---: | ---: |
| near-one | 124–130 | 0.912305 | 0.915636 |
| spread | 1–254 | 1.048080 | 1.046081 |
| tiny | 交替55–65、50–60 | 1.063950 | 1.061716 |
| 三类mul合计 | 原完整标量调用及checksum | 1.037670 | 1.037478 |

所以约3.75%是mul三类合计的归一化退化；near-one反而改善。整体四运算headline为父0.296406、子0.292794，不能把mul局部负面改写成整包慢3.75%。tiny指乘积进入次正规域，其输入并不是E1–23。这次实际测量不包含“把低normal旧fallback改为当前helper”的替换。

## 4. R5 matrix numeric：完整准备上下文的负面

39761679751、seed602，记录CPU为AMD EPYC9V45。实际输入22730b01…与冻结matrix-decode完全相同；父ba93c233…、两份原始verdict和25轮均已核对，完整gate通过。

该稿把A准备map和B打包读入改成既有numeric decoder，dot/output/scalar仍父本。BMM三类合计原始新/旧1.006916；按各自shipped-reference漂移归一化后1.022965。所谓约2.3%是后一个BMM分项结果，不是四运算headline。三类原始比dense/relu/wide分别为1.004496/1.006353/1.009905；归一化分别为1.021419/1.023210/1.023958。

固定旧BenchBmm实际为50×100乘100×50，默认pairs500000对应2批。dense/relu的normal输入为E124–130，wide为E102–151，ReLU A另含zero。计时包括kernel内部准备、打包、计算、输出与checksum；A/B原始输入生成在外。没有E1–23计时输入。raw未计时。这是“统一替换矩阵准备解码不一定获益”的真实负面，不能冒充当前低normal分支的测量。

原固定[BenchBmm](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/bench/BenchBmm.lean)和[BenchTensor](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/lean/bench/BenchTensor.lean)通过只读精确ref响应核实；Git blob与接收内容哈希在JSON。R4/R5都是同runner上顺序运行的候选，各自对官方参照配对，并非新旧候选另做交错晋升检验；不跨suite继承比值或份额。

## 5. 807暴露：仅计数，无耗时份额

存储screen与原模型记录可对齐：active_prefix_words为5035892，其中320是首rawNaN的repair add；native-add前缀为5035572。低normal295268不含这些NaN，约占native-add word数5.86364%，不是时间比例。新下界还会在保留ofBits的31922个subnormal上执行；zero已有table路径。

| 已暴露timed case | low-normal前缀word |
| --- | ---: |
| sum:sparse:1 | 74551 |
| sum:sparse:3 | 41652 |
| sum:subnormal:0 | 176393 |
| sum:extremes:0 | 2672 |

未计时raw的372个low-normal另列，不纳入上述计分计数。没有重跑生成器或大模型，也没有读取未来输入。low-normal、subnormal、普通路径各自实际耗时占比未知；不能用5.86%乘一个臆造局部加速比来报收益。

## 6. W13/W14已经返回的最小判别

W13实际main a17d90417f1a8cd6a8cd396510501082355a00e513cf82af7875d5f8f443928d与成功attempt2快照相同，显式exit0；diag1显式exit0且以同main为前缀。60项原始公理报告仅三允许项。真实接口是机器指数1–23、任意sign/fraction下的Float32等价及toBits=u。这是原件普通Lean证明，未升级为wrapper或新候选完整gate；包级审计仍由R/D负责。

W14实际公开60f wrapper的Lean和原配置clang-O3均exit0。源d5e02a23…、真实C66b65938…、对象回执5c0b3483…及所选汇编均已绑定。

- direct暖路径确实消失了该输入的of_bits调用，保留UInt32转换、signed table读取、两条mulss及内联once状态/常量读取。once冷支仍有外部调用和product保存。
- 真正ordered researchLoop在+0x7d先把accumulator写栈；低normal暖支+0xd5第一次乘法，+0xda/+0xe0/+0xe3检查once，+0xe9第二次乘法，+0xf1恢复acc，再到+0x12b add。**warm loop仍有acc栈往返。** 原fallback对应+0xc4保存、+0xca of_bits、+0xcf恢复。
- W14普通上端源机制保留，但整个guard机器布局从组合setcc/or变为条件分支，不能称机器码或成本不变。它是Array UInt32/Nat wrapper；私有3d9已经有嵌套guard且是Vector/USize，不能把这个控制流差异直接记为3d9退化。

对象hash是保存回执中的实际对象身份，未下载或本地重建二进制。没有计时、完整bench链接或官方suite结果。call减少是有效机制观察；spill仍在只推翻更强的“spill消除”说法，不构成必慢证明。

## 7. 当前投入判断

保留T06旧数学、R2慢样本以及本次W13精确证明和W14代码证据。最小数学/codegen等待已完成，无需再等同一份结果或取消已启动任务。新式不能因为“也叫数值缩放”被直接判重复，也不能因新名字回避旧的分布敏感、调用上下文与完整成本负面。

目前不自动新增运行候选：受影响时间份额未知，实际loop没有兑现spill消除，且普通分支/constant/表/索引成本均须计入。若协调者仍优先此路线，只对同一公式在真实有序调用上下文做一个有界完整成本判别，再决定集成；不展开更多变体，不重复wide64代理，不将证明或调用数当提速。最终gain保持UNKNOWN。
