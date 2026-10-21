# Public #628：五分钟只读起点审计

结论：#628 是 public609 的种子解析器加 route 选择性码价重解析/另一引擎组合，不是本轮快速 PC 的局部低成本改造，也不等同于本仓 B。可迁移线索是利用已验证种子匹配、依据 token 块码价选择计划；完整新增机制具有多遍扫描、DP 和缓冲成本，不能据源码或正式总成绩承诺低成本收益。本文件仅作为下一轮起点，未新建候选、运行工具链/CI 或改变任何冻结源码。

## 来源与绑定

普通公开 source 接口在 snapshot29702 返回 #628；原响应保留于 [receipt](../luna/source-628/receipt.json)，作者 hotkey `5DM8HSJ17XPGKYTERQUbQuhqWJm3RtpJqTSUH7Dn8m5MVuJ6`。Rust `784e02703c98a32f85753cae4f3b62aea3f505d91088869f327e0ad646629c14`（312445B），Lean `7c909191f2801e76ac5080966d6df5339191ce48a97a16a3e66ee2a0ca4c636e`（523018B），两份本地字节与 receipt 精确一致。

public609 来源为 `references/round24-public-609`，作者 hotkey `5DPo51y7zmk2WfnkvU4MxAqw66ouW9KonrUGguLRWtPqiP9t`；Rust `05f535a6411cefcc5ebd1cd6fe394d7cf23eb8dd8f6ad3361d445a5bf77994a4`，Lean `2d20d999d4a238c891d51e0d5ef484ac4509fc2738016a3cda0fed96aa15fa47`。B 为 `r24-609-fast-adaptive-proof1`，Rust `ef3268f4b4183b50af7825e505266c7dc05b49e9bb1aebb1f642a5609fc6423e`，Lean `09f79e1d6b4d60bdcc692425a7baae6503f3995f8cc6f9937d7f23a347e9e20e`；其既有作者归属及 gate manifest 不修改。

#628 原响应正式 time5.8521311587 / quality34.0914226175。主线程报告同29702快照 #629 time5.845479、同显示质量，支配 #628，使 #628 当前为零；此处未重新联网或独立评分。#629 源码 UNKNOWN，相同正式质量不证明相同源码。609 的旧 source receipt 成绩属于不同历史快照，不能作为本次配对性能证据。

## VERIFIED：大类源码差异

静态比较提取顶层 `pub fn` 的括号正文并去除空白；该方法只判断文本差异，不证明语义等价。详细函数及常量差异、全部字节哈希见 [机器回执](public628-handoff.json)。

1. **609 种子家族保留，但 postprocess 选择被重排。** `Z469` 分类器、`SFbase` 及大量已有 helper 正文相同；共用 helper 真正改变的是 `SFenabled`、`SFshape`、`SFdepth` 及入口 `parse`。628 增加 `SF_MODE`/`SF_DEP` 表选择是否处理、重处理模式和深度；28000 字节的 `SFtinytokens` 路径被移除，40000 字节 `SFtinyrun` 正文仍相同。此前按下一函数截断会把邻接常量变化误报为 helper 变化，本回执改用正文括号范围。
2. **删除609入口重复调用，不是对B的新收益。** 609 的 `parse` 在 `ZREPEAT` 非零时先调用一次 `Zmain`，再无条件调用一次；628 的 `seed_parse` 没有这个入口重复。B 已直接单次 `Zmain`，所以不能将去重复的机会再次记作相对 B 的新优化。未运行 token 等价验证，也不将静态删调用换算时间。
3. **新增 RF 块价候选与迭代 DP 重解析。** `HY_REFINE` 仅 routes18/19/23/24 非零，配置分别5/2/4/34。`rf_find` 扫描位置建立候选，使用种子剩余匹配、3-byte 链及配置可开的4-byte链；`rf_exact` 按16384 token 块统计频率、内部 package-merge/block 模型与码价表；`rf_dp`/`rf_dp_relax` 搜索长度选择，`refine` 迭代后只在内部估价 `bestbytes < seedbytes` 时返回替代计划。源码有最多16轮保护；这些四个现有配置实际轮数字段均为2。内部估价不是原 encoder 回执，不保证真正重编码更小。
4. **新增仅class18/350000入口的 E 引擎。** `EPon` 要求 `input.len()==350000 && Z469(input)==18`。`e_pick`/`e_quality` 用有限前缀观察选择模式，`e_parse` 按32768字节块规划，含 dual/BF 候选、后向码价与 refine/fallback；发射由 `e_verified` 再检查长度、距离和字节匹配。其他输入首先走 `seed_parse`。不能把这条窄入口移到所有快速输入，或据函数名宣称同本轮dual8机制。
5. **B 的本地快路径未被直接沿用。** B 的 `Afirstword`、`Aroot145/162/186/189`、`Z145full/Z186full` 及 `SFprice_bend` 不存在于628；相对B，SF solve/候选 helper 与 Z145/162/186/189 等正文另有差异。628保留的是609对应代码，不能继承B的性能测量或证明迁移结论。

## INFERRED：可迁移线索与最低下一步

优先看 RF 的“复用种子匹配、按真实 token 块构造码价、只接受内部估价更小的计划”能否解释哪些文件的质量差。它与本轮 tinyPC 的字母表成本问题相关，但完整 RF 还要位置扫描、候选收集、两轮 DP/块价重建及 O(n) 数组；并无本轮低成本质量机制已成立的证据。SF 表化选择可以减少特定旧 postprocess 工作，但改变路由处理与质量，且B已经删除入口重复；也不能当作免费提速。

下一轮最小判别是冻结628，原28输入记录原token/output/decode、实际seed/E/refine路径及内部估价接受事件，与609、B、combo配对原encoder质量分列。先定位质量差由种子、SF选择、E还是RF贡献，再决定是否值得做一份机制消融。不得先复制路由、删过程或将RF缩小后声称保留质量；更不能用正式总体quality近似相等来跳过逐文件检查。

## UNKNOWN 与证明风险

本审计未运行628原版完整gate、Rust、Lean、原encoder或配对计时；其本地安全性、公理/obligation、真实逐文件收益、对B/combo成本及629源码均为UNKNOWN。若迁移RF，需要从真实提取检查计划表示与decoded-prefix、候选安全、DP回溯、数组初始化/界限及最终emit接口；628附带Lean的存在不替代新候选精确gate。E的发射全字节验证及大栈数组亦有实际成本，不能仅因安全检查完整就承诺快速。
