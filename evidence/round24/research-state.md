# R24 续跑状态

## UTC22:16 活跃摘要（最高优先）

固定截止UTC05:28:08，剩约7h12m，不结束本轮。分支HEAD在b35847e7后仍有W/X及报告收尾待提交。

- 当前查询快照29617，份额见`analysis-noq-lm.json`；N主约3.19%与L主约3.33%均只有1runner2发现块。没有稳定10/15候选、没有R24已确认完整gate。
- T 38089577310已收齐：split完整Rust、constant小样例、nestedflag小样例全部提取成功；原L及原nestedreturn最小例失败保留。`feedback-t-extract.json`支持嵌套提前返回结构是触发条件，内部根因UNKNOWN。split Rust与原L28token/output相同（38089590199）。新的`r24-609-buffer-split-proof1`Rust4b40f24c、Lean7d7aca11；真实参数和证明依赖顺序已迁移，gate运行中。
- N完整gate：38089867281 `gate-price-groups`，UTC22:01派发，50mincap；目前originalfullgate步骤。不要提前取消。原N Ruste13c3b15、Lean9606dd10。
- T完整gate：38090360927 `gate-buffer-split1`，UTC22:09派发，50mincap。
- U native38089849431已收齐，同once28token/output。31546013calls、13934263usefulprefixhits、201929031extraknownbytes；局部256槽同距离endpoint缓存，原搜索回退。`feedback-u-native.json`。原协议计时38090350074 `screen-u`（UTC22:09、45mincap）运行中。
- V native38090058012成功并收齐，八槽实际4864104B（-22B），仅比L再少11B，目标空间仍不足；暂停昂贵计时，原始负面投入决定保留。
- W native38090374946 `short-w-native`成功，待收集；A Z314宽度<=3直接求最小值，长循环不动，16000有限回绕/tie模型。Rust/Lean仍DRAFT。
- X `adaptive-x-native`准备好未推送／派发：只在最长匹配<8时用额外预算，最大2x旧depth；两种collector都应用，实际质量未知。源码和预声明由build-round24-adaptive-search.py生成。
- O proof1已写但因O计时主影子0/2.98%分歧且无稳定收益，gate-slot-proof1暂缓派发。N+O也未优于N，不机械叠加。
- `quality-switch-noq.json`是合成坐标，不是新测量；小于最小体积端点会切换归一化并降份额。
- 账户UTC22:04已用6%／剩94%，保存usage-0236m；0重置／购买。最近projectcheck通过305pairs，新文件后需再查。

下一步收集W；收齐N/Tgate后仅修已识别错误或绑定证书。继续U反馈、X实际质量和其他有依据方向，最后120分钟确认／交付余量仍保留。所有gate候选与发现证据按精确哈希绑定。

## UTC21:56 补充（以下旧状态保留作时序，冲突以本段为准）

- 当前剩余约7h32m；固定截止不变。最新完成捕获`official-feedback-lm`快照29615（computed UTC21:00:18）；`official-feedback-noq`正在刷新，当前份额报告先等刷新。
- LM 38085296381已成功收齐。L两块主条件份额3.317019%–3.347066%、中位3.332043%；影子3.331912%–3.338089%、中位3.335000%；仅1runner发现证据，10/15目标均未达到。M约快0.1085%但两块两视图0。`analysis-lm.json`。
- J2 38085284180成功，`diagnostic-j2-analysis.json`：固定20下609影子偏差+0.05091%/+0.13362%，均衡20为+0.02240%/+0.05815%；once的偏差却由-0.00071%/-0.03028%变成+0.10924%/+0.07785%。均衡顺序未统一消除分歧。原协议结果与此诊断分列。
- N 38085691541：28文件同token/output；长查询从53099791组合段减为43782793，约17.5%减少；单匹配占求解访问65.7723%，不是唯一位置比例。O inline-slot（38086398070）、Q slot-groups（38087259204）也28文件同token/output。组合不假设提速相加。
- NOQ原协议38087742693成功，正在收集。两个反序块9methods；待同一最新快照逐块及联合分析。
- P 38087248563：O原版提取成功，Funs留存；L提取exit1、空日志，无Lean结果。S 38088860305：精确L重现，helper-only和caller缩小样例也在提取阶段失败（0.8s），三个intake/policy/static均通过；不能把CI overall success当候选提取通过。
- 已按diagnosing-bugs建立真实红色回路。T预声明三个可区分假设：嵌套非局部返回、嵌套循环本身、公共小样例外壳。constant、flag无提前返回、完整split helper版本准备完成，待派发。失败原始文件不修改。
- O proof1仅改Lean，Rust仍f42256aa；真实提取的两个保留循环状态为(items,seen,first,c)，已按此迁移。完整gate准备完成但未运行。不得当新独立优化候选。
- R longkey6 38088869307成功：实际output4865631B，比once+1505B，prose+1021B，条件质量退步。暂无速度证据；先暂停昂贵计时。保留既有3-byte和near4 hints仍未弥补旧4/5匹配损失。
- 最近实际账户用量UTC21:23:52为已用5%、剩95%；仍0重置、0购买。账户共享，不能当本任务独占成本。
- UTC21:56后NOQ收齐，官方刷新29617（UTC21:48:44 computed）。`analysis-noq-lm.json`逐块：N主3.186242%–3.201090%，影子3.169093%–3.230083%；Q主3.042032%–3.264801%，无叠加优势；O主0/2.984899%、影子全0，主影子改变排序。O gate虽准备好但根据实际性能暂缓派发；保留证明迁移草稿。T提取／native修复继续，下一步N+质量机制及更大质量改进。


预算不可重置：北京时间2026-10-11 **03:28:08–13:28:08**（UTC 2026-10-10 19:28:08至2026-10-11 05:28:08）。最后120分钟从北京时间11:28:08起预留完整gate、精确pair冻结后新runner确认与交付。当前ACTIVE，继续循环；本文件不是最终报告。

工作区：`D:/CodingProject/Bitget/.runtime/r24-worktree`，分支`codex/round24-stable-dual`。main保持`5bd2a575`。所有研究小段已按授权提交／推送，常规提交skip CI；手动公共runner。没有正式上传、签名、注册或资金动作授权；没有子代理派发授权。入口`docs/rounds/round24.md`、`evidence/round24/budget.json`与`AGENTS.md`。

## 目标／稳定口径

两个真正不同候选，单独加入各>=10%和>=15%竞赛池份额；另重放共同加入的相互影响，不相加。优先不同质量／时间位置。公开迁移均INFERRED，正式／私有／支付UNKNOWN。最终计划每对冻结后3新runner各3原协议块（预算允许时），保留最低／中位／范围、零及目标次数、两种同源码校准；观察范围内无低于目标反例才描述稳定。不能把样本比例当成功概率。

## 当前已知

- 最新完整捕获`official-loop-l`为29612（UTC20:26:50，freshness unknown），620提交／579账户。每次报告当前份额前再查询。当前官方纯scorer取自`official-rules-start`，复算API权重误差约2.78e-17。当前公开HEAD只比固定实验pin多一个DB／快照发布提交，parser/encoder/gate实现未变；原pins不修改。
- `r24-595-gain`、`r24-595-chain3-gain`各少1444／1482B，但原协议各2块两视图均0，较各自父版慢0.24%–0.64%，暂停。`analysis-a.json`。
- `r24-609-once`去掉公开609外层被覆盖的重复解析，28文件同token／输出。B发现+后续D控制共4块、2runner，时间对609约快29%–30%；主份额0–2.979401%、中位0、零3/4；影子0–2.979894%、中位1.486103%、零2/4（29611）。这是发现／控制，不是最终冻结确认。`analysis-bd.json`。
- `r24-609-seedtail`同字节但2块慢1.3507%／1.2858%，两视图均0，暂停。
- F tiny-converge：实际2轮1改善，无“拒绝后还剩下一轮”，所以没可省工作；G distance-prior只+2总字节／极小等文件改变量，暂停二者，无性能／完整gate。
- 公开552／532加原R19 SF模块分别少1748B／1406B，实际总时间增加太多，两个组合两块两视图均0，暂停直接组合。`analysis-h.json`。
- L `r24-609-buffer-frontier`：原路径13220344个有效加入、3146060个不同码溢出、3143737次存在可替换被支配槽。新实际输出少11B，条件质量34.0915734745（609锚）；在同级父时间附近几何约3%–4%，**实际时间尚未收齐**。小字节变化确实可解除同质量支配，不能因只有11B而误删。`buffer-l-space.json`是合成时间机会图，不是候选成绩。
- M `r24-609-cap-stop`：原路径13494190有效探测，4261420满缓存探测，2120521超最大保留距离码探测；停止这类单调链尾后28文件token／输出完全相同。实际时间待收集。**M不能直接叠加L**：M依赖原四槽策略对新距离码一律丢弃，L改变了该策略。
- N `r24-609-price-groups`：SF长度查询按实际相等价格合并，每段最多32，仍用原两段16值RMQ覆盖。24800有限区间模型检查通过，native成功，**下一步读取其计数和输出对照**。不改变原编码器／价格／搜索。
- 完整R24 gate尚未运行；所有新候选Lean均DRAFT。不要继承公共父版或其他Rust的通过状态。

## 活跃与待收集

|run|批次|状态／下一步|
|---|---|---|
|38085284180|order-j2-diagnostic|运行中，固定20 vs均衡20、两块反序；诊断，不能当原协议分数|
|38085296381|screen-lm|运行中，L与M原协议两块＋实际once父版＋609影子；结束后完整收集、最新快照逐块与联合重算|
|38085691541|groups-n-native|成功并已下载，读取`diagnostics/r24-groups/receipt.json`及`r13-encoder/encoder.json`|

J原作业38083597086失败：原诊断过程默认300秒，首臂只有12/28文件，stderr明确timeout；partial原始输出和`execution-log`保留。J2仅将R24诊断每臂上限设900.0秒（已核对Config.timeout为float秒），4臂上限3600秒，job75分钟；原版单候选11次计时和Lean900秒限制没有更改。已启动作业自然结束，不取消。

## 下一步依据

1. 读取N：原／合并查询数及0..4匹配数分布，确认真实token／output是否相同；有实际减少才测总时间。
2. 收齐LM并刷新官方快照。若L提供稳定正份额基础或M真实省时，再分配完整证明和新runner；目标10/15尚未完成。
3. 如果N显示多数位置只有一个匹配，可考虑把单匹配token直接存入逐位置槽，只有多匹配用带标志索引，减少CSR间接读取／单匹配items存储。先最小真实编码与生成输入，保留旧R10 packed更慢的反例；这是尚未实现的不同表示假设。
4. A内核的`Z308/Z307/Z314/Z145`与旧R18精确价格缓存负结果一致（`revisit-core-comparison.json`）。旧范围平均约3.54，不能盲目重做RMQ或精确缓存。新I诊断A匹配约0.5s、A DP约0.72s包含时间；按等文件比值的`weighted-stage-priority.json`只是跨诊断的粗投入模型，不是速度上界。
5. K原版SF消融显示多类输入均有真实质量贡献（`feedback-k.json`），没有明显可删的大块零收益路径。不要靠精确文件身份路由或人为延时进入窄窗。

## 工具／消耗

- 收集：`python scripts/collect-round4.py status|pull RUN diagnostics|gate --round 24 --batch BATCH`。native用diagnostics，标准计时用gate；artifact叫gate不意味着Lean已验收。
- 分析：`python scripts/analyze-round24.py <gate directories> --capture <latest capture> --output <new json>`；沿用逐file原始rep审计并含已声明同Rust后续控制。纯scorer只读副本已放本worktree的忽略`sources/.../pareto.py`。
- 派发：`python scripts/dispatch-round24.py BATCH --max-minutes N`，先冻结commit＋push。它验证公开仓库、remoteSHA、批次和固定截止；最大75分钟。多个同SHA批次须顺序派发，避免run发现混淆。
- 网络/Git常用临时清空HTTP_PROXY／HTTPS_PROXY／ALL_PROXY；Git加`-c http.proxy= -c http.version=HTTP/1.1`。`gh`走`collect-round2.gh_env()`，不打印凭据。
- 最近真实额度UTC20:09:45已用2%、剩98%，0重置／0购买。定期重查；不能把已用1%当剩1%。工具不能指定某张重置卡，不盲兑。
- 项目检查PASS：31任务／1298aliases／554links／10manualworkflows／296pairs（后续新增后再运行）。轻量Python的`Failed to find real location...`提示后脚本仍正常运行；本地不安装或运行重型Rust/Lean。
