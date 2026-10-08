# R11 gap：观察先于实现

本轮授权起点2026-10-08 11:14:07 +08，硬截止13:14:07。文件范围仅本任务分配的候选、专用build/diagnostic脚本及本页；主线程负责CI、提交和整合。沿用 huan-open-research 的实验/证明边界。

## 首个有效检验

问题：R10的端点缓存因查询范围短、维护过贵而失败；尚未计数原 `d_gap` 第三段的实际同价格平台及连续continuation胜出宽度。变化：只观察原标量循环，不替换规划状态或输出。检验成本上限：15分钟准备，CI原生编译180秒、36输入执行300秒上限；不是性能测试。计数不足或低成本守卫无覆盖就停止这条批量实现路线。

基线为 `candidates/r10-finder-pipeline-proof`：Rust `b74ae5fd9575101b6b34b9f2718d8835adca770c6765c30b33bb895878ba1adf`，Lean `e0ded4248a894e8c53bc1ce644c7c3f5c6681fe3c06eaab597caf10a5bf472db`，已有完整公共gate。开始时Git工作区干净，分支 `codex/round10-balanced`、HEAD `196513f`；此处不提交或切分支。

产物：`scripts/research-round11-gap.py`。接口 `ROUND4_SPEC` 的布尔 `gap_diagnostics`；未请求时早退；读取同name的基线entry并核对精确Rust/Lean哈希。仅GitHub Linux runner执行。结果落在 `RUNNER_TEMP/round4-receipts/gap-diagnostics/{gap-diagnostics.json,build.log,runtime.log}`。

本地仅完成Python语法、注入锚点及完整源码反转核对，**native Rust UNCOMPILED / CI NOT_RUN**。所有观察语句移除后恢复原源码全部字节。脚本SHA256 `ec89e4d8a62c0a70938a86cc82562a1a0a7e604e4d698cab7b40008d5270a862`；runner instrumented Rust预期SHA256 `b82e23ee88a4aef041860c211f3d40eb492511f005b2c444773864bc9131216d`，harness `c7006525b30ef05944267a9e1974d8329086dbd60e1709558c6b84b4594a8084`。

诊断每个输入运行frozen和observed两份parser，先核对tokens逐字相同及独立decode，再保存计数。语料为28个公共文件（15,930,000字节）加现有 `round3_synthetic.inputs()` 的8个固定生成输入，分别汇总，不充当私有集。报告保留源码、harness、脚本、生成器及每输入SHA。

## 计数语义

- 三段原循环分别计数；第三段保留原 `vc < vl`、两个原数组写入及nxt赋值，只旁路读取这些已有值。
- 64个计数区分strict continuation、literal及full-cell tie；high-cost tie的低choice胜方单列。零价按胜方及dlit模式分层；32位打包截断、u64 wrapping、choice高位/长度范围/lo边界独立记录。
- 六组宽度直方图：实际lc平台、严格胜出连续段、strict seed后oracle安全段、每表min/max守卫安全段，以及后二者按物理ring边界切分的段；桶为1、2、3、4..7、8..15、16..31、32..63、64..127、128..255、>=256。
- 每个安全段采用greedy、不重叠计数：先由原式处理一个strict seed；之后同平台且守卫成立的位置计入B。B排除seed。物理ring切分不自动增seed，setup与重新seed成本另计。
- 每个实际d_load epoch扫描256个literal项，取得min/max/zero；扫描512个实际lc项取得平台数。它们只是诊断元数据。报告记录每epoch的offset/min/max/zero/platform以及256+512项扫描、3*256+512次逻辑比较；不声称是机器load数或未来免费工作。
- 原式已经计算出的每个被判安全的v必须逐位等于vc，否则带owner/epoch/q/rem/kc/L/price/chd/dlit/nxt/vc/vl状态立即失败。第三段实际q>=lo也失败。长调用仅保存至多16个代表性状态，避免巨量日志。

oracle和保守段均额外限制rem在3..258、dlit为0/D_LIT。守卫采用自然数choice=chd+rem<2^32、dlit<2^32；C=(kc+L) mod 2^32。oracle检查当前price，而保守检查C+maxlit<2^32和(minlit>0或choice<=dlit)。进入每位置还检查nxt高位等于C。当前价检查的机会不可等同于无需逐字节价检查的机会。

## 可审阅快路径草案：尚未实现

若保守B及切分后宽度支持投入，一份候选只替换第三段中strict seed之后的平台区间。前两段、缓存kc、block/owner/lo边界、标量fallback保持。不能把合法producer长度/价格来源偷偷加到原全输入obligation。

候选可在实际d_load epoch取得literal min/max与实际lc平台右端点，供后续gap复用；必须记录并实测其初始化成本。每段批量长度B受q-stop、实际平台右端、rem<=258、自然choice<2^32和ring物理边界共同限制。守卫失败仍执行原标量递推。批量核心仍逐项写ring U64/out U32，只消除literal查表、成本加法及choice比较；不省字节输出或两个必要存储。

守卫的纸面语义理由来自 `evidence/round10/gap-next-experiment.md`：平台内continuation高位C固定，且无literal的32位成本回绕。正价时continuation严格赢；零价时choice<=dlit仍得到相同完整cell，等号分支虽选literal但cell相同。首个实现优先最容易解释的strict条件，放宽等cell条件须单列，不假称已证明。

最低证明代价待真实提取确定：第三段及新fill helper的数组界/游标递减/返回状态总性；若metadata跨调用，d_load/d_block与d_dp的loopstate/plumbing也变化。原 `d_gap_loop2_spec` / `d_gap_spec` 仅证明out长度保持，不能当语义最优性或父子全输入等价证明。批量q减B须证明1<=B<=q-stop和q_new+B=q，不能沿用只证明减1的d2_pred。后续候选仍需真实Aeneas提取、原obligation、公理白名单及完整公共gate；本轮父证明通过不覆盖新Rust。

主线程要求优先审阅局部方案，具体界面如下（仅设计）：

1. 保持 `d_gap` 签名，第三段开始前可计算一个局部packed u64 literal bound（max为低32位、min为高32位）。该值在第三循环中不变，因此是额外函数参数而非新的loopstate。代价是每gap一次256项扫描；是否值得由实际gap/安全B分布判别，不假称免费。
2. strict seed后使用 `d_gap_platform(lc, next_rem, limit, L)` 从实际表取得第一个不同价格位置，普通数组循环限rem<259；该循环每次rem加1的总性可复用现有 `d2_inck` 固定常量界，不用新的复杂fuel或mask。
3. 由当前q-stop、平台长度、rem<=258和ring连续槽数取B。守卫用显式u32截断后的C、价格bound、自然choice界及标准dlit模式；失败原标量继续。
4. 新fill helper返回nxt/ring/out/q。最低总性post为out长度不变且q_out<=q_in；外层每轮先完成原scalar seed已使q减1，随后helper仅进一步递减，outer measure可由q_out<=q_seed<q_entry闭合。完整ring/out/nxt语义一致是另外的命题，不能用此measure证明替代。

若局部256扫描被计数否定，而表epoch更少且覆盖足够，可考虑一份加载时融合min/max的方案：读取原 `litc[i]` 时更新界，避免额外literal getter；将两u32界packed为一个u64沿 `d_load`、`d_block`、`d_dp` 传递。源码审计显示当前两个主要backward loopstate均为9项（`d_dp_loop0_loop0_spec` 2613行、`d_dp_loop0_spec` 2651行），需各迁移一个缓存scalar及初始化/返回绑定；只保证总性的旧post无需偷偷加入价格来源前提，但新版本仍需实际提取和gate。该后备方案证明成本更高，目前未选用或实现。

## 保留槽表示只读审计（11:38前，未实现）

主线程提出检查 `lc[264..512]` 哨兵区传metadata。原d_load 1949行统一填 `0x00ff_ffff`。实际D读取为：gap 2004/2018行的 `lc[rem%512]`；d_bcost 2030行与d_best_len_old 2057行的 `lc[l%512]`；d_push 2081行的 `lc[(el+x)%512]`。文件更早/后面的DP、其他引擎lc是独立数组，并非此d_load装载的D数组。

不能使用264..510：仅凭合法producer长度<=258不够，d_top对未验证rs仍允许cl=511，gap可能使用rem=510。slot511则有更窄的完整调用链界：

- d_dp在2226行要求p<hi，hi初始n且以后降为p，所以p<n。若cl<=room=n-p，d_end的p+cl自然不溢出且end<=n；否则end=p，continuation的end>=q guard使它不会读取lc。
- cl=top%512<=511。每次gap的while q>p1、p1=p+1和d_stop保证stop>=p+1。gap真正处理位置q>=stop，故rem=end-q<=cl-1<=510。此推导容许病态rs与任意tabs，不用合法producer的258界。
- d_cand 2126行先拒绝len>258和len<=prev；prev从2开始且仅由接受的len更新。调用best时lo=prev+1、e=len+1<=259，因此d_dp内不会走可读slot511的d_best_len_old fallback。
- d_push 2080行显式el<=258、x<=258-el，所以el+x<=258。d_back即使获得病态bl也受这个guard约束。

**候选表示，仍未选用：** 只占slot511，写入“256个literal全部正价时的实际maxlit，否则0”。0表示禁用，max>0时守卫C+max<2^32足以严格连续胜出，不需要保存完整min/max两个u32。任意loaded u32价格也可正确计算此值；不用假定价格生成范围或全正价。

必须保留原通用d_load、d_block、d_gap及其他helper；新增专用d_load_meta/d_block_meta/d_gap_meta，仅让d_dp内部调用它们。加载helper先真正装载litc再计算slot511，block切换每次同样更新；其他原价槽保持。这样d_dp两个9项loopstate不变，仅函数绑定迁移。仍需审查实际新提取，新增loader/bounds/fill helper总性，完整gate与token对照。

slot511不是可自认证的metadata：若单独向新fast helper传任意lc与litc，不能假定meta对应litc。例如C=2^32-2、伪max=1、真实当前literal价3会通过错误守卫，而原literal回绕后胜出。故新fast helper独立全输入token等价是**不成立的声明**；它的语义论证必须明确绑定实际loader来源不变量。原通用helper保持原式作为generic fallback；不能把来源不变量悄悄加入原LZ77 obligation，也不能由总性gate推出通用helper语义等价。如实现无法保持这个分离，否决保留槽方案。

## 已完成观察与唯一候选（11:47）

**VERIFIED有限native观察：** run `37722786008`、commit `02e8095c8f719f9026791354ee7531b4cf8f3059`，回执 `evidence/round11/37722786008/probe-a/diagnostics/gap-diagnostics/gap-diagnostics.json` SHA256 `b34125c6c245896c7bd711910abe83be9b17edca93eecaca91ed8dcac5bb3e9f`。28公共和8既有生成输入frozen/observed tokens及decode全部相同，安全预测逐cell核对全部通过。不是优化性能或新proof。

公共三段字节数为1,141,915 / 1,660,992 / 5,699,346。gap calls 1,030,274；真实d_load仅130次，literal元数据扫描33,280项。所有价格为正，无literal打包回绕或choice高位。guard与oracle seed后安全字节均3,140,732，占third的55.106884%；非空guard段801,413，平均B=3.918993。B直方图为 `[413210,57357,160575,95494,47148,20937,5757,935,0,0]`；无后续字节的strict seed另有1,321,669。物理段803,707。**判断：** 否决每gap256扫描；仅保留每load metadata。短段和失败的下一lc探测会增加启动/检查成本，覆盖不能直接换算时间。

父线程已授权一份 `candidates/r11-gap-meta`。构建脚本 `scripts/build-round11-gap-meta.py` SHA256 `16639dec66b7c2dade3d9e65681dc83df951540dafbca34abbbcd728839feaf6`。Rust SHA256 `25bd4ee52560288f36c73f813a769345044cab2c4924705e6c4c92a64c017de6`；复制父Lean `e0ded4248a894e8c53bc1ce644c7c3f5c6681fe3c06eaab597caf10a5bf472db` 明确UNADAPTED。源码反转及builder --check可重现通过；本地未运行Rust、CI或新Lean。

具体机制：保留旧公共d_load/d_block/d_gap以及原D访问helper逐字，d_dp仅替换1个load、2个block、1个gap调用名称。新增loader每次实际加载后扫描当前256价，写slot511正价max编码；0禁用。新gap前两段保持递推，第三段原strict scalar seed后，检查cost+max<2^32、rem3..258、dlit低32与chd<=2^32-1-258；内层直接核对每个后续lc等于seed平台并写cell，不做平台预扫描，不依赖价格来源假设或额外dp loopstate。缓存kc不重新读ring endpoint。原fallback保留，实际DP rem<=510因此不读metadata作价格。

`native-helper-check.rs` SHA256 `24b6fb47cb660bcb3c57554c01f9a16178d054a472b2efa5baab4928f200aeca` 设计10个loader和1540个病态rs/表/模式DP对照，包括len259/264/510/511、零价、u32最大价、多block reload、非法节点计数、slot510真正读取witness、正确metadata成本wrap回退及伪metadata预期反例。**此harness当前UNCOMPILED/NOT_RUN。** 主线程可设置spec `gap_candidate_checks:true`，新版 `research-round11-gap.py` SHA256 `d150b545783f6480d0f45595f53a2d43bef99d8583dafba166c784dd5b2fb3fd` 将在CI生成 `gap-diagnostics/gap-candidate-checks.json` 与两份日志；原observer生成hash不变，probe receipt的旧脚本hash保留。

原生444、公共同token/byte、真实Aeneas提取、精确新Lean及完整gate与总时间均仍UNKNOWN，不能继承父证明接受。下一步由主线程同run筛选和提取；有有效同字节时间信号才在独立 `r11-gap-meta-proof` 适配真实接口，否则停止此固定实现，不扫阈值或扩缓存。

## 最终负反馈与证明停止（12:12）

上段UNKNOWN为11:47时状态，现补充后续实物：gap-b `37724534982` / commit `d703bdbc901f9518b1443093437ba210b5de0540` 自然success。真实官方提取accepted，`extraction/r11-gap-meta/Funs.lean` SHA256 `dd29b3f280b82c2e942deb633b03daca246fe9885734961028d8a28a562cc955`；native444及公共token/output同父，专用helper检查也通过10loader/1540DP、slot510 witness、正确metadata wrap回退与伪metadata预期反例。它们不构成新Lean完整gate。

实际Funs显示max_loop三项state `(i,maximum,positive)` 返回 `(maximum,positive)`；new gap前两段与嵌套 `d_gap_meta_loop2_loop0` 均四项 `(ring,out,q,nxt)`，outer loop2 state同四项、返回 `(nxt,ring,out)`；d_dp内外仍各九项。新loop2 scalar seed的写入被Aeneas转为Array/Slice.index_mut_usize及back闭包，需单独处理Slice back长度。Std API模式参照已有官方作者Array proof及 [Aeneas Slice.index_mut_usize_spec](https://github.com/AeneasVerif/aeneas/blob/main/backends/lean/Aeneas/Std/Slice.lean#L255)；最终仍须针对比赛固定pin编译，主分支资料不当作已通过pin的证据。

12:05:36开始第一次实际接口迁移，12:12:15生成独立 `candidates/r11-gap-meta-proof`：Rust逐字 `25bd4ee52560288f36c73f813a769345044cab2c4924705e6c4c92a64c017de6`，Lean `052fc5336cef9214a140c3204fe23c214e1be637cec8899ec98d03aa02aaaa46`。builder `scripts/build-round11-gap-meta-proof.py` SHA256 `7c199de56ba100e33833000801e76e25070572a04c39263560175b138dd41821`。静态反转恢复父证明全部字节：新增helpers和四处调用绑定之外，原checked emitter/root suffix不变，无新sorry/axiom。**此草稿UNCOMPILED；没有运行Lean或完整gate。** 剩余义务为mutable-back API及长度wrapper、nested q<=entry与outer严格下降、投影/shift/lift/bind战术对齐和整份原始gate。状态在该目录 `UNCOMPILED_STATUS.json`，第一次草稿/manifest保留生成时状态，不改写为已验收。

配对公共总时间相对同场pipeline两块为 **+1.04529253% / +1.11799604%**，均值 **+1.08164428%**；公共大小轴保持33.934365747942536%，delta0pp。汇总 `evidence/round11/two-loop-summary.json`，原始 `evidence/round11/37724534982/gap-b/gate`。该固定实现被支配，主线程指示立即停止proof修复/fullgate；没有独立性能确认、正式admission或任何资金动作。D/nonD归因由主线程另外核对，此处不推断原因已确认。

本轮取得的最小结论：slot511的窄用途与0禁用正价max编码，在现有调用链源证据和有限病态检查下保持原消费范围；宽泛“padding皆空闲”的假设没有采用，0..510原价完整保留。公共实际有55.1%的third seed后安全位置，但该直接填充实现仍更慢，否定由覆盖/廉价metadata直接推导总时间收益。段平均仅3.92、seed-only多、失败下一lc探测及代码布局/寄存器变化都是待区分解释，不能冒充已测CPU原因。停止本固定实现，不以调整阈值或扩缓存救负方向。

## 预先停止条件

观察副本token/decode不同或守卫内v!=vc先停止并保留失败；不解释为收益。每表保守覆盖为空或只有seed、仅逐字节oracle有长覆盖且没有便宜来源不变量、物理/平台/block截断加setup后同类新增工作抵消可省工作，均停止当前方案。若机会集中于单个文件，保留逐文件等权轴贡献及外推缺口，不用总字节覆盖代替性能。计数支持时也只授权一份候选的真实配对判断，不承诺速度或前沿收益。
