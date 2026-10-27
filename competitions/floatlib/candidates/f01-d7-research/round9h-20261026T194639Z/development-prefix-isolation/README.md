# 独立prefix进程判别 v2（待D派发）

UTC 2026-10-26 23:29:01接手，15分钟预算。仅修改已授权v2草稿、新增本目录及`f01-r19-dev-prefix-isolation1`；无Git/CI/本地Lean/新agent。旧resource-audit.py、v5、ci-diagnostics、统计及旧marker候选均未改。

- v2旧稿已逐字节保存为`resource-audit-v2.before.py`，原SHA `89134b37b25d67a15dd87881ca687113d9a5328fcd713b785408921971691340`；原路径/大小见`draft-before.json`。
- carrier Kernel逐字节为B2：226829 B，SHA `622d8394a7127e93dcaf992c62c6dfcff7208d212738409a5e34525dfafd1a58`。manifest指向`development-resource-audit-v2.py`及其新hash，components仅本R19新目录内文件。
- ImportOnly完整模块18 B / `239175fe9907a272f0b9816f700dbc310b5b3e33ffca567fde220339d93ffa70`；QuotientOnly完整模块1341 B / `014acd413d37ee012bdc55fb813591815ccb5dce0adf09f27dac9a17fd68573d`。均原字节复制，不prepend import，不加#eval/options。

执行顺序：原v5仅一次B2两模块重放＋原4根axiom audit；然后一次独立`g.own([LAKE,'env','lean','work/R19ImportOnlyPrefix.lean'],cap,build='read')`。ImportOnly失败/异常/预算不足立即停，QuotientOnly保存NOT_RUN状态；只有正控退出0才再用独立g.own运行QuotientOnly。退出0只说明对应完整prefix进程完成，不说明1180完整Kernel/spec或新候选通过。

沿用原g.own的资源隔离和build=read，不改内存/CPU/env/编译参数。每call上限仍≤180且≤g._BUILD_TIMEOUT，并按stage注册起110秒剩余预算收紧，预留5秒记录资源/查询/写回；默认外层诊断120秒仍约束整次replay。预算包括注册之后的原carrier阶段；若原阶段已耗尽就不启动prefix。它不扩大原v5阶段的caps，外层注册前开销也没有被伪称为零。

资源采样仅/proc comm、status RSS、cgroup v2的memory.current/peak/max/events；不读进程args/env。仅查询采样确实观察到的run-*.scope的原6个属性，最多4个、各≤0.5秒。RSS和scope关联仅是证据，不由137等非零码自动断言OOM。

**新schema，不复用旧resource-feedback.py：** artifact输出为`prefix-isolation/summary.json`及每个`prefix-isolation/{import-only,quotient-only}/`下的`source.lean`、`output.raw`、`resources.json`、`summary.json`。summary含schema_version=2、每prefix独立exit_code（未运行为null）、状态、source/output/sampling哈希、资源及scope属性。即使未运行也预留源/空stdout/空resources及状态；异常的可用部分stdout保留。两个子目录还逐字节复制同一份已执行的B2 `helper-audit.json/helper-audit-source.lean/helper-axioms.raw`，复制不代表重跑审计。

`verify-prefix-isolation.py`的AST/hash及五个mock场景已PASS：双成功、正控失败后停止、quotient非零、预算耗尽不启动、异常部分输出留存；均检查B2 kernel replay调用1次、四根audit own调用1次、prefix调用顺序/个数、原始源字节及完整哈希。mock stdout均标MOCK，位于`mock-fixtures/`，不是真实Lean或资源证据。

复验：`python -B competitions/floatlib/candidates/f01-d7-research/round9h-20261026T194639Z/development-prefix-isolation/verify-prefix-isolation.py`。真实prefix Lean/资源状态全部NOT_RUN，CI未派发；由D核hash后使用已预留v2入口派发。本目录`MANIFEST.json`和`local-verification.json`为交付索引，不能当作1180证明通过。
