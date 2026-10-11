# R25 固定合成质量诊断：完整结果与边界

**tinyPC 在这12个固定12,000字节active输入全部更小；end4 在12个400,000字节active输入出现5个回退。** 保留两个既有质量组件和全部反例，不改候选、种子、样本或路由。这次没有测时间、官方分数、私有集、份额或奖励。

原 run `38136091624`，Git `bc0e824af675f858cb5ee549df633d87eba884ca`。原 receipt：`evidence/round25/38136091624/heldout-o-native/diagnostics/r25-heldout-quality/quality.json`，SHA `69a3a342b44b2b000ad04a18bb82858dff10b061e2b51a7e1207c8b6269f2437`。完整机器反馈含54个成对得失、原token/output/input SHA与各族/seed反例：[heldout-quality-feedback.json](heldout-quality-feedback.json)。原始receipt保持字节不变。

## 独立审计实际完成了什么

重新生成并逐字比对留存的27个UTF8输入，确认精确长度、字节/input SHA及冻结manifest一致；重新读取81个run-log结果，对bytes、token数和实际route逐行核对；三份原Rust/Lean、三个实际route-observer原文件和harness SHA均匹配。54项差额从81原始行重新计算，未直接信任root或原summary。

原成功native run执行81组Rust decode与81组独立zlib roundtrip，frozen/observed parse逐token相同。这里审计它们与精确script/harness及成功receipt的绑定，**没有在本地重跑Rust或encoder**。脚本 SHA `3a26b6df478fbe3986a952bac3f45f41e9fdaf30f5c213abd294f8aae5ce7ed3`；generator SHA `e3a29e3884f7f6091b71ce3f59c4c92f3333ed5f0780908cf7e35692ec8b078d`；frozen input manifest SHA `7d560edccba805eb51faaa7decac3b00e40aae655546aa2af59329b956d9c5f5`。原encoder/token仍为 `172c240…5fdec` / `8bf5d962…4917`。

比较精确来源为combo Rust `57a8fb4f…37275`、end4 `03ec0aa4…ed8e6`、tinyPC proof1 `5c20b99c…91f00`；完整Rust/Lean SHA见机器反馈。没有以另一个proof/Rust副本代替本次来源。

## Active 与未覆盖样本分列

|组件 / 组|实际原路由|例数|更小 / 同体积 / 更大|B差总和 / 范围 / 中位|token差总和|
|---|---|---:|---:|---|---:|
|end4 active主样本|400000→row1|12|3 / 4 / 5|+205；−25至+103；0|+171|
|end4 inactive主样本|12000→row12 ETINY|12|0 / 12 / 0|0 / 0 / 0|0|
|end4 fallback控制|196608→fallback|3|0 / 3 / 0|0 / 0 / 0|0|
|tinyPC active主样本|12000→row12克隆PC|12|12 / 0 / 0|−12444；−1272至−828；−1015|−25186|
|tinyPC inactive主样本|400000→原row1|12|0 / 12 / 0|0 / 0 / 0|0|
|tinyPC fallback控制|196608→fallback|3|0 / 3 / 0|0 / 0 / 0|0|

所有inactive主样本与fallback控制均完整token/output SHA相同，不仅同体积。它们是路由/未改路径控制，不能增加active机制证据数。`active`只表示实际进入包含改动的row；没有新增内部offer/guard计数，不能从同输出推导没有新增插入或工作。

end4 的4个“同”仅指同**字节数**：C seed3多1个token且token/output SHA都变化，只有另外3个C样本完整身份相同。Markdown seed1则token数量相同但不同token/output、少25 B。token数、字节数和完整输出身份分别核对。

## 全部族与seed的active结果

差额均为候选减combo；正B表示回退。三个族为固定自写模板，seed按预声明0、1、2、3排列。

|end4，400000 B|seed0 B / token|seed1 B / token|seed2 B / token|seed3 B / token|
|---|---:|---:|---:|---:|
|JSON配置样式|−6 / −11|+59 / +27|+48 / +33|+103 / +64|
|Markdown/日志|+27 / +37|−25 / 0|+11 / +19|−12 / +1|
|C样式源码|0 / 0|0 / 0|0 / 0|0 / +1|

五个回退完整保留：JSON seeds1/2/3，Markdown seeds0/2。新增可检索位置不保证最终编码质量单调；此次没有隔离距离/长度选择、后续parse轨迹与Huffman分布哪项导致这些回退，不能把源码猜测写成已确认原因。

|tinyPC，12000 B|seed0 B / token|seed1 B / token|seed2 B / token|seed3 B / token|
|---|---:|---:|---:|---:|
|JSON配置样式|−865 / −1684|−828 / −1554|−869 / −1631|−885 / −1610|
|Markdown/日志|−1173 / −2517|−1245 / −2677|−1272 / −2732|−1234 / −2668|
|C样式源码|−1017 / −2032|−1004 / −1986|−1039 / −2069|−1013 / −2026|

这些数据补充了“tinyPC质量改变不只在官方tiny-config那一份字节”的有限证据：在此固定长度、三个自建结构族和四个预定seed均更小。它们没有验证其他长度的路由迁移，也不支持总时间或可支付表现。

## 样本选择与相关性

预声明先于生成与native输出。最初方案的196608无法覆盖end4，在静态route检查时被发现；root在结果前把主长度改为400000，并保留3个196608 inactive控制。这个失败的覆盖假设没有删去，源码路由没有修改。

这些是**自建固定合成域外诊断**，不是从真实官方/private总体抽样。相同family/seed的12000、400000及seed0控制共享确定性unit流的前缀；不同seed仍共享模板、词表与参数生成规则。**12个active不是12个独立统计抽样，12/12更小不是成功概率**。没有估计置信区间、正式准入率、私有成绩或奖励。合成字节改善也不能与已有固定28输入改善相加为新官方坐标。

## 下一轮值得区分的机制问题（只提议，不执行）

优先保留更强的已验证匹配覆盖，同时保留小长度/距离字母表的编码成本优势，区分“匹配发现”与“怎样发射这些匹配”。不因小字母表版本的质量损失退回整个弱matcher，也不把更少token当作更快encoder。

最小新证据应来自精确父版原encoder的逐块实际literal/length/distance活跃码、树头bit、已验证span及分片/残留literal工作，再设计**一个**有明确成本依据的发射交换对照。保留 unrestricted PC 与原小字母表来源作实际control，质量/正确性有机会后才测原协议配对总时间；实际时间、当前官方前沿与冻结确认仍决定是否值得完整证明投入。R13按局部码价改写未得到实际字节收益的反例必须保留，不能从局部bits推出最终bytes。

这不是追加开发或调样本授权，也不在这27例上调参数/路由。下一轮若需要新诊断样本，应在任何输出前另行预声明，保持其与搜索、固定官方语料及私有/正式结果的边界。

**VERIFIED**：冻结输入与留存字节、原来源/observer/harness、81成功native checks的绑定、实际路由和全部质量得失重算。**INFERRED**：小字母表成本与更强匹配值得作为下一轮可分离问题。**UNKNOWN / NOT_MEASURED**：合成输入总时间、新净两轴、官方/私有成绩、可支付份额和未来泛化。
