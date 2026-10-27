# R16 source-budget：容量有解，等待精确源验证

2026-10-25 09:54:36–10:03 UTC；只做容量调查，已停止扩展。分支 `huan/codex-gpt`，D 仍独占 Git/index/push/CI。tokens/cache UNKNOWN，CI 0；未改 queued sources，未造合并 Kernel，未读本轮确认输入/结果。

**VERIFIED（字节／静态引用）**：B2 `622d8394…` 226829B、A4B2 `5f53a930…` 245867B、repack `c972fd72…` 247533B 全哈希吻合。共同两轮 plain-theorem 片段裁剪可回收 **11990B**：第一轮23个／6981B，第二轮13个／5009B。36片在三源中 SHA 完全相同；第二轮按仅删共同第一轮后的源码重新计数。独立回放核对片段、阶段哈希、字节数及删后无叶名或生成子名的前缀引用，三份原件仍原字节。

**最低风险的足量方案**：仅这36个无显式引用、无 attribute、无注释的普通 theorem 片段；保留全部 def/instance/notation、八个公开函数／规格名、来源许可和剩余代码缩进。无需使用旧 df5c 专用脚本，无需注释或空白压缩。纯注释＋空行本身只约2615/3107/3182B，不足10571B；不得将其与定理含有的空行重复相加。

**INFERRED（容量足够）**：线性组合估计266571 −11990 = **254581B**，距256000上限尚余 **1419B**。实际合并字节数 UNKNOWN；完整合并如多出超过1419B修复代码，须重新核算。

**边界／下一动作**：静态无引用不是 Lean elaboration 证明。本调查未运行 Lean/full gate，不能声明编译、等价、依赖公理或性能已通过。D 决定整合后，将 `budget.json` 的 `common_plan.rounds` 按逐片 SHA 回放到新候选，重新扫描引用并冻结精确文件；由 D 执行原完整 gate／四规格／公理审计及所需新确认，不能继承旧回执。完整标识、坐标、可重放脚本和独立回执见同目录 `budget.json`、`audit_budget.py`、`verify_replay.py`、`replay-verification.json`。调查问题已足量回答，不再挖后续裁剪。
