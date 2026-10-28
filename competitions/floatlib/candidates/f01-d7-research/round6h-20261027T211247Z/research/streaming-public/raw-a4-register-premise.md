# Raw A4 + prepared B2 + scalar accumulators：15 分钟历史前提调查

调查从 **22:11:31 UTC** 开始；只读历史与现有 C，未造候选、未编译、未排 CI。共同截止不变。

**决定：未找到“同一完整 4×2 caller 去掉 A 面板、保留只读 B2、8 个独立 Float32 参数”的已测精确版本。可保留为一个条件性新判别，但不能把已有无分配/SIMD循环重命名为新收益。** 有界扫描412份顶层候选 Kernel，加上下面手工调用链核对；该扫描不是全仓穷尽或新颖性证明。唯一命中的8标量/raw读取实现是R20一行×八列探针，不能冒充四行×两列完整调用。

| 精确历史 | 已实现的实际调用与留下的成本 | 原结果/范围 |
|---|---|---|
| R16 A4B2 `2a937bb0` | 4行×2列、8个Float32标量参数，USize循环；k分支两次borrowed读取、6字段读、8乘加，无Nat/codec/alloc/RC/apply。A每四行先packA一次，另建G个F8结果tiles再写四行；packA与tiles各有一次Array.ofFn闭包。 | 40183711165完整25轮，whole/B2 **1.00785021**、BMM **1.04343738**，未采用。401854实际C确认改造真的进入caller；该轮新A4B2 ASM缺失，不能声称已测“全程留寄存器”。 |
| typed-within `22ea9e26` | 4×10、40标量参数；actual core仍全局map原A为Array Float32，然后四行循环borrow原生A/packedB。它删除的是运行尺寸检查，不是A物化。 | 40068680108 full；whole/旧6c **1.00004516**，无可靠收益。C体确有40条链，不能当新8/16链的成本结果。 |
| GeneralPanel `a1ab536c` | 改成每块F4 A-panel、40标量acc；actual Panel4.wordLoop C借读A4/B10。历史asm记录825B body、10组跨四行SIMD，loop无动态state map；一个panel/块、结果tiles和终态F40仍在。 | 40073679847 full，whole/旧6c **1.00229811**，无收益。当前保存的hash-bound解析记录可读；其原capture路径未在本次本地范围定位到，未补造新ASM验证。 |
| R19 Dual `c36bc250` | 同一行连续4k的A4+B8时间包、仅两条acc；实际常规full4无codec call、仍有一组16B acc store/reload。新增整次flat A缓存/记录/释放，无R16跨行tiles。 | 40438045432 full25轮，whole/B2 **0.99818401**、BMM **0.98576836**、p05 **-0.01164509**，原体停放；不因旧交接仍写UNKNOWN而覆盖这个后来的负验收。 |
| R11 raw-A-one-group `c477e807` | 一行×10，raw A每k一次decode，无全局nativeA map；有10标量参数、终态F10。保留行号Array、group closure、rowTiles、旧输出结构；新RawIndex ASM未捕到。 | 三个完整发现对a066 whole约.99054/.98717/.98542，均未过整包门槛；BMM局部有改善。这是“删A物化”已被真实测过的邻近机制，但不是4×2 caller。 |
| R20 RowBroadcast8 `ec40e88e` | 一行×8，四个temporal B8组，8标量参数，每4k共享四次raw A decode；无A缓存/Array状态。 | 9根/两模块通过；四公开入口仍B2，没有该完整新BMM性能结论。是接口储备，不是已测完整4×2失败。 |

## 真正能删与必须加回的工作

以**同宽R16 4×2**为对照，删除每四行块的n个A4记录、A-panel指针Array、packA闭包/回调及其写入、读取、RC/释放；保留一次全局B2准备、G=ceil(p/2)个终态F8、结果tiles和四行writer。没有理由宣称把结果tiles一并删掉：任意p时若只append，四行row-major输出仍需暂存其余行；改为全输出预分配/set又是另一份成本。

删除A面板会把raw A转换从 **4n** 改为 **4Gn**，重新放入有活跃acc的k循环。p=2/G=1转换次数不变；p>2次数增加。相对当前PreparedQuad，A转换同样从每四行块4n变4Gn，代价换来消除每k整列Array/Cell加载、清槽/写回和CtorReuse检查。**这些是不同参照下的计数，不能把两份节省相加。**

因此最小结构判别应只取**8标量、B2保持原布局**，复用R16的group/尾行/原finish协议，唯一运行变化先限于取消A-panel并直接读取四个原A行。不要先开B4/16参数、列宽或阈值网格；“8而不是40”已是R16旧机制，不能再记一次收益。

## 首个可证伪检查

1. 沿真正public/bench caller→guard→block/tile→新loop，确认A没有pack/map；B仍只准备一次；loop签名是8个native float参数，正常backedge只有标量赋值/goto，无Array state map/set、无每k F8或Float32 box/closure。原始A/B保留给finish/NaN replay，batch内4行与0..3尾行不变。
2. 解码四个A后再借读B2，避免让B字段跨四次codec调用存活；这是待生成代码检查的表达意图，不保证编译器保持。实际ASM要记录8acc和前三个A值在codec调用间的保存/重载，以及普通backedge的mulps/addps，而不是看一个独立helper或SIMD名字。
3. **主要反证风险是跨call spill**：R19真实c70常规4k有4个codec call及16个向量栈动作；Dual去codec后只有2个，但完整调用仍未达标。新的raw4会把转换移回live-acc区，源码标量参数不意味着寄存器常驻。出现每k对象/动态apply即未实现前提；若只是spills，必须比较完整生命周期，不能从指令计数裁定净速度。
4. 只有当前quad/prepared成本提供继续理由，才由D做这一个实际caller判别；随后完整成本包括B准备、F8/tiles、四行finish、odd列/尾行、释放。R16/R11/R19原负结果原样保留；没有10%whole预测。

## 可复用证明与证据入口

R16的`wordLoop_row`已经给8acc按四行投影回原`R15PackedB2.loop`的形式；新raw loop可删panel hread前提，直接用四个原getD地址关闭一步，然后复用buildTiles/emitBlock/尾行运输。当前R22的通用block/flat-tail接口同样可用。形式化迁移、实际caller及字节上限仍需验证，本文没有新增Lean草稿。

`scalar-resident-survey.json`保存412源的有界扫描、7份现有报告原字节SHA；R16真实C片段在原 `round3h-20261025T091810Z/astra-workers/matrix-architecture/cost-review-401854-excerpts/`。typed C正文保存在原codegen JSON；GeneralPanel函数/ASM对象hash在原1224010 JSON；Dual真实选中C和native路径在原 `development-workers/anchor-323/dual-ci15-review/`。原路径缺失项已明确标出，不把历史报告说成新捕获。
