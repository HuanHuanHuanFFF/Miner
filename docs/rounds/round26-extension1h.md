# 第26轮追加一小时：先建立可靠的小份额

本次固定北京时间为 **2026-10-12 19:50:15–20:50:15**。用户同意先争取跨runner可靠的小份额，再追5%/10%。**本轮没有建立稳定正份额，也没有可推荐正式提交的完整包。** 执行规则见[AGENTS.md](../../AGENTS.md)，原八小时及追加4h记录不改写。

三个不同Rust候选完成最小实验，只有C4进入原协议计时；5次CI已全部收齐，4成功、1完整gate失败。没有冻结后独立确认、正式上传、注册、签名、支出或重置卡兑换。[固定预算](../../evidence/round26/extension1h/budget.json) · [逐圈状态](../../evidence/round26/extension1h/state.md) · [机器汇总](../../evidence/round26/extension1h/close-summary.json)。

## 三圈反馈

| 候选 | 实质变化与实测反馈 | 时间／份额状态 | 完整gate |
|---|---|---|---|
| C2 fold-tail | 合并旧match前加末字节必要检查。444有限检查及28公共输出通过；能拒绝40.15%调用，但每次仅省1.014个原word比较，新增检查覆盖全部256144次调用。按预声明停止。 | 未计时，份额UNKNOWN；没有证明它更慢 | NOT_RUN |
| C3 deferred-extension | 保留lazy选择，把长于64的完整扩展留给可信发射。444有限decode及28输出通过；75920调用仅684个长匹配，省5784/99989次发现word比较，覆盖薄，停止晋升。 | 未计时，份额UNKNOWN | NOT_RUN；另存未编译草稿 |
| C4 greedy-once | 删除整个lazy选择，首字提示后由可信matcher一次扩展发射。444有限decode通过；docs多7280B、prose多19619B，公共共多26899B。一次原协议主候选慢0.180460%，副本慢0.038953%。 | 主份额0%，未建立稳定性 | proof1在stage4 statement失败 |

C1同距离fold复用仅做可达性检查，不生成第四算法；计数为0。新公开#662已保存作者及原始source响应，限定静态比较未发现值得替代本窗主线的新结构，未计时。[C2决定](../../evidence/round26/extension1h/c2-decision.json)、[C3决定](../../evidence/round26/extension1h/c3-decision.json)、[C4固定方案](../../evidence/round26/extension1h/route-c/c4-predeclaration.md)。

## 当前快照下的份额与测量边界

最后完整查询保存的是 **29924**，官方计算UTC12:36:40.176764；最后查询时间见[原始响应回执](../../evidence/round26/extension1h/official-final/receipt.json)。667条记录、624账户，API freshness仍为unknown；同一快照weights匹配。评分源码commit `6bf303f14e6c7bccc63e9a557e4ac83e032fa9e8`；原始SHA及独立公式核验见[最终评分审计](../../evidence/round26/extension1h/score-audit-final.json)。

以下均是**条件公共投影**，不代表正式admission或可支付成绩：

| 计时身份 | 校准参照 | 时间轴 X（倍） | 大小轴 Y | 竞赛池份额 |
|---|---|---:|---:|---:|
| C4主候选 | 主658 | 0.472423942 | 35.682892319% | 0% |
| C4主候选 | 同源码影子658 | 0.471579035 | 35.682892319% | 0% |
| 同源码C4副本 | 主658 | 0.471756632 | 35.682892319% | 0% |
| 同源码C4副本 | 同源码影子658 | 0.470912919 | 35.682892319% | 0.026455393% |

X为配对incumbent的总压缩时间比，Y为每文件压缩后／原始字节比例的等权均值，两轴越低越好。上表为本轮结束时快照29924的历史条件投影，份额与该行校准坐标对应，不代表实时榜单或正式成绩。其对应的公共原始实测另列如下；未直接用公共坐标重放的份额保持UNKNOWN：

| 计时身份 | 公共实测 X（倍） | 公共实测 Y | 竞赛池份额 |
|---|---:|---:|---|
| C2（仅原编码器大小测量） | UNKNOWN | 35.308210978% | UNKNOWN |
| C3（仅原编码器大小测量） | UNKNOWN | 35.308210978% | UNKNOWN |
| C4主候选 | 0.467251204 | 35.387422883% | UNKNOWN |
| 同源码C4副本 | 0.466591201 | 35.387422883% | UNKNOWN |

主候选只有1个runner、1个发现块：最佳／中位／最低全0%，零1/1、正份额0/1；没有独立确认样本。副本与两种校准不是新候选或独立样本，不能相加成组合份额。C2/C3未计时，联合份额UNKNOWN。[逐文件原始时间与每种投影](../../evidence/round26/extension1h/c4-final-analysis.json)。

父版同二进制差0.179165%，候选副本差−0.141252%，足以改变很小的前沿判断。按同一总时间中位rep分解，主/主下两个改token文件贡献−0.114691个百分点，其余26个同token文件贡献+0.295152，合计+0.180460%。这证明本块分歧的位置，不证明所有差异都是噪声、布局效应，也不能去掉其他文件制造修正成绩。算法整体净收益仍未定。[原始分解](../../evidence/round26/extension1h/c4-cost-feedback.json)、[独立核验](../../evidence/round26/extension1h/audit/c4-final-timing-review.md)。

## 精确文件与验收缺口

[全部文件对及完整SHA256](../../evidence/round26/extension1h/candidate-pairs.json)保留3份不同Rust、4份文件对；C4 proof1只是同Rust的证明配对，不算第四候选。

C4已测精确包：[源码及失败证明](../../candidates/r26-c-658-greedy-once-proof1/manifest.json)。Rust `ae4602290cc2a0253703ab6e6ac0d2fe098e84429cc4d56314ac9326abbf0f88`；Lean `11426ab441c65b37949eff9de9840310d9192fd797870433d90d5e06463fb105`。

原版gate已重新提取Rust，但在Lean声明阶段拒绝：新增helper的`step*`停在cap的if/bind，后续回退证明无法匹配整个尚未展开的程序。原obligation、公理白名单最终输出和公共roundtrip接受均未完成。[原始失败回执](../../evidence/round26/38248430871/gate-c4-proof1/exact-gate/exact-gate/gate-receipt.json)。针对实际错误只准备了[proof2草稿](../../evidence/round26/extension1h/audit/C4-Parse-proof2-UNCOMPILED.lean)，SHA `1182e84949bf7e1003af878ff9253ea39d9238147c9e138c374610f104cf53c1`，508337B；**UNCOMPILED**，不能说修复成功。原proof1及失败日志保留。

## 资源、看板与后续

五作业runner墙钟合计 **1772秒（29.53分钟）**；准备、排队、实现、收集、分析和交付均计入本小时。[逐作业消耗](../../evidence/round26/extension1h/resource-summary.json)。账户已用从66%到70%，剩30%；这是共享账户读数，不能算成本轮专用token或费用。没有重置、购买；模型费用及GitHub账单UNKNOWN。

[提交看板](../../DASHBOARD.md)已按同一29924快照刷新：7笔历史提交当前均0%，累计历史官方奖励11.833628944α。注册费用折算净额与查询区块见看板原始回执；这不是本轮新增收益或钱包到账。

下一份有价值投入应先区分真实小幅收益与同源码0.14%–0.18%分歧：检验已定位的实际CPU/controller约束或进程顺序干预，诊断协议与原协议分列。C4的局部速度观察值得保留，但压缩损失与整体零份额不容忽略；proof2即使以后通过，也不能替代新的稳定性确认。保持质量且复用可信匹配结果可能值得探索，但需重新核查覆盖及跨选择/发射的证明代价，不能继续扫阈值。

VERIFIED：原始质量、发现计时、公式复算、同源码分歧及gate失败。INFERRED：同族公共投影、机会与未来改进方向。UNKNOWN：私有集迁移、稳定正份额、正式可支付性、新proof2通过情况及完整费用。

交付核验：精确Git字节审计核对1,927个文件、209,778,454 bytes，覆盖全R26的65个已结束CI；本窗5个另见资源表。项目检查通过33任务、900本地链接、381候选文件对。均不替代失败的Lean gate。[字节审计](../../evidence/round26/extension1h/final-byte-audit.json) · [项目检查](../../evidence/round26/extension1h/project-check-final.json)。
