# R25 续跑状态

固定北京时间窗口：2026-10-11 16:06:21–21:06:21；main基线48baf622，分支codex/round25-fast-quality，一个worktree。执行规则见[AGENTS.md](../../AGENTS.md)。目标为快速端低成本改善压缩、争取稳定竞赛池份额榜首；截至18:23尚未建立稳定正份额，更未达成榜首。

截止不重算。19:36:21拟冻结，最后90分钟保留完整原版gate、精确文件对独立确认与交付；20:06后不派新普通发现实验。已启动CI自然完成或既定超时，不主动取消。

分工：Astra/xhigh做tinyPC新helper Lean迁移，独占r25-astra-tiny-pc8-proof1等新增路径；Sol/xhigh完成duplicate-hop并审边界；Luna/max官方来源/算术审计当前空闲；主线程管理Git、CI、评分与共享入口。工具支持根加3子线程，无额外worktree，无嵌套。

已收齐19个成功作业：原15个，加HI screen/I extraction/J native/J screen。原协议共94配对进程，均发现测量。完整gate已通过end4，tinyPC proof1 gate38130996700仍运行。所有raw保留。F一次dispatch前只读网络失败另存，不是CI失败；一次本地Git暂存文件名错误也在dispatch前被冻结检查挡住，没有新增CI。

性能：A end4/backtie/gap1各两块595主影子均0；end4对combo慢0.72%–0.92%。end4完整原版gate通过，Rust03ec0aa4.../Lean4ff09d16...绑定VERIFICATION，仅保留质量/正确性组件。C dual8少14674B但总时间慢3.02%–3.26%，595/影子/578视图全0；D wordtail与end4真实444有限等价和28文件输出相同，但主测时一块慢0.495%、一块快0.060%，份额全0，暂无收益，不扩展gate/asm。

诊断：E确定dual8主成本为额外8字节哈希/维护；F的2538080次record写入贡献53017次获胜提示，不可视为无用。H mainonly实际删除这些写入后，比dual8多17230B，比combo多2556B；耗时未知，仍给一次原协议代价端点实验。G发现父链短匹配遇相同8字节前缀时有有据机会，但长匹配也依赖同前缀链，因此不整体替换prev；J只在短主匹配、dp1、合法重复前缀时多看一次prev，保持所有插入。

最新质量信号I：r25-root-tiny-pc8 Rust5c20b99c...，只替换已有row12的ETINY为专用PC引擎，8头插入、正常验证过的emitter、原路由不变。28原编码器仅tiny-config变化2487→2155B，少332B，平衡压缩比例改善0.0988095pp；总时间/份额/完整gate未知。与历史584同文件体积一致不代表整体时间相同。

最新HI/J反馈：H比dual8快1.276%–1.456%，但比combo慢1.120%–1.155%且多2556B，份额全0，暂停。J实际3497B改善、目标12文件全部较小，仍慢0.617%–0.815%，份额全0，暂停完整证明。I慢1.574%/1.682%，主份额0.071394%/0、595影子0.111155%/0，不是高份额候选。cost-i-screen逐rep恒等分解表明唯一改变的tiny-config编码成本贡献+1.50至+1.65pp，parser仅+0.18至+0.19pp；27原输出文件不是主因。

下一批K/L：counts-k-native临时encoder观察，combo/I各tiny-config和tiny-app控制，核对原token、原/观察encoder字节与decode，观察三棵Huffman树live/包数/复制量及len/dist查表；price-l-native对combo/public578/public584各28文件的len3真实原block码价与亏损覆盖做未计时观察。两个脚本分别Astra、Sol准备，root已建batch/路由，须等完整preflight通过再提交/dispatch，各12分钟上限。没有新候选/掩码/阈值扫。Luna在统计已落盘CI成本检查点。观察结果不能替代原协议时间。

当前运行：38130996700 gate-tiny-pc8-proof1，Rust5c20b99c...不变，Lean3bd53694...，真实提取14新定义/9局部定理已静态核对；尚未完整Lean/axiom/roundtrip。最终确认次数仍0。

最新完整官方捕获official-score-hi快照29680，查询18:14附近，计算18:12:14，freshness unknown；#612份额20.524717%，规则policy未变。其前29678对29677稳定字段逐项一致，Luna审计及全部raw保存。每次后续当前投影前重新捕获。

最新提交5ff84aa8已推送，HI/J原始回执和新评分待下次提交。官方source/contract/encoder/pins阅读副本未改；临时诊断副本单列。

账户北京时间17:56真实used11%/剩89%，仅共享读数，不当任务独占消耗；0重置/购买/正式上传/签名/注册。本轮推送仅实验分支。结束必须刷新看板、研究方法、round25报告/索引，核对原始回执与成本并project.py check。


18:38更新：I proof1完整gate38130996700成功并绑定，原Rust5c20b99c/Lean3bd53694，540.2秒、原900秒、公理/roundtrip全过。K38131861001因早期读取本机sources目录失败，无算法结果；修复后K2 run38132193695成功，L run38132209168成功，原始回执已收齐并推送7091eec1。K2确认短文件LL live84→106、distance7→23，树/查表工作增加；L当前PC三字节亏损仅627局部bit，Sol准备按route/dcode完整反馈，不开阈值候选。M候选r25-astra-tiny-pc-sparse Rust84ccbcbe...仅固定稀疏发射+2行lens初始化，原匹配/路由不变，Lean3bd复制DRAFT；quality-m-native38132623194运行中，actualparent tiny-pc8，另有combo/595。无其它活跃CI。账户18:35真实used15%/剩85%，未重置/购买。累计原协议仍94进程、冻结后最终独立确认0。当前目标仍未达成；固定截止21:06:21不变。


19:21更新：M计时及提取全部成功收齐，原协议累计114进程。M较I快1.23%–1.38%，但较combo慢0.467%–0.723%，主/影子/候选副本份额均0；proof草稿r25-astra-tiny-pc-sparse-proof1 Rust84ccbc/Lean36cb549未gate，暂停此版全gate。官方最新完整捕获official-score-m=29687，计算18:53:33，627上前沿、628待评分，612当前快照16.328547%；analysis-all/rank-all-29687将A/C/D/HI/J/M共6runner全部重放，新高目标仍未达。

N固定预算交换完成native38134237148：比combo多1271B/+0.00275468pp，比追加end4少保留8668B；原实际更新数的21,600有限模型相同。初版无条件head预算降1被位置模型反例拒绝，改成仅可替代第二头部时交换，否则保留原schedule；原计划/反例/修正都保留。N/T原协议screen-nt38134540554运行，11方法22进程，N与此前只测大小的tail4都含副本、actualparents，先测成本再取舍。

两份已gate的保留组件已按精确pair冻结并启动跨runner独立确认：confirm-components-a38134827293、b38134842459，同提交e231b5c6，各2块/11方法/22原协议进程，含595主影子、578、combo及owncopies。每份计划4个新主块，尚未有结果；不将旧发现/副本当确认。本轮目标仍未完成。

停止AoS新实现：Sol发现R13 pair64已覆盖相同PC read-ahead机制，31函数/常量相同；R2/R3遗漏R13的更正和旧全部反例在sol/packed-head-preaudit.md，未创建candidate/builder或CI。L真实码价审计关闭当前距离域rewrite：PC len3仅627局部亏损bit，所有标准距离码都有获益反例，不能按bits冒称重编码收益。

并行额外输入诊断O由Sol准备，root已建heldout-o-native和共享路由，尚未dispatch。预声明24主样本=3结构族×12000/400000×4固定seed，另3个196608 inactivecontrols；初始196608不覆盖end4在任何输出前按静态路由纠正。只是合成quality/decode，不算官方份额/私有成功率。Luna正在新捕获official-target-late并按实测控制波动复核first几何投入缺口。当前最新推送e231b5c6，未合main；固定21:06:21截止、19:36冻结目标及20:06普通研究派发截止不变。


19:31更新（重要恢复点）：screen-nt38134540554、confirm-components-a38134827293、b38134842459全部在screen前失败，原因是root未把本地official-score-m快照加入Git提交；540有限decode通过但无performance state，不计任何新paired/确认。原失败回执已收齐。3bd8e378已推送完整snapshot并修dispatch-round25.py：派发前核验Git树内全部Rust/Lean、snapshot，以及确认所需cert/receipt的字节；对三个真实失败commit复现失败，新commit三批17/21/21依赖通过。

当前仅3个活动CI：screen-nt2=38135725985；confirm-components-a2=38135739022；confirm-components-b2=38135751559，19:29派发，同Git3bd8e378，上限各30分钟，source/protocol/order未改；旧失败不覆盖。paired仍114，最终独立确认仍0，等待新成功结果。上次snapshot-dependency-repair-check.json有fresh本地回归结果但尚未提交。

Luna最新捕获official-target-late=29690，628已评分、612约16.38204%；target-map-late由原scorer生成可用。但其late-target-note初稿错误地把原始public time/quality直接和正式frontier比较，root已要求显式更正并用同一29690 projected字段；不要使用未修正的1.65%等绝对缺口。raw同源码变动只作独立描述。

O额外输入诊断仍在Sol实现，当前方案在首次输出前修订为24主样本(12000/400000)和3个196608 inactivecontrols；原因196608 fallback不覆盖end4。main严格原codecSHA/parse parity/decode，不计时不算份额。root已在共享native/preflight加r25_heldout_quality路由，heldout-o-native未dispatch；等脚本完整预检、所有依赖提交后再开，12分钟上限。

冻结时间19:36仍保留；当前算法源全部冻结。M完整proof草稿仍DRAFT不跑gate；N/T是否值得新gate等重试结果。保留的两份精确gate包是end4(03ec0aa4/4ff09d16)与tinyPCproof1(5c20b99c/3bd53694)。截止21:06:21不延长；20:06后无新普通研究派发。收尾仍须更新DASHBOARD/optimization-methods/round25与任务状态、全raw哈希/CI成本审计、最新榜单单独/联合重放、精确审阅包、project.pycheck和授权实验分支push，不自动merge或正式上传。

19:57更新：三项重跑全部成功收齐，原协议累计180配对进程。N比combo慢0.943%/1.031%且多1271B；T主慢1.343%/0.509%，同源码副本-0.169%/+0.080%，但最新29697所有主/影子/副本份额均0。两份gate源各2新runner×2块确认全0，595主影子与578校准均0，联合同样0；保留完整gate质量组件，暂停N/T精确版本完整证明。O诊断81原编码/双decode通过，tiny12个active全小，end4三小四等体积五大；同体积不等于同token，全部反例保留。全部34作业结束(30成功/4失败)，640份声明文件原字节校验通过，12种Rust；源码包仅两个源文件并已逐字核对。账户19:52 used18%/剩82%，无重置/购买。21:06:21截止不变，当前做完整审计、可复用结论、最终最新快照及看板交付；不正式上传、不自动merge。
