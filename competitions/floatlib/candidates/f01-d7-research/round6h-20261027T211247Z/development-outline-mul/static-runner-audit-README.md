# 可复用实际 C 闭包初筛：纯函数已检验

`static_runner_audit.py` SHA **1806bb3c9a6aa4285a22a7a811d070c3257537d92295b9c8b79be832ce1efe00**。
接口为 `audit_static_runners(actual_c_bytes, wanted=DEFAULT_RUNNERS)`；默认五个 R22 IO 名称。成功返回 JSON-compatible report；失败抛 `StaticRunnerAuditError`，其 `.report` 保留完整失败与已经识别的闭包。函数只使用输入字节，不读写文件、时钟、环境或工具。

检查五个 named IO entry 仅有 World-compatible C 签名（World已擦除时0参数；或1个lean object参数）及object返回，并保留原D初筛的“入口内无运行时闭包构造”要求。同时扫描 `lean_alloc_closure` 与多行 `static const lean_closure_object`，拒绝两类中任何 `arity >= 3 && fixed >= 1`；记录 callback symbol、arity、fixed、owner、行列及字符位置。注释、字符串、字符字面量不当作代码；遇到无法解析的字段或动态计数字段时拒绝，不默默漏项。

C的object参数形状不能单独证明其语义就是World；仍须绑定精确Lean IO入口源码。全局初筛通过也不等于selected MUL已经arity2，必须继续逐五个runner的实际Suite参数追链到boxed／typed callback，再审核实际hot/cold ASM。静态arity3/fixed0等没有捕获的其他函数会列入清单，不会仅按arity误拒。

`test_static_runner_audit.py` 的 **19项**检验已通过，回执 `static-runner-audit-local-verification.json`。覆盖静态／分配式captured Bool、IO额外Bool／双参数、入口内动态构造、缺字段／非literal计数、多行重排、注释与字符串误报、重复／缺失entry、坏UTF8／未闭合注释及正例；另对原40432634558精确C SHA24770重核，识别3个static fixed0与2个allocated arity3/fixed1，并按预期拒绝旧ABI。该旧样本不含新五runner，测试显式指定其实际 `_lean_main` 只用于负例验证。

整合时可以由D薄wrapper把返回report写入out；若捕获异常，先保存 `exc.report` 再交给原诊断失败处理。40607316341不取消；本函数可先用于收件后的补充审核，再由D用于后续小screen。这里没有改D文件、官方gate或采用门槛，未跑Lean/native/CI。
