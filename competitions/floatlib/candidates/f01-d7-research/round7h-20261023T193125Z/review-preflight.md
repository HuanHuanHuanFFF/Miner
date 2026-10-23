R11预检完成：共享CI/公有suite链可复用，但轮次工具不能直接从R10目录调用。预检只写本MD/JSON，不执行任何prepare/summarize/CI/Git或测试，不改候选、工具或全局状态，不生成未来确认输入。

本轮19:31:25—次日02:31:25 UTC；源码目标00:46:25冻结、01:15前派发确认、01:35后不启动新长作业。保留源41bce485…235169B，研究起点a06608bd…237142B；后者只余18858B容纳新运行与全部证明，不能把超限草稿视为可验证包。

复用接口和误写点：

- ci.py的dispatch/status/collect是全局工具。保留既有技术wrapper f01-d7-public-suite和D7/public-suite.py路径；它们虽名字旧，但不是R10状态。ci.py只有d6/d7特判，盲改成R11 wrapper会丢失当前4b7嵌套路径。现行默认deflate-baseline.yml会附competition=floatlib并得到floatlib job；名字更直观的floatlib-validate.yml job却叫verify，现有最终guard严格要求floatlib，不能随意换路后放宽身份检查。D公开精确commit后手动派发，allow_private=false，最多2并行。
- wrapper固定原4b7/public-v2、generator、500000pairs/25rounds，保存输入、请求、drawn-plan、26cell work和原verdict/log。旧978外层wrapper是statement-only适配，不等于新候选fullgate通过；验收只能读嵌套完整score verdict。这个双层版本关系须保留，不改官方源。
- R10 prepare/summarize的OUT来自__file__，换cwd无效：仍写R10计划/freezes/screens/result-SEED-CANDIDATE，并引用R10授权；round-status更会写旧README/round-results和硬编码R10窗口/结论。不要直接调用来“更新R11”。
- 预检期间已出现R11 prepare（SHA5d06eeed…44795），其OUT、授权、prepared_requests和多候选接口已修正。D应显式列出41、a066、新候选；脚本不会强制包含/固定这两个对照。confirmation仅要求prior-run参数存在，没有重读发现组身份/资格。它在63–64写plan/live/freeze后才于66断言轮次R11，故调用前必须先核轮次；最小后续修正是把该检查移到首写之前。freeze还应绑定round-plan、自身、summary/cohort及所用capture/diagnostic helper hash。此处均未改代码。
- summarize-run只支持--run/--candidate，固定对41统计whole/各运算/cell归一化比与本地bootstrap。R11要同时比较a066，可在同一三包job内分别总结new和a066再相除，不能拿异runner绝对ns相除。其load_run要求两者完整PASS，statement/kernel/axiom/checksum失败会先抛错，结果文件可能不存在；原始收集与失败登记不能依赖这一个摘要脚本。

三组工具已经存在，不再是“只有两组guard”的旧缺项。但R10 freeze-cohort写死已执行842/843，verify-three-groups还读取additional_inputs/selection_policy等R10字段；本次读取的R11 plan只有selection文字，没有这两个结构字段。即使复制脚本改路径，也会在旧schema或旧种子上失败。先冻结R11新种子、规则结构及外部cohort SHA，再复用已有三组验证逻辑；不要改写R10原件。研究BMM进步相对a066和“保留/展示”whole门槛要分别写清，不能事后换准入分母或把未达门槛的研究首选改称正式采用。

必须冻结：候选/父本/41/a066的完整字节与SHA、实际shape guard和布局、原plan/commit、suite/generator/contracts/Lean/FloatLib/reference、CI/workflow/adapter/本轮prepare与summary/cohort hashes、可选代码生成collector与真实符号选择、三组角色/输入种子/顺序/阈值。最终两组在源码冻结后保持未查看；842/843/850/852等R10输入已暴露，不能重新叫独立留出。source hash不做换行规范化；JSON元数据如有换行差异必须按原commit/request字节说明。本次复核850本地freeze、plan和实际artifact request的SHA完全一致，未发现该历史记录换行错绑。

形状筛查的边界已经核实：opportunity.json的5个输入SHA重读一致，分母为852单个未插桩诊断control的34个timedBMM best_ns和35992011。batch≥4,n>4,p=2那8例占24.1616%，p=1那3例占6.1998%；这只是旧完整case族的成本曝光，不是新内核阶段占比、可消除时间、官方权重或新收益。候选若guard是batch*m≥4，命中集合还会不同，不能借用旧百分比；重叠形状族不求和。先验证新guard实际触发及新C，再看完整成本。

p=2四独立行最易漏掉的义务：

1. 对每个有效行实例r_l证明b_l=r_l/m、i_l=r_l%m及各自界限。A_l(k)=r_l*n+k，B_lj(k)=(b_l*n+k)*2+j。跨batch时四个b_l可能不同，绝不能把首lane的B基址共给其余行；同一行的两个列才可共享A转换。
2. 12字段表示要逐字段连接4A和8B；八个累加器分别从+0、按k递增做acc+(fa*fb)，保留两次舍入，无FMA/分段归约/新flags。逐lane投影到原dotLoop，不以“向量同算”代替证明。
3. 输出q_lj=r_l*2+j。若内核字段是四个column0接四个column1，不能直接当row-major写出；需交织或证明scatter。若四batch固定i成组，输出本来可能有m*p跨距，连续push也要有明确置换。
4. 每个输出保留原raw A/B与自己的base地址。native NaN不能全块统一成canonicalNaN，不能用一条lane的NaN停止其它有限链。可复用原replayEarly及已证明quiet-acc吸收乘积规则，不能新造停止条件。0×Inf、Inf反号、s/qNaN payload、±0、次正规必须逐输出隔离；一行的两列也可一个invalid、一个有限。
5. 四行末尾1/2/3条要覆盖，不漏/重写任何输出。全局r=4g+l的有效性、跨batch边界和按batch重启分组的尾部策略必须一致。未观察的安全读取不自动是错误，但其值、NaN flag或累加器不能污染有效lane。
6. batch/m/p为空、n=0及p≠2保留原空/+0/完整回退。USize条件必须覆盖所有base+k*p+j、包数及ceil(rows/4)算术；仅rows<USize.size不够保证rows+3转换不回卷。巨大Nat回退不能省。

最小反例形状留给后续精确候选审查：batch4,m1,p2（四个不同B batch）；batch2,m3,p2（组内跨batch并有2行尾部）；m5/m7,p2（1/3行尾部）；空维度、n0、n1负零及一列NaN另一列有限。本次没有新增这些测试或生成数据。

代码生成证据要绑定新源码：完整Kernel/编译WORK SHA、Submission/MainFull C、trace、object SHA、nm符号、带relocation汇编、编译/链接命令和原stage UTC日志。当前ci-diagnostics和capture STEMS主要挑旧Packed/NativeDecode/NativeFinal符号，新R11内核与MainFull特化可能漏选；新候选定稿后按实际nm名冻结一组目标。只看旧F10汇编、C大小或call数不能证明新SIMD/收益。capture模块可抓原statement对象，但观测开销仍UNKNOWN；便宜的单独statement回放对象则不是最终计时对象。确认组全部observer关闭。临时ELF留在artifact外且清理，只保存源码/trace/nm/asm/metadata，不上传.o/二进制。

D可直接按以下顺序推进：先完成R11轮次/schema/对照/工具hash预检；关键证明或新布局不确定时做精确源statement诊断；随后41+a066+new同job干净完整发现；收齐所有terminal原件并登记失败/慢样本，按完整per-cell成本与新代码生成选路线。00:46:25前冻结唯一最终运行源，使用两组新未查看输入，01:15目标派发，三组逐一验收后才能写保留/展示结论。旧组件百分比不相加，正式冠军准入单列。已启动CI收至终态，即使收集越过02:31；不在截止后开启新研究。

缺项集中在R11本轮schema/cohort与失败摘要、对a066比较的实际接线、新内核地址/八投影/尾部证明、新符号机器码和完整成本。此报告不是任何R11候选的Lean/性能接受。额度重置由D按本轮条件管理，本审查没有相关操作。
