# R26 fallback C — 当前交接

最终交接09:55 UTC；实际首clock09:02:35，共同截止09:55:15。只写本目录；严格文件通信；Git/CI均由D；本角色无本机Lean/native、无CI、无正式提交。全体Lean仍 **NOT_COMPILED**，无速度/完整gate结论。

已处理父09:41源审（09:46读到）：实际ma/mb各≤2^31，UInt64乘积≤2^62不先回绕；`preparedBody`本身每dot重扫两侧max，成本探针prepared模式改用已缓存max，二者边界不同。`@[specialize]`不等于已见无装箱；旧R24已结构递归/每MAC无分配，未重标创新。

- **第一编译入口**：`WordBlockRuntime.lean` **2612bcae…/3287B**，真实UInt32 getter→UInt64标量block16→lo/hi分参128合并→Int bias/finishWord，false guard惰性回shipped。`WordBlockCarrier.lean` **33746c38…/18821B**给实际索引乘加、进位、符号恢复、getter和尾块证明草稿。
- **原目标桥**：`WordBlockStaticV2.lean` **37dfa5c4…/41343B**把max guard、n≤2^20全局界、body+bias一次舍入接至原`dotOf(n+1)`；zeroSafeFinish在精确零回shipped保留±0。实际扫描/缓存元数据仍须证明满足显式前提；这是未编译源码链，非已闭合证明。
- **可测成本源**：`WordBlockCostMain.lean` **3152bdda…/8999B**＋normal/sparse fixtures，11轮×3次，比较each128/block16 prepared/full。160输出的源级重放通过，native未跑。它未接入D当前MainExact-only bridge，下一窗口按`NEXT-COMPILE.md`建临时自有target；不是完整模型，也非D现有word128基线对照。
- **有限证据**：`word-replay.json`160/160公开typical seed42首层点积、9尾长、125合并边界；源n608实际有39次合并（38非空＋1空尾）。`guard-counterexamples.json`保留±0及新bias反例：1−1+minSubnormal应word1，负移位−103截成0会错成679477248。`zero-fallback-census.json`同样本精确零回退0/160、ReLU零81/160，不能当部署概率。
- **第二机制与后续**：`WideBandRuntime.lean`实际索引/移位循环，1个wide点积逐字一致，14非空块合并＋10段移位合并＋608索引读；45移位边界。`WordBlockTwoChains.lean`独立后续变体160点积/12尾长一致，单/双链控制都省空尾，未测速；不把它计为第二独立路线。

`policy-preflight.json`8份helper的原intake/policy AST通过；`delivery-audit.json`核对精确source/parts/fixtures，不能替代Lean。`probe-plan.json`列首个最小验收；09:38后无新CI请求。已读D run40849705068依赖故障，未编译候选，未据此改冻结源。分支与D当前候选对接差异见`INTEGRATION-BOUNDARY.md`；资源/失败保留`resource-ledger.json`、`preflight-failures.json`。本角色于共同截止结束新增工作。D run40851060907也因队列截止执行0命令，仍无任何本目录编译或测速；后续原始回执由D回收。
