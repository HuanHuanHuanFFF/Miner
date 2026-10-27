# DC转换前沿：原双侧numeric方案停止，新raw-pair仅买代码生成判别

**建议：不重开直接双侧R2W01b.convert；可保留无准备raw-pair草稿作一次statement/selected-C候选，暂不直接投入完整D。**

旧R9 d5e3512f/235524B已经将相同convert接入NativeFinal.dotLoop两侧，run39961709177原完整gate通过，归一化BMM1.173127/whole1.040345，未过首D。旧R2W01b runtime所有声明与622d逐字相同；把旧dotLoop两处directDecode逆替成toFloat32后，loop正文与当前622d逐字相同。旧数据不能冒充当前同源对照：旧分派只有n≤4或p≤2，当前DC12例中5例属该形状域、7例为后来新域；新域占本次whole4.2608%。但没有发现会改变逐k转换取舍的新成本条件，因此不能只因新域而重开同一实现。

历史边界：R10 6ba7f035是LowScale.mul低指数word-product分支，不是本次双numeric转换，原完整gateBMM1.093503/whole1.032933；f65只改B1 A转换、另有cb7组合负D；f84只改B2 indexed A转换，实际接纳arm确删call/逐kspill，但其首Dwhole0.995855未过门槛。f65/f84的NativeFinal.dotLoop仍逐字622d。旧scalar caller与sum decoder的效果不转移到DC；固定Lean of_bits实现是bitcast后NaN canonicalization，不能直接当任意raw bitcast接口。核验与来源在audit.json。

原件：run39961709177的43件、39992610090的43件、40425497337的138件，逐项SHA/size/文件集合全部一致。CI10实际622d Submission C SHA0e3c1fc9…、MainFull C SHA94f69ed1…，不是新独立helper。MainFull第69行bmm闭包选public bmm42953→B2dispatch42773→B1dispatch41358→bmmBeforeR11Cross40936→DCoutput40886→实际row专化40840→column专化40798→NativeFinal.dot37322→dotLoop37221。脚本逐边断言调用并保存完整摘录。源别名bmmBeforeUnderflowZero在此实际链已被消去，不把它当额外调用。

当前selected loop每k有2个ofBits C调用站点、2个raw borrowed读取及2个bounds/default、3个Nat add/1 mul/3 lt。没有显式ctor/apply站点，Nat大数helper仍可能分配。dot终态每输出做self-BEq及toBits或原raw replayEarly；output只准备原输出数组，row基地址/除法一次每行。anchor-323已核原BenchSuite C：timer内完整kernel后遍历checksum、drop输出引用再返回，原输入构造及最终input/pass-closure释放在timer外；是否最后引用和native实际free成本仍UNKNOWN。此处保持该边界。现有native selector未采NativeFinal.dotLoop，故当前机器call保留、栈帧、逐kspill和转换实际耗时均UNKNOWN。不得用独立R2 converter或B2 ASM代替它。

## 有且仅有一个新草稿

`Kernel-dc-rawpair.draft.lean` **235299B，SHA8134696db068ceb0c969c7c896199e9c019a7cd375bfe34ab2712eb8d2464365**，精确父本622d/226829B，增加8470B。`RawPair.lean.inc`为完整新namespace，脚本生成前后diff和逐字逆差分回父本。其他三个public入口、outer UnderflowZero、B2/B1准备与路由、旧NativeFinal及所有原文件均未改；原DC外层guard逐字不变，仅其runtime/proof目标换成新core。

新core在n≤1或p≤1时回旧DC；其余DC按相邻双列直接读取原A/B，没有A.map、B.map、pack、panel或全局输入准备。每完整pair/k只读/转换A一次，原B两次转换和两条原顺序mul→add保持；源级4→3转换站点与两次k循环合一，**不是耗时降低25%的断言**。奇数尾组只调用原NativeFinal.dot一次，不执行多余第二链。每行只计算一次baseA/baseB及row/m，groupFrom收到这两个基地址；未照搬旧pair模板每组重算商。新增成本仍有每pair count判断、两累加器跨3次foreigncall可能增加spill、一次terminal F2及两个finish，编译器可能留下group/emit闭包；所有成本在原完整边界内。没有理由预先把这些记零。

证明草稿：loop_s0/loop_s1直接投影到旧NativeFinal.dotLoop，保持任意Nat地址和getD默认值；finish_select复用Packed10.finish_eq_dot，独立处理两列NaN与原raw replay；group_prefix→row_prefix→output_prefix→pairCore_eq_reference复用旧RowStream前缀框架；core_eq_direct最终等于旧DC。完整根名单在draft-receipt.json，整个新source、这些新proof及四public specs均需真实编译/回放/公理审计。没有新IEEE helper或未证helper作为运行前提。

静态Python语法/精确逆差分及8400组任意原字地址投影、1320个有限shape的有序表达式/输出/finish原参数检查PASS。这些只检查接线，**Lean、整模块回放、新public正确性、C、ASM和完整D均NOT_RUN；性能UNKNOWN**。

## 最小selected-C验收与停止条件

1. 以精确8134696d源编译，保存Submission/MainFull C、源拷贝、索引、对象SHA及固定Lean/clang flags。先通过新source普通statement、整模块回放和列明根的公理审计；旧convert_eq或旧B2 gate不能代替。
2. 从真实MainFull闭包→public bmm向下追，n>1,p≥2且原DC miss-B2/B1的调用必须进入R19DCRawPair；n≤1/p≤1及所有outer路由应回旧路径。不能只看导出rawPair.loop。
3. actual groupFrom/专化caller每完整pair只计算一次loop，两列都读取同一结果；循环应只有A/B0/B1三次原ofBits，无numeric converter/table/cast/mul替代。source中的base地址应在row循环每行一次；不能出现每pair row/m计算。
4. 实际热循环不得新增heap ctor/Float32 boxing/动态apply或另一个原dot重算；terminal F2最多一次每pair，释放必须落在计时内。group/emit如果留下新的每pair动态闭包，先停当前草稿晋级，不靠完整D猜原因。原getD/Nat后备属于保留成本，不能写成已消除。
5. 独立采真实被调用rawPair loop及旧NativeFinal.dotLoop的带relocation ASM，分开数每k call/保存重载、入口保存和terminal record。若少一次call却增加spill或未共享A，成本前提未成立。NaN finish/replay和odd尾不能从统计移除。上述检查通过才考虑按原门槛完整D，旧源不换seed，采用确认另用新冻结组。

只用已见1927003两次同binary进程的原逐case ns直接平均求和：DC7.1908%whole/44.3371%BMM；rawpair影响的10例p≥2为5.97846%whole。两个进程whole漂移1.848635×、BMM1.675709×，慢进程完整保留，原因UNKNOWN；不能当稳定跨runner分布。即使把全部DC删光，本样本也不足whole10%；rawpair独自达whole3%需完整局部耗时下降50.1802%。这只是该完整case范围的时间上界/敏感性，不能把其中转换或MAC/call数当时间。与更高上限路线抢唯一CI槽时，应停放此草稿；只有空余低成本statement槽才值得买一次真实代码生成判别。

本子任务只写本目录；没有Git/CI/本地Lean/新增agent，未读取在途确认或后续未见输入/性能。
