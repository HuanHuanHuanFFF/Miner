# 三个下溢数学域：完整输入扫描判别

只读重建已执行901/902/904的完整A/B字，使用此前与官方4b7 Git blob一致的原生成器与精确复现计划。逐数组完整max exponent、finiteScale、NaN/Inf计数与全字节SHA均在JSON；不是prefix最大值。实际Lean数组dump/运行轨迹仍未保存，结果为源重建推断。

|seed|域|命中case数|比当前固定域新增case|命中MAC份额|命中全scan词|miss早拒词|先A后B总读词|
|---|---|---:|---|---:|---:|---:|---:|
|901|fixed43|1|无|3.21%|6970|202|7172|
|901|scale_sum84|1|无|3.21%|6970|202|7172|
|901|scale_sum100|1|无|3.21%|6970|72412|79382|
|902|fixed43|3|无|12.20%|188599|171|188770|
|902|scale_sum84|3|无|12.20%|188599|173|188772|
|902|scale_sum100|3|无|12.20%|188599|174|188773|
|904|fixed43|2|无|8.30%|432182|44|432226|
|904|scale_sum84|2|无|8.30%|432182|60|432242|
|904|scale_sum100|2|无|8.30%|432182|24781|456963|

决定：**PARK_DYNAMIC_MAX_CERTIFICATE_NO_NEW_HITS**。
这三组输入中扩大两次数学域均没有新增整矩阵命中，既无新增MAC覆盖，也无已知新增耗时覆盖；不值得仅为动态max证书增加完整扫描、max维护和新scan证明。保持6a69固定短路guard，后续只在出现实际不对称低指数输入的新证据时重访。

三个域均按实际raw exponent255拒绝任意NaN/Inf。scale空数组最大值按0处理；normal/subnormal/zero由实际word字段判定，不看family标签。mag1严格center−min(ctz,spread)。

≤84域可复用现有任意UInt64 product的算术结论，但仍缺动态max扫描→每个读取scale界的证明和实际运行版本；≤100另缺24bit×24bit乘积界及round-to-even归零桥。

表中miss读词数来自唯一的先A后B早拒方案：A有限max扫描中见非finite或scale>上限即拒绝；A完成后B按剩余额度拒绝。当前fixed用原Array.all。完整max统计所做的分析扫描与提案运行时扫描分列，不能混记。所有逐case时间、scan/max/fill耗时及收益均UNKNOWN。
