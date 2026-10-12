# dual8 原生质量与真实提取预审

检查时间：2026-10-11 17:00 北京时间。只新增审阅材料；`r25-astra-dual8` 的Rust、Lean和manifest保持冻结。没有迁移或编译新Lean。

## 质量结论

实际28文件原encoder：较combo净少14,674B、公共等权大小少0.050599196pp；10文件更小、2文件更大、16文件字节相同，token总数净少12,730。所有实际改变均落在row1/row6对应的12个文件；三个binary/JS的row0和其他未改路径保持原输出。

|文件|输出字节变化|token变化|当前证据允许的解释|
|---|---:|---:|---|
|prose.txt|−6033|−4717|与保留更长重复片段的预测一致；不能仅凭此确定具体match来源|
|source.c.txt|−2911|−3011|同上|
|lean.txt|−1872|−1349|同上|
|docs.md.txt|−1472|−1256|同上|
|config.yaml.txt|+79|+77|与丢失旧短链机会相容，但需轨迹计数验证|
|records.json.txt|+123|−34|token更少仍更大，说明距离/符号分布/块边界等成本可能抵消；不能笼统称为短match丢失|

总减少14,876B、总增加202B。上面四个改善文件共贡献12,288B，即总减少的82.60285%。这个集中度支持“长文本/代码有不同保留机会”的解释，**不证明因果已经闭合**。新hint、解析轨迹、距离及Huffman统计都同时可能改变。

与end4相比，dual8总体再少7277B，但在受影响12文件中7个更好、5个更差；原row0三个文件没有获得end4的小幅收益。不存在逐文件支配关系，不能把end4和dual8的字节收益简单相加。尤其catalog、multibyte、records相对end4分别多447、500、299B。

**下一步约束：** 先等待已经运行的原协议总时间。若只有小幅质量而总时间无可用位置，不因14KB这一绝对值就启动大证明。若需解释损失，先在冻结父路径同时记录原head、原前驱和long hint的实际长度/距离及采用原因，不盲目组合更多表或更换键长。

## 已核对的真实提取范围

父级完整gate：R23 run38072972025 `gate-combo/exact-gate/exact-gate/extracted/Funs.lean`。

新提取：R25 run38126033837 `proof-c-extract/diagnostics/research5/r25-astra-dual8/`。

- 原Rust SHA：`4bfe5d2973ed553922eca1d451912bda5d8ad2d6f16c0ccb83419c5086f20f88`，与native和当前冻结文件一致。
- 新Funs 668,041B，SHA `ef51ccade7deff816bf6f7b36a7429a30b97f18d1a2d222378fe5c04f95adce3`。
- 新Constants 94,367B，与父提取逐字节相同。
- 1413个父定义→1430个新定义；去掉生成注释并统一空白后，旧定义仅 `p125_row1` / `p125_row6` 两处变化，无删除，新增17个定义全部是 `r25_d8_*`。
- 17个新定义包含5个源码函数及6个循环/循环体对，不代表必须写17份独立算法证明。
- 提取日志显示诊断使用空 `Parse.lean`，只完成intake/policy/static/extract。它不是当前Rust与复制父Lean这一pair的完整gate。

重放脚本 `audit-dual8-extraction.py` 与完整hash、定义清单、逐文件变化位于 `dual8-extraction-quality-audit.json`。文本比较不是Lean语义等价证明。

## 可行的最小证明路径

建议在原 `namespace PC` 结束前增加独立D8局部块，保留原PC全部证明和原始最终obligation。只替换两个wrapper使用的定理。新表内容仅当hint，**不证明long表必然保存正确hash历史或最优候选**；匹配真实性由检查建立。

|义务|实际接口/复用|重点|
|---|---|---|
|`d8_slot_spec`|`slot.r25_d8_slot s i`，返回 `<32768`|需 `i+8<=s.length`；证明U64乘积右移49后小于2^15，再处理Usize cast。可复用 `Nat.shiftRight_eq_div_pow` 与平台至少32位引理，不能只靠hash概率|
|`d8_link_spec`|返回 `(head,long)`|对head保留原 `HeadBound`；long没有内容不变量。比旧f_link多8字节输入读取前提|
|`d8_probe_spec`|`s c cw c8 p km`→FoundAt及长度/距离界|原 `probe_m_spec`；c8<c<=p和wrapping窗口恢复真实距离；完整word相等给 `pc_xlen16(...,0)` 的真实xor；使用 `FoundAt.of_matches` 或 `MatchAt.of_try`|
|record头循环|state=`(head,long,ins)`|旧 `record3_m_loop0` 的ins投影从r.2移到r.2.2，measure仍stop−ins；加强为 `stop+8<=s.length`，旧“stop+4不溢出”不足|
|record外层|新增long参数/返回|由stop<=lim、lim+8=n推输入界；`pc_TAIL`实际仍常量1，可直接排除else tail循环，无须泛化所有TAIL配置|
|lazy零步引理|实际两wrapper均传 `lazy=0`|`r25_d8_run1_loop0_loop0` 进入时l>=3，因此 `l<0` 为假，原样返回9项tuple。用单次loop展开或恒0下降量证明，不迁移一般lazy循环不变量|
|两个literal尾循环|与原pc_run1两个尾循环逻辑一致|复用C12599的循环模式/Dec.done，只改生成函数名|
|主循环|新增long字段，其他不变量不变|复用MainInv1，忽略long内容；fuel下降量的tuple位置变了，不能原封套C125101。实际 `ae` 仍是三项tuple|
|run1外层/row1/row6|run1参数仍H/input/out/skip/lazy/skcap/km|定理只覆盖lazy=0即可；原H>0、skip<32、输出长度前提保持；最终bulk_parse/parse证明可原样复用|

### 实际主循环状态顺序

```text
(out, nt, ls, p, head, long, miss, fuel, pre_slot, pre_c, pre_w)
```

燃料现在是第8项。`MainInv1`使用out/nt/ls/p/head/miss/pre_slot/pre_c/pre_w，跳过long。这样不会引入long查表的一致性证明。当前long写入被提取为 `Array.index_mut_usize` 及 `index_mut_back`，在match/miss各分支才显式应用；它是提取器对可变借用的表达，不应误判为写入遗漏。主循环只需索引界及忽略long内容，避免展开整个数组。

### 规模判断

预计需要约12–15个局部定理/包装证明（这是结构规模估计，不是耗时承诺），其中真正新增的数学点是15位索引界与long probe有效性；其余以既有record/Dec循环为模板。最容易被忽略的工程点是8字节边界、long加入后的tuple投影，以及空Lean提取不等于复制父Lean可通过。

当前没有发现必须重做全parser数学证明的接口阻断，也没有真实Lean编译来确认自动化能直接闭合。建议只在screen-c出现值得保留的两轴位置后投入；若未来需要迁移，先完成slot/link/probe及lazy0这四组小引理，再迁移主循环，最后绑定原版完整gate。

**VERIFIED**：原始字节、token、hash、成功提取、实际生成接口和定义差异。

**INFERRED**：长前缀保留对质量改善的解释、局部证明迁移路线与规模。

**UNKNOWN**：短匹配损失的因果比例、原协议总时间/条件份额、Lean编译、完整gate及正式表现。
