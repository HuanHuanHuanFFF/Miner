# R7：R6 `FL_CALL=0` 诊断与最小修复

检查时间：2026-10-22 18:41—18:48 UTC。只读检查现有源码、原始回执及精确官方版本；仅新增本报告。未改共享脚本、候选、官方 gate、Git、CI 或浏览器。未安装或运行本地 Lean/Linux 工具链。

结论：**VERIFIED 的源码级原因是函数提取正则提前结束，正常执行的最后一个返回完全没有插桩。** 这足以解释编译、链接和 checksum 成功而 `FL_CALL=0`。已在内存中对实际原始 C 重放并验证最小修复；修复后的 Linux 二进制运行仍为 **NOT_RUN**。R6 没有有效阶段份额，不应补算或推断。

## 精确证据

回执根目录：

`competitions/floatlib/candidates/f01-mul-log2-proof1/ci-runs/39789494626/download-1355dba2673f427a90994d7eab3b7f9e/diagnostics/f01-d6-costsplit/`

| 文件/对象 | 字节数 | SHA-256 |
|---|---:|---|
| `Kernel.lean`（已复核 costsplit 与 stream-pack 两份相同字节） | 139972 | `8eb63a2fea39f8c483eb16857cb1dcc35ac4a30168ab91046a48aa1cb561e045` |
| `candidate-generated-0.c` | 708275 | `65665cb68141c2603e48f62731058e45414af8faeffce9b1d02040e8a7705677` |
| `profile-instrumented.c` | 709624 | `0eb9ce3a47a49f7fb8f1db73276cf9bc430a990d78c229bd4429e1ba56475239` |
| `candidate-generated-1.c`（MainFull） | 46901 | `d70999b770e0cd893281c8d49ee8e0297684dfbe787977ee5685d387dc88cd34` |
| `profile-instrumented-0.log` | 507 | `655b392ef3117309d082503cd262a8a338f5a3ecddc55ba231eb524d28de7e4c` |
| `profile-control.log` | 507 | `d050338753d4a33df306797bb47403784c1f2607fdcdf0c29a2a78c34ebcf86b` |

`f01-d6-research/profile-scored.py:8` 和 `:29` 使用尾部 `.*?\n}\n}` 提取函数。它识别的是第一组相邻右括号，未识别函数真正的结束位置。

在实际 `profile-instrumented.c` 中：

- `RowStream_core` 从第 23039 行开始，旧正则只匹配至第 23101 行，完整函数至第 23112 行。
- 第 23061、23090、23099 行的三个返回前都有 `FL_CALL`。
- 第 23076 行计算 `lean_nat_dec_le(v___x_7941_, v___x_7941_)`，即同一个 Nat 与自身比较，结果为真；正常非空输入进入第 23102 行的最后一个 `else`。
- 该分支调用真实行循环后，在第 23108 行直接 `return v___x_7951_;`，前面没有 `FL_CALL`。前两个已插桩分支是空结果或不可能的比较分支。
- 行循环的旧正则也少包含一个函数右括号（原始 C 匹配范围 22958—23013，左/右括号 4/3），但 tile/output 两个实际调用点都已被插桩。漏掉整个正常返回是本次零输出的关键。

调用入口也可定位：`candidate-generated-1.c:62` 的闭包指向 `Submission_bmm`，`:1647` 传入 `Bench_runFull`；`Submission_bmm` 在非空且 n>0 时调用 `RowStream_core`。因此不是仅凭函数名猜测死代码。

## 已执行的本地红绿检查

所有检查均只在 Python 内存执行，没有生成候选或构建产物。

1. 重放原日志断言：实际 `FL_CALL` 数为 0，期待 13，断言失败；`profile-error.txt` 指向脚本第 92 行同一断言。控制组与插桩组均有 16 行校验结果，checksum 一致。
2. 执行当前 `instrument(candidate-generated-0.c)`，输出与保存的 `profile-instrumented.c` **逐字节相等**，两个 SHA 如上。排除了分析了另一版插桩源码的可能。
3. 在完整函数范围检查每个返回：四个真实返回中只有三个包含相邻记录；最后正常返回缺失。
4. 只对两个函数正则的尾部增加下一顶层导出函数约束，在内存重放同一个实际原始 C：`FL_CALL` 站点由 3 变为 4，全部四个返回均已插桩；行循环括号由 4/3 变为 4/4。

测试输出摘要：

```text
instrument(original) equals captured bytes: True
legacy regex lines: 23039 23101
full core lines: 23039 23112
full return count: 4
legacy matched return count: 3
RED: the final real-function return is outside the regex, so it has no FL_CALL
GREEN: repaired exact-original instrumentation covers all 4 RowStream_core returns
FL_CALL sites before / after: 3 4
```

## 最小修复及首次可证伪检查

对本次保存的生成 C，最小已验证改动是在 `profile-scored.py:8` 和 `:29` 的函数正则末尾加：

```python
(?=\nLEAN_EXPORT )
```

即尾部改为 `.*?\n}\n}(?=\nLEAN_EXPORT )`。两处均需处理。这是针对当前 Lean 生成格式的最小修复；应同时断言选定片段包含完整、平衡的函数体，且完整函数内每个 return 都获得恰好一次记录。若后续生成格式不再满足下一函数为 `LEAN_EXPORT`，应直接失败，再使用忽略注释/字符串的括号扫描提取完整函数，不能静默退回原正则。

首个 runner 检查只需重放同候选、同旧配置（702 / 500000 / inner=3），无需新 gate 或更改官方源码。**预测是出现 13 条连续 `FL_CALL` 且 checksum 完全一致。** 若仍为 0，当前解释未被运行端确认：先检查最终二进制是否包含 `FL_CALL` 字符串及正常返回对应的 printf 调用，不应继续计算份额。保留完整 `benchFull.rsp`、编译/链接命令、原始/插桩对象和二进制 SHA，区分未链接新对象与未调用该函数。

构建路径检查：保存的命令重编译 `Submission.c.o.export`，再通过 `benchFull.rsp` 重链接 `benchFull`；官方旧版 `gate.py` 的 write/read overlay 均使用同一 LAYER upper，因此“改了 upper、只读到 lower”没有源码支持。原回执未保留 rsp 内容、重链接后二进制 hash 或该返回的反汇编，故不能把实际重链接身份写成独立 VERIFIED。源码缺失记录已能解释全部现象，不需要假设 overlay 错误。

## 后续 current public-v2 诊断必须另做的绑定

这些是新套件迁移条件，不是 R6 零输出原因。

- 精确绑定候选字节、生成 C、官方 `4b7e83841cc0c32c6529f533923c73d33b5ecf97`、suite SHA、官方 generator SHA、实际 seed/work/inner 与完整 drawn-plan SHA。
- **必须把同一个官方 drawn plan 的紧凑 JSON 作为 `BENCH_PLAN` 传给控制与插桩进程。** 当前 `profile-scored.py:70` 没有传它。当前官方 MainFull 明确在缺少该变量时选择旧类 benchmark；只设置 `GATE_FULL_SUITE`、seed 或 pairs 不会让直接执行的二进制使用新套件。
- 从精确 plan 按顺序生成调用表：每个 timed BMM case 先 1 次 checksum/warm-up，再 inner 次计时；untimed raw/check 只有 1 次。每条绑定 case name、timed/phase、rep、batch/m/n/p、work，不再使用 `(call-1)//4`、固定四类或 `rows==100`。
- 本地现存 `initial-public-plan.json` 的 SHA 为 `903683eb628c5344bda06c111083207fe3f1a821d31693b4556ef978a20843e4`，实际是 **34 timed + 1 untimed BMM case**，inner=3 对应 **137 次**，并非 153。其 batch*m 范围为 4—176468。后续 plan 若有 38 timed case 才是 153；必须重新从实际 plan 计算，不能继承此处数字。
- 最外层 `Submission_bmm` 应有调用计数/路由核对。精确 parent `f01-d5-stream-pack` 的正维度可走 RowStream；若换为 direct-small 等候选，不能假设每次 BMM 都进入 RowStream。各 route 分开记录和验收。
- 不要求每个阶段耗时都严格大于 0：很小 case 可能落在时钟分辨率内；保持非负、完整计数/行数和 checksum 约束。每行时钟探针会增加开销，尤其 batch*m 很大或每行很短的 case，所得为诊断分解，不能冒充官方性能份额。
- 计时样本、checksum/warm-up、untimed raw 分列；先完整保留逐调用数据，再只用 timed 样本讨论阶段成本。官方验收与排名继续使用未插桩 gate 回执。

当前官方原文已按精确 commit 通过 GitHub 连接器读取：

- [MainFull.lean：BENCH_PLAN 分派](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/4b7e83841cc0c32c6529f533923c73d33b5ecf97/lean/bench/MainFull.lean)
- [BenchSuite.lean：measure、runBmm 和 plan 顺序](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/4b7e83841cc0c32c6529f533923c73d33b5ecf97/lean/bench/BenchSuite.lean#L184)
- [当前 gate.py：bench 的 BENCH_PLAN 注入](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/4b7e83841cc0c32c6529f533923c73d33b5ecf97/gate.py#L594)
- [旧精确 gate.py：overlay 写入与读取](https://github.com/conjectures-io/conjectures-optimisation-float-kernels/blob/978cc5b445edb9943fd9953b0a9037d97a9f33a8/gate.py#L295)

未运行修复后的 Linux binary，没有新的 gate/排名或阶段份额结论。原始失败回执保持原字节。

R7后续实际回收：807/39840672791已完成Linux未插桩控制与三份插桩binary，137次BMM调用逐一对齐，所有checksum一致。完整产物与开销异常见[profile-summary.json](profile-summary.json)，不改写本诊断时的未运行状态，也不把finish/raw fallback算作纯分配。805单独诊断的编译命令筛选失败原件保留。
