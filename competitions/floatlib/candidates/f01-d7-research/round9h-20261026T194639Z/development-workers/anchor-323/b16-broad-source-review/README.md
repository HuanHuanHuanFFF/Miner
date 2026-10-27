# 广域B16源码复核：有条件进入一次全源statement/C

**核心实际验收后，建议精确7f1d一次完整source statement、Submission/VerifyFull重放、19根及实际caller C；暂不直接完整D。** 本次只做源码/patch/依赖与地址审核，未读取CI19未完成验收、D17或确认输入/结果，未运行Git/CI/Lean或改候选。

| 精确源 | 本次核验 |
|---|---|
| a87f560a / 255600B | 相对c36正逆patch逐字可逆。新增B16 core+广域入口，public仅改dispatch/spec两个目标；原UnderflowZero先判及零分支不变，其余3ops未改。原稿miss确实回c36，未将它暗改。 |
| 7f1d4ec3 / 255655B，余345B | 独立在内存重建后与D副本逐字相同，正逆patch也可逆。恢复完整622d PackedB2 namespace，删除两旧outer shell，两个新fallback转B2；其它a87f字节不变。 |

**这不是仅两行修复。** a87f中PackedB2只有425B stub，无dispatch/spec。恢复完整9141B namespace增8716B；删除Temporal group起的4166B及Dual同段4487B后才满足字节限制。7f1d从文件头到PackedB2末共225870B与622d完全一致，包含旧依赖/其它3ops。新guard miss走保留B2，避免p5/6等非目标域继续承担c36 A4成本；不把R15ThinPairs语义等价入口冒充保留B2运行体。

删除的group/row/output/core/dispatch shells不在新19根内。保留的Temporal B8/read/packet/pack/loop及证明、Dual A4/blocks/packA/row_bound/loop/runDot及证明仍满足新入口引用；已知namespace的显式引用均能落到保留声明。19根声明全部存在。B16核心namespace与118d fragment逐字相同，**这不代表118d或全源已typed通过**；未知unqualified/typeclass/elaboration问题仍须真实Lean验收。

源码接线一致：true guard为`m>0,n>1,p≥3`及ceil等式，无p≤8/m≥4；false guard在7f1d为保留B2。行r的A原址`r*n+k`，B原址`(r/m)*n*p+4*g+j+k*p`；flat PB索引`(r/m)*ceil(p/4)+g`的商/余数恢复同一batch/group。A4 packet为`r*ceil(n/4)+t`。每lane独立原顺序累加，再用自身结果调用Packed10.finish及精确base+j的原字NaN replay，未用一个四lane总NaN标志。按row→group→有效j递增push，末组只emit真实列；无补零写、随机set或结果tile。batch0为空fold；m0/n≤1/p<3及pmod4=1/2回退。有限48090组有序地址/输出检查通过，仅作接线反证筛查，不替代任意Nat证明。

成本必须分域：旧Dual真域才已有A4，才可讨论两B8→一B16、两F2→一F4的增量。新DC/宽路会新引入A4+B16准备、驻留及析构；旧raw输入、finish、输出box/push和回放保留。ceil等式只对齐B8两列组的padded width，**不意味着比旧DC无新增MAC**：p=3 mod4时旧DC算p条真实列，新B16还算一条不emit的phantom lane。对宽路原布局的净替换要看实际caller，不能借用窄域账。

已核旧CI12非Underflow coverage7.2887%/5.9742%whole仅作选路，不能当可删除成本。此次值得买的是低行/宽路完整生命周期是否按源码生成的判别；不从核数、4lane、指令数或有限检查推速度。

下一次固定验收：确认真public→guard→一次PA/PB准备→actual四lane caller；区分导出low/high/join helper与执行体，检查有无新每字段Float32盒、每组动态apply/closure、重复pack、per-k lane selector或隐藏的释放成本。19根尤其finish_select/group_prefix必须全源重新验证。精确hash、根名单、删除声明及有限检查范围在`review.json`，所有输入绑定在`input-bindings.json`，输出hash在`receipt.json`。
