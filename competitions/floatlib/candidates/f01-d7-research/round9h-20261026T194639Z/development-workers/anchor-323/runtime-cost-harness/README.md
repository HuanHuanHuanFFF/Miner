# 748999运行成本Harness：有条件可行，草稿NOT_RUN

接手UTC 2026-10-27 00:01:23；前15分钟判别见[checkpoint](checkpoint.md)，总上限00:31:23。只写本目录，无Git/CI/本地Lean/新agent。

**建议：值得由D决定一次有界的独立诊断；不能直接挂进普通R19单候选120秒replay，也不是新public MUL或原gate。** 已找到可复用的小接口，无需改官方contracts/gate/bench/pins或手写compiler flags。

最小方案：[新Main草稿](R19RuntimeCostMain.lean)沿原MainFull三个imports，MUL直接用`@[inline] guardedMul Submission.mul`，不调用noinline diagnosticEntry。一个新binary包含control/guarded两个callback；`BENCH_VARIANT`只在main选择，timer和全部input构建继续由原BenchSuite完成。ADD/SUM/BMM始终是导入的旧B2，完整fallback/guard在MUL中计时。

[草稿函数](harness-draft.py)不改STAGES或插桩：`prepare`读取runner当前lakefile，只有benchFull target确为原默认srcDir/root两字段时，另建自有配置（原文件逐字节前缀＋自有lean_exe）。原lakefile本体不写。随后原g.own(build=write)构建新target；不用手写clang/link flags。Lake293d确有`-f`备用配置，exe通过root的原native link信息构建。[CLI原源码](https://raw.githubusercontent.com/leanprover/lean4/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/lake/Lake/CLI/Main.lean)，[Executable原源码](https://raw.githubusercontent.com/leanprover/lean4/293d5d0c0c3f3dded4688b3ccd6a33939ac5102b/src/lake/Lake/Build/Executable.lean)。

`build_and_measure`复用R13的156行parser/checksum函数和原g.run benchmark隔离。使用已见plan1927003/5原字节（各156例、152 timed），各按control/guarded/guarded/control执行，总8进程，原BENCH_INNER=3、CPU/memory约束；保留全行、慢样本和两对block的MUL/whole时间和。checksum任一不一致立即保留失败，不解释速度。这里whole是全152 timed case的诊断和，不是原25-round headline/采用统计。

## 真正构建成本及停放条件

- **不需**重新证明guardedMul等于乘法，亦不改748999或其旧public B2规格。**需要**新配置加载、新Main的Lean→C、新对象及一次link；不能只改Python回调或把原benchFull当作已测新代码。
- 原748999那批完整诊断replay已观测70.628秒；这不是新增Main的成本。历史R13六次完整进程共15.454秒（每次约2.39—2.76秒），仅说明该复用机制曾工作，不预测本次耗时。新增构建、8次本次计划执行及新caller代码质量均UNKNOWN。
- 草稿额外硬上限：构建≤180秒且不超过原g._BUILD_TIMEOUT，测量总≤300秒，后置复用nm/objdump工具最多32秒；不增加原资源caps。需要R13式**独立可信诊断预算/entry**，现有个体120秒路径未接入；本任务没有改dispatcher或派CI。
- 若触发大依赖重建、原MainFull/Submission对象或benchFull身份改变、当前benchFull有额外target flags、实际新compile/link flags不匹配：停止，不再扩框架。当前4b7 gate/lakefile远端读取cache miss；因此不把旧缓存lakefile视作当前原件，prepare必须在runner检查真实文件。

## 不能混同的结果

capture-mainfull/capture-codegen是原gate观察器，不能替换typed callback。草稿仅复用其有界post-tool；新C/对象/trace/binary在测量前后哈希绑定，C/ASM后置留存，原官方源码和原bench对象前后核验。不保留ELF到本地。**真正link facet/flags及control/guarded实际closure、额外call/spill仍须在CI产物上复核**；当前AST不能替代它。C发现diagnosticEntry直接拒绝，其他inline/caller差异仍须人工审阅后才能解释成本。

新Main和未来public MUL caller的布局、shared fallback frame可能不同；ADD/SUM/BMM维持旧B2，未来若重接其transitive scalar调用，本harness whole不能代替未来whole。即使两份输入所有checksum一致也只是有限样本，不证明新public正确性、原gate、adoption或冠军速度。58/62静态指令不得推收益。

D若同意，复用R13式独立diagnostic入口，在精确748999的成功原statement/模块/7root之后调用：

```python
prepared = harness.prepare(g, kernel, out)
try:
    harness.build_and_measure(g, prepared, out)
finally:
    harness.cleanup_owned(prepared)
```

这不是可直接使用的dispatcher入口。所有运行函数当前NOT_RUN；只通过[AST/哈希/准备fixture/合成行复验](local-verification.json)。fixture未执行g.own/g.run，原始官方文件、候选和flags未改。完整证据/边界见`feasibility.json`，产物哈希见`MANIFEST.json`。
