# 第十八轮研究状态

固定窗口：北京时间 2026-10-10 01:32:51—09:32:51；UTC 2026-10-09 17:32:51—2026-10-10 01:32:51。压缩上下文与额度重置不重计。新方向冻结点 UTC 23:12:51，最后140分钟留独立确认、两个完整gate和交付。

目标仍未完成：两个不同可提交候选，竞赛奖励池分别15%与5%；正式提交、注册、资金、签名不在授权范围。主目录 main 的未推送 b5cb035 已保留，本worktree从远端 e000933 建立。当前研究分支 codex/round18-frontier；可复核阶段已持续提交/推送，未推送 main。原版 sources/contract/encoder/pins/gate未修改。

当前官方快照29409，计算时间北京时间01:28:06，587条提交/552账户，freshness unknown；完整证据 official-start-live。当前官方scorer文本与本地一致，原始SHA差异只是CRLF，见official-code。目标地图 target-map.json：DNA高分窄窗仍对噪声敏感；573维持大小，有限采样约需16.5%时间下降达到5%、40.5%达到15%，不是全域或私有保证。

已完成：
- 37968740636 baselines-b-native：公开576/579/583/584的原编码器/解码，原作者及哈希保留在references/round18-public-*。539源码403，不绕过访问限制。
- 37968763899 ranges-c-native：40111987次范围查询，平均3.541项，常价段压缩不足；暂不实现全面RMQ。ranges-c-decision.json。
- 37969565393 repeat-e-native：136次完整DP、13362864位置，0次相同价格表/输入复算。停止精确重复缓存假设。repeat-e-decision.json。
- 37969110773 mechanisms-d-native：DNApack6仅genome多16312B；583abs15仅bundle.min.js少4B。均publicdecode通过，证明草稿。进入真实总时间筛选，未按大小单项否决。
- 37968372355 noise-a-diagnostic：失败已完整归档。原版隔离测量8进程完成；实际将exec测量引擎的进程请求CPU0却允许0-3，cpuset.effective也是0-3。首个multi的原始stdout因断言先于保存而遗失，不补造；stderr/context保留。只证明亲和性偏差，尚未证明噪声根因。

当前在途：
- 37969976740 screen-f：两个候选 r18-dna-pack6/r18-583-abs15，2镜像块，10版本/对照，540wholedecode、444DNA直接decode、原版提取。无完整gate。
- 37970399568 noise-g-diagnostic：修正保存顺序；2原版隔离块、4同进程未显式绑核块、4同进程绑CPU0块、2绑CPU0隔离块。不同协议分列，使用同一原测量引擎和encoder。40分钟作业上限。
- 37970737877 alternatives-h-native：r18-dna-literals（DNA路由纯literal）与 r18-579-base-tiny（去掉579通用SFshape，保留tiny选择），先核对原编码器大小。

工具：scripts/dispatch-round18.py BATCH --max-minutes N 只允许本研究分支/公开仓库/剩余窗口，默认通过已有 deflate-round9.yml 调用新round18可复用工作流。脚本都用既有gh_env凭据助手，不打印秘密。网络/提交需要exec require_escalated；已自动审核通过的授权不重复询问用户。scripts/collect-round4.py status/pull RUN diagnostics或gate --round18 --batch LABEL；实际语法是 --round 18。

新分析器 scripts/analyze-round18.py RECEIPT... --capture ... --output ... 核对原始SHA、11次rep、28文件、两轴、同源码ELF、逐块单独及同块联合几何。已在原R17完整回执上真实复算通过；analyzer-old-receipt-check.json仅分析器预检，不能计入本轮新测量。无任意压力情景。最终需按run与block展示峰值/中位/范围/零值/5与15达标次数/对照分歧，单独和同时加入的份额不可直接相加。

下一步：收齐H与F，按真实时间/大小重放评分并做敏感边界；读G诊断，区分实际绑核、共同分母、顺序效应。不停止其他路线。尚未为新候选跑完整Lean，至少预留最终两份精确pair gate；不能用提取或有限decode代替。

账户最新读数剩余99%、已用1%，未触发剩余≤1%。最多一次成功重置；工具没有指定卡的参数，当前可用卡实际到期也需再核验。共享账户用量不等于本任务成本。额度不延长窗口。

已用技能：huan-open-research及实验/数学/搜索细则；噪声调查使用diagnosing-bugs，历史份额重放和实际affinity检查均为red。当前3个解释已向用户展示：AllowedCPUs未限制实际mask、进程间incumbent漂移、方法顺序/缓存；以新观测区分，不能提前宣布修复。


## 后续检查点（UTC 2026-10-09 18:54附近，固定截止不变）

- 官方hour1快照29415已完整保存。F与I各20个配对进程共40，四份候选全部没有5%或15%观测。hour1-analysis.json记录单独/联合、逐块及对照；582pack、583abs15、DNA literals、579base-tiny暂不晋升。I的579base-tiny快15.6%但仍被支配；DNA literals慢约0.49%。
- noise-g与order-k已收齐：实际显式绑CPU0成功；原引擎在文件内固定方法顺序（不是逐rep轮转）。balanced20临时引擎副本只改调度，encoder/loader/token保留原字节；同源码绝对分歧中位数约0.104%，最大约0.199%，仍不能分辨0.108%窄窗。详见noise-g-analysis、order-k-analysis/decision。停止继续扩大测量基础设施，除非后续候选决策需要。原版协议仍是最终性能依据。
- 项目检查原先不接受workflow_call。已将R18job直接折入deflate-round9.yml并删除本轮新建的独立reusable文件；project.py check新结果PASS（22tasks、346links、10manualworkflows、205manifest pairs）。没有修改AGENTS或放宽检查器。
- 公共逐文件free-switch oracle仅作选路诊断，前后数据可使模型峰值32%变约9%，不是实际候选成绩。当前已实现r18-553-lookahead：原553三个PC文本wrapper从深度2/lazy0转为深度1/lazy16，其他引擎/原分类器不变。native37974541324真实11文件共少24982B、17输出不变，size -0.101228pp。标准screen-n运行37975340862，UTC18:44启动，40分钟cap，在途；冻结hash见manifest，尚未完整gate。
- r18-573-short-range针对实际75%的1-3项查询做直接精确min，长范围保留原loop；native short-p运行37975915149，UTC18:49启动。结果应要求所有tokens/output等于base573，后续总时间未知。
- 新公开586/587原始源码已保存；587只是579分类一处改动，586有全输入RF缓存/多轮DP refine新层。r18-586-base-only只把已有REFINE表置0，保留通用路由和基础引擎。refine-q-native已派发（dispatch文件或会话后续工具结果取run ID），同时跑原编码器和original586函数inclusive profile（parse/refine/rf_find/rf_dp/rf_exact/d_plan/s_plan/x32b_parse）。先根据真实质量损失和阶段成本决定。
- 新标准分析器脚本analyze-round18.py已在旧R17及本轮F/I真实原始回执上复算；oracle-round18.py将输入层内均值、runner间中位作乐观免费选择，跨族514迁移只作诊断，不是私有估计。原始回执SHA均保留。
- 额度18:38读数已用2%、剩余98%，从未兑换。本轮之后仍按剩余≤1%且最多一次成功处理；工具不能选择指定卡。
- 报告docs/rounds/round18.md和TASK_INDEX/tasks.json已增加本轮入口。最后状态更新时commit为e95a075（后续可能前进），研究分支持续push；main上b5cb035仍未随本轮推送。


## 两小时后：当前最好版本与在途验证（UTC 19:43附近）

固定窗口仍为UTC17:32:51至次日01:32:51，北京时间01:32:51至09:32:51；不要重计。正式15%/5%目标未完成。

当前最佳新候选r18-586-selective-rf：Rust b03af48fe3916b5b82dd563a4a69dbcc6e3e424579bd98ed0a11add6ef8b1bc6；Lean8c5d3ebbcf0f681f7005cc86a5d4a3045778af7165ffd145439b4d9b125ca9f2。只保留原RF类别13/25/26/29，public相对586多678B。screen-t原版2块在最新已取快照29421下：主对照份额2.4727/2.5190%，shadow2.4963/2.5248%，无零值；发现层，不是正式成绩。中心坐标约4.14628/34.098946。固定大小大约还需9%时间改善到5%，约37%到15%；小幅大小改善可降低速度要求，需测实际组合。

已启动精确完整gate：gate-selective-1，run37982026752，commit702574d，UTC19:42:16启动，50分钟cap。新脚本verify-round18-exact.py调用原verify.py，校验源/证明哈希、obligation、公理由原gate检查、stage1输出4865533B及上游不变；artifact末尾exact-gate，收集用collect-round4.py pull RUN exact-gate --round 18 --batch gate-selective-1。尚未拿到结果。gate-entry-preflight只是旧R17pair本地路径检查fixture，preflight_only阻止派发，不得记作新gate。

独立确认：confirm-y run37982104188，UTC19:42:57启动，4个新runner块（同一个新runner内4块），8条目含原586/shadow/base586/legacycontrols。r18_role=independent_confirmation，cap60min；尚未结果，原15/5目标未降低。需区分一个runner四块与四runner。

环形区间版本r18-586-rf-span：Rust9bb0703cc59965032e03a65d162b03ca4d1d9c3110c575166c0d9c94842d16aa；Lean仍是原586，新增r18_rf_relax的证明尚缺。span-w-native run37980664775已成功，28files与selective逐token/输出相同，6000真实Rusthelper边界差分通过。screen-x准备/已派发，运行ID看dispatch文件或后续工具返回；原协议2块，与selective parent和586shadow比较，cap60min。若有提升，还需新增helper总性证明和精确gate；不要复用selective的通过状态。

其他结果：
- screen-r run37977934141：r18-573-short-range公共同输出，主对照两块约0.49-0.54%条件份额，shadow有一块0，微小速度被对照分歧覆盖，未达5%。r18-586-base-only在R/T两runner4块全部0份额。
- selective以外RF实验：r18-586-rf-only（literal seed）多140696B；r18-586-dseed-rf（D第一遍匹配seed）多11350B，恢复多数但高端质量仍不足，未计时/未gate，暂停整版迁移；保留为局部替代。
- rf-counts-v-native run37979051837：selective真实5800000位置，平均1.1318bucket，排序2482532次，length relax130964766次。停止排序bitmap方案；据此提出rf-span。所有计数/observer均保持token/decode，仅诊断。
- #586分层profile：parse4.513s、RF2.113s；RF_find1.045s、RF_dp0.961s、RF_exact0.065s（含嵌套，不能相加）；tiny-app RF11.284ms换10B，tiny基本版845B/613tokens，full586835B/613tokens。既有576tiny844B，579tiny842B。这可作为进一步质量/成本研究线索，尚未新实验。
- 最新已保存官方快照29421，计算UTC19:04:06，589记录/554账户，freshness unknown。official-hour2目录完整原始响应和hash；不要把计算时间称实时块。

新增精确gate路由：workflow deflate-round9.yml 的R18 job直接手动启动；标签gate-*选择mode gate，其它规则见dispatch-round18.py。无自动CI、allow_private仍false。新的gate逻辑本地已用历史精确pair做预检，但第一次真实完整gate在上述run运行。

当前研究重点：保存并独立确认约2.5%的最佳成果，同时继续降低selective的实际成本或提高质量以争取5/15。原始数据high-rt-analysis.json含全部单独/匹配块联合几何与阴影差异，不能挑峰值。主目录main的b5cb035始终排除，研究分支持续push。最新已知commit702574d，之后可能前进。账户UTC19:17左右读数已用4%、剩余96%，未使用reset；记录在usage-observations。


## 三小时检查点（UTC 20:34 附近）

新快照29423，官方计算UTC19:48:20，589条提交/554账户，freshness unknown；原始数据official-hour3。固定截止01:32:51 UTC不变。

- r18-586-selective-rf完整原版gate run37982026752通过，507.3秒，Rust/Lean仍是b03af48f/8c5d3ebb。VERIFICATION.json绑定原始回执；正式提交未做。
- confirm-y run37982104188是一个新runner内四个新块。主对照条件份额2.776459–2.868103%，中位2.841345%；shadow2.620892–2.796631%，中位2.728139%。各0/4零份额、0/4达到5%、0/4达到15%。不能把一个runner四块说成四个runner，达标比例不是正式成功概率。
- 含发现T及后来作为对照X的三runner八块：主范围1.957023–2.868103%、中位2.647744%；shadow2.026243–2.796631%、中位2.572858%；与独立确认分列。hour3-confirmation-analysis.json重新核对原始SHA、精确gate、同源码对照及匹配块联合几何。
- rf-span screen-x run37982213585同输出却慢0.889652/1.444018%，条件份额1.56–2.02%，暂停精确版本。新增helper证明未完成，不能借用父版gate。
- model-aa-native run37983701790：carry-model +2619B、+0.012301pp；carry-one +1272B、+0.005632pp。没有实际计时或完整gate，暂停整版，保留真实逐文件负面证据。
- 361-ab-native run37986065782：原361底座加586RF文本再规划，public size改善0.05573944pp。源e96e4f5f、Lean仍是原361草稿，未迁移新wrapper/RF证明。准备screen-ad两原版块，有361/shadow、586和旧控制；若时间信号支持再迁移proof。
- rank-ac-native run37986533350：586A使用长匹配tie以及另加2unit/token，两版分别恶化0.00669405pp和0.00829113pp；没有支持大量速度补偿的机制，暂停精确版本，保留局部质量信号。
- 计划新的结构性RF优化：前一位置已经以不高于当前的basecost覆盖下一位置的多数等长度价格平台时，当前更新被支配。先用wholeparse逐token/编码及随机前向状态差分检验，再测原版总时间。它与失败的连续环形loop改写不同，不因span失败否决。
- 账户20:29读数用6%、剩94%，未触发reset。main b5cb035继续排除，研究分支独立提交/推送。所有目标仍未完成。


## 接近半程检查点（UTC 2026-10-09 21:17:33，北京时间05:17:33）

固定截止仍为UTC01:32:51/北京时间09:32:51，剩4小时15分；新方向冻结点23:12:51 UTC（最后140分钟确认/gate/报告）。不要重计。正式15%/5%目标仍未完成。

最新官方快照29430，computed_at UTC21:10:38，590提交/555账户，freshness unknown。official-hour4完整回执；590没有改变下列份额复算。588/589仍在前沿，source接口403明确SOURCE_WITHHELD，只在被击败后公开；原始403在source-probes-hour3，不绕过。额度UTC21:03:46已用7%、剩93%，未reset。

当前最好且唯一已获本轮完整gate的新候选仍r18-586-selective-rf。Rust b03af48fe3916b5b82dd563a4a69dbcc6e3e424579bd98ed0a11add6ef8b1bc6；Lean8c5d3ebbcf0f681f7005cc86a5d4a3045778af7165ffd145439b4d9b125ca9f2。完整gate run37982026752，507.3秒，证据VERIFICATION.json绑定原版新提取/obligation/公理/roundtrip。独立Y四块主2.77646–2.86810%，shadow2.62089–2.79663%，各0/4达到5/15。后来作为对照的数据全部保留：最新hour4-analysis含T/Y/X/AG/AH/AK共6runner14块，主中位2.52451%、范围1.95702–2.86810%；shadow中位2.49832%、范围2.02624–2.79663%；全部0零份额、0达到5/15。独立确认仍只有Y一个新runner四块，其他角色不同。

新增机制与实测：
- r18-586-rf-dominance（Rust53e2cd3d...）：前一位置最低距离成本包络支配多数后续等价价格平台更新。AE native run37988145120，20000真实Rust构造状态差分和28文件全token/字节相同；130964766次更新降到48792855（-62.7435%）。AG标准run37988811960完成，父版总时间+0.504166%、-0.153285%，条件主2.50436–2.58146%、shadow2.43911–2.48177%；符号未定，不能把少做工作当提速。尚无新helper/loop证明。真实Funs已存gate/research5/r18-586-rf-dominance。
- r18-586-rf-prefix（Rust473f40b5...）：沿用前一位置同距离匹配已证前缀。AF37988633350：20000构造匹配差分、28文件相同；2954955次比较里924911次命中，复用22884190字节。AH标准37989168571：总时间+0.321568%、+0.804710%，两块变慢，主份额2.08335–2.19695%、shadow1.97600–2.05116%；暂不投入新证明。保留历史H3prefix失败，未将此称新颖发明。
- r18-586-a-ring（Rust6ed817e2...）：A成本数组改512滚动窗，保留逻辑258距离。AI37989422658：2400真实A-DP边界/候选布局差分和28文件相同；AK37989989761标准总时间约+9.8%，远大于0.11%同源码差异；当前份额0.41–0.63%。暂停，不迁移Lean；不是所有环形存储都失败。
- r18-361-rf-text：AD37987843477，质量改善0.055739pp却总时间约4.1倍，主/shadow两块全0份额；停止完整组合，不迁移新增RF证明。
- A共享匹配缓存：AJ37989849474。r18-586-a-shared-rf只换已有A+RF类，弱全局一遍seed+共享A缓存导致multibyte多1949B（+0.00632792pp）；r18-586-a-refit所有A类使用该管线，多16679B（+0.0628936pp）。原始字节回执保留，未计时/未gate。AM37991195805的r18-586-a-strongseed-probe保留原A强seed但故意重复A搜索以隔离质量，损失降到290B（+0.000941558pp）；这是字节诊断原型，不可当速度候选或提交包。没有进行下一步共享生命周期实现。
- DNA域隔离：AL37990998091。保留65536 heads；r18-dna-split4 Rust665d288e... 将纯ACGT六mer放4096独立槽，其余前缀放余下61440槽；r18-dna-base6 Rustf5c1437c... 为ACGTN换行用46656槽，其余18880。原生实际只genome变：分别少1637/1622B，size -0.00649603/-0.00643651pp。原hash33601种前缀占26219桶，多7382种冲突；1638桶混合ACGT/其他域。新base6/4键模型有限穷举通过，Lean仍R17草稿cf4b7c1e...。
- DNA固定前沿机会重放dna-al-opportunity：假定582时间不变仍0；5%条件速度区间约相对582 -0.21529%至-0.10782%，15%至-0.121%。约0.108%窄窗仍未解除。只是所需坐标，不是新测量或成功概率。

在途或下一步：
- AP标准screen-ap run37992099832，commit8b3b540，UTC21:13:20启动，45min cap；两个DNA新表示，原582+shadow，2原协议块，split4直接DNA540/444协议按脚本执行，完整gate未安排。
- AN诊断noise-an-diagnostic run37992121536，同commit，UTC21:13:32，45min cap；selective与rf-dominance各两个相同源码/相同binary条目，同进程CPU0，两个镜像块，originalfixed11和scratchbalanced20分列。目的是分辨AG微小符号与顺序/独立分母噪声，不能用诊断替代官方成绩。research-round18-order新增可选block/protocol字段，默认旧K四块三协议保持；新预检检查5方法平衡次序。
- 已写待提交/派发demotion-aq-native：短DNA匹配在原搜索结束后转换为字面量，原codec比较0/6/8/10/12/16/all阈值，原582与split4两个冻结来源，仅publicgenome；计数token膨胀与实际大小，cap20min。它是变换token流诊断，不是可运行候选。先前gain40改变了搜索进程而literal-only多token增时；本次若有好点，应在pc_run1原匹配进程中保留end/插入位置，只改emission，然后全28文件、原计时、独立确认与精确gate。

当前没有任何本轮实测候选达到5或15。所有新优化的证明仍草稿，除selective完整gate通过。新方向还可推进约1小时55分，必须保留最后140分钟；不要由于一个CI结束提前结束8小时。本worktree只推codex/round18-frontier，main b5cb035未推送、未合并。最新已知远端8b3b540，之后可能继续提交。


## 2026-10-09T21:30:55.363444+00:00 预检纠错与在途更新

AQ demotion-aq-native run37992768154（commitbda216b，UTC21:19:39，20mincap）已完成并收齐。原582固定token位置短匹配<=8改literal，genome少8735B，但177559tokens增至869751；纯literal端点900000tokens/277999B与原始资料一致。时间不变的29430条件模型仅0.17055%，不制作实际demotion候选或投入gate；原始转换token流只作诊断。

发现本轮早先gain40预检解释有误：actual pc_HLIT=80（5bit），原源码减24实际3.5bit，不是2.5bit。原Rust8739f3ea...、原始J回执+1213B保持；manifest保留原说明并加更正，dna-cost-preflight-correction.json记录实质错误。新r18-dna-literal40-corrected Rust38299b88...真的减40实现2.5bit；新r18-dna-chain2 Rust3f2e792f...复用PC紧凑链多一个旧候选(dp=1)，保留DNA密集插入/nofold，Lean包裹调用改PC.run1c但仍草稿d7fa2759...。AR native配置已预检，等待本次提交后派发。两个候选均未知时间和完整gate，不继承原2.5bit“失败”结论。

AP run37992099832和AN run37992121536仍按原开始/超时运行。最新已知分支bda216b，main b5cb035保持排除。截止与新方向冻结点不变。


## 2026-10-09T21:40:16.945863+00:00 新18.27%信号及确认计划

AP run37992099832已完整成功并收齐。base6 Rustf5c1437c...两块主份额0.016388%/18.274972%，shadow两块0；主时间相对582 -0.290738%/-0.151834%，同源码参照却差-0.214472%/-0.665171%。块1成为左端点而删除533所以份额低；块2落533/539之间得到18.27%；换shadow都被539支配。dna-ap-analysis/decision保存完整重放，不能宣布15%达标。split4主最高0.02434%、shadow均0。

准备并即将派发gate-base6-1（原Rustf5c1437c/Lean cf4b7c1e，expectedpublicbytes5339229），以及noise-as-diagnostic（582/base6各两个同源码条目，CPU0、原fixed11与balanced20、两个镜像块）。它们是对高潜力且对照矛盾候选的有界投入。confirm-at四块联合确认base6+已验证selectiveRF已准备10条目、两个族锚点和shadow，但尚未派发；新增dispatch保护要求两个非control候选VERIFICATION精确pair均已通过后才可启动。若Lean修复，先更新最终pair与spec，再启动新确认；不要把旧proof绑定的测量当最终pair确认。

AR dna-ar-native run37993962642，commit9c1c58a，UTC21:31:22启动25mincap，在途。AN run37992121536同进程RF诊断仍在途；不要取消。账户半程读数已用8%、剩92%、reset0。main重新核对仍只有b5cb035未推送且干净，未触碰。


## 2026-10-09T22:05:30.964188+00:00 诊断收敛与新有界候选

AS run37994913713已完成：balanced20两块base6相对582均值+0.241222%、-0.097304%，582重复源码差-0.06041/-0.07877%，base6重复差+0.13145/+0.06296%。全16种候选/参照组合的评分敏感性保留在noise-as-analysis，不当成16独立样本或官方成绩。一个有利组合仍可能跨15%而其他为0，尚未解除0.108%窗口风险。base6 gate run37994890861（UTC21:40:47，50mincap，commit171b6a2）仍在原版gate阶段；confirm-at受保护，未启动。

AU run37995550516：当前A变量查询75848577次/808367027项，均宽10.6576；价格分段264904352，16对齐块覆盖15.062%项，理论减少原始项读取14.12%但未算额外成本。停16设计。已写并预检r18-586-a-block8 Rust1c43cf11...：保留原全长cost和width<32循环，用64个tagged8格块保存min/max/最早index；长查询按实际同价段，23位打包成本若可能环绕则回原逐项算法。Lean仍原586未适配。AW native spec/harness已预检2400真实DP分组价格/U32wrap/fullcost比较和28字节等价，待提交派发；不展开blocksize扫描。

AR两项后续AV run37995588693，commitb919738，UTC21:47:51启动45mincap，2原协议块、582/shadow/base6对照。literal40-corrected -9932B/+490992tokens；chain2 -321B/-6000tokens，未计时前不推成功。AN run37992121536已收齐，balanced20 dominance只+0.033/+0.064percent，和重复误差同级，暂停v0证明投入。

资源统计cost-hour4.json截至UTC21:50：46派发、42完整收集（41成功/1失败），累计完成runner18342秒；224个原协议配对进程。另4作业当时尚未收齐，不据本地缺回执判断仍运行。账单与本任务模型费用UNKNOWN，账户用量92%剩余、reset0。新方向截止23:12:51/最终01:32:51 UTC不变，勿重新计时。


## 2026-10-09T22:19:49.162453+00:00 base6证明修复与新负面确认

Gate-base6-1 run37994890861已失败收齐：原版stage3提取通过，stage4 statement失败；005-lake.log只报PC.slot_of_m_spec的六个掩码cast索引界，加一个嵌套slot分支WP续体。不是timeout，proof进程379.9秒；其余重复mvcgen警告原样保留。新r18-dna-base6-proof1保持Rust f5c1437c6e613a5a3c0740d590ac7ce972a24b86d963122c6ace3c576c3a98fd，Lean改为5212249ffd5e292793c69568ea9f34331db407d2571ab3265cb6c86e6365ea04；仅使用Array.property、cast_mod≤原值、Nat.and_le_right以及WP.spec_bind。未编译，等待gate-base6-2原版完整验收。它是同候选的证明版本，不计第二种候选。confirm-at已改绑定proof1并继续由exactcertificate保护，未派发。

AV run37995588693已收齐。literal40-corrected与chain2主/shadow两块全部0，暂停各自精确版本。base6作为对照新增两块主/shadow都是0；联合AP后base6主4块最佳18.27497%、中位0.008194%、2零值、1次≥5/15；shadow4块全0。仍未达标，不能选峰值。

AW block-aw-native run37997434316，commit690a21e，UTC22:07:06启动25mincap，在途；先看2400helper/28file等价，再决定是否原协议计时。最终截止01:32:51 UTC、新方向冻结23:12:51仍固定。


## 2026-10-09T23:45:48.685852+00:00 最后确认阶段（算法已冻结）

base6-proof2完整原版gate run38001724485通过，Rust f5c1437c...、Lean02a21f16...；gate506.4秒、Lean主体418.9秒，原900秒限制保持。原statement/公理白名单/roundtrip均通过，5339229B核对。VERIFICATION.json和两文件审阅zip已生成；不同proof版本只算同一个Rust候选。selectiveRF另一份完整gate和审阅包保留。两个正式奖励目标仍未完成。

第一台最终联合确认AT run38003736134，commit87e407c，UTC23:18:15启动，4块/10条目，60mincap。第二台BA run38004111809，commit3fa33bc，UTC23:22:37启动，4块/10条目，60mincap；第二台在查看第一台结果前预先登记，不能为追逐高点选择性重复。final-confirmation-plan.json绑定两run与两份精确pair。final report应以AT+BA两台八块为可比最终确认；S早期Y四块另列，发现/后续control观测另列。source_versions与preferred_verified_source_path已加入分析器，保留proof历史且数学复算经原AP/AV数据核对不变。

逐文件base6-time-components已精确复算候选总时间中位对应那次rep的parser/encoder，避免加两个独立中位数。AP高18.27%块，genome对总轴相对变化贡献+0.16427%，27个输出未变文件-0.31610%，合计-0.15183%；另块genome+0.21454%、其他-0.50527%。四块genome贡献始终为正。仅是观测分解，不能据此声称唯一因果根源。

交付前官方主分支复核：main6bf303f比固定a356前进1commit（2026-10-08，发生在本轮之前）。SCORING/MINER/pareto原始字节与开场相同，verifier文本同本地固定阅读副本；完整11文件diff是快照保留、评分发布标识与weight发布相关，PINS只改db/models.py、db/scoring.py、workers/weight_setter.py三项摘要。contract/encoder/scorer/verifier/toolchain未变；线上部署字节身份仍UNKNOWN。源码/官方pins阅读副本未修改。官方API现保留最近1小时快照，原始API响应已归档，勿依赖旧URL长期可用。

当前实验分支最后已知3fa33bc，后续文档/分析器变更待提交；main b5cb035保持排除。固定终点UTC01:32:51（北京时间09:32:51）不变，只继续确认、证据审计、最终快照和报告。Goal工具objective包含“未达标不得标完成”，不要因8h结束或两个gate通过而标目标complete。


## UTC 2026-10-10 00:04:28 最终八块已收齐，目标仍未完成

AT38003736134和BA38004111809均成功收齐，各4块；两台独立runner分别AMD EPYC9V74和7763，80个原协议配对进程。快照29456 computed UTC23:51:08，595提交/557账户；竞赛context freshness unknown，weights/current同快照但freshness stale，均原样保留。当前复算入口final-confirmation-summary-current.json，完整逐文件及同源码controls在final-confirmation-analysis-current.json。

A(base6-proof2)单独主中位0%、范围0–0.04344465%、5/8零；shadow中位0.00811408%、范围0–0.07509123%、4/8零。5/8块换同源码对照会改变零/非零，全部0/8达到5或15。shadow平均坐标评分20.318689%，但实际八块最大仅0.075091%，不可作为期望收益。B(selectiveRF)单独主中位1.66765171%、范围1.40019436–1.89211222；shadow中位1.66814830%、范围1.37904819–2.03431030%，均0/8零、0/8达到5/15。联合重算主A/B中位0/1.76620174%，shadow0.00808149/1.70093389%，两目标同时达到0/8。相同测量从29434换29456，B主中位2.35364363%变1.66765171%，这是竞争前沿变化，不是代码退化。

本地962个原始artifact文件逐字SHA已核对；HEAD中已提交864文件约85.99MB也与原始inventory相同，未发现换行转换破坏。新增完整审计工具将在最终提交后再次核对全部已提交文件。账户used12/remaining88，reset0；固定终点01:32:51UTC不变。余下只做证据/审阅包审计、当前前沿敏感性与下一步价值分析、最终快照/报告，不再展开新算法或新CI。


## UTC 2026-10-10 00:30 附近：新来源的有界替代诊断

两个最终精确pair及AT/BA八块保持冻结。固定终点01:32:51UTC不变。新公开源591第一次由本研究于00:13:41UTC取到（实际释放时间未知），与旧550有基础路由、缓存4→8、深度和seam价格变更；不是586改名。只读原始API与差分、作者归属保留。590只加空flush返回，当前官方被支配，未重复运行。

BB run38008542957，commit67003ac，UTC00:19:23派发25mincap，实际job61秒成功。原encoder28file/decode与原591观察器一致；base-only多1336B、size+0.00628209pp，原SFshape inclusive0.853s/parse3.432s。不能把该比值当总轴提速。因原必需gate/确认已完成，允许一次新来源诊断及反馈后的两块原协议screen-bc，预检与35mincap明确登记，保留至少10分钟收集边界。这是对新外部证据的有界调整，未延长8小时。

BC已准备新r18-591-base-proof1：Rust与BB端点相同d939eaa33d62b9d4f001e675986b3cc8b4539e56d62934db06934abbdf026496，Lean0205d5de0af39421394b100ef3f2096ac76a9409c501f8fa957784ae5a3204b9仅将外层parse_spec直接指向SFbase_spec，仍DRAFT。两个block/7条目，有591shadow；低于5%即停止本窗口进一步投入，高信号也必须先做评分敏感性及预算检查，不能借用原591完整gate。现有A/B最终表不混入该探索。

目标差距重放：29456下B同大小到5%最近样本需要约-11.67%总时间，同时间需要约-0.00193pp大小；15%对应-38.33%或约-0.00402666pp。都是所需坐标不是实现收益。七处原RF质量恢复的128种固定文件混合全部逐块/对照低于5，最好变体中位1.8271、最大2.8207，未据此扫参数。DNA最终genome贡献16个主/shadow变体均变慢，27输出不变文件决定部分总轴下降，观察分解而非唯一因果证明。

发现派生summary的analysis引用仍是CRLF序列化摘要，而当前analysis为LF；summary-binding-correction.json证明原hash正等于LF转CRLF后hash，保存旧summary，重新绑定后全部数值/runner/结论逐字段相同。所有原始artifact字节未变。新分析器显式写bytes避免重复。原始日志自带空白保留；源码新增行及脚本/文档单独检查。


## UTC 2026-10-10 01:03 附近：所有实验收齐，最后约30分钟只收尾

当前分支已推到9ae1801；之后BE回执、扩展审计和报告更新待提交。固定截止仍01:32:51UTC/北京时间09:32:51，不再启动新的云端作业。BC/BD/BE三个晚期作业全部成功，当前共57派发；正式上传/注册/签名0，reset0。

BC38009388929（72d545c，UTC00:30:58，35mincap）已收齐原协议14配对进程、一台两块。r18-591-base-proof1相对591快约23.14%，却有1336B质量损失；在新快照29469下主/shadow2块全0，停止全gate投入。Lean0205d5de只是直接wrapper草稿；原版fresh extract不等于完整gate。shape-bc-analysis-29469保存逐文件与影子。

official-hour7快照29469，官方computedUTC00:42:06，597提交/560账户，freshnessunknown。595(0.43182961047,36.5781427955)支配539；596/597也上前沿。同一最终AT/BA八块重放：A主中位0、范围0–0.04220981、5零；shadow中位0.00728955、范围0–0.07437354、4零。B主中位1.91992268、范围1.59429480–2.19468295；shadow中位1.92043235、范围1.56868097–2.36937716，均0零/0目标块。联合主A/B中位0/2.04605608，shadow0.00723526/1.96469178；全部没有同时15/5。A平均shadow坐标评分变19.235925，仍不能当期望。新快照改变窗口，最终不能沿用29456门槛。

539公开源码00:46:43UTC由普通API取得200，原Rust93159bf2...133358B/Lean86100ff4...509632B，距官方524288上限14656B。原作者、原始响应和精确文件保存在references/round18-public-539。BD38010839288（70bf473，00:51:34，15mincap）原始参照输出/观察器成功：公共5338390B，比582少2461B；CSV却多25588B，lean/bundle/prose少7166/4384/15974B。16文件走原长度捷径，12走内容回退。它不是本轮新候选，原正式gate也不算本轮新gate。

BE38011370070（9ae1801，00:59:31，15mincap）只绕开所有长度捷径，使用原内容fallback；DRAFT r18-539-content-route Rustd34940a8.../Lean a36d2264...。28文件token和输出完全相同，质量收益0，停止此端点。原协议速度、完整gate和私有/普遍等价均未建立。保留539作为新得到的有依据起点，不能说去掉长度捷径就改善质量。

扩展审计evidence-audit-expanded-preclose在BE收集前扫描到56artifact/1005原始文件，HEAD逐字一致；9份公开参照的18文件逐字等于各自API原始字段，代码重查回执也核对通过。最终BE提交后要再做完整57artifact审计。当前无在途云端作业。最后约30分钟预留01:20左右官方终点快照、全部原始/源码/zip字节核对、报告/索引绑定、远端和main边界核对、账户实际用量。不要把目标标complete，不能以继续等待扩展研究。


## 窗口结束与交付

固定八小时窗口在UTC2026-10-10 01:32:51/北京时间09:32:51结束，15%/5%正式目标未完成。最终查询official-final仍返回29469，四份数据文件与hour7逐字相同，final-snapshot-equivalence绑定确认，未虚构新的评分pass。全部57运行早已完成：54成功/3失败，352原协议配对进程，31不同Rust（含诊断端点）。最终1008原始artifact文件/18公开参照文件及两ZIP通过字节审计。账户01:17:40观测used15/remaining85，reset0；Goal计数2868550tokens，仅工具计数。

收尾审计和报告写入超出固定截止，实际超出秒数记录在budget.json；没有借此延展新算法、云端作业、正式提交、注册或钱包操作。main仍b5cb035干净、origin/main e000933，未推其他任务提交；最终分支推送后另核对远端tip。奖励目标不标complete。


## 用户明确追加3小时，UTC01:35:51恢复

新截止UTC04:32:51/北京时间12:32:51，沿用原起点共11小时，原8h关闭预算字节保存在budget-initial-window-closed.json。旧goal工具正文无法改时间字段，最新用户续跑授权和budget是当前时窗依据，goal保持active；不另建/假完成目标。原八小时报告不覆盖。BF为同场586/591/B成本矩阵，不当新候选或最终独立确认；同时核对新539CSV/textmatcher与证明复用。新方向冻结03:05:51，最后87分钟主要用于精确gate/独立确认/报告。下一次目标结束前提前完成大部分文档，避免前窗两分钟收尾超时。


## 追加窗口检查点：2026-10-10 10:23 北京时间

固定截止仍为北京时间12:32:51 / UTC04:32:51，总11小时；新方向截止UTC03:05:51，最后87分钟用于确认、完整gate、收集和交付。正式15%/5%目标仍未完成。

- BF 38014219359：2块、20个原协议配对进程完成。586、591、base591与原B同机逐文件成本矩阵已保存。32种固定自由文件混合诊断中，586校准最佳中位17.3311%，同方案591校准3.3340%。这是不可执行的机会模型，不是候选成绩。逐项评分重放确认差异包含邻居及归一化变化：前者右邻585，后者右邻588；不能挑校准宣布达标。
- BG 38015086518：539前驱低15位重建，key3版28文件输出未变；all版仅bundle少3B。停止这两版的昂贵验证。前置哈希宽度假设错误（实际pc_HB=15），在生成候选/CI前被断言拦截，失败原型已禁用并保留。
- BH 38015445461：539 row14跳步6→5仅CSV多3B。实际582路由观察表明CSV走row7单头四字节lazy引擎，而不是此前假设的row0；输出等价观察回执已保存。停止跳步端点。
- BI 38015807295：`r18-539-csv-lazy-content`将实际582 CSV机制接入539内容路由。原encoder/decode28文件通过；仅CSV少25588B，其余27文件输出一致。总5312802B，公共大小36.12845515218908%。Rust b83d5bd410c23171be87f13012e5dbc0d1de087c8a2375d50cf87d4247e6b500，Lean5719a7fd7c02f879887e98ff0ed5bb11cdbc9472220a50f502a0a9580b4c9bb4。BJ原协议计时38016030550、完整gate38016038976正在运行，不能沿用父版本验收。
- BK 38016407674：`r18-rf-sf-stage`实际把591边界重规划接到原B输出，复用按token结构匹配的辅助函数；不是整文件复制。原encoder/decode28文件通过，共少1244B，公共大小33.83071714030017%。74个迁移证明声明仍为未编译草稿，Lean494574B。将原始内容类别4..12作为一个有机制依据的计算分配变体`r18-rf-sf-content`；BL 38016734992等待/运行原生检查，完整gate和原协议时间尚未运行。
- 原8小时A/B精确验收包不修改，继续作为后备。最终版本要在精确pair gate后新开独立确认，并在同一计时块报告单独与联合份额。研究期间没有正式上传、注册或签名。
- 实时账户读取UTC02:23：已用17%，剩余83%；本轮成功重置0。当前工具列卡到期为北京时间10月30日和11月7日，未显示原指定10月23日的卡，且工具不能选择卡；未触发阈值，无兑换或购买。


## 追加窗口检查点：北京时间10:36

- 539内容CSV版完整原版gate已接受：38016038976，484.6秒，Lean Parse403.8秒，原900秒上限；原始义务、公理白名单和28文件roundtrip通过。`bind-round18-gate.py`复核整个原始artifact字节并写入精确VERIFICATION证书。Rust/Lean仍为BI冻结pair。
- BJ38016030550原协议2块16配对进程：主校准份额0和0.0275198%；shadow两块0。原539同二进制shadow时间轴快0.6568%和0.4607%。候选自身计时的代数贡献分别-0.6339和-0.8877个百分点，配对incumbent贡献-0.0228和+0.4270；这不是CPU原因证明。
- 快照29471固定539新大小轴36.565300711，15%附近速度窗口仍仅0.08641%宽；实际4个控制视图跨度0.65923%，2块1runner。坐标中心不是期望收益。
- BN38017426467：原快速分派版`r18-539-csv-lazy`与内容版配对原协议2块（20min cap），隔离原先未计时的分类成本。BO38017435935：同进程双副本、原fixed11与balanced20诊断（2块，20min cap），与原协议结果分列，不能用于替换成绩。
- BL38016734992：RF+SF内容守卫保留1233/1244B收益，仅images.bin回退11B、bf16 token变化但字节不变。公共大小33.83087428315732%，总4864300B。BM38017059987比较全stage/内容stage/原B/586shadow/591，共2块20配对进程，35min cap；完整内容stagegate38017073118，35min cap。两者正在执行。
- 当前提交3d67cb7，main仍保留其他任务b5cb035且未随实验推送。新的gate证书与回执尚待下个检查点提交。截止仍UTC04:32:51。


## 追加窗口检查点：北京时间11:04，进入最终确认准备

截止不变：UTC04:32:51 / 北京时间12:32:51。新方向截止UTC03:05:51；最后一个实现差异已于UTC03:00前冻结并派发。此后仅完成既有作业、必要证明修复、独立确认、低成本复算与交付。

- BM38017059987完成2块20个原协议配对进程。586校准：全SF版主中位8.2262%、shadow8.1767%；内容SF版主中位9.0264%、shadow8.9762%，观测区间合计8.9419%–9.1092%，均2/2≥5但0/2≥15；旧RF主中位2.0512%、shadow1.9965%。这是发现期单runner、条件预测，不是正式达标。
- 同时加入两个SF版：全SF约7.63%、内容SF约0.57%；旧RF+内容SF约1.96%/8.99%，联合收益不能相加独立份额。新SF和旧RF有实际机制/字节差异，仍共享原RF底座和作者归属。
- 使用同一BM块的591参照重算：内容SF约0.966%–1.031%，全SF约0.850%–0.939%，旧RF0。完整591族迁移是另一假设，不是置信界/保守界；586是实际父版本主校准。需同时呈现，不能把约9%写成正式可支付份额。
- RF内容版gate1（38017073118）失败仅在最后parse_spec的输出长度等式传递；74个复制/迁移声明没有报错，Parse阶段351.6秒。保留失败proof 20ec7cc...与原始回执。`r18-rf-sf-content-proof1` Rust仍16390a77d6b500f96b37441027512b89ba2d62b5091435e0527d9aa07b9834ef；Lean改为0a0171ac0dda3f6c06e574145e6b89b6b90fed45bd2d1d22be0ad199d18bacc7，仅以omega连接两条Nat长度等式。gate2 38018217854已于UTC02:46:56派发，正在运行。
- 最后一个编译差异：依赖提取脚本漏掉原591的10处SF内联标记。`r18-rf-sf-inline`恢复这些原标记，函数体、路由、深度和证明不变；Rust77f25929ae973f13707801addc5c07d568eb29d865448c26a6d9baebb697346c，Lean同0a0171ac。BP原协议2块38019015786与完整gate38019027347均UTC03:00派发，各35min cap。派发提交cdfe4955f1e5edf7f037a3f664414485dec69d02。不得根据未完成作业猜改善，也不再新开算法方向。
- BN38017426467完成：原快速路由CSV版比内容路由快0.2917%/0.0419%，28文件token/输出完全相同；所有primary/shadow块仍<0.26%，没有5/15信号，停止快路由版fullgate/晋升。内容版539完整gate包已生成，ZIP SHA256 de0068717c6351e70312880224cd329908b50f2836b0d8089d1321d683d917d7。
- BO38017435935诊断完成：balanced20父同二进制副本差-0.2105%/-0.1956%，候选相对双副本父平均+0.6868%/+0.3757%；原fixed11多方法诊断+0.0670%/+1.0226%。每项原始回执保留；均不是正式双方法协议成绩，不用于替换BJ/BN。
- 最新统一官方快照29472，官方计算UTC02:32:32.488273，597条提交/560榜单账户，weights同快照，freshness仍unknown。路径official-extension-70m。
- 最终计划：两台全新runner，每台3块（总6块），预先冻结顺序、精确Rust/Lean与目标。在BP发现期结果和完整gate到手后，从内容SF修复版/内联版选择实际较好且已验收者，与旧RF保留候选做新独立确认；同时加入539内容版作为额外已验收验证对象和591双副本参照。目标仍15%/5%，没有正式上传。预计每台35–45分钟；至少留20分钟交付。最终A/B角色要在计划明确，不能用原脚本DNA名称前缀猜角色（已支持显式role）。
- 最近账户UTC02:23剩余83%，重置0次。get_goal在UTC02:42附近累计3308518tokens、32962秒（工具计数不是账单）；goal仍active且文本旧8h，实际用户明确追加3h的budget.json为当前固定deadline依据。


## 交付准备完成：北京时间12:27

全部74个已派发作业已由实时GitHub查询核对completed：70success/4failure，无取消、无待收结果。总522个原协议配对进程，43538秒累计runner墙钟；追加窗口为17个作业、170个配对进程、14829秒runner墙钟。原始1338文件共133344337B与Git提交字节一致，18个公开参照文件校验一致。

最终两台新确认38020805122/38020818700，各3块，共6块、78配对进程，冻结提交49ec8e7943964769c82c8868bebb2d5fa9c7635e。最后抓取官方快照29481（UTC04:23:14.843636，598条提交/561账户，weights一致、freshnessunknown）。主校准：新SF单独中位7.60008482%，旧RF1.67672896%；联合7.59069271%/1.62039834%。新SF6/6≥5但0/6≥15，旧RF0/6≥5；共同15/5为0/6。新SF的591替代校准约0.84%，不是误差下界；没有正式达标声明。539补充版主/影子中位均0，保留完整gate包与独立数据。

最终主A为r18-rf-sf-content-proof1（Rust16390a77...，Lean0a0171ac...，完整gate38018217854）；主B为r18-586-selective-rf（Rustb03af48f...，Lean8c5d3ebb...，完整gate37982026752）。SF追加真实重规划机制，不能把二者份额相加。CSV额外验收版Rustb83d5bd4...、Lean5719a7fd...、gate38016038976。具体完整SHA/ZIP见docs/rounds/round18-extension.md。最终source/proof没有在确认期间变化。

main仍为其他任务的b5cb035，未推送、未合并；官方源码main仍6bf303f，官方读取副本与pins未改。未正式上传、未注册、未签名、未购买，重置0次。当前19%已用/81%剩余是共享账户观察，不是本任务账单。11小时固定截止仍12:32:51，不用收集或报告延长研究。正式15%/5%目标未完成，goal不标完成。
