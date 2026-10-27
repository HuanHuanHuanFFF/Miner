# 已执行901/902/904的下溢guard曝光

仅按精确官方生成器和已保存种子重建原始字；没有运行Lean或新计时，没有读取确认种子。两个原generator字节与官方4b7 Git blob一致，三个保存计划均由原Python planner逐项精确复现。实际Lean数组dump和新guard运行轨迹未保存，结果标为源重建推断。

|已执行seed|整块命中case（重建）|命中MAC工作量份额|命中输入扫描词|其余case短路扫描词|命中输出填充词|
|---|---|---:|---:|---:|---:|
|901|bmm:subnormal:1|3.21%|6970|202|1537|
|902|bmm:subnormal:0, bmm:subnormal:1, bmm:subnormal:3|12.20%|188599|171|14815|
|904|bmm:subnormal:2, bmm:subnormal:3|8.30%|432182|44|59356|

逐BMMcase的A/B独立all结果、首个失败字/索引、含失败字读取数、实际先A后B的短路读取数、形状/输入seed和前缀字节SHA在JSON。A拒绝时B运行读取数为0；B独立诊断结果不冒充运行时执行。mag1严格使用center−min(ctz,spread)，再处理scale/clamp及特殊值优先级。

**实际命中case的耗时覆盖为UNKNOWN。** 原完整25轮a066回执只保存cell总时间，未保留逐case时间；脚本没有把case工作量比例当时间比例，也没有按相同case数分摊。命中case所在cell的实际背景为：

- seed901 bmm:subnormal整cell占a066 BMM 12.31%（1/4case命中）；该整cell份额不等于命中部分或可回收成本。
- seed902 bmm:subnormal整cell占a066 BMM 5.84%（3/4case命中）；该整cell份额不等于命中部分或可回收成本。
- seed904 bmm:subnormal整cell占a066 BMM 22.83%（2/4case命中）；该整cell份额不等于命中部分或可回收成本。

本次没有scan/fill耗时或提速结论。完整命中消除点积的正确性与实际采用仍以精确6a69的新完整gate为准。来源、全部SHA、官方固定ref和逐项缺项均在JSON及source-receipt。
