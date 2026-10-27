# B2 前缀 UInt64 接口探针

精确输入 `Probe-b2-u64-roundtrip-v1.lean`，240164B，SHA9f9a297e90f236c349283248cca9aa8f94c35ff24ebe9e26873e2c63d708a933。原622d B2全文226829B逐字保留；只追加15个所需支持声明和原冻结13-helper数学片段。无新运行入口、无参数调优；原v1/v2/v3片段均未覆盖。

固定原gate intake/policy/options（含注释）、单import、≤256000B、canonical LF及read_bytes=read_text.encode检查PASS。仍NOT_COMPILED。`manifest.json`记录精确支持切片、15个依赖根与13个新根；`HelperAudit.lean.inc`恰列13个新根。原四spec通过不能替代新根重放／公理审计。

最小操作是原工具链statement；成功后完整模块leanchecker和显式13根依赖审计。没有性能变更，不需要计时。本probe不含新的guardedMul，也不建立整个MUL public spec。

错误判别按首个真实声明定位：支持命名／依赖问题只修新支持附录；`toUInt64_of_nonnegative_integral_decode`检查实际toInt构造子归约、目标整数类型及clamp界；`native_uint64_decode`检查R14舍入decode的指数等式；`product_word_nat`检查UInt64无回卷；`shift_recovery`检查shift mod64与整数除幂。先保存精确goal/日志，不凭上述可能性预改冻结v1。逐声明原行号在declaration-lines.json。

本方继续在独立后续片段推进原始MUL spec所需的阈值、移位和字段恢复，待D反馈再修这个精确输入。当前3.5h窗口08:15:28—11:45:28UTC；本阶段09:10交付点不变。无Git/CI/本机Lean、无模型重跑。
