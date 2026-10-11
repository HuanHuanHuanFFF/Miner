# R24 续跑状态

## UTC02:17 活跃摘要（最高优先）

固定UTC05:28:08／BJT13:28:08结束，已用6h49m，继续3h11m。最后120分钟UTC03:28:08起保留（gate/冻结后独立确认/交付）。不要因CI结束或本摘要重置时钟／提前收尾。当前已推送HEAD7566a0f13fad20276d67f0c84be6c67135877773；下面BE/BF准备与BD回执待提交。仍无稳定10/15，正式/私有/支付UNKNOWN，无上传/注册/签名授权。

### 新增已收齐证据

- AV **38101377725** 诊断结束，16paired进程全部保留。child-only setarch -R确实把personality00000000→00040000，全局randomize_va_space始终2。once同源码绝对差中位0.063414%→0.186766%（变坏）；faststack0.360575%→0.201281%（改善）。**不支持统一修复，不替换原协议，也不继续机械ASLR复跑。** layout-av-analysis.json由analyze-round24-layout.py生成，原始source本地读取副本CRLF、runner LF；已用原pin Gitblob确认差异仅换行，保留原字节，非hash相同冒认。
- AW **38101389424** 已收齐22原协议进程。analysis-aw.json／anchors-aw.json按29640：ASitem-price比once快0.677/0.579%，609主/影子两块全0，6070.109158–0.173292%，暂停独立完整gate。ATstack-adaptive对bufferstack慢4.086/4.151%，但质量让609主3.197968–3.198230%、影子3.126234–3.156502%，6073.412514–3.575804%，各两块均正；仍只发现，无10/15。
- AZ **38102490596** native收齐：stack-packed 4864126B/mean33.828446718361，28token/output同faststack；fast-adaptive4864057B/33.82807806895485，与旧X28文件完全同token/output，比AT少8B。该实际交互保留于feedback-aw-az.json，不能加和。
- BB **38102983632** 提取收齐，span-items/stack-packed/fast-adaptive全部接受，真实Funs在diagnostics/research5。span-items后续计时失败，不为它加完整gate。
- AY **38102353514** 已收齐：span-items比once慢2.567/2.667%，609主/影子和607全部0，暂停这个精确版本，见analysis-ay.json、anchors-ay.json、feedback-ay.json。
- **AT完整gate38102373130已接受且绑定**：r24-609-stack-adaptive-proof1，Rust eaa7752a8cbe6387cb8ea46ccd1d16096517e0eb895462e3ea2c6e2af297dfb0，Lean8d0d4b88407b7a0f8b79d392c950de93c1c678f967f6a7630ce023a11794cb5d；591.0s整体验收，原900sLean限制不变。现在已有6份gated不同Rust备用，但只有旧N/T曾做独立checkpoint。
- AQ **gate38102363209失败**，实际owned lc数组被Aeneas移到捕获参数后部，7处theorem调用顺序未迁移，非Rust反例。原失败pair与完整logs保留。repair-round24-packed-proof.py精确修正7处顺序，Rust不变；proof2 Lean4ca4bd8f8c9cacb61466c4f7c9738df11366fa559c82971579c545ec6f4db86e，完整gate运行中。
- Fastadaptive新proof1已按BB接口冻结：Rust ef3268f4b4183b50af7825e505266c7dc05b49e9bb1aebb1f642a5609fc6423e，Lean09f79e1d6b4d60bdcc692425a7baae6503f3995f8cc6f9937d7f23a347e9e20e，gate运行中。prepare-round24-bb-proof.py还可准备stack-packed证明；它目前只有check草稿，未freeze/gate，等BC是否保住组合收益。对其26个提取DP定义已与AQ实际Funs核对一致，参数修复可复用但不能继承完整gate。
- **BD38104046597新链前缀机制native成功收齐**：r24-609-chain-lcp8 Rustbb8b714ad8f252b46b88087abc775a7bd7da29d6f645d3b7d398b3864fc0bc0a。现有32bitprev中保存16bit后向距离+4bit capped8-LCP，所有消费者含SFtinytokens已更新。20000有限字符串/链/cap/seed模型；实际31546013查询逐次与原matcher相同，14685076由LCP三角关系直接确定，13851887额外已知前缀，78782386额外已知字节；构建新增10136801短前缀计算。28token/output同once。**操作量不代表净提速**，BE计时/BF提取已准备尚未派发。它是本阶段最后一个新匹配机制，不继续扩展无证据参数路线。

### 当前活跃CI

|run|batch|派发UTC|cap|下一步|
|---|---|---|---|---|
|38102994768|screen-bc|01:47:11|65m|两个AZ实际组合、11方法×2块；收齐后刷新官方snapshot，用主分析和anchors工具都重放|
|38104061119|gate-a-packed-proof2|02:06:21|50m|原失败7参数顺序修复；成功才bind，不覆盖proof1|
|38104425023|gate-fast-adaptive-proof1|02:12:57|50m|最终质量候选潜力版本精确gate，Rust/Lean哈希如上|

BE **screen-be**已冻结，9方法×2块/55mcap，chain-lcp8+once/once-shadow+607/609/影子；BF **proof-bf-extract**已冻结，1源/40mcap，链缓存新helper依赖与from/prior状态接口。先提交推送后顺序dispatch。BD有实质工作量减少但新增预计算，净性能未知，不要先称成功。只有BE原协议出现有意义收益后再考虑组合/全gate；若不够时间完成最终确认，保留实验起点而不掺进最终候选。

scripts/prepare-round24-final.py已写好但**未执行**：--base某双候选原协议批次 --candidate精确通过gate目录（两次） --prefix confirm-final；从base按Rust匹配，保留必要父版/3旧快参照/609主影子/607和各候选shadow，3fresh runners×3blocks，65mincap每份；要求剩>=85min和精确证书已知。若最终两份来自不同批次，需要先构造含两份实际父版的合并基准spec，不能混配错误parent。生成后逐个dispatch，收齐后同最新snapshot个体+联合，主候选9块，不把影子当18块。

最近账户UTC01:20:52剩86%，0重置／购买。最新官方仍official-feedback-ar／29640（computed01:26:38，读取约01:30）；后续当前报告前刷新。上一次dashboard --help不是支持参数，脚本意外执行refresh并被本地网络权限拒绝，**DASHBOARD/登记表保持原样**，failure.json在evidence/dashboard/20261011T020821518616Z已保留；收尾需以获授权网络权限、进程直连运行不带参数的python scripts/update-dashboard.py。它不支持指定snapshot；最终与候选分析核对快照时间，必要时刷新候选分析以同一最新榜单。

当前无活动PTY/functions cell。collector要先等exec session完成再读数据；下载优先本进程清空代理，勿改全局。重型工具链只runner。最终仍需最新DASHBOARD、方法结论、报告/index、rawSHA/CI成本审计与commit/push；不自动合并main或删除worktree。

## UTC01:38 活跃摘要（最高优先）

固定UTC05:28:08／BJT13:28:08截止不变，已用6h10m，仍继续3h50m。最后120分钟从UTC03:28:08保留。当前HEAD已推送 `bbae096728d164000cdb34b35d93cd40c42cd3cb`；新AZ派发回执未提交。主工作树main不动，无子线程。

### 最新反馈

- 最新官方 **29640**（computed UTC01:26:38；读取约01:30）在official-feedback-ar，623提交582账户，规则同版本，freshness unknown。AR所有新份额用此快照，不把29638旧值称当前。
- **AR38100245696已收齐**：query-inline相对once−0.033/−0.239%，主0与2.971643%、影子全0；暂停精确版本。a-packed相对once−1.091/−1.163%，609主3.050121–3.148662%、609影子3.065962–3.132576%，**607另口径只有0.178888–0.186328%**。1runner2发现块。once-shadow差+0.03136/−0.97594%，不能称稳定高份额。analysis-ar.json、anchors-ar.json、feedback-ar.json。607↔609此次速度迁移差1.5%–2.0%，大小差仍约0.0002222pp。
- **AX38101740543已收齐**：r24-609-span-items Rust7af26149...，28token/output同once；12000有限价长/tie模型；18306409itemuses，其中4163012裁掉前缀。长度offers351659637→327731298，短terms92074432→77515027，长groups少2699499。首次artifact下载exit1、空stage保留，进程直连重试成功（collection-ax-retry.json）；CI没有失败/取消/重跑。性能和完整gate未知。
- **AU38101365118已收齐**，a-packed/item-price/stack-adaptive三份原提取全部接受，Funs在diagnostics/research5各目录。只接口，不等于Lean验收。
- 本次新增proof1：a-packed Rust e1eb9a33...／Lean3b90b88b...；stack-adaptive Rusteaa7752a...／Lean8d0d4b88...。prepare-round24-au-proof.py按AU实际接口构造：APprices两个全局step；AT从已gatebufferstackproof1增加limit/longest及5/6元状态decr。ASitem-price仅草稿check，未freeze/未gate；等AW。
- 中途audit-mid-0600m.json通过：当时66dispatch、61已收集、779原始files共89968853B、238原协议配对进程、36不同R24Rust，累计已收集runner547.1min。是并行runner墙钟，不是账单或研究墙钟；不是最终统计。新audit-round24.py可最终再跑新输出路径。
- 账户UTC01:20:52剩86%，usage-0553m.json；0重置/购买，共享读数不归因任务费用。

### 活跃作业（尚未收取结果）

|run|batch|派发UTC|上限|范围|
|---|---|---|---|---|
|38101377725|layout-av-diagnostic|01:18:11|55m|原engine11×16对进程，child-only setarch -R对比；权限探针失败立即停止，不改全局sysctl/perf或sandbox。诊断不替代成绩|
|38101389424|screen-aw|01:18:24|65m|ASitem-price及ATbufferstack+X，11方法×2块，607/609/609影子、真实once/bufferstack/X父版|
|38102353514|screen-ay|01:35:35|50m|AXspan-items，8方法×2块，加607辅助参照|
|38102363209|gate-a-packed-proof1|01:35:46|50m|精确AQ完整原版gate|
|38102373130|gate-stack-adaptive-proof1|01:35:57|50m|精确AT完整原版gate|
|38102490596|compose-az-native|01:38:08|20m|两份新受控组合：faststack+AQ；faststack+X去掉L，以区分AT比X多8B的交互|

AZ `r24-609-stack-packed` Rust92058566...、`r24-609-fast-adaptive` Rustef3268f4...；两者Lean继承faststack2108c3e0但均DRAFT不能复用gate。新机制代码已推送，native结果未知。成本组合保持Z184/Z307/Z314全部旧inline；质量组合不改X的2x/8byte门槛。实际父参照fast-stack为已经完整gate的proof1。下一步收AZnative，若有价值把AX+AZ两份一起做三源实际提取，再按结果决定精确gate/受控计时；不加和机制收益。

当前可用完整gate备用仍是N、T、AE、faststackproof1、bufferstackproof1；只有N/T有冻结后2runner×2块旧checkpoint，不冒充新组合独立确认。当前两项稳定10/15仍未建立，607口径对微小质量优势的反例必须保留。最终候选要冻结精确pair、3新runner×3块原协议（预算允许）、自身与609同源码对照、607分列、联合重算；所有正式/私有/支付UNKNOWN，无上传/注册/签名授权。

后续收集建议进程局部清空HTTPS_PROXY/HTTP_PROXY/ALL_PROXY（曾直连恢复下载）；不要改全局配置。exec_command返回session_id时必须先write_stdin等待完成，再读取该回执或stage；本次AX曾提前读导致FileNotFound，未改变原始数据。当前没有活动PTY或functions cell。gate用exact-gate，native/extract/diagnostic用diagnostics，标准用gate；同SHA dispatch逐个结束再下一次。

## UTC01:16 活跃摘要（最高优先）

固定窗口UTC19:28:08→次日05:28:08，北京时间03:28:08→13:28:08；已用5h48m，仍研究4h12m，最后120分钟保留从UTC03:28:08起。不要提前结束或重新计时。主工作树保持；当前HEAD已推送f07e4d64，以下新回执／证书／批次待提交。

### 本次新增结果

- AM `38098908048 screen-am` 已成功收齐22配对进程。analysis-am.json在29638：faststack主3.392424–3.396483%、影子3.301763–3.408831%；bufferstack主3.384721–3.413146%、影子3.289619–3.429694%。1runner两块发现，所有>=5/10/15次数零。相对实际AE父版faststack快1.31/1.85%；bufferstack对faststack慢0.942/0.755%。相对once两块变号，原因见下。SF32比once慢2.036/6.586%，两视图全零，暂停精确版本完整gate；prepare-round24-sf32-proof.py只有接口草稿，未freeze或Lean执行。
- 两个新组合完整gate都接受并绑定：38099485452 `gate-root-word-price-proof1`，总验收1031.7s，Rust257fdd0d...／Lean2108c3e0...；38099507694 `gate-root-word-price-buffer-proof1`，1102.9s，Rust523486ff...／Lean96188bad...。原900sLean限制未改；正确性证书在各proof1目录。还没有这些新pair的冻结后独立确认。
- AO `38099461591 screen-ao` 记录合并比once慢1.038/0.813%，两视图两块全零。暂停精确inline合并版本，不由27.1%记录减少推断速度。原回执和analysis-ao.json保留。
- AP `38099777173 sf-ap-native` 两候选28token/output同once。heavy-fixedpoint实际检查0、可省0、仍6heavycalls，暂停计时。旧profile逐文件本已显示6文件各1次，应以后先查分文件调用数再造类似prototype。query-inline实际text394402→394338B且同源码编译库相同；机器码不同不等于提速，进入AR。
- AQ `38100047603 packed-aq-native`通过4800次真实Z184/Z307差分（choice和低23bit成本，窗口/tail/U32回绕），28token/output同once。保持旧inline属性，隔离R21曾意外移动never属性的混杂。进入AR。
- AS `38100756262 item-as-native`成功：实际15366033条编码items、18306409次读取价格逐次等于原ct；28token/output同once。Rust8dfea972...，Lean仍原草稿。固定每块距离价格保存在item空余高5bit，三个solver消费时解包；无性能结论。
- AT `38100776877 adaptive-at-native`成功：`r24-609-stack-adaptive` Rust eaa7752a...，实际4864065B，mean33.8281690538628；对once少61B、对bufferstack少50B、比X单独多8B（22/28文件token同X）。真实非加和交互，性能／完整证明未知。不能因稍慢就直接抛弃有质量余量版本。

### 最新快照与测量可信度

最新官方`official-mid-calibration`是29638，computed UTC00:36:07，读取约00:56，623提交582账户，freshness unknown，新622/623在前沿，未请求保护源码。`analysis-z-29638.json`逐块更新已确认N/T，仍无10/15；联合版本2已检查PASS8行，独立块仍4而非算影子8。

`calibration-b-29638.json`新工具analyze-round24-anchors.py审计完整B原始文件后回测：607→609速度误差−2.986/−3.162%，609→607+3.078/+3.265%；大小误差约±0.0002222pp。这个大小迁移差大于L的0.0001286pp改善，可能改变前沿归属。保留609主校准，607仅分列相关家族敏感性，不按高份额选参照，不把误差当私有保证。后续最终确认加public607。

`am-once-decomposition.json`：同once二进制两块原轴6.640831→6.366242；交叉candidateB/incumbentA为6.645617，candidateA/incumbentB为6.361351，所以主要是incumbent分母。tiny-app incumbent parse+52.679%，encode−0.622%，candidateparse+0.00083%；catalog/dump/server也主要incumbentparse。官方incumbent是固定stack-array hashchain，无随机哈希。局部读取官方源码SHA已记录，需runner比对。perf读取已被paranoid4拒绝，不修改global安全配置。

### 活跃／准备派发

- AR **38100245696 screen-ar**，UTC00:58:39，55mincap，10方法×2块：query-inline、a-packed；有once-shadow、609-shadow及public607。当前仍原版计时。收齐后同时跑analyze-round24.py和analyze-round24-anchors.py。
- AU **proof-au-extract**已冻结待提交／推送／派发，55mincap：a-packed、item-price、stack-adaptive三份实际提取，保留Funs；不是完整gate。
- AV **layout-av-diagnostic**已冻结待派发，55mincap。原bwrap中先探测child-only setarch x86_64 -R可用性及personality；若不允许即停止，不sudo、不改sysctl/perf权限。若允许，原engine11reps、原affinity请求、once及已gatefaststack各2同源码alias，2模式×2反序块16对进程；只改变child地址随机化，诊断不改原协议成绩。
- AW **screen-aw**已冻结待派发，65mincap，11方法×2块：AS、AT，actualonce/bufferstack/X参照和607/609主影子，核实交互与迁移。不把61B当69+11B。

先提交推送并顺序派发AU/AV/AW（每个dispatch返回完成后再同SHA下一次）；CI继续时做证明或分析。完整gate用exact-gate，标准用gate，native/extract/diagnostic用diagnostics。当前无挂起PTY；上次collect全部结束才stage。最新project check PASS31tasks1298aliases593links10manualworkflows326pairs。

账户最新仍UTC00:32剩88%，0重置/购买；约半小时后再读取。无正式上传/注册/签名授权。最终刷新DASHBOARD、方法结论、报告、索引、rawSHA审计和实际消耗，按已有授权commit/push，不自动merge。主目标稳定10/15仍未完成。

## UTC00:50 活跃摘要（最高优先）

固定截止仍为UTC05:28:08／北京时间13:28:08，最后120分钟从UTC03:28:08保留。已过约5h22m，未到收尾，10%与15%稳定目标均未建立。主工作树不变，继续codex/round24-stable-dual，最新已推送88a68cca；后续材料待提交。

- AM `38098908048 screen-am` 正在原版计时：两个实际组合root-word-price、root-word-price-buffer，以及独立sf32，11方法×2反序块，65mincap，开始UTC00:34:49。
- AE `38097639073 gate-root-prune-proof1` 已完成success，精确完整gate接受并绑定VERIFICATION.json。Rust329d3c9c...，Leandf36bda5...，总验收1062.1s（非Lean单独时间），原900sLean限制未改。候选r24-609-root-prune-proof1；Rust与AI实际计时AE相同。
- AN `38098770219 records-an-native` 已收齐：28token/output同once，4864126B；7179505次记录提供中合并1946351（27.1%）。仅Z189无限长度枚举消费路径，未改Z162有界尾部。原版总时间仍UNKNOWN。已准备screen-ao（7方法×2块，50mincap），待提交／推送／派发。
- AK native `38097518629 compose-ak-native`：两个组合分别同AE与T的28token/output；AL `38097534969 proof-al-extract`三个提取全部通过。新stack-proof1和buffer-proof1已按实际queryword参数顺序迁移，471446／472271B Lean，尚待完整gate。不能复用组件gate当组合验收。
- AJ `38096204611 sf32-aj-native`：28token/output同once，94/94solvercalls、9386981positions实际进入32位路径；137504有限RMQ检查通过。性能等待AM，证明尚DRAFT。
- AI `38095114589 screen-ai`：AC两块约快0.97–1.02%，AE快1.29–1.80%；AD慢0.49–0.57%，AG相对AE慢0.12–0.62%。因此暂停compactchild的精确版本，组合只用N/Y/AE/AC，再单独加L质量政策。analysis-ai.json在最新已捕获29628（computedUTC23:49:27，约00:00查询），各新候选份额最高约3.18%，无>=5/10/15。
- AF `38094411590 affinity-af-diagnostic`已收齐：沙箱原继承[0,1,2,3]、显式pin[0]。两块parent副本绝对差中位0.192528%→0.113012%，N却0.182030%→0.270140%。不支持统一消除波动，不替换原协议。见affinity-af-analysis.json。
- 最新官方快照29628在official-feedback-ai；新#621在前沿（源码未请求）。规则中途刷新official-rules-mid与起点同HEAD/5文件哈希。后续报告当前份额前再查询。
- 账户UTC00:32:55已用12%／剩88%，usage-0505m.json；0重置／购买，账户读数不能归因本任务。所有正式上传／签名仍未授权。

下一步提交并顺序派发AO与两个完整组合gate；CI期间继续真正不同机制或证明。保留N/T两个已验收备用，但最终任何新pair仍需新runner独立确认。最新Z联合只用analysis-z-v2.json，4主块而非把影子算8块。

## UTC23:21 活跃摘要（最高优先，前面旧摘要仅作历史）

固定起点UTC19:28:08、截止次日UTC05:28:08／北京时间13:28:08，不重置。已用约3h53m，继续约6h07m，最后120min从UTC03:28:08起保留。当前分支HEAD `cbecde5352e63a903a84705f5f0fc4ebfecfa6b3`，已推送；主工作树main仍保留。新派发回执等未提交材料均本轮。

### 已完整验收且已有新独立阶段确认

N `r24-609-price-groups` 和T/L修复 `r24-609-buffer-split-proof1` 的完整原版gate均通过，证书在各自VERIFICATION.json，原900sLean限制未改。N gate523.4s，T gate918.4s是整个验收墙钟，不是Lean单独用时。

Z1 `38091944225`、Z2 `38091958147`全部收齐，2新runner×2反序块，每份候选还有同Rust同库的副本。**主候选独立样本是4块，不能把副本加入称8块。** 使用`independent_confirmation_summary`；`summary`含8个主/副本测量，保留用于诊断。

最新查询`official-checkpoint-z`快照29621（computed UTC22:43:04、读取约23:03，620/579，freshness unknown）。主候选四块：N主0–3.202605%、中位3.088055%、零1/4；609影子校准3.045051–3.170323%、中位3.129140%、零0/4。T主3.061541–3.579673%、中位3.495769%、零0/4；影子3.495874–3.509879%、中位3.500357%、零0/4。全部>=5/10/15次数0。正式/私有/支付UNKNOWN，稳定10/15仍未建立。

**联合分析使用 `analysis-z-v2.json`。** 原`analysis-z.json`个体统计仍正确，但联合字典被后出现的同源码副本覆盖，保留旧文件，不再使用其joint字段。`joint-alias-fix.json`记录真实红→绿回归、原/新SHA及审计；R24其他分析和存在的R19–R23final-analysis均通过同一契约检查。`scripts/analyze-round18.py`已修正为每run/block/cal优先唯一candidate，无candidate才选唯一control，多alias明确跳过，并记录entry_name。`check-round24-joint.py`检查真实joint对应个体点。v2主联合N0–0.233436%、T3.061541–3.490958%；影子联合N0.150518–0.232938%、T3.408811–3.471273%。不可加独立份额。

Z1block1 public609同源码控制差2.249808%，让N从0变3.156095%。`checkpoint-z-decomposition.json`显示主要数值贡献来自incumbent分母；四角A/A9.28245、B/A9.22542、A/B9.55306、B/B9.49129。交叉角仅诊断，不是新成绩。driver.provenance的affinity是父Python驱动，不是实际engine，不可从[0,1,2,3]断言绑核失败。

### 活跃作业与下一动作

- **AF `38094411590` `affinity-af-diagnostic`**，UTC23:15，cap55。先在原measure_sandbox里读取真实继承affinity（exec true）。若已单核就停止；否则同一个原版engine、incumbent+单候选、11reps，两块反序比较原cgroup请求与显式sched_setaffinity，共16诊断进程。数据在diagnostics/r24-affinity，不能放入官方份额样本。原每进程300s不改。
- **AG `38094682573` `tree-ag-native`**，UTC23:20，cap20。组合AD紧凑child和AE删冗余状态，期待同once/组件token输出；待收齐。
- **AH `38094699832` `proof-ah-extract`**，UTC23:20，cap55。AD/AE/AG三源原版stageextract，保留真实接口，尚不是Lean/fullgate；成功后用于有价值候选的证明迁移。
- AD `38093247713`与AE `38093627577`已成功收齐，均28token/output同once。AD子链接按实际父节点编码相对距离，root仍U32；原子表256KiB→128KiB。AE对skip>=258用专门finder，去rct表和不可用cl/cd状态，保留skip<258原fallback。覆盖11/11调用、8.428M调用输入字节；lscpu原始记录L2one-size512K。不要把表尺寸等于L2解释为整个工作集适配或速度保证。
- AC `38092743994`已收齐。17个小路由wrapper inline属性，所有body/table不变；28token/output同once。原基准Cargo模板编译：once及once-shadow整个lib/text/rodata都相同；AC text394402→395746B，rodata38394→35594B，代码确实改变，速度UNKNOWN。计划和AD/AE/AG同runner四臂原协议计时；**等AGnative一致后准备批次**，4候选正好native_decode_pairs上限4，AGactualparent用AE候选名，避免重复父alias。
- XY `38091975486`已收齐，`analysis-xy.json`在29621：Y word-reuse约快1%，主2.992964–3.078363%、影子2.998832–3.019430%；X adaptive-search约慢4.2%，但质量改善69B，主3.061856–3.063077%、影子2.993791–3.068851%。均1runner2发现块、无完整gate；不因X稍慢丢掉质量起点，也不称稳定达标。
- AB `38092226149`已收齐：N-DNA成本40/16版本只改变genome，-9112B、+491688tokens。新条件大小36.5154616681；最新29621重放10/15窗口仍0.42858–0.430455，宽0.437491%。`feedback-ab-native.json`决定暂缓计时（旧PC同机制曾增加成本且0），实际新速度仍UNKNOWN，未判死DNA。
- AA `38091679388`已收齐，0新候选的606/611/614原版比较。611profile：base2.646s、SF.910s；Aengine1.791s、A_DP1.019s、RF.368s（其中find.152s、DP.181s），包含/嵌套时间不可相加推导收益。公开新来源`public-refresh-q3`。

### 继续范围／工具

下一步收AG/AH，准备AC/AD/AE/AG同场受控计时；AF运行期间继续分析或实现。候选改动之后必须新的精确完整gate与最终独立确认，现有N/T可作为已验收备用，不能宣称目标完成。

完整gate pull用`exact-gate`（路径会包含两层exact-gate）；native/extract/诊断pull用`diagnostics`；标准计时用`gate`。派发同SHA须逐个等dispatch完成，网络/凭据读取用require_escalated，普通push skipCI。当前无挂起PTY session。

最近账户UTC23:02已用9%／剩91%，`usage-0335m.json`，0重置/购买。projectcheck最新PASS313pairs／574links／31tasks／1298aliases／10manual workflows。没有正式上传/注册/签名授权。最终仍须刷新DASHBOARD、方法结论、索引、全部原始回执审计和实际消耗，按授权commit/push；不自动merge当前研究分支。

## UTC22:34 活跃摘要（以此为准）

- 已用约3h06m，固定截止UTC05:28:08，仍继续约6h54m；不要结束或重置。最后120分钟保留。
- 最新捕获`official-feedback-u`／`official-public-refresh`为29620（computed UTC22:15:46），620/579，freshness unknown。U/W按此逐块重放均0。
- **N完整gate通过且已绑定证书**：38089867281 `gate-price-groups`，523.4s总验收；Rust e13c3b1572e3ac432866768088f778c4d46d493ed5e61cf974473b5a493e4964、Lean9606dd10d8f86913c244330f06540adb8d91ba15b612b1004a5d76c17f28345e。
- **T修复后L完整gate通过且已绑定证书**：38090360927 `gate-buffer-split1`，918.4s总验收（不是Lean单独用时，原900s限制保留）；Rust4b40f24c17abd5e18468b4af0432cb2cd1b99bfd148f98e0be10e6dc3b09b426、Lean7d7aca1168639a921a45a14fabeab7a3da47ce2c9781b23f8b9f8d54c04d22a0。目录`r24-609-buffer-split-proof1`。完整gate artifacts是`exact-gate`，不要用diagnostics去pull。
- `prepare-round24-checkpoint.py`已运行，生成`checkpoint-z1`/`z2`，2新runner×2原协议反序块；N、T各自shadow＋609shadow，实际onceparent，10methods。预声明55min每run，仅在证书已知后可dispatch。**待提交／推送／派发**。这是冻结后独立阶段确认，不能代替最终后续修改版本的新确认；仍没10/15达标候选。
- U标准38090350074成功收齐，`analysis-u.json`：两块两视图0，整体几乎无时间收益（平均约+0.084%），不少文件回退；暂停exact256slotcache，命中14M并未变为收益。
- W标准38090872531成功收齐，`analysis-w.json`：约-0.26%时间，两块两视图0；暂停证明分配。无all-input等价／完整gate。
- Y native38091160946收齐：33540736treecalls，16774393zero-prefix，10355290firstwordmismatch；28token/output同once。已生成`screen-xy`，把Y与X分别计时，8methods2blocks，50mincap；**待提交／推送／派发**。不代表实现已组合。
- X native38090884260收齐：-69B至4864057，mean33.82807806895486，16文件大小变化；保留质量起点，time/proof UNKNOWN。V八槽-22B暂停，Rlongkey+1505B暂停。
- 新普通公开参照606/611/614均200，原始证据`public-refresh-q3`。611/614是RF+SF家族，主要表配置不同，没有发现外层重复解析。**AA baselines38091679388运行中**（`baselines-aa-native`，UTC22:30，20mincap），明确0个新候选，6份原版编码对象并对611做stageprofile；不可误称baseline为候选优化。原入口一次rf_refine名字断言失败，已改真实`refine`，未执行错误CI。
- 当前HEAD提交6aee36ae后有新gate证书、U/W/Y回执、XY/Z批次和状态待提交。工作区均本轮材料，没有其他用户改动。

下一步：提交推送并顺序派发XY/Z1/Z2，收AA。继续独立机制分析／实现。所有正式上传／签名未授权；0重置/购买，最新账户剩94%（UTC22:04）。

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
