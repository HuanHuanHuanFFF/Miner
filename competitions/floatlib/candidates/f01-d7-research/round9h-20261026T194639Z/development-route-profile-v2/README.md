# route-profile v2：只修metadata的eager输入构造

**CI10直接原因已证实：第二个metadata调用因剩余预算返回124。** 第一个1927003调用实际exit0，30.0s输出35标签；两个原binary随后exit0（2.5/4.6s），完整seed3 partial已保存。1927005只剩约22秒，原日志明确timeout，stdout0字节，module elapsed60.178s。不是“完整35行后main非零”；没有type/main-return错误或OOM/137证据，metadata RSS未知。原证据及红色trace检查在worker route-profile/recovery/CAUSE.md和cause.json。

v2最小变化：RouteLabels的两个`Vector.ofFn + Array.all`替换为同count/role/row、同原Bench.Suite.element/float和候选UnderflowZero.small的第一次false即停止扫描。aSmall/bSmall仍分别完整求值；路由判断、打印格式和main返回不变。没有materialize大数组，true时扫描全部元素，false时短路，逻辑等于原all。实际新Lean执行及节省时间尚NOT_RUN，不承诺此次一定在60秒完成。

原两份plan、原始输入、622d Kernel、原timer binary及CPU/inner3/pairs500000/两process配置不变；cap仍60，inner120/nested180及8秒reserve不变。driver仅把泛化metadata错误改为含seed/exit/elapsed，**仍先要求exit0，再解析全部标签**；绝不把stdout完整当成功。原v1包、hook、候选manifest和原回执没有覆盖。输出销毁边界仍待实际BenchSuite C复核。

候选为`f01-r19-dev-route-profile2`，hook为R19根`development-route-audit-v2.py`。8个运行组件均绑定本目录。当前全局ci-diagnostics只allowlist v1名字：**父会话须登记v2 hook名后再派发**；本任务按边界没有改全局ci、准备器或collector KeyError逻辑。

`validation-receipt.json`包含Python语法、组件/manifest/hash、hook导入、8191个有限布尔数组的eager/lazy结果一致和协议参数未变检查。打包当时v1保护清单全部未变；随后仅旧candidate1 manifest出现并发变化，前后hash已记录，未覆盖它。它不表示实际Lean或CI恢复成功。package-receipt.json保存v1保护清单；两个最小diff在worker recovery目录。真正绿色反馈须父会话在相同资源约束下运行v2。
