# R2-W01b 诊断命令

当前执行记录：C 与独立 Python 诊断已运行；Lean 编译、依赖审计与生成码均为 **NOT_RUN**。本文件与 `AuditAdmissionZero.lean` 仅供诊断，不属于候选 Kernel，不能拼进词法 policy 检查的候选文件。

## 1. 复现同一 C 协议

先在解压后的包根目录阅读已有 `results/`，保留已交付原始数据；需要重跑时在副本运行：

```sh
python3 diagnostics/run_probe.py
```

此命令只编译包内两个独立 C translation unit，不使用 Lean 工具链，不修改官方环境。脚本使用 8 类×96 条不同向量×1000 项、80 次重复、7 轮，输出全部原始计时与逐位核对记录。新机器上如浮点环境不满足 RN-even/gradual-subnormal，程序会拒绝运行而不是修改全局设置。

## 2. 独立整数诊断

```sh
python3 diagnostics/independent_diagnostic.py
```

使用脚本自己的输出路径规则；它没有额外 C 性能实验，不代表 native 或 Lean 运行。

## 3. 候选 Lean 编译与依赖审计

在维护者已经存在、版本与依赖均匹配本报告的固定 Lake 项目中执行，路径改为本包的绝对路径。不安装工具链、不修改 lakefile、lean-toolchain、编译选项、bench 或 gate。

```sh
lake env lean /absolute/path/to/package/lean/AdmissionZero.lean
lake env lean /absolute/path/to/package/diagnostics/AuditAdmissionZero.lean
```

Audit 文件为候选的完整独立副本加 `#print axioms` 命令，因此不依赖之前生成的 AdmissionZero.olean，也不会误用旧 olean 冒充新候选。审核输出仅允许 `propext`、`Classical.choice`、`Quot.sound`。组合定理即使依赖审计干净，也仍然具有明确的 normal 参数，不等于已经证明该参数或完整 Kernel。

## 4. 生成 C 的最小观察

下列仅观察该片段的输出，不是目标程序性能验证；所有输出放在临时路径。命令本轮未执行。

```sh
lake env lean -c /tmp/R2W01b_candidate.c /absolute/path/to/package/lean/AdmissionZero.lean
rg -n 'R2W01b|scaleTable|once|box_float32|unbox_float32|array_fget|array_get' /tmp/R2W01b_candidate.c
```

不要用本诊断 C 编译参数取代官方参数。最终需要查看整合后的真实 native sum 生成物，确认 table 获取/once/读取/解箱的位置、zero branch、原序 add 与末尾 finite 守卫的实际形状。片段的 standalone 输出不能证明整合后的优化形态相同。

## 5. 原始证据独立复算

`results/experiment_audit.json` 是已经保存的复算结果，来源脚本为 `diagnostics/audit_results.py`。该脚本按自身位置找到包内 results，读取既有 CSV，不运行或追加 C 实验：

```sh
python3 diagnostics/audit_results.py
```

新复算输出写在脚本同目录的 `experiment_audit.json`，不覆盖交付在 results 的原记录。主报告全部数值都可直接从 `probe_rounds.csv`、`probe_vector_results.csv` 和 `probe_summary.json` 复算。
