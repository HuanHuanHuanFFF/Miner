# R11 最终cohort只读预检

**修复前确有会选错D的入口；新final-choice静态核对与原规则一致。真实selection receipt、cohort和两个holdout尚待生成/验收，不能称三组确认完成。** 本审查只写报告/[JSON](D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/round7h-20261023T193125Z/review-final-cohort-preflight.json)，不改实现、测试、状态或Git/CI；没有重跑46项测试。

## 固定选择规则及已修复缺口

`final-selection-predeclared.json` 为1107 B / `7b6310569f39a0fed4d71331b0b28abe8899537608773b73c22b214a5605c38b`，记录于00:44:03.949908 UTC，早于933请求冻结00:53:31.360690及实际run创建00:55:01。新source固定E5 `e5b279b326e404d210cf2fb254c11a1773f84d2ab39cc853b9172f428c69c2d7`；backup固定6c `6c2d394dd34e8854d0d44d5d6605c194ecb27c152a1768d236481fc03fa4277d`。

只在933原fullgate完整、E5 vs41的whole≤0.97且p05>0，以及同一933输入E5 vs6c的whole<1且p05>0时选E5。否则选backup，**D必须仍为first clean930/run40044727137，不能换成933里更好的backup控制样本**。vs6c仅要求严格改善，不额外要求再快3%；不能误用通用summarize的local_discovery_screen_passed布尔值作为该项规则。

01:03:32检查到的旧freeze-cohort（afe5cc00…a10edfc，6021 B）及旧execution-binding（f70e0eeb…90ca3b，3291 B）未读取/冻结这份predeclaration，verify/adopt也不认识“first D930”义务。传入任意合格candidate+D即可冻结，因此存在误用933 backup D的路径；没有观察到实际错误cohort或adoption。

Root随后添加final-choice。当前静态核对：

- helper固定PREDECLARED_SHA和NEW_D=40047321773，直接重新认证原indexed artifact/请求/HEAD source；不靠可改的summarize sidecar统计。
- complete933中若E5失败，先只认证41控制，new_full=false后Python短路不会访问None统计，回落固定930。若933不完整、baseline失败或原证据不可认证，直接fail closed，不挑另一次“好D”。
- 完整成功时，原2000次、seed90423、每轮sub/inc配对保留的独立cross-gate bootstrap不变。take_new精确保留上述≤0.97与<1两个不同门槛。
- non-diagnostic freeze在写入cohort前调用choice.validate(candidate,D)，同时把helper、predeclared及真实receipt加入LOCAL_REVIEW_FILES；EXECUTION_FILES仍是原11份。保存receipt与重新计算的actual比较，receipt采用open(x)仅写一次。

使用D930原25round，分别提取执行新helper.compare和原summarize的统计AST，得到完全相同的ratio **0.9162235597601194**、p05 **0.06467445202258348**。仅做这次轻量只读数值重放，未调用原loader的Git读取，也未重跑回归套件。Root报告2条件回归PASS；原27三组回归需等待真实receipt，不能放placeholder，本审查未替代它们。

## 当前可绑定证据与未创建项

D930的43份indexed原件长度/hash全部匹配。真实backup与41均full/score/passed、seed930、25round，run与floatlib job120723717708均success；无capture/profile，sample_role=DISCOVERY。现有screen身份与ci-run/index/summary原hash匹配，且通过原门槛。11份当前执行文件与D930 prepare-freeze记录逐项相同；这是本地preflight兼容性检查，实际immutable HEAD blob检查仍须由Root的原guard/execution-binding执行。

01:08:48 UTC快照中，final-selection-receipt.json和cohort-freeze.json均不存在，R11没有任何FROZEN_INDEPENDENT_CONFIRMATION plan。934是statement diagnostic，不是holdout，已经派发的seed不能再作未来holdout。未来A/B尚未选择，因此不能提前断言两个具体seed“已确认未见”；只可在实际freeze时检查。

freeze构造器会检查三个正seed互异、未来seed不在所有已识别/不确定已派发记录中、R11不存在对应plan，然后一次写出UTC freeze与外部SHA。准备确认plan必须提供cohort SHA/role、相同prior D、精确seed与冻结顺序，且无observer/statement-only。验证器不独立重放全部历史时间轴；实际绑定回收时应保留“freeze→确认plan-freeze→dispatch→CI创建”的原时间证据。这是已知证据边界，当前未发现提前准备/运行holdout。

## 顺序、runner与原gate约束

freeze由实际D plan生成A=reverse(D)、B=左旋一次(D)，prepare和verify再逐组绑定实际顺序。若回落D930，两source下reverse与rotate必然都为[41,6c]，不能称三种不同排列；若选933的E5，三个source的三种顺序不同。

原guard要求D/A/B三个不同run、job、seed，且每个实际job有hosted Ubuntu24 provisioner日志。D930有该日志；runAttempt和runnerName字段缺失，保持UNKNOWN，不编造物理host身份。未来A/B的新runner证据尚待实际job，不能当前预报PASS。

共同执行绑定仍是11份实际run HEAD文件：workflow、pins、CI prepare/setup/validate/run-gates、ci.py、outer ci-diagnostics、public wrapper Kernel/manifest、D7 adapter。每个D/A/B原HEAD blob必须与cohort common execution SHA相等。新choice文件放LOCAL_REVIEW是正确边界，不要求旧D930 HEAD含后来才写的选择helper。原D7 adapter仍为 `86084d93c52022f4f4a5cfb7969e2b4a035b9a4a4f1f8c6c7e74bd412eafca24`，官方4b7/public-v2、generator、official-source-clean、25round、152timed+4raw、原fingerprint/完整verdict检查未变。

verify调用原D+A及D+B两组guard，D只算一次；三组各自whole≤0.97及p05>0，任何组失败均不能采纳。实际drawn-plan的shape/work及生成字段须三组两两有差异，不靠seed或JSON hash不同冒充输入多样性。capture discovery及任何其他source带observer的run均被拒绝用作clean D。

adopt再次读原三组、重验freeze/source、拒绝diagnostic/缺组/失败，并在写入前后重核固定文件；保留所有exact-source完整样本的role/observer标签。它仍不产生正式冠军准入结论。

## 本次文件SHA

| 文件 | SHA-256 |
| --- | --- |
| final-choice.py | `1014685a7130ec9c6aae3ef78eaf6f2dcccca9f466792d58db73056f47402c0f` |
| freeze-cohort.py（修复后） | `24ccacd0ae90ef1f38448e9ccd01d605a5627db5d82a8f519755b2f61d59e30e` |
| execution-binding.py（修复后） | `8783d5a85097c6457757093b66951a1ebdb7ed706a02ee298d4294e53285b212` |
| prepare-plan.py | `9d66505dc3b33bc17ec39727a86c54c0e8b89a290ff28e7a623616a5c3028ac5` |
| verify-three-groups.py | `84b7c319d81cefca2183ef6cf83d805153757d4a83dd15fbda480819485af41a` |
| adopt-three-confirmed.py | `698c98364ce28cfc030182f9490f227d744415afcbb29a416baf626594d56ebc` |
| summarize-run.py | `efd1337eba52b04b8c798a818384d6db73305fd9efe6c0ad30221c7a1626ba50` |
| adoption-guard.py | `b009d7b2f2161d756584013ebfc8adea3d2373ddac04c08a4602eb53e4c7a0b2` |

静态修复未见额外选择规则偏移。下一节点必须回收真实933终态、只写一次选择receipt、生成正确candidate+D的cohort后，再补actual bindings与27项回归；A/B原gate、顺序、独立输入/runner及最终三组采纳仍全部未完成。当前报告不能作为确认完成回执。
