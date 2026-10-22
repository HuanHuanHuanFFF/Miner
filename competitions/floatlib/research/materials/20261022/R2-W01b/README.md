# FloatLib R2-W01b research package

新一轮零域扩展与同路径准入研究。日期 2026-10-22（Asia/Shanghai）。

## 先读

- `FloatLib_R2-W01b_report.md`：完整中文报告，含推导、反例、原始数字的解释及完整 Lean 候选。
- `lean/AdmissionZero.lean`：唯一候选片段，只有 `import ContractTensor`；**NOT_RUN**；normal 定理仍是显式接口，不是完成的 Kernel。
- `appendices/source_audit.md`：固定 Lean/FloatLib/官方源码、真实 API 与 codegen/once/boxing 审查。
- `appendices/independent_review.md`：独立数学、候选静态与 C 结果复算审查。

## 诊断

- `diagnostics/zero_merge_probe.c`、`ofbits_external.c`、`run_probe.py`：本轮唯一 C surrogate，三臂、8 类×96 不同向量×1000、7 轮。
- `results/probe_rounds.csv`：全部 168 条计时，不是最好值；其余 probe 文件保留初始化、分布、逐输入/逐向量结果、环境和汇编。
- `diagnostics/independent_diagnostic.py`：独立整数模型；既有输出在 `results/independent_diagnostic.json`。
- `diagnostics/audit_results.py`：复算既有 CSV，不追加 C 实验。
- `diagnostics/AuditAdmissionZero.lean`：候选全文加依赖审计命令的独立诊断文件，**不可当 Kernel 提交**。
- `diagnostics/COMMANDS.md`：复现与固定 Lean 环境检查步骤。

## 来源与完整性

`sources/SOURCE_LIST.md` 与 `source_manifest.json` 含全部 91 个固定公开源码的链接、内容 hash。源码正文未重复打包；可用 `refetch_manifest.py` 按 manifest 内固定 commit 下载与核验。没有私有资料、可执行二进制或工具链。

`SHA256SUMS.txt` 覆盖包内所有其他文件，打包后已核对每项 SHA-256 和 ZIP CRC。Lean 编译、依赖审计、完整 gate 与目标性能未执行；已通过的旧基线来自本轮用户背景，不是本包重新验证的结果。旧包未读、未改。
