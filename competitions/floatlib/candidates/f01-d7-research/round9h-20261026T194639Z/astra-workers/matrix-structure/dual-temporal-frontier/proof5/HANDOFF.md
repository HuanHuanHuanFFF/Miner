# Dual proof5：三个真实末端目标最小收尾

`proof5/Kernel-dual-temporal-a4-proof5.lean` **241509 B**，SHA **c36bc2502904bf946d442de1a4646e09689f016643f09ab0b6788f9bdd375250**。只增加三处 `<;> rfl` /24 B；尾3/2/1之外不动，runtime/域/陈述/其余证明逐字不变。原b92d保留，18根与逆patch齐。

CI12/40430974047精确b92d已消掉全部equation错误，仅剩三个打印字段相同的F2记录等式。完整原目标保存在ci-40430974047/tail-goals.json，自有原件已核索引字节；此版用定义相等收尾，不重排FP运算。固定文本检查过，**新Lean/重放/根审计/C/全成本均NOT_RUN**。

下一步由D真实复编c36；成功后继续原callpath判别，不能用c70旧loop代替。Jam b372已交peer复验15根并冻结；不造新数学稿。R截止02:28:21 UTC不改，本方无Git/CI/本机Lean。
