# 当前622d BMM路由耗时：最小测量方案

**值得做一次独立诊断，已有原版逐case timer接口。这里交付设计与小草稿；新路由耗时全部UNKNOWN，未运行Lean/CI。** 不需要在kernel中插timer，也不需要建立新阶段成本框架。

窗口UTC22:19:58—22:49:58；首设计在15分钟内写入checkpoint。仅本目录写入；不操作Git/CI，不读取后续holdout，不接触dualTemporal算法。只复制已见1927003/1927005计划。核对发现40407333869原provenance实际是**1927005**，1927003在40398675395；request按原回执固定，未沿用错配名称。

## 已有数据能否直接给出路由时间

原`Bench.Suite.measure`183–194行本来就打印`name timed ns checksum`：一次warm checksum在timer外，然后取默认3次完整pass最小ns。`runBmm`216–225行的pass调用public bmm、遍历输出并形成scalar checksum。**原始ns是一整个case的计时pass，不是ns/work，也不是进程墙钟。**

两个已见完整D的全部原件已核哈希，日志均没有原四列逐case行；verdict只有26个class与25个全case总轮次。官方generator的`summarise`456–483行先逐case跨轮取min，汇总到class后不导出case值。class headline总ns可按其work恢复，但混合路由的class无法再拆成各路由。按MAC、对象或case数量摊分没有时间证据。

旧R13的fine/coarse有观察器；旧报告记录fine约8倍扰动，coarse BMM仍1.053773倍、Cross1.181010倍、sum3.330953倍。它们的阶段比例不能当原成本。旧whole_multi确实复用了**同一原benchFull、无C插桩/重链接**，其六process采集模块实测15.454秒，可复用接口；但源是df5c、输入1224xxx，含Cross等不同路由，旧份额不能转给622d。

## 最小运行与可信边界

1. 用原intake/policy/statement构建**精确622d**一次，保留原MainFull/BenchSuite和编译选项。独立entry只把原三项作为构建接口，阶段表变化限这个诊断进程，官方gate文件不改，生产完整gate不替换；该entry的成功只表示诊断构建/采集成功。
2. 单独metadata进程执行`RouteLabels.lean`：使用原`Bench.Suite.element/float`构造与runBmm逐字同定义的A/B，调用候选原`UnderflowZero.small`求两个all标志，再按冻结622d的入口guard贴UnderflowZero、B2、B1、DirectContinuous、DirectSmall、Packed10或Reference标签。标签是同输入/同guard的源级精确入口判断，不是内层采样；不在计时binary内运行。
3. 同一个原benchFull对每个已见plan跑2次，共4个进程；固定500000 pairs、inner3，保持原CPU/内存配置。保存每次全部156原行、35个BMM标签（34 timed）、checksum和失败日志，不剔除慢样本。同seed两个process逐case checksum必须一致。
4. 逐路由只加总timed case的**原始ns**，除以该process全部BMM ns或全部timed ns。保留逐process结果；另报两个process的逐case算术均值再汇总。不要乘work，不以元素数加权，不把两个同runner进程当独立采用确认或原25轮score。

这里测顶层入口路由的整次成本，包含该路由内部的prepare、NaN回放及输出；不再拆阶段，也不把整条路由的份额视作全部可消除成本。

| 边界 | 处理 |
|---|---|
| 原始A/B生成及输入最终销毁 | 保持原官方timer外边界；不改成另一种benchmark口径 |
| public bmm内underflow扫描、A/B准备、数值循环、输出构造、内部临时数组释放 | 整个原调用位于timer内；源码/C保持不变 |
| 输出遍历/checksum | 位于原timed pass内 |
| 输出vector最后释放 | pass只返回scalar，按原编译所有权流程应在返回前；**必须保存实际BenchSuite C核最后decref/返回/monoNanos顺序后确认**。此前全销毁范围UNKNOWN |
| metadata分类、启动、hash、日志解析 | 单独进程或timer外；不计作Kernel阶段时间 |

driver强制保存实际BenchSuite C、MainFull C、Submission C及三个对象/原binary前后hash。第一次回收后只需对BenchSuite的runBmm pass和measure做一次生命周期复核。找不到C或确认销毁在timer外时，只报告原timer口径，不拼加插桩阶段时间来补齐。输入生成器、原bmm和C若漂移则停止。

## 精确对象与预算

- 目标Kernel：`622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58`。当前B2 scope以它为准，未自动换成已失败的9f7/f84。
- 官方public源码：`4b7e83841cc0c32c6529f533923c73d33b5ecf97`；suite `a16494e97c6a073bfd8accf72480c34534c87808092c56074fdcfa42cd34868a`。
- generator：`7198464dfc08f4bb2a3a5e31ce5a105964d1d73ad6b11ee49e682a30c04daf69`；BenchSuite：`2f1672738e07851fdb24ed968c248fc2e6d8a3e677c27763ebd489ada9425a9f`。
- 已见1927003 plan：`b3d19580bc8d5c6674edcbfa4eda0c405d0f83bcef9064af827243503e5bb6a9`；1927005：`8c385cab83fdb6243420ed4dc80c8dbf9e843564e249602bccab16288c8eec90`。原路径/回执在input-audit.json，副本逐字保留。不会调用make_plan生成新样本。
- 原MainFull C预期`94f69ed19083e0fbb5d4b540d16d4575b82d4aac75779ce88043ef4f908bfecb`，其bmm闭包已在前述C审查认证。新诊断仍核实际build身份，不能拿别的caller代替。
- 采集模块硬deadline240秒，每次metadata或binary调用最多90秒且不越剩余deadline；这**不含**外部官方准备/statement构建，外部job总上限须由D派发时另定。新metadata执行成本UNKNOWN；两份plan共约603万输入元素，仅用于资源预检，不作耗时权重。

## 草稿与最小证伪

`route-profile-entry.py`是独立Linux构建入口；`route-profile-driver.py`复用旧已认证156行parser，只采原binary；`RouteLabels.lean`是metadata程序，未进入Kernel或计时binary。源码/计划/依赖清单由request.json和draft-validation.json绑定。未来CI须使R13 parser与本目录文件可访问，不能默默换parser。

建议第一步只做这个独立诊断，不增加score或确认。以下任一现象即停止并保留日志：精确源/plan/官方hash不符；MainFull caller不符；C/object/binary变化；缺/重复case或标签；timed ns无效；同seed checksum不一致；metadata编译/执行失败；出现旧FL13/FC13/pr13观察器。完整销毁边界未确认时不升级范围声明。

本地只做Python语法、旧真实156行parser、35个合成标签、3个拒绝案例及raw-ns守恒检查；合成时间/标签不作测量。Lean程序、新Linux入口、实际route标签/route时间和生命周期C复核均NOT_RUN。结果JSON仍是诊断份额，不是score、收益或成功概率。
