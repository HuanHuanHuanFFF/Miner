# B2路由完整调用诊断：首判别

窗口UTC22:19:58—22:49:58；首15分钟上限22:34:58。只写本目录，无Git/CI/Lean；仅使用已见1927003/1927005，不查看后续holdout或dualTemporal算法。

**决定：已有低成本可复用接口，值得形成小草稿。原版BenchSuite本身输出逐case `name timed ns checksum`；无需在kernel内插timer。** `BenchSuite.measure`183–194行先做checksum/warmup，然后取BENCH_INNER（默认3）次完整pass的最小ns；`runBmm`216–225行在timer外生成A/B，timer内调用原public bmm、遍历结果并形成scalar sink。准备B/A缓存、输出和临时对象生命周期属于原调用；要求保存实际BenchSuite C核对结果decref在pass返回前。原始输入生成/输入最终销毁仍遵循官方timer外边界。

**当前完整D无法倒推出逐路由时间。** 40407333869的原provenance实际seed是1927005；40398675395对应已见1927003。404073的gate.log只保留26个class汇总，verdict的rounds是25个全case总和；未见原四列逐case timer。`benchmark_suite.summarise`先逐case跨轮取min，再丢掉case级数据；不能用class/work/MAC/对象数拆给B2、Packed10或Direct。

最小办法：复用R13 whole_multi，固定精确622d B2、原4b7/public-v2和两个已见plan；同一未插桩原benchFull各跑2次，保留所有原156行、每process份额和同seed checksum。只改独立诊断driver，官方contracts/gate/bench/pins文件不变；不做score/采用。真实route标签用另一个计时外metadata进程调用原`Bench.Suite.element/float`构造相同A/B，再调用候选原`UnderflowZero.small`确认shortcut，其后按精确源码guard标B2/B1/DirectContinuous/Packed10。纯shape标签在underflow处不够。

旧诊断不足：fine约8倍扰动；coarse BMM仍1.0538倍、Cross1.181倍、sum3.33倍，不能把阶段份额视作原成本。whole_multi原timer无插桩可复用，但源是df5c、输入1224xxx，含当前622d已无的Cross等路由，其数值份额不转移。

最小证伪：源/plan/官方hash不符、原binary/C/object发生改变、缺/重复case、同seed checksum不一致、标签缺项或metadata执行失败，均停止并保留原日志，不产时间归属。若拿不到原BenchSuite C或发现结果销毁在timer外，销毁范围标UNKNOWN。接下来只做小型metadata/helper与原binary采集草稿，全部NOT_RUN，不扩阶段成本框架。

已核源码hash：622d=`622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58`；BenchSuite=`2f1672738e07851fdb24ed968c248fc2e6d8a3e677c27763ebd489ada9425a9f`；官方generator=`7198464dfc08f4bb2a3a5e31ce5a105964d1d73ad6b11ee49e682a30c04daf69`。当前新路由耗时仍UNKNOWN。
