# 独立 runtime cost 诊断包：REMOTE NOT_RUN

2026-10-27 UTC；只完成包装及纯Python复验，未派CI、未本机Lean。carrier逐字节为748999、228187B，四public/spec仍B2。该包用于判断昂贵新MUL证明是否值得继续；不提供新public MUL等价证明，不属于原25轮gate、D/A/B、确认组、score或adoption。

## 父会话接入点

`development-runtime-cost-audit.py`暴露原接口`stages(g,kernel,out,manifest)`，返回且仅返回`runtime-cost-diagnostic`一个stage。要求进入时原stage顺序恰为intake/policy/statement；由原`run_stages`在原statement成功后执行。既有40420540388 statement/Submission及VerifyFull replay/7root原件已复制并绑定`historical-bindings.json`，此包不重跑v5/kernel/axioms。

父会话需自行把新audit名字接现有显式hook白名单，并仅给`f01-r19-dev-runtime-cost1`外层600秒。manifest的`diagnostic_timeout_seconds=600`只是请求元数据，现有120秒超时不会自动变化。本任务未改ci-diagnostics、gate或任何全局入口。

预算为stage注册起580秒绝对截止（包含后续pin、原statement及其现有采证）。构建180秒、全8进程measure300秒、后工具32秒均为上限，按同一个remaining扣除；measure前保留52秒，工具前保留20秒回执，原`g.own`600秒entry预算再限制。所有build/measure使用原`g.own`、原bwrap/systemd scope、原4GiB build、原benchmark内存及CPU，不修改flags、limits或环境白名单。真实构建耗时UNKNOWN，不能将这些上限相加宣称能在600秒内完成。

## 实际接口与边界

4b7 gate原字节SHA `1eb74ef7479b0023c721e776cc5e4073af21c6662b4afffcf16a48a124d27194`：`own`不检查foreign，statement结束时检查foreign，gate结束清理Layer且无第二次foreign检查。包先要求原statement Layer无foreign，然后另建`work/R19RuntimeCostMain.lean`及`work/R19RuntimeCostLake.lean`；后者是runner原lakefile全部原字节前缀加一个自有lean_exe，原lakefile不写。

**新target不在原OWN_STEMS内，若再用原foreign验收会被拒绝。** 本包不修改白名单、不伪装MainFull；新产物只允许自有root/target stem。若父要求诊断最终Layer也满足原foreign，此路线应停放，不能据此放宽原gate。

Lake固定293d接口支持独立`-f`配置，exe使用原native目标机制；链接器响应文件会写入并保留。依据是[固定CLI源](https://raw.githubusercontent.com/leanprover/lean4/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/lake/Lake/CLI/Main.lean)、[固定Exe构建源](https://raw.githubusercontent.com/leanprover/lean4/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/lake/Lake/Build/Executable.lean)和[固定Actions源](https://raw.githubusercontent.com/leanprover/lean4/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/lake/Lake/Build/Actions.lean)。这是源码接口可行性判断，真实runner构建仍UNKNOWN。

新Main的`@[inline] r19CostGuardedMul`直接调用`Submission.R19DirectBias.guardedMul Submission.mul`，未调用noinline diagnosticEntry，未新增unsafe/extern。control与guarded使用同一新binary，variant选择在Suite计时外；ADD/SUM/BMM均固定原B2 callback。未来真正public Main的闭包/传递形态可能不同，因此这里只是该诊断组合的成本。实际C须继续确认选中guarded MUL链；C/ASM语义复核状态保留PENDING。

实际构建后逐项比较原MainFull与新root的compile argv、link argv及完整rsp，只映射root/target路径名，所有flags、顺序和其他对象输入须相等。记录源、C、object/binary哈希；原benchFull/MainFull/Submission和rsp引用的本项目对象全部再次核hash。原官方源、contracts/bench、lakefile/manifest/toolchain及可用pins也核hash。依赖重建、原对象漂移、flag不匹配、缺trace/rsp/产物都停止计时。原`g.own`为阻塞接口，重建只能在该次返回后检测并停止后续阶段，单次最多180秒；本包未另造实时进程框架。

## 数据与复核

仅用已见plan1927003、1927005原字节。每plan按control/guarded/guarded/control执行，共8进程；沿原Bench.Suite timer及原INNER=3、PAIRS=500000。复用R13解析器强制156唯一行、152正ns timed行、4条零ns非timed行；同seed四进程全部checksum匹配才汇总。两block分别比较G1/C0、G2/C3，保留所有逐行ns和慢样本，不裁剪、不做ns/work校准、不推成功概率或gate分数。ns仍含原pass/checksum/cleanup等完整timer边界，并非纯算术成本。

`prepare.json`、build.log、每进程原log/rows、runs.json、每步result.json、flags-and-link原件/解析、原statement C、新caller C、实际新对象nm/ASM和stage-receipt均留档。失败保留partial；正常或异常返回后仅删除逐hash验证的两个自有work源。外层强杀时只能保证已落盘partial，不能声称finally执行。

`verify-local.py`的18项检查已通过：完整假runner8×156、统一预算/保留时间/耗尽、构建失败、坏flags、原对象漂移、坏checksum、缺行、foreign/依赖重建/noinline拒绝、audit接入/清理、错误score/source/timeout拒绝。其产物全标SYNTHETIC，并非Lean/C/ASM测量。`synthetic-fixtures/`仅本地复现，已在本目录.gitignore中排除，派发只需manifest components、audit及candidate。

当前精确hash见`package-receipt.json`，manifest components是实际远端依赖清单。`driver-before.py`是旧草稿原字节快照，不被执行。下一决定：父接hook后先检查是否只构建自有root/target；若发生依赖重建或接口不合，保留失败并停放，勿改官方gate/bench/flags来适配。
