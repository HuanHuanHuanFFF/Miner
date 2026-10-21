# 最近距离候选的适用域与旧负例

本次仅静态审阅与一个字节匹配模型，没有生成候选或另开 CI。A8 的 screen / 预算 observer 继续原定运行。

**不要把当前待决 match 的距离当成 lazy 新候选。** A8 既有 `pc_probe_m`、`pc_f_try`、`pc_probe_lazy` 对选中的距离均前向延伸到首个不同字节、输入终点或 258。当前所有相关 lazy 上限不超过 258；进入 lazy 循环意味着 l<258。因而在 q=p+1 用同一个当前距离，只能保留 l−1 字节，或者因长度不足被拒绝。原 pc_gain 对合法长度严格递增；该候选无法胜出。这是基于这些调用条件的源码推论，未形式化，不能外推到截短匹配或另一种打分。

真正不同的来源是**上一已发射 match token 的距离**。它可以跨过一次此前的失配，在当前 head 已经成功的情况下，于 lazy 的下一位置恢复较长匹配。`last-distance-domain-model.json` 保存一个 100 字节的构造：旧 d32 在位置56最大匹配8；当前 d16 在位置64最大匹配4；位置65的旧 d32可匹配12，而当前d16只剩3。模型保留完整输入和 SHA，只证明这一匹配关系可同时成立，没有构造真实 head/prev 表或验证实际 parser 会走该轨迹。

## 精确历史排重

|先例|实际域和机制|已记录结果|是否直接覆盖当前 lazy 备选|
|---|---|---|---|
|R11 `r11-fast-continuation`|上一 match 恰到258边界、原主 hint 不可用时试其距离|少0.0064067 pp，平均慢0.54646%；见 `docs/rounds/round11.md` 与 `scripts/build-round11-fast.py`|否；但否定“重复距离自动免费”的假设|
|R11 `r11-fast-gaprepeat`|原 `run1` 主探测失败，且已有非空 literal gap；从 `out[nt−1]` 取距离再探测一次|少0.0222624 pp，平均慢0.850916%；`scripts/build-round11-fast-gaprepeat.py`|否，保留全部有效主候选，不检查主候选成功时的 lazy 位置|
|R13 `r13-514-rescue-one/gain`|主探测失败，借既有链的一个旧节点恢复|gain 少0.007856 pp，慢约0.22870%；`scripts/build-round13-rescue.py`|不是上一距离，但同属额外失败恢复，成本反例相关|
|R25 `r25-astra-gap1`|combo 的主探测失败且 p=ls+1，从上一 token 取距离；没有新增主循环状态|少1007B / 0.005834 pp，两块慢0.124% / 0.479%；`scripts/build-round25-astra.py`、`docs/rounds/round25.md`|不是 lazy 位置，也不替换原探测预算|
|R24 U `r24-609-match-cache`|256槽按相同距离缓存已验证终点，为既有 SF 比较省前缀；不增加候选、不替换搜索|高命中但总时间没有收益；`scripts/build-round24-match-cache.py`、`evidence/round24/analysis-u.json`|不同的消费路径与语义，不能当作这个新来源已测|
|R24 BD `r24-609-chain-lcp8`|把链边距离和已知前缀装入原32位项，借前缀传递缩短原比较|已知构建成本与时间反例；`scripts/build-round24-chain-prefix.py`|不同，不能把其 LCP 缓存收益当 rep 候选收益|

R3 `round3-tiny-rep1` 也明确打开 tiny planner 的 `TF_REP`，在链前尝试上一距离，并在相同长度时保留它；见 `scripts/make-round3-tiny.py`。它提醒“上一距离先试”本身不是新发明。此审阅没有从该名字推导当前641 lazy 的结果，也未重新复算其旧时间。

## 一手实现可借鉴的边界

已于本轮查看 [Zstd 官方 zstd_lazy.c](https://github.com/facebook/zstd/blob/dev/lib/compress/zstd_lazy.c)。`offset_1` 从历史 rep 数组初始化，在普通搜索之前及后续 lazy 位置直接校验对应源字，并使用 repcode 表示；其收益比较带有该格式的距离编码优势。这里只借鉴“无需沿 hash 链寻找的历史候选来源”，不能把 Zstd 的 gain 或重复距离编码优惠移植到 DEFLATE。网址为可变 dev 分支，本次没有复制其代码或将其当固定构建依赖。

若 A8 的真实总时间和预算观察值得继续，最小未回答问题应是：在当前 lazy 位置，上一已发射距离有多大比例不同于 head / 第一前驱 / 第二前驱；有多少真正通过原 DEFLATE 距离与字节检查、超过当前 match gain、且替代一个原本无用的链探测。候选来源可从现有上一 token 读取，无须先引入大型表；读取、分支、验证和以后轨迹的代价仍须计入。必须保留已有链独有有效匹配被挤掉的反例。

现在不实现。先消费正在运行的 normal-hop 存活与 lazy 拒绝统计；它能判断是否有探测预算值得移动，但不包含上一距离的真实机会，不能从旧 gap1、这个构造例或 Zstd 使用该技术就跳到收益判断。若未来改动，应固定一次“替代一条原探测”的机制，先原 encoder 与完整成本，不扫描多套距离个数或触发阈值。

**VERIFIED**：所列源码调用域、旧报告的明确记录、构造输入的四个最大匹配长度、Zstd 当前公开源码。**INFERRED**：当前距离续接不能改善现有 lazy 决策，以及上一已发射距离域与旧 miss 恢复不同。**UNKNOWN**：实际641/A8轨迹的机会频率、替代后的字节/时间、完整证明与目标份额。
