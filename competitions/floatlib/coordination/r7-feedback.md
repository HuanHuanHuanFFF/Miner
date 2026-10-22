# R7开发反馈

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
