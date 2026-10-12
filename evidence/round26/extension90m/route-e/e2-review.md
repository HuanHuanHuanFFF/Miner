# E2 受控组合：C2必要尾过滤与E1短same

准备 UTC 15:36，新 [精确pair入口](e2-entry.json) 是 `r26-e-658-short-tail-proof1`；同名不带proof1的目录保留相同两文件，不算第二种算法。Rust `586dec576a2026a5f8c40b82f67e306bd3422faaf938eef2b477477e6af12b06`；Lean `623d2986bb15846b777c34ca4c17fe6f76ed43a9c4909e8c65ff95a397df3732`，**UNCOMPILED**。

机制和对照：C2在整个旧token比较前用必要尾字节检查拒绝不相等者；E1令实际进入的短比较走受界保护的直接word前缀。两处改动的关系不同，但E1缩短比较后也可能改变C2过滤的成本收益，净效果必须实测。主线程将给一次原协议配对，不相加组件改善，不在缺少该测量时以理论或计数淘汰。无收益时不追加机械组合。

静态构建从C2已通过精确gate的Rust起点出发，只将 `u118_same` 完整函数替换为E1同函数。回退原C2 guard后恢复E1 Rust逐字hash，证实无第三处Rust变化。新完整Lean从E1 proof2起点出发，只将 U118 BackInv循环定理替换为C2已通过gate的同定理，其实质差异为五行注释/端点界。

[起点绑定](e2-static-preparation.json) 保存全部Rust/Lean hash和C2 VERIFICATION的hash。C2组件gate通过只覆盖其当时pair；E1 proof2尚待真实gate，组合的native、完整gate、两轴和稳定份额均未验证。若E1之后需要证明修补，新E2需重新配对，保留本冻结版本及其成绩。

父作者与来源回执保留；C2/E1全部旧冻结文件未修改。没有本地重型工具链、Git、CI派发、正式上传或资金操作。

VERIFIED：新pair字节、逆转C2 guard恢复E1、E1same逐字复用、C2 BackInv逐字复用。INFERRED：组件语义可组合保持公共等价。UNKNOWN：实际组合程序验收、净时间收益和稳定份额。
