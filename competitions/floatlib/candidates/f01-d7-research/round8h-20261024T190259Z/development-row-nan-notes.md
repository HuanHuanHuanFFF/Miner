# 按行NaN分流与延迟准备

旧RowStream先准备原生A与打包B，对每行执行完整native点积，最终NaN时再从原始字回放。若A行包含NaN，回放通常会早停，先前完整native计算和准备可能成为可消除的重复成本。

本次只改RowStream：每行先读原始字；有NaN则直接用既有`replayEarly`逐列输出，否则走同一Packed10路径。分类只选成本路径，两个分支各自对任意输入等于原序dot；不假设原生NaN payload相同，不改每步舍入。

A转换与B打包放入本次函数调用内的两个Thunk，首次需要才求值，其余行共享。固定[Lean4.34 Core声明](https://raw.githubusercontent.com/leanprover/lean4/v4.34.0/src/Init/Core.lean)给出纯逻辑getter及一次求值缓存的内建运行支持；未新增extern或修改运行时。仍需实际生成代码、完整gate与计时验证是否按预期降低成本。

零维和非RowStream路由保持原样。风险是普通行增加扫描与Thunk访问开销；NaN在B而不在A时此版不主动分流。不能把命中频率换成可消耗时或提前宣称收益。先编译原全输入等式，再测包含扫描、准备、输出和回放的完整调用；仅过固定门槛的冻结源码进入两组新输入确认。

源与状态见[构建记录](development-row-nan-build.json)。当前NOT_RUN。
