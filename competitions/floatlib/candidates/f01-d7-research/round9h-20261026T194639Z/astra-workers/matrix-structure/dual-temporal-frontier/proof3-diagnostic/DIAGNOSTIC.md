# c598：首分支目标诊断，非修复候选

来源为 run **40420540388** 的精确 **d765bd41234a26640eaa6df6c7134e0d4d8dca760e50eaef3aa82eff1fac0847**。statement 在 6751:8、6761:14、6766:14、6771:12、6776:10 五处 `rw [loop]` 失败。完整日志没有打印这些失败的目标或上下文；不能凭这五条短错误确定根因。group_eq 本次不再报错，但整个模块未验过，18 根公理审计、Submission/VerifyFull 重放与 C/ASM 均未执行。原件及原索引保存在 `../ci-40420540388/`，每项已核原索引哈希、字节数。

当前单一探针：`Kernel-dual-temporal-a4-proof3-diagnostic.lean`，**240744 B**，SHA **c5981413680244f3d93d79a372a09b36dcbe22028a942b8a35fd2cd18d5f0cf7**。仅完整块首分支改动：输出原目标，显式实例化 fully-qualified 新、旧 `loop.eq_def`，输出这两个等式，再只用显式新等式替换首个 `rw [loop]` 并输出残余目标。原 RHS unfold 和后续证明保留；其余四分支逐字保留，预期仍出现四处原失败。**这是用于买判别证据的诊断源，不应排全成本或宣称修好。**

所有运行定义、域、定理陈述、其余证明与 d765 逐字相同；逆 `proof-only.patch` 精确恢复 d765。新增局部等式来自原函数的生成展开定理，没有新增公理或改变原义务。仍列原 18 个 helper 根；其中未有通过审计的说法。固定原 gate 的纯文本 intake/policy/options 通过；**Lean NOT_RUN**。不在本机编译，D 独占远端验证，是明确分工对本地快速诊断的约束。

根因证据边界：pinned Lean **293d5d0c0c3f3dded4688b3ccd6a33939ac5102b** 的 `Rewrite.lean` 对 bare identifier 枚举 equation 定理；每次失败被备选分支吞掉，最终抛统一错误。显式应用的 equality term 绕开这条搜索。`Meta-Eqns.lean` 指定展开定理后缀 `eq_def`；`Unfold.lean` 对展开等式使用 reducible matching。这些只解释为何原日志没有 goal，**不证明 blocks alias 就是根因**。四份 upstream 文件保留 URL、Git blob SHA-1、逐字校验与 SHA-256，见 `compiler-originals/verified-provenance.json`；版本与当前 run 的 build-trace 记录一致。

下一次只按实际输出决定：

- 若首个 trace 的目标已不含新 loop，检查 `unfold blocks at *` 改写结果，不继续增加 rw 变体。
- 若 eq_def 实例化失败，原报错应给出真实参数/类型差异；优先按该差异修桥，不改变运行定义。
- 若实例化成功而显式 rw 失败，保留目标与等式全文，解决确切 dependent pattern 差异。
- 若显式 rw 成功，第三个 trace 显示展开后的真实 RHS，再判断旧 loop unfolding 及 ordered chain 对应。只有这一真实证据支持后，才在新修复副本将同样方式迁到其他分支。

本件不替换原9a5/d765，不重开 runtime、域或宽度网格；不会因为少 ofBits 或没有报 group 错误就推断实际速度或完整正确性。
