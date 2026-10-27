# 决定：STOP 当前 A4B2 晋升，保留已证明结构资产

精确2a937bb0在完整发现组40183711165通过原gate，但对622d整包1.00785021、BMM1.04343738，ADD/MUL/SUM约1；不重置失败、不进入确认。此次实际C表明**主要循环改造已经实现，未发现错误调用旧内核或输出反复计算的实现事故**。当前没有依据把未提速归因于“忘了内联/没有去掉转换”，也不足以再占完整计时预算。

**身份与范围。** 40185444601的内层原始input和40183711165计时input均重算为 `2a937bb02ece438cb129e65f7e18ce6c7b30658fcdf5f8a204e8da9208a4afc6`。内层Submission C为 `e683c27d…1176b`，MainFull C为 `94f69ed1…bfecb`；12份选用原件逐一对照原artifact哈希。MainFull第69行闭包明确指向Submission_bmm，并在3806–3807、3817–3818送入两个bench入口。没有采用外层8eb carrier的C/ASM。19个精确函数、行号、正文SHA与调用边界保存在 `cost-review-401854.json` 和同名前缀excerpts目录。

| 实际选中路径 | 已观察事实及成本含义 |
|---|---|
| bmm→dispatch→core | 45126+→44947+→44854+；原guard及fallback保留。core在44864只调用一次原B2打包，再进入专门生成的batch/block循环，通用output/writeBatch闭包定义不是这条实际路径。 |
| wordLoop43402–43462 | k热分支两次`uget_borrowed`、6次原生字段读、8组mul/add；零Nat、原字转换、分配、RC、apply。F8的32B标量payload只在终态构造。C源循环前提成立。 |
| 每块packA与tiles | 44713先packA一次，44727一次Array.ofFn构造G个结果，44729消费四行，44730释放tiles；没有按输出或按g重建A。packA实际每k一个16B payload记录、4次of_bits、4次getD边界检查、2次Nat乘法和7次Nat加法；没有逐字段Float32 box。 |
| 新准备开销 | packA分配捕获3值的闭包，tiles分配捕获5值的闭包，两个Array.ofFn仍经过boxed回调。packA回调释放其A引用；tiles回调释放panel/packedB引用。数值k循环本身保持借用。生命周期成本在外层，并未消失。 |
| 实际输出44397–44667 | tiles读取为borrowed，直接选Float32字段送原finish并push；无Float32 box、apply、再次runDot或F2投影对象。行号仍在每输出执行1–3个Nat相等判断，再选列；每行每g重算地址，C有5个Nat乘法站点。原B2 emitter仅有列选择。 |

**分配前提现在更具体。** 在p2..8与旧B2对照，按64位固定runtime头部和恰长数组容量，原先每完整四行块的主要请求增量 `32n+48−16G` 还要加上实际存在的两个闭包112B，变为 **`32n+160−16G`**。p=2即 `32n+144`，为正。闭包大小由固定lean.h第219–225、893–900行推导；该式仍不是物理分配器/RSS或时间测量，也不适用于把p>8的实际F10父路径当B2。旧622d三个选中B2函数在去除SSA编号与片段末尾换行后均一致，未发现比较基线运行体漂移。

**尚未知道。** ASM selector只保存Packed10Index和旧B2 fallback，未保存A4B2新符号；新SIMD宽度、spill、机器级调用及timed ELF均UNKNOWN。静态C不能证明分配/地址/输出中的哪项造成4.34% BMM退化；6类混合输入也不能作逐shape归因。即使未来取得无spill ASM，也不能抹掉当前完整成本负结果。

**只有重新分配研究预算时才考虑的一个改变：** 将外层改为显式一阶block准备/写出过程，预先计算四个raw行base，消除已看到的两份Array.ofFn闭包/回调引用操作和每A4 packet的2个stride乘法、3个不变base加法；数值wordLoop、宽度和准入域保持不变。最小判别先看该精确caller C确实消除这些工作且没有增加全局A或重复准备，再测完整成本。当前无相应耗时占比或大收益证据，**不据此创建变体/排CI**；预算继续给ADD主线。

本次只读取完成发现组和精确statement诊断，5秒强制超时脚本约0.1秒；无编译、Git、CI、未来确认读取或旧冻结记录修改。token计数UNKNOWN。诊断结束于本记录时间，后续只凭新证据重开。
