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
