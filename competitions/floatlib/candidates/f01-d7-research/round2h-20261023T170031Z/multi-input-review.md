三组验证目标可行，但当前自动工具仍只验两组。**第三组未完成、缺失或未通过时，不能运行现有两组adopter后宣称三组通过。** 这是本次最主要的工具缺项；不是已观察到某个R10候选错误晋升。

round-plan已预先要求共3组、同一候选hash、额外两组在freeze后才观察、每组归一化whole ratio≤0.97且gain p05>0。baseline精确41bce485…。prepare-plan会生成原4b7/public-v2、固定policy、无observer的同job control+candidate计划，保存source/helper/请求freeze；但它只支持一个--confirmation-run，没有三组参数。adoption-guard:51明确len(packets)==2，adopt-confirmed:19只调用一次两组verify，:69–76也只序列化两组。

最小接入不需要新框架：先对同一发现组D分别调用verify_adoption(D,A)与verify_adoption(D,B)，两份都必须成功；A/B计划confirmation_candidates都链接同一D与同一候选H。然后增加本轮专用的全局核对：三组run/job/seed各3个不同值、恰好预声明D/A/B、H/41/suite/generator/reference一致、3份drawn-plan SHA齐全且不同、每组各自达到whole与p05门槛。两份receipt重复包含D，只能计作3个不同数据组，不能写4组；第三组不能用最好的前两组替代。

现有guard已经会重核artifact listing/index及全部原字节、原HEAD树的request/helper/两Kernel、source_commit=runHEAD、精确suite/generator、156case=152timed+4raw/26cell work、完整score gate/25rounds、seed链、observer关闭、run及floatlib job成功等。不同组可用不同commit来保存不同请求，但候选字节H和baseline41必须一致。各组中的候选与control在一个actual hosted job内运行，各自有原版reference配对；本地统计是独立cross-gate bootstrap，不是官方候选-vs-41直接配对admission。跨组新job不要求CPU型号相同，CPU/affinity/原日志仍要保留；全树CI不超过2，root唯一协调。

当前还有三项应补在一次性验收记录里：

- prepare确认screen只调用load_run，再核candidateSHA/policy和统计，未完整调用seed/observer/精确baseline/结论等选用检查。最终verify会拒绝不合格证据，但screen自身不能当成最终验收；派发额外组前人工核这些字段，避免无效确认。prepare依赖assert，不用-O或PYTHONOPTIMIZE。
- round-plan的3组要求仅由authorization_receipt路径引用，prepare freeze未记录round-plan/prepare-plan SHA，guard也不读groups_total。应在额外结果前冻结本轮规则hash、候选H、D身份、两个额外组角色/种子/顺序；后续receipt将其与各原requestSHA和runHEAD绑定。无需回填旧历史请求。
- unused seed扫描覆盖当前ci.py的sent/identified（含ambiguous sent）状态，但旧手工/legacy run若无dispatch receipt仍需查已执行种子台账。三组全局唯一性不能只靠两次pair检查。

真正输入多样性在freeze并执行后核验：保留每组public-drawn-plan完整SHA及原generator SHA，另存(name,kernel,timed,length,batch,m,n,p,work)结构指纹与case seed/生成字段摘要。不同seed或带seed的JSON hash变化不能单独证明shape变化；报告实际变化数，允许官方生成器产生部分相同shape。若shape全同但value生成字段/seed不同，应明确是值分布组，而不夸称新shape。没有调用生成器或读取本轮842/843等未执行输入。

只用已执行821/822示例核对这条链：run39944891642/job120385013714与run39946600549/job120390667184，各43份artifact重哈希、精确41 fullgate25轮通过；drawn-plan SHA分别5f0e8924…1108a8与79316340…e34c8，结构指纹也不同，156case中81个shape/work记录变化，35个BMM（含1raw）均变化。首个timedBMM分别(batch,m,n,p)=(18,3,445,7)/(1,16,29,17)。这只是旧原件演示，不预测842/843。

所有失败和慢组保持原字节/时间/hash，不做best2-of3或平均阈值替代。旧834/836的候选虽完整gate通过，相对41 whole为1.040345/1.008428，仍应保留为拒绝样本。任一额外组慢或未达门槛，结论应为未获三组确认、保留41；不能换reserve seed直到凑够通过。基础设施失败保留为attempt、性能UNKNOWN，若明确批准同payload/seed重跑，仍保留所有attempt并区分性能拒绝。

最终只需一份本轮专用三组receipt：原身份/请求/冻结hash、逐组ratio+p05、drawn-plan/shape证据、两份guard返回和所有失败，先于任何状态写盘完成。当前adopter本身仍输出两组，因此若未加窄范围第三组前置校验，必须由root在调用前显式审阅并绑定这份receipt；不要把旧自动输出贴成三组通过。Random90423在每次pair调用重置，D统计相同，A/B各用该调用的第二段流；这一约定应预先固定并如实标为LOCAL_INDEPENDENT_CROSS_GATE_BOOTSTRAP，不提供三组联合置信或正式准入结论。

审查只写本MD/JSON，不执行prepare/adopt/guard（load_run内部会读Git对象）、不改代码/状态/候选、也未触碰另一个Sol的冻结锚文件。R10实际三组与新性能结论仍NOT_RUN/待回执。
