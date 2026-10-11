# R25 下一机制预审：当前不建议再开实现

审阅时间：2026-10-11 10:05–10:11 UTC（北京时间 18:05–18:11）；10:15 UTC 补核两块身份。只读来源、历史与实际回执，新增本文；没有候选实现、参数扫描、CI、本地 Rust/Lean、提交或推送。duplicate-hop 精确 pair 保持冻结。

**判断：public584/public578 的实际差异没有给出一个已分离、低成本且未被旧反例覆盖的质量机制。本次不建议追加实现。** 唯一保留的可证伪问题是：当前 PC 路线的最终三字节匹配是否存在成片的真实编码损失，足以支持一个固定、便宜的发射谓词；当前证据没有回答它，不能先把它写成 min4 或距离阈值候选。

## 已执行的身份与实际质量核对

`astra/quality-comparison.json` 的 21 份归档参照包含 public584 和 combo，**不包含 public578**。因此 public578 的大小与 token 信息取自已经完成的 screen-c 原协议 JSONL，未伪造为同一份 native 回执。按每个输入的 SHA-256、长度与候选源码身份对齐；两块 public578 的逐文件 token/output 身份相同，combo 与归档比较中的身份相同。本审阅未将这些历史时间跨 runner 比较，也未重新计算当前份额。

|来源|精确 Rust SHA-256|作者/来源|
|---|---|---|
|combo，`candidates/r22-595-chain-halfhead`|`57a8fb4feffa52d6b966899c4a56bc4754f6fc967a05cf52d5b02a574d037275`|保留 public595 / public514 及既有派生归属|
|public584，`references/round18-public-584`|`82297feee16db3fe6af50fe07f034b81d73d7189a40a829b78b44db167410cf2`|hotkey `5ETiZDkCgKUJAWEc2xgcsaUmpXRNYiNoCG5amz72ZseSqXMx`；原 PROVENANCE/source-receipt|
|public578，`references/round25-public-578`|`e1f72d323e66a6787cb1310b2f07cb1d4045ceb247a78f2fb3547d2cd03d951e`|hotkey `5EbuBvUpc3tPmQnfYdeeUUxmeCnzJcG1HQ4stFLbknVf4kNW`；普通官方 source，原 response SHA `8954eea734dc4465505e9cff5907593117773e783129e508834ef162a20991e2`|

28 输入共 15,930,000 B。combo 为 5,332,621 B、3,977,099 tokens、等文件大小轴 36.1599092647432%。public584 为 5,197,011 B，少 135,610 B / 31,934 tokens，等文件轴改善 0.615774061652633 pp。public578 为 5,327,867 B，虽少 4,754 B，等文件轴**恶化** 0.005448209528566674 pp；它不是整体质量改善的现成新起点。

|实际输入|584 对 combo 的 B/token 变化|578 对 combo 的 B/token 变化|用途|
|---|---:|---:|---|
|bundle.min.js.txt|−16,781 / +36,475|−4,984 / +41,975|证明少 token 不是原 encoder 质量的充分代理；原因尚未分离|
|prose.txt|−35,593 / −21,667|−6,591 / −6,783|584 更换整条双表贪心引擎；578 既有深度改变，均不等于一个免费模块|
|docs.md.txt|−10,216 / −5,968|+4,736 / +4,273|更大头表、lazy、深度等同时改变，不能取最好文件相加|
|config.yaml.txt|−3,139 / −1,784|+1,748 / +1,518|同上，保留反方向结果|

原始证据：

- public584 native：`evidence/round18/37968740636/baselines-b-native/diagnostics/r13-encoder/encoder.json`，归档 SHA `f3047c4384ea5a63d2ba02c33b927dcfae6713a3d948515e816a00e0d274115f`。
- public578 第一块：`evidence/round25/38126014186/screen-c/gate/round1-public578.jsonl`，SHA `7a8adcab9f6e2495bc1a182214fd0c883abcb0517de29cb31ebde648c132d271`。
- public578 第二块：同目录 `round2-public578.jsonl`，SHA `fd8f1295952e8da65a6caa81ca40a61f13e73d5f6d7310b40e035d70ad3f886a`。
- 实际父版两块：同目录 `round1-combo.jsonl` / `round2-combo.jsonl`，SHA 分别 `1a3fe38b57a7571563944a6b4653c3c4da0bd78ff11567194ad89307d67a83c7` / `c433863347aab634ea695282631ce2a726e8963f01b8403eb5f3d794eede8c18`。

## 源码能解释什么，尚不能解释什么

public578 对 combo 的 133 行 unified diff 只包含来源注释、`format_id` 内联属性、既有 class→row 分配与 row 参数。共享匹配、插入、折叠、发射、分类 kernel 逐字未变。它没有额外新算法可迁移；其质量差异由已有路径选择/预算改变产生。

以 bundle 为例：combo 使用 `pc_run1c::<32768>(skip5,lazy0,km=0xFFFFFF00,dp2,min3)`，public578 改为 `pc_run1c::<32768>(skip6,lazy0,km=0xFFFFFFFF,dp1,min4)`。完整四字节键阻止三字节主匹配，也改变槽碰撞与旧链；skip、dp 同时改变。**INFERRED**：避免某些短匹配可能参与 −4,984 B / +41,975 tokens 的交换。它没有证实“最后三字节改 literal”是原因，更没有证实全域 min4 值得迁移。

**10:36 UTC 根据 L 的真实路由更正：此处原先把 public584 的 bundle 误归因到 `pim_run1c::<65536>(skip6,lazy0,km=0xFFFFFF00,dp2,min3)`；这是静态审阅错误，不是实际观测。** 显式 `n==1000000` 的 bulk 入口覆盖 fallback，bundle 实际走 `p135_row10` → `pc_run1c::<131072>(skip4,lazy258,full4,dp2,min4)`，在真实 token 中没有 len3。`pim_run1c` 的 row7 在本语料实际只有 binary.db；它的真实16-bit表、头插入1、skip6仍与 combo 同文件父路径有多项变化，不能免费归因或盲试2→1。原错误已在 `len3-price-feedback.json` 保留原说法与修正；原始来源/回执不改。

其他 584 主要文本路径把实际 head 从 15 位改为 17 位，启用 lazy258 / dp2；prose 更换 `o_a_main_part::<10,256,8,5,32>`。这些是更多覆盖/规划或不同引擎。双表类属于本次排除的 dual8 邻近类别；全域 lazy、扩表、深度和插入密度不是这里提出的新机制。

## 历史防重复与强反例

已查 R20–R24 最近报告、相关 preflight/feedback 与 builder；没有将“未找到相同精确 PC 谓词”写成“类别从未尝试”。

- R20 539/CSV chain-lazy / head-lazy 少 48,058 / 16,339 B，但真实总时间增加，主/影子均零。R16/R18 的短 lazy 也有明确成本反例，见 `astra/quality-investment.md`。本次不再调一串 lazy 阈值。
- R22 全 PC nofold 多 161,484 B、大小恶化约 0.766 pp、首次两块约慢 1.56%。R20 两个 nofold 父版同样质量与总成本负面。局部发射改写不等于 nofold，但任何改写都会改变后续 backward-fold 看到的 token，不能声称整条父 parse 轨迹不变。
- R23 实际链三只在 lean 再少 3,097 B，却慢 0.426438% / 0.237179%，零投影。更多候选次数本身不足以支持投入。
- R24 `pc_gain(new)>pc_gain(old)` 已在当前 combo / chain3 上试过：少 1,444 / 1,482 B，却慢 0.24%–0.64%、所有主/影子为零。本次不重复这个接受条件。
- R24 当前 N 路径 `n-cost40` 属于已有静态匹配经济过滤，不能换一个价格常量宣称新机制；其来源还含 R18 PC-DNA cost40 和 R20 N 表示负例。
- 对三字节经济假设，额外回查 **R13 更直接的反例**：EF32 按原位置把全部三字节写成 literal 多 3,935 B / 慢 1.257595%；min4 多 3,720 B / 慢 0.872356%。随后真实原 block 码价观察 31,860 个 len3，其中 31,814 个更便宜，只有 39 个更贵、局部损失仅 56 bit。按实价选择改写仍 +15 / +1 B，d32/d128/d512/d2048 则 +5,505/+3,557/+2,532/+507 B。见 `evidence/round13/price-f-decision.json`、`scripts/research-round13-price.py`。

R13 是 EF32/浮点输入，不能据此证明所有 PC 文本三字节都划算；但它直接否定“短/远、token 少、局部 bits 改善必然使最终 bytes 改善”这条推断。当前 bundle 的反差是新的输入域线索，还不是足以覆盖这个反例的观测。

## 唯一保留的假设与最小判别动作（未执行）

**待证伪假设 H：当前 combo 的最终 PC 三字节 token，存在某个已有距离码域中集中的真实亏损；用一个便宜、固定的最终发射规则能追回质量，而不新增 hash、搜索、全输入扫描、文件名或输入长度路由。** 目前不选距离阈值、不生成 Rust。若 H 不成立，本方向关闭，不扫 minlen、距离或 literal 价格。

最小诊断建议仅复用 R13 的原 encoder block 码价观察器，对冻结 combo、public578、public584 各自**完整原 token** 做未计时一次观察。各自先确认 28 输入的原 token/output SHA 与上述回执一致、原 encoder 源码/模块哈希不变、全部独立 decode。只追加观察代码到临时副本，官方原文件不改。

统计所有输入的 len3 数、距离码直方图、原块 fixed/dynamic 类型、原 block 下 match 和三个 literal 的码长、缺失 literal 码、正负差总 bits；以既有算法路由分组，文件名仅作报告标签。应区分最终 len3 与“初始 len3 经 backward fold 已变长”，也保留最近/远源均可能便宜的反例。只看总 token 数或 dist extra bits 不足。

只有观察显示 H 有实质覆盖，才值得**一份**离线、同谓词的 token 改写重编码诊断；它的作用是证伪最终 bytes 交换，不是可运行 parser、性能、同输入全域证明或 oracle 可实现性。真实 Huffman 价依赖后续整块，不能直接放进低成本 parser。若获收益却找不到一个由现有状态计算的稳定便宜谓词，仍不应开实现。若正收益只来自某一文件专门条件、新增扫描/块价模型或阈值搜索，同样停止。

改变当前不投入判断所需的新证据：新 PC 域有明显且集中、可由既有状态分隔的亏损匹配；原 encoder 的一个固定改写保留反例后仍取得有用质量余量；候选无需追加扫描/表/新路由。其后才依次投入精确 Rust、原 encoder/decode、配对总时间及有用版本的实际 Lean gate。

## 证明与成本边界

若未来真的采用“三字节匹配最终改写成三个原 literal”，安全性可由 `MatchAt` 给出的 `p+3<=n`、`Dec` 的 `nt<=p` 与 `out.length>=n` 证明三个写入合法，再复用 literal 解码引理；保留正常 match 分支。**不能**直接继承 `PC.put_match_spec`，因为它当前承诺 `nt'=nt+1`，新分支是 `nt+3`。需要新 wrapper spec（解码与终点固定、token 数有界），并修改依赖该精确增量的 run1/run1c 循环调用证明，实际 Funs 捕获接口仍须重新提取。这是中等局部迁移成本，有限 replay 不能替代完整原 obligation、公理白名单和 round trip。

候选不会免费保留整条父轨迹：它即便保留本次 end，三个 literal 会改变后来折叠读取的前一 token。若要真正锁定父 token，只能做离线 replay，或者保存额外父 token 状态；后者违背当前低成本意图。实际 parser 必须重新比较 28 文件，不能引用离线结果冒充实现收益。

**VERIFIED**：已归档同输入原 encoder 字节/token、source 身份与 diff、上述历史精确负例；无新候选产生。

**INFERRED**：三字节经济损失可能参与 bundle 的字节/token 反差；当前来源变化的可分离性和迁移成本判断。

**UNKNOWN**：当前 PC len3 实际 block 价格/亏损覆盖、固定低成本谓词、真实 parser 改写后的质量/总成本、实际 Lean 接口/完整 gate。结论为**暂不建议新增实现**，不是该机制类别的全输入不可能性结论。

## L 原生观察后的停止决定

本节补充后续结果，不改写上文提出诊断时的 UNKNOWN。run `38132209168` 的原生观察已通过84组归档 token/output/input 身份、frozen/observed parse、原 encoder/追加观察副本以及独立 decode。机器可读完整分路由/距离码反馈见 `len3-price-feedback.json`，原 receipt SHA `e2bb08daad976dccbc6ff29c9868f5f5b1a260eb923983040d641f29d4c6e1d0`。

combo 的真实 PC len3 只有 row0 的 binary.db、bundle、machine-code：77,647个，其中76,172 match便宜、456 literal便宜、961同价、58 literal码价缺失。原块已知价下 match获益626,968bit、局部亏损627bit；全部引擎2,441bit亏损中的另1,758bit来自BFRAW、56bit来自EF32。后两者不是PC，未混入本假设。

每个有样本的标准距离码都保留大量 match更便宜的反例，整码域的已知原表 literal替代成本均为正；code29（24,577–32,768）也有2,280个获益match对184个亏损match、385同价、3缺失，原表已知获益5,509bit对亏损264bit。public578的PC、public584的PC和单列PIM也没有整码域能独立分隔正负。检查的是原30个码域，没有阈值搜索。

**关闭 H 当前便宜距离域规则的实现投入，不做 token改写、候选、参数或阈值扫描。** 627bit只表示父原块表下的局部差，不是实际输出收益、实际收益上界或可复现速度。缺失码价保持UNKNOWN；尚未试图证明其他廉价谓词、未来输入或改写后的Huffman表不可能受益。
