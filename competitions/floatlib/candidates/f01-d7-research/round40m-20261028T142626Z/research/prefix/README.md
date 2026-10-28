# R23 indexed8 输出前缀

窗口沿用 UTC 2026-10-28 14:26:26—15:06:26；本角色精确首工具时间 UNKNOWN，最早可核首探针完成时间 14:37:32。D 唯一 Git/CI；本目录及 `f01-r23-research-indexed-prefix/` 为本方写入范围。无本机 Lean，无正式上传。下列条目保留 14:48 交付时状态；当前验收见末尾更新。

- 首份可跑探针：`f01-r23-research-indexed-prefix/Kernel.lean`，254926 字节，SHA-256 `0d760ec9e77e8f4814c66dfc870f9c05066b4fdf942d78961ce3f897adff6fab`。基于精确 cost1/8e27，仅删除空行后追加 `IndexedPrefix.lean`；全部原非空行和运行时定义保持原字节。三根是 `R23IndexedPrefix.rows4_prefix`、`tail_read`、`output_eq_reference`。当前 **NOT_RUN**，后三层等价仍以具体四 reader 的读数等式为假设。
- 组合接口：`NatPrefix.lean` 是相同外环证明的实际 `R22Resident8` 版本，直接覆盖原 Nat 回退；`NatReaderBridge.lean.inc` 把四个 dot 读数接至 batch/point，并经主控 `output_eq_nat` 得到 fast/fallback 同时成立的条件 `core_eq_reference`、`guarded_spec`。
- `PackedReaders.lean.inc` 使用协作方实际 `tile_word`，以 `g=j/2,c=j%2` 连接具体 tiles/read0..3，构造 `all_reads`，得到无新假设的 `indexed_guarded_spec` 草稿。所有新组合 **NOT_RUN**；公开 `Submission.bmm` 尚未替换，不能继承正式资格或性能结论。
- 可复核静态检查：`static-check.json` 证实 cost1 前缀非空行保持、长度及 helper v8 哈希；`index-screen.json` 对 m/p=0..18、b=0..4 的 149454 个索引检查通过，仅属有限算术筛查，不能替代 Lean。协作方已对 PackedReaders 的实际 tile/字段/地址接口作一次关键静态复核，未发现缺前提。

集成顺序：原 cost1 运行时与 accepted indexed-loop/nat8projection → 实际 packB producer 与 cacheView/zero → NatTileBinding → 主控 indexed output_eq_nat → NatPrefix → NatReaderBridge → PackedReaders。建议验证根为 `R23NatReaderBridge.indexed_guarded_spec`，并保留真实 producer 与 tile 辅助根。helper 使用未改动 round9h `development-helper-audit-v8.py`，SHA `5b58eece211bd9cdaa270fc82bef624a5974c7d056732e19f54547c0fe6ef975`。

下一决定：以精确组合的公共 CI 编译/两模块回放/selected axioms 反馈修复；成功后才可替换公开入口并跑原完整 gate。先前 initial +0、固定乘加顺序、finish 特殊值回退与 batch 边界均由原运行时保持。无新性能测量；时间与 token 明细不足者 UNKNOWN，首探针在 14:37:32 完成。

## 15:04 当前验收更新

CI **40708758777** 的精确 `0d760ec9…` 已通过 statement、Submission/VerifyFull 两模块回放和全部三个 selected 根的允许公理审计。已重新读取原 `helper-audit.json` 并核实 SHA-256 `a678bff7458de6cfd55a271f95b370ec7d4cf3931a82c905760491c90c9e4890`；索引在本轮 `development-probe2-accepted.json`，其 `audit` 字段指向完整原件。该通过结论仅覆盖实际 indexed 外环的**条件读数证明**，不包括尚未组合验收的无条件 `indexed_guarded_spec`。旧源码/manifest 的 NOT_RUN 原字节保持。

第三批 **40711515352** 已由 D 启动；截至本更新仍等待原回执。主控 reader2 `7a41b05c…` 已纳入 producer 的具体 getInternal 语法修复；不能由旧 4c5b 的静态检查继承 CI。`NatPrefix`、`NatReaderBridge`、`PackedReaders` 完整组合的公开入口和完整 gate 仍未验收。

不同路线首判别见 `SHARED-BLOCK-FRONTIER.md`、`shared-block-frontier.json`：共享 A/B 块指数头可改变旧 SUM 扫描的摊销，但旧完整 case 触达上界只有整包 9.84%—11.48%，且实际无法删除全部；当前公共 10% 主线 PARK，无新候选/CI。跨 batch A4/B8 与首乘积负零修复均确认为历史路线，不重命名复跑。
