# R7开发反馈

## D08 20:38 UTC：808回收及810受控验证

- 808/39846309529原件已完整回收，实际9a2 NaN-fullpath与7ac raw-word均FULL PASS；同8eb归一化整包分别0.8794412/0.8939485，BMM0.7496733/0.7710745。9a跨806/808确认有效；raw-word相对9a整包1.016496、BMM1.028547，当前不采用，不因叶函数更短推定收益。
- b169只在dot_eq原rewrite后的simp无进展失败。已读R新39a99b32及3baa785e自比较修复，810准备以9a/39a/3baa三份完整计时；0de8643c native-prefix与sum-prefix-proof1仅statement先查共同祖先后的新证明。
- D40a281d9特殊分支与singleton-proof1同时只作statement检查。D特殊值原285报错为codec/native descriptor中间rw和未显式展开modelAdd/modelMul，运行算法不动，失败原件保留。Sol子agent修singleton具体Fin.val_zero目标，D统一CI。
- 809/39847080316仍在跑60f直接点积+nonnan组合独立确认和width4/8完整成本。最多两组runner，不重复派发。
- 20:34官方新鲜响应：冠军仍274，官方HEAD4b7/public-v2 SHA不变；新原件official-20261022T203420Z。十小时继续至04:22:17UTC，尚未实现新冠军目标。

## D01 18:28 UTC：新冠军与现行源码

- 官方实时冠军已从174变为269，digest为19d883b6ac6a8a2d943aff48021b027e3a3a3e2dacb42d769cad762cba0c5308，snapshot675。其新版26cell verdict的verification_current=true，表明新suite已有线上实际结果。相对当时参照ratio0.8611958，BMM全部组改善，特殊add/mul也改善。
- 官方GitHub当前HEAD为4b7e83841cc0c32c6529f533923c73d33b5ecf97；新提交仅拒绝同源码副本，原shipped Kernel SHA仍为5d0cef3f、public-v2 SHA仍为a16494e9。正式比较不沿用旧12类乘数。官方579.26×字段包含跨suite历史链，不直接当作新suite相同参照速度。
- 原件在candidates/f01-d7-research/official-20261022T182653Z/，current-official-snapshot.json为入口。冠军/source路径404，尚未取得源码；公开report已保存，仍核查正规源码取得方式。
- 没有旧CI在运行。D准备独立R7新suite适配与shape宽度候选，R按交接继续非有限值证明。无需回复消息，阶段检查读取。

## D02 18:42 UTC：两批矩阵对照执行中

- 801/39832394805，精确提交bd153d72：8eb父本、d9526a34四列、f36c6cab八列，原版4b7e838的public-v2完整gate。同计划、25轮、完整准备/回退/输出，尚无结果。
- 802/39833363659，精确提交91b31432：8eb父本与d9a80847 direct-small。仅按一般shape n≤4或p≤2旁路准备打包，调用已验NativeFinal.dot，其余保留原版。尚无结果。
- 两个公开runner均执行中。已看到R的bb199701 nonnan-bridge-probe，但研究状态尚未标准备交接，D未暂存或派发。请完成自然检查点和精确manifest后写入ready_candidates，D在空闲验证槽编译关键桥；不必等整个运行集成完成。
- D已安排一个20分钟只读独立检查R6阶段profile零记录原因的子任务，不接触R文件或占CI；R继续实际非有限值桥，不重复profile诊断。

## D03 18:50 UTC：801回收，803优先编译关键桥

- 801所有原件已回收校验；父本在当前4b7e838原版public-v2完整PASS，ratio0.4444675。两份width稿仅hz中残留十字段zero元组构造不匹配4/8字段，保留失败源；修复只改该证明构造，76422217/5759d138等待下一槽，无运行变化。
- 父本801份额add22.6%、mul22.6%、sum18.5%、bmm36.4%。其中bmm:dense、specials、extremes有明显回退/布局成本；不同公开seed份额变化较大，保留逐样本，不固定旧49.6%。完整数据见f01-d7-research/public-suite-results.json。
- R已明确交接bb199701。D在9dab4ebc提交精确候选，803/39834631426已派发编译探针，使用合同/FloatLib未变的pins环境，仅statement，不称fullgate。原始完整错误会在artifact，D收齐后反馈。802直接矩阵对照继续自然运行。
- profile根因已对实际保存C逐字节重放：函数提取正则漏掉常走的第四个返回，修补覆盖4/4返回。独立实现current-public-plan诊断模块正在准备，不占R文件或CI；只在新runner真实执行且计数/校验一致后使用。

## D04 18:55 UTC：bb199701关键桥实际编译PASS

- 803/39834631426已success终态，25份artifact原件全部校验。精确bb199701源码，statement57.001秒，compile_pass=true，原verdict mode=diagnostic-statement-only、stage=statement、passed=true，既有四项原obligation在statement构建通过。没有fullgate/公理重放或性能声明。
- 原件：candidates/f01-mul-log2-proof1/ci-runs/39834631426/download-a6a7813837c64ffb94ba6eedca21ca67/。实际源码C和完整build-output均已保留。
- 请据此推进已准备的真实non-NaN终点集成候选，立即交付精确manifest/ready供D跑当前public-v2完整gate；此桥没有编译错误需要先修。D优先给有较大潜在收益的实际集成验证槽。
- 802/39833363659也已success终态，D正在回收父本与direct-small逐项计时。width proof1可稍后同批验证，不阻塞non-NaN集成。

## D05 18:57 UTC：direct-small有实际收益，冻结确认中

- 802原件已全部回收校验：父本与d9a80847 direct-small均在当前原版public-v2/25轮完整PASS。
- 同机同计划，整包new/parent raw0.8758376、按各自reference归一化0.8757222；BMM归一化0.7402424，其他三个scalar/sum约1.0。发现样本整包少12.4%、BMM少26.0%。不跨seed/CPU挑极值。
- 804计划已冻结：parent、同一d9a80847、76422217 width4-proof1和5759d138 width8-proof1。新seed此前未检查，用于direct-small独立确认；宽度稿仍属发现筛选。
- D会在non-NaN实际集成候选ready后优先给第二个CI槽。若该组件通过，再将它与已验direct-small做精确组合与完整验证，不能把两者收益直接相加。

## D06 19:25 UTC：两个真实收益组件与下一阶段

- 804/39835885059已回收：d9直接点积冻结新seed、新runner完整PASS，整包归一化0.800864父本、BMM0.592062父本；802此前为0.875722/0.740242。D将d9作为当前保留完整包，旧8eb仍为本轮组件对照起点。窗口继续至04:22，不因已有提升提前结束。
- 805/39836787411已success并回收：精确c7605688 nonnan-runtime完整PASS，ratio0.3887693父本0.4360368，同机归一化整包0.8915974、sum0.7374286、BMM0.8334285；add/mul约1.0。可继续精确组合，但暂无新seed确认/冠军直接结果。artifact在download-bd809948d4a44095a7f1666cd876d450/diagnostics/f01-d7-public-suite/public-suite/。
- 805的独立profile未完成，原因明确是把Lean的-c输出C命令也当作clang编译器，真实trace红2/绿1已重放修复；不是实际算法/原版fullgate失败。暂不引用阶段份额，下一批重验。
- 806/39839349846已派发9bfc7f05：8eb、9a2a05cd NaN-fullpath、d9、4ba2a235 singleton四个原版fullgate；96131686/e40ccec9 width-proof2仅statement-only。single产品仍精确add(+0,mul)，未省略负零语义。804宽度稿只因zero常量定义与构造表达的rewrite匹配失败，已保留，不阻塞主路线。
- R接下来请优先依据806的实际NaN反馈闭合候选，并准备non-NaN终点与quiet-NaN后缀的精确组合；W01b raw quiet predicate仍有实际价值，但未测前不扩相似变体。D会负责与direct-small/singleton的最终组合和完整计时。
- D新的独立调查范围：标量特殊值派发的实际原始位型快路（NaN优先级/quiet、Inf/零）。只在现有finite守卫失败的分支改动，目标复用已编译非NaN桥与即将交付的raw分类，避免给普通路径加守卫成本；先核固定源码与最小证明/完整成本。不重复R的矩阵后缀循环。单遍sum NaN状态机先作备选，已有候选反馈与集成优先。

## D07 19:52 UTC：9a2 NaN实际FULL PASS，下一组合可排

- 806/39839349846原件已回收：9a2a05cd NaN-fullpath完整原版current-public-v2 PASS，25轮、原spec/重放/三公理/校验。整包归一化0.8067073父本，BMM0.6518841，add/mul/sum约1.0。这是首次发现样本，不提前改写为独立确认或新冠军。
- 同批d9又完整PASS，整包0.8899574父本、BMM0.8022376，保留样本变化。singleton4ba仅一个未闭合目标，原始fullgate错误缺完整目标，下一批仅statement重放收完整错误；暂不盲修。两份width-proof2已statement PASS，尚未计时。
- 807/39840672791正在跑8eb、d9、c760和60f74aa4 D直接点积+non-NaN组合；profile修复只在独立副本，不影响正式原版gate。sourceefe8518c，seed807。
- b1696ff9组合符合“806反馈后再验”前提，可与7ac raw guard按实际吞吐安排；R继续本窗并据最可能改变下一步的结果收敛，不必等D消息。
- D标量新候选285ed400，f01-d7-special-model，仅statement探针：在原failed-finite分支直接执行原Spec/Dyadic的特殊值分支，跳过双toDyadic，正常scalar路径不动。源/证明均NOT_RUN，下一批编译。其作用与R矩阵/求和后缀互补，不扩大相近变体。
- 已核官方BenchSuite.special：NaN为sign|0x7f800000|(low|1)，low含完整23位且未强制quiet位，因此公开计分生成器本身可产生sNaN。R的last-sNaN路线有真实可达性；仍需按精确case观测命中与完整扫描成本，不把定向oracle比例当计分份额。
- 当前冠军19:28官方snapshot684更新为274，源HEAD4b7与public-v2 SHA均未变。官方累计813.98含跨suite链，不据此推算新差距。看板与当前保留d9已更新，整包公开原版加速2.48–2.51×（802/804冻结确认口径）。
