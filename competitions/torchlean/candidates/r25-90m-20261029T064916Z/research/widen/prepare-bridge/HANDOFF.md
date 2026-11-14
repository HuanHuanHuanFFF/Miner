# R25 prepare 真正生产者接口

阶段首次工具07:41:15 UTC，07:58前交付；共同截止08:19:16。原始CI40834710293已复读：仅 `widen/Kernel.lean` **a88c70e5** 原full gate、Submission/VerifyExact replay、6 helper allowed-axiom均通过，55.314s。新actual/finite/prepare不继承接受。

- **新源码，NOT_RUN**：`PrepareAgreement.lean.inc` 6042B / `b08041257148669ba988ca15a319f0ad188aa6a5a95205b2555f24fd12dcf5a0`。核心 `prepare_eq_forIn` 连接原Id.run和完全相同的三变量state与分支；`prepare_eq_fold`后才证明实际 `prepare_values_data/size/valid_rawfinite/get/getter_interface`。不以pure替身结论代替原生产者。
- **精确原producer补片**：`PrepareRuntime.lean.inc` 883B / `b785d5e7a97703f717c7a310cddafb8376ee4ff2d9cb1af0897f1c3ecd261880`，仅原Prepared、index32、prepare，除LF归一无修改。既有完整actualruntime若已包含这些声明就不重复插入。
- **组合次序**：已接受W7（只借用expWord定义）→现有 `actual-bridge/ActualRuntime.lean.inc`（仅sx/sr/fastLog2/widenBits）→PrepareRuntime→PrepareAgreement。**不依赖actual/finite桥的未验收定理**；当前结论止于真实缓存读取的Float位值等式。未构造大Kernel、未排CI、未改资源。
- **优先检查**：先 `prepare_overflow/prepare_valid_sizecap`，然后必须检查 `prepare_eq_forIn`。后者若失败，保留前两根并回传原目标；其后所有fold/getter根不能算闭合。若通过，再检查body_yields、fold和getter_interface；所有声明此刻均未编译。
- **输出**：valid=true 推出 raw.size≤2^30、缓存size=raw.size；每个inbounds raw word不是exp255，真实FloatArray.get!等于Float.ofBits(actual widenBits raw[i])，并保留raw字段。最大指数/peak不变量、Tail、实际radius与native value后接未包含。

Lean4.34源已核默认 `backward.do.legacy=false`（固定源及完整Git blob见source-api-receipt.json）；新For明确按mutVars声明顺序组Prod，Basic按push登记，ProdN右结合，因而state是 `(FloatArray × UInt32 × Bool)`。该源级核对不代替 `prepare_eq_forIn` 的真实Lean检查。

本阶段普通交接仅文件；原始gate/hash与本片段来源统一见 `prepare-source-receipt.json`。token/cache/模型CPU UNKNOWN，本机Lean/native/Git/CI均无操作。下一步由主控根据剩余吞吐选择验证，不自动扩大队列。
