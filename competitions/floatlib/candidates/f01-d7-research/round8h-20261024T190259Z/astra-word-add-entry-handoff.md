# R14：实际 public ADD a234 已独立重建

时间：2026-10-25T00:58:13Z。`f01-r14-dev-word-add-entry1/Kernel.lean`，SHA **a2342948257d2e2e2011f0fe941bd2b692e70604b915734f4538b5efd1e69372**，255409B、余591B。

`astra-word-add-entry-audit.py/.json` 在不执行开发builder、不改源的情况下重建整份字节，核对11片段、旧fallback改名、新public add位置、后续公共add_eq和尾部原字节。Root d507的raw_add_model目标陈述保持逐字相同；只去864B重复helper并改用fields2里等价的sorted_domain/gap_pair。fields2仅去无需重复提供的derived order合取并调整投影；原始order仍在raw桥中单独推出。spec2直接使用rawModel_eq_native32，符合之前建议；未把spec1写成已确认编译失败。旧原件都保留。

新实际入口是 `R14WordAdd.guardedAdd addBeforeWord x y`；回退仍原x/y。它继承thin-cache/p8 BMM新机制，MUL/SUM字节由slim父源保留；不能把组合whole归因于单独add，亦不能继承旧BMM通过。实际优化caller、higher-order fallback消除、分支/UInt64 boxing成本仍待真实C/汇编和完整配对计时。

**本回执只确认字节与源码衔接。** 精确a234的Lean elaboration/axiom replay/官方full gate/性能全部NOT_RUN。当前没有额外数学洞或新源码请求；我转入最终接口/证据检查，若收到真实编译错误再按精确源修复。公开范围仍待你已向人类提出的问题回复，没有代理push/CI。
