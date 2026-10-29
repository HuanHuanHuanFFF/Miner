# R24研究当前入口

共同UTC2026-10-28 20:38:56—2026-10-29 03:38:56（北京04:38:56—11:38:56）不变。R首工具20:40:53，晚加入1m57；实际模型CPU/token/cache均UNKNOWN。D唯一Git/CI/采用，作业看上一层development-jobs.json。更新03:27。

- **已验收数学**：`core-certificate1/049b01fa/45684B`，40793795026 statement、module kernelReplay、13项allowed-axiom审计通过。准确为**9新增helper+4原公开义务**；R已独立重hash读原audit，见core13-independent-receipt.json。只绑定该精确core，父完整Kernel不继承PASS。
- **主组合未接受**：Math9/40810384656、island9/fdbe17b2仍有两处Widen.shift29转换失败。Widen6/2eb9c43b已消除Int外层，真实残留只是Nat数字536870912到Real的cast；Widen7/336b8bbc/12412B定点草稿已交，NOT_RUN，**本轮不再math CI**。35roots=31新helper+4原义务未接受；Mul-v4、SUM3、Power-v4源不变，失败原件保留。
- **已核成本**：40804860824收齐64进程。R独立重算64份原log的9408条ns/sink/iteration及32个配对、所有逐项慢例，与D统计一致。Tail full/lazy的49样本中位耗时之和相对自建UInt64/128参照降低**27.5%–32.9%**。每次准备、失败回退及释放计入full，prepared首次准备另列；固定MAC合成混合、同runner探索，非完整模型/官方成绩/冻结新runner确认。完整成本体正确性仍UNPROVED。见complete-cost-independent-review.json；共享行列缓存bank/40811305126已成功，16进程/144ns/464输出×3backend数值核对；eager全调用相对同类自建整数参照降低71.1%–72.8%，lazy62.4%–63.4%。R已从16原log独立重建，见bank-cost-independent-review.json。仍为三种合成shape、同runner探索，不是官方BMM或整模型成绩。
- **下一证明接口**：NormalCell、DyadicAgreement/DyadicCell、MidpointWords/Real、NativeSignOr/RawMidpoint、RadiusEndpoints、SubnormalWiden均有精确源码与范围，除core外新终端桥NOT_RUN。真实checker用`orderKey`而非Float.lt，需有限且边界非零的严格序运输，防止±0例外；还缺实际prepare/getter/Tail fold/rounder/fallback组合。首次关键复核与路线见CERTIFICATE-INTEGRATION-FRONTIER.md、对应independent-review回执。
- **独立高上限替代**：two-chain128/b2f408、encoder/01bdf、split/d54fb、indexed/25ed、residue/76db、HighCompat/1f5608bb有源码，NOT_RUN/NOT_QUEUED。原QY6G已为标准补码c0；缺原getter/旧loopRep/终端完整运输、实际codegen和成本。wordwrap反例保留，不再把原有两链说成新发现。
- **资料及发布**：六份Pro原始Markdown共105617B，八份MIT固定主源共101970B，均E下载后逐字节整理到本分支，materials-integrity.json零差异，无zip。Pro私有原件/回执只留E与本地；公开技术提取见PRO-REVIEW-DIGEST.md、public-pro-receipts.json。D使用public-research-allowlist.txt并在提交前重建manifest，不能盲目暂存整个research。UNKNOWN许可former2只读，不整份发布/复制。

主攻证书与实际Tail/checker闭合；新bank成本已支持下一轮将投入目标改为探索20/实现证明60/复核15/协调5（计划，实耗UNKNOWN），见NEXT-ROUND-DECISION.md。保守aligned64新判别在12个已见长narrow样本全部guard拒绝，停止抢主线；更宽exact128仍UNKNOWN。03:15停止新长实验，03:38:56停止新增并收齐已启动。旧3.5h恢复误判记录保留，不能改本窗。FloatLib新提交已关闭；TorchLean目标仍待D原问题的用户答复，当前无新12kernel/正式参赛/资金或本机Lean。
