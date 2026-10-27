# 公共出口review1：静态接线闭合，仍待Lean前缀反馈

2026-10-27 00:15Z。当前审查对象优先为`exact-arithmetic/bias-frontier/public-proof-review1/Kernel-direct-bias-public-v1.lean`，255311B，SHA **fa6529613fe10bd431ead1511900be989c2b80976423b31d90747f8651f37ac5**；数学接口32332B，SHA **2177e7b7e3c74f8fc7e7511cbe9d43fb34ea9d86eec97f0ab82053db49289266**。父版79e8/255269B和fae383/32290B保持原件。**只读静态审核完成；statement/replay/axioms/fullgate/performance全部NOT_RUN，HOLD等待原ImportOnly/QuotientOnly结果。**

| 核查 | 独立结果 |
|---|---|
| R14依赖缺口 | 新`PublicOutlet`本地提供`product_bounds/exp_bound/finiteScale_sum/normal_guard/sum_guard`，新增7片段没有`R14ExponentShift`引用；旧表所列缺失接口已在源中补齐，不等于证明已通过。 |
| 完整桥及48根 | 两套清单均48个唯一根且静态声明存在；=44个新具名theorem+4public规格，覆盖typed high/q/exponent、mask/字段、normalCore→roundP/core及guardedMul_spec。公共包四根是新wrapper规格；MathOutlet四根来自导入B2。 |
| runtime/root范围 | 冻结1359B片段在两包分别逐字出现，公共包只作命名空间替换；与已核7489的1358B后缀仅尾换行差异。48清单没有单列3个运行定义；normalCore/guardedMul在新等式/spec中被引用，diagnosticEntry是保留的未选诊断入口；最终仍须整模块重放。没有必要把48误写成48新证明或声称本批已验新机器码。 |
| B2与删叶 | 独立从unpruned260083B重放9个普通theorem叶删除，合计4814B，精确得到79e8；diff也逐字复原。**136个旧B2非证明声明**逆命名后全同。155是完整包总数：136旧+15新辅助定义+4public包装，删前删后155相同。不能写“155个旧B2声明”。 |
| 命名/接线 | 实际用`R19BiasBase`，不是组装前预算中的示例`R19Base`。seed/PostBias/R2W01c保持顶层；全部新Word/Shape/DirectBias和旧FastMul/UnderflowZero引用一致。公开MUL确实接guardedDirectBias和原`R19BiasBase.mul`fallback；此项也已由根独立核读。 |
| review1唯一delta | `exponentWord_nat`第一处`Nat.mod_eq_of_lt`显式限定`highWord.toNat < 2^32`，恰+42B；两份源逆替换逐字恢复父版，非证明声明/冻结runtime/guard/两套48根全同。它是预防性rw目标限定，不是已复现Lean错误或已验修复。 |

**字节风险已具体化：** review1余 **689B**，不是早期未加桥的8–10KiB余量；再加1KiB会到256335B，超335B。当前文件7268个LF、零CR；若Windows保存为CRLF则262579B，超6579B。保持LF并对最终确切字节重哈希；不得为方便把其他probe/support整段附加。需超过689B的真实修复时，必须另存精确版本、重新给证明叶省略回执并核runtime，不能沿用79e8/fa6529验收。此处未提出或执行新的删叶/运行变体。

审计脚本`audit_public79e8.py`只读actor文件，未调用其builder。`public79e8-and-review1-audit.json` SHA **80b3205eeaeeb9f4fc581e13b75b5a371e3dd821a33179558f3f26ff2da5b412**绑定完整源、7片段、2套根、9个删除片段和42B修订。具名静态存在不保证Lean解析、名称解析、tactic闭合或资源通过。根已另核UInt32.toNat_lt固定4.34声明，本方未重复该查证。

只写本方review目录；无actor源修改、无新Kernel/wrapper、无本机Lean/Git/index/CI。下一动作由两prefix原件决定；若源变更或GRS真实反馈到达，再以新SHA续审。
