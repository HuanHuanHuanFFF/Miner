# 812独立确认与自动选用审查

开始2026-10-23 04:58:54 UTC，最多10分钟；本轮依据04:52:58的新明确授权继续验证，不延长原十小时研究预算。本审查只读代码/协议/现有授权与计划，未执行audit/adopt、Git、CI、实验或联系其他会话。仅写本报告及同名JSON。

**在自动晋升cc06前必须修复：adopt没有相对60f的收益门槛；确认/aggregate绑定也应补成fail-closed。当前计分重算公式与原4b7 public-v2一致。811/814仍运行中，本审查不判断其终局，更不能由两次公共gate推导正式冠军准入。**

## 阻断项

**B1：完整正确性通过会被直接当成“值得替换”。** `adopt-confirmed.py:19–27`只要求两个full_gate、相同候选SHA、不同run/seed及confirmation_candidates链接；第43行开始写结果，第47行更新保留候选，之前没有任何相对previous的收益判断。

静态反例：两次cc06相对60f的reference-normalized whole-entry ratio都是1.10，其余身份/完整gate条件均满足，代码仍会采用并生成“再降耗-10%”文案。原gate `score:681–695`只做checksum和汇总，返回None；passed不承担对我方60f的准入判断。

最小修复：**所有写操作之前**，验证两份comparison的candidate/parent SHA、有限正数、指定收益指标及冻结的本地选用门槛。不满足或缺失则保留60f，结果仅记录为PASS correctness/性能不选用。不能只检查cc06对shipped的v.ratio≤0.97；那不是对60f的改进。

仓库track-rules记录ratio≤0.97与配对bootstrap收益p05>0，同时明确旧/新suite边界。本轮若沿用它作为**本地选用bar**，须提前冻结阈值、指标与统计方法；缺有效p05不得自动晋升。两个独立gate各自与shipped配对，cc06和60f并未彼此按round交替测量，不能把两份round数组同下标拼成“官方配对bootstrap”。可以另行明确本地跨gate、保留各自reference配对结构的独立重采样方法；这仍不是官方admission。最弱必要条件是两轮相对60f均确有正收益，不能替代已有更严门槛。

**B2：不同run/summary seed不证明独立seed/new runner。** `audit-suites.py:25`只把summary.seed写入row，未核verdict.seed；`adopt:24`仅比较两个row.seed及run ID。后者未读取ci-run/job身份，也不要求summary.source_commit等于原GitHub run head SHA。adopt还直接信任可写aggregate，未再次核原verdict/plan SHA及其来源。

最小修复：对811/812选用路径强制当前provenance schema，不走audit第16行“缺adapter_sha也继续”的兼容分支。保存并核run_id/run_attempt、实际job/runner记录、checkout/source_commit、原artifact index、summary/adapter/plan/verdict hashes；要求plan.seed=summary.seed=verdict.seed，811/812不同，且812在既有输入/运行账本中未使用。GitHub hosted `ubuntu-24.04`不同run提供新runner的基础，但脚本必须绑定实际workflow/job记录，不能只写一条new-runner标签。within-run verifier fingerprint起止一致已有检查；同批control/candidate及跨轮协议/工具链身份变化须显式审核。

**B3：baseline与协议/observer完整绑定不足。** `adopt:23`按名称找comparison，不核comparison.kernel_sha256/parent_sha256或两个记录suite SHA相同；第26行确认链接只约束cc06，未冻结60f哈希。第27行仅拒capture_codegen，不检查profile_parent/profile_current。当前811计划三者均false，因此不是本次discovery配置错误，但不足以保护后续自动确认。

最小修复：812计划必须冻结cc06=`cc06a47faf9f982c324d265c90beb2b9cea953f33773eabed3ed6eab29260dfc`、control60f=`60f74aa4af01a9b35ece66a7c310e6b05b5b84b9b7121a4cccd12a0a9c987e15`；adopt逐行核comparison与两份record/原输入一致。要求两轮同suite/generator/rounds/pairs及完整case/cell集合，全部observer字段false且实际row无capture记录。不能因聚合名称相同就接受另一个baseline版本或旧schema结果。

## 812验收必须绑定的字段

- official commit：`4b7e83841cc0c32c6529f533923c73d33b5ecf97`；public-v2 SHA：`a16494e97c6a073bfd8accf72480c34534c87808092c56074fdcfa42cd34868a`；generator SHA：`7198464dfc08f4bb2a3a5e31ce5a105964d1d73ad6b11ee49e682a30c04daf69`。
- seed812、25 rounds、500000 pairs；实际drawn-plan/hash、152 timed+4 untimed、26 scored cells、timed cell_work与原generator/plan对应。不要重新发明/覆盖官方argv/env；有效CPU/绑核/工具链配置按原日志保存。
- 两个精确Kernel SHA、原verdict SHA、passed/mode=gate/stage=score、exit0、原阶段日志、25轮数据及fingerprint起止一致。checksum通过由绑定原gate的passed结论支持；verdict没有逐case checksum字段时不能虚造该字段。814 statement-only不能混入这组条件。
- 812冻结plan包含候选SHA、prior_discovery_run=39903049887、baseline SHA、sample role、无observer；同时将plan SHA/adapter SHA/source commit绑定实际新run/job。811实际提交应为`4b9f84c230ca2e26d21486568e9d09adeb60d151`；812可以是保存确认计划的另一个精确提交，候选字节必须相同。
- 两轮完整raw数据、正有限的headline/operation aggregates、相对同一60f的指定指标、预先冻结的选用阈值/置信计算结果。所有缺项标UNKNOWN并阻止自动adopt，不能用另一轮成功补齐。

上述suite/generator身份由既有807原artifact字节重新核对，并与固定原generator源码一致；这不是811/812终局验收回执。

## 非阻断与已正确部分

`audit:41–43`以cell ns/work乘该cell所有timed case的work，还原全entry totals；与原`benchmark_suite.summarise:450–483`“每case跨轮最小值分别求和”一致。不是平均各cell ratio，也没有把raw checksum案例计入耗时。time_share是该计分口径的份额，不是25轮真实wall-clock份额。未发现该公式的确定计算错误。

statement-only已有full_gate断言阻挡；原summary/verdict/source/index部分哈希核对、fingerprint起止校验均有价值。需要补齐的是选用路径的强绑定及收益判断，不需改原gate或停掉正在执行的授权CI。

`adopt:51–62`还会沿旧window_finished/active_jobs写资源文案，而当前新授权在`authorized_validation_continuation`。这会错误写成“新CI尚待另行授权/无新CI”等旧窗口描述；属于状态/发布问题，不改变数值。最小修复是保留原研究截止事实，优先按新授权回执及其实际active_ci列表生成continuation资源/remaining文案，不创造新研究时间预算，也不再次索要已给授权。

结论：继续收齐811/814原结果；在任何cc06自动晋升前先修B1及本轮必需的B2/B3绑定。公共选用、正式admission、排名和正式提交继续分列。
