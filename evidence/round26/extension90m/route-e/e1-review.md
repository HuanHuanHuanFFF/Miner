# E1：短 same 前置 word 路径

缺口：#658 U118 对短旧 token 的比较仍先建立 k/ok 通用循环，再进入 word tail；编译器是否已消去这些状态与分支未知。变化：仅在 `u118_same` 中加入 len1..8、n≥8、a/b≤n−8 的前置直接 xor/shift 返回。最小有效操作是精确 Rust 的有限原生正确性与原协议配对计时；源码计数和数学等价模型不作为速度结论。由主线程调度，执行与预算沿用本窗，负结果保留。

历史查找读取优化方法汇总、round2* 报告，搜索全候选 manifest 的 short/same/word/len≤8 机制及候选、公开参照 Rust 的短 len guard，没有找到相同前置 dispatch 的已计时直接先例。#658 的 `pc_same` 和 `u118_same` 均保留原通用 loop+tail。**短 word mask 本身是已有机制**；本次只改变短输入到它的控制流，不宣称新匹配原语或已获机器码收益。

主可测 pair 见 [e1-entry.json](e1-entry.json)：Rust `bc1b3fec788a0d58d220efb84505e26f83a7045129c724f43095704c6097adc0`，父 Lean `354d56aa9f58536efdb410f3d5ecdf1945bded607965fe8a48161f96b035c494`。Lean 为父 scaffold，**UNCOMPILED**，不能作为正式正确性包。

新路径 len1..7 与原 k=0 masked tail 比較同一前缀；len8 用 shift0 比较整 word，与原第一轮等价。len≥1 排除 shift64，len≤8 给出 shift0..56；n≥8 与 a/b≤n−8 保证两个完整 word load 以及 a+8/b+8 不溢出。len0、长 len、近尾或缺少完整 word window 继续执行逐字保留的原 fallback。用户授权范围内没有修改其他函数、路由、encoder、token逻辑或C2/C3冻结对。

[有限模型](e1-finite-model.json) 通过 135,300 个 Python 语义比较，n0..24、len0..min(n,10)、全部合法a/b位置，模式为全零、递增、周期3及固定seed随机。检查还直接对照所请求的 byte slice 相等。这只能支持所枚举的模型，无实际 Rust 执行、机器码证据、原版抽取或 Lean acceptance。

另准备 [proof1-entry](e1-proof1-entry.json)：Rust 相同，Lean `f89c185a339c499c4b07deb7e25eb94a66c7b3bd6f28e51a6e36e64f997cee12`。新 `e1_mask_match` 使用既有 `Nat.shiftRight_xor_distrib`、`nat_xor_eq_zero` 和 `word8_prefix`，覆盖 len8；`same_spec` 的通用 fallback 继续使用原 same_loop0/Matches.mask 证明。草稿保留完整原 obligation，无 sorry/admit/新增 axiom，**UNCOMPILED**。实际提取后变量匹配、短路分支与原同名函数 loop interface 尚未验证，不能把草稿称为通过。

VERIFIED：来源、精确文件字节、单函数补丁与有限模型。INFERRED：所有合法调用的返回等价及现有证明结构可迁移。UNKNOWN：真实 native、gate、原协议净收益、编译器 lowering 和稳定份额。
