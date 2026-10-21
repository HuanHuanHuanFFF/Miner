# 第26轮追加四小时：稳定份额研究

用户追加的固定北京时间窗口为 **2026-10-12 14:48:52–18:48:52**，目标仍是两份不同候选分别稳定取得竞赛奖励池5%与10%，联合加入另算。原八小时的断电中断记录见[原轮次报告](round26.md)，两段不能拼成连续执行。执行规则见[AGENTS.md](../../../../AGENTS.md)。

全部实验与测量核验已收齐，研究输出已冻结，稳定5%／10%目标未完成。最终材料采用下述最新快照；截止前的最后身份查询与用量另保留回执。固定[预算及授权](../../evidence/round26/extension4h/budget.json)不改，阶段记录见[状态](../../evidence/round26/extension4h/state.md)。

## 已执行结果

**截至本阶段，稳定5%／10%双目标未完成，没有推荐正式提交包。** 追加8份不同Rust，6份完成原协议发现计时、2份未计时；24次云端作业全部成功并收齐，包含16次native、6次standard和2次环境diagnostic。原协议88份配对进程不是88份独立候选确认；每份主候选仅一runner两发现块。完整Lean／原版公共gate与冻结后独立确认均未运行。

最新保存的完整榜单为**29888**，官方计算UTC10:43:57.085857，查询UTC10:44:25–10:44:44，freshness=`unknown`。[原始响应与SHA](../../evidence/round26/extension4h/official-last-live/receipt.json)及[独立评分核验](../../evidence/round26/extension4h/score-audit-29888/decision-note.md)确认659行、104点前沿，公式与API重放一致。以下份额全是该快照的**条件公共预测**，不是正式可支付成绩。

| 追加候选 | 原协议两主块时间变化 | 主参照份额最低／中位／最高 | 零值次数 | 结论 |
|---|---|---|---|---|
| A14 tagged-head | 慢3.121938%／3.336959% | 0／0／0% | 2/2 | 标签跳过收益未覆盖维护成本 |
| A16 near-retain | 未计时 | UNKNOWN | UNKNOWN | 仅少510B，实际省写覆盖过薄 |
| A18 window-filter | 未计时 | UNKNOWN | UNKNOWN | 保输出，新增读取明显多于取消common的机会 |
| A19 safe-word-offsets | 慢0.277417%／快0.148876% | 0／0.388151%／0.776302% | 1/2 | 同源码副本均0，没有稳定收益 |
| B21 tree-prefix | 慢1.779525%／1.078100% | 0／0／0% | 2/2 | 新表维护抵消少做的比较 |
| B27 tree-packed | 慢2.840276%／2.429873% | 0／0／0% | 2/2 | 去掉独立表后打包／解包仍未形成净收益 |
| B31 a-flatten | 慢0.733903%／0.716664% | 0／0／0% | 2/2 | 大量填充和补齐扫描有实际代价 |
| B36 a-no-owner | 慢1.408720%／0.154823% | 0／0／0% | 2/2 | 删除来源写入后仍有恢复来源和base维护成本 |

六份已计时候选的12主块中11块为零，达到5%／10%的次数均0。A19换影子参照后为0／0.884898%，同源码候选副本在两种参照下均零；不能把参照和副本当成额外独立runner，也不能以峰值晋升。全部逐文件总压缩时间、实际父版、二进制、环境、原始回执、未计时版本及精确Rust／Lean哈希见[完整候选对比](../../evidence/round26/extension4h/candidate-comparison-29888.md)、[机器台账](../../evidence/round26/extension4h/candidate-ledger-29888.json)和[按角色分层](../../evidence/round26/extension4h/all-roles-29888.json)。

原窗加追加共28份不同Rust，13份做过原协议主计时，26主块中25块为零；全轮60次作业57成功、3份原窗失败全部保留。没有将未测版本写成0%，也没有从复制的父Lean推定新版本通过gate。

## 评分与组合

[按同一29888快照重放](../../evidence/round26/extension4h/all-analysis-29888.json)包括全部12次原协议运行、186份配对进程。对有共同run／块／校准的组合，重新加入两点后计算前沿和归一化：tree-prefix＋tree-packed、full-owner＋no-owner的已有同场视图全为零。hash17＋allow-near的旧主参照仍全零；第一影子块分别加入为1.529768%／0.293051%，联合变为1.528745%／0.292533%，第二块仍双零。辅助控制角色见原表，没有拼凑新独立确认。A19与其他路线没有新的共同确认，联合稳定份额UNKNOWN。

最新几何目标只用于决定投入，不是实测成绩。保持锚点质量时，658最近的5%／10%命中格点分别约需时间轴降低2.83%／4.73%；552相应约需15.71%／27.41%。评分非单调，不能把最近命中说成“超过该速度必定达标”；完整命中区、邻居切换和各源码单runner的观测敏感性保留在[二维取样](../../evidence/round26/extension4h/score-audit-29888/score-map-29888.json)。

同时重算旧备选：[R24、R25及旧快速父版历史原始回执](../../evidence/round26/extension4h/historical-29885/historical-replay-summary-29885.json)覆盖去重后的330份配对文件，没有新增测量。R24与R25最终候选的旧独立确认在此快照全部为零；旧chain-halfhead的四主确认块主参照最低0、中位0.967857%、最高2.301892%，两块为零，也未到5%。历史控制峰值单列，不作为本轮稳定成果。

## 实验怎样改变取舍

[A路线报告](../../evidence/round26/route-a/a14-a20-route-summary.md)保留短标签、固定上一距离、近头保留、末读、必要窗口和安全算术各自的反例。真实构建证据显示很多源级开销已被编译器消除；A19实际只改到一个lazy热guard，完整时间又受encoder与incumbent分母变化影响。没有围绕微峰扫更多相似变体。

[B路线报告](../../evidence/round26/route-b/b41-extension-route-close.md)覆盖树前缀的两种真实表示、官方配置下的向量化、DP flatten及去owner修复。B37主解析时间分别增加31.05ms／28.34ms；第二块较小的评分时间轴回退来自分母项抵消，不是稳定解析加速。实际提取还将新owner helper变成两个循环，说明源码证明预审必须再与真实接口核对。此处extract-only通过不等于Lean、原始义务、公理白名单和完整round trip验收。

A20在新runner上按exe哈希、PID和启动时间绑定原引擎，52个运行期样本的有效mask一直为0–3，最后执行CPU出现0和2；原CPU0请求未形成单核限制。[精确遥测](../../evidence/round26/route-a/a20-placement-feedback.json)与[官方接口文档核查](../../evidence/round26/extension4h/measurement-followup/decision-note.md)分开保留。它不能追认另一runner上的A19历史根因；频率和祖先控制器状态仍UNKNOWN，也没有用诊断时间修正候选份额。

V1随后对精确658／incumbent做两份同scratch引擎、同DSO进程，原timer外记录CPU端点；原树、源码、encoder与pins未改。两过程各有1232个measured阶段调用，端点不同分别2／1次；这些不是迁移概率。实际user.slice未向下启用cpuset，app.slice未向scope启用cpu，故对应scope没有控制接口。48个同文件／方法／阶段且共同CPU端点的跨过程分层全部在CPU3，仅catalog parser一组观察范围不交叠，中位相差约1.366%。异端点与部分长耗时共现，但端点相同也不能排除途中迁移；CPU、进程、频率等因素未被独立干预。[原始绑定分析](../../evidence/round26/extension4h/v1-analysis.json)、[A23独立复核](../../evidence/round26/route-a/a23-v1-result-review.md)均不生成候选分数或校正A19。

## 资源与剩余验收

追加24作业的非跳过job墙钟合计**6748秒，112.47分钟**，可并行，不能当实际账单费用。候选搜索在9:18:52UTC截止；没有值得gate的候选后，[明确调整未用验证预留](../../evidence/round26/extension4h/verification-reserve-adjustment.json)，于09:59启动唯一的V1测量核验，实际job388秒完成，总截止不变。已启动作业均自然完成。模型账户用量另保留启动、30分钟、一小时、两小时、三小时及收尾读数；账户读数共享，不等于本任务独占成本。没有重置、购买、正式上传、注册、签名或新增链支出。

**VERIFIED**：精确源码、原生有限检查、原协议发现计时、原始字节与CI状态、实际engine遥测及公式复算。**INFERRED**：条件份额、二维投入空间、机制成本解释与后续路线。**UNKNOWN／未完成**：两个稳定目标、私有集迁移、候选完整gate、冻结后独立确认和正式可支付结果。

保留的成果是可复用机制条件、观察器、真实负例和两个公开起点的差异，不能按作业数量宣称研究成功。后续优先动作须由具体收益缺口和已测反例决定；新的源码修改、CI或正式提交仍按后续请求的授权范围处理。

下一轮路线已做[既有证据审查](../../evidence/round26/route-a/a21-next-route-review.md)：仅保留一个条件性U118两起点深搜预算归属问题，先查实际赢家和发射存活，不直接写新生产候选。该路径仅约6.35%的总时间轴parser权重，且已有高赢家存活率反例；没有证据支持再凑一条主线或预期稳定达到目标。

## 交付核对

[提交看板](../../DASHBOARD.md)已对齐29888，七份历史正式提交当前均0%，累计官方记录11.833628944α；历史初始份额逐条保留。扣注册成本的当前估值约3.745177α，仅扣已登记注册成本、按finalized区块9266509池储备换算，不是本轮新增收入或钱包到账，模型／CI成本未计。[看板核对](../../evidence/round26/extension4h/dashboard-consistency.json)。

严格Git字节核查识别四份候选manifest的CRLF差异；已保留原本地字节并将当前路径对齐现有Git的LF字节，Rust／Lean和所有原始CI响应未改。旧manifest SHA仍可按[精确映射](../../evidence/round26/extension4h/metadata-byte-reconciliation/receipt.json)找到原件，未放宽字节检查。[收尾原字节审计](../../evidence/round26/extension4h/audit-close.json)覆盖1643文件、175508317字节。

[最终机器汇总](../../evidence/round26/extension4h/close-summary.json)与[严格Git字节审计](../../evidence/round26/extension4h/git-byte-audit-close.json)绑定1647份文件、175547528字节至提交9b9c222d；后续提交只收录汇总及核查回执。账户最后读取北京时间18:35:17，主窗口已用65%／剩35%，启动时已用48%；差额17个百分点属于共享账户，模型精确费用UNKNOWN。没有兑换重置卡或购买额度。

截止前榜单从29885连续更新至29888；最终29888完整捕获含同快照weights，全部原协议块已重算且独立误差小于1e-15pp，数值不变。659行指标与当前前沿的重放保留在最终资料；旧29885历史备选与取样图仍按原时间标记，前沿及政策逐项相同已核对。看板最终换算以其最新原始summary为准，前文3.745177α及区块9266509保留为18:25阶段值。
