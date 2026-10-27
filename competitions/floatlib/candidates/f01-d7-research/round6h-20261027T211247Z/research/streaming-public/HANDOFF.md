# R22 A：完整公共 streaming BMM 与固定 guard

实际起时 **2026-10-27 21:17:47 UTC**，共同截止 **2026-10-28 03:12:47 UTC**。仅写本目录；D 唯一 Git / CI / push。应用 huan-open-research 与 prompt-entropy；持续研究，不因本交接停止。

- **当前交 D 源**：[v2-guarded/Kernel.lean](v2-guarded/Kernel.lean)，SHA **ebfb6408b3ee5639ff1d800fa1385f87b40a891bb649311449caa9418b9a26ef**，**254601 B / 38 根 / 1399 B 余量**。逐字引入 D 先定的 `BmmCost.lean.inc`（8790cda2），唯一运行源替换是旧 B2 fallback 名称改为 `bmmBeforeR22Streaming`；保留 `1<n ∧ 2≤m ∧ 2≤p` eligibility、`emit ((m%2)*p)` 奇尾及其原基址。追加 proof-only 的 rows / output / core 运输和 guarded_spec，再绑定公开 bmm。**全部新组合 NOT_RUN，不继承 19 根 PASS 或 cost 性能。**
- 可单独取 [CostCallerProof.lean.inc](CostCallerProof.lean.inc) 和 [GuardedPublicEntry.lean.inc](GuardedPublicEntry.lean.inc)。依赖 c3c3 的 matrix 前缀证明；若直接在原 4e36 包中使用，先补 c3c3 writer。首稿 [v1/Kernel.lean](v1/Kernel.lean) 的 **059f0401 / 252031 B / 36 根**已冻结保留，不改它。
- 组合原本 **256254 B 超限**，原字节保留 `v2-guarded/pretrim-Kernel.lean`（76b685f1）。仅删 4 个无引用 theorem（emit_finish_eq、emit_two_rows_eq、adjacent_A_base、odd_tail_valid），共 1653 B；运行体不动，删除项/hash 在 manifest。新 MUL 如超过 1399 B 仍需做有依据的依赖裁剪；目前没有大规模整理。
- [schedule-check.json](schedule-check.json)：batch 0..4、m 0..9、n 0..7、p 0..9 共 4000 个形状，按每输出的原始 A/B 地址及 k 顺序逐项相等；旧 batch=2,m=3,n=2,p=3 反例现在通过；故意跨批的变异在输出 9/10/11 被拦截。它不证明 Float32 / Lean 正确性。
- **成本仍 UNKNOWN**：固定 Array.mapIdx 实现已复核，安全入口落到原库清槽/写回后端；首次 replicate 共享 Cell、稳态复用、closure / RC / COW / 输出释放等待 D 的真实双行 caller 数据。未见确认组，也不据结构推算速度。

下一决定：若真实调用成本支持，D 编译 ebfb 精确稿，首错回传我处理；若表示已被成本否定，保留完整 bridge 并转向不依赖这份表示的布局，不调阈值追分。
