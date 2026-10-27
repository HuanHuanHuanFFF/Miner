# Dual A4+B8：d765仍失败；c598只买目标诊断

新增真实结果：run **40420540388** 精确 d765 在 `loop_eq` 五处 `rw [loop]` 失败；原 full-build-output **没有目标/上下文**。`group_eq` 此次不再报错。statement 未过，18 根、Submission/VerifyFull 重放、C/ASM 和成本均未进入。原文件按原 artifact 索引逐项校验并存 `../ci-40420540388/`，不把批次 failure 当作其他路线结论。

单一诊断源 `proof3-diagnostic/Kernel-dual-temporal-a4-proof3-diagnostic.lean`，**240744 B**，SHA **c5981413680244f3d93d79a372a09b36dcbe22028a942b8a35fd2cd18d5f0cf7**。仅首完整块分支 trace 真实目标/新旧 eq_def，显式实例化新展开等式并试首步；其余四分支原样保留，**预期仍四红，不是待计时候选**。runtime、域、所有陈述、其余证明不变；原 d765 与9a5不覆盖。逆 patch 精确恢复 d765；文本 intake/policy/options 通过，Lean **NOT_RUN**。

Pinned Lean 源码证实 bare `rw [loop]` 隐去逐条 equation 匹配错误，解释当前缺失上下文；未确认 blocks alias 根因。下一决定只依据这次首分支实际目标与显式等式结果，随后才作最小全分支修复。详 `proof3-diagnostic/DIAGNOSTIC.md`、`diagnostic-receipt.json`、`proof-only.patch`、`compiler-originals/verified-provenance.json`。

不并生 runtime 版本。A 全局准备/释放/填充成本可能抵消循环收益；既有 `callpath-prediction-2301.md` 与 row-interleaving 条件提案保留，须等真正 **R19DualTemporal_loop** 的 C/ASM 与全成本，旧 c70 loop 不代替。D 唯一 Git/CI，本方无本地 Lean/CI/Git；R 最新窗口截止 **2026-10-27 02:28:21 UTC**，D 原窗口不改。
