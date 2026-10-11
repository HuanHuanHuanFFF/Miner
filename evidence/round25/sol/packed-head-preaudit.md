# R25 packed-head：停止本轮实现，保留 R13 精确先例

2026-10-11 10:50–11:00 UTC。遵 root 后续指令，初始15分钟实现包改为静态审计。**本次没有创建 `candidates/r25-sol-packed-head` 或 `scripts/build-round25-sol-packed-head.py`，没有新 native、CI、Git 或本地工具链。** 其他 M / Astra 工作路径未改。

**决定：不实施这份 rows1/6 packed-head 提案。** row1 与旧 R13 的 PC 目标 closure 相同；高低半位互换、保留常量为零的 lazy 分支、复制/布局改变没有形成一个新的信息或工作量机制。combo 的 row6 确实增加了一个旧 pair64 未改变的负载，但旧逐文件数据不支持足够大的净收益，当前只是未测可能性，不满足 root 新设的重访条件。该 exact combo/row6 变体未测，不能称已测无效。

## 本轮先例遗漏与更正

root 初始调查只核查 R2/R3 的两张 hash-indexed SoA bucket2，把 inline AoS 当作未覆盖方向；**遗漏了更直接的 R13 PC pair64**。R2/R3 的负结果不能单独覆盖 AoS，这句话仍正确；由此推导“当前 PC/read-ahead AoS 未试过”则错误。源检查已更正，保留这次选题失误，不为旧负例换名重新派发。

旧入口：`scripts/build-round13-pair64.py`，SHA `1d12dc2e43892e78d7392aa53d5d24655121e03e8ef1d3efb0540d00054975b1`。

它从 public514 克隆 PC ahead / ahead_if / ahead_fix / record / run，只替换 depth1/lazy0 row1：

- 单个 hash-indexed `[u64;32768]` 存最近/次近两个完整 U32 位置；移除 position-indexed prev；两者总量同为262,144 B。
- 旧 packing 当前位于高32位、次近在低32位；本轮提案方向相反，信息和槽数量相同。
- 在覆盖当前 slot 前携带 `pre_cl`；在 `ahead_fix` 复用 word 时也读取最新次近槽，已经处理了本轮强调的 cached older 时序。
- 保留旧 key、插入顺序/位置、skip、完整 `pc_f_try`、fold/emitter；删除常量 lazy0 的 inactive 循环。

旧 Rust `fedf8108d428d86ee37a7678714a8111addabcac344753da62e6e651ff8f58b1`；作者来源 public514 hotkey `5Dr4CXBVFEMfxvoFjP1fCiozMpJCq5tC4DZxpVJfp26tndsz`，原归属/headers retained。旧 copied Lean 未适配，不继承完整 gate。

## 与当前 combo 的精确 closure 对照

public514 Rust：`e337b70b9bd81a1f189a05a37fcd26ca13b1a741a3b6bd8c89705e30896b004a`。

combo Rust：`57a8fb4feffa52d6b966899c4a56bc4754f6fc967a05cf52d5b02a574d037275`。

对两源按 Rust 大括号提取并比较：**全部31个 `pc_*` 函数参数和完整函数体逐字相同，全部 `pc_*` 常量声明与各函数 inline 属性列表相同。** `format_id`、`route`、`bulk_parse`、`parse` 函数体也相同。因此 row1 的算法分类域没有改变。

|调用|旧 public514|当前 combo|解释|
|---|---|---|---|
|row1|`pc_run1c::<32768>(skip4,lazy0,full4,dp1,min4)`|逐字相同|R13 已经实测这条 PC/read-ahead/ring 路线的 AoS 替代|
|row6|`pc_run1::<32768>(skip5,lazy0,full4)`|`pc_run1c::<32768>(skip6,lazy0,full4,dp1,min4)`|新增旧 pair64 未改变的 chain1 负载，但使用同一 PC kernel|
|row0|原 three-byte/depth2|保持原版|本轮计划不涉及，也不能算新收益覆盖|

实际 combo row1 域为 catalog/config/docs/multibyte/page/prose/records/source.c/source.py/source.rs/sourcemap 的11文件；row6 实际只有 lean。分类标签取 L 的真实原 row 调用观察，而不是新增按文件名路由。

另需修正成本措辞：`prev[i%32768]` 的**写**按当前扫描/插入位置 i 前进并周期回绕，不是 hash 随机寻址；`prev[c%32768]` 的**读**按候选源位置寻址。删除一个位置表可能改变 traffic，但不能将两者都笼统称为随机工作或由源码推断可省时间。

## R13 原始配对重新核算

原 run `37850501371`，同一 Intel Xeon Platinum 8573C runner，两块，1 warmup+11 measured reps，nightly-2026-08-18。原 JSONL 源/ELF身份核对，28文件逐 input/token/output SHA 同 parent；不是采用 manifest 的初始 UNKNOWN/PASS 标签作为验收。

`gate/equivalence-research.json` 实际 returncode0，pair64 对 public514 的444例全部 `different_or_failed=0`，SHA `28726606993e9678a0875026fa5e51c88c5faba5fc2c2fb1617ada4a73760260`。仅有限等价，不是全输入证明。

按每文件原 candidate 总时间中位 / 独立配对 incumbent 总时间中位的等权平均重算：

|旧块|pair64 对实际514的总时间轴变化|同源码514-shadow对实际514|
|---|---:|---:|
|1|+0.201216840381%|+0.013256594252%|
|2|−0.146192614961%|−0.176365195246%|

两块变化均值 **+0.027512112710%**，与旧决策一致。第二块同源码本身改善更大，不能把该负值当作 AoS 已建立的收益。没有新 runner 确认、稳定净收益或新完整 gate。

原路径均为 `evidence/round13/37850501371/structure-h/gate/round<block>-<method>.jsonl`。SHA（块1/块2）如下：

|method|块1 SHA|块2 SHA|
|---|---|---|
|public514|`966e092aa7089ca92d08f1c59a252f5837f0154a25f30df658eb866d6994efec`|`687926d74f57096bf0520b4bbe208170e391cd87d69c8bcd4291d08ae7c56054`|
|pair64|`c88527d0f3f992d065bfca4cea2f3f591ba8f2e970535038a6c88c3232202b98`|`c9de4626779c3da9f8abe1e154bc9a9774b6cc035546d86acd8730be1a82a94d`|
|514-shadow|`ab20fa027b09bbb2cc6e7fa5ed8849f4d2fa28ee5c61005745f09b744772cdf4`|`89fff1ea541bb1d562996659998aa4ee72b03562be5f99952407028c2b244d48`|

### 改动11文件的阶段数值并未支持明显 parser 收益

选择与 total 中位数同一个 rep 的 parser/encoder 分量，用对称恒等式拆分 candidate、encoder与独立incumbent分母的变化，贡献按父整轴归一化。它们严格相加回原总轴变化；这是描述性账目，不是剖析、因果或可回收速度。

|组 / 块|parser贡献|encoder贡献|配对分母贡献|合计|
|---|---:|---:|---:|---:|
|实际row1 / 1|+0.029537874 pp|+0.158899488 pp|−0.019030902 pp|+0.169406460 pp|
|实际row1 / 2|+0.004123105 pp|+0.043018016 pp|−0.005229109 pp|+0.041912012 pp|
|未改17文件 / 1|−0.020892037 pp|+0.300426439 pp|−0.247724021 pp|+0.031810380 pp|
|未改17文件 / 2|−0.080901464 pp|−1.050341671 pp|+0.943138507 pp|−0.188104627 pp|

row1 的整体 parser 数值贡献两块都略增加；个别文件有小幅改善，也保留：

|row1输入|parser变化块1|parser变化块2|
|---|---:|---:|
|catalog|+1.0563%|−0.1889%|
|config|+0.3107%|+1.7969%|
|docs|−0.0544%|−0.6108%|
|multibyte|−0.6915%|−0.0318%|
|page|+0.3223%|−1.4168%|
|prose|−0.7234%|−0.5306%|
|records|+1.0884%|+0.3725%|
|source.c|+0.2889%|+1.1730%|
|source.py|+1.6082%|−0.1526%|
|source.rs|−0.3612%|−0.0979%|
|sourcemap|+1.1896%|+0.4069%|

表中是原 total 中位 rep 的 parser 比，不能称跨runner确认；不能按文件挑正案例迁移为新路由。旧 lean 没被 pair64 改动，其 parser仍分别 +0.3541% / +0.2610%，总轴该文件分量一正一负，说明未改路径也移动，不能把它当 packed row6 信号。

## 新 row6 负载真实，但机会尚未闭合

当前 combo 的 G 原轨迹观察：row6/lean 92,786次4-byte/dp1查询，短61,278、长31,491、cap17；原prev实际短胜9,346、长胜3,469。row1十一文件共785,779次（短580,819、长203,719、cap1,241）。row6 的长查询占比约33.94%，row1约25.93%，有不同覆盖/负载；这不等于同一个 AoS 改法获得新净收益，旧表述“不一样的PC read-ahead父版”不足以区分。

最新已归档 J 的实际 combo 父版两块，lean total 中位rep parser占该文件总时间22.8976% / 22.8330%。仅在固定其他分量/分母的数值模型里，**删除整份 lean parser**对应整轴约0.604098% / 0.600429%贡献。这不是可获得收益或性能上界，更不能把一个 prev 表转换当作删除整份 parser；它只说明新增加的唯一文件并没有无限预算。这里未查询/推演新份额，当前目标几何由 root 另行处理。

因此当前不存在“明确未覆盖操作 + 旧逐文件证据支持足够净收益”这组同时成立的理由。若未来获得独立的新负载成本证据，应先给真实可省占比与原配对目标余量，不用高低半位、inline/复制方式或新的文件分配重命名再测。

## 正确性/证明风险保留

当前源未改，以下只是以后重访所需义务：

- 正常、未U32回绕且源c在有效window时，`prev[c%32768]`被本次p覆盖只可能在 `p-c=32768`；严格更旧c2已经超window，原`pc_f_try`应拒绝。它是结构推理，不是已证明的所有输入等价。
- 超U32位置截断、重复插入、读ahead后二槽更新、尾部记录/word复用仍须完整保留；旧 R13 的 `ahead_fix`已经刷新older，不能删掉后重用word/older旧tuple。
- `[u64;H]`需要新packed HeadBound/取低高位界与cached word状态，main tuple增加older字段；原 MatchAt/FoundAt与完整pc_f_try可复用，但原Lean复制只能DRAFT，新真实Funs、原obligation、公理白名单和roundtrip仍不可省。

**VERIFIED**：31个PC函数/常量/属性及路由体精确比较、旧source/444与28原身份、两块旧原总轴和逐文件描述性分解、当前G的真实row6覆盖。**INFERRED**：新负载不足以据旧数据支持本轮投入、ring边界拒绝及固定分量的机会模型。**UNKNOWN**：该exact combo packed rows1/6 Rust的全输入等价、实际原生token/质量/总时间与gate；根本没有生成该Rust。
