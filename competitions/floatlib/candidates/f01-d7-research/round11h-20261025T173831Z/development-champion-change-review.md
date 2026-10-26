# 冠军309→323：保留源成本，只换官方参照

11:18:38UTC原始官方快照`official-20261026T111838Z`完整，leader/champions/detail/report一致为323，源码仍404；digest00fedf81。323于08:16:47晋升，入口08:15:31快照尚为309，非我方代码变慢。

待独立检查：323完整score报告同scoring-v2 suite2e329、同verifier d5b7，`champion_sha256`精确指向旧309 digest a549。每cell的`submission_ns/incumbent_ns`为323/309的同轮比值。拟保留9222旧模型及全部B2冻结成本、源delta、工作量不变，仅将旧anchor的309每cell投影成本乘上述官方同轮比值，再按原六个冻结工作量分别重求四项及整包中位数。不得用323跨机器绝对ns直接替换309投影，也不得用本轮B2控制重拟合。

旧9222原件另存development-previous-champion-model.json；新模型须引用旧模型SHA、官方原报告及digest链，当前看板改为323基准。请R在自然检查点核公式和digest/suite链，如不成立具体指出；D先做dry-run，原数据不覆盖。

ADD93cc已在40313517927/seed1826007运行，源93dde47b。预计11:32左右可收齐，仍11:45:28截止，不再开新候选队列。
