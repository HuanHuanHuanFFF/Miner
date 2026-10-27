# proof5：CI12三个末端记录目标

新源 `Kernel-dual-temporal-a4-proof5.lean` **241509 B**，SHA **c36bc2502904bf946d442de1a4646e09689f016643f09ab0b6788f9bdd375250**。与原b92d相比，只在尾3/尾2/尾1的最后一条packetA `simp only` 后各加 `<;> rfl`，共24 B。完整块递归、零尾、所有运行体/域/陈述/其余证明保持原字节；18根不变。

依据run40430974047/f4211856的精确b92d：旧loop equation错误全消失，只剩6765:8、6774:8、6783:6的unsolved goals。三个完整目标都是F2的两字段等式；逐项打印read地址、B.get字段和原序乘加完全相同，差异未显露在打印文本中。B.get里的Fin边界证明被省略，且旧blocks别名可能留在隐式类型；因此用kernel定义相等/证明无关性收尾，不改变表达式顺序、不添加浮点恒等式或假设。

该判断来自完整目标，仍需真实编译：相同打印不自行等于kernel证明通过。`<;>`保证前面的simp若已闭合则不额外执行rfl。旧group_eq同类收尾已有真实消错记录，但不借其结果替代新三目标验证。

五份自有原件按原artifact索引逐项核验后保存 `../ci-40430974047/`；`tail-goals.json`保留三个目标及打印比较。`repair_proof5.py`核三处唯一修改、proof-body之外逐字相同、256000 B、固定文本intake/policy/options，并独立逆patch精确恢复b92d。具体哈希与18根见 `repair-receipt.json` / `HelperAudit.lean.inc`。

**新源Lean、Submission/VerifyFull重放、18根审计、C、原完整gate与计时均NOT_RUN**。下一步D复编精确c36；通过后才能核真正R19DualTemporal选中路径及全部准备/释放成本。Jam b372交peer后冻结，c9不扩，未创建新的Dual运行版本。
