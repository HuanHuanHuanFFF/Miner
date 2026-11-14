# NatPost 条件计划快照（已被后续定位推进）

406146已证401d OOM，故5b按门槛SKIPPED。当前唯一状态入口为 `../HANDOFF.md`，最新helper为b9b7 NatBiasExplicit；以下保留当时条件计划，不作当前排队指令。

- 原cbdb2 NatPost在406115发生4GiB物理OOM；原8d49 NoWrap typecheck PASS，原文保持，额外axiom/replay未跑。整包88cdf原因仍UNKNOWN。
- **先验** `NatPostBeforeNormalized.lean`：401d368efb2ab40358f1fa6b2e23fad2b0577e52393c2558e478284fb294ed30／3131B。原前3115B逐字保留，仅去最后声明，4根，NOT_RUN。
- **仅401d PASS后试** `NatPostLightNormalized.lean`：5b3e6b56cf66cfe0e124ac9424d9a8cebb83891718ca7073a39d0e722eeb26d1／7282B。原normalized陈述/域与shift/biased不动，新增6私有B-only引理，新段0 omega；未编译。API固定293d：div_eq_of_lt_le先lo后hi。16整数边界检查不能替代Lean。
- 若401d OOM，按`natpost-declaration-index.json`继续向前切；不把最后normalized当原因，不运行轻量版制造“修复”叙事。
- helper通过后，公共splice预计257924B，只移除全空白行可255981B／余19B（f3968adc…）；详见`blank-line-capacity.json`，未物化新整包，88cdf未改。之后仍跑原完整gate、49根与实际MainFull，不继承诊断成本。

`prefix-manifest.json`／`light-manifest.json`绑定全文。仅本方文件，D唯一Git/CI。共同截止03:12:47Z不变。
