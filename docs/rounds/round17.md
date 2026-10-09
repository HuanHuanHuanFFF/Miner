# 第十七轮：DNA高份额候选复测与完整证明

用户明确要求对`r14-514-dna-nofold`再测两次，并完成Lean验证；份额表现是本次优先指标，不用“比父版稍慢”否决完整验证。执行规则见[AGENTS](../../AGENTS.md)。这是第十六轮结束后的独立授权，不延用已关闭的两小时时窗，也不包含正式竞赛上传或钱包签名。

Rust保持`805c03a521b44b665aef3113cb4d6f823924032fec164524163aa0c756002542`。初始Lean为`f22880631041cea2d1f380aeb898fadfe36ca3f3a9912938abf0801d3acd11bf`。

- A：新runner四个镜像计时块，随后无条件运行原始完整gate，作业上限60分钟。
- B：另一新runner四个镜像计时块，上限40分钟。两次均保留原514、同源码shadow、原abs15和DNA-direct对照。
- 旧结果只有一台runner两块；新八块单独展示，再与旧两块合计。以实际份额范围、中心和波动描述，不以压力情景代替测量，也不把峰值当稳定收益。
- 若初始证明失败，原失败和精确文件保留；只修Lean，不改Rust。修复使用不增加配对性能测量的独立原版gate流程。

[执行计划](../../evidence/round17/plan.json)、[A配置](../../evidence/round17/retest-a.json)、[B配置](../../evidence/round17/retest-b.json)。当前快照29370仍给旧两块的中心约22.33%，只是同族条件投影，实际稳定性、完整证明和正式奖励分别核实。

## 最终结果（2026-10-09 23:55 北京时间）

VERIFIED：两次新增性能运行已收齐，共64个配对进程、目标8个计时块；连同旧运行共82进程、目标10块。原始证明失败已完整保留。只修Lean后，`r17-dna-nofold-proof1`通过原始完整公共gate，运行37953420535，重新提取、原始obligation、公理白名单和stage1 roundtrip均通过；公开输出5,340,851字节。Rust与原候选逐字一致，原Lean不应被标记为通过。

[精确证明证书](../../candidates/r17-dna-nofold-proof1/VERIFICATION.json)、[原失败诊断](../../evidence/round17/proof-diagnosis.json)、[完整通过回执](../../evidence/round17/37953420535/gate-proof1/exact-gate/gate-receipt.json)。

INFERRED：按官方快照29382（计算时间15:42:46 UTC，API freshness unknown）重算。下面都是公共数据的条件份额投影，不是实际奖励。使用实际跨运行波动，无人为压力修正。

| 口径 | 新8块 | 全部10块 |
|---|---:|---:|
| 原514校准最高 | 17.720% | 23.120% |
| 原514校准中位数 | 0.0264% | 0.0452% |
| 原514校准最低 | 0% | 0% |
| 原514校准至少1% | 1/8 | 3/10 |
| 同源码shadow最高 | 0.0922% | 19.826% |
| 同源码shadow至少1% | 0/8 | 1/10 |

等权运行平均坐标再评分仍为23.030%，但不能将其当作稳定份额或期望收益：评分非线性、平均坐标落在狭窄高分区，而多数实测块落在区外。新增8块的份额算术平均2.246%也不能替代正式收益预测。高峰值得关注，但稳定20%未复现。

[最终逐块份额](../../evidence/round17/block-shares-final.json)、[原始测量审计及复算](../../evidence/round17/final-performance-analysis.json)、[官方快照](../../evidence/round17/official-final/receipt.json)。

UNKNOWN：正式admission、私有集排名和新奖励。本轮未正式上传、未签名。若试投，应使用上面的修补证明组合，不能使用旧Lean文件。既有#573是另一候选，不能混用其正式结果。
