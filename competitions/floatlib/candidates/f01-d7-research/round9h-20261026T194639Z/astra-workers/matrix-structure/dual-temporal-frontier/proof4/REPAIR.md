# proof4：传播CI11已成功的显式方程模式

新源 `Kernel-dual-temporal-a4-proof4.lean` **241485 B**，SHA **b92dac573897e6dc5c72eef9d5eebac778eeefde1f9ca262657dfacaa368c4ca**。只改 `Submission.R19DualTemporal.loop_eq` 证明体，所有运行定义、域、陈述、其余证明与d765/c598逐字相同。固定原文本intake/policy/options通过；**新源Lean / 内核重放 / 18根审计 / C / 完整gate / 性能均NOT_RUN**。

真实依据为run40428306094/a92abea/1927011，精确c598。该源仍statement失败，但仅四个未改尾分支6769/6774/6779/6784报bare `rw [loop]`错误。verdict SHA `2498133080de44fe88c57c341ad514b2bb5a7da34b80c60909dfa9e781fa44e4`；完整build-output SHA `989ce574c1f933281937109414fa76fc360183b4eaab99d4e89efaa298ec6f1d`。五份自有原件逐项绑定原索引并复制至 `../ci-40428306094/`；原3段完整trace另有 `trace-targets.txt` 便于阅读。

真实目标说明：B/hA/hread类型已规范为(n+3)/4，目标仍以原新loop调用为左项，排除了“unfold blocks已经把整个目标头提前展开”。两条fully-qualified eq_def成功实例化，左端与目标调用一致；第三trace明确显示新loop已经展开为A4字段与B8字段的四步原序链。首分支的后续RHS展开、字段read对应、递归步没有报错，其他四个原分支仍在bare equation rewrite处失败。模块未接受，所以这些观测不等于全定理或kernel replay通过。

能锁定的故障层是**隐式equation选择/实例化失败，显式实例化eq_def可用**；不是方程缺失或新loop数学等价被反驳。blocks别名/默认透明性是与现有类型形状一致的解释，但未另外隔离内部匹配细因，保留此边界。Pinned Lean的bare rewrite吞内部匹配错误行为，仍见 `../proof3-diagnostic/compiler-originals/`。

修复严格照成功首模式复制：每分支都先显式实例化新、旧eq_def，再 `rw [dual_p3_new_eq]` 和原 `conv_rhs => unfold R19Temporal.loop`。首分支只删除3次trace和诊断注释；四尾的其余simp/packetA/read/终止表达式逐字保留。旧eq局部绑定虽然没有直接用于rw，也暂不删除，以免同次修复又优化未经独立验证的形式。没有新全局bridge、假设、运行版本或根名单变化。

`repair_proof4.py` 检查仅proof-body差分、剥方程步骤后其他证明字节相同、三版本掩码一致、256000B上限及固定原文本规则；独立逆补丁精确恢复原CI11输入c598。详 `repair-receipt.json`、`proof-only.patch`。D仍唯一Git/CI；下一步是新b92真实声明/完整重放/18根审计，之后才能读真正R19DualTemporal active C/ASM并决定全成本，不能用c70旧loop代替。
