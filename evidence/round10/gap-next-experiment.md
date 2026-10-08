# 后续最小计数设计：d_gap 无 pending-push 平台段

状态：**SOURCE_REVIEW_ONLY / NOT_IMPLEMENTED / NOT_RUN**。本页仅给出下轮可证伪设计，不授权或启动实验，不改变本轮结论：pipeline 公共同输出时间相对 scalar 改善约1.712%，完整公共 gate 已通过，仍未进入预测前沿。

绑定源码：`candidates/r10-finder-pipeline-proof/parse.rs`，SHA256 `b74ae5fd9575101b6b34b9f2718d8835adca770c6765c30b33bb895878ba1adf`；Lean SHA256 `e0ded4248a894e8c53bc1ce644c7c3f5c6681fe3c06eaab597caf10a5bf472db`。本轮 gate 只证明原 obligation，不证明下面的批量替代等价。

## 1. 精确观察位置与状态

观察 [d_gap](../../candidates/r10-finder-pipeline-proof/parse.rs#L1979) 的第三循环，Rust2014-2022行。每次进入循环时先将游标q减1，再计算rem=end-q；只比较literal和continuation，写入ring[q%1024]、out[q]并更新nxt。第二循环2000-2012行额外合并ring旧值，应保留为对照分类，不能纳入无push快路径。

literal-only段的mid由1983行d_clip(end.saturating_sub(2),stop,hi)决定；pending-push段的s1由1999行d_clip(lo,stop,q)决定。对有效stop<=hi及可执行数组界，第三循环处理的位置低于lo：lo在区间内时第二循环处理到lo后，第三循环从lo-1开始；lo<=stop时第三段为空；lo>=进入第二段的q时第二段为空且第三段位置均低于lo。计数须记录实际处理位置q，而非减1之前的游标，防止一字节边界误标。

固定一个d_gap调用的状态为：hi/stop/end/kcd/chd/lo/nxt0/dlit、第二段结束后的q/nxt，以及1998行缓存的kc。**必须使用该局部kc，不得在批量写ring后重新读取ring[end%1024]**；环回可能已覆盖那个物理槽。

调用者 [d_dp](../../candidates/r10-finder-pipeline-proof/parse.rs#L2204) 在2244-2249行逐块调用d_block、d_stop、d_gap，随后处理较低节点。批量段不能跨调用、encoder block表切换或gap所属节点切换。不同的同值价格表也应按实际load epoch区分。

## 2. 可审查的充分条件；分支获胜与cell相同分开

设M=2^32。先用原标量比较处理一个seed位置q0，得到nxt等于该位置的continuation cell。后续位置q递减，r=end-q递增。对一个拟批量区间，要求：

1. 仍在第三循环的原区间与数组界内；端点end、局部kc、chd、dlit和成本表均固定，没有pending-push合并。
2. 实际`lc[r%512]`在整个区间恒等于L。不能以长度代码相同、平均价格或单调价格替代逐表的平台事实。
3. 自然数意义的`chd+r<M`对最大r也成立，且`dlit<M`。因此choice没有混入高32位；具体prototype还可保守要求dlit仅为0或D_LIT，其余通用输入走原标量fallback。
4. 令C=(kc+L) mod M，即原式continuation的准确高32位。每个后续字节的literal价格p满足`C+p<M`，并且`p>0`或`chd+r<=dlit`。

此时进入后续位置时若nxt>>32=C，原式的两cell为：

```text
vc = (C << 32) | (chd+r)
vl = ((C+p) << 32) | dlit
```

p>0时vc严格小于vl。p=0时由choice比较决定，choice<=dlit保证原式输出仍等于vc；choice等于dlit时源码会走literal分支，但两个cell逐位相同。故可归纳得到整个区间的ring/out/nxt与逐字节原式一致。**“continuation分支持续严格获胜”需p>0或choice<dlit；cell等价可用<=。** 首轮计数优先报告严格获胜段，放宽的等cell段单列。

平台内kc+L可能已经发生32位成本截断；只要C取自原式的模M值且固定，这本身不破坏上面的归纳。危险的是后续literal的C+p再次跨M。不能把“没有u64加法溢出”当成没有打包成本回绕。

容易部署的保守守卫是每个活动表的minlit/maxlit：C+maxlit<M且minlit>0足够，无需逐字节再读取literal价格。合法match choice<D_LIT、dlit=D_LIT时，minlit=0也可满足零价条件。若实现仍需扫描每个字节验证p，便没有省掉原literal查表；必须把这种oracle机会与无需逐字节检查的机会分开计数。

## 3. 有效d_dp调用事实与通用helper fallback

可从当前调用源码推导、但**尚未由现有d_gap_spec承载**的事实：

- 2215行构造dlit为0或D_LIT。2233-2235行令distance=cdm+1、cdm取模32768，所以chd=512*distance且distance在1..32768，chd<=2^24。
- 当前合法producer经d_rec_cand限制长度<=258；gap stop>=p+1，使剩余continuation长度更小。对于仅凭d_dp遮罩得到、未验证的top词，cl仍可能是259..511，不能套用合法258前提。首个prototype可显式限r在3..258，其他输入fallback。
- 完整d_push_table生成、正确d_load的literal表，源码d_unseen/d_ecost/d_mix支持严格正价推导；任意tabs或get0的越界零值则没有这个保证。现有总性lemma没有传递价格正性、表来源或语义平台谓词。

通用d_gap允许任意kcd/chd/dlit/价格/range，现有Lean也不要求合法距离/长度。必须运行时守卫或保留原fallback处理：高位choice污染、dlit高位、零价与不利choice tie、literal打包回绕、非平台、合法长度外区间、边界不满足等。对有效调用可另证来源不变量以减少守卫；不能把它们悄悄添作原全输入定理的假设。

已有反例必须保留为将来判别用例：

| 情形 | 原式结果与错误假设 |
|---|---|
| C=0xfffffffe，下一literal价格3 | 和为0x100000001，左移打包后的高32位为1；literal会胜过C，即使u64加法没有溢出 |
| p=0，dlit=0，合法正match choice | 两高位相同但literal低位0更小；“已赢就一直赢”失效 |
| p=0，dlit=D_LIT，合法choice<D_LIT | continuation仍严格赢；正价是充分条件而非必要条件 |
| chd+r跨2^32或dlit含高位 | OR会改变成本高位，不能仅用kc/lc的低32成本平台论证 |

前两项来自 [final-claims-review](final-claims-review.md) 的已有源级反例，本次未运行新的模型、Rust或Lean。

## 4. 一次最小、输出不变的计数诊断

取得后续明确运行授权后，只使用冻结pipeline的原始副本加只读观察。28公共文件及现有8生成输入复用已知输入哈希；不换语料、不增加搜索参数、不执行批量替代。原版与观察副本需逐文件tokens/解码相同，验证所有源码/输入/harness哈希并保留失败日志。观察耗时不计作官方轴或算法提速。

每个d_gap调用记录owner节点p、active block/实际load epoch、hi/stop/end/lo、三段起止与字节数、kc/kcd/chd/dlit、entry/exit q/nxt。每个第三段标量位置读取原本已有的p/L/vc/vl/v信息，聚合以下字段，避免逐字节巨量日志；只保存有限数量的反例与代表性长段。

| 必须计数 | 用途 |
|---|---|
| literal-only/push/third字节数，third调用数与长度直方图 | 分母必须是本机制真正触及的位置，不能使用旧RMQ getter总数 |
| strict-continuation/literal/full-cell-equal；high-cost-equal的低choice胜方；按dlit模式分层 | 区分branch严格赢与cell等价；不要把高位tie当完整cell tie |
| seed后的实际同lc平台宽度、strict胜出连续宽度、安全守卫宽度 | 平台存在不等于continuation赢，也不等于可批量写 |
| 每表minlit/maxlit、零价发生次数及零价前后胜方 | 对照逐字节oracle守卫与每表保守守卫的可部署覆盖 |
| literal C+p>=M次数与余量M-1-C；kc/kc+L的32位截断及u64 wrap单列 | 不混淆cost打包丢高位与u64 overflow；literal两操作数均<=u32::MAX，其u64加法本来不会overflow |
| chd+r>=M、choice>=D_LIT、dlit高位/非标准literal模式、r<3/r>258/r%512 wrap | 量化generic fallback与有效调用边界，而非假定不存在 |
| stop/block/owner/push-frontier/ring物理边界截断次数和损失字节 | 知道长机会实际被切成多少小段 |
| table loads/epochs、可能需要的min/max及平台元数据建立次数、setup/segment数 | 防止重复表扫描或每gap维护成本抵消收益 |

对每个实际strict seed，从其之后的未处理位置构建两个离线机会版本：逐字节价格守卫的oracle段；每表min/max守卫即可覆盖的保守段。段限于同一个owner、表、lo边界和实际lc平台。记录长度1、2、3、4-7、8-15、16-31、32-63、64-127、128-255及更长尾项，并逐文件保存。

随后按ring物理边界分段：从first=q0-1向下，第一段最多first%1024+1个槽，再在1023处继续；不能默认整个逻辑区间对应连续ring地址。最终nxt必须等于最后一个处理位置的原cell。定义B为seed之后满足守卫的后续位置数，seed另记且不纳入B；物理分段本身不要求重新做scalar seed。报告potential_avoided_literal_getters/compares=B，再扣除实现确实仍做同类操作的setup位置，不能重复扣除已排除的seed。若未来实现选择每物理段重做seed，须另扣其实际数量；ring U64与out U32的每字节写入仍保留。

任何被标为安全的后续原位置，其实际v必须逐位等于预测continuation cell，否则保存完整调用状态、相关价格及当前位置，立即判本假设/观察实现失败。此检查在原标量运行之外只观察值，不改变未来ring或nxt。

**守卫成本仍需解决：** 平台与价格min/max可以在observer的实际d_load epoch计算一次，但未来生产实现若新增这些元数据，会影响d_load/d_block状态和成本。不能每gap扫描256价格却仍计为免费。若考虑利用现有长度代码保证的平台，须额外证明实际lc确实来自对应表生成；generic helper不能直接采用这个来源假设。

## 5. 预先声明的停止与继续门槛

以下结果直接停止这个批量实现提案，不通过换深度/阈值补救：

1. 观察副本改变tokens/解码或原文件哈希；先判诊断错误，不解释为收益。
2. 安全条件内出现一个v!=预测vc的反例；或第三段实际处理q>=lo却被标为无push。保存反例，重审条件后才谈新的方案。
3. 保守可部署段全为空，或全为单个seed而无后续字节；当前守卫方案没有可消除工作。
4. 只有oracle逐字节价检查可获得长段，每表守卫覆盖为零，且没有便宜可证的来源不变量；不能据oracle数量直接实施捷径。
5. 将block/ring/平台截断及setup加入后，预期能省的literal getter/比较数不超过新增价检查/元数据维护所需同类工作；当前成本机制被反驳。不同操作的计数不能硬换成纳秒。

存在长且分散的保守安全段，也只允许下一次小规模真实实现/配对判别，不表示提速已成立。若机会集中于单个公共文件或路由，记录其等文件轴权重及外推缺口，不把总字节加权覆盖当官方收益。计数本身不能证明达到了任何时间门槛；后续门槛要按届时冻结官方快照复算，不能复用R9的17.25%或本轮旧估计。

## 6. Lean迁移实际范围

当前 [d_gap_loop2_spec](../../candidates/r10-finder-pipeline-proof/Parse.lean#L2362) 只证明out长度保持；[d_gap_spec](../../candidates/r10-finder-pipeline-proof/Parse.lean#L2389) 拼接三段的长度保持。它们不证明最优性、价格正性、完整cell相等或通用输入token等价。

最低实现范围若保留d_gap公共签名：新增守卫/平台批量helper的totality与数组界lemma，修改真实提取后的d_gap_loop2.body/loop及对应spec；保留scalar fallback。批量推进q减B时须证明1<=B<=q-stop、q_new+B=q、out界、ring段界和nxt返回值，不能继续使用只证明q减1的d2_pred。d_gap_spec的拼接调用也须绑定新实际接口。

另需一个独立语义lemma：在第2节明确条件下，一段bulk的完整ring/out/nxt与原标量递推相同；其证明用模M成本与低choice比较，不由原长度保持spec代替。原LZ77.Obligation、三个允许公理和checked emitter不得弱化。

若元数据保持为每call局部，外层d_dp接口可以保留；如果跨调用保存min/max或平台端点，则实际受影响的还包括d_load_loop0/loop1及d_load_spec、d_block_spec、d_dp_loop0_loop0_spec（当前2625行调用d_gap）、d_dp_loop0_spec和d_dp_spec的state/return plumbing。不能宣称父proof直接可复用，须新版本真实提取和完整gate。

本页止于可审阅设计：没有新增候选、脚本、计数读数、Rust/Lean运行或性能承诺。
