# UInt64 product → native bits →整数重定位：历史只读筛

阶段首工具 **02:46:45 UTC**，上限02:56:45；共同截止03:12:47不重置。只读冻结前R14–R20/R22先前材料，无运行体、候选、CI或当前确认组读取。

**没有定位到同一完整已测体；先保留为未测成本条件，不据此开新版本。** 有界扫描133份R9–R20顶层Kernel的运行def，没有找到单一运行块同时含UInt64整数积、toFloat32及toBits/ofFloat32；跨helper写法、退休稿和未进入top-level Kernel的代码不由此穷尽。旧负面范围不能扩大或抹去。

| 已测邻近机制 | 精确范围与原结果 |
|---|---|
| R16 c972fd72 native repack | 两个UInt32精确cast→一F32乘法→toBits→word重定位，S128..380。40183711165 whole/B2 **1.030550**、MUL **1.081897**。实际选中C有2cast/1MUL/0table/1toBits；toBits非尾部，sum/sign跨call。不是单个UInt64 product cast。 |
| R17 00ab99c7 | UInt64 product→Float32→**toUInt64**→阈值/shift/wordpack。40309310448原fullgate通过但whole **1.0140207**、MUL **1.0325739**，停放。它移除toBits外call但付反向数值cast/clamp；不能当toBits回读体。 |
| R21/R22 scaled-U32 | UInt64 product→Float32×2^-23→toUInt32→pack；原精确负结果保留。不同反向转换和缩放，不复活它。 |
| R22 e51a/92ff | UInt64 product→Float32→一次combined scale表乘→ofFloat32，域S174..380。已曝光406073四组MUL1.035–1.099，精确体PARK；没有直接field repack。 |

本次问题是把首次native integer RNE的结果取bits，读取Ep∈{173,174}与fraction，最终Eout=S+Ep−300。6589已验product decode及R17 middle_bounds/Pmax可提供同一数学目标；S128..380对应Eout1..254，46→47舍入carry保留，Pmax排除47→48。这里只列数学接口，不写新证明或扩大实际e51a守卫。

实际待删工作相对e51a只有scale表读取和第二次F32乘法；相对c972则改为一UInt64整数imul+一cast，原两个UInt32 cast可并行，不能按primitive个数定速度。**toBits仍固定外call**，从e51a最终尾位置移到需word算术的非尾位置；sum/sign或预合成delta跨call，旧c972的真实风险重新出现。相对已经有局部signal的pureword路线，新体还保留cast+call，故当前没有更高上限的实测依据。

若以后买一个判别，必须用相同cold B2边界/完整caller，核实际非尾toBits和保存代价后再测完整guard/fallback；不能继承e51a尾call或00ab无call的生成代码证据。只做数学字段代换不能关闭这个成本未知。普通UInt32/64.log2已由root核为shr/inc循环，不把BSR假设引入新成本账。

原证据入口：R16 scalar-representation/cost-and-coverage.md、c972-caller-review.json及astra-conclusions.md；R17 scalar-cost/review.md、development-mul-cost-and-add-plan.md；本轮native-product-scale/feasibility.md。最新源/结果均保持各自范围。本目录没有新运行源或已通过证明。
